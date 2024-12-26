#pragma once

#define ENCODE_STEP 0x8c

#include "step/TraversalStep.h"

namespace gremlinxx {

    class EncodeStep : public TraversalStep {
        private:
            std::string emb_name;
        public:
            EncodeStep(std::string embedding_name);

            using TraversalStep::apply;
            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}