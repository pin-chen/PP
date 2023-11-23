#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstddef>
#include <omp.h>
#include <algorithm>

#include "../common/CycleTimer.h"
#include "../common/graph.h"

#define ROOT_NODE_ID 0
#define NOT_VISITED_MARKER -1

void vertex_set_clear(vertex_set *list)
{
    list->count = 0;
}

void vertex_set_init(vertex_set *list, int count)
{
    list->max_vertices = count;
    list->vertices = (int *)malloc(sizeof(int) * list->max_vertices);
    vertex_set_clear(list);
}

// Take one step of "top-down" BFS.  For each vertex on the frontier,
// follow all outgoing edges, and add all neighboring vertices to the
// new_frontier.
void top_down_step(
    Graph g,
    int depth,
    vertex_set *frontier,
    vertex_set *new_frontier,
    int *distances)
{
    #pragma omp parallel
    {
        int index = 0;
        int* new_frontier_vertics = new int[g->num_nodes];
        #pragma omp for
        for (int i = 0; i < frontier->count; i++)
        {
            int node = frontier->vertices[i];

            int start_edge = g->outgoing_starts[node];
            int end_edge = (node == g->num_nodes - 1)
                            ? g->num_edges
                            : g->outgoing_starts[node + 1];

            // attempt to add all neighbors to the new frontier
            #pragma omp simd
            for (int neighbor = start_edge; neighbor < end_edge; neighbor++)
            {
                int outgoing = g->outgoing_edges[neighbor];
                //#pragma omp critical
                //if (distances[outgoing] == NOT_VISITED_MARKER)
                //{
                //    distances[outgoing] = distances[node] + 1;
                //    int index = new_frontier->count++;
                //    new_frontier->vertices[index] = outgoing;
                //}
                
                // atomic compare and swap
                if (__sync_bool_compare_and_swap(&distances[outgoing], NOT_VISITED_MARKER, depth))
                {
                    new_frontier_vertics[index++] = outgoing;
                }
            }
        }
        #pragma omp critical
        {
            #pragma omp simd
            for (int j = 0; j < index; j++)
            {
                int k = new_frontier->count + j;
                new_frontier->vertices[k] = new_frontier_vertics[j];
            }
            new_frontier->count += index;
        }
        delete[] new_frontier_vertics;
    }
}

// Implements top-down BFS.
//
// Result of execution is that, for each node in the graph, the
// distance to the root is stored in sol.distances.
void bfs_top_down(Graph graph, solution *sol)
{
    vertex_set list1;
    vertex_set list2;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);

    vertex_set *frontier = &list1;
    vertex_set *new_frontier = &list2;

    // initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    // setup frontier with the root node
    frontier->vertices[frontier->count++] = ROOT_NODE_ID;
    sol->distances[ROOT_NODE_ID] = 0;

    int depth = 0;
    while (frontier->count != 0)
    {
        depth++;

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        vertex_set_clear(new_frontier);

        top_down_step(graph, depth, frontier, new_frontier, sol->distances);

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set *tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;
    }

    free(list1.vertices);
    free(list2.vertices);
}

void bottom_up_step(
    Graph g,
    int depth,
    int &count,
    int *distances)
{
    #pragma omp parallel for schedule(auto) reduction(+:count)
    for (int node = 0; node < g->num_nodes; node++)
    {
        if (distances[node] == NOT_VISITED_MARKER)
        {
            int start_edge = g->incoming_starts[node];
            int end_edge = (node == g->num_nodes - 1) 
                            ? g->num_edges 
                            : g->incoming_starts[node + 1];

            for (int neighbor = start_edge; neighbor < end_edge; neighbor++)
            {
                int incoming = g->incoming_edges[neighbor];
                if (distances[incoming] == depth - 1)
                {
                    distances[node] = depth;
                    count++;
                    break;
                }
            }
        }
    }
}

