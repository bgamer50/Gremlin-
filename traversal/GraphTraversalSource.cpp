#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"
#include "strategy/TraversalStrategy.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "strategy/RepeatStepCompletionStrategy.h"
#include "strategy/RepeatUnrollStrategy.h"
#include "strategy/ByModulatingStrategy.h"
#include "strategy/FromToModulatingStrategy.h"
#include "strategy/LimitSupportingStrategy.h"
#include "strategy/NoOpRemovalStrategy.h"
#include "strategy/SubgraphStepCompletionStrategy.h"
#include "strategy/HasJoinStrategy.h"
#include "strategy/BasicPatternExtractionStrategy.h"

#include "traversal/BasicTraverserSet.h"
#include "step/graph/VStep.h"
#include "step/vertex/AddVertexStartStep.h"
#include "step/edge/AddEdgeStartStep.h"
#include "step/controlflow/InjectStep.h"


namespace gremlinxx {

	GraphTraversalSource::GraphTraversalSource(Graph* gr) {
		graph = gr;
		this->withStrategy(RepeatStepCompletionStrategy);
		this->withStrategy(RepeatUnrollStrategy);
		this->withStrategy(ByModulatingStrategy);
		this->withStrategy(FromToModulatingStrategy);
		this->withStrategy(HasJoinStrategy);
		this->withStrategy(LimitSupportingStrategy);
		this->withStrategy(NoOpRemovalStrategy);
		this->withStrategy(BasicPatternExtractionStrategy);
		this->withStrategy(SubgraphStepCompletionStrategy);
		
		this->withTypeRegistration(std::type_index(typeid(uint64_t)), maelstrom::uint64);
		this->withTypeRegistration(std::type_index(typeid(uint32_t)), maelstrom::uint32);
		this->withTypeRegistration(std::type_index(typeid(uint8_t)), maelstrom::uint8);
		this->withTypeRegistration(std::type_index(typeid(int64_t)), maelstrom::int64);
		this->withTypeRegistration(std::type_index(typeid(int32_t)), maelstrom::int32);
		this->withTypeRegistration(std::type_index(typeid(int8_t)), maelstrom::int8);
		this->withTypeRegistration(std::type_index(typeid(double)), maelstrom::float64);
		this->withTypeRegistration(std::type_index(typeid(float)), maelstrom::float32);

		this->withTypeRegistration(std::type_index(typeid(Vertex)), graph->get_vertex_dtype());
		this->withTypeRegistration(std::type_index(typeid(Edge)), graph->get_edge_dtype());
	}

	GraphTraversalSource* GraphTraversalSource::withStrategy(TraversalStrategy strategy) {
		this->strategies.push_back(strategy);
		return this;
	}

	GraphTraversalSource* GraphTraversalSource::withoutStrategy(TraversalStrategy strategy) {
		auto it = std::find_if(
			this->strategies.begin(),
			this->strategies.end(),
			[&strategy](TraversalStrategy& ts){return (ts.name == strategy.name);}
		);
		this->strategies.erase(it);

		return this;
	}

	GraphTraversalSource* GraphTraversalSource::withoutStrategies() {
		this->strategies.clear();
		return this;
	}

	GraphTraversalSource* GraphTraversalSource::withTypeRegistration(std::type_index tid, maelstrom::dtype_t dtype) {
		this->type_registrations[tid] = dtype;
		return this;
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

	maelstrom::dtype_t GraphTraversalSource::get_dtype(std::any obj) {
		const std::type_index type = std::type_index(obj.type());
		auto z = this->type_registrations.find(type);
		if(z == this->type_registrations.end()) {
			throw std::runtime_error("Could not find type!");
		}

		return z->second;
	}

	std::vector<TraversalStrategy>& GraphTraversalSource::getStrategies() {
		return this->strategies;
	}

	Graph* GraphTraversalSource::getGraph() {
		return graph;
	}

	gremlinxx::traversal::TraverserSet* GraphTraversalSource::getNewTraverserSet() {
		return new gremlinxx::traversal::BasicTraverserSet();
	}

	GraphTraversal GraphTraversalSource::V() {
		GraphTraversal trv(this);
		trv.appendStep(new VStep({}));
		return trv;
	}

	GraphTraversal GraphTraversalSource::V(Vertex v) {
		GraphTraversal trv(this);
		trv.appendStep(new VStep({v.id}));
		return trv;
	}

	GraphTraversal GraphTraversalSource::V(std::any v_id) {
		GraphTraversal trv(this);
		trv.appendStep(new VStep( {v_id}));
		return trv;
	}

	GraphTraversal GraphTraversalSource::V(std::vector<Vertex> vertices) {
		GraphTraversal trv(this);
		
		std::vector<std::any> v_ids;
		v_ids.reserve(vertices.size());
		for(Vertex& v : vertices) v_ids.push_back(v.id);

		trv.appendStep(new VStep(v_ids));
		return trv;
	}

	GraphTraversal GraphTraversalSource::V(std::vector<std::any> v_ids) {
		GraphTraversal trv(this);
		trv.appendStep(new VStep(v_ids));
		return trv;
	}

	GraphTraversal GraphTraversalSource::E() {
		// FIXME should call a step with this as the default implementation
		return this->V().outE();
	}

	GraphTraversal GraphTraversalSource::addV() {
		GraphTraversal trv(this);
		trv.appendStep(new AddVertexStartStep());
		return trv;
	}

	GraphTraversal GraphTraversalSource::addV(std::string label) {
		GraphTraversal trv(this);
		trv.appendStep(new AddVertexStartStep(label));
		return trv;
	}

	GraphTraversal GraphTraversalSource::addE(std::string label) {
		GraphTraversal trv(this);
		trv.appendStep(new AddEdgeStartStep(label));
		return trv;
	}

	GraphTraversal GraphTraversalSource::inject(std::vector<std::any> injects) {
		GraphTraversal trv(this);
		return trv.appendStep(new InjectStep(injects));
	}

}