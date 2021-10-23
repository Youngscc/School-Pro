package multiIntervalset;

import intervalSet.CommonIntervalSet;
import intervalSet.*;
import base.Pair;

import java.util.*;

/**
 * This class {@link CommonMultiIntervalSet} implies some basic functions of {@link MultiIntervalSet}
 * @param <L> the resource of the label.
 */

public class CommonMultiIntervalSet<L> implements MultiIntervalSet<L> {

    private final Map<L, List<Pair>> mp = new HashMap<>();
    private long totStart;
    private long totEnd;
    public CommonMultiIntervalSet () {}

    public CommonMultiIntervalSet (IntervalSet<L> initial) throws ClassNotFoundException {
        if (initial == null) throw new ClassNotFoundException("The IntervalSet is null.");
        Map<L,Pair> rp = initial.getMp();
        for (L it : rp.keySet()) this.mp.put(it,new ArrayList<>(mp.get(it)));
        checkRep();
    }

    @Override
    public MultiIntervalSet<L> empty() { return new CommonMultiIntervalSet<L>();
    }

    @Override
    public boolean insert(long start, long end, L label) {
        if (!mp.containsKey(label)) return false;
        mp.get(label).add(new Pair(start,end));
        checkRep();
        return true;
    }

    @Override
    public boolean insert(L label) {
        if (mp.containsKey(label)) return false;
        mp.put(label,new ArrayList<Pair>());
        checkRep();
        return true;
    }

    @Override
    public Set<L> labels() {
        return mp.keySet();
    }

    @Override
    public boolean remove(L label) {
        if (label == null) return false;
        if (!mp.containsKey(label)) return false;
        mp.get(label).clear();
        mp.remove(label);
        return true;
    }

    @Override
    public IntervalSet<Integer> intervals(L label) {
        IntervalSet<Integer> ret = new CommonIntervalSet<Integer>();
        if (!mp.containsKey(label)) return ret;
        Collections.sort(mp.get(label));
        for (int i=0; i<mp.get(label).size(); ++i) ret.insert(mp.get(label).get(i).start(),mp.get(label).get(i).end(),i);
        return ret;
    }


    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        for (L it1:mp.keySet()) {
            sb.append(it1.toString()).append(" :\n");
            for (Pair it2:mp.get(it1)) {
                sb.append(it2.start()).append(" ~ ").append(it2.end()).append("\n");
            }
            sb.append('\n');
        }
        return sb.toString();
    }

    @Override
    public Map<L, List<Pair>> getMp() {
        return new HashMap<>(this.mp);
    }

    @Override
    public void setStart(long start) {
        totStart = start;
    }

    @Override
    public void setEnd(long end) {
        totEnd = end;
    }

    @Override
    public long getStart() {
        return totStart;
    }

    @Override
    public long getEnd() {
        return totEnd;
    }

    @Override
    public void clear() { this.mp.clear(); }

    @Override
    public void clear(L label) {this.mp.get(label).clear();}

    public void checkRep() {
        for (L it1:mp.keySet()) {
            for (Pair it2:mp.get(it1)) assert it2.start()<=it2.end();
        }
    }
}
