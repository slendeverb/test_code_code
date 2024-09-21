package org.test;

public class App {
    public static void main(String[] args) {
        int[] edges=new int[]{1,0,0,0,0,7,7,5};
        Solution so=new Solution();
        System.out.println(so.edgeScore(edges));
    }
}

class Solution {
    public int edgeScore(int[] edges) {
        int n = edges.length;
        long[] points = new long[n];
        for (int i = 0; i < n; i++) {
            points[edges[i]] += i;
        }
        long maxPoints = -1;
        int res = -1;
        for (int i = 0; i < n; i++) {
            if (points[i] > maxPoints) {
                maxPoints = points[i];
                res = i;
            }
        }
        return res;
    }
}