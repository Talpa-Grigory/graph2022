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
#include "graph.hpp"

namespace graph {
/**
 *@brief Поиск наименьшего предка.
 *
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
size_t LCA(size_t root, size_t u, size_t v, std::unordered_map < size_t, size_t > * match, std::unordered_map < size_t, size_t > * father, std::unordered_map < size_t, size_t > * base, size_t V) {
    std::unordered_map < size_t, bool > inp;
    for (size_t i = 0; i < V + 1; i++) {
        inp[i] = 0;
    }
    while (true) {
        inp[u = ( * base)[u]] = true;
        if (u == root)
            break;
        u = ( * father)[( * match)[u]];
    }
    while (true) {
        if (inp[v = ( * base)[v]])
            return v;
        else
            v = ( * father)[( * match)[v]];
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
void MarkBlossom(size_t lca, size_t u, std::unordered_map < size_t, size_t > * match, std::unordered_map < size_t, size_t > * father, std::unordered_map < size_t, size_t > * base, std::unordered_map < size_t, bool > * inb) {
    while (( * base)[u] != lca) {
        size_t v = ( * match)[u];
        ( * inb)[( * base)[u]] = ( * inb)[( * base)[v]] = true;
        u = ( * father)[v];
        if (( * base)[u] != lca)
            ( * father)[u] = v;
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
void BlossomContraction(size_t s, size_t u, size_t v, std::unordered_map < size_t, size_t > * match, std::unordered_map < size_t, size_t > * father, std::unordered_map < size_t, size_t > * base, std::unordered_map < size_t, size_t > * q, std::unordered_map < size_t, bool > * inq, size_t * qt, size_t V) {
    size_t lca = LCA(s, u, v, match, father, base, V);
    std::unordered_map < size_t, bool > inb;
    for (size_t i = 0; i < V + 1; i++) {
        inb[i] = 0;
    }

    MarkBlossom(lca, u, match, father, base, & inb);
    MarkBlossom(lca, v, match, father, base, & inb);

    if (( * base)[u] != lca)
        ( * father)[u] = v;
    if (( * base)[v] != lca)
        ( * father)[v] = u;
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
/**
 *@brief Поиск увеличивающей цепи.
 *
 *@tparam T тип графа.
 *
 *@param base массив базу цветка вершин.
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
size_t FindAugmentingPath(size_t s, T graph, std::unordered_map < size_t, size_t > * match, std::unordered_map < size_t, size_t > * father, size_t V) {
    for (size_t i = 0; i < V + 1; i++) {
        ( * father)[i] = 0;
    }
    size_t qh = 0, qt = 0;
    std::unordered_map < size_t, bool > inq;
    for (size_t i = 0; i < V + 1; i++) {
        inq[i] = 0;
    }
    std::unordered_map < size_t, size_t > base;
    for (size_t i = 0; i < V + 1; i++) {
        base[i] = i;
    }
    std::unordered_map < size_t, size_t > q;
    for (size_t i = 0; i < V + 1; i++) {
        q[i] = 0;
    }

    inq[q[qh = qt = 0] = s] = true;

    while (qh <= qt) {
        size_t u = q[qh++];
        if (graph.HasVertex(u)) {
            for (auto elem: graph.Edges(u)) {
                size_t v = elem;
                if (base[u] != base[v] && ( * match)[u] != v) {
                    if ((v == s) || (( * match)[v] != 0 && ( * father)[( * match)[v]] != 0))
                        BlossomContraction(s, u, v, match, father, & base, & q, & inq, & qt, V);
                    else if (( * father)[v] == 0) {
                        ( * father)[v] = u;
                        if (( * match)[v] == 0)
                            return v;
                        else if (!inq[( * match)[v]]) {
                            inq[q[++qt] = ( * match)[v]] = true;
                        }
                    }
                }
            }
        }
    }
    return 0;
}

/**
 *@brief Увелечение пути вдоль цепи.
 *
 *@tparam T тип графа.
 *
 *@param father массив хранящий предков нечетных вершин.
 *@param match массив хранящий паросочетания.
 */
size_t AugmentPath(size_t t, std::unordered_map < size_t, size_t > * match, std::unordered_map < size_t, size_t > * father) {
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
/**
 *@brief Алгоритм Эдондса.
 *
 *@tparam T тип графа.
 *
 *@param match массив хранящий паросочетания.
 *@param match_counts количество ребер в наибольшем парасочетании.
 */
size_t EdmondsBlossomAlgorithm(T graph, size_t V, std::unordered_map < size_t, size_t > * match) {
    size_t match_counts = 0;
    std::unordered_map < size_t, size_t > father;
    for (size_t i = 0; i < V + 1; i++) {
        father[i] = 0;
    }

    for (size_t u = 0; u < V; u++) {
        if (( * match)[u] == 0)
            match_counts += AugmentPath(FindAugmentingPath(u, graph, match, & father, V), match, & father);
    }
    return match_counts;
}

template < class T >
/**
 *@brief Функция поиска наибольшего паросочетания.
 *
 *@tparam T тип графа.
 *
 *@param result вектор, в котором хранится ответ.
 */
void FindMaxMatching(T graph, std::vector < std::pair < size_t, size_t >> * result) {
    size_t V = graph.NumVertices();
    std::unordered_map < size_t, size_t > match;
    for (size_t i = 0; i < V + 1; i++) {
        match[i] = 0;
    }
    size_t res = EdmondsBlossomAlgorithm(graph, V, & match);
    if (!res)
        return;
    for (size_t i = 0; i < V; i++) {
        if (i < match[i]) {
            ( * result).push_back({i,match[i]});
        }
    }
}
} // namespace graph
#endif // INCLUDE_FIND_MAX_MATCHING_HPP_