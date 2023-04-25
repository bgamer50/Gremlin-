#pragma once

#define GROUP_COUNT_STEP 0x62

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversalSource.h"
#include <optional>

class GroupCountStep : public TraversalStep {
    private:
        std::optional<std::string> by_key;

        struct gc_global_hash {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p) const {
                return p.first->test_hash(p.second);
            }
        };

        struct gc_global_equals {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p, const std::pair<GraphTraversalSource*, boost::any>& q) const {
                return p.first->test_equals(p.second, q.second);
            }
        };

    public:
        GroupCountStep();

        inline void set_by_key(std::string by_key) { this->by_key = by_key; }
        
        inline std::optional<std::string> get_by_key() { return this->by_key; }

        using TraversalStep::getInfo;
        virtual std::string getInfo();

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

};

