package P3;

import java.util.*;

public class FriendshipGraph {
	private Map <String, Integer> personID;
	private Map<Integer, Set<Integer>> Friendship;
	
	public FriendshipGraph() {
		this.Friendship = new TreeMap<Integer, Set<Integer>>();
		this.personID = new HashMap<String,Integer>();
	}

	/**
	 * Add vertex.
	 * @param person The person who needs to be added.
	 * @return The uid of the person.
	 */
	
	public int addVertex(Person person) {
		if (this.personID.containsKey(person.Name()))
			throw new IllegalArgumentException("There has already been a person named"+person.Name());
		int id = this.personID.size();
		this.personID.put(person.Name(),  id);
		this.Friendship.put(id, new TreeSet<>());
		return id;
	}


	/**
	 * Add edge.
	 * @param a The one of the pair which has an edge.
	 * @param b The another one of the pair which has an edge.
	 * @return Successful or not to add the edge.
	 */
	public boolean addEdge (Person a,Person b) {
		int x,y;
		try {
			x = (int) this.personID.get(a.Name());
			y = (int) this.personID.get(b.Name());
		} catch (NullPointerException e) {
			return false;
		}
		this.Friendship.get(x).add(y);
		return true;
	}

	/**
	 * Qury the ID.
	 * @param person The person whose uid needs to be queried.
	 * @return The uid of the person or -1 if the person doesn't exist.
	 */
	
	private int getPersonID(Person person) {
		return this.personID.getOrDefault(person.Name(), -1);
	}

	/**
	 *
	 * @param person The person.
	 * @return Whether the person exists or not.
	 */
	public boolean containPerson(Person person) {
		return this.personID.containsKey(person.Name());
	}

	/**
	 *
	 * @param fromPerson One person.
	 * @param toPerson The other person.
	 * @return If the two persons have edge between them.
	 */
	
	public boolean containsEdge(Person fromPerson, Person toPerson) {
		int from = getPersonID(fromPerson), to = getPersonID(toPerson);
		if (from == -1 || to == -1)
			return false;
		return this.Friendship.get(from).contains(to);
	}

	/**
	 * Qury the distance between any two persons.
	 * @param a One person.
	 * @param b Another person.
	 * @return The distance between them or -1 if they can't touch each other.
	 */
	public int getDistance(Person a,Person b) {
		int x,y;
		try {
			x = (int) this.personID.get(a.Name());
			y = (int) this.personID.get(b.Name());
		} catch (NullPointerException e) {
			return -1;
		}
		if (x == y) return 0;
		int[] dis = new int[this.personID.size()];
		Queue<Integer> q = new LinkedList<>();
		Arrays.fill(dis,-1);
		q.add(x);
		dis[x] = 0;
		while (!q.isEmpty()) {
			int now = q.poll();
			for (int  v:this.Friendship.get(now)) {
				if (dis[v] != -1) continue;
				if (v == y) return dis[now]+1;
				dis[v] = dis[now]+1;
				q.add(v);
			}
		}
		return -1;
	}
	
	public static void main(String[] args) throws Exception{
		FriendshipGraph graph = new FriendshipGraph();
        Person rachel = new Person("Rachel");
        Person ross = new Person("Ross");
        Person ben = new Person("Ben");
        Person kramer = new Person("Kramer");
        graph.addVertex(rachel);
        graph.addVertex(ross);
        graph.addVertex(ben);
        graph.addVertex(kramer);
        graph.addEdge(rachel, ross);
        graph.addEdge(ross, rachel);
        graph.addEdge(ross, ben);
        graph.addEdge(ben, ross);
        System.out.println(graph.getDistance(rachel, ross));//should print 1
        System.out.println(graph.getDistance(rachel, ben));//should print 2
        System.out.println(graph.getDistance(rachel, rachel));//should print 0
        System.out.println(graph.getDistance(rachel, kramer));//should print -1
	}
}
