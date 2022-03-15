package P2;

import org.junit.Test;
import static org.junit.Assert.*;

public class FriendshipGraphTest {

	/**
	 * Test method for {@link FriendshipGraph#addVertex(Person)}
	 * covers:
	 * vertex in the graph
	 * vertex not in the graph graph
	 */
	@Test
	public void addVertexTest() throws IllegalAccessException {
		FriendshipGraph g = new FriendshipGraph();
		Person p = new Person("a");
		g.addVertex(p);
		boolean error = false;
		try {
			g.addVertex(p);
		} catch (IllegalArgumentException e) {
			error = true;
		}
		assertTrue(error);
		Person q = new Person("b");
		assertFalse(g.addEdge(p, q));
		g.addVertex(q);
		assertTrue(g.addEdge(p, q));
	}

	/**
	 * Test method for {@link FriendshipGraph#addEdge(Person, Person)}
	 * covers:
	 * A is equal to B
	 * A exist, B not exist
	 * A not exist, B not exist
	 * A not exist, B exist
	 * A exist, B exist
	*/
	@Test
	public void testAddEdge() {
		FriendshipGraph g = new FriendshipGraph();
		Person a = new Person("a");
		Person b = new Person("b");
		Person c = new Person("c");
		assertFalse(g.addEdge(a, b));
		g.addVertex(a);
		g.addVertex(b);
		assertFalse(g.addEdge(a, c));
		assertFalse(g.addEdge(a, a));
		assertFalse(g.addEdge(c, b));
		assertTrue(g.addEdge(a, b));
		g.addVertex(c);
		assertTrue(g.addEdge(c, b));
		assertTrue(g.addEdge(a, c));
	}

	/**
	 * Test method for {@link FriendshipGraph#getDistance(Person, Person)}
	 * covers:
	 * 	A is equal to B
	 * 	A is not equal to B
	 */
	
	@Test
	public void getDistanceTest() {
		FriendshipGraph graph = new FriendshipGraph();
        Person[] a = new Person[8];
        for(int i=0; i<8; i++)
            a[i] = new Person(""+i);
        for(int i = 0 ;i<7;i++) graph.addVertex(a[i]);
        graph.addEdge(a[0],a[1]);
        graph.addEdge(a[0],a[2]);
        graph.addEdge(a[2],a[3]);
        graph.addEdge(a[3],a[4]);
        graph.addEdge(a[1],a[4]);
        graph.addEdge(a[2],a[5]);
        assertEquals(1,graph.getDistance(a[0],a[1]));
        assertEquals(0,graph.getDistance(a[0],a[0]));
        assertEquals(2,graph.getDistance(a[0],a[5]));
        assertEquals(2,graph.getDistance(a[0],a[4]));
        assertEquals(-1,graph.getDistance(a[0],a[6]));
        assertEquals(-1,graph.getDistance(a[0],a[7]));
	}
}