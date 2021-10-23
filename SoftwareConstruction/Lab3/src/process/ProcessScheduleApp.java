package process;

import multiIntervalset.ProcessIntervalSet;

import java.util.Scanner;

public class ProcessScheduleApp {
    public static void main(String[] args){
        System.out.println("******************************************");
        System.out.println("**                                      **");
        System.out.println("**         Process Schedule App         **");
        System.out.println("**                                      **");
        System.out.println("******************************************");

        ProcessIntervalSet set = new ProcessIntervalSet();
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("");
            System.out.println("");
            System.out.println("-----------------------***------------------------");
            System.out.println("1.Add a new process                               ");
            System.out.println("2.Start running randomly                          ");
            System.out.println("3.Start running with shortest first               ");
            System.out.println("4.Show the status                                 ");
            System.out.println("-----------------------***------------------------");
            System.out.print("Please input your choice:");

            String opt = scanner.next();
            System.out.println();
            switch (opt) {
                case "1": {
                    insert(set);
                    break;
                }
                case "2": {
                    set.run(1);
                    break;
                }
                case "3": {
                    set.run(2);
                    break;
                }
                case "4": {
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

    /**
     * Add a new process
     * @param set a set.
     */
    private static void insert(ProcessIntervalSet set) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter the ID");
        long id = scanner.nextLong();
        System.out.println("Please enter the name");
        String name = scanner.next();
        System.out.println("Please enter the minimal run time");
        long minTime = scanner.nextLong();
        System.out.println("Please enter the maximum run time");
        long maxTime = scanner.nextLong();
        set.insertProcess(new Process(id,name,minTime,maxTime));
    }
}
