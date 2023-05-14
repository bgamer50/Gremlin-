#include "traversal/GraphTraversal.h"
#include "traversal/SyntaxHelper.h"

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
	this->traversers = src->getNewTraverserSet();
}

#include "step/TraversalStep.h"
GraphTraversal::GraphTraversal(GraphTraversal* trv) : GraphTraversal() {
	this->steps = trv->getSteps();
	this->source = trv->getTraversalSource();
	this->traversers = this->source->getNewTraverserSet();
}

GraphTraversal::GraphTraversal(GraphTraversalSource* src, GraphTraversal* trv) {
	this->steps = trv->getSteps();
	this->source = src;
	this->traversers = src->getNewTraverserSet();
}

Graph* GraphTraversal::getGraph() {
	return source->getGraph();
}

bool GraphTraversal::hasNext() {
	if(!this->has_iterated) this->iterate();
	return !this->traversers->empty();
}

std::vector<boost::any> GraphTraversal::toVector() {		
	std::vector<boost::any> results;
	this->forEachRemaining([&](boost::any& a){results.push_back(a);});
	return results;
}

std::list<boost::any> GraphTraversal::toList() {
	std::list<boost::any> results;
	this->forEachRemaining([&](boost::any& a) {
		results.push_back(a);
	});
	return results;
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
void GraphTraversal::setInitialTraversers(gremlinxx::traversal::TraverserSet* initial_traversers) {
	this->traversers->clear();
	this->traversers->addTraversers(initial_traversers);
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

#include "step/controlflow/UnionStep.h"
GraphTraversal* GraphTraversal::_union(std::vector<GraphTraversal*> traversals) {
	return this->appendStep(new UnionStep(traversals));
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

GraphTraversal* GraphTraversal::V(boost::any v_id) {
	return this->appendStep(new GraphStep(VERTEX, {boost::any(v_id)}));
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

#include "step/graph/SubgraphStep.h"
GraphTraversal* GraphTraversal::subgraph(std::string sideEffectLabel) {
	return this->appendStep(new SubgraphStep(sideEffectLabel));
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
template<typename T>
GraphTraversal* GraphTraversal::min() {
	auto comparison_type = gremlinxx::comparison::C_TYPEID<T>();
	return this->appendStep(new MinStep(comparison_type));
}

template
GraphTraversal* GraphTraversal::min<uint64_t>();
template
GraphTraversal* GraphTraversal::min<uint32_t>();
template
GraphTraversal* GraphTraversal::min<uint8_t>();
template
GraphTraversal* GraphTraversal::min<int64_t>();
template
GraphTraversal* GraphTraversal::min<int32_t>();
template
GraphTraversal* GraphTraversal::min<int8_t>();
template
GraphTraversal* GraphTraversal::min<std::string>();

#include "step/math/CountStep.h"
GraphTraversal* GraphTraversal::count() {
	return this->appendStep(new CountStep());
}

#include "step/math/GroupCountStep.h"
GraphTraversal* GraphTraversal::groupCount() {
	return this->appendStep(new GroupCountStep());
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
	return this->appendStep(new EmitStep(identity()));
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

GraphTraversal* GraphTraversal::cap(std::string sideEffectLabel) {
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

#include "step/logic/MapStep.h"
GraphTraversal* GraphTraversal::map(GraphTraversal* map_traversal) {
	return this->appendStep(new MapStep(map_traversal));
}

#include "step/controlflow/TimesStep.h"
GraphTraversal* GraphTraversal::times(size_t times) {
	return this->appendStep(new TimesStep(times));
}

#include "step/controlflow/LoopsStep.h"
GraphTraversal* GraphTraversal::loops() {
	return this->appendStep(new LoopsStep());
}

std::string GraphTraversal::explain() {
	return this->explain(0);
}

std::string GraphTraversal::explain(size_t indent) {
	std::string ind = "";
	for(size_t k = 0; k < indent; ++k) ind += "  ";

	if(this->source != nullptr) this->getInitialTraversal();

	std::string explanation = "GraphTraversal {\n";
	for(int k = 0; k < this->steps.size(); k++) explanation += ind + this->steps[k]->getInfo() + "\n";

	return explanation + "}";
}

#include "traversal/Traverser.h"
#include <omp.h>

boost::any GraphTraversal::first() {
	this->iterate();
	if(this->traversers->empty()) throw std::runtime_error("Traversal produced an empty set of final traversers!");

	boost::any next_result = this->traversers->getData(0);
	traversers->clear();
	return next_result;
}

boost::any GraphTraversal::next() { 
	if(!this->has_iterated) this->iterate();
	if(this->traversers->empty()) throw std::runtime_error("No traversers available when calling next()");

	boost::any next_result = this->traversers->getData(0);
	traversers->erase(0);

	return next_result;
}

void GraphTraversal::forEachRemaining(std::function<void(boost::any&)> func) {
	if(!this->has_iterated) this->iterate();

	this->traversers->apply([func](boost::any& data_i, std::unordered_map<std::string, boost::any>& se_i, std::vector<boost::any>& path_i) {
		func(data_i);
		return boost::any();
	});

	traversers->clear();
}

void GraphTraversal::iterate() {
	if(this->has_iterated) throw std::runtime_error("Traversal has already iterated!");
	
	this->getInitialTraversal();
	
	std::for_each(this->steps.begin(), this->steps.end(), [&](TraversalStep* step){
		std::cout << "step: " << step->uid << std::endl;
		std::cout << step->getInfo() << std::endl;
		step->apply(this, this->traversers);
	});

	this->has_iterated = true;
}

std::vector<Traverser> GraphTraversal::getTraversers() {
	return this->traversers->getTraversers();
}

gremlinxx::traversal::TraverserSet* GraphTraversal::getTraverserSet() {
	return this->traversers;
}

