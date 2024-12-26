#pragma once

#define EMBEDDING_STEP 0x76

#include "step/TraversalStep.h"
#include "maelstrom/containers/vector.h"

namespace gremlinxx {

    class EmbeddingStep: public TraversalStep {
        private:
            std::string name;
            maelstrom::vector embedding;
            std::any default_value;

        public:
            EmbeddingStep(std::string name, maelstrom::vector emb, std::any default_val=std::any())
            : TraversalStep(MAP, EMBEDDING_STEP) {
                this->name = name;
                this->embedding = std::move(emb);
                this->default_value = default_val;
            }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}