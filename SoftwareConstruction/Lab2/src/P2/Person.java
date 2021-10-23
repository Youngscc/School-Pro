package P2;

import java.util.Objects;

public class Person {
	private final String name;
	
	/**
	 * 
	 * @param name the name of the person
	 */
	
	public Person(String name) {
		this.name = name;
	}
	
	/**
	 * 
	 * get the name of the person
	 *@return the name of the person
	 */
	
	public String Name() {
		return name;
	}
	@Override
	public int hashCode() {
		return Objects.hash(name);
	}

	@Override
	public boolean equals(Object obj) {
		Person p = (Person) obj;
		return this.name.equals(p.name);
	}
}