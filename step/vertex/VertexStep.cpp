#include "step/vertex/VertexStep.h"

#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/Graph.h"

namespace gremlinxx {

    VertexStep::VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, VertexStepType gsType_arg)
    : TraversalStep(MAP, VERTEX_STEP) {
        direction = dir;
        std::for_each(edge_labels_arg.begin(), edge_labels_arg.end(), [&](std::string str){ this->edge_labels.insert(str); });
        this->vsType = gsType_arg;
    }

    VertexStep::VertexStep(Direction dir, VertexStepType gsType_arg)
    : TraversalStep(MAP, VERTEX_STEP) {
        direction = dir;
        this->vsType = gsType_arg;
    }

    std::string VertexStep::getInfo() {
        std::string info = "VertexStep(";
        info += (direction == IN ? "IN" : direction == OUT ? "OUT" : "BOTH");
        info += ", ";
        if(!edge_labels.empty()) {
            info += "{";
            auto p = edge_labels.begin();
            for(int k = 0; k < edge_labels.size() - 1; k++) info = info + *(p++) + ", ";
            info = info + *p + "}";
        }
        else info += "{}";
        info = info + ", " + (vsType == VERTEX_TO_VERTEX ? "VERTEX" : "EDGE");
        return info + ")";
    }

    void VertexStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        auto vs_type = this->vsType;
        auto graph = traversal->getGraph();
        std::vector<std::string> labels(this->edge_labels.begin(), this->edge_labels.end());
        auto dir = this->direction;

        traversers.advance([&graph, vs_type, &labels, dir](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            maelstrom::vector successors;
            maelstrom::vector output_origin;
            switch(vs_type) {
                case VERTEX_TO_VERTEX: {
                    if(traverser_data.empty()) {
                        successors = maelstrom::vector(traverser_data.get_mem_type(), graph->get_vertex_dtype());
                        output_origin = maelstrom::vector();
                    } else {
                        if(traverser_data.get_dtype() != graph->get_vertex_dtype()) throw std::runtime_error("Can only call out()/in() on vertices!");
                        std::tie(
                            successors,
                            output_origin
                        ) = graph->V(traverser_data, labels, dir);
                    }
                    break;
                }
                case VERTEX_TO_EDGE: {
                    if(traverser_data.empty()) {
                        successors = maelstrom::vector(traverser_data.get_mem_type(), graph->get_edge_dtype());
                        output_origin = maelstrom::vector();
                    } else {
                        if(traverser_data.get_dtype() != graph->get_vertex_dtype()) throw std::runtime_error("Can only call outE()/inE() on vertices!");
                        std::tie(
                            successors,
                            output_origin
                        ) = graph->E(traverser_data, labels, dir);
                    }
                    break;
                }
                case EDGE_TO_VERTEX: {
                    if(traverser_data.empty()) {
                        successors = maelstrom::vector(traverser_data.get_mem_type(), graph->get_vertex_dtype());
                        output_origin = maelstrom::vector();
                    } else {
                        if(traverser_data.get_dtype() != graph->get_edge_dtype()) throw std::runtime_error("Can only call outV()/inV() on edges!");
                        std::tie(
                            successors,
                            output_origin
                        ) = graph->toV(traverser_data, dir);
                    }
                    break;
                }
                default: {
                    throw std::runtime_error("Invalid vertex step type");
                }
            }

            return std::make_pair(
                std::move(successors),
                std::move(output_origin)
            );
        });
    }

}