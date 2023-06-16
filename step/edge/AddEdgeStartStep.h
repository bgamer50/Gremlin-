#pragma once

#define ADD_EDGE_START_STEP 0x72

#include <string>
#include <vector>
#include <boost/any.hpp>

#include "step/modulate/FromToModulating.h"
#include "step/TraversalStep.h"

#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"

namespace gremlinxx {

	class AddEdgeStartStep: public TraversalStep, virtual public FromToModulating {
		private:
			std::string label;
			std::optional<GraphTraversal> out_vertex_traversal = {}; // filled in at runtime
			std::optional<GraphTraversal> in_vertex_traversal = {}; // filled in at runtime
		public:
			AddEdgeStartStep(std::string label_arg);
			
			using TraversalStep::getInfo;
			virtual std::string getInfo();


			inline GraphTraversal& get_out_traversal() { 
				if(!this->out_vertex_traversal) throw std::runtime_error("Traversal does not have an out traversal!");

				return this->out_vertex_traversal.value();
			}
			inline GraphTraversal& get_in_traversal() { 
				if(!this->in_vertex_traversal) throw std::runtime_error("Traversal does not have an in traversal!");
				return this->in_vertex_traversal.value();
			}
			inline std::string get_label() { return this->label; }

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);

			virtual void modulate_from(GraphTraversal arg);
			
			virtual void modulate_to(GraphTraversal arg);
	};

}