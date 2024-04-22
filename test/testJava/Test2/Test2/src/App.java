
public class App {
    public static void main(String[] args) {
        Animal a[]=new Animal[3];
        a[0]=new Animal();
        a[1]=new Tiger();
        a[2]=new Bird();
        for(Animal animal:a){
            animal.run();
        }
    }
}

class Animal{
    void run(){
        System.out.println("Animal is running slow...");
    }
}
class Tiger extends Animal{
    @Override
    void run(){
        System.out.println("Tiger is running fast...");
    }
}
class Bird extends Animal{
    @Override
    void run(){
        System.out.println("Bird is flying fast...");
    }
}