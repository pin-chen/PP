#include "page_rank.h"

#include <stdlib.h>
#include <cmath>
#include <omp.h>
#include <utility>

#include "../common/CycleTimer.h"
#include "../common/graph.h"

// pageRank --
//
// g:           graph to process (see common/graph.h)
// solution:    array of per-vertex vertex scores (length of array is num_nodes(g))
// damping:     page-rank algorithm's damping parameter
// convergence: page-rank algorithm's convergence threshold
//
void pageRank(Graph g, double *solution, double damping, double convergence)
{

  // initialize vertex weights to uniform probability. Double
  // precision scores are used to avoid underflow for large graphs

  int numNodes = num_nodes(g);
  double equal_prob = 1.0 / numNodes;
  double *score_new = new double[numNodes];
  double *score_old = new double[numNodes];
  #pragma omp parallel for
  for (int i = 0; i < numNodes; ++i)
  {
    score_old[i] = equal_prob;
  }

  bool converged = false;
  while (!converged) {
    double score_of_nodes_with_no_outgoing_edges = 0.0;
    #pragma omp parallel for reduction(+:score_of_nodes_with_no_outgoing_edges)
    for (int v = 0; v < numNodes; v++)
    {
      if (outgoing_size(g, v) == 0)
      {
        score_of_nodes_with_no_outgoing_edges += score_old[v];
      }
    }

    double global_diff = 0.0;
    #pragma omp parallel for reduction(+:global_diff)
    for (int vi = 0; vi < numNodes; vi++)
    {
      score_new[vi] = 0.0;
      const Vertex* begin = incoming_begin(g, vi);
      const Vertex* end = incoming_end(g, vi);
      for (const Vertex* vj = begin; vj != end; vj++)
      {
        score_new[vi] += score_old[*vj] / outgoing_size(g, *vj);
      }
      score_new[vi] = (damping * score_new[vi]) + (1.0 - damping) / numNodes;
      score_new[vi] += damping * score_of_nodes_with_no_outgoing_edges / numNodes;
      global_diff += abs(score_new[vi] - score_old[vi]);
    }

    converged = (global_diff < convergence);

    #pragma omp parallel for
    for (int vi = 0; vi < numNodes; vi++)
    {
      score_old[vi] = score_new[vi];
    }
  }

  #pragma omp parallel for
  for (int vi = 0; vi < numNodes; vi++)
  {
    solution[vi] = score_old[vi];
  }

  delete[] score_new;
  delete[] score_old;
  /*
     For PP students: Implement the page rank algorithm here.  You
     are expected to parallelize the algorithm using openMP.  Your
     solution may need to allocate (and free) temporary arrays.

     Basic page rank pseudocode is provided below to get you started:

     // initialization: see example code above
     score_old[vi] = 1/numNodes;

     while (!converged) {

       // compute score_new[vi] for all nodes vi:
       score_new[vi] = sum over all nodes vj reachable from incoming edges
                          { score_old[vj] / number of edges leaving vj  }
       score_new[vi] = (damping * score_new[vi]) + (1.0-damping) / numNodes;

       score_new[vi] += sum over all nodes v in graph with no outgoing edges
                          { damping * score_old[v] / numNodes }

       // compute how much per-node scores have changed
       // quit once algorithm has converged

       global_diff = sum over all nodes vi { abs(score_new[vi] - score_old[vi]) };
       converged = (global_diff < convergence)
     }

   */
}
