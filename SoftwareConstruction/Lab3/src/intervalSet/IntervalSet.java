package intervalSet;

import base.Pair;

import java.util.*;

/**
 * This class {@link IntervalSet} is an interface to represent a set.
 *
 * @param <L> the resource of the label.
 */

public interface IntervalSet<L> {

    /**
     * Return a new empty interval set.
     * @return a new empty interval set.
     */
    IntervalSet<L> empty();

    /**
     * Add a new interval into the set.
     * @param start The start position of the interval.
     * @param end The end position of the interval.
     * @param label The label of the interval.
     */
    void insert(long start, long end, L label);

    /**
     * Return a set of all labels of the interval set.
     * @return a set of all labels of the interval set.
     */
    Set<L> labels();

    /**
     * Remove the specific interval from the set.
     * @param label the label of the specific interval.
     * @return true if remove successfully and false or not.
     */
    boolean remove(L label);

    /**
     * Return the start position of a specific label.
     * @param label The specific label.
     * @return the start position of the specific label.
     * @throws ClassNotFoundException if the label is null.
     */
    long start (L label) throws ClassNotFoundException ;

    /**
     * Return the end position of a specific label.
     * @param label The specific label.
     * @return the end position of the specific label.
     * @throws ClassNotFoundException if the label is null.
     */

    long end (L label) throws ClassNotFoundException ;

    /**
     * Return the connect between all labels and their intervals.
     * @return the connect between all labels and their intervals.
     */
    Map<L, Pair> getMp();

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
}
