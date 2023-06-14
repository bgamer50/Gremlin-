#pragma once

#define PROPERTY_STEP 0x75
#define PROPERTY_STEP_SIDE_EFFECT_KEY "__PropertyStep__originating_traverser__"

#include "step/TraversalStep.h"
#include "structure/VertexProperty.h"
#include "traversal/Scope.h"
#include "traversal/Traverser.h"

namespace gremlinxx {

	class MinStep;
	class Element;
	class Vertex;

	// Edge properties currently not supported.
	class PropertyStep : public TraversalStep {
		private:
			Cardinality cardinality;
			std::string key;
			boost::any value;
		public:
			PropertyStep(std::string property_key, boost::any value);

			PropertyStep(Cardinality card, std::string property_key, boost::any value);

			inline Cardinality get_cardinality() { return this->cardinality; }

			inline std::string get_key() { return this->key; }

			inline boost::any get_value() { return this->value; };
			
			virtual void apply(GraphTraversal* current_traversal, gremlinxx::traversal::TraverserSet& traversers);
	};

}