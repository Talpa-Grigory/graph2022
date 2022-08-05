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

namespace graph {
	
size_t LCA(size_t root, size_t u, size_t v,std::vector<size_t>* match, std::vector<size_t>* father,std::vector<size_t>* base, size_t V) {
        static std::vector<bool> inp(V + 1);
		std::cout << "27" << std::endl;
        while (1) {
			std::cout << "28" << std::endl;
            inp[u = (*base)[u]] = true;
            if (u == root){
				std::cout << "29" << std::endl;
                break;
			}
			std::cout << "30" << std::endl;
            u = (*father)[(*match)[u]];
        }
		std::cout << "30.5" << std::endl;
        while (1) {
			std::cout << "31" << std::endl;
			v = (*base)[v];
            if (inp[(*base)[v]]){
				std::cout << "32" << std::endl;
                return v;
			}
            else {
				std::cout << "33" << std::endl;
                v = (*father)[(*match)[v]];
			}
        }
}
	
void MarkBlossom(size_t lca, size_t u, std::vector<size_t>* match, std::vector<size_t>* father,std::vector<size_t>* base,std::vector<bool>* inb) {
        std::cout << "23" << std::endl;
		while ((*base)[u] != lca) {
			std::cout << "24" << std::endl;
            size_t v = (*match)[u];
            (*inb)[(*base)[u]] = (*inb)[(*base)[v]] = true;
            u = (*father)[v];
			std::cout << "25" << std::endl;
            if ((*base)[u] != lca){
				std::cout << "26" << std::endl;
                (*father)[u] = v;
			}
        }
}
	
void BlossomContraction(size_t s, size_t u, size_t v,std::vector<size_t>* match,std::vector<size_t>* father,std::vector<size_t>* base,std::vector<size_t>* q,std::vector<bool>* inq, size_t* qt, size_t V) {
        std::cout << "17" << std::endl;
		size_t lca = LCA(s, u, v,match,father,base,V);
        std::vector<bool> inb(V + 1);
        MarkBlossom(lca, u,match,father,base,&inb);
        MarkBlossom(lca, v,match,father,base,&inb);
        if ((*base)[u] != lca){
			std::cout << "18" << std::endl;
            (*father)[u] = v;
		}
        if ((*base)[v] != lca){
			std::cout << "19" << std::endl;
            (*father)[v] = u;
		}
        for (size_t i = 0; i < V; i++){	
			std::cout << "20" << std::endl;		
            if (inb[(*base)[i]]) {
				std::cout << "21" << std::endl;
                (*base)[i] = lca;
                if (!(*inq)[i]){
					std::cout << "22" << std::endl;
                    (*inq)[(*q)[++(*qt)] = i] = true;
				}
            }
		}
    }

template<class T>

size_t FindAugmentingPath(size_t s, T graph,std::vector<size_t>* match,std::vector<size_t>* father, size_t V) {
	std::cout << "7" << std::endl;
    size_t qh = 0, qt = 0;
	std::vector<bool> inq(V + 1);
	std::vector<size_t> base(V + 1);
    for (size_t i = 0; i < V; i++)
        base[i] = i;
	std::vector<size_t> q(V + 1);
    inq[q[qh = qt = 0] = s] = true;
	std::cout << "8" << std::endl;
	std::cout << "father: ";
				for(size_t i = 0; i < V + 1; i++){
					std::cout << (*father)[i] << " ";
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
            if (base[u] != base[v] && (*match)[u] != v) {
				std::cout << "12" << std::endl;
				std::cout << "v: " << v << std::endl;
				std::cout << "u: " << u << std::endl;
				std::cout << "father: ";
				for(size_t i = 0; i < V + 1; i++){
					std::cout << (*father)[i] << " ";
				}
				std::cout << "" << std::endl;
                if ((v == s) || ((*match)[v] != 0 && (*father)[(*match)[v]] != 0)) {
					std::cout << "13" << std::endl;
                        BlossomContraction(s, u, v,match,father,&base,&q,&inq,&qt,V);
                    } else if ((*father)[v] == 0) {
						std::cout << "14" << std::endl;
                        (*father)[v] = u;
                        if ((*match)[v] == 0){
							std::cout << "15" << std::endl;
                            return v;
						}
                        else if (!inq[(*match)[v]]){
							std::cout << "16" << std::endl;
                            inq[q[++qt] = (*match)[v]] = true;
						}
                    }
            }
            }
            }
        }
        return 0;
    }

size_t AugmentPath(size_t t,std::vector<size_t>* match,std::vector<size_t>* father) {
    size_t u = t;
    size_t  v, w;
	std::cout << "5" << std::endl;
    while (u != 0) {
		std::cout << "6" << std::endl;
        v = (*father)[u];
        w = (*match)[v];
        (*match)[v] = u;
        (*match)[u] = v;
        u = w;
    }
    return t != 0;
}

template<class T>
size_t EdmondsBlossomAlgorithm(T graph,std::vector<size_t>* match, size_t V) {
    size_t match_counts = 0;
    std::vector<size_t> father(V + 1);
	std::cout << "2" << std::endl;
	std::cout << "father: ";
	for(size_t i = 0; i < V + 1; i++){
		std::cout << father[i] << " ";
	}
	std::cout << "" << std::endl;
    for (size_t u = 0; u < V; u++) {
		std::cout << "3" << std::endl;
        if ((*match)[u] == 0){
			std::cout << "4" << std::endl;
            match_counts += AugmentPath(FindAugmentingPath(u, graph, match, &father,V), match, &father);
		}
    }
    return match_counts;
}

template<class T>
void FindMaxMatching(T graph, std::vector<std::pair<size_t, size_t>>* result) {
    size_t V = graph.NumVertices();
	std::vector<size_t> match(V + 1);
	std::cout << "1" << std::endl;
    size_t res = EdmondsBlossomAlgorithm(graph,&match,V);
	std::cout << "35" << std::endl;
    if (!res){
        return;
		std::cout << "36" << std::endl;
	}
    for (size_t i = 0; i < V; i++){
		std::cout << "37" << std::endl;
        if (i < match[i]){
			std::cout << "38" << std::endl;
		(*result).push_back({i, match[i]});
        }
    }
	std::cout << "39" << std::endl;
}

} // namespace graph
#endif  // INCLUDE_FIND_MAX_MATCHING_HPP_