package intervalSet;
import static org.junit.Assert.*;

import duty.Employee;
import org.junit.Test;

import java.text.ParseException;

public class DutyIntervalSetTest {

    @Test(expected = AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    public DutyIntervalSet emptyInstance() {
        return new DutyIntervalSet();
    }

    @Test
    public void testInsertEmployee() {
        DutyIntervalSet s = emptyInstance();
        assertTrue( s.insertEmployee(new Employee("a","a","1111111")));
        assertFalse( s.insertEmployee(new Employee("a","a","1111111")));
    }

    @Test
    public void testDeleteEmployee() {
        DutyIntervalSet s = emptyInstance();
        Employee a = new Employee("a","a","1111111");
        Employee b = new Employee("b","b","1111111");
        s.insertEmployee(a);
        s.setStart("2020-10-01");
        s.setEnd("2021-10-01");
        s.insertTask(a,"2021-01-01","2021-01-02");
        assertFalse(s.deleteEmployee(a));
        s.insertEmployee(b);
        assertTrue(s.deleteEmployee(b));
        assertFalse(s.deleteEmployee(b));
    }

    @Test
    public void testInsertTask() {
        DutyIntervalSet s = emptyInstance();
        Employee a = new Employee("a","a","1111111");
        s.setStart("2020-10-01");
        s.setEnd("2021-10-01");
        assertFalse(s.insertTask(a,"2021-01-01","2021-01-02"));
        s.insertEmployee(a);
        assertFalse(s.insertTask(a,"2020-01-01","2020-01-02"));
        assertTrue(s.insertTask(a,"2021-01-01","2021-01-02"));
        assertFalse(s.insertTask(a,"2020-01-04","2020-01-05"));
    }

    @Test
    public void testIsFull() {
        DutyIntervalSet s = emptyInstance();
        Employee a = new Employee("a","a","1111111");
        Employee b = new Employee("b","b","1111111");
        Employee c = new Employee("c","c","1111111");
        s.setStart("2021-10-01");
        s.setEnd("2021-10-10");
        s.insertEmployee(a);
        s.insertEmployee(b);
        s.insertEmployee(c);
        s.insertTask(a,"2021-10-01","2021-10-02");
        s.insertTask(b,"2021-10-03","2021-10-08");
        assertFalse(s.isFull());
        s.insertTask(c,"2021-10-09","2021-10-10");
        assertTrue(s.isFull());
    }
}
