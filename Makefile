libgremlin.dylib: Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o P.o
	g++ --std=c++11 -shared Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o P.o -o libgremlin.dylib
	mv libgremlin.dylib /usr/local/lib/libgremlin.dylib
	chmod 755 /usr/local/lib/libgremlin.dylib

TraversalStep.o: TraversalStep.cpp
	g++ --std=c++11 -c TraversalStep.cpp -o TraversalStep.o

Vertex.o: Vertex.cpp
	g++ --std=c++11 -c Vertex.cpp -o Vertex.o

Edge.o: Edge.cpp
	g++ --std=c++11 -c Edge.cpp -o Edge.o

Graph.o: Graph.cpp
	g++ --std=c++11 -c Graph.cpp -o Graph.o

GraphTraversal.o: GraphTraversal.cpp
	g++ --std=c++11 -c GraphTraversal.cpp -o GraphTraversal.o

GraphTraversalSource.o: GraphTraversalSource.cpp
	g++ --std=c++11 -c GraphTraversalSource.cpp -o GraphTraversalSource.o

VertexStep.o: VertexStep.cpp
	g++ --std=c++11 -c VertexStep.cpp -o VertexStep.o

EdgeStep.o: EdgeStep.cpp
	g++ --std=c++11 -c EdgeStep.cpp -o EdgeStep.o

GraphStep.o: GraphStep.cpp
	g++ --std=c++11 -c GraphStep.cpp -o GraphStep.o

HasStep.o: HasStep.cpp
	g++ --std=c++11 -c HasStep.cpp -o HasStep.o

P.o: P.cpp
	g++ --std=c++11 -c P.cpp -o P.o

clean:
	rm -rf *.o *.exe *.so *.dylib
