#pragma once

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "step/modulate/FromToModulating.h"
#include "traversal/Traverser.h"
#include <string>
#include <vector>

#define ADD_EDGE_STEP 0x73

	namespace gremlinxx {

	class AddEdgeStep: public TraversalStep, virtual public FromToModulating {
		private:
			std::string label;
			std::optional<GraphTraversal> out_vertex_traversal = {}; // filled in at runtime
			std::optional<GraphTraversal> in_vertex_traversal = {}; // filled in at runtime
		public:
			AddEdgeStep(std::string label_arg);

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			inline GraphTraversal& get_out_traversal() { 
				if(!this->out_vertex_traversal) throw std::runtime_error("This traversal does not have an out vertex traversal!");
				return this->out_vertex_traversal.value();
			}
			inline GraphTraversal& get_in_traversal() { 
				if(!this->in_vertex_traversal) throw std::runtime_error("This traversal does not have an in vertex traversal!");
				return this->in_vertex_traversal.value(); 
			}
			inline std::string get_label() { return this->label; }

			virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

			virtual void modulate_from(GraphTraversal trv);

			virtual void modulate_to(GraphTraversal trv);
	};

}