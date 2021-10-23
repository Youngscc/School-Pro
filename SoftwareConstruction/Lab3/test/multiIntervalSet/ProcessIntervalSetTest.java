package multiIntervalSet;

import static org.junit.Assert.*;
import multiIntervalset.ProcessIntervalSet;
import org.junit.Test;
import process.Process;

import java.util.HashSet;
import java.util.Set;

public class ProcessIntervalSetTest {

    @Test(expected = AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public ProcessIntervalSet emptyInstance() {
        return new ProcessIntervalSet();
    }

    @Test
    public void testInsertProcess() {
        ProcessIntervalSet s = emptyInstance();
        Set<Process> st = new HashSet<>();
        Process a = new Process(111111,"a",5,7);
        assertTrue(s.insertProcess(a));
        assertFalse(s.insertProcess(a));
    }
}
