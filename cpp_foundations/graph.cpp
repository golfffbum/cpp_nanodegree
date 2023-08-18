#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <set>


using namespace std;



bool validPath(int n, vector<vector<int>> edges, int source, int destination) {
    vector<int> graph[n];

    for(int i=0; i<edges.size(); i++)
    {
        graph[edges[i][0]].push_back(edges[i][1]);
        graph[edges[i][1]].push_back(edges[i][0]);

    }

    for(int i=0; i<n; i++)
    {
        string l;

        for ( int a : graph[i])
        {
            l = l + to_string(a);
        }
        cout << i << ": " << l << ", ";
    }

    queue<int> line;
    line.push(source);

    int iterator = 0;
    set<int> visited; //set use 
    while(!line.empty())
    {
        int curr = line.front();
        line.pop();
        
        if (!(visited.find(curr) != visited.end()))
        {
            visited.insert(curr);

            cout << "\n" << "curr: " + to_string(curr) << ". ";
            // std::cout << line.front() << " ";

            if (curr == destination)
            {
                cout << "\nPath found";
                return true;
            }

            for (int i: graph[curr])
            {
                line.push(i);
                cout << to_string(i);
            }

            if (iterator != 0 && curr == source)
            {
                cout<< "max";
                return false;
            }
        }


    }

    cout << "No Path found";
    return false;
}

int main()
{
    vector<vector<int>> test = {{0,1},{1,2}, {2,0}};
    validPath(3, test, 0, 2);

    vector<vector<int>> test2 = {{0,1},{0,2},{3,5},{5,4},{4,3}};
    validPath(6, test2, 0, 5);

    vector<vector<int>> test3 = {{4,3},{1,4},{4,8},{1,7},{6,4},{4,2},{7,4},{4,0},{0,9},{5,4}};
    validPath(10, test3, 5, 9);

}