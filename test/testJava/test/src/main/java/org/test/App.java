package org.test;

public class App {
    public static void main(String[] args) {
        
    }
}

class Shape{
    void display(int x1,int y1,int x2,int y2){

    }
}

class LegacyRectangle{
    void display(int x1,int y1,int w,int h){

    }
}

class Rectangle extends Shape{
    LegacyRectangle legacyRectangle=new LegacyRectangle();
    @Override
    void display(int x1, int y1, int x2, int y2) {
        legacyRectangle.display(x1, y1, Math.abs(x2-x1), Math.abs(y2-y1));
    }
}