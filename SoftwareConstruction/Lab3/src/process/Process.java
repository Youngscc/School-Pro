package process;

/**
 * This is an immutable class.
 */

public class Process {
    private final long id;
    private final String name;
    private final long minTime;
    private final long maxTime;

    public Process(long id,String name,long minTime,long maxTime) {
        this.id = id;
        this.name = name;
        this.minTime = minTime;
        this.maxTime = maxTime;
        checkRep();
    }

    /**
     * Get the minimal run time.
     * @return the minimal run time.
     */
    public Long getMinTime(){ return minTime; }

    /**
     * Get the maximum run time.
     * @return the maximum run time.
     */
    public Long getMaxTime(){ return maxTime; }

    /**
     * Check if id positive and maximum run time not less than minimal run time.
     */
    public void checkRep() {
        assert id > 0;
        assert name != null;
        assert minTime > 0;
        assert maxTime >= minTime;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + (int)id;
        result = prime * result + name.hashCode();
        result = prime * result + (int)minTime;
        result = prime * result + (int)maxTime;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        Process other = (Process) obj;
        if (id != other.id) return false;
        if (!name.equals(other.name)) return false;
        return true;
    }

    @Override
    public String toString() {
        return id + ": " + name + "   Min time = " + minTime + "   Max time = " + maxTime;
    }
}
