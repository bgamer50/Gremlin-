#pragma once

#include <vector>
#include <memory>

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

			/*
				Returns the number of vertices in this Graph.
			*/
			virtual size_t num_vertices() = 0;

			/**
			 * Returns a copy of this Graph's edges.
			**/
			virtual std::vector<Edge> edges() = 0;

			/*
				Returns the number of edges in this Graph.
			*/
			virtual size_t num_edges() = 0;

			// Vertex labels are optional, implementer should check if the label is empty and react appropriately
			virtual Vertex add_vertex(std::string label="") = 0;
			virtual maelstrom::vector add_vertices(size_t n_new_vertices, std::string label="") = 0;

			// Edge labels are always required
			virtual Edge add_edge(Vertex from_vertex, Vertex to_vertex, std::string label) = 0;
			virtual maelstrom::vector add_edges(maelstrom::vector& from_vertices, maelstrom::vector& to_vertices, std::string label) = 0;

			// Traverses vertices to their neighbors.  Returns the resulting vertices (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> V(maelstrom::vector& current_vertices, std::vector<std::string>& labels, Direction direction) = 0;

			// Traverses vertices to their edges.  Returns the resulting edges (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> E(maelstrom::vector& current_vertices, std::vector<std::string>& labels, Direction direction) = 0;

			// Traverses edges to their vertices.  Returns the resulting vertices (first element) and originating index (second element).
			virtual std::pair<maelstrom::vector, maelstrom::vector> toV(maelstrom::vector& current_edges, Direction direction) = 0;

			// Constructs an independent edge-induced subgraph from the given edges.
			virtual std::shared_ptr<Graph> subgraph(maelstrom::vector& edges) = 0;

			/*
				Sets the vertex properties of the given vertices to the given values.
			*/
			virtual void set_vertex_properties(std::string property_name, maelstrom::vector& vertices, maelstrom::vector& property_values) = 0;

			/*
				Gets the vertex properties of the given vertices.
				Returns a pair where the first vector consists of the property values
				and the second vector consists of the originating indices.

				If return_values is true, the values (first element in pair) are returned.
				If return_values is false, an empty vector is returned in place of the values.
			*/
			virtual std::pair<maelstrom::vector, maelstrom::vector> get_vertex_properties(std::string property_name, maelstrom::vector& vertices, bool return_values=true) = 0;

			virtual std::vector<std::string> get_vertex_property_names() = 0;

			/*
				Returns the number of vertices that have the given property.
			*/
            virtual size_t get_vertex_property_num_entries(std::string property_name) = 0;

			/*
				Returns the number of edges that have the given property.
			*/
            virtual size_t get_edge_property_num_entries(std::string property_name) = 0;

			/*
				Sets the edge properties of the given edges to the given values.
			*/
			virtual void set_edge_properties(std::string property_name, maelstrom::vector& edges, maelstrom::vector& property_values) = 0;

			/*
				Gets the edge properties of the given edges.
				Returns a pair where the first vector consists of the property values
				and the second vector consists of the originating indices.

				If return_values is true, the values (first element in pair) are returned.
				If return_values is false, an empty vector is returned in place of the values.
			*/
			virtual std::pair<maelstrom::vector, maelstrom::vector> get_edge_properties(std::string property_name, maelstrom::vector& edges, bool return_values=true) = 0;

			virtual std::vector<std::string> get_edge_property_names() = 0;

			virtual maelstrom::vector get_vertex_labels(maelstrom::vector& vertices) = 0;
			virtual maelstrom::vector get_edge_labels(maelstrom::vector& edges) = 0;

			virtual maelstrom::dtype_t get_vertex_dtype() = 0;
			virtual maelstrom::dtype_t get_edge_dtype() = 0;
	};
	
}

#include "traversal/GraphTraversalSource.h"