package intervalSet;

import base.Pair;

import java.util.Map;
import java.util.Set;

/**
 * The decorator of {@link IntervalSet}.
 * @param <L> the source of the label.
 */

public abstract class IntervalSetDecorator<L> implements IntervalSet<L>{
    protected final IntervalSet<L> intervalSet;

    public IntervalSetDecorator (IntervalSet<L> intervalSet) {
        this.intervalSet = intervalSet;
    }

    @Override
    public IntervalSet<L> empty() {
        return intervalSet.empty();
    }

    @Override
    public void insert(long start , long end , L label) {
        intervalSet.insert(start, end, label);
    }

    @Override
    public Set<L> labels() {
        return intervalSet.labels();
    }

    @Override
    public boolean remove(L label) {
        return intervalSet.remove(label);
    }

    @Override
    public long start(L label) throws ClassNotFoundException {
        return intervalSet.start(label);
    }

    @Override
    public long end(L label) throws ClassNotFoundException {
        return intervalSet.end(label);
    }

    @Override
    public Map<L, Pair> getMp() {
        return intervalSet.getMp();
    }

    @Override
    public void checkRep() {
        intervalSet.checkRep();
    }

    @Override
    public void setStart(long start) { intervalSet.setStart(start); }

    @Override
    public void setEnd(long end) { intervalSet.setEnd(end); }

    @Override
    public long getStart() { return intervalSet.getStart(); }

    @Override
    public long getEnd() { return intervalSet.getEnd(); }

    @Override
    public void clear() { intervalSet.clear(); }
}
