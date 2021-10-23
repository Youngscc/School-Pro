package multiIntervalSet;

import multiIntervalset.CommonMultiIntervalSet;
import multiIntervalset.IsRepeatCheck;
import org.junit.Test;

import static org.junit.Assert.*;

public class IsRepeatCheckTest {

    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    @Test
    public void testRepeatCheck() {
        IsRepeatCheck<String> s = new IsRepeatCheck<>(new CommonMultiIntervalSet<>());
        s.insert("a");
        s.insert(1,3,"a");
        s.insert(6,9,"a");
        assertTrue(s.repeatCheck());
        s.insert(3,4,"a");
        assertFalse(s.repeatCheck());
    }
}
