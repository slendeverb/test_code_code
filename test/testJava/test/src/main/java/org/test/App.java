package org.test;

import java.math.BigInteger;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

class Solution {
    public int maxTotalReward(int[] rewardValues) {
        int m=0;
        for(int v:rewardValues){
            m=Math.max(v, m);
        }
        Set<Integer> set=new HashSet<>();
        for(int v:rewardValues){
            if(v==m-1){
                return 2*m-1;
            }
            if(set.contains(v)){
                continue;
            }
            if(set.contains(m-1-v)){
                return 2*m-1;
            }
            set.add(v);
        }
        Arrays.sort(rewardValues);
        int pre=0;
        BigInteger f=BigInteger.ONE;
        for(int v:rewardValues){
            if(v==pre){
                continue;
            }
            BigInteger mask=BigInteger.ONE.shiftLeft(v).subtract(BigInteger.ONE);
            f=f.or(f.and(mask).shiftLeft(v));
            pre=v;
        }
        return f.bitLength()-1;
    }
}

public class App {
    
    public static void main(String[] args) {
        long start=System.currentTimeMillis();
        BigInteger bigInteger=new BigInteger("4");
        System.out.println(bigInteger.pow(1000000));
        long end=System.currentTimeMillis();
        System.out.println(end-start);
    }
}