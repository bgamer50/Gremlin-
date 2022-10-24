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

        void apply_global(GraphTraversal* traversal, TraverserSet& traversers) {
            Traverser min_value = traversers.front();
            for(Traverser t : traversers) {
                min_value = this->min(t, min_value);
            }
            
            traversers.clear();
            traversers.push_back(min_value);
        }

        void apply_local(GraphTraversal* traversal, TraverserSet& traversers) {
            std::unordered_map<scope_group_t, Traverser> min_values;
            std::for_each(traversers.begin(), traversers.end(), [this, &min_values](Traverser& t){
                scope_group_t group_id = boost::any_cast<scope_group_t>(t.get_side_effects()[*this->scope_context->side_effect_key]);
                if(min_values.find(group_id) == min_values.end()) min_values[group_id] = t;
                else {
                    auto old_min = min_values[group_id];
                    min_values[group_id] = this->min(t, old_min);
                }
            });
            
            traversers.clear();
            for(auto it = min_values.begin(); it != min_values.end(); ++it) traversers.push_back(it->second);
        }

    public:
        MinStep(gremlinxx::comparison::C comparison_type)
        : TraversalStep(true, MAP, MIN_STEP) {
            this->comparison_type = comparison_type;
        }

        void set_scope_context(ScopeContext sc) { this->scope_context = sc; }
        
        gremlinxx::comparison::C get_comparison_type() { return this->comparison_type; }

        Traverser min(Traverser& t1, Traverser& t2) {
            return C_LESS(this->comparison_type, t1.get(), t2.get()) ? t1 : t2;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            if(!traversers.empty()) {
                if(!scope_context || scope_context->scope == global) apply_global(traversal, traversers);
                else apply_local(traversal, traversers);
            }
        }
};
