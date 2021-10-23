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
public class ConcreteVerticesGraph<L> implements Graph<L> {

    private final List<Vertex<L>> vertices = new ArrayList<>();

    /**
     * <p>
     * Abstraction function:
     * </p>
     * f(G) = {v | v is the vertex in the graph G}
     *
     * <p>
     * Representation invariant:
     * </p>
     * All vertices are distinct, and the edges info exist both in sources and targets.
     *
     * <p>
     * Safety from rep exposure:
     * </p>
     * All fields are private, and method are also private if possible to avoid exposure.
     * Public methods return copied variable(unable to access to the private field).
     * Elements of vertices are immutable.
     */

    /**
     * construction
     */
    ConcreteVerticesGraph() {
    }

    private void checkRep() {
        Set<L> check = new HashSet<>();
        for (Vertex<L> value : vertices) {
            assert !(check.contains(value.getLabel()));
            check.add(value.getLabel());
        }
        for (Vertex<L> vertex : vertices) {
            Map<L, Integer> tmp = vertex.getSources();
            for (L e : tmp.keySet()) {
                assert check.contains(e);
            }
        }
        for (Vertex<L> vertex : vertices) {
            Map<L, Integer> tmp = vertex.getTargets();
            for (L e : tmp.keySet()) {
                assert check.contains(e);
            }
        }
    }

    @Override public boolean add(L vertex) {
        for (Vertex<L> v : vertices)
            if (v.getLabel().equals(vertex)) return false;

        Vertex<L> v = new Vertex<L>(vertex);
        vertices.add(v);
        checkRep();
        return true;
    }

    @Override public int set(L source, L target, int weight) {
        if (weight < 0) throw new RuntimeException("The weight should be positive");
        Vertex<L> SourceVertex = null,TargetVertex = null;
        boolean isSource = false,isTarget = false;
        if (weight > 0) {
            add(source);
            add(target);
        }
        for (Vertex<L> v : vertices) {
            if (v.getLabel().equals(source)) {
                SourceVertex = v;
                isSource = true;
            }
            if (v.getLabel().equals(target)) {
                TargetVertex = v;
                isTarget = true;
            }
        }

        if (weight == 0) {
            if (isSource == false || isTarget == false) return 0;
        }

        int ret;
        ret = SourceVertex.setTargetEdge(target,weight);
        TargetVertex.setSourceEdge(source,weight);

        checkRep();
        return ret;
    }

    @Override public boolean remove(L vertex) {
        boolean isVertex = false;
        for (int i=0; i<vertices.size(); ++i) {
            if (!vertices.get(i).getLabel().equals(vertex)) continue;
            isVertex = true;
            vertices.remove(i);
            break;
        }
        if (isVertex == false) return false;

        for (Vertex<L> v:vertices) {
            v.setSourceEdge(vertex,0);
            v.setTargetEdge(vertex,0);
        }
        checkRep();
        return true;
    }

    @Override public Set<L> vertices() {
        Set<L> resultSet = new HashSet<>();
        for (Vertex<L> v : vertices)
            resultSet.add(v.getLabel());
        return resultSet;
    }

    @Override public Map<L, Integer> sources(L target) {
        Vertex<L> targetVertex = null;
        for (Vertex<L> v:vertices) {
            if (v.getLabel().equals(target)) {
                targetVertex = v;
                break;
            }
        }
        if (targetVertex == null) return new HashMap<>();
        return targetVertex.getSources();
    }

    @Override public Map<L, Integer> targets(L source) {
        Vertex<L> sourceVertex = null;
        for (Vertex<L> v:vertices) {
            if (v.getLabel().equals(source)) {
                sourceVertex = v;
                break;
            }
        }
        if (sourceVertex == null) return new HashMap<>();
        return sourceVertex.getTargets();
    }

    @Override
    public String toString() {
        StringBuilder ans = new StringBuilder();
        for (Vertex<L> vertex : vertices) {
            ans.append(vertex.toString()).append("\n--------------------\n");
        }
        return ans.toString();
    }

}

/**
 * TODO specification
 * Mutable.
 * This class is internal to the rep of ConcreteVerticesGraph.
 *
 * <p>PS2 instructions: the specification and implementation of this class is
 * up to you.
 */
