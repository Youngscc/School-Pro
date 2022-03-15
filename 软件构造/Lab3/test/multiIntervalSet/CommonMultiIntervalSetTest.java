package multiIntervalSet;

import base.Pair;
import multiIntervalset.CommonMultiIntervalSet;
import multiIntervalset.MultiIntervalSet;
import org.junit.Test;

import java.util.*;

import static org.junit.Assert.*;

public class CommonMultiIntervalSetTest {
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public MultiIntervalSet<String> emptyInstance() {
        return new CommonMultiIntervalSet<>();
    }

    @Test
    public void testInitialMapEmpty() {
        assertEquals(Collections.emptyMap(), emptyInstance().getMp());
    }

    @Test
    public void testInsert() {
        MultiIntervalSet<String> s = emptyInstance();
        Map<String, ArrayList<Pair>> mp = new HashMap<>();
        ArrayList<Pair> now = new ArrayList<>();
        HashSet<String> name = new HashSet<>();
        assertFalse(s.insert(1,5,"a"));
        assertFalse(s.labels().contains("a"));
        assertEquals(Collections.emptyMap(),s.getMp());

        assertTrue(s.insert("a"));
        name.add("a");
        assertEquals(s.labels(),name);

        assertTrue(s.insert(1,5,"a"));
        now.add(new Pair(1,5));
        mp.put("a", now);
        assertEquals(mp,s.getMp());
        assertTrue(s.labels().contains("a"));
    }

    @Test
    public void testLabels() {
        MultiIntervalSet<String> s = emptyInstance();
        Set<String> ans = new HashSet<>();
        s.insert("a");
        s.insert("b");
        ans.add("a");
        ans.add("b");
        assertEquals(ans,s.getMp().keySet());
        assertTrue(s.getMp().containsKey("a"));
        assertFalse(s.getMp().containsKey("c"));
    }

    @Test
    public void testRemove() {
        MultiIntervalSet<String> s = emptyInstance();
        Map<String, ArrayList<Pair>> mp = new HashMap<>();
        s.insert("a");
        s.insert("b");
        s.insert(1,5,"a");
        s.insert(1,5,"b");
        assertTrue(s.remove("b"));
        assertFalse(s.remove("c"));
        ArrayList<Pair> now = new ArrayList<>();
        now.add(new Pair(1,5));
        mp.put("a", now);
        assertEquals(mp,s.getMp());
    }

    @Test
    public void testSetStart() {
        MultiIntervalSet<String> s = emptyInstance();
        s.setStart(4);
        assertEquals(4,s.getStart());
    }

    @Test
    public void testSetEnd() {
        MultiIntervalSet<String> s = emptyInstance();
        s.setEnd(4);
        assertEquals(4,s.getEnd());
    }

    @Test
    public void testClear() {
        MultiIntervalSet<String> s = emptyInstance();
        s.insert("a");
        s.insert("b");
        s.insert("c");
        s.insert(1,5,"a");
        s.insert(2,8,"b");
        s.insert(1,7,"c");
        s.clear();
        assertEquals(s.getMp(),Collections.emptyMap());
    }
}
