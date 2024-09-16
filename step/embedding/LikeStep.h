#pragma once

#define LIKE_STEP 0x8b

#include "step/TraversalStep.h"

#include "maelstrom/algorithms/similarity.h"

namespace gremlinxx {

    class LikeStep : public TraversalStep {
        private:
            maelstrom::vector embeddings;
            std::string emb_name;
            size_t emb_stride;
            double match_threshold;
            maelstrom::similarity_t similarity_metric;

        public:
            LikeStep(std::string emb_name, std::vector<maelstrom::vector> embs, double threshold, maelstrom::similarity_t metric=maelstrom::COSINE);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}