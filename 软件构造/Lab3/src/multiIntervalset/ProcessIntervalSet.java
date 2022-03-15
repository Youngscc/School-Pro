package multiIntervalset;

import base.Pair;

import java.util.*;

public class ProcessIntervalSet {
    private final MultiIntervalSet<process.Process> set;
    private final List<process.Process> hang;
    private final Map<process.Process, Long> RanTime;
    private long nowTime;
    private process.Process nowRunning;

    public ProcessIntervalSet() {
        this.set = new IsRepeatCheck<>(new CommonMultiIntervalSet<>());
        this.hang = new LinkedList<>();
        this.RanTime = new HashMap<>();
        nowTime = 0;
        nowRunning = null;
    }

    public void checkRep() {set.checkRep();}

    public boolean insertProcess(process.Process o) {
        if  (set.insert(o)) {
            RanTime.put(o,0L);
            hang.add(o);
            System.out.println("This process has been added successful!");
            checkRep();
            return true;
        }
        else System.err.println("ERROR: This process has been added before");
        return false;
    }

    public void run(int p) {
        Random rd = new Random();
        if (hang.size() > 0) {
            int opt = 0;
            if (p == 1) opt = rd.nextInt(hang.size() + 1);
            else if (p == 2) {
                for (int i = 1; i < hang.size(); ++i) {
                    if (hang.get(i).getMaxTime() - RanTime.get(hang.get(i)) < hang.get(opt).getMaxTime() - RanTime.get(hang.get(opt)))
                        opt = i;
                }
                opt++;
            }

            if (opt == 0) {
                nowTime += rd.nextInt(10)+1;
                nowRunning = null;
            }
            else {
                nowRunning = hang.get(opt-1);
                long now = rd.nextLong();
                long runTime = (now > 0? now:-now) % (hang.get(opt - 1).getMaxTime() - RanTime.get(hang.get(opt - 1))) + 1;
                set.insert(nowTime , nowTime + runTime - 1 , hang.get(opt - 1));
                nowTime += runTime;
                RanTime.replace(hang.get(opt - 1) , RanTime.get(hang.get(opt - 1)) + runTime);
                if (RanTime.get(hang.get(opt - 1)) >= hang.get(opt - 1).getMinTime() && RanTime.get(hang.get(opt - 1)) <= hang.get(opt - 1).getMaxTime())
                    hang.remove(opt - 1);
            }
        } else System.out.println("All the processes have been finished.");
        System.out.println("Finish arrangement.");
    }

    public void show() {
        Map<Pair, process.Process> mpp = new TreeMap<>();
        for (process.Process it:set.getMp().keySet()) {
            for (Pair itt:set.getMp().get(it)) {
                mpp.put(itt,it);
            }
        }

        System.out.println("The schedule is as following");
        for (Pair it: mpp.keySet()) System.out.println(it.start() + " ~ " + it.end() + ": " + mpp.get(it).toString());

        if (nowRunning == null) System.out.println("No Process is running now.");
        else System.out.println("Now running: "+nowRunning.toString());
    }
}