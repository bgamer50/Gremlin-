#ifndef GRAPH_TRAVERSAL_SOURCE_H
#define GRAPH_TRAVERSAL_SOURCE_H

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

#include "traversal/GraphTraversal.h"
#include "strategy/TraversalStrategy.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "strategy/RepeatStepCompletionStrategy.h"
#include "strategy/ByModulatingStrategy.h"
#include "strategy/FromToModulatingStrategy.h"

GraphTraversalSource::GraphTraversalSource(Graph* gr) {
	graph = gr;
	this->withStrategy(repeat_step_completion_strategy);
	this->withStrategy(by_modulating_strategy);
	this->withStrategy(from_to_modulating_strategy);
	
	this->withTypeRegistration(
		std::type_index(typeid(int)), 
		[](boost::any a, boost::any b){return boost::any_cast<int>(a) - boost::any_cast<int>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(int) && b.type() == typeid(int)) ? boost::any_cast<int>(a) == boost::any_cast<int>(b) : false;},
		[](boost::any v){return std::hash<int>()(boost::any_cast<int>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(long)), 
		[](boost::any a, boost::any b){return boost::any_cast<long>(a) - boost::any_cast<long>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(long) && b.type() == typeid(long)) ? boost::any_cast<long>(a) == boost::any_cast<long>(b) : false;},
		[](boost::any v){return std::hash<long>()(boost::any_cast<long>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(unsigned int)), 
		[](boost::any a, boost::any b){return (long)boost::any_cast<unsigned int>(a) - (long)boost::any_cast<unsigned int>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(unsigned int) && b.type() == typeid(unsigned int)) ? boost::any_cast<unsigned int>(a) == boost::any_cast<unsigned int>(b) : false;},
		[](boost::any v){return std::hash<unsigned int>()(boost::any_cast<unsigned int>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(unsigned long)), 
		[](boost::any a, boost::any b){return (long)boost::any_cast<unsigned long>(a) - (long)boost::any_cast<unsigned long>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(unsigned long) && b.type() == typeid(unsigned long)) ? boost::any_cast<unsigned long>(a) == boost::any_cast<unsigned long>(b) : false;},
		[](boost::any v){return std::hash<unsigned long>()(boost::any_cast<unsigned long>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(float)), 
		[](boost::any a, boost::any b){return boost::any_cast<float>(a) - boost::any_cast<float>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(float) && b.type() == typeid(float)) ? boost::any_cast<float>(a) == boost::any_cast<float>(b) : false;},
		[](boost::any v){return std::hash<float>()(boost::any_cast<float>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(double)), 
		[](boost::any a, boost::any b){return boost::any_cast<double>(a) - boost::any_cast<double>(b);}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(double) && b.type() == typeid(double)) ? boost::any_cast<double>(a) == boost::any_cast<double>(b) : false;},
		[](boost::any v){return std::hash<double>()(boost::any_cast<double>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(std::string)), 
		[](boost::any a, boost::any b){return boost::any_cast<std::string>(a).compare(boost::any_cast<std::string>(b));}, 
		[](boost::any a, boost::any b){return (a.type() == typeid(std::string) && b.type() == typeid(std::string)) ? boost::any_cast<std::string>(a) == boost::any_cast<std::string>(b) : false;},
		[](boost::any v){return std::hash<std::string>()(boost::any_cast<std::string>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(const char*)),
		[](boost::any a, boost::any b){return std::string(boost::any_cast<const char*>(a)).compare(boost::any_cast<const char*>(b));},
		[](boost::any a, boost::any b){return (a.type() == typeid(const char*) && b.type() == typeid(const char*)) ? std::string(boost::any_cast<const char*>(a)) == std::string(boost::any_cast<const char*>(b)) : false;},
		[](boost::any v){return std::hash<std::string>()(std::string(boost::any_cast<const char*>(v)));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(Vertex*)),
		[](boost::any a, boost::any b){return reinterpret_cast<long>(boost::any_cast<Vertex*>(a)) - reinterpret_cast<long>(boost::any_cast<Vertex*>(a));},
		[](boost::any a, boost::any b){return boost::any_cast<Vertex*>(a) == boost::any_cast<Vertex*>(a);},
		[](boost::any v){return std::hash<Vertex*>()(boost::any_cast<Vertex*>(v));}
	);
	this->withTypeRegistration(
		std::type_index(typeid(Edge*)),
		[](boost::any a, boost::any b){return reinterpret_cast<long>(boost::any_cast<Edge*>(a)) - reinterpret_cast<long>(boost::any_cast<Edge*>(a));},
		[](boost::any a, boost::any b){return reinterpret_cast<long>(boost::any_cast<Edge*>(a)) == reinterpret_cast<long>(boost::any_cast<Edge*>(a));},
		[](boost::any v){return std::hash<long>()(reinterpret_cast<long>(boost::any_cast<Edge*>(v)));}
	);
}

