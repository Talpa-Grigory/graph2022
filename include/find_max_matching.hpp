#ifndef INCLUDE_FIND_MAX_MATCHING_HPP_
#define INCLUDE_FIND_MAX_MATCHING_HPP_#include <vector>

#include <unordered_set>

#include "graph.hpp"

namespace graph {

  size_t LCA(size_t root, size_t u, size_t v, std::vector < size_t > * match, std::vector < size_t > * father, std::vector < size_t > * base, size_t V) {
    std::vector < bool > inp(V + 1);
    while (true) {
      inp[u = ( * base)[u]] = true;
      if (u == root) {
        break;
      }
      u = ( * father)[( * match)[u]];
    }
    while (true) {
      v = ( * base)[v];
      if (inp[( * base)[v]]) {
        return v;
      } else {
        v = ( * father)[( * match)[v]];
      }
    }
  }

  void MarkBlossom(size_t lca, size_t u, std::vector < size_t > * match, std::vector < size_t > * father, std::vector < size_t > * base, std::vector < bool > * inb) {
    while (( * base)[u] != lca) {
      size_t v = ( * match)[u];
      ( * inb)[( * base)[u]] = ( * inb)[( * base)[v]] = true;
      u = ( * father)[v];
      if (( * base)[u] != lca) {
        ( * father)[u] = v;
      }
    }
  }

  void BlossomContraction(size_t s, size_t u, size_t v, std::vector < size_t > * match, std::vector < size_t > * father, std::vector < size_t > * base, std::vector < size_t > * q, std::vector < bool > * inq, size_t * qt, size_t V) {
    size_t lca = LCA(s, u, v, match, father, base, V);
    std::vector < bool > inb(V + 1);
    MarkBlossom(lca, u, match, father, base, & inb);
    MarkBlossom(lca, v, match, father, base, & inb);
    if (( * base)[u] != lca) {
      ( * father)[u] = v;
    }
    if (( * base)[v] != lca) {
      ( * father)[v] = u;
    }
    for (size_t i = 0; i < V; i++) {
      if (inb[( * base)[i]]) {
        ( * base)[i] = lca;
        if (!( * inq)[i]) {
          ( * inq)[( * q)[++( * qt)] = i] = true;
        }
      }
    }
  }

  template < class T >

    size_t FindAugmentingPath(size_t s, T graph, std::vector < size_t > * match, std::vector < size_t > * father, size_t V) {
      for (size_t i = 0; i < V + 1; i++) {
        ( * father)[i] = 0;
      }
      size_t qh = 0, qt = 0;
      std::vector < bool > inq(V + 1);
      std::vector < size_t > base(V + 1);
      for (size_t i = 0; i < V; i++)
        base[i] = i;
      std::vector < size_t > q(V + 1);
      inq[q[qh = qt = 0] = s] = true;
      while (qh <= qt) {
        size_t u = q[qh++];
        if (graph.HasVertex(u)) {
          for (auto elem: graph.Edges(u)) {
            size_t v = elem;
            if (base[u] != base[v] && ( * match)[u] != v) {
              if ((v == s) || (( * match)[v] != 0 && ( * father)[( * match)[v]] != 0)) {
                BlossomContraction(s, u, v, match, father, & base, & q, & inq, & qt, V);
              } else if (( * father)[v] == 0) {
                ( * father)[v] = u;
                if (( * match)[v] == 0) {
                  return v;
                } else if (!inq[( * match)[v]]) {
                  inq[q[++qt] = ( * match)[v]] = true;
                }
              }
            }
          }
        }
      }
      return 0;
    }

  size_t AugmentPath(size_t t, std::vector < size_t > * match, std::vector < size_t > * father) {
    size_t u = t;
    size_t v, w;
    while (u != 0) {
      v = ( * father)[u];
      w = ( * match)[v];
      ( * match)[v] = u;
      ( * match)[u] = v;
      u = w;
    }
    return t != 0;
  }

  template < class T >
    size_t EdmondsBlossomAlgorithm(T graph, std::vector < size_t > * match, size_t V) {
      size_t match_counts = 0;
      std::vector < size_t > father(V + 1);
      for (size_t u = 0; u < V; u++) {
        if (( * match)[u] == 0) {
          match_counts += AugmentPath(FindAugmentingPath(u, graph, match, & father, V), match, & father);
        }
      }
      return match_counts;
    }

  template < class T >
    void FindMaxMatching(T graph, std::vector < std::pair < size_t, size_t >> * result) {
      size_t V = graph.NumVertices();
      std::vector < size_t > match(V + 1);
      size_t res = EdmondsBlossomAlgorithm(graph, & match, V);
      if (!res) {
        return;
      }
      for (size_t i = 0; i < V; i++) {
        if (i < match[i]) {
          ( * result).push_back({
            i,
            match[i]
          });
        }
      }
    }

} // namespace graph
#endif // INCLUDE_FIND_MAX_MATCHING_HPP_