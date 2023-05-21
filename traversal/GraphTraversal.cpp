#include "traversal/GraphTraversal.h"
#include "traversal/SyntaxHelper.h"

#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

/*
	The "default" constructor.
*/
gremlinxx::GraphTraversal::GraphTraversal() {
	this->source = nullptr;
	this->traversers = nullptr;
}

#include "traversal/GraphTraversalSource.h"
/*
	The given traversal source is allowed to be null, in the case of an
	anomymous traversal.
*/
gremlinxx::GraphTraversal::GraphTraversal(GraphTraversalSource* src) : GraphTraversal() {
	source = src;
	this->traversers = src->getNewTraverserSet();
}

#include "step/TraversalStep.h"
gremlinxx::GraphTraversal::GraphTraversal(GraphTraversal* trv) : GraphTraversal() {
	this->steps = trv->getSteps();
	this->source = trv->getTraversalSource();
	this->traversers = this->source->getNewTraverserSet();
}

gremlinxx::GraphTraversal::GraphTraversal(GraphTraversalSource* src, GraphTraversal* trv) {
	this->steps = trv->getSteps();
	this->source = src;
	this->traversers = src->getNewTraverserSet();
}

gremlinxx::Graph* gremlinxx::GraphTraversal::getGraph() {
	return source->getGraph();
}

bool gremlinxx::GraphTraversal::hasNext() {
	if(!this->has_iterated) this->iterate();
	return !this->traversers->empty();
}

std::vector<boost::any> gremlinxx::GraphTraversal::toVector() {		
	std::vector<boost::any> results;
	this->forEachRemaining([&](boost::any& a){results.push_back(a);});
	return results;
}

std::list<boost::any> gremlinxx::GraphTraversal::toList() {
	std::list<boost::any> results;
	this->forEachRemaining([&](boost::any& a) {
		results.push_back(a);
	});
	return results;
}

gremlinxx::GraphTraversalSource* gremlinxx::GraphTraversal::getTraversalSource() {
	return source;
}

/*
	In general this should be called by the finalization steps in
	classes that extend GraphTraversal.
*/
void gremlinxx::GraphTraversal::getInitialTraversal() {
	// Apply each strategy to this traversal's traversers.
	std::for_each(this->source->getStrategies().begin(), this->source->getStrategies().end(), [this](TraversalStrategy strategy) {
		strategy(this->steps);
	});
}

/*

*/
void gremlinxx::GraphTraversal::setInitialTraversers(gremlinxx::traversal::TraverserSet& initial_traversers) {
	this->traversers->clear();
	this->traversers->addTraversers(initial_traversers);
}

#include "step/edge/AddEdgeStartStep.h"
#include "step/vertex/AddVertexStartStep.h"
#include "step/logic/NoOpStep.h"


#include "step/edge/AddEdgeStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::addE(std::string label){
	return this->appendStep(new AddEdgeStep(label));
}

#include "step/vertex/AddVertexStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::addV(std::string label) {
	return this->appendStep(new AddVertexStep(label));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::addV() {
	return this->appendStep(new AddVertexStep());
}

#include "step/controlflow/CoalesceStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::coalesce(std::vector<GraphTraversal*> traversals) {
	return this->appendStep(new CoalesceStep(traversals));
}

#include "step/controlflow/UnionStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::_union(std::vector<GraphTraversal*> traversals) {
	return this->appendStep(new UnionStep(traversals));
}

#include "step/property/AddPropertyStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::property(std::string property_key, boost::any value) {
	return this->appendStep(new AddPropertyStep(property_key, value));
}

