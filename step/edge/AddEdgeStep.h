#ifndef ADD_EDGE_STEP_H
#define ADD_EDGE_STEP_H

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "step/InjectStep.h"
#include <string>
#include <vector>

#define ADD_EDGE_STEP 0x73

class AddEdgeStep: public TraversalStep {
	private:
		std::string label;
		GraphTraversal* out_vertex_traversal; // filled in at runtime
		GraphTraversal* in_vertex_traversal; // filled in at runtime
	public:
		AddEdgeStep(std::string label_arg)
		: TraversalStep(MAP, ADD_EDGE_STEP) {
			label = label_arg;
			out_vertex_traversal = NULL;
			in_vertex_traversal = NULL;
		}

		virtual std::string getInfo() {
			std::string info = "AddEdgeStep(";
			info += label + ")";
			return info;
		}

		GraphTraversal* get_out_traversal() { return this->out_vertex_traversal; }
		GraphTraversal* get_in_traversal() { return this->in_vertex_traversal; }
		void set_out_traversal(GraphTraversal* new_traversal) { this->out_vertex_traversal = new_traversal; }
		void set_in_traversal(GraphTraversal* new_traversal) { this->in_vertex_traversal = new_traversal; }
		std::string get_label() { return this->label; }

		virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
			// For each traverser
			std::for_each(traversers.begin(), traversers.end(), [&, this](Traverser& trv) {
				// Need to check if there is enough info to add the Edge, then add it if we can.
				
				GraphTraversalSource* my_traversal_source = traversal->getTraversalSource();
				if(my_traversal_source == NULL) throw std::runtime_error("Cannot call this step from an anonymous traversal!");

				Vertex* from_vertex;
				Vertex* to_vertex;
				bool used_current_traverser = false;
				if(this->out_vertex_traversal == nullptr) {
					from_vertex = boost::any_cast<Vertex*>(trv.get());
					used_current_traverser = true;
				} else { 
					GraphTraversal from_traversal(my_traversal_source, this->out_vertex_traversal);
					std::vector<boost::any> inj; inj.push_back(trv.get());
					InjectStep inject_step(inj);
					from_traversal.insertStep(0, &inject_step);
					from_vertex = boost::any_cast<Vertex*>(from_traversal.next());
				}

				if(this->in_vertex_traversal == nullptr) {
					if(used_current_traverser) {
						throw std::runtime_error("No from/to step was provided.");
					}
					to_vertex = boost::any_cast<Vertex*>(trv.get());
				} else { 
					GraphTraversal to_traversal(my_traversal_source, this->in_vertex_traversal);
					std::vector<boost::any> inj; inj.push_back(trv.get());
					InjectStep inject_step(inj);
					to_traversal.insertStep(0, &inject_step);
					to_vertex = boost::any_cast<Vertex*>(to_traversal.next()); 
				}

				Graph* my_graph = my_traversal_source->getGraph();
				Edge* new_edge = my_graph->add_edge(from_vertex, to_vertex, label);
				trv.replace_data(new_edge);
			});
		}
};

#endif