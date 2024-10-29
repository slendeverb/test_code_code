package org.test;

import java.util.ArrayList;
import java.util.List;

class Solution {
    public List<String> validStrings(int n) {
        List<String> ans=new ArrayList<>();
        char[] path=new char[n];
        dfs(0, n, path, ans);
        return ans;
    }

    private void dfs(int i,int n,char[] path,List<String> ans){
        if(i==n){
            ans.add(new String(path));
            return;
        }
        
        path[i]='1';
        dfs(i+1, n, path, ans);

        if(i==0||path[i-1]=='1'){
            path[i]='0';
            dfs(i+1, n, path, ans);
        }
    }
}

public class App {

    public static void main(String[] args) {
        
    }
}