/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <queue>

/**
 * Finds the minimum edge weight in the Graph graph.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph& graph)
{
    // set all vertices to UNEXPLORED
    vector<Vertex> tmp = graph.getVertices();
    for (size_t i = 0; i < tmp.size(); i++) {
        graph.setVertexLabel(tmp[i], "UNEXPLORED");
    }

    // set all edges to UNEXPLORED
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); i++) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    // get min edge
    Edge res = BFS(graph, graph.getStartingVertex());
    graph.setEdgeLabel(res.source, res.dest, "MIN");

    return res.weight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{

    // set all vertices to UNEXPLORED
    vector<Vertex> vertices = graph.getVertices();
    for (size_t i = 0; i < vertices.size(); i++) {
        graph.setVertexLabel(vertices[i], "UNEXPLORED");
    }

    // set all edges to UNEXPLORED
    vector<Edge> edges = graph.getEdges();
    for (size_t i = 0; i < edges.size(); i++) {
        graph.setEdgeLabel(edges[i].source, edges[i].dest, "UNEXPLORED");
    }

    queue<Vertex> q;
    graph.setVertexLabel(end, "VISITED");
    // start from end vertex (leaf)
    q.push(end);

    unordered_map<Vertex, Vertex> parentMapper;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                // key = child (start at end), value = parent (finish at start)
                parentMapper[adj[i]] = v;
            } 
        }
    }

    int tmp = 0;
    // TODO - get this to work
    while (end != start) {
        graph.setEdgeLabel(start, parentMapper[start], "MINPATH");
        start = parentMapper[start];
        tmp++;
    }


    return tmp;
}

/**
 * Finds a minimal spanning tree on a graph.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    /* your code here! */
}

/**
 * Does a BFS of a graph, keeping track of the minimum
 *  weight edge seen so far.
 * @param g - the graph
 * @param start - the vertex to start the BFS from
 * @return the minimum weight edge
 */
Edge GraphTools::BFS(Graph& graph, Vertex start)
{
    queue<Vertex> q;
    graph.setVertexLabel(start, "VISITED");
    q.push(start);
    Edge min;
    min.weight = INT_MAX;

    while (!q.empty()) {
        Vertex v = q.front();
        q.pop();
        vector<Vertex> adj = graph.getAdjacent(v);
        for (size_t i = 0; i < adj.size(); ++i) {
            if (graph.getVertexLabel(adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "DISCOVERY");
                graph.setVertexLabel(adj[i], "VISITED");
                q.push(adj[i]);
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            } else if (graph.getEdgeLabel(v, adj[i]) == "UNEXPLORED") {
                graph.setEdgeLabel(v, adj[i], "CROSS");
                int weight = graph.getEdgeWeight(v, adj[i]);
                if (weight < min.weight) {
                    min.source = v;
                    min.dest = adj[i];
                    min.weight = weight;
                }
            }
        }
    }
    return min;
}
