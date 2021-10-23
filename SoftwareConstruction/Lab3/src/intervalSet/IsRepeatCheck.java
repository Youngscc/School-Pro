package intervalSet;

import base.Pair;

import java.util.*;

/**
 * A decorator to check if there is repeat.
 * @param <L> the resource of the label.
 */

public class IsRepeatCheck<L> extends IntervalSetDecorator<L> {

    public IsRepeatCheck(IntervalSet<L> intervalSet) {
        super(intervalSet);
    }

    /**
     * Check if there are intervals repeating.
     * @return true if there are no intervals repeating or false if not.
     */
    public boolean repeatCheck(){
        if (this.intervalSet.getMp().size() == 0) return true;
        List<Pair> lt = new ArrayList<>();
        for (L it:this.intervalSet.labels()) lt.add(this.intervalSet.getMp().get(it));
        Collections.sort(lt);
        long i=-1;
        for (Pair it:lt) {
            if (i >= it.start()) return false;
            i = it.end();
        }
        return true;
    }
}
