#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include <typeindex>
#include <any>

#include "maelstrom/storage/datatype.h"
#include "traversal/TraverserSet.h"

namespace gremlinxx {
	class Graph;
	class Vertex;
	class Edge;
	class TraversalStep;
	class GraphTraversal;
	typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;
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
		
		Graph* getGraph();

		/*
			Constructs and returns a new traverser set object.
		*/
		gremlinxx::traversal::TraverserSet* getNewTraverserSet();

		GraphTraversalSource* withStrategy(TraversalStrategy strategy);
		//GraphTraversalSource* withoutStrategy(TraversalStrategy strategy); TODO
		GraphTraversalSource* withTypeRegistration(std::type_index tid, maelstrom::dtype_t dtype);
		//GraphTraversalSource* withoutTypeRegistration(typeid_t tid); TODO
		
		GraphTraversalSource* withAdminOption(std::string option_name, std::string value);
		std::string getOptionValue(std::string option_name);

		maelstrom::dtype_t get_dtype(std::any obj);

		std::vector<TraversalStrategy>& getStrategies();

		GraphTraversal V();
		GraphTraversal V(Vertex v);
		GraphTraversal V(std::any v_id);
		GraphTraversal E();
		GraphTraversal addV();
		GraphTraversal addV(std::string label);
		GraphTraversal addE(std::string label);
		GraphTraversal inject(std::vector<std::any> injects);
	};

}