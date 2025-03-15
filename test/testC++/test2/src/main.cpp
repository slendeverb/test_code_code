#include <bits/stdc++.h>
using namespace std;

template<typename T>
class SharedCount{
private:
	T* ptr;
	int count;
	
	SharedCount(const SharedCount&) = delete;
	SharedCount& operator=(const SharedCount&) = delete;
	
public:
	SharedCount(T* ptr_): ptr(ptr_),count(1){}
	
	~SharedCount(){
		delete ptr;
	}
	
	void increase(){
		++count;
	}
	
	void decrease(){
		if(--count==0){
			delete this;
		}
	}
	
	T* get(){
		return ptr;
	}
};

template<typename T>
class SharedPtr{
private:
	T* ptr;
	SharedCount<T>* countPtr;
	
public:
	SharedPtr(T* ptr_=nullptr): ptr(ptr_){
		if(ptr_!=nullptr){
			countPtr=new SharedCount<T>(ptr_);
		}else{
			ptr_=nullptr;
		}
	}
	
	SharedPtr(const SharedPtr& other): ptr(other.ptr),countPtr(other.countPtr){
		if(countPtr!=nullptr){
			countPtr->increase();
		}
	}
	
	SharedPtr(SharedPtr&& other): ptr(other.ptr),countPtr(other.countPtr){
		other.ptr=nullptr;
		other.countPtr=nullptr;
	}
	
	~SharedPtr(){
		if(countPtr){
			countPtr->decrease();
		}
	}
	
	T* operator->() const {
		return ptr;
	}
	
	T& operator*() const {
		return *ptr;
	}
	
	void reset(T* p=nullptr){
		if(p!=ptr){
			if(countPtr){
			    countPtr->decrease();
		    }
		}
		ptr=p;
		if(p){
			countPtr=new SharedCount<T>(p);
		}else{
			countPtr=nullptr;
		}
	}
	
	T* get() const {
		return ptr;
	}
};

int main() {
	SharedPtr<std::vector<int>> ptr(new std::vector<int>(10,0));
    std::cout<<ptr->front()<<"\n";
}