#include "step/graph/VStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::V() {
	return this->appendStep(new VStep({}));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::V(Vertex* vertex) {
	return this->appendStep(new VStep({vertex->id()}));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::V(std::vector<Vertex*> vertices) {
	std::vector<boost::any> ids;
	for(Vertex* v : vertices) ids.push_back(v->id());
	return this->appendStep(new VStep(ids));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::V(boost::any v_id) {
	return this->appendStep(new VStep({boost::any(v_id)}));
}

#include "step/modulate/FromStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::from(std::string sideEffectLabel) {
	return this->appendStep(new FromStep(sideEffectLabel));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::from(Vertex* fromVertex) {
	return this->appendStep(new FromStep(fromVertex));
}

#include "step/modulate/ToStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::to(std::string sideEffectLabel) {
	return this->appendStep(new ToStep(sideEffectLabel));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::to(Vertex* toVertex) {
	return this->appendStep(new ToStep(toVertex));
}

#include "step/modulate/ByStep.h"
// Modulator for valuemap and others
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::by(boost::any arg) {
	return this->appendStep(new ByStep(arg));
}

#include "step/logic/UnfoldStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::unfold() {
	return this->appendStep(new UnfoldStep());
}

#include "step/logic/FoldStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::fold() {
	return this->appendStep(new FoldStep());
}

#include "step/vertex/VertexStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::both() {
	return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::both(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::bothE() {
	return this->appendStep(new VertexStep(BOTH, {}, EDGE));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::bothE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, EDGE));
}

//GraphTraversal* bothV();
//GraphTraversal* inV();
//GraphTraversal* otherV();

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::out() {
	return this->appendStep(new VertexStep(OUT, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::out(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::in() {
	return this->appendStep(new VertexStep(IN, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::in(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, VERTEX));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::outE() {
	return this->appendStep(new VertexStep(OUT, EDGE));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::outE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, EDGE));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::inE() {
	return this->appendStep(new VertexStep(IN, EDGE));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::inE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, EDGE));
}

#include "step/graph/SubgraphStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::subgraph(std::string sideEffectLabel) {
	return this->appendStep(new SubgraphStep(sideEffectLabel));
}

#include "step/graph/IdStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::id() {
	return this->appendStep(new IdStep());
}

#include "step/logic/IdentityStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::identity() {
	return this->appendStep(new IdentityStep());
}

#include "step/filter/IsStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::is(boost::any val) {
	return this->is(P::eq(val));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::is(P predicate) {
	return this->appendStep(new IsStep(predicate));
}

#include "step/math/MinStep.h"
template<typename T>
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min() {
	auto comparison_type = gremlinxx::comparison::C_TYPEID<T>();
	return this->appendStep(new MinStep(comparison_type));
}

template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<uint64_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<uint32_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<uint8_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<int64_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<int32_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<int8_t>();
template
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::min<std::string>();

#include "step/math/CountStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::count() {
	return this->appendStep(new CountStep());
}

#include "step/math/GroupCountStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::groupCount() {
	return this->appendStep(new GroupCountStep());
}

#include "step/property/HasStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::has(std::string key, P pred) {
	return this->appendStep(new HasStep(key, pred));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::has(std::string key, boost::any value) {
	return this->appendStep(new HasStep(key, P::eq(value)));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::has(std::string key) {
	return this->appendStep(new HasStep(key, P::neq(boost::any())));
}

#include "step/logic/DedupStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::dedup() {
	return this->appendStep(new DedupStep());
}

#include "step/logic/OrderStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::order() {
	return this->appendStep(new OrderStep());
}

#include "step/filter/WhereStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::where(std::string label, P predicate) {
	return this->appendStep(new WhereStep(label, predicate));
}

#include "step/property/PropertyStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::values(std::vector<std::string> labels) {
	return this->appendStep(new PropertyStep(VALUE, labels));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::values(std::string label) {
	return this->appendStep(new PropertyStep(VALUE, {label}));
}

#include "step/property/ValueMapStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::valueMap(std::vector<std::string> labels) {
	return this->appendStep(new ValueMapStep(labels));
}

#include "step/controlflow/RepeatStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::repeat(gremlinxx::GraphTraversal* repeatTraversal) {
	return this->appendStep(new gremlinxx::RepeatStep(repeatTraversal));
}

