package org.test;

class Solution {
    public String getSmallestString(String s) {
        char[] t=s.toCharArray();
        for(int i=1;i<t.length;i++){
            char x=t[i-1];
            char y=t[i];
            if(x>y&&x%2==y%2){
                t[i-1]=y;
                t[i]=x;
                break;
            }
        }
        return new String(t);
    }
}

public class App {

    public static void main(String[] args) {
        String s="45320";
        Solution solution=new Solution();
        String smallestString = solution.getSmallestString(s);
        System.out.println(smallestString);
    }
}