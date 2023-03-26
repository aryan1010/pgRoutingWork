#include <boost/config.hpp>
#include <iostream>
#include <fstream>
                                                        //INCLUDING SOME BASIC HEADERS
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/property_map/property_map.hpp>
                                                        //INCLUDING BOOST HEADERS
using namespace boost;

int main(int, char*[])
{
    typedef adjacency_list< listS, vecS, directedS, no_property,
        property< edge_weight_t, int > >
        graph_t;
    typedef graph_traits< graph_t >::vertex_descriptor vertex_descriptor;
    typedef std::pair< int, int > Edge;

    const int num_nodes = 17;                           // INPUT EDGES
    Edge edge_array[] = { {5,6},{6,5},{10,6},{6,7},{7,6},{7,11},{11,7},{3,7},{7,3},{1,3},{3,1},{11,16},{16,11},{15,10},{16,15},{15,16}
    ,{17,16},{16,17},{11,12},{12,17},{7,8},{8,7},{8,9},{10,11},{8,12},{2,4},{4,2},{13,14},{14,13},{9,8} };
    int weights[] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};  //INPUT WEIGHTS OF THE EDGES
    int distance=5;                                                         //INPUT DISTANCE D FOR THE DRIVING DISTANCE 
    int num_arcs = sizeof(edge_array) / sizeof(Edge);                       //
    graph_t g(edge_array, edge_array + num_arcs, weights, num_nodes);       //MAKING GRAPH
    property_map< graph_t, edge_weight_t >::type weightmap
        = get(edge_weight, g);
    std::vector< int > d(num_vertices(g));                                  //VECTOR FOR STORING THE DISTANCE TO OTHER NODES 
    vertex_descriptor s = vertex(11, g);                                     //STARTING (ROOT) VERTEX

    dijkstra_shortest_paths(g, s,                                           //CALLING THE BOOST LIBRARY FUNCTION
        distance_map(boost::make_iterator_property_map(
                d.begin(), get(boost::vertex_index, g))));

    std::cout << "Distances" << std::endl;
    graph_traits< graph_t >::vertex_iterator vi, vend;                      //DECLARING ITERATORS FOR THE GRAPH'S VERTICES
    for (boost::tie(vi, vend) = vertices(g); vi != vend; ++vi)
    {                                                                       //OUTPUTING THE VERTICES WITH RESTRICTION
        if(d[*vi]<=distance)
        std::cout << "distance(" << *vi << ") = " << d[*vi]<< std::endl;
        else 
        std::cout << "distance(" << *vi<< ") = " << "Not Reachable"<< std::endl;
                 
    }
    std::cout << std::endl;

    // std::ofstream dot_file("figs/dijkstra-eg.dot");       //UNUSED CODE 

    // dot_file << "digraph D {\n"
    //          << "  rankdir=LR\n"
    //          << "  size=\"4,3\"\n"
    //          << "  ratio=\"fill\"\n"
    //          << "  edge[style=\"bold\"]\n"
    //          << "  node[shape=\"circle\"]\n";

    // graph_traits< graph_t >::edge_iterator ei, ei_end;
    // for (boost::tie(ei, ei_end) = edges(g); ei != ei_end; ++ei)
    // {
    //     graph_traits< graph_t >::edge_descriptor e = *ei;
    //     graph_traits< graph_t >::vertex_descriptor u = source(e, g),
    //                                                v = target(e, g);
    //     dot_file << name[u] << " -> " << name[v] << "[label=\""
    //              << get(weightmap, e) << "\"";
    //     if (p[v] == u)
    //         dot_file << ", color=\"black\"";
    //     else
    //         dot_file << ", color=\"grey\"";
    //     dot_file << "]";
    // }
    // dot_file << "}";
    return EXIT_SUCCESS;
}
