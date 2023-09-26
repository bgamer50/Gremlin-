#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/Scope.h"
#include "traversal/Comparison.h"

#include <optional>

namespace gremlinxx {

    class ReductionStep : public TraversalStep {
        protected:
            std::optional<ScopeContext> scope_context;
        
        public:

            ReductionStep(unsigned int id)
            : TraversalStep(true, MAP, id) {}

            inline void set_scope_context(ScopeContext sc) { this->scope_context = sc; }

            virtual void apply_global(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) = 0;

            virtual void apply_local(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) = 0;

            using TraversalStep::apply;
            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
                if(!scope_context || scope_context->scope == global) apply_global(traversal, traversers);
                else apply_local(traversal, traversers);
            }

            using TraversalStep::getInfo;
            virtual std::string getInfo() = 0;

    };

}