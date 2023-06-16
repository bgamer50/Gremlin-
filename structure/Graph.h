#pragma once

#include <vector>

#include "structure/Edge.h"
#include "structure/Vertex.h"
#include "maelstrom/storage/datatype.h"
#include "maelstrom/containers/vector.h"

namespace gremlinxx {

	class GraphTraversalSource;

	class Graph {
		public:
			Graph(){}
			virtual GraphTraversalSource* traversal() = 0;

			/**
			 * Returns a copy of this Graph's vertices.
			 **/
			virtual std::vector<Vertex> vertices() = 0;

			/**
			 * Returns a copy of this Graph's edges.
			**/
			virtual std::vector<Edge> edges() = 0;

			// Vertex labels are optional, implementer should check if the label is empty and react appropriately
			virtual Vertex add_vertex(std::string label="") = 0;
			virtual maelstrom::vector add_vertices(size_t n_new_vertices, std::string label="") = 0;

			// Edge labels are always required
			virtual Edge add_edge(Vertex from_vertex, Vertex to_vertex, std::string label) = 0;
			virtual maelstrom::vector add_edges(maelstrom::vector& from_vertices, maelstrom::vector& to_vertices, std::string label) = 0;

			// Traversers vertices to their neighbors.  Returns the resulting vertices (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> V(maelstrom::vector& current_vertices, std::vector<std::string>& labels, Direction direction) = 0;

			// Traversers vertices to their edges.  Returns the resulting edges (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> E(maelstrom::vector& current_vertices, std::vector<std::string>& labels, Direction direction) = 0;

			// Traversers edges to their vertices.  Returns the results vertices (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> toV(maelstrom::vector& current_edges, Direction direction) = 0;

			/*
				Sets the vertex properties of the given vertices to the given values.
			*/
			virtual void setVertexProperties(std::string property_name, maelstrom::vector& vertices, maelstrom::vector& property_values) = 0;

			/*
				Gets the vertex properties of the given vertices.
				Returns a pair where the first vector consists of the vertices that had this property
				and the second vector consists of the property values of those vertices.

				If return_values is true, the values are returned.
				If return_values is false, an empty vector is returned in place of the values.
			*/
			virtual std::pair<maelstrom::vector, maelstrom::vector> getVertexProperties(std::string property_name, maelstrom::vector& vertices, bool return_values=true) = 0;

			virtual std::vector<std::string> getVertexPropertyNames() = 0;

			virtual maelstrom::vector getVertexLabels(maelstrom::vector& vertices);

			virtual maelstrom::dtype_t get_vertex_dtype() = 0;
			virtual maelstrom::dtype_t get_edge_dtype() = 0;
	};
	
}

#include "traversal/GraphTraversalSource.h"