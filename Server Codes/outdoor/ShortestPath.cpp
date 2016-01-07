#include "ShortestPath.h"
 
 
void ShortestPath::DijkstraComputePaths(vertex_t source, const adjacency_list_t &adjacency_list,
                          vector<weight_t> &min_distance, vector<vertex_t> &previous)
{
    int n = adjacency_list.size();
    min_distance.clear();
    min_distance.resize(n, max_weight);
    min_distance[source] = 0;
    previous.clear();
    previous.resize(n, -1);
    set<pair<weight_t, vertex_t> > vertex_queue;
    vertex_queue.insert(make_pair(min_distance[source], source));
 
    while (!vertex_queue.empty()) 
    {
        weight_t dist = vertex_queue.begin()->first;
        vertex_t u = vertex_queue.begin()->second;
        vertex_queue.erase(vertex_queue.begin());
 
        
        const vector<neighbor> &neighbors = adjacency_list[u];
        for (vector<neighbor>::const_iterator neighbor_iter = neighbors.begin();
             neighbor_iter != neighbors.end();
             neighbor_iter++)
        {
            vertex_t v = neighbor_iter->target;
            weight_t weight = neighbor_iter->weight;
            weight_t distance_through_u = dist + weight;
    	    if (distance_through_u < min_distance[v]) {
    	        vertex_queue.erase(std::make_pair(min_distance[v], v));
     
    	        min_distance[v] = distance_through_u;
    	        previous[v] = u;
    	        vertex_queue.insert(std::make_pair(min_distance[v], v));
    	    }
 
        }
    }
}
 
 
vector<vertex_t> ShortestPath::DijkstraGetShortestPathTo(vertex_t vertex, const vector<vertex_t> &previous)
{
/*
    std::list<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
*/
    vector<vertex_t> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_back(vertex);
    return path;
}





void ShortestPath::split(const string& s, char delim,vector<string>& v) 
{
    int i = 0;
    int pos = s.find(delim);
    v.clear();
    while (pos != string::npos) {
      v.push_back(s.substr(i, pos-i));
      i = ++pos;
      pos = s.find(delim, pos);

      if (pos == string::npos)
         v.push_back(s.substr(i, s.length()));
    }
}


void ShortestPath::readFile(string filename, vector< vector<neighbor> >& graph)
{
    ifstream file;
    string temp;
    file.open(filename.c_str());
    graph.clear();
    
    while(!file.eof())
    {
        vector<string> v;

        getline(file, temp);
        split(temp, ':', v);
        graph.push_back(vector<neighbor>());

        int listIndex = (char)v[0][0] - 'A';
        
        //cout << "index " << listIndex << " " << v[0][0] << endl;

        for (int i = 1; i < v.size(); i+=2)
        {
            neighbor tempNB(v[i][0]-'A', atof(v[i+1].c_str()));
            graph[listIndex].push_back(tempNB);
            //cout << tempNB;
        }
        //cout << endl;
    }
    cout << endl << endl << graph.size()<< endl;

}
void ShortestPath::printPath(vector<vertex_t> path)
{
    cout << "Path : ";
    for (int i = 0; i < path.size(); ++i)
    {
        cout << path[i] << "\t";
    }
    cout << endl;
    cout << "Path : ";
    for (int i = 0; i < path.size(); ++i)
    {
        cout << (char)(path[i] +'A') << "\t";
    }
    cout << endl;
}

vector<vertex_t> ShortestPath::dijkstra(string filename, vertex_t source_out, vertex_t dest_out)
{
     // remember to insert edges both ways for an undirected graph
    adjacency_list_t adjacency_list(REFERENCE_POINT_NUMBER);

    readFile(filename.c_str(), adjacency_list);
    int SOURCE_REVERSE, SOURCE = source_out;
    int DEST_REVERSE, DEST = dest_out;
    SOURCE_REVERSE = DEST;
    DEST_REVERSE = SOURCE;
 
    vector<weight_t> min_distance;
    vector<vertex_t> previous;
    vector<weight_t> min_distance_reverse;
    vector<vertex_t> previous_reverse;

    int dist;
    vector<vertex_t> realpath;

    DijkstraComputePaths(SOURCE, adjacency_list, min_distance, previous);
    DijkstraComputePaths(SOURCE_REVERSE, adjacency_list, min_distance_reverse, previous_reverse);
    cout << "min :" << min_distance[DEST] << endl;
    cout << "min_reverse : " << min_distance_reverse[DEST_REVERSE] << endl;

    vector<vertex_t> path;
    if(min_distance[DEST] > min_distance_reverse[DEST_REVERSE])
    {
        dist = min_distance_reverse[DEST_REVERSE];
        path = DijkstraGetShortestPathTo(DEST_REVERSE, previous_reverse);       
    }
    else
    {
        dist = min_distance[DEST];
        path = DijkstraGetShortestPathTo(DEST, previous);   

        for (int i = 0; i < path.size()/2; ++i)
        {
            vertex_t temp = path[i];
            path[i] = path[path.size() - 1 - i];
            path[path.size() - 1 - i] = temp;
        }
    }

    cout << "Distance : " << dist << endl;
    //printPath(path);
    return path;

}

/*

int main()
{
    ShortestPath path;

    path.dijkstra(A, R);
}

*/