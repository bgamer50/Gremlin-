#include "step/edge/AddEdgeStartStep.h"

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Graph.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

namespace gremlinxx {
    AddEdgeStartStep::AddEdgeStartStep(std::string label_arg)
    : TraversalStep(MAP, ADD_EDGE_START_STEP) {
        this->label = label_arg;
        this->out_vertex_traversal;
        this->in_vertex_traversal;
    }

    std::string AddEdgeStartStep::getInfo() {
        std::string info = "AddEdgeStartStep(";
        info += label + ")";
        return info;
    }

    void AddEdgeStartStep::modulate_from(GraphTraversal t_from) { 
        this->out_vertex_traversal.emplace(std::move(t_from));
    }

    void AddEdgeStartStep::modulate_to(GraphTraversal t_to) {
        this->in_vertex_traversal.emplace(t_to);		
    }

    void AddEdgeStartStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        // Need to check if there is enough info to add the Edge, then add it
        // if we can.
        // from() and to() are both always required here.
        GraphTraversalSource* my_traversal_source = trv->getTraversalSource();
        if(my_traversal_source == NULL) throw std::runtime_error("Cannot call this step from an anonymous traversal!\n");

        GraphTraversal from_traversal(my_traversal_source, this->out_vertex_traversal.value());
        GraphTraversal to_traversal(my_traversal_source, this->in_vertex_traversal.value());

        Vertex from_vertex = std::any_cast<Vertex>(from_traversal.next());
        Vertex to_vertex = std::any_cast<Vertex>(to_traversal.next());

        Edge new_edge = trv->getGraph()->add_edge(from_vertex, to_vertex, label);
        traversers.advance([new_edge, my_traversal_source](maelstrom::vector& data, std::unordered_map<std::string, maelstrom::vector>& se, gremlinxx::traversal::PathInfo& paths){
            std::vector<std::any> any_vec = {new_edge};
            return std::make_pair(
                maelstrom::make_vector_from_anys(
                    data.get_mem_type(),
                    my_traversal_source->getGraph()->get_edge_dtype(),
                    any_vec
                ),
                maelstrom::vector()
            );
        });
    }

}