#ifndef GRAPH_TRAVERSAL_H
#define GRAPH_TRAVERSAL_H

#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <iostream>
#include <typeindex>
#include <unordered_map>
#include <unordered_set>

#include "structure/Direction.h"
#include "traversal/P.h"
#include "structure/Direction.h"
#include "traversal/Scope.h"

class Edge;
class Vertex;
class TraversalStep;
class Graph;
class GraphTraversalSource;
class Traverser;

class GraphTraversal {
protected:
	std::vector<TraversalStep*> steps;
	std::vector<Traverser> traversers;
private:
	GraphTraversalSource* source;
public:
	/*
		The "default" constructor.
	*/
	GraphTraversal();

	/*
		The given traversal source is allowed to be null, in the case of an
		anomymous traversal.
	*/
	GraphTraversal(GraphTraversalSource* src);
	GraphTraversal(GraphTraversal* trv);
	GraphTraversal(GraphTraversalSource* src, GraphTraversal* trv);

	Graph* getGraph();


	GraphTraversalSource* getTraversalSource();

	std::vector<TraversalStep*>& getSteps() {
		return this->steps;
	}

	GraphTraversal* appendStep(TraversalStep* step) {
		this->steps.push_back(step);
		return this;
	}

	GraphTraversal* insertStep(size_t k, TraversalStep* step) {
		this->steps.insert(steps.begin() + k, step);
		return this;
	}

	// Steps
	GraphTraversal* addE(std::string label);

	GraphTraversal* addV(std::string label);

	GraphTraversal* addV();

	GraphTraversal* property(std::string property_key, boost::any value);

	//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
	//GraphTraversal<auto n> _and();
	//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
	
	GraphTraversal* as(std::string sideEffectLabel);
	
	//GraphTraversal* barrier();
	GraphTraversal* by(boost::any arg);
	//GraphTraversal* cap(std::vector<std::string> sideEffectLabels);
	//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
	//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
	
	GraphTraversal* coalesce(std::vector<GraphTraversal*> traversals);
	//GraphTraversal* coin(float chance);
	//GraphTraversal constant(void* value, size_t size);
	GraphTraversal* count();
	//GraphTraversal* cyclicPath();
	GraphTraversal* dedup();
	//GraphTraversal* drop();
	GraphTraversal* emit();
	//GraphTraversal emit(Predicate predicate);
	GraphTraversal* emit(GraphTraversal* emitTraversal);
	GraphTraversal* fold();
	//GraphTraversal* from(GraphTraversal* fromTraversal);

	GraphTraversal* from(std::string sideEffectLabel);

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

	GraphTraversal* has(std::string key, P pred);

	GraphTraversal* has(std::string key, boost::any value);

	GraphTraversal* has(std::string key);

	//GraphTraversal* has(std::string key, GraphTraversal* valueTraversal);
	//GraphTraversal* has(std::string key);
	//GraphTraversal* hasNot(std::string key);
	//GraphTraversal* hasLabel(std::vector<std::string> labels);
	//GraphTraversal* hasLabel(std::string label);
	//GraphTraversal* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
	//GraphTraversal* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
	
	GraphTraversal* id();

	GraphTraversal* identity();
	GraphTraversal* inject(std::vector<boost::any> objects);
	GraphTraversal* is(boost::any val);
	GraphTraversal* is(P predicate);
	//GraphTraversal key();
	//GraphTraversal* label();
	GraphTraversal* limit(uint64_t the_limit);
	//GraphTraversal limit(Scope scope, unsigned long theLimit);
	//GraphTraversal* local(GraphTraversal* localTraversal);
	//GraphTraversal* loops();
	//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
	//GraphTraversal* math(std::string equation);
	//GraphTraversal* max();
	//GraphTraversal max(Scope scope);
	//GraphTraversal* mean();
	//GraphTraversal mean(Scope scope);
	
	GraphTraversal* min(std::function<int(Traverser&, Traverser&)> c);

