#pragma once

#define SIMILARITY_STEP 0x8a

#include "step/TraversalStep.h"
#include "maelstrom/algorithms/similarity.h"

namespace gremlinxx {

    class SimilarityStep : public TraversalStep {
        private:
            maelstrom::similarity_t similarity_metric;
            std::string name;
            maelstrom::vector embeddings;
            size_t emb_stride;

        public:
            SimilarityStep(std::string emb_name, std::vector<maelstrom::vector>& embedding_values, maelstrom::similarity_t metric=maelstrom::COSINE);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}