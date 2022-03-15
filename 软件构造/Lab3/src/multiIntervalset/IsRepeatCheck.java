package multiIntervalset;

import base.Pair;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class IsRepeatCheck<L> extends MultiIntervalSetDecorator<L> {
    public IsRepeatCheck(MultiIntervalSet<L> multiIntervalSet) {
        super(multiIntervalSet);
    }

    public boolean repeatCheck() {
        if (this.getMp().size() == 0) return true;
        List<Pair> lt = new ArrayList<>();
        for (L it:this.multiIntervalSet.labels())
            lt.addAll(this.multiIntervalSet.getMp().get(it));
        Collections.sort(lt);
        long i=-1;
        for (Pair it:lt) {
            if (i >= it.start()) return false;
            i = it.end();
        }
        return true;
    }
}
