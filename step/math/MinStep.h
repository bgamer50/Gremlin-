#pragma once

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/Scope.h"
#include "traversal/Comparison.h"

#include <functional>

class MinStep : public TraversalStep {
    private:
        std::optional<ScopeContext> scope_context;
        gremlinxx::comparison::C comparison_type;

        void apply_global(GraphTraversal* traversal, TraverserSet& traversers);

        void apply_local(GraphTraversal* traversal, TraverserSet& traversers);

    public:
        MinStep(gremlinxx::comparison::C cmp_type);

        inline void set_scope_context(ScopeContext sc) { this->scope_context = sc; }
        
        inline gremlinxx::comparison::C get_comparison_type() { return this->comparison_type; }

        inline Traverser min(Traverser& t1, Traverser& t2) {
            return C_LESS(this->comparison_type, t1.get(), t2.get()) ? t1 : t2;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

        using TraversalStep::getInfo;
        virtual std::string getInfo();
};
