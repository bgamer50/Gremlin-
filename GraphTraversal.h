#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include "TraversalStep.h"
#include "HasStep.h"
#include "P.h"
#include "Direction.h"
#include "Scope.h"
#include <string>
#include <vector>
#include <functional>

class Graph;
class Vertex;
class Edge;
class GraphTraversalSource;

class GraphTraversal {
protected:
	std::vector<TraversalStep*> steps;
private:
	GraphTraversalSource* source;
public:
	GraphTraversal(GraphTraversalSource* src);
	Graph* getGraph();
	GraphTraversalSource* getTraversalSource();
	std::vector<TraversalStep*> getSteps();
	
	// Steps
	GraphTraversal* addE(std::string label);
	GraphTraversal* addV(std::string label);
	GraphTraversal* addV();
	GraphTraversal* property(std::string label, void* value, size_t size);
	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	GraphTraversal* as(std::string sideEffectLabel);
	GraphTraversal* barrier();
	GraphTraversal* by(GraphTraversal* byTraversal);
	GraphTraversal* by(std::string label);
	GraphTraversal* cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	//GraphTraversal<auto n> coalesce(std::vector<GraphTraversal<A>> traversals);
	GraphTraversal* coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	GraphTraversal* count();
	GraphTraversal* cyclicPath();
	GraphTraversal* dedup();
	GraphTraversal* drop();
	GraphTraversal* emit();
	//GraphTraversal emit(Predicate predicate);
	GraphTraversal* emit(GraphTraversal* emitTraversal);
	std::string explain();
	GraphTraversal* fold();
	GraphTraversal* from(std::string sideEffectLabel);
	GraphTraversal* from(GraphTraversal* fromTraversal);
	GraphTraversal* from(Vertex* fromVertex);
	GraphTraversal* V();
	GraphTraversal* V(Vertex* vertex);
	GraphTraversal* V(std::vector<Vertex*> vertices);
	//GraphTraversal* V(void* objects, size_t sizeOfEach, int length);
	//GraphTraversal group();
	//GraphTraversal group(std::string sideEffectLabel);
	//GraphTraversal groupCount();
	//GraphTraversal groupCount(std::string sideEffectLabel);
	//GraphTraversal has(std::string key, void* value, size_t size); // dangerous operation
	//GraphTraversal has(std::string label, std::string key, void* value, size_t size); // dangerous operation
	template<typename T> GraphTraversal* has(std::string key, P<T> predicate);
	GraphTraversal* has(std::string key, int value);
	GraphTraversal* has(std::string key, std::string value);

