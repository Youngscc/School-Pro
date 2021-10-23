/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.graph;

import java.util.*;

/**
 * An implementation of Graph.
 *
 * <p>PS2 instructions: you MUST use the provided rep.
 */
public class ConcreteEdgesGraph<L> implements Graph<L> {

    private final Set<L> vertices = new HashSet<>();
    private final List<Edge<L>> edges = new ArrayList<>();

    /**
     * <p>
     * Abstraction function:
     * </p>
     * f(G) = {e | e is the edge in the graph G}
     *
     * <p>
     * Representation invariant:
     * </p>
     * For all the edge in the graph, target and source are vertices in the graph, and weight is positive.
     *
     * <p>
     * Safety from rep exposure:
     * <p>
     * All reps are private final, and method are also private if possible to avoid exposure.
     * Public methods return copied variable(unabel to access to the private field).
     * Elements of vertices and edges are immutable.
     */

    public ConcreteEdgesGraph() {
    }

    /**
     * Check representation.
     */

    protected void checkRep() {
        for (Edge<L> e : edges) {
            assert e.getWeight() > 0;
            assert vertices.contains(e.getSource()) && vertices.contains(e.getTarget());
        }
    }

    @Override public boolean add(L vertex) {
        boolean res = vertices.add(vertex);
        checkRep();
        return res;
    }

    @Override public int set(L source, L target, int weight) {
        if (weight < 0)
            throw new RuntimeException("weight should be positive");
        int pre = 0;
        boolean verExist = true;

        if (!vertices.contains(source)) {
            if (weight > 0) vertices.add(source);
            verExist = false;
        }
        if (!vertices.contains(target)) {
            if (weight > 0) vertices.add(target);
            verExist = false;
        }
        if (verExist == true) {
            boolean edgeExist = false;
            for (int i=0; i<edges.size(); ++i) {
                Edge<L> e = edges.get(i);
                if (e.getSource().equals(source) && e.getTarget().equals(target)) {
                    pre = e.getWeight();
                    if (weight > 0) {
                        edges.set(i, edges.get(i).modify(weight));
                    } else {
                        edges.remove(i);
                    }
                    edgeExist = true;
                    break;
                }
            }
            if (edgeExist == false && weight > 0)
                edges.add(new Edge<L>(source, target, weight));
        } else if (weight > 0) {
            edges.add(new Edge<L>(source, target, weight));
        }
        checkRep();
        return pre;
    }

    @Override public boolean remove(L vertex) {

        boolean ret = vertices.remove(vertex);
        if (ret == false) return false;

        for (int i=0; i< edges.size(); ++i) {
            Edge<L>e = edges.get(i);
            if (e.getSource().equals(vertex) || e.getTarget().equals(vertex)) {
                edges.remove(i);
                i--;
            }
        }

        checkRep();
        return true;
    }

    @Override public Set<L> vertices() {
        return new HashSet<>(vertices);
    }

    @Override public Map<L, Integer> sources(L target) {
        Map<L, Integer> ans = new HashMap<>();
        for (Edge<L> e : edges) {
            if (e.getTarget().equals(target)) {
                ans.put(e.getSource(), e.getWeight());
            }
        }
        return ans;
    }

    @Override public Map<L, Integer> targets(L source) {
        Map<L, Integer> ans = new HashMap<>();
        for (Edge<L> e : edges) {
            if (e.getSource().equals(source)) {
                ans.put(e.getTarget(), e.getWeight());
            }
        }
        return ans;
    }

    @Override
    public String toString() {
        return "Vertices: " + vertices.toString() + "\nEdges: " + edges.toString();
    }

}

/**
 * TODO specification
 * Immutable.
 * This class is internal to the rep of ConcreteEdgesGraph.
 *
 * <p>PS2 instructions: the specification and implementation of this class is
 * up to you.
 */
class Edge<L> {

    private final int weight;
    private final L source, target;

    /**
     * <p>
     * Abstraction function:
     * </p>
     * f(E) = (source, target, weight), represent an edge from source to target with weight
     *
     * <p>
     * Representation invariant:
     * </P>
     * Weight is positive
     *
     * <p>
     * Safety from rep exposure:
     * </p>
     * all of the reps are private final to avoid exposure,
     * the L type and the Edge type are both immutable
     * when return the vertices, use defensive return
     */

    /**
     *The constructor of the edge
     *
     * @param source the source of the edge
     * @param target the target of the edge
     * @param weight the weight of the edge
     */

    public Edge(L source, L target, int weight) {
        this.source = source;
        this.target = target;
        this.weight = weight;
        checkRep();
    }

    /**
     * Check representation
     */

    private void checkRep() {
        assert this.weight > 0;
    }

    /**
     * Get the source of the edge
     * @return the source of the edge
     */

    public L getSource() {
        return this.source;
    }

    /**
     * Get the target of the edge
     * @return the target of the edge
     */

    public L getTarget() {
        return this.target;
    }

    /**
     * Get the weight of the edge.
     * @return the weight of the edge
     */

    public int getWeight() {
        return this.weight;
    }

    /**
     * Creat a new Edge with original source and target but new weight
     *
     * @param w a positive weight
     * @return new Edge with original source and target but new weight
     */
    public Edge<L> modify(int w) {
        checkRep();
        return new Edge<>(this.source, this.target, w);
    }

    /**
     * Change the edge into a string in text
     * @return (source -> target : weight)
     */

    @Override
    public String toString() {
        return "(" + source.toString() + " -> " + target.toString() + " : " + weight + ")";
    }

}
