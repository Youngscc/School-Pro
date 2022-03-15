package duty;

import intervalSet.DutyIntervalSet;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Scanner;

/**
 * This is duty roster app.
 */

public class DutyRosterApp {

    public static void main(String[] args) throws ParseException {
        System.out.println("************************************");
        System.out.println("**                                **");
        System.out.println("**        Duty Roster App         **");
        System.out.println("**                                **");
        System.out.println("************************************");

        DutyIntervalSet set = new DutyIntervalSet();
        Scanner scanner =new Scanner(System.in);
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");


        while (true) {
            System.out.println("");
            System.out.println("");
            System.out.println("-----------------------***------------------------");
            System.out.println("1.Set the start date and end date of scheduling   ");
            System.out.println("2.Add a new employee                              ");
            System.out.println("3.Delete an old employee                          ");
            System.out.println("4.Schedule a task for an employee                 ");
            System.out.println("5.Show if the scheduling id full                  ");
            System.out.println("6.Automatic scheduling for employees              ");
            System.out.println("7.Displays the current schedule                   ");
            System.out.println("0.Quit                                            ");
            System.out.println("-----------------------***------------------------");
            System.out.print("Please input your choice:");

            String opt = scanner.next();
            System.out.println();
            switch (opt) {
                case "1": {
                    System.out.println("Please enter the start date:(yyyy-MM-dd)");
                    String startData = scanner.next();
                    System.out.println("Please enter the end date:(yyyy-MM-dd)");
                    String endDate = scanner.next();
                    set.setStart(startData);
                    set.setEnd(endDate);
                    assert simpleDateFormat.parse(startData).getTime() < simpleDateFormat.parse(endDate).getTime();
                    break;
                }
                case "2": {
                    System.out.println("Please enter the employee's name :");
                    String nameString = scanner.next();
                    System.out.println("Please enter the employee's position :");
                    String postString = scanner.next();
                    System.out.println("Please enter the employee's phone number :");
                    String phoneString = scanner.next();
                    Employee employee = new Employee(nameString, postString, phoneString);
                    set.insertEmployee(employee);
                    break;
                }
                case "3": {
                    System.out.println("Please enter the employee's name :");
                    String nameString = scanner.next();
                    System.out.println("Please enter the employee's position :");
                    String postString = scanner.next();
                    System.out.println("Please enter the employee's phone number :");
                    String phoneString = scanner.next();
                    Employee employee = new Employee(nameString, postString, phoneString);
                    set.deleteEmployee(employee);
                    break;
                }
                case "4": {
                    System.out.println("Please enter the employee's name :");
                    String nameString = scanner.next();
                    System.out.println("Please enter the employee's position :");
                    String postString = scanner.next();
                    System.out.println("Please enter the employee's phone number :");
                    String phoneString = scanner.next();
                    Employee employee = new Employee(nameString, postString, phoneString);
                    System.out.println("Please enter the start date: (yyyy-MM-dd)");
                    String startString = scanner.next();
                    System.out.println("Please enter the end date: (yyyy-MM-dd)");
                    String endString = scanner.next();
                    set.insertTask(employee, startString, endString);
                    break;
                }
                case "5": {
                    set.isFull();
                    break;
                }
                case "6": {
                    set.autoArrange();
                    break;
                }
                case "7": {
                    set.show();
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
}
