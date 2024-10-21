#include "step/embedding/EncodeStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

#include "maelstrom/containers/vector.h"
#include "maelstrom/algorithms/arange.h"
#include "maelstrom/algorithms/increment.h"

#include "maelstrom/util/any_utils.h"

namespace gremlinxx {

    EncodeStep::EncodeStep(std::string embedding_name)
    : TraversalStep(MAP, ENCODE_STEP) {
        this->emb_name = embedding_name;
    }

    void EncodeStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        Graph* graph = traversal->getGraph();

        if(traversers.getCurrentDataType() != graph->get_vertex_dtype()) {
            throw std::runtime_error("Can only encode vertices.");
        }

        std::string& name = this->emb_name;
        traversers.advance([&graph, name](auto& data, auto& se, auto& paths){
            auto emb = graph->get_vertex_embeddings(name, data);
            const size_t emb_stride = emb.size() / graph->num_vertices();

            auto ix = maelstrom::arange(data.get_mem_type(), static_cast<size_t>(0), static_cast<size_t>(emb_stride * data.size()));
            maelstrom::increment(ix, emb_stride, maelstrom::DIVIDE);

            return std::make_pair(
                std::move(emb),
                std::move(ix)
            );
        });
        
    }

    std::string EncodeStep::getInfo() {
        return "EncodeStep{" + this->emb_name + "}";
    }

}
