#include <cstdio>
#include <vector>
#include <tuple>
#include "Graph.h"
#include "GraphTraversalSource.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

int main()
{
    printf("hello from Gremlin__!\n");
	Graph graph;
	vector<Vertex> arr = graph.vertices();
	graph.traversal();
	for (int k = 0; k < arr.size(); k++) printf("%lu\n", arr[k].id());
    return 0;
}