package P2;

import java.util.*;

import P1.graph.ConcreteEdgesGraph;
import P1.graph.ConcreteVerticesGraph;
import P1.graph.Graph;

public class FriendshipGraph {
	private final Graph<Person> graph;

	/**
	 * FriendshipGraph Constructor
	 */
	public FriendshipGraph() {
		graph = Graph.empty();
	}


	/**
	 * add a Person to the vertex
	 *
	 * @param a a <Person>
	 */
	public void addVertex(Person a) {
		if (!graph.add(a)) {
			throw new IllegalArgumentException("There has already been a person named"+a.Name());
		}
	}


	/**
	 * add an edge with weight 1 from A to B，if A B both exist
	 * and A doesn't equal B
	 *
	 * @param A a {@link Person} A which exist in the graph
	 * @param B a {@link Person} B which exist in the graph
	 * @return false if A or B doesn't exist in the graph,
	 * or A equals B
	 * true otherwise and add an edge with weight 1,
	 * if there is already an edge from A to B, will just return
	 * true and the graph will not be modified
	 */
	public boolean addEdge (Person A,Person B) {
		if (A.equals(B)) {
			return false;
		}
		Set<Person> s = graph.vertices();
		if (!s.contains(A) || !s.contains(B)) {
			return false;
		}
		graph.set(A, B, 1);
		return true;
	}


	/**
	 * get the shortest distance between A and B
	 *
	 * @param A a {@link Person}
	 * @param B a {@link Person}
	 * @return the shortest distance from A to B in the graph
	 * if A and B both exist in the graph and there is a path from A to B,
	 * otherwise -1
	 */
	public int getDistance(Person A, Person B) {
		if (!graph.vertices().contains(A) || !graph.vertices().contains(B)) return -1;
		Map<Person, Integer> vis = new HashMap<>();
		for (Person e : graph.vertices()) {
			vis.put(e, 0);
		}
		Queue<Person> q = new LinkedList<>();
		q.add(A);
		while (!q.isEmpty()) {
			Person tmp = q.remove();
			if (tmp.equals(B))
				return vis.get(tmp);
			for (Person v : graph.targets(tmp).keySet()) {
				if (vis.get(v) > 0)
					continue;
				if (v.equals(B))
					return vis.get(tmp) + 1;
				else {
					vis.put(v, vis.get(tmp) + 1);
					q.add(v);
				}
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
