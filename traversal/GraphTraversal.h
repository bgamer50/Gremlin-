#pragma once

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

#include <any>
#include <memory>

#include "structure/Direction.h"
#include "traversal/P.h"
#include "structure/Direction.h"
#include "traversal/Scope.h"
#include "traversal/Traverser.h"
#include "traversal/TraverserSet.h"

#include "structure/Element.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

namespace gremlinxx {

	class TraversalStep;
	class Graph;
	class GraphTraversalSource;

	class GraphTraversal {
	protected:
		std::vector<std::shared_ptr<TraversalStep>> steps;
		std::unique_ptr<gremlinxx::traversal::TraverserSet> traversers; // FIXME change this to unique pointer
		std::unordered_map<std::string, std::any> traversal_properties;
	private:
		GraphTraversalSource* source;
		bool has_iterated = false;
	public:
		/*
			The "default" constructor.
		*/
		GraphTraversal();

		~GraphTraversal();

		/*
			The given traversal source is allowed to be null, in the case of an
			anomymous traversal.
		*/
		GraphTraversal(GraphTraversalSource* src);
		GraphTraversal(const GraphTraversal& trv);
		GraphTraversal(GraphTraversal&& trv);
	
		GraphTraversal(GraphTraversalSource* src, GraphTraversal& trv);

		GraphTraversal& operator=(const GraphTraversal& trv);

		Graph* getGraph();


		GraphTraversalSource* getTraversalSource();

		inline std::vector<std::shared_ptr<TraversalStep>>& getSteps() {
			return this->steps;
		}

		inline GraphTraversal& appendStep(TraversalStep* step) {
			this->steps.push_back(std::unique_ptr<TraversalStep>(step));
			return *this;
		}

		inline GraphTraversal& insertStep(size_t k, TraversalStep* step) {
			this->steps.insert(steps.begin() + k, std::unique_ptr<TraversalStep>(step));
			return *this;
		}

		/*
			Sets the traversal property with the given name to the given value.
			Returns true if successful, false if unsuccessful.
		*/
		inline bool setTraversalProperty(std::string property_name, std::any property_value) {
			this->traversal_properties[property_name] = property_value;
			return true;
		}

		/*
			Gets a copy of the traversal property with the given name.
		*/
		inline std::any getTraversalProperty(std::string property_name) {
			auto f = this->traversal_properties.find(property_name);
			if(f == traversal_properties.end()) return std::any();
			return f->second;
		}

		/*
			Removes and returns the traversal property with the given name.
			If no such property exists, returns an empty any.
		*/
		inline std::any removeTraversalProperty(std::string property_name) {
			auto f = this->traversal_properties.find(property_name);
			if(f == traversal_properties.end()) {
				return std::any();	
			}

			auto val = std::move(f->second);
			this->traversal_properties.erase(f);
			return std::move(val);
		}

		// Steps
		GraphTraversal& addE(std::string label);

		GraphTraversal& addV(std::string label);

		GraphTraversal& addV();

		GraphTraversal& property(std::string property_key, std::any value);

		//GraphTraversal<auto n> aggregate(std::string sideEffectLabel);
		//GraphTraversal<auto n> _and();
		//GraphTraversal<auto n> _and(std::vector<GraphTraversal<auto m>> traversals);
		
		GraphTraversal& sideEffect(std::string sideEffectLabel, std::any value);

		GraphTraversal& as(std::string sideEffectLabel);
		
		//GraphTraversal* barrier();
		GraphTraversal& by(std::any arg);
		GraphTraversal& cap(std::string sideEffectLabel);
		//GraphTraversal<auto n> choose(GraphTraversal<A> ifTraversal, GraphTraversal<B> trueTraversal, GraphTraversal<C> falseTraversal);
		//GraphTraversal<auto n> choose(GraphTraversal<A> withOptionTraversal);
		
		GraphTraversal& coalesce(std::vector<GraphTraversal> traversals);
		//GraphTraversal* coin(float chance);
		//GraphTraversal constant(void* value, size_t size);
		GraphTraversal& count();
		//GraphTraversal* cyclicPath();
		GraphTraversal& dedup();
		//GraphTraversal* drop();
		GraphTraversal& emit();
		//GraphTraversal emit(Predicate predicate);
		GraphTraversal& emit(GraphTraversal emitTraversal);
		GraphTraversal& fold();
		//GraphTraversal* from(GraphTraversal* fromTraversal);

		GraphTraversal& from(std::string sideEffectLabel);

		GraphTraversal& from(Vertex fromVertex);

		GraphTraversal& V();

		GraphTraversal& V(Vertex vertex);

		GraphTraversal& V(std::vector<Vertex> vertices);

		GraphTraversal& V(std::any v_id);

		//GraphTraversal* V(void* objects, size_t sizeOfEach, int length);
		//GraphTraversal group();
		//GraphTraversal group(std::string sideEffectLabel);
		GraphTraversal& groupCount();
		//GraphTraversal groupCount(std::string sideEffectLabel);
		//GraphTraversal has(std::string key, void* value, size_t size); // dangerous operation
		//GraphTraversal has(std::string label, std::string key, void* value, size_t size); // dangerous operation

