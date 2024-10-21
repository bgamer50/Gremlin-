#include "step/embedding/LikeStep.h"
#include "structure/Graph.h"
#include "traversal/GraphTraversal.h"

#include "maelstrom/algorithms/filter.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/topk.h"

namespace gremlinxx {

    LikeStep::LikeStep(std::string name, std::vector<maelstrom::vector>& embs, std::optional<double> threshold, std::optional<size_t> count, maelstrom::similarity_t metric)
    : TraversalStep(FILTER, LIKE_STEP) {
        if(!threshold && !count) {
            throw std::invalid_argument("Either threshold, count, or both must be provided for LikeStep");
        }

        this->emb_name = name;
        this->match_threshold = threshold;
        this->count = count;
        this->similarity_metric = metric;

        this->emb_stride = embs[0].size();
        this->embeddings = maelstrom::vector(
            embs[0].get_mem_type(),
            embs[0].get_dtype()
        );
        this->embeddings.reserve(this->emb_stride * embs.size());

        for(maelstrom::vector& vec : embs) {
            if(vec.size() != this->emb_stride) {
                throw std::invalid_argument("Embedding lengths do not match");
            }
            this->embeddings.insert(vec);
        }
    }

    void LikeStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        Graph* graph = traversal->getGraph();

        traversers.advance([this, &graph](auto& data, auto& se, auto& paths){
            auto src_emb = graph->get_vertex_embeddings(this->emb_name, data);

            maelstrom::vector empty;
            auto sim = maelstrom::similarity(
                this->similarity_metric,
                src_emb,
                empty,
                this->embeddings,
                this->emb_stride
            );

            maelstrom::vector z, ix;
            if(this->match_threshold) {
                ix = maelstrom::filter(
                    sim,
                    maelstrom::GREATER_THAN_OR_EQUAL,
                    this->match_threshold
                );

                z = maelstrom::select(
                    data,
                    ix
                );
            }

            if(this->count) {
                if(this->match_threshold) {
                    auto tix = maelstrom::topk(z, this->count.value());
                    z = maelstrom::select(z, tix);
                    ix = maelstrom::select(ix, tix);
                } else {
                    ix = maelstrom::topk(sim, this->count.value());
                    z = maelstrom::select(data, ix);
                }
            } 

            return std::make_pair(
                std::move(z),
                std::move(ix)
            );
        });
    }

    std::string LikeStep::getInfo() {
        return "LikeStep{}";
    }

}