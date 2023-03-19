#include <boost/config.hpp>
#include <iostream>
#include <fstream>
// including basic headers
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
// including boost headers
using namespace boost;

int main(int, char*[])
{
    typedef adjacency_list< listS, vecS, directedS, no_property,property< edge_weight_t, int > > graph_t;
    typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;
    typedef std::pair< int, int > Edge;

    const int num_nodes = 5;
    enum nodes{A,B,C,D,E};
    char name[] = "ABCDE";
    Edge edge_array[] = { {A,C}, {B,B}, {B, D}, {B, E},{C, B}, {C,D},{D,E}, 
    {E, A},{E, B} };
    int weights[] = { 1, 2, 1, 2, 7, 3, 1, 1, 1 };
    int num_arcs = sizeof(edge_array) / sizeof(Edge);
    graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);
    property_map< graph_t, edge_weight_t >::type weightmap
        = get(edge_weight, g);
    std::vector< int > d(num_vertices(g));
    vertex_descriptor s = vertex(A, g);

    dijkstra_shortest_paths(g, s,distance_map(boost::make_iterator_property_map( 
                d.begin(), get(boost::vertex_index, g))));

    std::cout << "Distances " << std::endl;
    graph_traits< graph_t >::vertex_iterator vi, vend;
    for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi)
    {
        std::cout << "distance(" << name[*vi] << ") = " << d[*vi]<<std::endl;
    }

    return 0;
}

// This code demonstrates how to use the Boost C++ library's graph algorithms to perform Dijkstra's shortest path algorithm on a graph.

// The code starts by including various Boost libraries, including the Graph library which contains functions and data structures for graph manipulation. It then defines a directed graph data structure using the adjacency_list template, which represents a graph as a collection of vertices and edges.

// The graph structure includes the property template parameter to specify that the edges have an associated weight of type int. It then defines a type alias for the graph's vertex descriptor and an Edge pair representing an edge in the graph.

// Next, it creates a graph with five nodes labeled A through E and edges connecting them with different weights. The code then creates a property map that maps the edges of the graph to their weights.

// After that, it defines two vectors for storing the predecessor and distance information of the vertices in the graph. It selects vertex A as the starting vertex for the shortest path algorithm and calls the dijkstra_shortest_paths function from Boost's graph algorithms library with the graph, the starting vertex, and the two vectors.

// The dijkstra_shortest_paths function calculates the shortest paths from the starting vertex to all other vertices in the graph and stores the results in the two vectors.

// Finally, the code iterates over all the vertices in the graph, printing out the shortest distances from the starting vertex to each vertex and their corresponding parents.