		GraphTraversal& has(std::string key, P pred);

		GraphTraversal& has(std::string key, std::any value);

		GraphTraversal& has(std::string key);

		//GraphTraversal* has(std::string key, GraphTraversal* valueTraversal);
		//GraphTraversal* has(std::string key);
		GraphTraversal& hasNot(std::string key);
		//GraphTraversal* hasLabel(std::vector<std::string> labels);
		//GraphTraversal* hasLabel(std::string label);
		//GraphTraversal* hasId(void* ids, size_t sizeOfEach, int length); // dangerous operation
		//GraphTraversal* hasValue(void* values, size_t* sizesOfEach, int length); // dangerous operation
		
		GraphTraversal& id();

		GraphTraversal& identity();
		GraphTraversal& inject(std::vector<std::any> objects);
		GraphTraversal& is(std::any val);
		GraphTraversal& is(P predicate);
		//GraphTraversal key();
		//GraphTraversal* label();
		GraphTraversal& limit(uint64_t the_limit);
		//GraphTraversal limit(Scope scope, unsigned long theLimit);
		//GraphTraversal* local(GraphTraversal* localTraversal);
		GraphTraversal& loops();
		//GraphTraversal match(std::vector<GraphTraversal> matchTraversals);
		//GraphTraversal* math(std::string equation);
		//GraphTraversal* max();
		//GraphTraversal max(Scope scope);
		//GraphTraversal* mean();
		//GraphTraversal mean(Scope scope);
		
		GraphTraversal& min();
		GraphTraversal& min(ScopeContext sc);

		//GraphTraversal min(Scope scope);
		//GraphTraversal _not(GraphTraversal notTraversal);
		//GraphTraversal option(GraphTraversal optionTraversal);
		//GraphTraversal optional(GraphTraversal OptionalTraversal);
		//GraphTraversal _or(std::vector<GraphTraversal> orTraversals);
		GraphTraversal& order();
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
		GraphTraversal& repeat(GraphTraversal repeatTraversal);
		// sack step not supported
		GraphTraversal& sample(size_t sampleSize);
		//GraphTraversal sample(Scope scope, int sampleSize);
		// single-label select is special
		GraphTraversal& select(std::string sideEffectLabel);
		//GraphTraversal select(std::vector<std::string> sideEffectLabels);
		//GraphTraversal select(GraphTraversal selectTraversal);
		//GraphTraversal* simplePath();
		//GraphTraversal* skip(unsigned long toSkip);
		//GraphTraversal skip(Scope scope, unsigned long toSkip);
		//GraphTraversal* store(std::string sideEffectLabel);
		GraphTraversal& subgraph(std::string sideEffectLabel);
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
		GraphTraversal& to(std::string sideEffectLabel);

		// MODULATOR for addE
		GraphTraversal& to(Vertex toVertex);

		//GraphTraversal* toV(Direction direction);
		//GraphTraversal tree(std::string sideEffectLabel);
		//GraphTraversal tree();
		GraphTraversal& unfold();
		GraphTraversal& _union(std::vector<GraphTraversal> unionTraversals);
		//GraphTraversal until(Predicate predicate);
		GraphTraversal& until(GraphTraversal untilTraversal);
		//GraphTraversal value();
		GraphTraversal& elementMap(std::vector<std::string> labels);
		//GraphTraversal values();
		GraphTraversal& values(std::vector<std::string> labels);

		GraphTraversal& values(std::string label);

		GraphTraversal& both();
		GraphTraversal& both(std::vector<std::string> labels);
		GraphTraversal& bothE();
		GraphTraversal& bothE(std::vector<std::string> labels);
		//GraphTraversal* bothV();
		GraphTraversal& outV();
		GraphTraversal& inV();
		//GraphTraversal* otherV();
		GraphTraversal& out();
		GraphTraversal& out(std::vector<std::string> labels);
		GraphTraversal& in();
		GraphTraversal& in(std::vector<std::string> labels);
		GraphTraversal& outE();
		GraphTraversal& outE(std::vector<std::string> labels);
		GraphTraversal& inE();
		GraphTraversal& inE(std::vector<std::string> labels);

		GraphTraversal& times(size_t times);

		//GraphTraversal where(Predicate predicate);
		/**
		 * Used for comparison of two objects stored as side effects.
		 * TODO Current implementation is incorrect; used only as a temporary timesaver
		 * **/
		GraphTraversal& where(std::string label, P predicate);
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
		void setInitialTraversers(gremlinxx::traversal::TraverserSet& initial_traversers);

		// The explain finalizer which works in anonymous GraphTraversals
		std::string explain();
		std::string info();

		// Finalizing steps

		bool hasNext();

		std::vector<std::any> toVector();

		std::list<std::any> toList();

		// much more efficient & memory-safe for getting the first result than next()
		std::any first();

		std::any next();

		void forEachRemaining(std::function<void(std::any&)> func);

		void iterate();

		std::vector<Traverser> getTraversers();

		gremlinxx::traversal::TraverserSet& getTraverserSet();

		//GraphTraversal toSet();
	};

}