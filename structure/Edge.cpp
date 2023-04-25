#include "structure/Edge.h"
#include "structure/Vertex.h"

std::pair<Vertex*, Vertex*> Edge::bothV() {
	return std::make_pair(outV(), inV());
}