#include "step/controlflow/EmitStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::emit(gremlinxx::GraphTraversal* emitTraversal) {
	return this->appendStep(new EmitStep(emitTraversal));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::emit() {
	return this->appendStep(new EmitStep(identity()));
}

#include "step/controlflow/UntilStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::until(GraphTraversal* untilTraversal) {
	return this->appendStep(new UntilStep(untilTraversal));
}

#include "step/sideeffect/AsStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::as(std::string sideEffectLabel) {
	return this->appendStep(new AsStep(sideEffectLabel));
}

#include "step/sideeffect/SelectStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::select(std::string sideEffectLabel) {
	return this->appendStep(new SelectStep(sideEffectLabel));
}

gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::cap(std::string sideEffectLabel) {
	return this->appendStep(new SelectStep(sideEffectLabel));
}

#include "step/filter/LimitStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::limit(uint64_t the_limit) {
	return this->appendStep(new LimitStep(the_limit));
}

#include "step/controlflow/InjectStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::inject(std::vector<boost::any> injects) {
	return this->appendStep(new InjectStep(injects));
}

#include "step/logic/MapStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::map(GraphTraversal* map_traversal) {
	return this->appendStep(new MapStep(map_traversal));
}

#include "step/controlflow/TimesStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::times(size_t times) {
	return this->appendStep(new TimesStep(times));
}

#include "step/controlflow/LoopsStep.h"
gremlinxx::GraphTraversal* gremlinxx::GraphTraversal::loops() {
	return this->appendStep(new LoopsStep());
}

std::string gremlinxx::GraphTraversal::explain() {
	return this->explain(0);
}

std::string gremlinxx::GraphTraversal::explain(size_t indent) {
	std::string ind = "";
	for(size_t k = 0; k < indent; ++k) ind += "  ";

	if(this->source != nullptr) this->getInitialTraversal();

	std::string explanation = "GraphTraversal {\n";
	for(int k = 0; k < this->steps.size(); k++) explanation += ind + this->steps[k]->getInfo() + "\n";

	return explanation + "}";
}

#include "traversal/Traverser.h"
#include <omp.h>

boost::any gremlinxx::GraphTraversal::first() {
	this->iterate();
	if(this->traversers->empty()) throw std::runtime_error("Traversal produced an empty set of final traversers!");

	boost::any next_result = this->traversers->getData(0);
	traversers->clear();
	return next_result;
}

boost::any gremlinxx::GraphTraversal::next() { 
	if(!this->has_iterated) this->iterate();
	if(this->traversers->empty()) throw std::runtime_error("No traversers available when calling next()");

	boost::any next_result = this->traversers->getData(0);
	traversers->erase(0);

	return next_result;
}

void gremlinxx::GraphTraversal::forEachRemaining(std::function<void(boost::any&)> func) {
	if(!this->has_iterated) this->iterate();

	auto data = this->traversers->getTraverserData();
	auto data_host = maelstrom::as_host_vector(data);
	
	for(size_t k = 0; k < data_host.size(); ++k) {
		auto data_k = data.get(k);
		func(data_k);
	}

	traversers->clear();
}

void gremlinxx::GraphTraversal::iterate() {
	if(this->has_iterated) throw std::runtime_error("Traversal has already iterated!");
	
	this->getInitialTraversal();
	
	std::for_each(this->steps.begin(), this->steps.end(), [&](TraversalStep* step){
		std::cout << "step: " << step->uid << std::endl;
		std::cout << step->getInfo() << std::endl;
		step->apply(this, *this->traversers);
	});

	this->has_iterated = true;
}

std::vector<Traverser> gremlinxx::GraphTraversal::getTraversers() {
	return this->traversers->toTraversers();
}

gremlinxx::traversal::TraverserSet& gremlinxx::GraphTraversal::getTraverserSet() {
	if(this->traversers == nullptr) throw std::runtime_error("Cannot get traverser set of an anonymous traversal!");

	return *(this->traversers);
}

