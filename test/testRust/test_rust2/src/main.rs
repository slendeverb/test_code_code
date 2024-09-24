use std::{
    fs,
    io::{Read, Write},
    net::{TcpListener, TcpStream},
    sync::{
        mpsc::{self},
        Arc, Mutex,
    },
    thread,
    time::Duration,
};

struct Worker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}

trait FnBox {
    fn call_box(self: Box<Self>);
}

impl<F: FnOnce()> FnBox for F {
    fn call_box(self: Box<F>) {
        (*self)()
    }
}

impl Worker {
    fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Message>>>) -> Worker {
        let thread = thread::spawn(move || loop {
            let message=receiver.lock().unwrap().recv().unwrap();
            match message {
                Message::NewJob(job)=>{
                    println!("Worker {} got a job; executing.",id);
                    job.call_box();
                }
                Message::Terminate=>{
                    println!("Worker {} was told to terminate.",id);
                    break;
                }
            }
        });
        Worker { id, thread:Some(thread) }
    }
}

type Job = Box<dyn FnBox + Send + 'static>;

enum Message {
    NewJob(Job),
    Terminate,
}

struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Message>,
}

impl ThreadPool {
    /// Create a new ThreadPool.
    ///
    /// The size is the number of the threads in the pool.
    ///
    /// # Panics
    ///
    /// The 'new' function will panic if the size is zero.
    fn new(size: usize) -> ThreadPool {
        assert!(size > 0);
        let (sender, receiver) = mpsc::channel();
        let receiver = Arc::new(Mutex::new(receiver));
        let mut workers = Vec::with_capacity(size);
        for id in 0..size {
            workers.push(Worker::new(id, receiver.clone()));
        }
        ThreadPool { workers, sender }
    }

    fn execute<F>(&self, f: F)
    where
        F: FnOnce() + Send + 'static,
    {
        let job = Box::new(f);
        self.sender.send(Message::NewJob(job)).unwrap();
    }
}

impl Drop for ThreadPool {
    fn drop(&mut self) {
        println!("Sending terminate message to all workers.");

        for _ in &mut self.workers{
            self.sender.send(Message::Terminate).unwrap();
        }
        println!("Shutting down all workers.");

        for worker in &mut self.workers {
            println!("Shutting down worker {}",worker.id);
            if let Some(thread) = worker.thread.take() {
                thread.join().unwrap();
            }
        }
    }
}

fn handle_connection(mut stream: TcpStream) {
    let mut buffer = [0; 1024];
    stream.read(&mut buffer).unwrap();
    let get = b"GET / HTTP/1.1\r\n";
    let sleep = b"GET /sleep HTTP/1.1\r\n";
    let ok = ("HTTP/1.1 200 OK\r\n\r\n", "src/hello.html");
    let err = ("HTTP/1.1 404 NOT FOUND\r\n\r\n", "src/404.html");

    let (status_line, filename) = if buffer.starts_with(get) {
        ok
    } else if buffer.starts_with(sleep) {
        thread::sleep(Duration::from_secs(5));
        ok
    } else {
        err
    };
    let content = fs::read_to_string(filename).unwrap();
    let responce = format!("{}{}", status_line, content);
    stream.write(responce.as_bytes()).unwrap();
    stream.flush().unwrap();
}

fn main() {
    let listener = TcpListener::bind("127.0.0.1:7878").unwrap();
    let pool = ThreadPool::new(4);
    for stream in listener.incoming().take(10) {
        let stream = stream.unwrap();
        pool.execute(|| {
            handle_connection(stream);
        });
    }
    println!("Shutting down.");
}
