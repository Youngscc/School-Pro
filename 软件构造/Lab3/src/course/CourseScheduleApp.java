package course;

import multiIntervalset.CourseIntervalSet;
import java.util.Scanner;

/**
 * This is the Course Schedule App.
 */
public class CourseScheduleApp {
    public static void main(String[] args) throws ClassNotFoundException {
        System.out.println("******************************************");
        System.out.println("**                                      **");
        System.out.println("**         Course Schedule App          **");
        System.out.println("**                                      **");
        System.out.println("******************************************");

        CourseIntervalSet set = new CourseIntervalSet();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("");
            System.out.println("");
            System.out.println("-----------------------***------------------------");
            System.out.println("1.Set the first day and the numbers of the weeks  ");
            System.out.println("2.Add an new course                               ");
            System.out.println("3.Set specified course time                       ");
            System.out.println("4.View non scheduled courses                      ");
            System.out.println("5.Check the blank ratio of the schedule           ");
            System.out.println("6.Check the repeat ratio of the schedule          ");
            System.out.println("7.View the schedule for a given date              ");
            System.out.println("-----------------------***------------------------");
            System.out.print("Please input your choice:");

            String opt = scanner.next();
            System.out.println();

            switch (opt) {
                case "1": {
                    setDate(set);
                    break;
                }
                case "2": {
                    addCourse(set);
                    break;
                }
                case "3": {
                    addCourseTime(set);
                    break;
                }
                case "4": {
                    set.showBlankCourse();
                    break;
                }
                case "5": {
                    set.showBlankRatio();
                    break;
                }
                case "6": {
                    set.showRepeatRatio();
                    break;
                }
                case "7": {
                    showSchedule(set);
                    break;
                }
                case "0": {
                    System.exit(0);
                }
                default:{
                    System.err.println("Wrong Input! Try again!");
                }
            }
        }
    }

    /**
     * Set the start date.
     * @param set the set.
     */
    private static void setDate(CourseIntervalSet set) {
        Scanner scanner =new Scanner(System.in);
        System.out.println("Please enter the start date:(yyyy-MM-dd)");
        String startDate = scanner.next();
        set.setStartDate(startDate);
        System.out.println("Please enter the number of weeks");
        int weekNum = scanner.nextInt();
        set.setWeekNum(weekNum);
    }

    /**
     * Add a course.
     * @param set the set.
     */

    private static void addCourse(CourseIntervalSet set) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the course's ID :");
        long ID = Long.parseLong(scanner.next());
        System.out.println("Please enter the course's name :");
        String courseName = scanner.next();
        System.out.println("Please enter the course's teacher :");
        String teacherName = scanner.next();
        System.out.println("Please enter the course's classroom :");
        String place = scanner.next();
        System.out.println("Please enter the course's weekTime :");
        long weekTime = Long.parseLong(scanner.next());
        Course course = new Course(ID, courseName, teacherName, place, weekTime);
        set.addCourse(course);
    }

    /**
     * Arrange a time for a specific course.
     * @param set a set.
     */

    private static void addCourseTime(CourseIntervalSet set) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the date (eg:Monday : 1):");
        int i = scanner.nextInt();
        System.out.println("Please enter the time :");
        System.out.println("8-10 : 1; 10-12 : 2; 13-15 : 3; 15-17 : 4; 19-21 : 5");
        int j;
        while (true) {
            j = scanner.nextInt();
            if (j < 1 || j > 5) {
                System.out.println("Please enter a number between 1 and 5. Try again!");
            }
            else break;
        }
        System.out.println("Please enter the course's ID :");
        long ID = scanner.nextLong();
        if (set.addCourseTime(ID,i* 5L -5+j,i* 5L -5+j)) System.out.println("Arrange successfully!");
        else System.err.println("ERROR: The Course Not Existing!");
    }

    /**
     * Show the schedule.
     * @param set the set.
     */
    private static void showSchedule(CourseIntervalSet set) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the start date:(yyyy-MM-dd)");
        String date = scanner.next();
        set.showDateCourse(date);
    }
}
