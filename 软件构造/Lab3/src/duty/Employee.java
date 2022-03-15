package duty;

/**
 * This is an immutable class.
 */
public class Employee {
    private final String Name;
    private final String Position;
    private final String PhoneNumber;

    public Employee(String Name,String Position,String PhoneNumber) {
        this.Name = Name;
        this.Position = Position;
        this.PhoneNumber = PhoneNumber;
        checkRep();
    }

    public void checkRep() {
        assert Name != null;
        assert Position != null;
        assert PhoneNumber != null;
    }

    @Override
    public String toString() {
        return Name+"("+Position+") Phone Number: "+PhoneNumber+"\n";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + Name.hashCode();
        result = prime * result + Position.hashCode();
        result = prime * result + PhoneNumber.hashCode();
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null) return false;
        if (getClass() != obj.getClass()) return false;
        Employee other = (Employee) obj;
        if (!Name.equals(other.Name)) return false;
        if (!Position.equals(other.Position)) return false;
        if (!PhoneNumber.equals(other.PhoneNumber)) return false;
        return true;
    }
}
