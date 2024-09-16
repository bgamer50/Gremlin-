#include "step/embedding/SimilarityStep.h"
#include "traversal/GraphTraversal.h"
#include "structure/Graph.h"

#include "maelstrom/algorithms/arange.h"

namespace gremlinxx {

    SimilarityStep::SimilarityStep(std::string emb_name, std::vector<maelstrom::vector>& embedding_values, maelstrom::similarity_t metric=maelstrom::COSINE)
    : TraversalStep(MAP, SIMILARITY_STEP) {
        this->similarity_metric = metric;
        this->name = emb_name;
        
        this->embeddings = maelstrom::vector(
            embedding_values[0].get_mem_type(),
            embedding_values[0].get_dtype()
        );

        this->emb_stride = embedding_values[0].size();
        this->embeddings.reserve(this->emb_stride * embedding_values.size());

        for(maelstrom::vector& vec : embedding_values) {
            if(vec.size() != this->emb_stride) {
                throw std::invalid_argument("Embedding lengths do not match");
            }
            this->embeddings.insert(vec);
        }
    }

    void SimilarityStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        Graph* graph = traversal->getGraph();
        traversers.advance([this, &graph](auto& data, auto& se, auto& paths){
            auto trv_emb = graph->get_vertex_embeddings(this->name, data);

            maelstrom::vector empty;
            auto sim_vals = maelstrom::similarity(
                this->similarity_metric,
                trv_emb,
                empty,
                this->embeddings,
                this->emb_stride
            );

            return std::make_pair(
                std::move(sim_vals),
                std::move(
                    maelstrom::arange(data.get_mem_type(), data.size())
                )
            );
        });
    }

    std::string SimilarityStep::getInfo() {
        return "SimilarityStep{}";
    }

}