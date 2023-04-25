#include "step/edge/AddEdgeStep.h"
#include "structure/Graph.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

AddEdgeStep::AddEdgeStep(std::string label_arg)
: TraversalStep(MAP, ADD_EDGE_STEP) {
    label = label_arg;
    out_vertex_traversal = NULL;
    in_vertex_traversal = NULL;
}

std::string AddEdgeStep::getInfo() {
    std::string info = "AddEdgeStep(";
    info += label + ")";
    return info;
}

void AddEdgeStep::modulate_from(boost::any arg) { 
    if(arg.type() == typeid(Vertex*)) {
        this->out_vertex_traversal = new GraphTraversal();
        this->out_vertex_traversal->setInitialTraversers({Traverser(arg)});
    }
    else if(arg.type() == typeid(GraphTraversal*)) this->out_vertex_traversal = boost::any_cast<GraphTraversal*>(arg); 
    else throw std::runtime_error("Invalid object passed in from() to AddEdgeStep");			
}

void AddEdgeStep::modulate_to(boost::any arg) {
    if(arg.type() == typeid(Vertex*)) {
        this->in_vertex_traversal = new GraphTraversal();
        this->in_vertex_traversal->setInitialTraversers({Traverser(arg)});
    }
    else if(arg.type() == typeid(GraphTraversal*)) this->in_vertex_traversal = boost::any_cast<GraphTraversal*>(arg);
    else throw std::runtime_error("Invalid object passed in to() to AddEdgeStep");		
}

void AddEdgeStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
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
            from_traversal.setInitialTraversers({trv});
            //std::cout << "about to call from_traversal.next()" << std::endl;
            //std::cout << from_traversal.explain() << std::endl;
            from_vertex = boost::any_cast<Vertex*>(from_traversal.next());
        }

        if(this->in_vertex_traversal == nullptr) {
            if(used_current_traverser) {
                throw std::runtime_error("No from/to step was provided.");
            }
            to_vertex = boost::any_cast<Vertex*>(trv.get());
        } else { 
            GraphTraversal to_traversal(my_traversal_source, this->in_vertex_traversal);
            to_traversal.setInitialTraversers({trv});
            to_vertex = boost::any_cast<Vertex*>(to_traversal.next()); 
        }

        Graph* my_graph = my_traversal_source->getGraph();
        Edge* new_edge = my_graph->add_edge(from_vertex, to_vertex, label);
        trv.replace_data(new_edge);
    });
}