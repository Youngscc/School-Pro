package intervalSet;

import org.junit.Test;

import static org.junit.Assert.*;

public class IsRepeatCheckTest {

    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public IntervalSet<String> emptyInstance() {
        return new CommonIntervalSet<>();
    }

    @Test
    public void testRepeatCheck() {
        IsRepeatCheck<String> s = new IsRepeatCheck<>(new CommonIntervalSet<>());
        s.insert(1,3,"a");
        s.insert(6,9,"b");
        assertTrue(s.repeatCheck());
        s.insert(3,4,"c");
        assertFalse(s.repeatCheck());
    }
}
