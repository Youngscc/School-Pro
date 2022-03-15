/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import static org.junit.Assert.*;

import java.util.*;

import org.junit.Test;

/**
 * Tests for instance methods of Graph.
 *
 * <p>PS2 instructions: you MUST NOT add constructors, fields, or non-@Test
 * methods to this class, or change the spec of {@link #emptyInstance()}.
 * Your tests MUST only obtain Graph instances by calling emptyInstance().
 * Your tests MUST NOT refer to specific concrete implementations.
 */


public abstract class GraphInstanceTest {
    /**
     * Testing strategy
     *
     * For {@link graph.Graph#add(Object)}
     * covers:
     *  vertex in the graph.
     * 	vertex not in the graph graph.
     *
     * For {@link graph.Graph#set(Object , Object , int)}
     * covers:
     *  set edge not existing with existing source, existing target and weighted zero.
     *  set edge not existing with existing source, existing target and weighted positive.
     *  set edge existing with existing source, existing target and weighted positive.
     *  set edge existing with existing source, existing target and weighted zero.
     *  set edge not existing with existing source, not existing target and weighted zero.
     *  set edge not existing with existing source, not existing target and weighted positive.
     *  set edge not existing with not existing source, existing target and weighted zero.
     *  set edge not existing with not existing source, existing target and weighted positive.
     *  set edge not existing with not existing source, not existing target and weighted zero.
     *  set edge not existing with not existing source, not existing target and weighted positive.
     *
     * For {@link graph.Graph#remove(Object)}
     * covers:
     *  remove a vertex existing.
     *  remove a vertex not existing.
     *
     * For {@link graph.Graph#vertices()}
     * covers:
     *  an empty graph.
     *  a graph with vertices.
     *
     * For {@link graph.Graph#sources(Object)}
     * covers:
     *  the vertex is not exist.
     *  no edge connected to the target.
     *  positive number of edges connected to the target.
     *
     * For {@link graph.Graph#targets(Object)}
     * covers:
     *  no edge connected to the source.
     *  positive number of edges connected to the source.
     */

    /**
     * Overridden by implementation-specific test classes.
     *
     * @return a new empty graph of the particular implementation being tested.
     */
    public abstract Graph<String> emptyInstance();

    @Test(expected=AssertionError.class)
    public void testAssertionsEnabled() {
        assert false; // make sure assertions are enabled with VM argument: -ea
    }

    @Test
    public void testInitialVerticesEmpty() {
        // TODO you may use, change, or remove this test
        assertEquals("expected new graph to have no vertices",
                Collections.emptySet(), emptyInstance().vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#add(Object)}
     * covers:
     *  vertex in the graph.
     * 	vertex not in the graph.
     */

    @Test
    public void addTest() {
        Graph<String> graph = emptyInstance();
        Set<String> ans = new HashSet<String>();
        assertTrue(graph.add("a"));
        ans.add("a");
        assertEquals(ans,graph.vertices());
        assertFalse(graph.add("a"));
        assertEquals(ans,graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#set(Object, Object, int)}
     * covers:
     *  set edge not existing with existing source, existing target and weighted zero.
     *  set edge not existing with existing source, existing target and weighted positive.
     *  set edge existing with existing source, existing target and weighted positive.
     *  set edge existing with existing source, existing target and weighted zero.
     *  set edge not existing with existing source, not existing target and weighted zero.
     *  set edge not existing with existing source, not existing target and weighted positive.
     *  set edge not existing with not existing source, existing target and weighted zero.
     *  set edge not existing with not existing source, existing target and weighted positive.
     *  set edge not existing with not existing source, not existing target and weighted zero.
     *  set edge not existing with not existing source, not existing target and weighted positive.
     */

    @Test
    public void setTest() {
        Graph<String> graph = emptyInstance();
        Set<String> ans = new HashSet<String>();
        graph.add("a");
        graph.add("b");
        graph.add("c");
        ans.add("a");
        ans.add("b");
        ans.add("c");
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("a", "b", 0));
        assertEquals(0, graph.set("a", "b", 1));
        assertEquals(1, graph.set("a", "b", 2));
        assertEquals(2, graph.set("a", "b", 0));
        assertEquals(0, graph.set("a", "d", 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("a", "d", 1));
        ans.add("d");
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("e", "d", 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("e", "d", 1));
        ans.add("e");
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("f", "g", 0));
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("f", "g", 1));
        ans.add("g");
        ans.add("f");
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#remove(Object)}
     * covers:
     *  remove a vertex existing.
     *  remove a vertex not existing.
     */
    @Test
    public void removeTest() {
        Graph<String> graph = emptyInstance();
        Set<String> ans = new HashSet<String>();
        assertFalse(graph.remove("a"));
        assertEquals(ans, graph.vertices());
        graph.add("a");
        ans.add("a");
        graph.add("b");
        ans.add("b");
        graph.set("a","b",1);
        assertTrue(graph.remove("a"));
        ans.remove("a");
        assertEquals(ans, graph.vertices());
        assertEquals(0, graph.set("a","b",0));
        assertTrue(graph.remove("b"));
        ans.remove("b");
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#vertices()}
     * covers:
     *  an empty graph.
     *  a graph with vertices.
     */

    @Test
    public void verticesTest() {
        Graph<String> graph = emptyInstance();
        Set<String> ans = new HashSet<String>();
        assertEquals(ans, graph.vertices());
        graph.add("a");
        ans.add("a");
        assertEquals(ans, graph.vertices());
    }

    /**
     * Test for {@link P1.graph.Graph#sources(Object)}
     * covers:
     *  the vertex is not exist.
     *  no edge connected to the target.
     *  positive number of edges connected to the target.
     */
    @Test
    public void sourcesTest() {
        Graph<String> graph = emptyInstance();
        Map<String, Integer> ans = new HashMap<String, Integer>();
        assertEquals(ans, graph.sources("a"));
        graph.add("a");
        graph.add("b");
        graph.add("c");
        assertEquals(ans, graph.sources("a"));
        graph.set("a", "b", 1);
        assertEquals(ans,graph.sources("a"));
        graph.set("b", "a", 2);
        graph.set("c", "a", 3);
        ans.put("b",2);
        ans.put("c",3);
        assertEquals(ans,graph.sources("a"));
    }

    /**
     * Test for {@link P1.graph.Graph#targets(Object)}
     * covers:
     *  the vertex is not exist.
     *  no edge connected to the source
     *  positive number of edges connected to the source
     */
    @Test
    public void targetsTest() {
        Graph<String> graph = emptyInstance();
        Map<String, Integer> ans = new HashMap<String, Integer>();
        assertEquals(ans, graph.targets("a"));
        graph.add("a");
        graph.add("b");
        graph.add("c");
        assertEquals(ans, graph.targets("a"));
        graph.set("b", "a", 1);
        assertEquals(ans,graph.targets("a"));
        graph.set("a", "b", 2);
        graph.set("a", "c", 3);
        ans.put("b",2);
        ans.put("c",3);
        assertEquals(ans,graph.targets("a"));
    }
}
