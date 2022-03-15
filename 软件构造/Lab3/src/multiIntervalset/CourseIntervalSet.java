package multiIntervalset;

import apis.APIs;
import base.Pair;
import course.Course;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;



public class CourseIntervalSet {
    private final MultiIntervalSet<Course> set;
    private final Map<Course,Long> arranged;
    private final APIs<Course> api = new APIs<>();
    private final Map<Long,Integer> from = new HashMap<>(),to = new HashMap<>();
    private Date startDate;
    private int weeks;
    private final SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");

    public CourseIntervalSet() {
        this.startDate = null;
        this.weeks = 0;
        this.set = new CommonMultiIntervalSet<>();
        arranged = new HashMap<>();
        this.set.setStart(1);
        this.set.setEnd(35);
        this.from.put(1L,8);
        this.from.put(2L,10);
        this.from.put(3L,13);
        this.from.put(4L,15);
        this.from.put(5L,19);
        this.to.put(1L,10);
        this.to.put(2L,12);
        this.to.put(3L,15);
        this.to.put(4L,17);
        this.to.put(5L,21);

    }

    public void checkRep() {set.checkRep();}

    /**
     * Set the start date
     * @param startDate start date.
     */

    public void setStartDate(String startDate) {
        try {
            this.startDate = simpleDateFormat.parse(startDate);
        } catch (ParseException e) {
            e.printStackTrace();
        }
    }

    /**
     * Set the week numbers.
     * @param weekNum the week numbers.
     */
    public void setWeekNum(int weekNum) {
        this.weeks = weekNum;
    }

    /**
     * Add a course
     * @param course the course to be added.
     * @return true if it is added successfully or false if not.
     */

    public boolean addCourse(Course course) {
        if (set.insert(course)) {
            arranged.put(course,0L);
            System.out.println("This course is added successfully!");
            return true;
        }
        System.err.println("ERROR: This course has been added before.");
        return false;
    }

    /**
     * Add a time for a course.
     * @param id the ID of the course.
     * @param start the start time.
     * @param end the end time.
     * @return true if add successfully or false if not.
     */

    public boolean addCourseTime(long id,long start,long end) {
        for (Course it:set.labels()) {
            if (it.getID() == id) {
                if (arranged.get(it) == it.getCourseTime()) {
                    System.err.println("ERROR: This course has been arranged with enough time.");
                    return false;
                }
                set.insert(start,end,it);
                arranged.replace(it,arranged.get(it)+2);
                System.out.println("This course has been arrange at this time.");
                return true;
            }
        }
        System.err.println("ERROR: There is no such course.");
        return false;
    }

    /**
     * Show the blank course.
     */
    public void showBlankCourse() {
        System.out.println("The courses no scheduled are as follows:");
        for (Course it:set.labels()) {
            if (arranged.get(it) == 0) {
                System.out.println(it.toString());
            }
        }
        System.out.println("");
    }

    public void showBlankRatio() {
        System.out.println("The blank ratio is "+api.calcFreeTimeRatio(set)*100 + "%.");
    }

    public void showRepeatRatio() {
        System.out.println("The repeat ratio is "+api.calcConflictRatio(set)*100 + "%.");
    }

    public static int getWeekOfDate(Date date) {
        Calendar cal = Calendar.getInstance();
        cal.setTime(date);
        int w = cal.get(Calendar.DAY_OF_WEEK) - 1;
        if (w < 0)
            w = 7;
        return w;
    }

    public void showDateCourse(String date) {
        Date nowDate = null;
        try {
            nowDate = simpleDateFormat.parse(date);
        } catch (ParseException e) {
            e.printStackTrace();
        }
        assert nowDate != null;
        if (nowDate.getTime() - startDate.getTime() > (long) weeks *7*24*60*60*1000) {
            System.out.println("This Date is out of the teaching week.");
        }
        Map <Pair, Course> mpp = new TreeMap<>();
        for (Course it:set.labels()) {
            for (Pair itt:set.getMp().get(it)) {
                mpp.put(itt,it);
            }
        }
        System.out.println("The schedule of the date "+date+" is as follows:");
        for (Pair it:mpp.keySet()) {
            if ((it.start()-1) / 5 + 1 == getWeekOfDate(nowDate))
                System.out.println(from.get(it.start())+ ":00 ~ " + to.get(it.start()) + ":00  " + mpp.get(it).toString());
        }
    }
}
