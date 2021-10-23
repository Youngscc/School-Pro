package base;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.*;

public class PairTest {
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    @Test
    public void testStart() {
        Pair a = new Pair(1,2);
        assertEquals(a.start(),1);
    }

    @Test
    public void testEnd() {
        Pair a = new Pair(1,2);
        assertEquals(a.end(),2);
    }

    @Test
    public void testCompareTo() {
        List <Pair> a = new ArrayList<>();
        List <Pair> b = new ArrayList<>();
        a.add(new Pair(3,4));
        a.add(new Pair(4,7));
        a.add(new Pair(3,5));
        a.add(new Pair(1,5));
        Collections.sort(a);
        b.add(new Pair(1,5));
        b.add(new Pair(3,4));
        b.add(new Pair(3,5));
        b.add(new Pair(4,7));
        assertEquals(a,b);
    }

    @Test
    public void testEquals() {
        Pair a = new Pair(1,3);
        Pair b = new Pair(1,3);
        Pair c = new Pair(2,3);
        Pair d = new Pair(1,2);
        assertEquals(a , b);
        assertNotEquals(a , c);
        assertNotEquals(a , d);
    }
}
