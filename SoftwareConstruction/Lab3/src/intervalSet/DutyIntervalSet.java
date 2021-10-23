package intervalSet;

import duty.Employee;
import base.Pair;
import apis.APIs;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.*;


public class DutyIntervalSet{
    private final Set<Employee> employees;
    private final IntervalSet<Employee> duty;
    private final IsRepeatCheck<Employee> isRepeatCheck;
    private final IsBlankCheck<Employee> isBlankCheck;
    SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
    public DutyIntervalSet() {
        this.duty = new IsRepeatCheck<Employee>(new IsBlankCheck<Employee>(new CommonIntervalSet<Employee>()));
        isRepeatCheck = (IsRepeatCheck<Employee>) this.duty;
        isBlankCheck = (IsBlankCheck<Employee>) isRepeatCheck.intervalSet;
        this.employees = new HashSet<>();
        this.checkRep();
    }

    public void checkRep() {
        duty.checkRep();
    }

    /**
     * Set the start date.
     * @param start the start date.
     */

    public void setStart(String start) {
        try {
            this.duty.setStart(simpleDateFormat.parse(start).getTime()/(24*60*60*1000));
        } catch (ParseException e) {
            // TODO: handle exception
            e.printStackTrace();
        }
    }

    /**
     * Set the end date.
     * @param end the end date.
     */

    public void setEnd(String end) {
        try {
            this.duty.setEnd(simpleDateFormat.parse(end).getTime()/(24*60*60*1000));
        } catch (ParseException e) {
            // TODO: handle exception
            e.printStackTrace();
        }
    }

    /**
     * Add a new employee.
     * @param o the employee.
     * @return true if add successfully or false if not.
     */

    public boolean insertEmployee(Employee o) {
        if (this.employees.contains(o))
        {
            System.err.println("ERROR: This employee has been added into the set.");
            return false;
        }
        this.employees.add(o);
        System.out.println("This employee has been inserted successfully.");
        return true;
    }

    /**
     * Remove a employee.
     * @param o the employee.
     * @return true if delete him or false if not.
     */

    public boolean deleteEmployee(Employee o) {
        if (duty.getMp().containsKey(o))
        {
            System.err.println("ERROR: This employee can not be deleted.");
            return false;
        }
        if (!employees.contains(o))
        {
            System.err.println("ERROR: This employee doesn't exist.");
            return false;
        }
        employees.remove(o);
        System.out.println("This employee has been deleted successfully.");
        return true;
    }

    /**
     * Add a new task.
     * @param o The employee.
     * @param startDate The start time.
     * @param endDate The end time.
     * @return true if add successfully or false if not.
     */
    public boolean insertTask(Employee o,String startDate,String endDate) {
        Date taskStart,taskEnd;
        try {
            taskStart = simpleDateFormat.parse(startDate);
            taskEnd = simpleDateFormat.parse(endDate);
        } catch (ParseException e) {
            e.printStackTrace();
            return false;
        }

        if (!employees.contains(o)) {
            System.err.println("ERROR: This employee doesn't exist.");
            return false;
        }
        else if (duty.getMp().containsKey(o)) {
            System.err.println("ERROR: This employee has had his or her duty.");
            return false;
        }
        else if (taskStart.getTime()/(24*60*60*1000) < duty.getStart() || taskEnd.getTime()/(24*60*60*1000) > duty.getEnd()) {
            System.err.println("ERROR: This duty is out of the bound.");
            return false;
        }
        else {
            duty.insert(taskStart.getTime()/(24*60*60*1000),taskEnd.getTime()/(24*60*60*1000),o);
            if (!isRepeatCheck.repeatCheck()) {
                removeTask(o);
                System.err.println("This time arrangement is not allowed.");
                return false;
            }
            System.out.println("This task has been arranged successfully.");
        }
        return true;
    }

    public void removeTask(Employee o) { this.duty.remove(o); }

    /**
     * check if every time some one is on duty.
     * Show the free time.
     * Show the free time ratio.
     * @return true if the arrangement is full or false if not.
     */

