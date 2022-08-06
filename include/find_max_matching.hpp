/**
 *@file find_max_matching.hpp
 *@author Talpa Grigory
 *
 *Реализация метода поиска наибольшего паросочетания.
 */

#ifndef INCLUDE_FIND_MAX_MATCHING_HPP_
#define INCLUDE_FIND_MAX_MATCHING_HPP_
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <optional>
#include "graph.hpp"

namespace graph {
/**
 *@brief Поиск наименьшего предка.
 *
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
std::optional<size_t> LCA(std::optional<size_t> root, std::optional<size_t> u, std::optional<size_t> v,
         std::unordered_map<size_t, std::optional<size_t>>* match,
         std::unordered_map<size_t, std::optional<size_t> >* father,
         std::unordered_map<size_t, std::optional<size_t> >* base,
         size_t V) {
    std::unordered_map<size_t, bool> inp;
    for (size_t i = 0; i < V + 1; i++) {
      inp[i] = 0;
    }
    while (true) {
    u = (*base)[u];
    inp[u] = true;
    if (u == root)
      break;
    u = (*father)[(*match)[u]];
  }
    while (true) {
      v = (*base)[v];
        if (inp[v])
            return v;
        else
            v = (*father)[(*match)[v]];
    }
}

/**
 *@brief Проход от вершины до базы.
 *
 *
 *@param base массив базу цветка вершин.
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 *@param lca наименьший общий предок
 */
void MarkBlossom(std::optional<size_t> lca, std::optional<size_t> u,
         std::unordered_map<size_t, std::optional<size_t>>* match,
         std::unordered_map<size_t, std::optional<size_t>>* father,
         std::unordered_map<size_t, std::optional<size_t>>* base,
         std::unordered_map<size_t, bool>* inb) {
    while ((*base)[u] != lca) {
        std::optional<size_t> v = ( * match)[u];
        (*inb)[(*base)[u]] = true;
        (*inb)[(*base)[v]] = true;
        u = (*father)[v];
        if ((*base)[u] != lca)
            (*father)[u] = v;
    }
}

/**
 *@brief Сжатие цветка.
 *
 *
 *@param base массив базу цветка вершин.
 *@param father массив хранящий предков нечетных вершин.
 *@param lca наименьший общий предок
 */
void BlossomContraction(std::optional<size_t> s, std::optional<size_t> u, std::optional<size_t> v,
            std::unordered_map<size_t, std::optional<size_t>>* match,
            std::unordered_map<size_t, std::optional<size_t>>* father,
            std::unordered_map<size_t, std::optional<size_t>>* base,
            std::unordered_map<size_t, std::optional<size_t>>* q,
            std::unordered_map<size_t, bool>* inq,
            size_t* qt, size_t V) {
    std::optional<size_t> lca = LCA(s, u, v, match, father, base, V);
    std::unordered_map<size_t, bool> inb;
    for (size_t i = 0; i < V + 1; i++) {
        inb[i] = 0;
    }

    MarkBlossom(lca, u, match, father, base, & inb);
    MarkBlossom(lca, v, match, father, base, & inb);

    if ((*base)[u] != lca)
        (*father)[u] = v;
    if ((*base)[v] != lca)
        (*father)[v] = u;
    for (size_t i = 0; i < V; i++) {
        if (inb[(*base)[i]]) {
            (*base)[i] = lca;
            if (!(*inq)[i]) {
        ++(*qt);
        (*q)[(*qt)] = i;
                (*inq)[i] = true;
            }
        }
    }
}

template <class T>
/**
 *@brief Поиск увеличивающей цепи.
 *
 *@tparam T тип графа.
 *
 *@param base массив базу цветка вершин.
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
std::optional<size_t> FindAugmentingPath(size_t s, const T& graph,
              std::unordered_map<size_t, std::optional<size_t>>* match,
              std::unordered_map<size_t, std::optional<size_t>>* father,
              size_t V) {
    for (size_t i = 0; i < V + 1; i++) {
        (*father)[i] = std::nullopt;
    }
    size_t qh = 0, qt = 0;
    std::unordered_map<size_t, bool> inq;
    for (size_t i = 0; i < V + 1; i++) {
        inq[i] = 0;
    }
    std::unordered_map<size_t, std::optional<size_t>> base;
    for (size_t i = 0; i < V + 1; i++) {
        base[i] = i;
    }
    std::unordered_map<size_t, std::optional<size_t>> q;
    for (size_t i = 0; i < V + 1; i++) {
        q[i] = std::nullopt;
    }
    q[0] = s;
    inq[s] = true;

    while (qh <= qt) {
        std::optional<size_t> u = q[qh++];
        if (graph.HasVertex(u)) {
          for (auto elem : graph.Edges(u)) {
                size_t v = elem;
                if (base[u] != base[v] && (*match)[u] != v) {
                  if ((v == s) ||
                  ((*match)[v] != std::nullopt &&
                  (*father)[(*match)[v]] != std::nullopt)) {
                    BlossomContraction(s, u, v, match,
                    father, &base, &q, &inq, &qt, V);
                  } else if ((*father)[v] == std::nullopt) {
                      (*father)[v] = u;
                      if ((*match)[v] == std::nullopt) {
                        return v;
                      } else if (!inq[(*match)[v]]) {
                        ++qt;
                        q[qt] = (*match)[v];
                        inq[(*match)[v]] = true;
                      }
                  }
                }
          }
        }
    }
    return std::nullopt;
}

/**
 *@brief Увелечение пути вдоль цепи.
 *
 *@tparam T тип графа.
 *
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
size_t AugmentPath(std::optional<size_t> t, std::unordered_map<size_t, std::optional<size_t>>* match,
           std::unordered_map<size_t, std::optional<size_t>>* father) {
    if(t == std::nullopt)
      return 0;
    std::optional<size_t> u = t;
    std::optional<size_t> v, w;
    while (u != std::nullopt) {
        v = (*father)[u];
        w = (*match)[v];
        (*match)[v] = u;
        (*match)[u] = v;
        u = w;
    }
    return 1;
}

template <class T>
/**
 *@brief Алгоритм Эдондса.
 *
 *@tparam T тип графа.
 *
 *@param match массив хранящий паросочетания.
 *@param match_counts количество ребер в наибольшем парасочетании.
 */
size_t EdmondsBlossomAlgorithm(const T& graph, size_t V,
                 std::unordered_map<size_t, std::optional<size_t>>* match) {
    size_t match_counts = 0;
    std::unordered_map<size_t, std::optional<size_t>> father;
    for (size_t i = 0; i < V + 1; i++) {
        father[i] = std::nullopt;
    }

    for (size_t u = 0; u < V; u++) {
        if ((*match)[u] == std::nullopt)
            match_counts +=
            AugmentPath(FindAugmentingPath(u,
            graph, match, & father, V), match, & father);
    }
    return match_counts;
}

template <class T>
/**
 *@brief Функция поиска наибольшего паросочетания.
 *
 *@tparam T тип графа.
 *
 *@param result вектор, в котором хранится ответ.
 */
void FindMaxMatching(const T& graph,
           std::vector<std::pair<size_t, size_t>>* result) {
    size_t V = graph.NumVertices();
    std::unordered_map<size_t, std::optional<size_t>> match;
    for (size_t i = 0; i < V + 1; i++) {
        match[i] = std::nullopt;
    }
    size_t res = EdmondsBlossomAlgorithm(graph, V, & match);
    if (!res)
        return;
    for (size_t i = 0; i < V; i++) {
        if (i < match[i]) {
            (*result).push_back({i, match[i]});
        }
    }
}
}  // namespace graph
#endif  // INCLUDE_FIND_MAX_MATCHING_HPP_
