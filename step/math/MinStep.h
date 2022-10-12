#ifndef MIN_STEP_H
#define MIN_STEP_H

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/Scope.h"

#include <functional>
#include <execution>

#include <tbb/concurrent_unordered_map.h>

class MinStep : public TraversalStep {
    private:
        std::function<int(Traverser&, Traverser&)> compare;
        std::optional<ScopeContext> scope_context;

        void apply_global(GraphTraversal* traversal, TraverserSet& traversers) {
            Traverser min_value = traversers.front();
            for(Traverser t : traversers) {
                min_value = this->min(t, min_value);
            }
            
            traversers.clear();
            traversers.push_back(min_value);
        }

        void apply_local(GraphTraversal* traversal, TraverserSet& traversers) {
            tbb::concurrent_unordered_map<scope_group_t, Traverser> min_values;
            //std::unordered_map<scope_group_t, Traverser> min_values;
            std::for_each(std::execution::par_unseq, traversers.begin(), traversers.end(), [this, &min_values](Traverser& t){
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
        MinStep(std::function<int(Traverser&, Traverser&)> c)
        : TraversalStep(true, MAP, MIN_STEP) {
            compare = c;
        }

        void set_scope_context(ScopeContext sc) { this->scope_context = sc; }

        Traverser min(Traverser& t1, Traverser& t2) {
            int cmp = compare(t1, t2);
            return cmp < 0 ? t1 : t2;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            if(!traversers.empty()) {
                if(!scope_context || scope_context->scope == global) apply_global(traversal, traversers);
                else apply_local(traversal, traversers);
            }
        }
};

#endif