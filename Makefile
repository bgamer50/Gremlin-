main.exe: gremlin.dll main.o
	g++ --std=c++11 -Wall main.o -lgremlin -o main.exe

main.o: main.cpp
	g++ --std=c++11 -c main.cpp -o main.o

gremlin.dll: Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o
	g++ --std=c++11 -shared Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o -o gremlin.dll
	mv gremlin.dll /usr/lib/gremlin.dll
	chmod 755 /usr/lib/gremlin.dll

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

clean:
	rm -rf *.o *.exe *.so *.dll
