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

template<typename U, typename W>
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
	GraphTraversal<U, Edge>* addE(std::string label);
	GraphTraversal<U,W>* addV(std::string label);
	GraphTraversal<U,W>* addV();
	GraphTraversal<U,W>* property(std::string label, void* value, size_t size);
	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	GraphTraversal<U,W>* as(std::string sideEffectLabel);
	GraphTraversal<U,W>* barrier();
	GraphTraversal<U,W>* by(GraphTraversal<U,W>* byTraversal);
	GraphTraversal<U,W>* by(std::string label);
	GraphTraversal<U,W>* cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	//GraphTraversal<auto n> coalesce(std::vector<GraphTraversal<A>> traversals);
	GraphTraversal<U,W>* coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	GraphTraversal<U,W>* count();
	GraphTraversal<U,W>* cyclicPath();
	GraphTraversal<U,W>* dedup();
	GraphTraversal<U,W>* drop();
	GraphTraversal<U,W>* emit();
	//GraphTraversal emit(Predicate predicate);
	GraphTraversal<U,W>* emit(GraphTraversal<U,W>* emitTraversal);
	std::string explain();
	GraphTraversal<U,W>* fold();
	GraphTraversal<U,W>* from(std::string sideEffectLabel);
	GraphTraversal<U,W>* from(GraphTraversal<U,W>* fromTraversal);
	GraphTraversal<U,W>* from(Vertex* fromVertex);
	GraphTraversal<U,Vertex>* V();
	GraphTraversal<U,Vertex>* V(Vertex* vertex);
	GraphTraversal<U,Vertex>* V(std::vector<Vertex*> vertices);
	//GraphTraversal<U,W>* V(void* objects, size_t sizeOfEach, int length);
	//GraphTraversal group();
	//GraphTraversal group(std::string sideEffectLabel);
	//GraphTraversal groupCount();
	//GraphTraversal groupCount(std::string sideEffectLabel);
	//GraphTraversal has(std::string key, void* value, size_t size); // dangerous operation
	//GraphTraversal has(std::string label, std::string key, void* value, size_t size); // dangerous operation
	template<typename T> GraphTraversal<U,W>* has(std::string key, P<T> predicate);
	GraphTraversal<U,W>* has(std::string key, int value);
	GraphTraversal<U,W>* has(std::string key, std::string value);

	GraphTraversal<U,W>* has(std::string key, GraphTraversal<U,W>* valueTraversal);
	GraphTraversal<U,W>* has(std::string key);
	GraphTraversal<U,W>* hasNot(std::string key);
	GraphTraversal<U,W>* hasLabel(std::vector<std::string> labels);
	GraphTraversal<U,W>* hasLabel(std::string label);
	GraphTraversal<U,W>* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	GraphTraversal<U,W>* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	//GraphTraversal<auto n> id();
	GraphTraversal<U,W>* identity();
	//GraphTraversal inject(void* object, size_t size);
	GraphTraversal<U,W>* is(void* val, size_t size);
	//GraphTraversal is(Predicate predicate);
	//GraphTraversal key();
	GraphTraversal<U,W>* label();
	GraphTraversal<U,W>* limit(unsigned long theLimit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	GraphTraversal<U,W>* local(GraphTraversal<U,W>* localTraversal);
	GraphTraversal<U,W>* loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	GraphTraversal<U,W>* math(std::string equation);
	GraphTraversal<U,W>* max();
	//GraphTraversal max(Scope scope);
	GraphTraversal<U,W>* mean();
	//GraphTraversal mean(Scope scope);
	GraphTraversal<U,W>* min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
	GraphTraversal<U,W>* order();
	//GraphTraversal order(Scope scope);
	// pagerank step not supported
	GraphTraversal<U,W>* path();
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
	GraphTraversal<U,W>* sample(int sampleSize);
	//GraphTraversal sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal<U,W>* select(std::string sideEffectLabel);
	//GraphTraversal select(std::vector<std::string> sideEffectLabels);
	//GraphTraversal select(GraphTraversal selectTraversal);
	GraphTraversal<U,W>* simplePath();
	GraphTraversal<U,W>* skip(unsigned long toSkip);
	//GraphTraversal skip(Scope scope, unsigned long toSkip);
	GraphTraversal<U,W>* store(std::string sideEffectLabel);
	//GraphTraversal subgraph(std::string sideEffectLabel);
	GraphTraversal<U,W>* sum();
	//GraphTraversal sum(Scope scope);
	//GraphTraversal tail();
	//GraphTraversal tail(unsigned long theLimit);
	//GraphTraversal tail(Scope scope);
	//GraphTraversal tail(Scope scope, unsigned long theLimit);
	GraphTraversal<U,W>* timeLimit(long time);
	GraphTraversal<U,W>* to(Direction direction, std::vector<std::string> labels);
	GraphTraversal<U,W>* to(Direction direction);
	GraphTraversal<U,W>* to(Direction direction, std::string label);
	GraphTraversal<U,W>* to(std::string sideEffectLabel); // modulator for addE
	GraphTraversal<U,W>* to(GraphTraversal<U,W>* toTraversal); //modulator for addE
	GraphTraversal<U,W>* to(Vertex* toVertex); //modulator for addE
	GraphTraversal<U,W>* toV(Direction direction);
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
	GraphTraversal<U,W>* both();
	GraphTraversal<U,W>* both(std::vector<std::string> edgeLabels);
	GraphTraversal<U,W>* bothE();
	GraphTraversal<U,W>* bothE(std::vector<std::string> edgeLabels);
	GraphTraversal<U,W>* bothV();
	GraphTraversal<U,W>* inV();
	GraphTraversal<U,W>* otherV();
	GraphTraversal<U,W>* out();
	GraphTraversal<U,W>* out(std::vector<std::string> edgeLabels);
	GraphTraversal<U,W>* in();
	GraphTraversal<U,W>* in(std::vector<std::string> edgeLabels);
	GraphTraversal<U,W>* outE();
	GraphTraversal<U,W>* outE(std::vector<std::string> edgeLabels);
	GraphTraversal<U,W>* inE();
	GraphTraversal<U,W>* inE(std::vector<std::string> edgeLabels);
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
	GraphTraversal<U,W>* appendStep(TraversalStep* step);
	void getInitialTraversal();
};

#endif