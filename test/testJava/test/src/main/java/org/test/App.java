package org.test;

public class App {
    
    public static void main(String[] args) {
        long start=System.currentTimeMillis();
        for(int i=0;i<1_0000_0;i++){
            System.out.println(i);
        }
        long end=System.currentTimeMillis();
        System.out.println(end-start);
    }
}