	GraphTraversal* min();
	//GraphTraversal min(Scope scope);
	//GraphTraversal _not(GraphTraversal notTraversal);
	//GraphTraversal option(GraphTraversal optionTraversal);
	//GraphTraversal optional(GraphTraversal OptionalTraversal);
	//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
	GraphTraversal* order();
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
	GraphTraversal* repeat(GraphTraversal* repeatTraversal);
	// sack step not supported
	//GraphTraversal* sample(int sampleSize);
	//GraphTraversal sample(Scope scope, int sampleSize);
	// single-label select is special
	GraphTraversal* select(std::string sideEffectLabel);
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
	GraphTraversal* unfold();
	//GraphTraversal _union(std::vector<GraphTraversal> unionTraversals);
	//GraphTraversal until(Predicate predicate);
	GraphTraversal* until(GraphTraversal* untilTraversal);
	//GraphTraversal value();
	//GraphTraversal valueMap();
	GraphTraversal* valueMap(std::vector<std::string> labels);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue);
	//GraphTraversal valueMap(bool includeIdLabelKeyValue, std::vector<std::string> labels);
	//GraphTraversal values();
	GraphTraversal* values(std::vector<std::string> labels);

	GraphTraversal* values(std::string label);

	GraphTraversal* both();
	GraphTraversal* both(std::vector<std::string> labels);
	GraphTraversal* bothE();
	GraphTraversal* bothE(std::vector<std::string> labels);
	//GraphTraversal* bothV();
	//GraphTraversal* inV();
	//GraphTraversal* otherV();
	GraphTraversal* out();
	GraphTraversal* out(std::vector<std::string> labels);
	GraphTraversal* in();
	GraphTraversal* in(std::vector<std::string> labels);
	GraphTraversal* outE();
	GraphTraversal* outE(std::vector<std::string> labels);
	GraphTraversal* inE();
	GraphTraversal* inE(std::vector<std::string> labels);

	//GraphTraversal where(Predicate predicate);
	/**
	 * Used for comparison of two objects stored as side effects.
	 * TODO Current implementation is incorrect; used only as a temporary timesaver
	 * **/
	GraphTraversal* where(std::string label, P predicate);
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
	void setInitialTraversers(std::vector<Traverser> initial_traversers);

	// The explain finalizer which works in anonymous GraphTraversals
	std::string explain();

	// Finalizing steps

	// TODO; this is a really bad implementation of hasNext but will likely be changed in the Traverser refactor.
	bool hasNext() {
		return !this->toVector().empty();
	}

	std::vector<boost::any> toVector() {
		std::vector<boost::any> results;
		this->forEachRemaining([&](boost::any& a){results.push_back(a);});
		return results;
	}

	std::list<boost::any> toList() {
		std::list<boost::any> results;
		this->forEachRemaining([&](boost::any& a) {
			results.push_back(a);
		});
		return results;
	}

	boost::any next() { 
		return this->toVector()[0];
	}

	void forEachRemaining(std::function<void(boost::any&)> func);

	void iterate();

	std::vector<Traverser> getTraversers();

	//GraphTraversal toSet();
};

#ifndef __
#define __ (new GraphTraversal())
#endif

#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

/*
	The "default" constructor.
*/
GraphTraversal::GraphTraversal() {
	source = NULL;
}

#include "traversal/GraphTraversalSource.h"
/*
	The given traversal source is allowed to be null, in the case of an
	anomymous traversal.
*/
GraphTraversal::GraphTraversal(GraphTraversalSource* src) : GraphTraversal() {
	source = src;
}

#include "step/TraversalStep.h"
GraphTraversal::GraphTraversal(GraphTraversal* trv) : GraphTraversal() {
	this->steps = trv->getSteps();
	this->source = trv->getTraversalSource();
}

GraphTraversal::GraphTraversal(GraphTraversalSource* src, GraphTraversal* trv) {
	this->steps = trv->getSteps();
	this->source = src;
}

Graph* GraphTraversal::getGraph() {
	return (*source).getGraph();
}


GraphTraversalSource* GraphTraversal::getTraversalSource() {
	return source;
}

/*
	In general this should be called by the finalization steps in
	classes that extend GraphTraversal.
*/
void GraphTraversal::getInitialTraversal() {
	// Apply each strategy to this traversal's traversers.
	std::for_each(this->source->getStrategies().begin(), this->source->getStrategies().end(), [this](TraversalStrategy strategy) {
		strategy(this->steps);
	});
}

/*

*/
void GraphTraversal::setInitialTraversers(TraverserSet initial_traversers) {
	this->traversers.clear();
	this->traversers.insert(this->traversers.begin(), initial_traversers.begin(), initial_traversers.end());
}

#include "step/edge/AddEdgeStartStep.h"
#include "step/vertex/AddVertexStartStep.h"
#include "step/logic/NoOpStep.h"


#include "step/edge/AddEdgeStep.h"
GraphTraversal* GraphTraversal::addE(std::string label){
	return this->appendStep(new AddEdgeStep(label));
}

#include "step/vertex/AddVertexStep.h"
GraphTraversal* GraphTraversal::addV(std::string label) {
	return this->appendStep(new AddVertexStep(label));
}

GraphTraversal* GraphTraversal::addV() {
	return this->appendStep(new AddVertexStep());
}

#include "step/controlflow/CoalesceStep.h"
GraphTraversal* GraphTraversal::coalesce(std::vector<GraphTraversal*> traversals) {
	return this->appendStep(new CoalesceStep(traversals));
}

#include "step/property/AddPropertyStep.h"
GraphTraversal* GraphTraversal::property(std::string property_key, boost::any value) {
	return this->appendStep(new AddPropertyStep(property_key, value));
}

