package Course;

import course.Course;
import org.junit.Test;

import static org.junit.Assert.*;

public class CourseTest {

    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    @Test
    public void testGetID() {
        Course a = new Course(111,"a","a","a",30);
        assertEquals(a.getID(),111);
    }

    @Test
    public void testEquals() {
        Course a = new Course(111,"a","a","a",30);
        Course b = new Course(111,"a","a","a",30);
        Course c = new Course(111,"b","a","a",30);
        Course d = new Course(111,"a","b","a",30);
        Course e = new Course(111,"a","a","b",30);
        Course f = new Course(111,"a","a","a",32);
        assertEquals(a , b);
        assertNotEquals(a , c);
        assertNotEquals(a , d);
        assertNotEquals(a , e);
        assertNotEquals(a , f);
    }
}
