/* Copyright (c) 2015-2016 MIT 6.005 course staff, all rights reserved.
 * Redistribution of original or derived work requires permission of course staff.
 */
package P1.poet;

import java.io.File;
import java.io.IOException;
import java.util.*;

import P1.graph.Graph;

/**
 * A graph-based poetry generator.
 *
 * <p>GraphPoet is initialized with a corpus of text, which it uses to derive a
 * word affinity graph.
 * Vertices in the graph are words. Words are defined as non-empty
 * case-insensitive strings of non-space non-newline characters. They are
 * delimited in the corpus by spaces, newlines, or the ends of the file.
 * Edges in the graph count adjacencies: the number of times "w1" is followed by
 * "w2" in the corpus is the weight of the edge from w1 to w2.
 *
 * <p>For example, given this corpus:
 * <pre>    Hello, HELLO, hello, goodbye!    </pre>
 * <p>the graph would contain two edges:
 * <ul><li> ("hello,") -> ("hello,")   with weight 2
 *     <li> ("hello,") -> ("goodbye!") with weight 1 </ul>
 * <p>where the vertices represent case-insensitive {@code "hello,"} and
 * {@code "goodbye!"}.
 *
 * <p>Given an input string, GraphPoet generates a poem by attempting to
 * insert a bridge word between every adjacent pair of words in the input.
 * The bridge word between input words "w1" and "w2" will be some "b" such that
 * w1 -> b -> w2 is a two-edge-long path with maximum-weight weight among all
 * the two-edge-long paths from w1 to w2 in the affinity graph.
 * If there are no such paths, no bridge word is inserted.
 * In the output poem, input words retain their original case, while bridge
 * words are lower case. The whitespace between every word in the poem is a
 * single space.
 *
 * <p>For example, given this corpus:
 * <pre>    This is a test of the Mugar Omni Theater sound system.    </pre>
 * <p>on this input:
 * <pre>    Test the system.    </pre>
 * <p>the output poem would be:
 * <pre>    Test of the system.    </pre>
 *
 * <p>PS2 instructions: this is a required ADT class, and you MUST NOT weaken
 * the required specifications. However, you MAY strengthen the specifications
 * and you MAY add additional methods.
 * You MUST use Graph in your rep, but otherwise the implementation of this
 * class is up to you.
 */
public class GraphPoet {

    private final Graph<String> graph = Graph.empty();
    private final List<String> wordList;

    /**
     * <p>
     * Abstraction function:
     * </p>
     * f(input) =  a graph with vertices which are words exist in the text,
     * edges shows A and B are adjacent and weight shows the number of the adjacency
     *
     * <p>
     * Representation invariant:
     * </p>
     * if there is more than one vertex
     * there is only one vertex with inEdge-weightSum = outEdge-weightSum -1
     * and only one vertex with inEdge-weightSum = outEdge-weightSum +1
     * other vertices all satisfy inEdge-weightSum = outEdge-weightSum
     *
     * <p>
     * Safety from rep exposure:
     * </p>
     * Field graph is private and final and has no outer access.
     *
     */

    /**
     * Create a new poet with the graph from corpus (as described above).
     *
     * @param corpus text file from which to derive the poet's affinity graph
     * @throws IOException if the corpus file cannot be found or read
     */
    public GraphPoet(File corpus) throws IOException {
        wordList = new LinkedList<>();

        try (Scanner scanner = new Scanner(corpus)) {
            while (scanner.hasNext()) {
                String lineString = scanner.nextLine();
                wordList.addAll(splitWord(lineString));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        if (wordList.isEmpty()) return;

        if (wordList.size() == 1) graph.add(wordList.get(0).toLowerCase());
        else {
            for (int i=0; i<wordList.size()-1; ++i) {
                int w = graph.set(wordList.get(i).toLowerCase(),wordList.get(i+1).toLowerCase(),1);
                graph.set(wordList.get(i).toLowerCase(),wordList.get(i+1).toLowerCase(),w+1);
            }
        }
        checkRep();
    }

    /**
     * Parse words from the string
     * @param s the string to parse
     * @return the word list
     */

    public List<String> splitWord(String s) {
        List<String> ret = new LinkedList<>();
        for (String now : s.split("\\s+")) if (!now.isEmpty()) ret.add(now);
        return ret;
    }

    /**
     * Check the representation
     */

    private void checkRep() {
        int in = 0,out = 0;
        Set<String> vertices = graph.vertices();
        if (vertices.size() == 1) return;
        for (String s : vertices) {
            int a = 0;
            Map<String, Integer> map = graph.sources(s);
            for (String w : map.keySet()) a += map.get(w);
            int b = 0;
            map = graph.targets(s);
            for (String w : map.keySet()) b += map.get(w);
            if (a == b + 1) {
                in += 1;
                assert in == 1;
            } else if (a == b - 1) {
                out += 1;
                assert out == 1;
            } else {
                assert a == b;
            }
        }
    }

    /**
     * Get the Bridge between two String
     * @param pre the previous String
     * @param post the post String
     * @return the Bridge word, if no such word return "";
     */

    private String getBridge(String pre, String post) {
        String ans = "";
        int weight = -1;
        Map<String, Integer> bridges = graph.targets(pre.toLowerCase());
        for (String e : bridges.keySet()) {
            int tmp = bridges.get(e);
            Map<String, Integer> last = graph.targets(e);
            if (last.containsKey(post.toLowerCase())) {
                int tmp1 = tmp + last.get(post.toLowerCase());
                if (tmp1 > weight) {
                    weight = tmp1;
                    ans = e;
                }
            }
        }
        return ans;
    }

    /**
     * Generate a poem.
     *
     * @param input string from which to create the poem
     * @return poem (as described above)
     */
    public String poem(String input) {
        String[] arr = input.trim().toLowerCase().split("\\s+");
        StringBuilder ans = new StringBuilder();
        for (int i = 0; i < arr.length - 1; i++) {
            ans.append(arr[i]);
            ans.append(" ");
            String bridge = getBridge(arr[i], arr[i + 1]);
            if (!bridge.isEmpty()) {
                ans.append(bridge);
                ans.append(" ");
            }
        }
        ans.append(arr[arr.length - 1]);
        return ans.toString();
    }

    @Override
    public String toString() {
        return graph.toString();
    }

}
