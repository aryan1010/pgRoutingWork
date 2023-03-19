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
