#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include <typeindex>
#include <any>
#include <memory>

#include "maelstrom/storage/datatype.h"
#include "traversal/TraverserSet.h"
#include "strategy/TraversalStrategy.h"

namespace gremlinxx {
	class Graph;
	class Vertex;
	class Edge;
	class TraversalStep;
	class GraphTraversal;
	typedef std::function<int(std::any,std::any)> compare_func_t;
	typedef std::function<bool(std::any,std::any)> equals_func_t;
	typedef std::function<size_t(std::any)> hash_func_t;

	class GraphTraversalSource {
		private:
			Graph* graph;

		protected:
			std::vector<TraversalStrategy> strategies;
			std::unordered_map<std::type_index, maelstrom::dtype_t> type_registrations;
			std::unordered_map<std::string, std::string> options;

		public:
			GraphTraversalSource(Graph* gr);
			
			virtual Graph* getGraph();

			/*
				Constructs and returns a new traverser set object.
			*/
			virtual gremlinxx::traversal::TraverserSet* getNewTraverserSet();

			virtual GraphTraversalSource* withStrategy(TraversalStrategy strategy);
			virtual GraphTraversalSource* withoutStrategy(TraversalStrategy strategy);
			virtual GraphTraversalSource* withoutStrategies();
			virtual GraphTraversalSource* withTypeRegistration(std::type_index tid, maelstrom::dtype_t dtype);
			//GraphTraversalSource* withoutTypeRegistration(typeid_t tid); TODO
			
			virtual GraphTraversalSource* withAdminOption(std::string option_name, std::string value);
			virtual std::string getOptionValue(std::string option_name);

			virtual maelstrom::dtype_t get_dtype(std::any obj);

			virtual std::vector<TraversalStrategy>& getStrategies();

			virtual GraphTraversal V();
			virtual GraphTraversal V(Vertex v);
			virtual GraphTraversal V(std::any v_id);
			virtual GraphTraversal V(std::vector<Vertex> vertices);
			virtual GraphTraversal E();
			virtual GraphTraversal addV();
			virtual GraphTraversal addV(std::string label);
			virtual GraphTraversal addE(std::string label);
			virtual GraphTraversal inject(std::vector<std::any> injects);
	};

}