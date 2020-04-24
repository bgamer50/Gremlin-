#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

#include <string>
#include <vector>
#include <functional>

class Graph;
class Vertex;
class Edge;
class TraversalStep;
class GraphTraversal;
typedef std::function<void(std::vector<TraversalStep*>&)> TraversalStrategy;
typedef std::function<int(boost::any,boost::any)> compare_func_t;
typedef std::function<bool(boost::any,boost::any)> equals_func_t;

class GraphTraversalSource {
private:
	Graph* graph;

protected:
	std::vector<TraversalStrategy> strategies;
	std::unordered_map<std::type_index, std::pair<compare_func_t, equals_func_t>> type_registrations;

public:
	GraphTraversalSource(Graph* gr);
	
	Graph* getGraph();

	GraphTraversalSource* withStrategy(TraversalStrategy strategy);
	//GraphTraversalSource* withoutStrategy(TraversalStrategy strategy); TODO
	GraphTraversalSource* withTypeRegistration(std::type_index tid, compare_func_t cmp, equals_func_t eql);
	GraphTraversalSource* withTypeRegistration(std::type_index tid, compare_func_t cmp);
	//GraphTraversalSource* withoutTypeRegistration(typeid_t tid); TODO

	std::vector<TraversalStrategy>& getStrategies();

	bool test_equals(boost::any a, boost::any b);
	int test_compare(boost::any a, boost::any b);

	virtual GraphTraversal* V() = 0;
	virtual GraphTraversal* V(Vertex* v) = 0;
	virtual GraphTraversal* E() = 0;
	virtual GraphTraversal* addV() = 0;
	virtual GraphTraversal* addV(std::string label) = 0;
	virtual GraphTraversal* addE(std::string label) = 0;
};

#include "traversal/GraphTraversal.h"
#include "strategy/TraversalStrategy.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "strategy/AddEdgeStepCompletionStrategy.h"
#include "strategy/RepeatStepCompletionStrategy.h"
#include "strategy/ValueMapStepCompletionStrategy.h"

GraphTraversalSource::GraphTraversalSource(Graph* gr) {
	graph = gr;
	this->withStrategy(add_edge_step_completion_strategy);
	this->withStrategy(repeat_step_completion_strategy);
	this->withStrategy(valuemap_step_completion_strategy);
	
	this->withTypeRegistration(
		std::type_index(typeid(int)), 
		[](boost::any a, boost::any b){return boost::any_cast<int>(a) - boost::any_cast<int>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(int) && b.type() == typeid(int)) ? boost::any_cast<int>(a) == boost::any_cast<int>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(long)), 
		[](boost::any a, boost::any b){return boost::any_cast<long>(a) - boost::any_cast<long>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(long) && b.type() == typeid(long)) ? boost::any_cast<long>(a) == boost::any_cast<long>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(unsigned int)), 
		[](boost::any a, boost::any b){return boost::any_cast<unsigned int>(a) - boost::any_cast<unsigned int>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(unsigned int) && b.type() == typeid(unsigned int)) ? boost::any_cast<unsigned int>(a) == boost::any_cast<unsigned int>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(unsigned long)), 
		[](boost::any a, boost::any b){return boost::any_cast<unsigned long>(a) - boost::any_cast<unsigned long>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(unsigned long) && b.type() == typeid(unsigned long)) ? boost::any_cast<unsigned long>(a) == boost::any_cast<unsigned long>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(float)), 
		[](boost::any a, boost::any b){return boost::any_cast<float>(a) - boost::any_cast<float>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(float) && b.type() == typeid(float)) ? boost::any_cast<float>(a) == boost::any_cast<float>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(double)), 
		[](boost::any a, boost::any b){return boost::any_cast<double>(a) - boost::any_cast<double>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(double) && b.type() == typeid(double)) ? boost::any_cast<double>(a) == boost::any_cast<double>(b) : false;}
	);
	this->withTypeRegistration(
		std::type_index(typeid(std::string)), 
		[](boost::any a, boost::any b){return boost::any_cast<std::string>(a).compare(boost::any_cast<std::string>(b));}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(std::string) && b.type() == typeid(std::string)) ? boost::any_cast<std::string>(a) == boost::any_cast<std::string>(b) : false;}
	);
}

GraphTraversalSource* GraphTraversalSource::withStrategy(TraversalStrategy strategy) {
	this->strategies.push_back(strategy);
	return this;
}

GraphTraversalSource* GraphTraversalSource::withTypeRegistration(std::type_index tid, compare_func_t cmp, equals_func_t eql) {
	this->type_registrations[tid] = std::make_pair(cmp, eql);
	return this;
}

GraphTraversalSource* GraphTraversalSource::withTypeRegistration(std::type_index tid, compare_func_t cmp) {
	std::function<bool(boost::any, boost::any)> eql = [&](boost::any a, boost::any b){
		return bool(cmp(a,b) == 0);
	};
	return this->withTypeRegistration(tid, cmp, eql);
}

bool GraphTraversalSource::test_equals(boost::any a, boost::any b) {
	const std::type_index type = std::type_index(a.type());
	return this->type_registrations[type].second(a,b);
}

int GraphTraversalSource::test_compare(boost::any a, boost::any b) {
	const std::type_index type = std::type_index(a.type());
	return this->type_registrations[type].first(a,b);
}

std::vector<TraversalStrategy>& GraphTraversalSource::getStrategies() {
		return this->strategies;
	}

Graph* GraphTraversalSource::getGraph() {
		return graph;
	}

#endif