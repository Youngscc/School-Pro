package multiIntervalset;

import intervalSet.IntervalSet;
import base.Pair;

import java.util.*;

/**
 * This class {@link MultiIntervalSet} is an interface to represent a set.
 * @param <L> the resource of the label.
 */

public interface MultiIntervalSet<L> {

    /**
     * Return a new empty interval set.
     * @return a new empty interval set.
     */
    MultiIntervalSet<L> empty();

    /**
     * Add a new interval into the set.
     * @param start The start position of the interval.
     * @param end The end position of the interval.
     * @param label The label of the interval.
     */
    boolean insert(long start, long end, L label);

    /**
     * Add a new label into the label set.
     * @param label the new label.
     * @return true if adding successfully of false if not.
     */
    boolean insert(L label);

    /**
     * Return a set of all labels of the multi interval set.
     * @return a set of all labels of the multi interval set.
     */
    Set<L> labels();

    /**
     * Remove the specific interval from the set.
     * @param label the label of the specific interval.
     * @return true if remove successfully and false or not.
     */
    boolean remove(L label);

    /**
     * Return all the intervals of a specific label.
     * @param label the specific label.
     * @return a set of all the intervals of a specific label.
     */
    IntervalSet<Integer> intervals(L label);

    /**
     * Return the connect between all labels and their intervals.
     * @return the connect between all labels and their intervals.
     */
    Map<L, List<Pair>> getMp();

    /**
     * Check if all the intervals are allowed.
     */
    void checkRep();

    /**
     * Set the totally start position.
     * @param start the totally start position.
     */
    void setStart(long start);

    /**
     * Set the totally end position.
     * @param end the totally end position.
     */
    void setEnd(long end);

    /**
     * Return the totally start position.
     * @return the totally start position.
     */
    long getStart();

    /**
     * Return the totally end position.
     * @return the totally end position.
     */
    long getEnd();

    /**
     * Clear all the intervals and labels.
     */
    void clear();

    /**
     * Clear all the intervals of the specific label.
     */
    void clear(L label);
}