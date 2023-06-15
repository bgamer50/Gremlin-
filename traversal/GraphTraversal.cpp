#include "traversal/GraphTraversal.h"
#include "traversal/SyntaxHelper.h"

#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "step/TraversalStep.h"
#include "traversal/GraphTraversalSource.h"

#include "step/edge/AddEdgeStartStep.h"
#include "step/vertex/AddVertexStartStep.h"
#include "step/logic/NoOpStep.h"
#include "step/controlflow/InjectStep.h"
#include "step/filter/LimitStep.h"
#include "step/sideeffect/SelectStep.h"
#include "step/sideeffect/AsStep.h"
#include "step/controlflow/UntilStep.h"
#include "step/controlflow/EmitStep.h"
#include "step/property/ElementMapStep.h"
#include "step/property/ValueStep.h"
#include "step/filter/WhereStep.h"
#include "step/logic/OrderStep.h"
#include "step/math/GroupCountStep.h"
#include "step/vertex/VertexStep.h"
#include "step/modulate/ByStep.h"
#include "step/modulate/FromStep.h"
#include "step/edge/AddEdgeStep.h"	
#include "step/vertex/AddVertexStep.h"
#include "step/controlflow/CoalesceStep.h"
#include "step/controlflow/UnionStep.h"
#include "step/property/PropertyStep.h"
#include "step/graph/VStep.h"
#include "step/modulate/ToStep.h"
#include "step/graph/SubgraphStep.h"
#include "step/graph/IdStep.h"
#include "step/logic/IdentityStep.h"
#include "step/filter/IsStep.h"
#include "step/math/CountStep.h"
#include "step/property/HasStep.h"
#include "step/logic/DedupStep.h"
#include "step/controlflow/TimesStep.h"
#include "step/controlflow/LoopsStep.h"
#include "step/controlflow/RepeatStep.h
#include "step/math/MinStep.h"

#include <boost/any.hpp>

namespace gremlinxx {

	/*
		The "default" constructor.
	*/
	GraphTraversal::GraphTraversal() {
		this->source = nullptr;
		this->traversers = nullptr;
	}

	/*
		The given traversal source is allowed to be null, in the case of an
		anomymous traversal.
	*/
	GraphTraversal::GraphTraversal(GraphTraversalSource* src) : GraphTraversal() {
		source = src;
		this->traversers = src->getNewTraverserSet();
	}

	
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
	void GraphTraversal::setInitialTraversers(traversal::TraverserSet& initial_traversers) {
		this->traversers->clear();
		this->traversers->addTraversers(initial_traversers);
	}

	
	GraphTraversal* GraphTraversal::addE(std::string label){
		return this->appendStep(new AddEdgeStep(label));
	}

	GraphTraversal* GraphTraversal::addV(std::string label) {
		return this->appendStep(new AddVertexStep(label));
	}

	GraphTraversal* GraphTraversal::addV() {
		return this->appendStep(new AddVertexStep());
	}

	GraphTraversal* GraphTraversal::coalesce(std::vector<GraphTraversal*> traversals) {
		return this->appendStep(new CoalesceStep(traversals));
	}

	GraphTraversal* GraphTraversal::_union(std::vector<GraphTraversal*> traversals) {
		return this->appendStep(new UnionStep(traversals));
	}

	GraphTraversal* GraphTraversal::property(std::string property_key, boost::any value) {
		return this->appendStep(new PropertyStep(property_key, value));
	}

	GraphTraversal* GraphTraversal::V() {
		return this->appendStep(new VStep({}));
	}

	GraphTraversal* GraphTraversal::V(Vertex* vertex) {
		return this->appendStep(new VStep({vertex->id()}));
	}

	GraphTraversal* GraphTraversal::V(std::vector<Vertex*> vertices) {
		std::vector<boost::any> ids;
		for(Vertex* v : vertices) ids.push_back(v->id());
		return this->appendStep(new VStep(ids));
	}

	GraphTraversal* GraphTraversal::V(boost::any v_id) {
		return this->appendStep(new VStep({boost::any(v_id)}));
	}

	GraphTraversal* GraphTraversal::from(std::string sideEffectLabel) {
		return this->appendStep(new FromStep(sideEffectLabel));
	}

	GraphTraversal* GraphTraversal::from(Vertex* fromVertex) {
		return this->appendStep(new FromStep(fromVertex));
	}

	GraphTraversal* GraphTraversal::to(std::string sideEffectLabel) {
		return this->appendStep(new ToStep(sideEffectLabel));
	}

	GraphTraversal* GraphTraversal::to(Vertex* toVertex) {
		return this->appendStep(new ToStep(toVertex));
	}

	// Modulator for valuemap and others
	GraphTraversal* GraphTraversal::by(boost::any arg) {
		return this->appendStep(new ByStep(arg));
	}

