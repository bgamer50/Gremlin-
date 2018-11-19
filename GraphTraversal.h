#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>

#include "TraversalStep.h"
#include "GraphTraversalSource.h"
#include "VertexStep.h"
#include "AddEdgeStep.h"
#include "AddVertexStep.h"
#include "AddEdgeStartStep.h"
#include "AddVertexStartStep.h"
#include "AddPropertyStep.h"
#include "NoOpStep.h"
#include "Direction.h"
#include "HasStep.h"
#include "FromStep.h"
#include "ToStep.h"
#include "P.h"
#include "Direction.h"
#include "Scope.h"

#include "Vertex.h"

class Edge;
class Graph;

template<typename U, typename W>
class GraphTraversal {
protected:
	std::vector<TraversalStep*> steps;
private:
	GraphTraversalSource* source;
public:
	/*
		The given traversal source is allowed to be null, in the case of an
		anomymous traversal.
	*/
	GraphTraversal(GraphTraversalSource* src) {
		source = src;
	}

	GraphTraversal() {
		source = NULL;
	}

	GraphTraversal(GraphTraversal<void*,void*>* trv) {
		this->steps = ((GraphTraversal<U, W>*)trv).getSteps();
		this->source = ((GraphTraversal<U, W>*)trv)->getTraversalSource;
	}

	Graph* getGraph() {
		return (*source).getGraph();
	}


	GraphTraversalSource* getTraversalSource() {
		return source;
	}

	std::vector<TraversalStep*> getSteps() {
		return this->steps;
	}

	GraphTraversal<U,W>* appendStep(TraversalStep* step) {
		steps.push_back(step);
		return this;
	}
	
	// Steps
	GraphTraversal<U, Edge>* addE(std::string label){ 
		return (GraphTraversal<U, Edge>*)this->appendStep(new AddEdgeStep(label));
	}

	GraphTraversal<U,Vertex>* addV(std::string label) {
		return this->appendStep(new AddVertexStep(label));
	}
	
	GraphTraversal<U,Vertex>* addV() {
		return this->appendStep(new AddVertexStep());
	}

	template<typename T>
	GraphTraversal<U, W>* property(std::string property_key, T value) {
		return this->appendStep(new AddPropertyStep<T>(property_key, value));
	}
	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	//GraphTraversal<U,W>* as(std::string sideEffectLabel);
	//GraphTraversal<U,W>* barrier();
	//GraphTraversal<U,W>* by(GraphTraversal<U,W>* byTraversal);
	//GraphTraversal<U,W>* by(std::string label);
	//GraphTraversal<U,W>* cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	//GraphTraversal<auto n> coalesce(std::vector<GraphTraversal<A>> traversals);
	//GraphTraversal<U,W>* coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	//GraphTraversal<U,W>* count();
	//GraphTraversal<U,W>* cyclicPath();
	//GraphTraversal<U,W>* dedup();
	//GraphTraversal<U,W>* drop();
	//GraphTraversal<U,W>* emit();
	//GraphTraversal emit(Predicate predicate);
	//GraphTraversal<U,W>* emit(GraphTraversal<U,W>* emitTraversal);
	//GraphTraversal<U,W>* fold();
	//GraphTraversal<U,W>* from(GraphTraversal<U,W>* fromTraversal);

	GraphTraversal<U,W>* from(std::string sideEffectLabel) {
		// Because from() uses void* (sigh) this awkward memory copy is necessary.
		const char* base_string = sideEffectLabel.c_str();
		size_t size = (1 + strlen(base_string));

		char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
		strncpy(sideEffectLabel_cpy, base_string, size);

		return this->appendStep(new FromStep(sideEffectLabel_cpy));
	}

	GraphTraversal<U,W>* from(Vertex* fromVertex) {
		return this->appendStep(new FromStep(fromVertex));
	}

	GraphTraversal<U,Vertex>* V() {
		return this->appendStep(new GraphStep(VERTEX, {}));
	}

	GraphTraversal<U,Vertex>* V(Vertex* vertex) {
		return (GraphTraversal<U, Vertex>*)this->appendStep(new GraphStep(VERTEX, {(void*)vertex->id()}));
	}

	GraphTraversal<U,Vertex>* V(std::vector<Vertex*> vertices) {
		std::vector<void*> ids;
		for(std::vector<Vertex*>::iterator v = vertices.begin(); v != vertices.end(); v++) {
			void* id = (void*)((*v)->id());
			ids.push_back(id);
		}
		return this->appendStep(new GraphStep(VERTEX, ids));
	}

