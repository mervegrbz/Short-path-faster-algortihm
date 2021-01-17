#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
typedef pair<pair<int, int>, bool> Edge;
const int MAX_N = 300;
long long INF = numeric_limits<long long>::max() / 4;
void trace(int j);
int t, n, m;
vector<vector<Edge>> adjList;

long long dis[MAX_N];
int pre[MAX_N], len[MAX_N];
bool in_queue[MAX_N];
bool visited[MAX_N], on_stack[MAX_N];
bool spfa_early_terminate();
int main(int argc, char *argv[])
{
    ifstream input(argv[1]);
    ofstream output(argv[2]);

    int number;
    input >> number;
    for (int i = 0; i < number; i++)
    {
        int numOfVert;
        input >> numOfVert;
        n = numOfVert * 2;
        adjList = vector<vector<Edge>>(numOfVert * 2);
        for (int j = 0; j < numOfVert * 2; j++)

            adjList[j] = (vector<Edge>(numOfVert * 2));

        for (int j = 0; j < numOfVert; j++)
        {

            for (int k = 0; k < numOfVert; k++)
            {

                int cap;
                input >> cap;
                adjList[j][k + numOfVert] = (Edge(make_pair(k + numOfVert, -cap), true));
                adjList[k + numOfVert][j] = (Edge(make_pair(j, +cap), false));
            }
        }
        for (int m = 0; m < numOfVert; m++)
        {
            adjList[m][m + numOfVert].second = false;
            adjList[m + numOfVert][m].second =true;
        }
        while (spfa_early_terminate())
        {
        }
        spfa_early_terminate();

        int sum = 0;
        for (int i = 0; i < numOfVert; i++)
        {
            for (int m = 0; m < numOfVert; m++)
            {
                if (adjList[i+numOfVert][m].second)
                {

                    sum += adjList[i+numOfVert][m].first.second;
                }
            }
        }
        output << sum << endl;
    }

    return 0;
}

bool detect_cycle()
{
    vector<int> vec;
    fill(on_stack, on_stack + n, false);
    fill(visited, visited + n, false);
    for (int i = 0; i < n; ++i)
        if (!visited[i])
        {

            for (int j = i; j != -1; j = pre[j])
                if (!visited[j])
                {
                    visited[j] = true;
                    vec.push_back(j);
                    on_stack[j] = true;
                }
                else
                {
                    if (on_stack[j])
                    {

                        trace(j);
                        return true;
                    }
                    break;
                }
            for (int j : vec)
            {
                on_stack[j] = false;
            }
            vec.clear();
        }
    return false;
}
bool spfa_early_terminate()
{
    fill(dis, dis + n, 0);
    fill(pre, pre + n, -1);
    fill(in_queue, in_queue + n, true);
    queue<int> queue;
    for (int i = 0; i < n; ++i)
    {
        queue.push(i);
    }
    int iter = 0;
    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop();
        in_queue[u] = false;
        for (Edge edge : adjList[u])
        {
            if (edge.second)
            {
                if (dis[u] + edge.first.second < dis[edge.first.first])
                {
                    pre[edge.first.first] = u;
                    dis[edge.first.first] = dis[u] + edge.first.second;
                    if (++iter == n)
                    {
                        iter = 0;
                        if (detect_cycle())
                        {
                            return true;
                        }
                    }
                    if (!in_queue[edge.first.first])
                    {
                        queue.push(edge.first.first);
                        in_queue[edge.first.first] = true;
                    }
                }
            }
        }
    }
    if (detect_cycle())
        return true;
    return false;
}
void trace(int v)
{
    stack<int> stacks;
    vector<bool> control(n, false);
    vector<int> cyclem;

    while (!control[v])
    {
        stacks.push(v);
        control[v] = true;
        v = pre[v];
    }
    cyclem.push_back(v);

    while (stacks.top() != v)
    {
        cyclem.push_back(stacks.top());
        stacks.pop();
    }
    cyclem.push_back(v);


    for (int i = 0; i <cyclem.size()-1; i++)
    {
        int from = cyclem[i];
        int to = cyclem[i + 1];
        adjList[from][to].second = false;
        adjList[to][from].second = true;
    }


   
}