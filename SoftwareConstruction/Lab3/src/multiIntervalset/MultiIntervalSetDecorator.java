package multiIntervalset;

import base.Pair;
import intervalSet.IntervalSet;

import java.util.List;
import java.util.Map;
import java.util.Set;

/**
 * The decorator of {@link MultiIntervalSet}.
 * @param <L> the source of the label.
 */

public abstract class MultiIntervalSetDecorator <L> implements MultiIntervalSet<L> {
    protected final MultiIntervalSet<L> multiIntervalSet;

    public MultiIntervalSetDecorator(MultiIntervalSet<L> multiIntervalSet) {
        this.multiIntervalSet = multiIntervalSet;
    }


    @Override
    public MultiIntervalSet<L> empty() {
        return multiIntervalSet.empty();
    }

    @Override
    public boolean insert(long start , long end , L label) {
        return multiIntervalSet.insert(start,end,label);
    }

    @Override
    public boolean insert(L o) {
        return multiIntervalSet.insert(o);
    }

    @Override
    public Set<L> labels() {
        return multiIntervalSet.labels();
    }

    @Override
    public boolean remove(L label) {
        return multiIntervalSet.remove(label);
    }

    @Override
    public intervalSet.IntervalSet<Integer> intervals(L label) {
        return multiIntervalSet.intervals(label);
    }

    @Override
    public Map<L, List<Pair>> getMp() {
        return multiIntervalSet.getMp();
    }

    @Override
    public void checkRep() {
        multiIntervalSet.checkRep();
    }

    @Override
    public void setStart(long start) {
        multiIntervalSet.setStart(start);
    }

    @Override
    public void setEnd(long end) {
        multiIntervalSet.setEnd(end);
    }

    @Override
    public long getStart() {
        return multiIntervalSet.getStart();
    }

    @Override
    public long getEnd() {
        return multiIntervalSet.getEnd();
    }

    @Override
    public void clear() {
        multiIntervalSet.clear();
    }

    @Override
    public void clear(L label) {
        multiIntervalSet.clear(label);
    }
}
