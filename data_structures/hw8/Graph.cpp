#include <queue>
#include "Graph.hpp"

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


void Graph::addEdge(string v1, string v2) {
  for (int i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == v1) {
      for (int j = 0; j < vertices.size(); j++) {
        if (vertices[j]->name == v2) {
          adjVertex adj1;
          adj1.v = vertices[j];
          vertices[i]->adj.push_back(adj1);
          adjVertex adj2;
          adj2.v = vertices[i];
          vertices[j]->adj.push_back(adj2);
        }
      }
    }
  }
}


void Graph::displayEdges() {
int numVertices = vertices.size();
int numAdjacentVertices;
  for (int i = 0; i < numVertices; i++) {
    if (vertices[i]->adj.size() > 0) {
      cout << vertices[i]->name << " --> ";
      numAdjacentVertices = vertices[i]->adj.size();
      for (int j = 0; j < numAdjacentVertices; j++) {
        cout << vertices[i]->adj[j].v->name << " ";
      }
      cout << endl;
    }
  }
}


void Graph::breadthFirstTraverse(string sourceVertex) {
  vertex *vStart = new vertex();
  int numVertices = vertices.size();
  int numAdjacentVertices;
  for (int i = 0; i < numVertices; i++) {
    if (vertices[i]->name == sourceVertex) {
      vStart = vertices[i];
    }
  }
  cout << "Starting vertex (root): " << vStart->name << "-> ";
  vStart->visited = true;
  queue <vertex*> queue;
  queue.push(vStart);
  vertex *t;
  while (!queue.empty()) {
    t = queue.front();
    queue.pop();
    numAdjacentVertices = t->adj.size();
    for (int i = 0; i < numAdjacentVertices; i++) {
      if (t->adj[i].v->visited == false) {
        t->adj[i].v->distance = t->distance + 1;
        cout << t->adj[i].v ->name << "(" << t->adj[i].v->distance << ")" << " ";
        t->adj[i].v->visited = true;
        queue.push(t->adj[i].v);
      }
    }
  }
}


int Graph::getConnectedComponents() {
  int numConnected = 0;
  int numVertices = vertices.size();
  int numAdjacentVertices;
  vertex *start;
  queue <vertex*> queue;
  vertex *t;
  for (int i = 0; i < numVertices; i++) {
    start = vertices[i];
    if (start->visited == false) {
      numConnected++;
      start->visited = true;
      queue.push(start);
      while (!queue.empty()) {
        t = queue.front();
        queue.pop();
        numAdjacentVertices = t->adj.size();
        for (int i = 0; i < numAdjacentVertices; i++) {
          if (t->adj[i].v->visited == false) {
            t->adj[i].v->visited = true;
            queue.push(t->adj[i].v);
          }
        }
      }
    }
  }
  return numConnected;
}


bool Graph::checkBipartite() {
  // If the graph is empty
  if (vertices.size() == 0) {
    return false;
  }
  int numVertices = vertices.size();
  int numAdjacentVertices;
  vertex *start;
  string nextColor;
  queue <vertex*> queue;
  vertex *t;
  for (int i = 0; i < numVertices; i++) {
    start = vertices[i];
    if (start->visited == false) {
      start->color = "red";
      start->visited = true;
      queue.push(start);
      while (!queue.empty()) {
        t = queue.front();
        queue.pop();
        if (t->color == "red") {
          nextColor = "green";
        }
        else if (t->color == "green") {
          nextColor = "red";
        }
        numAdjacentVertices = t->adj.size();
        for (int j = 0; j < numAdjacentVertices; j++) {
          // Color of an adjacent vertex is same of current vertex
          if (t->adj[j].v->color == t->color) {
            return false;
          }
          else {
            t->adj[j].v->color = nextColor;
          }
          if (t->adj[j].v->visited == false) {
            t->adj[j].v->visited = true;
            queue.push(t->adj[j].v);
          }
        }
      }
    }
  }
  return true;
}


int main() {
  Graph graph;
  graph.addVertex("Boulder");
  graph.addVertex("Denver");
  graph.addVertex("Cheyenne");
  graph.addVertex("Fruita");
  graph.addVertex("Moab");
  graph.addVertex("Longmont");
  graph.addVertex("London");
  graph.addVertex("Paris");
  graph.addEdge("Boulder", "Denver");
  graph.addEdge("Boulder", "Cheyenne");
  graph.addEdge("Fruita", "Denver");
  graph.addEdge("Longmont", "Moab");
  graph.addEdge("London", "Paris");
  cout << graph.checkBipartite() << endl;
}
