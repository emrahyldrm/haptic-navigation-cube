#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <string>

using namespace std;
 
#define REFERENCE_POINT_NUMBER      11

class neighbor;
class Shortestpath;

typedef enum 
{A, B, C, D, E, F, G, H, I, J, K}
Points;
 
typedef int vertex_t;
typedef double weight_t;
typedef vector<vector<neighbor> > adjacency_list_t;
 
const weight_t max_weight = numeric_limits<double>::infinity();


class neighbor {
public:
    vertex_t target;
    weight_t weight;
    neighbor(vertex_t arg_target, weight_t arg_weight)
        : target(arg_target), weight(arg_weight) { }

    friend ostream& operator <<(ostream &out, neighbor nb);
};

/*
ostream& operator <<(ostream &out, neighbor nb)
{
    out << nb.target << " " << nb.weight << endl; 
    return out;
}
*/

class ShortestPath
{
public:
	vector<vertex_t> dijkstra(string filename, vertex_t source_out, vertex_t dest_out);


private:
	void DijkstraComputePaths(vertex_t source, const adjacency_list_t &adjacency_list,
	                          vector<weight_t> &min_distance, vector<vertex_t> &previous);

	vector<vertex_t> DijkstraGetShortestPathTo(vertex_t vertex, const vector<vertex_t> &previous);
	void split(const string& s, char delim,vector<string>& v);
	void readFile(string filename, vector< vector<neighbor> >& graph);
	void printPath(vector<vertex_t> path);

};



#endif