	//GraphTraversal<U,W>* V(void* objects, size_t sizeOfEach, int length);
	//GraphTraversal group();
	//GraphTraversal group(std::string sideEffectLabel);
	//GraphTraversal groupCount();
	//GraphTraversal groupCount(std::string sideEffectLabel);
	//GraphTraversal has(std::string key, void* value, size_t size); // dangerous operation
	//GraphTraversal has(std::string label, std::string key, void* value, size_t size); // dangerous operation
	template <typename T>
	GraphTraversal<U,W>* has(std::string key, P<T> pred) {
		return this->appendStep(new HasStep<T>(key, pred));
	}

	GraphTraversal<U,W>* has(std::string key, int value) {
		return this->appendStep(new HasStep<int>(key, new P<int>(EQ, value, value)));
	}

	GraphTraversal<U,W>* has(std::string key, std::string value) {
		return this->appendStep(new HasStep<std::string>(key, new P<std::string>(EQ, value, value)));
	}

	//GraphTraversal<U,W>* has(std::string key, GraphTraversal<U,W>* valueTraversal);
	//GraphTraversal<U,W>* has(std::string key);
	//GraphTraversal<U,W>* hasNot(std::string key);
	//GraphTraversal<U,W>* hasLabel(std::vector<std::string> labels);
	//GraphTraversal<U,W>* hasLabel(std::string label);
	//GraphTraversal<U,W>* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	//GraphTraversal<U,W>* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	//GraphTraversal<auto n> id();
	//GraphTraversal<U,W>* identity();
	//GraphTraversal inject(void* object, size_t size);
	//GraphTraversal<U,W>* is(void* val, size_t size);
	//GraphTraversal is(Predicate predicate);
	//GraphTraversal key();
	//GraphTraversal<U,W>* label();
	//GraphTraversal<U,W>* limit(unsigned long theLimit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	//GraphTraversal<U,W>* local(GraphTraversal<U,W>* localTraversal);
	//GraphTraversal<U,W>* loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	//GraphTraversal<U,W>* math(std::string equation);
	//GraphTraversal<U,W>* max();
	//GraphTraversal max(Scope scope);
	//GraphTraversal<U,W>* mean();
	//GraphTraversal mean(Scope scope);
	//GraphTraversal<U,W>* min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
	//GraphTraversal<U,W>* order();
	//GraphTraversal order(Scope scope);
	// pagerank step not supported
	//GraphTraversal<U,W>* path();
	// peerpressure step not supported
	//std::string profile();
	//GraphTraversal project(std::vector<std::string> sideEffectLabels);
	// program step not supported
	//GraphTraversal properties(std::vector<std::string> labels);
	//GraphTraversal properties();
	//GraphTraversal propertyMap(std::vector<std::string> labels);
	//GraphTraversal propertyMap();
	//GraphTraversal range(long low, long high);
	//GraphTraversal repeat(GraphTraversal repeatTraversal);
	// sack step not supported
	//GraphTraversal<U,W>* sample(int sampleSize);
	//GraphTraversal sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal<U,W>* select(std::string sideEffectLabel) {
		//TODO write this
	}	
	//GraphTraversal select(std::vector<std::string> sideEffectLabels);
	//GraphTraversal select(GraphTraversal selectTraversal);
	//GraphTraversal<U,W>* simplePath();
	//GraphTraversal<U,W>* skip(unsigned long toSkip);
	//GraphTraversal skip(Scope scope, unsigned long toSkip);
	//GraphTraversal<U,W>* store(std::string sideEffectLabel);
	//GraphTraversal subgraph(std::string sideEffectLabel);
	//GraphTraversal<U,W>* sum();
	//GraphTraversal sum(Scope scope);
	//GraphTraversal tail();
	//GraphTraversal tail(unsigned long theLimit);
	//GraphTraversal tail(Scope scope);
	//GraphTraversal tail(Scope scope, unsigned long theLimit);
	//GraphTraversal<U,W>* timeLimit(long time);
	//GraphTraversal<U,W>* to(Direction direction, std::vector<std::string> labels);
	//GraphTraversal<U,W>* to(Direction direction);
	//GraphTraversal<U,W>* to(Direction direction, std::string label);
	//GraphTraversal<U,W>* to(GraphTraversal<U,W>* toTraversal); //MODULATOR for addE

	// MODULATOR for addE
	GraphTraversal<U,W>* to(std::string sideEffectLabel) {
		// Because to() uses void* (sigh) this awkward memory copy is necessary.
		const char* base_string = sideEffectLabel.c_str();
		size_t size = (1 + strlen(base_string));

		char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
		strncpy(sideEffectLabel_cpy, base_string, size);

		return this->appendStep(new ToStep(sideEffectLabel_cpy));
	}

	// MODULATOR for addE
	GraphTraversal<U,W>* to(Vertex* toVertex) {
		return this->appendStep(new ToStep(toVertex));
	}

	//GraphTraversal<U,W>* toV(Direction direction);
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

	GraphTraversal<U,W>* both() {
		return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
	}

	GraphTraversal<U,W>* both(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
	}

	GraphTraversal<U,W>* bothE() {
		return this->appendStep(new VertexStep(BOTH, {}, EDGE));
	}

	GraphTraversal<U,W>* bothE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, EDGE));
	}

	//GraphTraversal<U,W>* bothV();
	//GraphTraversal<U,W>* inV();
	//GraphTraversal<U,W>* otherV();

	GraphTraversal<U,W>* out() {
		return this->appendStep(new VertexStep(OUT, {}, VERTEX));
	}

	GraphTraversal<U,W>* out(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, VERTEX));
	}

	GraphTraversal<U,W>* in() {
		return this->appendStep(new VertexStep(IN, {}, VERTEX));
	}

	GraphTraversal<U,W>* in(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(IN, labels, VERTEX));
	}

	GraphTraversal<U,W>* outE() {
		return this->appendStep(new VertexStep(OUT, {}, EDGE));
	}

	GraphTraversal<U,W>* outE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, EDGE));
	}

	GraphTraversal<U,W>* inE() {
		return this->appendStep(new VertexStep(IN, {}, EDGE));
	}

	GraphTraversal<U,W>* inE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(IN, labels, EDGE));
	}

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

	// The explain finalizer which works in anonymous GraphTraversals
	std::string explain() {
		this->getInitialTraversal();
		std::string explanation = "GraphTraversal {\n";
		for(int k = 0; k < steps.size(); k++) explanation += steps[k]->getInfo() + "\n";

		return explanation + "}";
	}

	// Finalizing steps; these don't do anything in anonymous GraphTraversals
	//boolean hasNext();
	virtual W* next() { return NULL; }
	virtual void forEachRemaining(std::function<void (W*)> func) {};
	virtual void iterate() {};
	//std::vector<W*> toVector();
	//GraphTraversal toSet();

	/*
		In general this should be called by the finalization steps in
		classes that extend GraphTraversal.
	*/
	void getInitialTraversal() {
		for(int k = 0; k < steps.size(); k++) {
			TraversalStep* currentStep = steps[k];
			switch(currentStep->uid) {
				case ADD_EDGE_STEP: {
					AddEdgeStep* aes = (AddEdgeStep*)currentStep;
					if(k + 1 < steps.size()) {
						if(steps[k + 1]->uid == FROM_STEP) {
							aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						else if(steps[k + 1]->uid == TO_STEP) {
							aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						if(k + 1 < steps.size()) {
							if(steps[k + 1]->uid == FROM_STEP) {
								aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
								delete steps[k + 1];
								steps[++k] = new NoOpStep();
							}
							else if(steps[k + 1]->uid == TO_STEP) {
								aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
								delete steps[k + 1];
								steps[++k] = new NoOpStep();
							}
						}
					}
					break;
				}
				case ADD_EDGE_START_STEP: {
					AddEdgeStartStep* aes = (AddEdgeStartStep*)currentStep;
					if(k + 1 < steps.size()) {
						if(steps[k + 1]->uid == FROM_STEP) {
							aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						else if(steps[k + 1]->uid == TO_STEP) {
							aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						if(k + 1 < steps.size()) {
							if(steps[k + 1]->uid == FROM_STEP) {
								aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
								delete steps[k + 1];
								steps[++k] = new NoOpStep();
							}
							else if(steps[k + 1]->uid == TO_STEP) {
								aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
								delete steps[k + 1];
								steps[++k] = new NoOpStep();
							}
						}
					}
					break;
				}
			}	
		}
	}
};

#define __ (new GraphTraversal<void*, void*>())

template<typename T>
inline P<T>* eq(T t) { return new P<T>(EQ, t, NULL); }

template<typename T>
inline P<T>* lt(T t) { return new P<T>(LT, t, NULL); }

template<typename T>
inline P<T>* gt(T t) { return new P<T>(GT, t, NULL); }

template<typename T>
inline P<T>* gte(T t) { return new P<T>(GTE, t, NULL); }

template<typename T>
inline P<T>* lte(T t) { return new P<T>(LTE, t, NULL); }

template<typename T>
inline P<T>* bt(T t0, T t1) { return new P<T>(LTE, t0, t1); }

#endif