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
			GraphTraversal* out_vertex_traversal; // filled in at runtime
			GraphTraversal* in_vertex_traversal; // filled in at runtime
		public:
			AddEdgeStep(std::string label_arg);

			using TraversalStep::getInfo;
			virtual std::string getInfo();

			inline GraphTraversal* get_out_traversal() { return this->out_vertex_traversal; }
			inline GraphTraversal* get_in_traversal() { return this->in_vertex_traversal; }
			inline std::string get_label() { return this->label; }

			virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

			virtual void modulate_from(boost::any arg);

			virtual void modulate_to(boost::any arg);
	};

}