	GraphTraversal* has(std::string key, GraphTraversal* valueTraversal);
	GraphTraversal* has(std::string key);
	GraphTraversal* hasNot(std::string key);
	GraphTraversal* hasLabel(std::vector<std::string> labels);
	GraphTraversal* hasLabel(std::string label);
	GraphTraversal* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	GraphTraversal* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	//GraphTraversal<auto n> id();
	GraphTraversal* identity();
	//GraphTraversal inject(void* object, size_t size);
	GraphTraversal* is(void* val, size_t size);
	//GraphTraversal is(Predicate predicate);
	//GraphTraversal key();
	GraphTraversal* label();
	GraphTraversal* limit(unsigned long theLimit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	GraphTraversal* local(GraphTraversal* localTraversal);
	GraphTraversal* loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	GraphTraversal* math(std::string equation);
	GraphTraversal* max();
	//GraphTraversal max(Scope scope);
	GraphTraversal* mean();
	//GraphTraversal mean(Scope scope);
	GraphTraversal* min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
	GraphTraversal* order();
	//GraphTraversal order(Scope scope);
	// pagerank step not supported
	GraphTraversal* path();
	// peerpressure step not supported
	std::string profile();
	//GraphTraversal project(std::vector<std::string> sideEffectLabels);
	// program step not supported
	//GraphTraversal properties(std::vector<std::string> labels);
	//GraphTraversal properties();
	//GraphTraversal propertyMap(std::vector<std::string> labels);
	//GraphTraversal propertyMap();
	//GraphTraversal range(long low, long high);
	//GraphTraversal repeat(GraphTraversal repeatTraversal);
	// sack step not supported
	GraphTraversal* sample(int sampleSize);
	//GraphTraversal sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal* select(std::string sideEffectLabel);
	//GraphTraversal select(std::vector<std::string> sideEffectLabels);
	//GraphTraversal select(GraphTraversal selectTraversal);
	GraphTraversal* simplePath();
	GraphTraversal* skip(unsigned long toSkip);
	//GraphTraversal skip(Scope scope, unsigned long toSkip);
	GraphTraversal* store(std::string sideEffectLabel);
	//GraphTraversal subgraph(std::string sideEffectLabel);
	GraphTraversal* sum();
	//GraphTraversal sum(Scope scope);
	//GraphTraversal tail();
	//GraphTraversal tail(unsigned long theLimit);
	//GraphTraversal tail(Scope scope);
	//GraphTraversal tail(Scope scope, unsigned long theLimit);
	GraphTraversal* timeLimit(long time);
	GraphTraversal* to(Direction direction, std::vector<std::string> labels);
	GraphTraversal* to(Direction direction);
	GraphTraversal* to(Direction direction, std::string label);
	GraphTraversal* to(std::string sideEffectLabel); // modulator for addE
	GraphTraversal* to(GraphTraversal* toTraversal); //modulator for addE
	GraphTraversal* to(Vertex* toVertex); //modulator for addE
	GraphTraversal* toV(Direction direction);
	//GraphTraversal tree(std::string sideEffectLabel);
	//GraphTraversal tree();
	//GraphTraversal unfold();
	//GraphTraversal _union(std::vector<GraphTraversal> unionTraversals);
	//GraphTraversal until(Predicate predicate);
	//GraphTraversal until(GraphTraversal untilTraversal);
	//GraphTraversal value();
	//GraphTraversal valueMap();
	//GraphTraversal valueMap(std::vector<std::string> labels);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue, std::vector<std::string> labels);
	//GraphTraversal values();
	//GraphTraversal values(std::vector<std::string> labels);
	GraphTraversal* both();
	GraphTraversal* both(std::vector<std::string> edgeLabels);
	GraphTraversal* bothE();
	GraphTraversal* bothE(std::vector<std::string> edgeLabels);
	GraphTraversal* bothV();
	GraphTraversal* inV();
	GraphTraversal* otherV();
	GraphTraversal* out();
	GraphTraversal* out(std::vector<std::string> edgeLabels);
	GraphTraversal* in();
	GraphTraversal* in(std::vector<std::string> edgeLabels);
	GraphTraversal* outE();
	GraphTraversal* outE(std::vector<std::string> edgeLabels);
	GraphTraversal* inE();
	GraphTraversal* inE(std::vector<std::string> edgeLabels);
	//GraphTraversal where(Predicate predicate);
	//GraphTraversal where(std::string label, Predicate predicate);
	//GraphTraversal where(GraphTraversal<auto n> whereTraversal);
	
	// These may replace predicates...
	//GraphTraversal lt(double max_exclusive);
	//GraphTraversal gt(double min_exculsive);
	//GraphTraversal eq(double equal, double tolerance);
	//GraphTraversal eq(long equal);
	//GraphTraversal eq(int equal);
	//GraphTraversal eq(std::string equal);
	//GraphTraversal 

	// Finalizing steps; these don't do anything in anonymous GraphTraversals
	//boolean hasNext();
	virtual void* next() { return NULL; }
	virtual void forEachRemaining(std::function<void (void*)> func) {};
	virtual void iterate() {};
	//GraphTraversal toList();
	//GraphTraversal toSet();

	// Special additions
	GraphTraversal* appendStep(TraversalStep* step);
	void getInitialTraversal();
};

#endif