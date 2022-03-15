package duty;

import org.junit.Test;

import static org.junit.Assert.*;

public class EmployeeTest {
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    @Test
    public void testEquals() {
        Employee a = new Employee("a","a","1111");
        Employee b = new Employee("a","a","1111");
        Employee c = new Employee("b","a","1111");
        Employee d = new Employee("a","b","1111");
        Employee e = new Employee("a","a","1112");
        assertEquals(a , b);
        assertNotEquals(a , c);
        assertNotEquals(a , d);
        assertNotEquals(a , e);

    }
}
