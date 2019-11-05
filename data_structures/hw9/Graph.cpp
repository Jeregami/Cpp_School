#include "Graph.hpp"
#include <stack>

using namespace std;

void Graph::addVertex(string name) {
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == name) {
      return;
    }
  }
  vertex *v = new vertex();
  v->name = name;
  vertices.push_back(v);
}

void Graph::addEdge(string v1, string v2, int num) {
  for (unsigned int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == v1) {
      for (unsigned int j = 0; j < vertices.size(); j++) {
        if (vertices[j]->name == v2) {
          adjVertex adj1;
          adj1.v = vertices[j];
          adj1.weight = num;
          vertices[i]->adj.push_back(adj1);
          adjVertex adj2;
          adj2.v = vertices[i];
          adj2.weight = num;
          vertices[j]->adj.push_back(adj2);
        }
      }
    }
  }
}

void depthFirstTraversalHelper(string sourceVertex, vector <vertex*> vertices) {
  vertex *n = new vertex;
  for (unsigned int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == sourceVertex) {
      n = vertices[i];
    }
  }
  cout << n->name << " --> ";
  n->visited = true;
  for (unsigned int i = 0; i < n->adj.size(); i++ ) {
    if (n->adj[i].v->visited == false) {
      depthFirstTraversalHelper(n->adj[i].v->name, vertices);
    }
  }
}

void Graph::depthFirstTraversal(string sourceVertex) {
  depthFirstTraversalHelper(sourceVertex, vertices);
  cout << "Done";
}

vertex* Graph::DijkstraAlgorithm(string start, string end) {
  vertex *startVertex = new vertex;
  for (unsigned int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == start) {
      startVertex = vertices[i];
    }
  }
  vertex *endVertex = new vertex;
  for (unsigned int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == end) {
      endVertex = vertices[i];
    }
  }
  startVertex->visited = true;
  vector <vertex*> solved;
  solved.push_back(startVertex);
  vertex* minDistance;
  while (!endVertex->visited) {
    minDistance = NULL;
    for (unsigned int i = 0; i < solved.size(); i++) {
      for (unsigned int j = 0; j < solved[i]->adj.size(); j++) {
        if (!solved[i]->adj[j].v->visited) {
          if (solved[i]->adj[j].v->distance == 0) {
            solved[i]->adj[j].v->distance = solved[i]->distance + solved[i]->adj[j].weight;
            solved[i]->adj[j].v->pred = solved[i];
          }
          else {
            if (solved[i]->adj[j].v->distance > solved[i]->distance + solved[i]->adj[j].weight) {
              solved[i]->adj[j].v->distance = solved[i]->distance + solved[i]->adj[j].weight;
              solved[i]->adj[j].v->pred = solved[i];
            }
          }
          if (minDistance == NULL) {
            minDistance = solved[i]->adj[j].v;
          }
          else {
            if (solved[i]->adj[j].v == minDistance) {
              if (solved[i]->adj[j].v->distance < minDistance->distance) {
                minDistance = solved[i]->adj[j].v;
              }
            }
            else {
              if (solved[i]->adj[j].v->distance < minDistance->distance) {
                minDistance = solved[i]->adj[j].v;
              }
            }
          }
        }
      }
    }
    minDistance->visited = true;
    solved.push_back(minDistance);
  }
  return endVertex;
}

void markAllUnvisited(vector <vertex*> vertices) {
  for (unsigned int i = 0; i < vertices.size(); i++) {
    vertices[i]->visited = false;
  }
}

void Graph::shortestpath(string s1, string s2) {
  markAllUnvisited(vertices);
  vertex *currentVertex = DijkstraAlgorithm(s1, s2);
  vector <vertex*> path;
  while (currentVertex != NULL) {
    path.insert(path.begin(), currentVertex);
    currentVertex = currentVertex->pred;
  }
  for (unsigned int i = 0; i < path.size(); i++) {
    cout << path[i]->name << " ";
  }
  cout << endl;
}

int main() {
  Graph graph;
  graph.addVertex("A");
  graph.addVertex("B");
  graph.addVertex("C");
  graph.addVertex("D");
  graph.addVertex("F");
  graph.addEdge("A", "B", 5);
  graph.addEdge("A", "C", 10);
  graph.addEdge("A", "F", 30);
  graph.addEdge("B", "D", 10);
  graph.addEdge("B", "F", 15);
  graph.addEdge("C", "D", 10);
  vertex* shortestpath = graph.DijkstraAlgorithm("A", "F");
  cout << shortestpath->distance << endl;
  graph.shortestpath("A", "F");
}
