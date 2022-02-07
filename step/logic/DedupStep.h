#ifndef DEDUP_STEP_H
#define DEDUP_STEP_H

#define DEDUP_STEP 0x49

#include <string>
#include <functional>
#include <optional>

#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"

// In the future this may get optimized away for most traversals by moving
// the barrier to the left of the step and testing each element upon appearance
class DedupStep: public TraversalStep, virtual public ByModulating {
    private:
        std::optional<std::string> dedup_by_key; // TODO make this actually do something

        struct dc_global_hash {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p) const {
                return p.first->test_hash(p.second);
            }
        };

        struct dc_global_equals {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p, const std::pair<GraphTraversalSource*, boost::any>& q) const {
                return p.first->test_equals(p.second, q.second);
            }
        };

    public:
        // This is a barrier step
        DedupStep()
        : TraversalStep(true, FILTER, DEDUP_STEP) {}

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
        virtual std::string getInfo();

        virtual void modulate_by(boost::any arg) { this->dedup_by_key = boost::any_cast<std::string>(arg); }
};

inline void DedupStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* source = traversal->getTraversalSource();
    
    std::unordered_set<std::pair<GraphTraversalSource*, boost::any>, dc_global_hash, dc_global_equals> deduplicated_set;
    deduplicated_set.reserve(traversers.size() / 10 + 10);
    for(auto it = traversers.begin(); it != traversers.end(); ++it) {
        if(!deduplicated_set.insert(std::make_pair(source, it->get())).second) {
            it = traversers.erase(it) - 1;
        }
    }
}

inline std::string DedupStep::getInfo() {
    return "DedupStep(" + this->dedup_by_key.value_or("") + ")";
}

#endif