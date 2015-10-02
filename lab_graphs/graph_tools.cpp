/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
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
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	queue<Vertex> q;
	q.push(start);
	unordered_map<Vertex, Vertex> pred;
	pred.insert(make_pair(start,start));
	
	Vertex b;
	while(!q.empty()){
		Vertex u = q.front();
		q.pop();
		if(u==end)
		b=u;
		vector<Vertex> ad = graph.getAdjacent(u);
		for(int i =0;i<ad.size();i++){
			if(graph.getVertexLabel(ad[i])!="Visited"){
				q.push(ad[i]);
				graph.setVertexLabel(ad[i],"Visited");
				pred.insert(make_pair(ad[i],u));
			}		
		}
		
	}
	Vertex u;
	int count = 0;
	while(b!=pred[b]){
		u = pred[b];
		graph.setEdgeLabel(b,u,"MINPATH");
		b = u;
		count++;		
	}
	return count;	
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
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
int GraphTools::findMinWeight(Graph & graph)
{
 	vector<Vertex> allVertex = graph.getVertices();
        vector<Edge> allEdge = graph.getEdges();
        for (int i=0; i<allVertex.size();i++)
        {
                graph.setVertexLabel(allVertex[i],"UNEXPLORED");
                vector<Vertex> adjacent = graph.getAdjacent(allVertex[i]);
                for (int j=0; j<adjacent.size();j++)
                {
                        graph.setEdgeLabel(allVertex[i],adjacent[j],"UNEXPLORED");
                }
        }
 
        stack<Vertex> vertices1;
        stack<Vertex> vertices2;
 
    	minWeightHelper(graph, graph.getStartingVertex(), vertices1, vertices2);
        Vertex curbest1;
        Vertex curbest2;
       
        curbest1 = vertices1.top();
        curbest2 = vertices2.top();
        vertices1.pop();
        vertices2.pop();
        while (!vertices1.empty())
        {
                if (graph.getEdgeWeight(vertices1.top(),vertices2.top()) < graph.getEdgeWeight(curbest1,curbest2))
                {
                        curbest1 = vertices1.top();
                        curbest2 = vertices2.top();
                }
                vertices1.pop();
                vertices2.pop();
        }
        graph.setEdgeLabel(curbest1,curbest2,"MIN");
        return graph.getEdgeWeight(curbest1,curbest2);
}

void GraphTools::minWeightHelper(Graph & graph, Vertex v, stack<Vertex> & vertices1, stack<Vertex> & vertices2)
{
        vector<Vertex> adjacent = graph.getAdjacent(v);
        for(int i=0;i<adjacent.size();i++)
        {
                if (graph.getVertexLabel(adjacent[i]) == "UNEXPLORED")
                {
                        graph.setVertexLabel(adjacent[i],"VISITED");
                        graph.setEdgeLabel(v,adjacent[i],"DISCOVERY");
                        vertices1.push(v);
                        vertices2.push(adjacent[i]);
                        minWeightHelper(graph,adjacent[i],vertices1,vertices2);
                }
                else if (graph.getEdgeLabel(v,adjacent[i]) == "UNEXPLORED")
                {
                        graph.setEdgeLabel(v,adjacent[i],"CROSS");
                        vertices1.push(v);
                        vertices2.push(adjacent[i]);
                }
        }
        return;
}
/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector<Edge> theEdges = graph.getEdges();
    std::sort(theEdges.begin(), theEdges.end());

    DisjointSets theVertexSet;
    vector<Vertex> theVertices = graph.getVertices();
    theVertexSet.addelements(theVertices.size());

    int size = theVertices.size();
    int count = 0;
    vector<Edge>::iterator iter;
    for(iter = theEdges.begin(); iter != theEdges.end(); iter++)
    {
        if(count == size - 1) break;
        if(theVertexSet.find(iter->source) != theVertexSet.find(iter->dest))
        {
            theVertexSet.setunion(iter->source, iter->dest);  
            graph.setEdgeLabel(iter->source, iter->dest, "MST");
            count++;
        }
    }
}
