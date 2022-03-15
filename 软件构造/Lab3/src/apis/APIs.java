package apis;

import intervalSet.IntervalSet;
import multiIntervalset.MultiIntervalSet;
import base.Pair;

import java.util.*;

/**
 * API
 * @param <L> the recourse of label
 */

public class APIs<L> {



    /**
     * Calculate the free time ratio.
     * @param set a set to calculate.
     * @return the free time ratio.
     * @throws ArithmeticException if the total length is zero.
     */
    public double calcFreeTimeRatio(IntervalSet<L> set) throws ArithmeticException{
        if (set.getEnd() < set.getStart()) throw new ArithmeticException(String.format("Something was wrong when calculating."));
        List<Pair> lt = new ArrayList<>();
        for (L it:set.getMp().keySet()) lt.add(set.getMp().get(it));
        Collections.sort(lt);
        double tot = 0,mr = set.getStart()-1;
        for (int i=0; i<lt.size(); ++i) {
            if (mr < lt.get(i).start()-1) tot += lt.get(i).start()-mr-1;
            mr = Math.max(mr,lt.get(i).end());
        }
        tot += set.getEnd()-mr;
        return tot / (double) (set.getEnd()-set.getStart()+1);
    }

    /**
     * Calculate the free time ratio.
     * @param set set a set to calculate.
     * @return the free time ratio.
     * @throws ArithmeticException if the total length is zero.
     */
    public double calcFreeTimeRatio(MultiIntervalSet<L> set) throws ArithmeticException{
        if (set.getEnd() < set.getStart()) throw new ArithmeticException("Something was wrong when calculating.");
        List<Pair> lt = new ArrayList<>();
        for (L it:set.getMp().keySet())
            lt.addAll(set.getMp().get(it));
        Collections.sort(lt);
        double tot = 0,mr = set.getStart()-1;
        for (Pair pair : lt) {
            if (mr < pair.start() - 1) tot += pair.start() - mr - 1;
            mr = Math.max(mr , pair.end());
        }
        tot += set.getEnd()-mr;
        return tot / (double) (set.getEnd()-set.getStart()+1);
    }

    /**
     * Calculate the conflict ratio.
     * @param set set a set to calculate.
     * @return the conflict ratio.
     * @throws ArithmeticException if the total length is zero.
     */
    public double calcConflictRatio(IntervalSet<L> set) throws ArithmeticException {
        if (set.getEnd() < set.getStart()) throw new ArithmeticException(String.format("Something was wrong when calculating."));
        Map<Long,Integer> t = new HashMap<>();
        for (L it:set.labels()) {
            try {
                for (long i=set.start(it); i<=set.end(it); ++i) {
                    if (!t.containsKey(i)) t.put(i,0);
                    t.put(i,t.get(i)+1);
                }
            } catch (ClassNotFoundException e) {
                e.printStackTrace();
            }
        }
        double tot = 0;
        for (Long it:t.keySet()) {
            if (t.get(it) > 1) tot = tot+1;
        }
        return tot / (double) (set.getEnd()-set.getStart()+1);
    }

    /**
     * Calculate the conflict ratio.
     * @param set set a set to calculate.
     * @return the conflict ratio.
     * @throws ArithmeticException if the total length is zero.
     */
    public double calcConflictRatio(MultiIntervalSet<L> set) throws ArithmeticException{
        if (set.getEnd() < set.getStart()) throw new ArithmeticException(String.format("Something was wrong when calculating."));
        Map<Long,Integer> t = new HashMap<>();
        for (L it:set.labels()) {
            for (Pair itt: set.getMp().get(it))
               for (long i=itt.start(); i<=itt.end(); ++i) {
                   if (!t.containsKey(i)) t.put(i,0);
                    t.put(i,t.get(i)+1);
                }
        }
        double tot = 0;
        for (Long it:t.keySet()) {
            if (t.get(it) > 1) tot = tot+1;
        }
        return tot / (double) (set.getEnd()-set.getStart()+1);
    }
}
