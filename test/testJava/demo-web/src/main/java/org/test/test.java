package org.test;

public class test {
    public static void main(String[] args) {
        int num = 7 + (int) (Math.random() * 13);
        if (num <= 13) {
            System.out.print("<h1>Hello</h1><br>");
        } else {
            System.out.print("<h1>hello</h1><br>");
        }
    }
}
