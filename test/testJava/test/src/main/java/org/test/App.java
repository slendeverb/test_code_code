package org.test;

import java.util.Arrays;
import java.util.HashSet;

public class App {
    public static void main(String[] args) {
        String[] ideas=new String[]{"coffee","donuts","time","toffee"};
        System.out.println(new Solution().distinctNames(ideas));
    }
}

class Solution{
    @SuppressWarnings("unchecked")
    public long distinctNames(String[] ideas){
        HashSet<String>[] groups=new HashSet[26];
        Arrays.setAll(groups,i->new HashSet<>());
        for(String s:ideas){
            groups[s.charAt(0)-'a'].add(s.substring(1));
        }

        long res=0;
        for(int a=1;a<26;a++){
            for(int b=0;b<a;b++){
                long m=0;
                for(String s:groups[a]){
                    if(groups[b].contains(s)){
                        m++;
                    }
                }
                res+=(long)(groups[a].size()-m)*(groups[b].size()-m);
            }
        }
        return res*2;
    }
}