class Vertex<L> {

    private final L label;
    private final Map<L, Integer> sources,targets;

    /**
     * <p>
     * Abstraction function:
     * </p>
     * f(V) = (label, {(source, weight) | edges to V}, {(target, weight) | edges
     * from V}), represent a vertex
     *
     * <p>
     * Representation invariant:
     * </p>
     * All weights are positive.
     *
     * <p>
     * Safety from rep exposure:
     * </p>
     * use immutable String and Integer type
     * when return the out , use defensive return
     */

    /**
     * Vertex constructor
     * @param label the label of the vertex
     */

    public Vertex(L label) {
        this.label = label;
        this.sources = new HashMap<>();
        this.targets = new HashMap<>();
    }

    /**
     * Check representation
     */

    private void checkRep() {
        for (Integer weight : sources.values()) assert weight > 0;
        for (Integer weight : targets.values()) assert weight > 0;
    }

    /**
     * Get the label of the vertex.
     *
     * @return the label of the vertex
     */
    public L getLabel() {
        return label;
    }

    /**
     * Get the edges from the vertex.
     *
     * @return the pair (source, weight) from the vertex
     */
    public Map<L, Integer> getTargets() {
        return new HashMap<>(targets);
    }

    /**
     * Get the edges to the vertex.
     *
     * @return the pair (source, weight) to the vertex
     */
    public Map<L, Integer> getSources() {
        return new HashMap<>(sources);
    }

    /**
     *
     * @param target a vertex to be check whether a target
     * @return true if the vertex is one of the targets
     */

    public boolean isTarget(L target) {
        return targets.containsKey(target);
    }

    /**
     *
     * @param source a vertex to be check whether a source
     * @return true if the vertex is one of the source
     */

    public boolean isSource(L source) {
        return targets.containsKey(source);
    }

    /**
     * Get the weight of the edge from this vertex to target
     * @param target the target of the edge
     * @return the weight of the edge or 0 if the edge is not exit
     */

    public int getTargetWeight(L target) {
        if (isTarget(target))
            return targets.get(target);
        return 0;
    }

    /**
     * Get the weight of the edge from source to the vertex
     * @param source the source of the edge
     * @return the weight of the edge or 0 if the edge is not exit
     */

    public int getSourceWeight(L source) {
        if (isSource(source))
            return sources.get(source);
        return 0;
    }

    /**
     * Add, change or remove a weighted directed edge from this vertex to target.
     * If the weight is positive, add a new edge from this vertex to target or update the weight of the edge to the new weight.
     * Vertices with the given labels are added to the graph if they do not already exist.
     * If weight is zero, remove the edge if it exists (the graph is not otherwise modified).
     *
     * @param target the target of the edge
     * @param weight the weight of the edge
     * @return the previous weight of the edge (zero if not exist)
     */

    public int setTargetEdge(L target, int weight) {
        if (targets.containsKey(target)) {
            int ret;
            if (weight > 0) ret = targets.replace(target, weight);
            else ret = targets.remove(target);
            checkRep();
            return ret;
        } else {
            if (weight > 0) targets.put(target, weight);
            checkRep();
            return 0;
        }
    }

    /**
     * Add, change or remove a weighted directed edge from source to this vertex.
     * If the weight is positive, add a new edge from source to this vertex or update the weight of the edge to the new weight.
     * Vertices with the given labels are added to the graph if they do not already exist.
     * If weight is zero, remove the edge if it exists (the graph is not otherwise modified).
     *
     * @param source the source of the edge
     * @param weight the weight of the edge
     * @return the previous weight of the edge (zero if not exist)
     */

    public int setSourceEdge(L source, int weight) {
        if (sources.containsKey(source)) {
            int ret;
            if (weight > 0) ret = sources.replace(source, weight);
            else ret = sources.remove(source);
            checkRep();
            return ret;
        } else {
            if (weight > 0) sources.put(source, weight);
            checkRep();
            return 0;
        }
    }

    @Override
    public String toString() {
        String ans;
        ans = this.getLabel().toString();
        ans += ":\nSources:";
        ans += sources.toString();
        ans += ":\nTarget:";
        ans += targets.toString();
        ans += ":\n";
        return ans;
    }

}
