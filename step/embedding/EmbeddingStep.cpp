#include "step/embedding/EmbeddingStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

namespace gremlinxx {

    void EmbeddingStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        Graph* graph = traversal->getGraph();
        auto data = traversers.getTraverserData();

        graph->set_vertex_embeddings(this->name, data, this->embedding, this->default_value);
    }

    std::string EmbeddingStep::getInfo() {
        return "EmbeddingStep{" + this->name + "}";
    }

}