#include "step/graph/GraphStep.h"
GraphTraversal* GraphTraversal::V() {
	return this->appendStep(new GraphStep(VERTEX, {}));
}

GraphTraversal* GraphTraversal::V(Vertex* vertex) {
	return this->appendStep(new GraphStep(VERTEX, {vertex->id()}));
}

GraphTraversal* GraphTraversal::V(std::vector<Vertex*> vertices) {
	std::vector<boost::any> ids;
	for(Vertex* v : vertices) ids.push_back(v->id());
	return this->appendStep(new GraphStep(VERTEX, ids));
}

#include "step/modulate/FromStep.h"
GraphTraversal* GraphTraversal::from(std::string sideEffectLabel) {
	return this->appendStep(new FromStep(sideEffectLabel));
}

GraphTraversal* GraphTraversal::from(Vertex* fromVertex) {
	return this->appendStep(new FromStep(fromVertex));
}

#include "step/modulate/ToStep.h"
GraphTraversal* GraphTraversal::to(std::string sideEffectLabel) {
	return this->appendStep(new ToStep(sideEffectLabel));
}

GraphTraversal* GraphTraversal::to(Vertex* toVertex) {
	return this->appendStep(new ToStep(toVertex));
}

#include "step/modulate/ByStep.h"
// Modulator for valuemap and others
GraphTraversal* GraphTraversal::by(boost::any arg) {
	return this->appendStep(new ByStep(arg));
}

#include "step/logic/UnfoldStep.h"
GraphTraversal* GraphTraversal::unfold() {
	return this->appendStep(new UnfoldStep());
}

#include "step/logic/FoldStep.h"
GraphTraversal* GraphTraversal::fold() {
	return this->appendStep(new FoldStep());
}

#include "step/vertex/VertexStep.h"
GraphTraversal* GraphTraversal::both() {
	return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
}

GraphTraversal* GraphTraversal::both(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
}

GraphTraversal* GraphTraversal::bothE() {
	return this->appendStep(new VertexStep(BOTH, {}, EDGE));
}

GraphTraversal* GraphTraversal::bothE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, EDGE));
}

//GraphTraversal* bothV();
//GraphTraversal* inV();
//GraphTraversal* otherV();

GraphTraversal* GraphTraversal::out() {
	return this->appendStep(new VertexStep(OUT, VERTEX));
}

GraphTraversal* GraphTraversal::out(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, VERTEX));
}

GraphTraversal* GraphTraversal::in() {
	return this->appendStep(new VertexStep(IN, VERTEX));
}

GraphTraversal* GraphTraversal::in(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, VERTEX));
}

GraphTraversal* GraphTraversal::outE() {
	return this->appendStep(new VertexStep(OUT, EDGE));
}

GraphTraversal* GraphTraversal::outE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, EDGE));
}

GraphTraversal* GraphTraversal::inE() {
	return this->appendStep(new VertexStep(IN, EDGE));
}

GraphTraversal* GraphTraversal::inE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, EDGE));
}

#include "step/graph/IdStep.h"
GraphTraversal* GraphTraversal::id() {
	return this->appendStep(new IdStep());
}

#include "step/logic/IdentityStep.h"
GraphTraversal* GraphTraversal::identity() {
	return this->appendStep(new IdentityStep());
}

#include "step/filter/IsStep.h"
GraphTraversal* GraphTraversal::is(boost::any val) {
	return this->is(P::eq(val));
}

GraphTraversal* GraphTraversal::is(P predicate) {
	return this->appendStep(new IsStep(predicate));
}

#include "step/math/MinStep.h"
GraphTraversal* GraphTraversal::min(std::function<int(Traverser&, Traverser&)> c) {
	return this->appendStep(new MinStep(c));
}

GraphTraversal* GraphTraversal::min() {
	return this->appendStep(new MinStep(nullptr));
}

#include "step/math/CountStep.h"
GraphTraversal* GraphTraversal::count() {
	return this->appendStep(new CountStep());
}

#include "step/property/HasStep.h"
GraphTraversal* GraphTraversal::has(std::string key, P pred) {
	return this->appendStep(new HasStep(key, pred));
}

GraphTraversal* GraphTraversal::has(std::string key, boost::any value) {
	return this->appendStep(new HasStep(key, P::eq(value)));
}

GraphTraversal* GraphTraversal::has(std::string key) {
	return this->appendStep(new HasStep(key, P::neq(boost::any())));
}

#include "step/logic/DedupStep.h"
GraphTraversal* GraphTraversal::dedup() {
	return this->appendStep(new DedupStep());
}

#include "step/logic/OrderStep.h"
GraphTraversal* GraphTraversal::order() {
	return this->appendStep(new OrderStep());
}

