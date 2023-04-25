#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <functional>
#include <typeindex>
#include <boost/any.hpp>

class Graph;
class Vertex;
class Edge;
class TraversalStep;
class GraphTraversal;
typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;
typedef std::function<int(boost::any,boost::any)> compare_func_t;
typedef std::function<bool(boost::any,boost::any)> equals_func_t;
typedef std::function<size_t(boost::any)> hash_func_t;

class GraphTraversalSource {
private:
	Graph* graph;

protected:
	std::vector<TraversalStrategy> strategies;
	std::unordered_map<std::type_index, std::tuple<compare_func_t, equals_func_t, hash_func_t>> type_registrations;
	std::unordered_map<std::string, std::string> options;

public:
	GraphTraversalSource(Graph* gr);
	
	Graph* getGraph();

	GraphTraversalSource* withStrategy(TraversalStrategy strategy);
	//GraphTraversalSource* withoutStrategy(TraversalStrategy strategy); TODO
	GraphTraversalSource* withTypeRegistration(std::type_index tid, compare_func_t cmp, equals_func_t eql, hash_func_t hsh);
	GraphTraversalSource* withTypeRegistration(std::type_index tid, compare_func_t cmp, hash_func_t hsh);
	//GraphTraversalSource* withoutTypeRegistration(typeid_t tid); TODO
	
	GraphTraversalSource* withAdminOption(std::string option_name, std::string value);
	std::string getOptionValue(std::string option_name);

	std::vector<TraversalStrategy>& getStrategies();

	bool test_equals(boost::any a, boost::any b);
	int test_compare(boost::any a, boost::any b);
	size_t test_hash(boost::any v);

	GraphTraversal* V();
	GraphTraversal* V(Vertex* v);
	GraphTraversal* V(boost::any v_id);
	GraphTraversal* E();
	GraphTraversal* addV();
	GraphTraversal* addV(std::string label);
	GraphTraversal* addE(std::string label);
	GraphTraversal* inject(std::vector<boost::any> injects);
};

