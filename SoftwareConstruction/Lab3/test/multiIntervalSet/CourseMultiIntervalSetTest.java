package multiIntervalSet;
import static org.junit.Assert.*;


import course.Course;
import multiIntervalset.CourseIntervalSet;
import org.junit.Test;
import java.util.Set;
public class CourseMultiIntervalSetTest {

    @Test(expected = AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public CourseIntervalSet emptyInstance() {
        return new CourseIntervalSet();
    }

    @Test
    public void testAddCourse() {
        CourseIntervalSet s = emptyInstance();
        Course a = new Course(1111,"a","a","a",24);
        assertTrue(s.addCourse(a));
        assertFalse(s.addCourse(a));
    }

    @Test
    public void testAddCourseTime() {
        CourseIntervalSet s = emptyInstance();
        Course a = new Course(1111,"a","a","a",4);
        assertFalse(s.addCourseTime(1111,1,1));
        s.addCourse(a);
        assertTrue(s.addCourseTime(1111,1,1));
        assertTrue(s.addCourseTime(1111,2,2));
        assertFalse(s.addCourseTime(1111,3,3));
    }
}