GraphTraversalSource* GraphTraversalSource::withStrategy(TraversalStrategy strategy) {
	this->strategies.push_back(strategy);
	return this;
}

GraphTraversalSource* GraphTraversalSource::withTypeRegistration(std::type_index tid, compare_func_t cmp, equals_func_t eql, hash_func_t hsh) {
	this->type_registrations[tid] = std::make_tuple(cmp, eql, hsh);
	return this;
}

GraphTraversalSource* GraphTraversalSource::withTypeRegistration(std::type_index tid, compare_func_t cmp, hash_func_t hsh) {
	std::function<bool(boost::any, boost::any)> eql = [&](boost::any a, boost::any b){
		return bool(cmp(a,b) == 0);
	};
	return this->withTypeRegistration(tid, cmp, eql, hsh);
}

GraphTraversalSource* GraphTraversalSource::withAdminOption(std::string option_name, std::string value) {
	this->options[option_name] = value;
	return this;
}

std::string GraphTraversalSource::getOptionValue(std::string option_name) {
	auto kv = this->options.find(option_name);
	if(kv == this->options.end()) return "";
	else return kv->second;
}

bool GraphTraversalSource::test_equals(boost::any a, boost::any b) {
	const std::type_index type = std::type_index(a.type());
	auto reg = this->type_registrations.find(type);
	if(reg == this->type_registrations.end()) {
		throw std::runtime_error("No registration for type " + std::string(type.name()));
	}
	return std::get<1>(this->type_registrations[type])(a,b);
}

int GraphTraversalSource::test_compare(boost::any a, boost::any b) {
	const std::type_index type = std::type_index(a.type());
	auto reg = this->type_registrations.find(type);
	if(reg == this->type_registrations.end()) {
		throw std::runtime_error("No registration for type " + std::string(type.name()));
	}
	return std::get<0>(this->type_registrations[type])(a,b);
}

size_t GraphTraversalSource::test_hash(boost::any v) {
	const std::type_index type = std::type_index(v.type());
	auto reg = this->type_registrations.find(type);
	if(reg == this->type_registrations.end()) {
		throw std::runtime_error("No registration for type " + std::string(type.name()));
	}
	return std::get<2>(this->type_registrations[type])(v);
}

std::vector<TraversalStrategy>& GraphTraversalSource::getStrategies() {
		return this->strategies;
}

Graph* GraphTraversalSource::getGraph() {
		return graph;
}

#include "step/graph/GraphStep.h"
#include "step/vertex/AddVertexStartStep.h"
#include "step/edge/AddEdgeStartStep.h"
#include "step/controlflow/InjectStep.h"

GraphTraversal* GraphTraversalSource::V() {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new GraphStep(VERTEX, {}));
	return trv;
}

GraphTraversal* GraphTraversalSource::V(Vertex* v) {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new GraphStep(VERTEX, {v->id()}));
	return trv;
}

GraphTraversal* GraphTraversalSource::V(boost::any v_id) {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new GraphStep(VERTEX, {v_id}));
	return trv;
}

//TODO should be a version of the Graph Step
GraphTraversal* GraphTraversalSource::E() {
	return this->V()->outE();
}

GraphTraversal* GraphTraversalSource::addV() {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new AddVertexStartStep());
	return trv;
}

GraphTraversal* GraphTraversalSource::addV(std::string label) {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new AddVertexStartStep(label));
	return trv;
}

GraphTraversal* GraphTraversalSource::addE(std::string label) {
	GraphTraversal* trv = new GraphTraversal(this);
	trv->appendStep(new AddEdgeStartStep(label));
	return trv;
}

GraphTraversal* GraphTraversalSource::inject(std::vector<boost::any> injects) {
	GraphTraversal* trv = new GraphTraversal(this);
	return trv->appendStep(new InjectStep(injects));
}

#endif