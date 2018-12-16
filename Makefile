CC := g++
CFLAGS := --std=c++14 -fPIC -g

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

lib: VertexProperty.o Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o AddVertexStartStep.o AddVertexStep.o AddEdgeStartStep.o AddEdgeStep.o AddPropertyStep.o FromStep.o ToStep.o NoOpStep.o P.o Traverser.o
	$(CC) $(CFLAGS) -shared VertexProperty.o Vertex.o Edge.o Graph.o GraphTraversalSource.o GraphTraversal.o TraversalStep.o VertexStep.o GraphStep.o HasStep.o AddVertexStartStep.o AddVertexStep.o AddEdgeStartStep.o AddEdgeStep.o AddPropertyStep.o FromStep.o ToStep.o P.o Traverser.o -o $(LIBGREMLIN_NAME)
	mv $(LIBGREMLIN_NAME) $(LIBGREMLIN_PATH)
	chmod 755 $(LIBGREMLIN_PATH)

TraversalStep.o: TraversalStep.cpp TraversalStep.h
	$(CC) $(CFLAGS) -c TraversalStep.cpp -o TraversalStep.o

VertexProperty.o: VertexProperty.cpp VertexProperty.h
	$(CC) $(CFLAGS) -c VertexProperty.cpp -o VertexProperty.o

Vertex.o: Vertex.cpp Vertex.h
	$(CC) $(CFLAGS) -c Vertex.cpp -o Vertex.o

Edge.o: Edge.cpp Edge.h
	$(CC) $(CFLAGS) -c Edge.cpp -o Edge.o

Graph.o: Graph.cpp Graph.h
	$(CC) $(CFLAGS) -c Graph.cpp -o Graph.o

GraphTraversal.o: GraphTraversal.cpp GraphTraversal.h
	$(CC) $(CFLAGS) -c GraphTraversal.cpp -o GraphTraversal.o

GraphTraversalSource.o: GraphTraversalSource.cpp GraphTraversalSource.h
	$(CC) $(CFLAGS) -c GraphTraversalSource.cpp -o GraphTraversalSource.o

VertexStep.o: VertexStep.cpp VertexStep.h
	$(CC) $(CFLAGS) -c VertexStep.cpp -o VertexStep.o

EdgeStep.o: EdgeStep.cpp EdgeStep.h
	$(CC) $(CFLAGS) -c EdgeStep.cpp -o EdgeStep.o

GraphStep.o: GraphStep.cpp GraphStep.h
	$(CC) $(CFLAGS) -c GraphStep.cpp -o GraphStep.o

HasStep.o: HasStep.cpp HasStep.h
	$(CC) $(CFLAGS) -c HasStep.cpp -o HasStep.o

AddVertexStartStep.o: AddVertexStartStep.cpp AddVertexStep.h
	$(CC) $(CFLAGS) -c AddVertexStartStep.cpp -o AddVertexStartStep.o

AddVertexStep.o: AddVertexStep.cpp AddVertexStep.h
	$(CC) $(CFLAGS) -c AddVertexStep.cpp -o AddVertexStep.o

AddEdgeStartStep.o: AddEdgeStartStep.cpp AddEdgeStartStep.h
	$(CC) $(CFLAGS) -c AddEdgeStartStep.cpp -o AddEdgeStartStep.o

AddEdgeStep.o: AddEdgeStep.cpp AddEdgeStep.h
	$(CC) $(CFLAGS) -c AddEdgeStep.cpp -o AddEdgeStep.o

AddPropertyStep.o: AddPropertyStep.cpp AddPropertyStep.h
	$(CC) $(CFLAGS) -c AddPropertyStep.cpp -o AddPropertyStep.o

FromStep.o: FromStep.cpp FromStep.h
	$(CC) $(CFLAGS) -c FromStep.cpp -o FromStep.o

ToStep.o: ToStep.cpp ToStep.h
	$(CC) $(CFLAGS) -c ToStep.cpp -o ToStep.o

NoOpStep.o: NoOpStep.cpp NoOpStep.h
	$(CC) $(CFLAGS) -c NoOpStep.cpp -o NoOpStep.o

P.o: P.cpp P.h
	$(CC) $(CFLAGS) -c P.cpp -o P.o

Traverser.o: Traverser.cpp Traverser.h
	$(CC) $(CFLAGS) -c Traverser.cpp -o Traverser.o

clean:
	rm -rf *.o *.exe *.so *.dylib
