#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include "TraversalStep.h"
#include "Direction.h"
#include "Scope.h"
#include <string>
#include <vector>

class Graph;
class Vertex;
class Edge;
class GraphTraversalSource;

template <typename T>
class GraphTraversal {
private:
	GraphTraversalSource* source;
	std::vector<TraversalStep> steps;
public:
	GraphTraversal<Vertex>(GraphTraversalSource* src);
	Graph* getGraph();
	GraphTraversalSource* getTraversalSource();
	
	// Steps
	GraphTraversal<Edge> addE(std::string label);
	GraphTraversal<Vertex> addV(std::string label);
	GraphTraversal<Vertex> property(std::string label, void* value, size_t size);
	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	GraphTraversal<T> as(std::string sideEffectLabel);
	GraphTraversal<T> barrier();
	GraphTraversal<T> by(GraphTraversal byTraversal);
	GraphTraversal<T> by(std::string label);
	GraphTraversal<T> cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	//GraphTraversal<auto n> coalesce(std::vector<GraphTraversal<A>> traversals);
	GraphTraversal<T> coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	GraphTraversal<long> count();
	GraphTraversal<T> cyclicPath();
	GraphTraversal<T> dedup();
	GraphTraversal<T> drop();
	GraphTraversal<T> emit();
	//GraphTraversal emit(Predicate predicate);
	GraphTraversal<T> emit(GraphTraversal emitTraversal);
	std::string explain();
	GraphTraversal<std::vector<T>> fold();
	GraphTraversal<T> from(std::string sideEffectLabel);
	GraphTraversal<T> from(GraphTraversal fromTraversal);
	GraphTraversal<T> from(Vertex fromVertex);
	GraphTraversal<Vertex> V();
	GraphTraversal<Vertex> V(void* objects, size_t sizeOfEach, int length);
	//GraphTraversal group();
	//GraphTraversal group(std::string sideEffectLabel);
	//GraphTraversal groupCount();
	//GraphTraversal groupCount(std::string sideEffectLabel);
	GraphTraversal<T> has(std::string key, void* value, size_t size); // dangerous operation
	GraphTraversal<T> has(std::string label, std::string key, void* value, size_t size); // dangerous operation
	//GraphTraversal has(std::string key, Predicate predicate);
	GraphTraversal<T> has(std::string key, GraphTraversal<void*> valueTraversal);
	GraphTraversal<T> has(std::string key);
	GraphTraversal<T> hasNot(std::string key);
	GraphTraversal<T> hasLabel(std::vector<std::string> labels);
	GraphTraversal<T> hasLabel(std::string label);
	GraphTraversal<T> hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	GraphTraversal<T> hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	//GraphTraversal<auto n> id();
	GraphTraversal<T> identity();
	//GraphTraversal inject(void* object, size_t size);
	GraphTraversal<T> is(T val);
	//GraphTraversal is(Predicate predicate);
	//GraphTraversal key();
	GraphTraversal<std::string> label();
	GraphTraversal<T> limit(unsigned long theLimit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	GraphTraversal<void*> local(GraphTraversal<void*> localTraversal);
	GraphTraversal<unsigned long> loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	GraphTraversal<double> math(std::string equation);
	GraphTraversal<double> max();
	//GraphTraversal max(Scope scope);
	GraphTraversal<double> mean();
	//GraphTraversal mean(Scope scope);
	GraphTraversal<double> min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal<auto n> _or(std::vector<GraphTraversal<auto m>> orTraversals);
	GraphTraversal<T> order();
	//GraphTraversal order(Scope scope);
	// pagerank step not supported
	GraphTraversal<std::vector<void*>> path();
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
	GraphTraversal<T> sample(int sampleSize);
	//GraphTraversal<T> sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal<void*> select(std::string sideEffectLabel);
	//GraphTraversal select(std::vector<std::string> sideEffectLabels);
	//GraphTraversal select(GraphTraversal selectTraversal);
	GraphTraversal<T> simplePath();
	GraphTraversal<T> skip(unsigned long toSkip);
	//GraphTraversal skip(Scope scope, unsigned long toSkip);
	GraphTraversal<T> store(std::string sideEffectLabel);
	//GraphTraversal subgraph(std::string sideEffectLabel);
	GraphTraversal<double> sum();
	//GraphTraversal<double> sum(Scope scope);
	//GraphTraversal tail();
	//GraphTraversal tail(unsigned long theLimit);
	//GraphTraversal tail(Scope scope);
	//GraphTraversal tail(Scope scope, unsigned long theLimit);
	GraphTraversal<T> timeLimit(long time);
	GraphTraversal<Vertex> to(Direction direction, std::vector<std::string> labels);
	GraphTraversal<Vertex> to(Direction direction);
	GraphTraversal<Vertex> to(GraphTraversal toTraversal);
	GraphTraversal<Vertex> to(Vertex toVertex);
	GraphTraversal<Vertex> to(Direction direction, std::string label);
	GraphTraversal<Edge> toV(Direction direction);
	//GraphTraversal tree(std::string sideEffectLabel);
	//GraphTraversal tree();
	//GraphTraversal<auto n> unfold();
	//GraphTraversal _union(std::vector<GraphTraversal> unionTraversals);
	//GraphTraversal until(Predicate predicate);
	//GraphTraversal<T> until(GraphTraversal untilTraversal);
	//GraphTraversal<auto n> value();
	//GraphTraversal valueMap();
	//GraphTraversal valueMap(std::vector<std::string> labels);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue, std::vector<std::string> labels);
	//GraphTraversal<std::vector<auto n>> values();
	//GraphTraversal<std::vector<auto n>> values(std::vector<std::string> labels);
	GraphTraversal<Vertex> both();
	GraphTraversal<Vertex> both(std::vector<std::string> edgeLabels);
	GraphTraversal<Edge> bothE();
	GraphTraversal<Edge> bothE(std::vector<std::string> edgeLabels);
	GraphTraversal<Vertex> bothV();
	GraphTraversal<Vertex> inV();
	GraphTraversal<Vertex> otherV();
	GraphTraversal<Vertex> out();
	GraphTraversal<Vertex> out(std::vector<std::string> edgeLabels);
	GraphTraversal<Edge> outE();
	GraphTraversal<Edge> outE(std::vector<std::string> edgeLabels);
	GraphTraversal<Edge> inE();
	GraphTraversal<Edge> inE(std::vector<std::string> edgeLabels);
	//GraphTraversal where(Predicate predicate);
	//GraphTraversal where(std::string label, Predicate predicate);
	//GraphTraversal<T> where(GraphTraversal<auto n> whereTraversal);
	
	// These may replace predicates...
	//GraphTraversal lt(double max_exclusive);
	//GraphTraversal gt(double min_exculsive);
	//GraphTraversal eq(double equal, double tolerance);
	//GraphTraversal eq(long equal);
	//GraphTraversal eq(int equal);
	//GraphTraversal eq(std::string equal);
	//GraphTraversal 
};

#endif