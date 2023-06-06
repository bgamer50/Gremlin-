#pragma once

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/Scope.h"
#include "traversal/Comparison.h"

#include <optional>

namespace gremlinxx {

    class MinStep : public TraversalStep {
        private:
            std::optional<ScopeContext> scope_context;

            void apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            void apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

        public:
            MinStep();

            inline void set_scope_context(ScopeContext sc) { this->scope_context = sc; }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
    };

}