#include<iostream>
#include<set>
#include<list>
#include<algorithm>
using namespace std;

typedef struct nodes {
   int dest;
   int cost;
}node;

class Graph {
   int n;
   list<node> *adjList;
   private:
      void showList(int src, list<node> lt) {
         list<node> :: iterator i;
         node tempNode;

         for(i = lt.begin(); i != lt.end(); i++) {
            tempNode = *i;
            cout << "(" << src << ")---("<<tempNode.dest << "|"<<tempNode.cost<<") ";
         }
         cout << endl;
      }
   public:
      Graph() {
         n = 0;
      }

      Graph(int nodeCount) {
         n = nodeCount;
         adjList = new list<node>[n];
      }

      void addEdge(int source, int dest, int cost) {
         node newNode;
         newNode.dest = dest;
         newNode.cost = cost;
         adjList[source].push_back(newNode);
      }

      void displayEdges() {
         for(int i = 0; i<n; i++) {
            list<node> tempList = adjList[i];
            showList(i, tempList);
         }
      }

      friend void dijkstra(Graph g, int *dist, int *prev, int start);
};

void dijkstra(Graph g, int *dist, int *prev, int start) {
   int n = g.n;

   for(int u = 0; u<n; u++) {
      dist[u] = 9999;   //set as infinity
      prev[u] = -1;    //undefined previous
   }

   dist[start] = 0;   //distance of start is 0
   set<int> S;       //create empty set S
   list<int> Q;

   for(int u = 0; u<n; u++) {
      Q.push_back(u);    //add each node into queue
   }

   while(!Q.empty()) {
      list<int> :: iterator i;
      i = min_element(Q.begin(), Q.end());
      int u = *i; //the minimum element from queue
      Q.remove(u);
      S.insert(u); //add u in the set
      list<node> :: iterator it;

      for(it = g.adjList[u].begin(); it != g.adjList[u].end();it++) {
         if((dist[u]+(it->cost)) < dist[it->dest]) { //relax (u,v)
            dist[it->dest] = (dist[u]+(it->cost));
            prev[it->dest] = u;
         }
      }
   }
}

int main() {
   int n = 5;
   Graph g(n);
   int dist[n], prev[n];
   int start = 0;


g.addEdge(5,6,1);
g.addEdge(6,5,1);
g.addEdge(10,6,1);
g.addEdge(6,7,1);
g.addEdge(7,6,1);
g.addEdge(7,11,1);
g.addEdge(11,7,1);
g.addEdge(3,7,1);
g.addEdge(7,3,1);
g.addEdge(1,3,1);
g.addEdge(3,1,1);
g.addEdge(11,16,1);
g.addEdge(16,11,1);
g.addEdge(15,10,1);
g.addEdge(16,15,1);
g.addEdge(15,16,1);
g.addEdge(17,16,1);
g.addEdge(16,17,1);
g.addEdge(11,12,1);
g.addEdge(12,17,1);
g.addEdge(7,8,1);
g.addEdge(8,7,1);
g.addEdge(8,9,1);
g.addEdge(10,11,1);
g.addEdge(8,12,1);
g.addEdge(2,4,1);
g.addEdge(4,2,1);
g.addEdge(13,14,1);
g.addEdge(14,13,1);
g.addEdge(9,8,1);


   dijkstra(g, dist, prev, start);

   for(int i = 0; i<n; i++)
      if(i != start)
         cout<<start<<" to "<<i<<", Cost: "<<dist[i]<<" Previous: "<<prev[i]<<endl;
    return 0;
}