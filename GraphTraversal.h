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
#include "IdStep.h"
#include "AddEdgeStep.h"
#include "AddVertexStep.h"
#include "AddEdgeStartStep.h"
#include "AddVertexStartStep.h"
#include "AddPropertyStep.h"
#include "NoOpStep.h"
#include "Direction.h"
#include "HasStep.h"
#include "P.h"
#include "Direction.h"
#include "Scope.h"

#include "Vertex.h"

class Edge;
class Graph;

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

	GraphTraversal(GraphTraversal* trv) {
		this->steps = trv->getSteps();
		this->source = trv->getTraversalSource();
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

	GraphTraversal* appendStep(TraversalStep* step) {
		steps.push_back(step);
		return this;
	}

	// Steps
	GraphTraversal* addE(std::string label){
		return this->appendStep(new AddEdgeStep(label));
	}

	GraphTraversal* addV(std::string label) {
		return this->appendStep(new AddVertexStep(label));
	}

	GraphTraversal* addV() {
		return this->appendStep(new AddVertexStep());
	}

	GraphTraversal* property(std::string property_key, boost::any value) {
		return this->appendStep(new AddPropertyStep(property_key, value));
	}
	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	//GraphTraversal* as(std::string sideEffectLabel);
	//GraphTraversal* barrier();
	//GraphTraversal* by(GraphTraversal* byTraversal);
	//GraphTraversal* by(std::string label);
	//GraphTraversal* cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	//GraphTraversal<auto n> coalesce(std::vector<GraphTraversal<A>> traversals);
	//GraphTraversal* coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	//GraphTraversal* count();
	//GraphTraversal* cyclicPath();
	//GraphTraversal* dedup();
	//GraphTraversal* drop();
	//GraphTraversal* emit();
	//GraphTraversal emit(Predicate predicate);
	//GraphTraversal* emit(GraphTraversal* emitTraversal);
	//GraphTraversal* fold();
	//GraphTraversal* from(GraphTraversal* fromTraversal);

	GraphTraversal* from(std::string sideEffectLabel);

	GraphTraversal* from(Vertex* fromVertex);

	GraphTraversal* V() {
		return this->appendStep(new GraphStep(VERTEX, {}));
	}

	GraphTraversal* V(Vertex* vertex) {
		return this->appendStep(new GraphStep(VERTEX, {vertex->id()}));
	}

	GraphTraversal* V(std::vector<Vertex*> vertices) {
		std::vector<boost::any> ids;
		for(Vertex* v : vertices) ids.push_back(v->id());
		return this->appendStep(new GraphStep(VERTEX, ids));
	}

	//GraphTraversal* V(void* objects, size_t sizeOfEach, int length);
	//GraphTraversal group();
	//GraphTraversal group(std::string sideEffectLabel);
	//GraphTraversal groupCount();
	//GraphTraversal groupCount(std::string sideEffectLabel);
	//GraphTraversal has(std::string key, void* value, size_t size); // dangerous operation
	//GraphTraversal has(std::string label, std::string key, void* value, size_t size); // dangerous operation

	template<typename T>
	GraphTraversal* has(std::string key, std::function<bool(boost::any)> pred) {
		return this->appendStep(new HasStep(key, pred));
	}

	template<typename T>
	GraphTraversal* has(std::string key, T value) {
		return this->appendStep(new HasStep(key, P<T>::eq(value)));
	}

	template<typename T>
	GraphTraversal* has(std::string key) {
        return this->appendStep(new HasStep(key, nullptr));
	}

	//GraphTraversal* has(std::string key, GraphTraversal* valueTraversal);
	//GraphTraversal* has(std::string key);
	//GraphTraversal* hasNot(std::string key);
	//GraphTraversal* hasLabel(std::vector<std::string> labels);
	//GraphTraversal* hasLabel(std::string label);
	//GraphTraversal* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	//GraphTraversal* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	GraphTraversal* id() {
		return this->appendStep(new IdStep());
	};
	//GraphTraversal* identity();
	//GraphTraversal inject(void* object, size_t size);
	//GraphTraversal* is(void* val, size_t size);
	//GraphTraversal is(Predicate predicate);
	//GraphTraversal key();
	//GraphTraversal* label();
	//GraphTraversal* limit(unsigned long theLimit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	//GraphTraversal* local(GraphTraversal* localTraversal);
	//GraphTraversal* loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	//GraphTraversal* math(std::string equation);
	//GraphTraversal* max();
	//GraphTraversal max(Scope scope);
	//GraphTraversal* mean();
	//GraphTraversal mean(Scope scope);
	//GraphTraversal* min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
	//GraphTraversal* order();
	//GraphTraversal order(Scope scope);
	// pagerank step not supported
	//GraphTraversal* path();
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
	//GraphTraversal* sample(int sampleSize);
	//GraphTraversal sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal* select(std::string sideEffectLabel) {
		//TODO write this
	}
	//GraphTraversal select(std::vector<std::string> sideEffectLabels);
	//GraphTraversal select(GraphTraversal selectTraversal);
	//GraphTraversal* simplePath();
	//GraphTraversal* skip(unsigned long toSkip);
	//GraphTraversal skip(Scope scope, unsigned long toSkip);
	//GraphTraversal* store(std::string sideEffectLabel);
	//GraphTraversal subgraph(std::string sideEffectLabel);
	//GraphTraversal* sum();
	//GraphTraversal sum(Scope scope);
	//GraphTraversal tail();
	//GraphTraversal tail(unsigned long theLimit);
	//GraphTraversal tail(Scope scope);
	//GraphTraversal tail(Scope scope, unsigned long theLimit);
	//GraphTraversal* timeLimit(long time);
	//GraphTraversal* to(Direction direction, std::vector<std::string> labels);
	//GraphTraversal* to(Direction direction);
	//GraphTraversal* to(Direction direction, std::string label);
	//GraphTraversal* to(GraphTraversal* toTraversal); //MODULATOR for addE

	// MODULATOR for addE
	GraphTraversal* to(std::string sideEffectLabel);

	// MODULATOR for addE
	GraphTraversal* to(Vertex* toVertex);

	//GraphTraversal* toV(Direction direction);
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

	GraphTraversal* both() {
		return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
	}

	GraphTraversal* both(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
	}

	GraphTraversal* bothE() {
		return this->appendStep(new VertexStep(BOTH, {}, EDGE));
	}

	GraphTraversal* bothE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, EDGE));
	}

	//GraphTraversal* bothV();
	//GraphTraversal* inV();
	//GraphTraversal* otherV();

	GraphTraversal* out() {
		return this->appendStep(new VertexStep(OUT, {}, VERTEX));
	}

	GraphTraversal* out(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, VERTEX));
	}

	GraphTraversal* in() {
		return this->appendStep(new VertexStep(IN, {}, VERTEX));
	}

	GraphTraversal* in(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(IN, labels, VERTEX));
	}

	GraphTraversal* outE() {
		return this->appendStep(new VertexStep(OUT, {}, EDGE));
	}

	GraphTraversal* outE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, EDGE));
	}

	GraphTraversal* inE() {
		return this->appendStep(new VertexStep(IN, {}, EDGE));
	}

	GraphTraversal* inE(std::vector<std::string> labels) {
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

	void getInitialTraversal();

	// The explain finalizer which works in anonymous GraphTraversals
	std::string explain() {
		this->getInitialTraversal();

		std::string explanation = "GraphTraversal {\n";
		for(int k = 0; k < steps.size(); k++) explanation += steps[k]->getInfo() + "\n";

		return explanation + "}";
	}

	// Finalizing steps; these don't do anything in anonymous GraphTraversals
	//boolean hasNext();
	virtual boost::any next() { return NULL; }
	virtual void forEachRemaining(std::function<void(boost::any&)> func) {};
	virtual void iterate() {};
	//std::vector<W*> toVector();
	//GraphTraversal toSet();
};

