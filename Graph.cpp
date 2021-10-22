#include <iostream>
#include <vector>

using std::vector;
using std::cout;
class Node
{
public:
    vector<int> neighbours;
    int val = 0;
};
class Graph
{
public:


    vector<Node> make_graph(vector<vector<int>> vectors, size_t n_nodes)
    {
        vector <Node> nodes(n_nodes);

        for(vector<int> &a : vectors)
        {
            nodes[a[0] - 1].neighbours.push_back(a[1] - 1);
            nodes[a[1] - 1].neighbours.push_back(a[0] - 1);
        }

        return nodes;
    }

};


int main()
{
    Graph a;
    vector <vector<int>> nodes = {{3,4}, {1,2}, {1,2}, {1,3}};
    vector<Node> vecs= a.make_graph(nodes,4);
    for (int i = 0 ; i<vecs.size();i++)
    {
        cout<<i + 1<<':';
        for(int &t:vecs[i].neighbours)
        {
            cout<<t + 1<<' ';
        }

            cout<<'\n';

    }
    return 0;
}
