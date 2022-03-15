package base;

/**
 * This is a immutable class.
 */

public class Pair implements Comparable<Pair>{
    private final long start;
    private final long end;

    public Pair(long start,long end) {
        this.start = start;
        this.end = end;
    }

    /**
     * Return the start position.
     * @return the start position
     */
    public long start(){ return start;}

    /**
     * Return the end position.
     * @return the end position
     */
    public long end(){ return end;}

    @Override
    public int compareTo(Pair o) {
        long i = this.start() - o.start();
        if(i == 0){
            if (this.end() - o.end() > 0) return 1;
            else if (this.end() - o.end() < 0) return -1;
            return 0;
        }
        else if(i < 0) return -1;
        else return 1;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        Pair other = (Pair) obj;
        if (start != other.start) return false;
        if (end != other.end) return false;
        return true;
    }
}
