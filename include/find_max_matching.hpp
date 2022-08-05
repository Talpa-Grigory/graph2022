/**
 * @file find_max_matching.hpp
 * @author Talpa Grigory
 *
 * Реализация метода поиска наибольшего паросочетания.
 */
#ifndef INCLUDE_FIND_MAX_MATCHING_HPP_
#define INCLUDE_FIND_MAX_MATCHING_HPP_
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <utility>
#include <unordered_set>
#include <cstring>
#include "graph.hpp"
#define M 500  // max number of vertices
size_t V, qh = 0, qt = 0;
int match[M], father[M];
size_t q[M], base[M];
bool inq[M], inb[M];

namespace graph {

/**
* @brief Поиск наименьшего предка.
*
* @param father массив хранящий предков нечетных вершин.
* @param match массив хранящий паросочетания.
*/  
size_t LCA(size_t root, size_t u, size_t v) {
        static bool inp[M];
		std::cout << "27" << std::endl;
        memset(inp, 0, sizeof(inp));
        while (1) {
			std::cout << "28" << std::endl;
            inp[u = base[u]] = true;
            if (u == root){
				std::cout << "29" << std::endl;
                break;
			}
			std::cout << "30" << std::endl;
            u = static_cast<size_t>(father[match[u]]);
        }
		std::cout << "30.5" << std::endl;
        while (1) {
			std::cout << "31" << std::endl;
			v = base[v];
            if (inp[v]){
				std::cout << "32" << std::endl;
                return v;
			}
            else {
				std::cout << "33" << std::endl;
                v = static_cast<size_t>(father[match[v]]);
			}
        }
    }
/**
* @brief Проход от вершины до базы.
*
*
* @param base массив базу цветка вершин.
* @param father массив хранящий предков нечетных вершин.
* @param match массив хранящий паросочетания.
* @param lca наименьший общий предок
*/ 
    void MarkBlossom(size_t lca, size_t u) {
		std::cout << "23" << std::endl;
        while (base[u] != lca) {
			std::cout << "24" << std::endl;
            size_t v = static_cast<size_t>(match[u]);
            inb[base[u]] = inb[base[v]] = true;
            u = static_cast<size_t>(father[v]);
			std::cout << "25" << std::endl;
            if (base[u] != lca) {
				std::cout << "26" << std::endl;
                father[u] = static_cast<int>(v);
			}
        }
    }
/**
 * @brief Сжатие цветка.
 *
 *
 * @param base массив базу цветка вершин.
 * @param father массив хранящий предков нечетных вершин.
 * @param lca наименьший общий предок
 */    
    void BlossomContraction(size_t s, size_t u, size_t v) {
        std::cout << "17" << std::endl;
		size_t lca = LCA(s, u, v);
        memset(inb, 0, sizeof(inb));
        MarkBlossom(lca, u);
        MarkBlossom(lca, v);
        if (base[u] != lca){
			std::cout << "18" << std::endl;
            father[u] = static_cast<int>(v);
		}
        if (base[v] != lca){
			std::cout << "19" << std::endl;
            father[v] = static_cast<int>(u);
		}
        for (size_t i = 0; i < V; i++){
		std::cout << "20" << std::endl;
            if (inb[base[i]]) {
				std::cout << "21" << std::endl;
                base[i] = lca;
                if (!inq[i]){
					std::cout << "22" << std::endl;
                    inq[q[++qt] = i] = true;
				}
            }
		}
    }
template<class T>
/**
 * @brief Поиск увеличивающей цепи.
 *
 * @tparam T тип графа.
 *
 * @param base массив базу цветка вершин.
 * @param father массив хранящий предков нечетных вершин.
 * @param match массив хранящий паросочетания.
 */

int FindAugmentingPath(size_t s, T graph) {
    std::cout << "7" << std::endl;
	memset(inq, 0, sizeof(inq));
    memset(father, -1, sizeof(father));
    for (size_t i = 0; i < V; i++)
        base[i] = i;
    inq[q[qh = qt = 0] = s] = true;
	std::cout << "8" << std::endl;
	std::cout << "father: ";
	for(int i = 0; i < V + 1; i++){
		std::cout << father[i] << " ";
	}
	std::cout << "" << std::endl;
    while (qh <= qt) {
		std::cout << "9" << std::endl;
        size_t u = q[qh++];
		std::cout << "u: " << u << std::endl;
        if (graph.HasVertex(u)) {
			std::cout << "10" << std::endl;
			std::cout << "u: " << u << std::endl;
        for (auto elem : graph.Edges(u)) {
			std::cout << "11" << std::endl;
            size_t v = elem;
			std::cout << "v: " << v << std::endl;
            if (base[u] != base[v] && static_cast<size_t>(match[u]) != v) {
				std::cout << "12" << std::endl;
				std::cout << "v: " << v << std::endl;
				std::cout << "u: " << u << std::endl;
				std::cout << "father: ";
				for(int i = 0; i < V + 1; i++){
					std::cout << father[i] << " ";
				}
				std::cout << "" << std::endl;
                if ((v == s) || (match[v] != -1 && father[match[v]] != -1)) {
					std::cout << "13" << std::endl;
                        BlossomContraction(s, u, v);
                    } else if (father[v] == -1) {
						std::cout << "14" << std::endl;
                        father[v] = static_cast<int>(u);
                        if (match[v] == -1){
							std::cout << "15" << std::endl;
                            return static_cast<int>(v);
						}
                        else if (!inq[match[v]]){
							std::cout << "16" << std::endl;
                            inq[q[++qt] = static_cast<size_t>(match[v])] = true;
						}
                    }
            }
            }
            }
        }
        return -1;
    }
/**
 * @brief Увелечение пути вдоль цепи.
 *
 * @tparam T тип графа.
 *
 * @param father массив хранящий предков нечетных вершин.
 * @param match массив хранящий паросочетания.
 */
size_t AugmentPath(int t) {
    int u = t;
    size_t  v, w;
	std::cout << "5" << std::endl;
    while (u != -1) {
		std::cout << "6" << std::endl;
        v = static_cast<size_t>(father[u]);
        w = static_cast<size_t>(match[v]);
        match[v] = u;
        match[u] = static_cast<int>(v);
        u = static_cast<int>(w);
    }
    return t != -1;
}
    template<class T>
/**
 * @brief Алгоритм Эдондса.
 *
 * @tparam T тип графа.
 *
 * @param match массив хранящий паросочетания.
 * @param match_counts количество ребер в наибольшем парасочетании.
 */
size_t EdmondsBlossomAlgorithm(T graph) {
    size_t match_counts = 0;
    memset(match, -1, sizeof(match));
	std::cout << "2" << std::endl;
    for (size_t u = 0; u < V; u++) {
		std::cout << "3" << std::endl;
        if (match[u] == -1) {
			std::cout << "4" << std::endl;
            match_counts += AugmentPath(FindAugmentingPath(u, graph));
		}
    }
    return match_counts;
}
template<class T>
    /**
 * @brief Функция поиска наибольшего паросочетания.
 *
 * @tparam T тип графа.
 *
 * @param result вектор, в котором хранится ответ.
 */
void FindMaxMatching(T graph, std::vector<std::pair<size_t, size_t>>* result) {
    V = graph.NumVertices();
	std::cout << "1" << std::endl;
    size_t res = EdmondsBlossomAlgorithm(graph);
	std::cout << "35" << std::endl;
    if (!res){
		std::cout << "36" << std::endl;
        return;
	}
    for (int i = 0; i < static_cast<int>(V); i++) {
		std::cout << "37" << std::endl;
            if (i < match[i]) {
				std::cout << "38" << std::endl;
(*result).push_back({static_cast<size_t>(i), static_cast<size_t>(match[i])});
            }
    }
	std::cout << "39" << std::endl;
}

}  // namespace graph
#endif  // INCLUDE_FIND_MAX_MATCHING_HPP_

