#pragma once

#define GROUP_COUNT_STEP 0x62

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversalSource.h"
#include <optional>

namespace gremlinxx {

    class GroupCountStep : public TraversalStep {
        private:
            const std::string DEFAULT_KEY = "GROUP";
            std::optional<std::string> by_key;

        public:
            GroupCountStep();

            inline void set_by_key(std::string by_key) { this->by_key = by_key; }
            
            inline std::optional<std::string> get_by_key() { return this->by_key; }

            using TraversalStep::getInfo;
            virtual std::string getInfo();

            /*
                There are some important semantic differences with the GroupCount step in Gremlin++:
                    (1) All paths and side effects are invalidated upon calling this step.
                    (2) Each output traverser is a size_t with a single side effect (the by key).
                    (3) If there was no by key, the side effect key is "GROUP"
            */
            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

    };

}