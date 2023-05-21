#include "step/edge/AddEdgeStep.h"
#include "structure/Graph.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include <tuple>

namespace gremlinxx {
    
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
        if(arg.type() == typeid(GraphTraversal*)) this->out_vertex_traversal = boost::any_cast<GraphTraversal*>(arg);
        else {
            this->out_vertex_traversal = new GraphTraversal();
            this->out_vertex_traversal->inject({arg});
        }
    }

    void AddEdgeStep::modulate_to(boost::any arg) {
        if(arg.type() == typeid(GraphTraversal*)) this->in_vertex_traversal = boost::any_cast<GraphTraversal*>(arg);
        else {
            this->in_vertex_traversal = new GraphTraversal();
            this->in_vertex_traversal->inject({arg});
        }
    }

    void AddEdgeStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        // TODO run the traversals on everything at once - don't unpack anything, instead use the final traversal results
        // TODO allow multiple src/dst outputted by the traversal

        GraphTraversalSource* src = traversal->getTraversalSource();
        Graph* graph = traversal->getGraph();

        if(src == nullptr) throw std::runtime_error("Cannot call AddEdgeStep from an anonymous traversal!");
        if(graph == nullptr) throw std::runtime_error("Cannot add edges without access to the graph!");

        auto unpacked_traversers = traversers.unpack();
        std::vector<boost::any> added_edges;
        added_edges.reserve(traversers.size());
        for(auto it = unpacked_traversers.begin(); it != unpacked_traversers.end(); ++it) {
            Vertex* from_vertex;
            Vertex* to_vertex;
            bool used_current_traverser = false;

            if(this->out_vertex_traversal == nullptr) {
                try {
                    from_vertex = boost::any_cast<Vertex*>(std::get<0>(*it).get(0));
                } catch(boost::bad_any_cast& exc) { throw std::runtime_error("Attempted to add an edge from something that is not a Vertex!"); }
                catch(std::out_of_range& exr) { throw std::runtime_error("Attempted to add an edge but incoming traversal was empty!"); }
                
                used_current_traverser = true;
            } else {
                GraphTraversal from_traversal(src, out_vertex_traversal);
                from_traversal.getTraverserSet().reinitialize(
                    std::move(std::get<0>(*it)),
                    std::move(std::get<1>(*it)),
                    std::move(std::get<2>(*it))
                );
                
                from_vertex = boost::any_cast<Vertex*>(from_traversal.next());
            }

            if(this->in_vertex_traversal == nullptr) {
                if(used_current_traverser) throw std::runtime_error("No from/to step was provided.");

                try {
                    to_vertex = boost::any_cast<Vertex*>(std::get<0>(*it).get(0));
                } catch(boost::bad_any_cast& exc) { throw std::runtime_error("Attempted to add an edge to something that is not a Vertex!"); }
                catch(std::out_of_range& exr) { throw std::runtime_error("Attempted to add an edge but incoming traversal was empty!"); }
            } else {
                GraphTraversal to_traversal(src, in_vertex_traversal);
                to_traversal.getTraverserSet().reinitialize(
                    std::move(std::get<0>(*it)),
                    std::move(std::get<1>(*it)),
                    std::move(std::get<2>(*it))
                );
                
                to_vertex = boost::any_cast<Vertex*>(to_traversal.next());
            }

            added_edges.push_back(
                graph->add_edge(from_vertex, to_vertex, label)
            );
        }

        traversers.advance([&added_edges, graph](auto& traverser_data, auto& traverser_se, auto& traverser_path_info){
            auto m_edges = maelstrom::make_vector_from_anys(
                traverser_data.get_mem_type(),
                graph->get_edge_dtype(),
                added_edges
            );

            return std::make_pair(
                m_edges,
                maelstrom::vector()
            );
        });
    }

}