	GraphTraversal* GraphTraversal::both() {
		return this->appendStep(new VertexStep(BOTH, {}, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::both(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::bothE() {
		return this->appendStep(new VertexStep(BOTH, {}, VERTEX_TO_EDGE));
	}

	GraphTraversal* GraphTraversal::bothE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(BOTH, labels, VERTEX_TO_EDGE));
	}

	//GraphTraversal* bothV();
	//GraphTraversal* inV();
	//GraphTraversal* otherV();

	GraphTraversal* GraphTraversal::out() {
		return this->appendStep(new VertexStep(OUT, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::out(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::in() {
		return this->appendStep(new VertexStep(IN, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::in(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(IN, labels, VERTEX_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::outE() {
		return this->appendStep(new VertexStep(OUT, VERTEX_TO_EDGE));
	}

	GraphTraversal* GraphTraversal::outE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(OUT, labels, VERTEX_TO_EDGE));
	}

	GraphTraversal* GraphTraversal::inE() {
		return this->appendStep(new VertexStep(IN, VERTEX_TO_EDGE));
	}

	GraphTraversal* GraphTraversal::inE(std::vector<std::string> labels) {
		return this->appendStep(new VertexStep(IN, labels, VERTEX_TO_EDGE));
	}

	GraphTraversal* GraphTraversal::outV() {
		return this->appendStep(new VertexStep(OUT, EDGE_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::inV() {
		return this->appendStep(new VertexStep(IN, EDGE_TO_VERTEX));
	}

	GraphTraversal* GraphTraversal::subgraph(std::string sideEffectLabel) {
		return this->appendStep(new SubgraphStep(sideEffectLabel));
	}

	GraphTraversal* GraphTraversal::id() {
		return this->appendStep(new IdStep());
	}

	GraphTraversal* GraphTraversal::identity() {
		return this->appendStep(new IdentityStep());
	}

	GraphTraversal* GraphTraversal::is(boost::any val) {
		return this->is(P::eq(val));
	}

	GraphTraversal* GraphTraversal::is(P predicate) {
		return this->appendStep(new IsStep(predicate));
	}

	template<typename T>
	GraphTraversal* GraphTraversal::min() {
		auto comparison_type = comparison::C_TYPEID<T>();
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

		
	GraphTraversal* GraphTraversal::count() {
		return this->appendStep(new CountStep());
	}

	GraphTraversal* GraphTraversal::groupCount() {
		return this->appendStep(new GroupCountStep());
	}


	GraphTraversal* GraphTraversal::has(std::string key, P pred) {
		return this->appendStep(new HasStep(key, pred));
	}

	GraphTraversal* GraphTraversal::has(std::string key, boost::any value) {
		return this->appendStep(new HasStep(key, P::eq(value)));
	}

	GraphTraversal* GraphTraversal::has(std::string key) {
		return this->appendStep(new HasStep(key, P::neq(boost::any())));
	}

	GraphTraversal* GraphTraversal::dedup() {
		return this->appendStep(new DedupStep());
	}

	GraphTraversal* GraphTraversal::order() {
		return this->appendStep(new OrderStep());
	}

	GraphTraversal* GraphTraversal::where(std::string label, P predicate) {
		return this->appendStep(new WhereStep(label, predicate));
	}

	GraphTraversal* GraphTraversal::values(std::vector<std::string> labels) {

		return this->appendStep(new ValueStep(labels));
	}

	GraphTraversal* GraphTraversal::values(std::string label) {
		return this->appendStep(new ValueStep({label}));
	}

	GraphTraversal* GraphTraversal::elementMap(std::vector<std::string> labels) {
		return this->appendStep(new ElementMapStep(labels));
	}

	GraphTraversal* GraphTraversal::repeat(GraphTraversal* repeatTraversal) {
		return this->appendStep(new RepeatStep(repeatTraversal));
	}

	GraphTraversal* GraphTraversal::emit(GraphTraversal* emitTraversal) {
		return this->appendStep(new EmitStep(emitTraversal));
	}

	GraphTraversal* GraphTraversal::emit() {
		return this->appendStep(new EmitStep(identity()));
	}

	GraphTraversal* GraphTraversal::until(GraphTraversal* untilTraversal) {
		return this->appendStep(new UntilStep(untilTraversal));
	}

	GraphTraversal* GraphTraversal::as(std::string sideEffectLabel) {
		return this->appendStep(new AsStep(sideEffectLabel));
	}

	GraphTraversal* GraphTraversal::select(std::string sideEffectLabel) {
		return this->appendStep(new SelectStep(sideEffectLabel));
	}

	GraphTraversal* GraphTraversal::cap(std::string sideEffectLabel) {
		return this->appendStep(new SelectStep(sideEffectLabel));
	}
	
	GraphTraversal* GraphTraversal::limit(uint64_t the_limit) {
		return this->appendStep(new LimitStep(the_limit));
	}

	GraphTraversal* GraphTraversal::inject(std::vector<boost::any> injects) {
		return this->appendStep(new InjectStep(injects));
	}

	GraphTraversal* GraphTraversal::times(size_t times) {
		return this->appendStep(new TimesStep(times));
	}

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

		auto data = this->traversers->getTraverserData();
		auto data_host = maelstrom::as_host_vector(data);
		
		for(size_t k = 0; k < data_host.size(); ++k) {
			auto data_k = data.get(k);
			func(data_k);
		}

		traversers->clear();
	}

	void GraphTraversal::iterate() {
		if(this->has_iterated) throw std::runtime_error("Traversal has already iterated!");
		
		this->getInitialTraversal();
		
		std::for_each(this->steps.begin(), this->steps.end(), [&](TraversalStep* step){
			std::cout << "step: " << step->uid << std::endl;
			std::cout << step->getInfo() << std::endl;
			step->apply(this, *this->traversers);
		});

		this->has_iterated = true;
	}

	std::vector<Traverser> GraphTraversal::getTraversers() {
		return this->traversers->toTraversers();
	}

	traversal::TraverserSet& GraphTraversal::getTraverserSet() {
		if(this->traversers == nullptr) throw std::runtime_error("Cannot get traverser set of an anonymous traversal!");

		return *(this->traversers);
	}

}