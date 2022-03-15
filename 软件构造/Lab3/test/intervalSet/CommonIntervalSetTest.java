package intervalSet;

import base.Pair;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.*;

/**
 * This Class {@link CommonIntervalSetTest} is to test {@link CommonIntervalSet}.
 */

public class CommonIntervalSetTest {

    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    /**
     * Generate a new CommonIntervalSet.
     * @return a new CommonIntervalSet.
     */
    public IntervalSet<String> emptyInstance() {
        return new CommonIntervalSet<>();
    }

    /**
     * Test if the set is empty initially,
     */
    @Test
    public void testInitialMapEmpty() {
        assertEquals(Collections.emptyMap(), emptyInstance().getMp());
    }

    /**
     * Test {@link CommonIntervalSet#insert(long, long, Object)}.
     * There is or no such a member.
     */
    @Test
    public void testInsert() {
        IntervalSet<String> s = emptyInstance();
        Map<String, Pair> mp = new HashMap<>();
        s.insert(1,5,"a");
        mp.put("a", new Pair(1,5));
        assertEquals(mp,s.getMp());
    }

    /**
     * Test{@link CommonIntervalSet#labels()}.
     *
     * Test if there is or no such members before.
     */
    @Test
    public void testLabels() {
        IntervalSet<String> s = emptyInstance();
        Set<String> ans = new HashSet<>();
        s.insert(1,5,"a");
        s.insert(1,5,"b");
        ans.add("a");
        ans.add("b");
        assertEquals(ans,s.getMp().keySet());
    }

    /**
     * Test{@link CommonIntervalSet#remove(Object)}.
     *
     * Test if there is or no such members before.
     */
    @Test
    public void testRemove() {
        IntervalSet<String> s = emptyInstance();
        Map<String, Pair> mp = new HashMap<>();
        s.insert(1,5,"a");
        s.insert(1,5,"b");
        s.remove("b");
        mp.put("a", new Pair(1,5));
        assertEquals(mp,s.getMp());
    }

    /**
     * Test {@link CommonIntervalSet#start(Object)}.
     * Test if there is or no such members before.
     */
    @Test
    public void testStart() {
        IntervalSet<String> s = emptyInstance();
        Map<String, Pair> mp = new HashMap<>();
        s.insert(1,5,"a");
        try {
            assertEquals(1,s.start("a"));
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Test{@link CommonIntervalSet#end(Object)}.
     * Test if there is or no such members before.
     */
    @Test
    public void testEnd() {
        IntervalSet<String> s = emptyInstance();
        Map<String, Pair> mp = new HashMap<>();
        s.insert(1,5,"a");
        try {
            assertEquals(5,s.end("a"));
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     * Test {@link CommonIntervalSet#start(Object)}.
     */
    @Test
    public void testSetStart() {
        IntervalSet<String> s = emptyInstance();
        s.setStart(4);
        assertEquals(4,s.getStart());
    }

    /**
     * Test{@link CommonIntervalSet#end(Object)}
     */
    @Test
    public void testSetEnd() {
        IntervalSet<String> s = emptyInstance();
        s.setEnd(4);
        assertEquals(4,s.getEnd());
    }

    /**
     * Test{@link CommonIntervalSet#clear()}.
     * Before or after clear.
     */
    @Test
    public void testClear() {
        IntervalSet<String> s = emptyInstance();
        s.insert(1,5,"a");
        s.insert(2,8,"b");
        s.insert(1,7,"c");
        s.clear();
        assertEquals(s.getMp(),Collections.emptyMap());
    }
}
