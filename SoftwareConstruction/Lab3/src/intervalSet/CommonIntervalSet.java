package intervalSet;

import base.Pair;
import java.util.*;

/**
 * This class {@link CommonIntervalSet} implies some basic functions of {@link IntervalSet}
 * @param <L> the resource of the label.
 */

public class CommonIntervalSet<L> implements IntervalSet<L>{

    private final Map<L, Pair> mp = new HashMap<>();
    private long totStart = 0;
    private long totEnd = 0;
    public CommonIntervalSet(){ }

    @Override
    public IntervalSet<L> empty() {
        return new CommonIntervalSet<L>();
    }

    @Override
    public void insert(long start, long end, L label) {
        mp.put(label,new Pair(start,end));
        checkRep();
    }

    @Override
    public Set<L> labels() {
        return mp.keySet();
    }

    @Override
    public boolean remove (L label) {
        if (!mp.containsKey(label)) return false;
        mp.remove(label);
        return true;
    }

    @Override
    public long start (L label) throws ClassNotFoundException {
        if (!mp.containsKey(label))
            throw new ClassNotFoundException(String.format("Can't find a class with such label: %s",label.toString()));
        return mp.get(label).start();
    }

    @Override
    public long end (L label) throws ClassNotFoundException {
        if (!mp.containsKey(label))
            throw new ClassNotFoundException(String.format("Can't find a class with such label: %s",label.toString()));
        return mp.get(label).end();
    }

    @Override
    public Map<L, Pair> getMp() {
        return new HashMap<>(mp);
    }

    public void checkRep() {
        for (L it:mp.keySet()) {
            assert mp.get(it).start() <= mp.get(it).end();
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (L it:mp.keySet()) {
            sb.append(it.toString()).append(": ").append(mp.get(it).start()).append(" ~ ").append(mp.get(it).end()).append("\n");
        }
        return sb.toString();
    }

    @Override
    public void clear() {
        this.mp.clear();
    }

    @Override
    public void setStart(long start) {
        this.totStart = start;
    }

    @Override
    public void setEnd(long end) {
        this.totEnd = end;
    }

    @Override
    public long getStart() {
        return this.totStart;
    }

    @Override
    public long getEnd() {
        return this.totEnd;
    }
}
