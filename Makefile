CC := g++
CFLAGS := --std=c++14 -fPIC

ifeq ($(shell uname -s), Darwin)
	LIBGREMLIN_PATH := /usr/local/lib/libgremlin.dylib
	LIBGREMLIN_NAME := libgremlin.dylib
endif
ifeq ($(shell uname -s), CYGWIN_NT-10.0)
	LIBGREMLIN_PATH := /usr/lib/libgremlin.dll.a
	LIBGREMLIN_NAME := libgremlin.dll.a
endif
ifeq ($(shell uname -s), Linux)
	LIBGREMLIN_PATH := /usr/lib/libgremlin.so
	LIBGREMLIN_NAME := libgremlin.so
endif

lib: Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o AddVertexStartStep.o AddVertexStep.o P.o Traverser.o
	$(CC) $(CFLAGS) -shared Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o AddVertexStartStep.o AddVertexStep.o P.o Traverser.o -o $(LIBGREMLIN_NAME)
	mv $(LIBGREMLIN_NAME) $(LIBGREMLIN_PATH)
	chmod 755 $(LIBGREMLIN_PATH)

TraversalStep.o: TraversalStep.cpp
	$(CC) $(CFLAGS) -c TraversalStep.cpp -o TraversalStep.o

Vertex.o: Vertex.cpp
	$(CC) $(CFLAGS) -c Vertex.cpp -o Vertex.o

Edge.o: Edge.cpp
	$(CC) $(CFLAGS) -c Edge.cpp -o Edge.o

Graph.o: Graph.cpp
	$(CC) $(CFLAGS) -c Graph.cpp -o Graph.o

GraphTraversal.o: GraphTraversal.cpp
	$(CC) $(CFLAGS) -c GraphTraversal.cpp -o GraphTraversal.o

GraphTraversalSource.o: GraphTraversalSource.cpp
	$(CC) $(CFLAGS) -c GraphTraversalSource.cpp -o GraphTraversalSource.o

VertexStep.o: VertexStep.cpp
	$(CC) $(CFLAGS) -c VertexStep.cpp -o VertexStep.o

EdgeStep.o: EdgeStep.cpp
	$(CC) $(CFLAGS) -c EdgeStep.cpp -o EdgeStep.o

GraphStep.o: GraphStep.cpp
	$(CC) $(CFLAGS) -c GraphStep.cpp -o GraphStep.o

HasStep.o: HasStep.cpp
	$(CC) $(CFLAGS) -c HasStep.cpp -o HasStep.o

AddVertexStartStep.o: AddVertexStartStep.cpp
	$(CC) $(CFLAGS) -c AddVertexStartStep.cpp -o AddVertexStartStep.o

AddVertexStep.o: AddVertexStep.cpp
	$(CC) $(CFLAGS) -c AddVertexStep.cpp -o AddVertexStep.o

P.o: P.cpp
	$(CC) $(CFLAGS) -c P.cpp -o P.o

Traverser.o: Traverser.cpp
	$(CC) $(CFLAGS) -c Traverser.cpp -o Traverser.o

clean:
	rm -rf *.o *.exe *.so *.dylib
