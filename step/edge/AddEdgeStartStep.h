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
			GraphTraversal* out_vertex_traversal; // filled in at runtime
			GraphTraversal* in_vertex_traversal; // filled in at runtime
		public:
			AddEdgeStartStep(std::string label_arg);
			
			using TraversalStep::getInfo;
			virtual std::string getInfo();


			inline GraphTraversal* get_out_traversal() { return this->out_vertex_traversal; }
			inline GraphTraversal* get_in_traversal() { return this->in_vertex_traversal; }
			inline std::string get_label() { return this->label; }

			virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);

			virtual void modulate_from(boost::any arg);
			
			virtual void modulate_to(boost::any arg);
	};

}