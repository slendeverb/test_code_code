package org.test;

public class App {
    public static void main(String[] args) {
        int n = 3;
        int[][] trust = new int[][] { { 1, 3 }, { 2, 3 }, { 3, 1 } };
        Solution so = new Solution();
        System.out.println(so.findJudge(n, trust));
    }
}

class Solution {
    public int findJudge(int n, int[][] trust) {
        int[][] trust_and_trusted = new int[n + 1][2];
        for (int[] trust_pair : trust) {
            trust_and_trusted[trust_pair[0]][0]++;
            trust_and_trusted[trust_pair[1]][1]++;
        }
        int count = 0;
        int ans = -1;
        for (int i = 1; i <= n; i++) {
            int[] pair = trust_and_trusted[i];
            if (pair[0] == 0 && pair[1] == n - 1) {
                count++;
                ans = i;
            }
        }
        if (count != 1) {
            ans = -1;
        }
        return ans;
    }
}