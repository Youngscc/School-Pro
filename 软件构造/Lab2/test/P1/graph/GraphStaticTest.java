/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import static org.junit.Assert.*;

import java.util.*;

import org.junit.Test;

/**
 * Tests for static methods of Graph.
 * 
 * To facilitate testing multiple implementations of Graph, instance methods are
 * tested in GraphInstanceTest.
 */
public class GraphStaticTest {
    
    // Testing strategy
    //   empty()
    //     no inputs, only output is empty graph
    //     observe with vertices()
    
    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }
    
    @Test
    public void testEmptyVerticesEmpty() {
        assertEquals("expected empty() graph to have no vertices",
                Collections.emptySet(), Graph.empty().vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#add(Object)}
     * covers:
     *  vertex in the graph
     * 	vertex not in the graph
     */

    @Test
    public void addTestInt() {
        Graph<Integer> graph = Graph.empty();
        Set<Integer> ans = new HashSet<Integer>();
        assertTrue(graph.add(1));
        ans.add(1);
        assertEquals(ans,graph.vertices());
        assertFalse(graph.add(1));
        assertEquals(ans,graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#set(Object, Object, int)}
     * covers:
     *  set edge not existing with existing source, existing target and weighted zero
     *  set edge not existing with existing source, existing target and weighted positive
     *  set edge existing with existing source, existing target and weighted positive
     *  set edge existing with existing source, existing target and weighted zero
     *  set edge not existing with existing source, not existing target and weighted zero
     *  set edge not existing with existing source, not existing target and weighted positive
     *  set edge not existing with not existing source, existing target and weighted zero
     *  set edge not existing with not existing source, existing target and weighted positive
     *  set edge not existing with not existing source, not existing target and weighted zero
     *  set edge not existing with not existing source, not existing target and weighted positive
     */

    @Test
    public void setTestInt() {
        Graph<Integer> graph = Graph.empty();
        Set<Integer> ans = new HashSet<Integer>();
        graph.add(1);
        graph.add(2);
        graph.add(3);
        ans.add(1);
        ans.add(2);
        ans.add(3);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1, 2, 0));
        assertEquals(0, graph.set(1, 2, 1));
        assertEquals(1, graph.set(1, 2, 2));
        assertEquals(2, graph.set(1, 2, 0));
        assertEquals(0, graph.set(1, 4, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1, 4, 1));
        ans.add(4);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(5, 4, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(5, 4, 1));
        ans.add(5);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(6, 7, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(6, 7, 1));
        ans.add(6);
        ans.add(7);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#remove(Object)}
     * covers:
     *  remove a vertex existing
     *  remove a vertex not existing
     */
    @Test
    public void removeTestInt() {
        Graph<Integer> graph = Graph.empty();
        Set<Integer> ans = new HashSet<Integer>();
        assertFalse(graph.remove(1));
        assertEquals(ans, graph.vertices());
        graph.add(1);
        ans.add(1);
        graph.add(2);
        ans.add(2);
        graph.set(1,2,1);
        assertTrue(graph.remove(1));
        ans.remove(1);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1,2,0));
        assertTrue(graph.remove(2));
        ans.remove(2);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#vertices()}
     * covers:
     *  an empty graph
     *  a graph with vertices
     */

    @Test
    public void verticesTestInt() {
        Graph<Integer> graph = Graph.empty();
        Set<Integer> ans = new HashSet<Integer>();
        assertEquals(ans, graph.vertices());
        graph.add(1);
        ans.add(1);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#sources(Object)}
     * covers:
     *  no edge connected to the target
     *  positive number of edges connected to the target
     */
    @Test
    public void sourcesTestInt() {
        Graph<Integer> graph = Graph.empty();
        Map<Integer, Integer> ans = new HashMap<Integer, Integer>();
        graph.add(1);
        graph.add(2);
        graph.add(3);
        assertEquals(ans, graph.sources(1));
        graph.set(1, 2, 1);
        assertEquals(ans,graph.sources(1));
        graph.set(2, 1, 2);
        graph.set(3, 1, 3);
        ans.put(2,2);
        ans.put(3,3);
        assertEquals(ans,graph.sources(1));
    }

    /**
     * Test for {@link P1.graph.Graph#targets(Object)}
     * covers:
     *  no edge connected to the source
     *  positive number of edges connected to the source
     */
    @Test
    public void targetsTestInt() {
        Graph<Integer> graph = Graph.empty();
        Map<Integer, Integer> ans = new HashMap<Integer, Integer>();
        graph.add(1);
        graph.add(2);
        graph.add(3);
        assertEquals(ans, graph.targets(1));
        graph.set(2, 1, 1);
        assertEquals(ans,graph.targets(1));
        graph.set(1, 2, 2);
        graph.set(1, 3, 3);
        ans.put(2,2);
        ans.put(3,3);
        assertEquals(ans,graph.targets(1));
    }

    /**
     * Test for {@link P1.graph.Graph#add(Object)}
     * covers:
     *  vertex in the graph
     * 	vertex not in the graph
     */

    @Test
    public void addTestDouble() {
        Graph<Double> graph = Graph.empty();
        Set<Double> ans = new HashSet<Double>();
        assertTrue(graph.add(1.1));
        ans.add(1.1);
        assertEquals(ans,graph.vertices());
        assertFalse(graph.add(1.1));
        assertEquals(ans,graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#set(Object, Object, int)}
     * covers:
     *  set edge not existing with existing source, existing target and weighted zero
     *  set edge not existing with existing source, existing target and weighted positive
     *  set edge existing with existing source, existing target and weighted positive
     *  set edge existing with existing source, existing target and weighted zero
     *  set edge not existing with existing source, not existing target and weighted zero
     *  set edge not existing with existing source, not existing target and weighted positive
     *  set edge not existing with not existing source, existing target and weighted zero
     *  set edge not existing with not existing source, existing target and weighted positive
     *  set edge not existing with not existing source, not existing target and weighted zero
     *  set edge not existing with not existing source, not existing target and weighted positive
     */

    @Test
    public void setTestDouble() {
        Graph<Double> graph = Graph.empty();
        Set<Double> ans = new HashSet<Double>();
        graph.add(1.1);
        graph.add(2.2);
        graph.add(3.3);
        ans.add(1.1);
        ans.add(2.2);
        ans.add(3.3);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1.1, 2.2, 0));
        assertEquals(0, graph.set(1.1, 2.2, 1));
        assertEquals(1, graph.set(1.1, 2.2, 2));
        assertEquals(2, graph.set(1.1, 2.2, 0));
        assertEquals(0, graph.set(1.1, 4.4, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1.1, 4.4, 1));
        ans.add(4.4);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(5.5, 4.4, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(5.5, 4.4, 1));
        ans.add(5.5);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(6.6, 7.7, 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(6.6, 7.7, 1));
        ans.add(6.6);
        ans.add(7.7);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#remove(Object)}
     * covers:
     *  remove a vertex existing
     *  remove a vertex not existing
     */
    @Test
    public void removeTestDouble() {
        Graph<Double> graph = Graph.empty();
        Set<Double> ans = new HashSet<Double>();
        assertFalse(graph.remove(1.1));
        assertEquals(ans, graph.vertices());
        graph.add(1.1);
        ans.add(1.1);
        graph.add(2.2);
        ans.add(2.2);
        graph.set(1.1,2.2,1);
        assertTrue(graph.remove(1.1));
        ans.remove(1.1);
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set(1.1,2.2,0));
        assertTrue(graph.remove(2.2));
        ans.remove(2.2);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#vertices()}
     * covers:
     *  an empty graph
     *  a graph with vertices
     */

    @Test
    public void verticesTestDouble() {
        Graph<Double> graph = Graph.empty();
        Set<Double> ans = new HashSet<Double>();
        assertEquals(ans, graph.vertices());
        graph.add(1.1);
        ans.add(1.1);
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#sources(Object)}
     * covers:
     *  no edge connected to the target
     *  positive number of edges connected to the target
     */
    @Test
    public void sourcesTestDouble() {
        Graph<Double> graph = Graph.empty();
        Map<Double, Integer> ans = new HashMap<Double, Integer>();
        graph.add(1.1);
        graph.add(2.2);
        graph.add(3.3);
        assertEquals(ans, graph.sources(1.1));
        graph.set(1.1, 2.2, 1);
        assertEquals(ans,graph.sources(1.1));
        graph.set(2.2, 1.1, 2);
        graph.set(3.3, 1.1, 3);
        ans.put(2.2,2);
        ans.put(3.3,3);
        assertEquals(ans,graph.sources(1.1));
    }

    /**
     * Test for {@link P1.graph.Graph#targets(Object)}
     * covers:
     *  no edge connected to the source
     *  positive number of edges connected to the source
     */
    @Test
    public void targetsTestDouble() {
        Graph<Double> graph = Graph.empty();
        Map<Double, Integer> ans = new HashMap<Double, Integer>();
        graph.add(1.1);
        graph.add(2.2);
        graph.add(3.3);
        assertEquals(ans, graph.targets(1.1));
        graph.set(2.2, 1.1, 1);
        assertEquals(ans,graph.targets(1.1));
        graph.set(1.1, 2.2, 2);
        graph.set(1.1, 3.3, 3);
        ans.put(2.2,2);
        ans.put(3.3,3);
        assertEquals(ans,graph.targets(1.1));
    }
}
