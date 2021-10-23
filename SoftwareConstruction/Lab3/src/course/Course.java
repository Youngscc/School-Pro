package course;

/**
 * This is an immutable class.
 */
public class Course {
    private final long id;
    private final String name;
    private final String teacher;
    private final String place;
    private final long courseTime;

    public Course(long id,String name,String teacher,String place,long courseTime) {
        this.id = id;
        this.name = name;
        this.teacher = teacher;
        this.place = place;
        this.courseTime = courseTime;
        checkRep();
    }

    /**
     * Check if the course time is even and the id is positive.
     */
    void checkRep() {
        assert courseTime%2 == 0;
        assert name != null;
        assert teacher != null;
        assert id > 0;
    }

    /**
     * Get the id.
     * @return the id.
     */
    public long getID() {return id;}

    /**
     * Get the course time.
     * @return the course time.
     */
    public long getCourseTime() {return courseTime;}

    @Override
    public String toString() {
        return id + ": " + name + "  Teacher: " + teacher + "  Time: " + courseTime + " hours ";
    }

    @Override
    public int hashCode () {
        final int prime = 31;
        int result = 1;
        result = prime * result + (int)id;
        result = prime * result + name.hashCode();
        result = prime * result + teacher.hashCode();
        result = prime * result + (int)courseTime;
        return result;
    }

    @Override
    public boolean equals (Object obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        Course other = (Course) obj;
        if (id != other.id) return false;
        if (!name.equals(other.name)) return false;
        if (!teacher.equals(other.teacher)) return false;
        if (!place.equals(other.place)) return false;
        return courseTime == other.courseTime;
    }
}
