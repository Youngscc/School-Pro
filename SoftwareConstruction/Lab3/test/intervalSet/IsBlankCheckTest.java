package intervalSet;

import org.junit.Test;
import static org.junit.Assert.*;
import java.util.*;

public class IsBlankCheckTest {
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public IntervalSet<String> emptyInstance() {
        return new CommonIntervalSet<>();
    }

    @Test
    public void testBlankCheck() {
        IsBlankCheck<String> s = new IsBlankCheck<>(new CommonIntervalSet<>());
        s.insert(1,3,"a");
        s.insert(6,9,"b");
        assertFalse(s.blankCheck());
        s.insert(4,5,"c");
        assertTrue(s.blankCheck());
    }
}