    public boolean isFull() {
        long mostStart=-1,mostEnd=-1;
        for (Employee it:duty.getMp().keySet()) {
            if (mostStart == -1) mostStart = duty.getMp().get(it).start();
            else mostStart = Math.min(mostStart,duty.getMp().get(it).start());
            if (mostEnd == -1) mostEnd = duty.getMp().get(it).end();
            else mostEnd = Math.max(mostEnd, duty.getMp().get(it).end());
        }
        if (mostEnd != duty.getEnd() || mostStart != duty.getStart() || !isBlankCheck.blankCheck()) {

            System.out.println("The time where no one is on duty is as follow: ");

            if (duty.getMp().size() == 0) {
                System.out.println(simpleDateFormat.format(new Date(duty.getStart()*(24*60*60*1000))) + " ~ " + simpleDateFormat.format(new Date(duty.getEnd()*(24*60*60*1000))));
                return false;
            }

            List<Pair> lt = new ArrayList<>();
            for (Employee it:this.duty.getMp().keySet()) lt.add(this.duty.getMp().get(it));
            Collections.sort(lt);
            if (duty.getStart() != lt.get(0).start())
                System.out.println(simpleDateFormat.format(new Date(duty.getStart()*(24*60*60*1000)+(24*60*60*1000)*2)) + " ~ " + simpleDateFormat.format(new Date(lt.get(0).start()*(24*60*60*1000))));
            for (int i=0; i<lt.size()-1; ++i) {
                if (lt.get(i).end() != lt.get(i+1).start() - 1)
                    System.out.println(simpleDateFormat.format(new Date(lt.get(i).end()*(24*60*60*1000) + 24*60*60*1000*2)) + " ~ " + simpleDateFormat.format(new Date(lt.get(i+1).start()*(24*60*60*1000))));
            }
            if (duty.getEnd() != lt.get(lt.size()-1).end())
                System.out.println(simpleDateFormat.format(new Date(lt.get(lt.size()-1).end() * (24*60*60*1000) + 24*60*60*1000*2)) + " ~ " + simpleDateFormat.format(new Date(duty.getEnd()*(24*60*60*1000)+(24*60*60*1000))));
            System.out.println("The free time ratio is "+getRatio()*100+"%");
            return false;
        }
        else {
            System.out.println("The arrangement is full");
            return true;
        }
    }

    /**
     * calculate the free time ratio.
     * @return the free time ratio.
     */

    public double getRatio() {
        APIs<Employee> API = new APIs<Employee>();
        return API.calcFreeTimeRatio(duty);
    }


    /**
     * Auto arrange the schedule.
     */
    public void autoArrange() {
        duty.clear();
        long days = (duty.getEnd()-duty.getStart())/employees.size()+1;

        Random rad = new Random();
        List<Integer> v = new ArrayList<>();
        for (int i=0; i<employees.size(); ++i) v.add(i);
        for (int i=0; i<employees.size(); ++i) {
            int x=rad.nextInt(employees.size());
            int y=rad.nextInt(employees.size());
            int t = v.get(x);
            v.set(x,v.get(y));
            v.set(y,t);
        }
        int i=0;
        for (Employee it:employees) {
            insertTask(it,simpleDateFormat.format(new Date((duty.getStart()+i*days+1)*(24*60*60*1000))),simpleDateFormat.format(new Date((Math.min(duty.getStart()+i*days+days-1,duty.getEnd())+1)*(24*60*60*1000))));
            i++;
        }
        System.out.println("The duty has been arranged successfully.");
    }

    /**
     * Show the schedule.
     */

    public void show() {
        Map<Pair,Employee> mpp = new TreeMap<>();
        for (Employee it:duty.getMp().keySet()) mpp.put(duty.getMp().get(it),it);
        System.out.println("The arrangement is as following");
        for (Pair it:mpp.keySet()) System.out.println(simpleDateFormat.format(new Date(it.start()*(24*60*60*1000)+(24*60*60*1000)))+" ~ "+simpleDateFormat.format(new Date(it.end()*(24*60*60*1000)+(24*60*60*1000))) + ": " + mpp.get(it).toString());
    }
}
