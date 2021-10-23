package P3;

import org.junit.Test;
import static org.junit.Assert.*;

public class FriendshipGraphTest {
	@Test
	public void addVertexTest() throws IllegalAccessException {
		FriendshipGraph graph = new FriendshipGraph();
		Person a = new Person("a");
		Person b = new Person("b");
		Person c = new Person("a");
		
		assertEquals(0, graph.addVertex(b));
		assertTrue(graph.containPerson(b));
		assertFalse(graph.containPerson(a));
		
		assertEquals(1, graph.addVertex(a));
		assertTrue(graph.containPerson(a));
		
		boolean thrown = false;
		try
        {
            graph.addVertex(c);
        }
        catch (IllegalArgumentException e)
        {
            thrown = true;
        }
        assertTrue(thrown);
	}
	
	@Test
	public void addEdgeTest() throws IllegalAccessException {
		
		FriendshipGraph graph = new FriendshipGraph();
		Person a = new Person("a");
		Person b = new Person("b");
		Person c = new Person("c");

		graph.addVertex(a);
		graph.addVertex(b);
		graph.addVertex(c);

		graph.addEdge(a, b);
		assertTrue(graph.containsEdge(a, b));
		assertFalse(graph.containsEdge(b, a));

		graph.addEdge(b, a);
		assertTrue(graph.containsEdge(b, a));

		graph.addEdge(a, c);
		assertTrue(graph.containsEdge(a, c));
		assertFalse(graph.containsEdge(c, a));

		graph.addEdge(c, a);
		assertTrue(graph.containsEdge(c, a));

		assertFalse(graph.containsEdge(b, c));
	}
	
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