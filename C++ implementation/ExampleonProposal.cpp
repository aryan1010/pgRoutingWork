#include<bits/stdc++.h>
using namespace std;
// Total number of vertices in graph
#define V 5
// For printing the shortest path
void shortest_path(int dist[], int n)
{
   cout<<"Vertex "<<"\t"<<"Distance from Source\n";
   for (int i = 1; i <= V; i++)
   cout<<" \t\t \n"<< i<<" \t\t "<<dist[i-1];
}
// For calculating minimum distance
int minDist(int dist[], bool Set[])
{
   int min = INT_MAX, min_index;
   for (int i = 0; i < V; i++)
   if (Set[i] == false && dist[i] <= min)
   min = dist[i], min_index = i;
   return min_index;
}
// Calculate shortest paths from source to all other vertices
void Dijkstra(int g[V][V], int src, int D)
{
    src--;
   int dist[V];
   bool Set[V];
   for (int i = 0; i < V; i++)
   dist[i] = INT_MAX, Set[i] = false;
   dist[src] = 0;
   for (int c = 0; c < V- 1; c++)
   {
      int u = minDist(dist, Set);
      if(dist[u]>=D)      //breaking the code here
      break; 
      Set[u] = true;
      for (int j = 0; j < V; j++)
    if (!Set[j] && g[u][j] && dist[u] != INT_MAX && dist[u]+ g[u][j] < dist[j])
    {
    dist[j] = dist[u] + g[u][j];
      }
   }
   shortest_path(dist, V);
}
// Driver Program
int main()
{
      ios_base::sync_with_stdio(false);
      cin.tie(NULL);
      int G[V][V] = { 
      { 0, 3, 1, 0, 0},
      { 3, 0, 7, 5, 1},
      { 1, 7, 0, 2, 0},
      { 0, 5, 2, 0, 7},
      { 0, 1, 0, 7, 0},};
      Dijkstra(G, 1 ,5);  
      return 0;
}