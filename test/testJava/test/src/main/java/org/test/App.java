package org.test;

public class App {
    public static void main(String[] args) {
        MyClass myClass1=MyClass.getInstance();
        MyClass myClass2=MyClass.getInstance();
        System.out.println(myClass1);
        System.out.println(myClass2);
        
    }
}

class MyClass{
    private MyClass(){

    }

    private MyClass(MyClass myClass){

    }

    public static MyClass getInstance(){
        if(myClass==null){
            myClass=new MyClass();
        }
        return myClass;
    }

    private static volatile MyClass myClass;
}