#include "step/filter/WhereStep.h"
GraphTraversal* GraphTraversal::where(std::string label, P predicate) {
	return this->appendStep(new WhereStep(label, predicate));
}

#include "step/property/PropertyStep.h"
GraphTraversal* GraphTraversal::values(std::vector<std::string> labels) {
	return this->appendStep(new PropertyStep(VALUE, labels));
}

GraphTraversal* GraphTraversal::values(std::string label) {
	return this->appendStep(new PropertyStep(VALUE, {label}));
}

#include "step/property/ValueMapStep.h"
GraphTraversal* GraphTraversal::valueMap(std::vector<std::string> labels) {
	return this->appendStep(new ValueMapStep(labels));
}

#include "step/controlflow/RepeatStep.h"
GraphTraversal* GraphTraversal::repeat(GraphTraversal* repeatTraversal) {
	return this->appendStep(new RepeatStep(repeatTraversal));
}

#include "step/controlflow/EmitStep.h"
GraphTraversal* GraphTraversal::emit(GraphTraversal* emitTraversal) {
	return this->appendStep(new EmitStep(emitTraversal));
}

GraphTraversal* GraphTraversal::emit() {
	return this->appendStep(new EmitStep(__->identity()));
}

#include "step/controlflow/UntilStep.h"
GraphTraversal* GraphTraversal::until(GraphTraversal* untilTraversal) {
	return this->appendStep(new UntilStep(untilTraversal));
}

#include "step/sideeffect/AsStep.h"
GraphTraversal* GraphTraversal::as(std::string sideEffectLabel) {
	return this->appendStep(new AsStep(sideEffectLabel));
}

#include "step/sideeffect/SelectStep.h"
GraphTraversal* GraphTraversal::select(std::string sideEffectLabel) {
	return this->appendStep(new SelectStep(sideEffectLabel));
}

#include "step/filter/LimitStep.h"
GraphTraversal* GraphTraversal::limit(uint64_t the_limit) {
	return this->appendStep(new LimitStep(the_limit));
}

#include "step/controlflow/InjectStep.h"
GraphTraversal* GraphTraversal::inject(std::vector<boost::any> injects) {
	return this->appendStep(new InjectStep(injects));
}

std::string GraphTraversal::explain() {
	this->getInitialTraversal();

	std::string explanation = "GraphTraversal {\n";
	for(int k = 0; k < this->steps.size(); k++) explanation += this->steps[k]->getInfo() + "\n";

	return explanation + "}";
}

#include "traversal/Traverser.h"
#include <omp.h>


void GraphTraversal::forEachRemaining(std::function<void(boost::any&)> func) {
	this->getInitialTraversal();
	
	std::for_each(this->steps.begin(), this->steps.end(), [&](TraversalStep* step){
		//std::cout << "step: " << step->uid << std::endl;
		step->apply(this, this->traversers);
	});

	std::for_each(this->traversers.begin(), this->traversers.end(), [&](Traverser& trv){
		boost::any obj = trv.get();
		func(obj);
	});
}


/*
void GraphTraversal::forEachRemaining(std::function<void(boost::any&)> func) {
	this->getInitialTraversal();
	
	size_t current_step = 0;
	size_t num_steps = steps.size();
	
	while(current_step < num_steps) {
		std::cout << steps[current_step]->uid << std::endl;;
		steps[current_step++]->apply(this, traversers);
		TraverserSet new_traversers;

		size_t step = current_step;
		size_t k = 0;
		size_t sz = traversers.size();
		size_t thread;
		#pragma omp for private(step, k, thread)
		for(size_t k = 0; k < sz; ++k) {
			thread = omp_get_thread_num();
			TraverserSet local_traversers(traversers.begin() + k, traversers.begin() + k + 1);
			while(step < num_steps && !steps[step]->is_barrier) {
				steps[step]->apply(this, local_traversers);
				step++;
				if(thread == 0) current_step = step;
			}

			#pragma omp critical 
			{
				new_traversers.insert(new_traversers.end(), local_traversers.begin(), local_traversers.end());
			}
		}

		traversers.swap(new_traversers);
	
	}

	std::for_each(traversers.begin(), traversers.end(), [&](Traverser& trv){
		boost::any obj = trv.get();
		func(obj);
	});
}*/


void GraphTraversal::iterate() {
	//std::cout << "in iterate" << std::endl;
	this->getInitialTraversal();

	std::for_each(this->steps.begin(), this->steps.end(), [&](TraversalStep* step){
		//std::cout << "iterate " << step->uid << std::endl;
		//std::cout << step->getInfo() << std::endl;
		step->apply(this, this->traversers);
	});

	//this->forEachRemaining([](boost::any& t){;});
}

TraverserSet GraphTraversal::getTraversers() {
	return this->traversers;
}

#endif
