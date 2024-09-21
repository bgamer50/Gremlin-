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
            LikeStep(std::string emb_name, std::vector<maelstrom::vector>& embs, double threshold, maelstrom::similarity_t metric=maelstrom::COSINE);

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            inline maelstrom::vector get_embeddings() { return this->embeddings; }
            inline std::string get_embedding_name() { return this->emb_name; }
            inline size_t get_embedding_stride() { return this->emb_stride; } 
            inline double get_match_threshold() { return this->match_threshold; }
            inline maelstrom::similarity_t get_metric() { return this->similarity_metric; }

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}