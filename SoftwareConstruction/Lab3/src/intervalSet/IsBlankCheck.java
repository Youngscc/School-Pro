package intervalSet;

import base.Pair;

import java.util.*;

/**
 * A decorator to check if there is blank.
 * @param <L> the source of the labels.
 */

public class IsBlankCheck<L> extends IntervalSetDecorator<L>{

    public IsBlankCheck(IntervalSet<L> intervalSet) {
        super(intervalSet);
    }

    /**
     * Check if there is no blank among all the intervals.
     * @return true if there is no blank among all the intervals or no if not.
     */
    public boolean blankCheck() {
        if (this.intervalSet.getMp().size() == 0) return true;
        List<Pair> lt = new ArrayList<>();
        for (L it:this.intervalSet.getMp().keySet()) lt.add(this.intervalSet.getMp().get(it));
        Collections.sort(lt);
        long i = lt.get(0).start();
        for (Pair it:lt) {
            if (i < it.start()-1) return false;
            i = Math.max(i,it.end());
        }
        return lt.get(0).start() == this.intervalSet.getStart() && lt.get(lt.size() - 1).end() == this.intervalSet.getEnd();
    }
}