void bfs_bottom_up(Graph graph, solution *sol)
{
    // For PP students:
    //
    // You will need to implement the "bottom up" BFS here as
    // described in the handout.
    //
    // As a result of your code's execution, sol.distances should be
    // correctly populated for all nodes in the graph.
    //
    // As was done in the top-down case, you may wish to organize your
    // code by creating subroutine bottom_up_step() that is called in
    // each step of the BFS process.

    // initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    // setup frontier with the root node
    sol->distances[ROOT_NODE_ID] = 0;

    int depth = 0;
    int count = 1;
    while (count != 0)
    {
        depth++;

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        //vertex_set_clear(new_frontier);
        count = 0;

        bottom_up_step(graph, depth, count, sol->distances);

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif
    }
}

void bottom_up_step_hybrid(
    Graph g,
    int depth,
    vertex_set *new_frontier,
    int *distances)
{
    /*
    int all_not_visited = 0;
    int* all_not_visited_vertics = new int[g->num_nodes];
    #pragma omp parallel
    {
        int not_visited = 0;
        int* not_visited_vertics = new int[g->num_nodes];
        #pragma omp for
        for (int node = 0; node < g->num_nodes; node++)
        {
            if (distances[node] == NOT_VISITED_MARKER)
            {
                not_visited_vertics[not_visited++] = node;
            }
        }
        #pragma omp critical
        {
            #pragma omp simd
            for (int i = 0; i < not_visited; i++)
            {
                all_not_visited_vertics[all_not_visited + i] = not_visited_vertics[i];
            }
            all_not_visited += not_visited;
        }
    }
    */
    #pragma omp parallel 
    {
        int index = 0;
        int *new_frontier_vertics = new int[g->num_nodes];
        #pragma omp for schedule(auto)
        for (int node = 0; node < g->num_nodes; node++)
        {
            if (distances[node] == NOT_VISITED_MARKER)
            {
                int start_edge = g->incoming_starts[node];
                int end_edge = (node == g->num_nodes - 1) 
                                ? g->num_edges 
                                : g->incoming_starts[node + 1];

                for (int neighbor = start_edge; neighbor < end_edge; neighbor++)
                {
                    int incoming = g->incoming_edges[neighbor];
                    if (distances[incoming] == depth - 1)
                    {
                        distances[node] = depth;
                        new_frontier_vertics[index++] = node;
                        break;
                    }
                }
            }
        }
        #pragma omp critical
        {
            #pragma omp simd
            for (int i = 0; i < index; i++)
            {
                new_frontier->vertices[new_frontier->count + i] = new_frontier_vertics[i];
            }
            new_frontier->count += index;
        }
        delete[] new_frontier_vertics;
    }
}

void bfs_hybrid(Graph graph, solution *sol)
{
    // For PP students:
    //
    // You will need to implement the "hybrid" BFS here as
    // described in the handout.


    vertex_set list1;
    vertex_set list2;
    vertex_set_init(&list1, graph->num_nodes);
    vertex_set_init(&list2, graph->num_nodes);

    vertex_set *frontier = &list1;
    vertex_set *new_frontier = &list2;

    // initialize all nodes to NOT_VISITED
    #pragma omp parallel for
    for (int i = 0; i < graph->num_nodes; i++)
        sol->distances[i] = NOT_VISITED_MARKER;

    // setup frontier with the root node
    frontier->vertices[frontier->count++] = ROOT_NODE_ID;
    sol->distances[ROOT_NODE_ID] = 0;

    int depth = 0;
    int num_visited = 1;
    while (frontier->count != 0)
    {
        depth++;

#ifdef VERBOSE
        double start_time = CycleTimer::currentSeconds();
#endif

        vertex_set_clear(new_frontier);

        // choose better approach
        if (frontier->count <= (graph->num_nodes - num_visited) / 4)
        {
            top_down_step(graph, depth, frontier, new_frontier, sol->distances);
        }
        else
        {
            bottom_up_step_hybrid(graph, depth, new_frontier, sol->distances);
        }

        num_visited += new_frontier->count;

#ifdef VERBOSE
        double end_time = CycleTimer::currentSeconds();
        printf("frontier=%-10d %.4f sec\n", frontier->count, end_time - start_time);
#endif

        // swap pointers
        vertex_set *tmp = frontier;
        frontier = new_frontier;
        new_frontier = tmp;
    }

    free(list1.vertices);
    free(list2.vertices);
}