#define __ (new GraphTraversal())

#include "FromStep.h"
#include "ToStep.h"

/*
	In general this should be called by the finalization steps in
	classes that extend GraphTraversal.
*/
void GraphTraversal::getInitialTraversal() {
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
							std::cout << "adding the to step\n";
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

GraphTraversal* GraphTraversal::from(std::string sideEffectLabel) {
	// Because from() uses void* (sigh) this awkward memory copy is necessary.
	const char* base_string = sideEffectLabel.c_str();
	size_t size = (1 + strlen(base_string));

	char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
	strncpy(sideEffectLabel_cpy, base_string, size);

	return this->appendStep(new FromStep(sideEffectLabel_cpy));
}

GraphTraversal* GraphTraversal::from(Vertex* fromVertex) {
	return this->appendStep(new FromStep(fromVertex));
}

// MODULATOR for addE
GraphTraversal* GraphTraversal::to(std::string sideEffectLabel) {
	// Because to() uses void* (sigh) this awkward memory copy is necessary.
	const char* base_string = sideEffectLabel.c_str();
	size_t size = (1 + strlen(base_string));

	char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
	strncpy(sideEffectLabel_cpy, base_string, size);

	return this->appendStep(new ToStep(sideEffectLabel_cpy));
}

// MODULATOR for addE
GraphTraversal* GraphTraversal::to(Vertex* toVertex) {
	return this->appendStep(new ToStep(toVertex));
}

#endif
