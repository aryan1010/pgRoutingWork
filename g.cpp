#include "drivers/driving_distance/drivedist_driver.h"

#include <sstream>
#include <deque>
#include <vector>

#include "dijkstra/pgr_dijkstra.hpp"

#include "cpp_common/pgr_alloc.hpp"
#include "cpp_common/pgr_assert.h"

#undef WITH_TIME
void
do_pgr_driving_many_to_dist(
        Edge_t  *data_edges, size_t total_edges,
        int64_t *start_vertex, size_t s_len,
        double distance,
        bool directedFlag,
        bool equiCostFlag,
        Path_rt **return_tuples, size_t *return_count,) {

    
        graphType gType = directedFlag? DIRECTED: UNDIRECTED;
        std::deque<Path> paths;
        std::vector<int64_t> start_vertices(start_vertex, start_vertex + s_len);

        auto vertices(pgrouting::extract_vertices(data_edges, total_edges));
        if (directedFlag) {

            pgrouting::DirectedGraph digraph(vertices, gType);

            digraph.insert_edges(data_edges, total_edges, true);

            paths = pgr_drivingDistance(
                    digraph, start_vertices, distance, equiCostFlag, log);

        }

        size_t count(count_tuples(paths));

        *return_tuples = pgr_alloc(count, (*return_tuples));
        auto trueCount(collapse_paths(return_tuples, paths));
        *return_count = trueCount;


    
}
