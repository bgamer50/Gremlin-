#ifndef LIMIT_STEP_H
#define LIMIT_STEP_H

#define LIMIT_STEP 0x48

#include <string>
#include "step/TraversalStep.h"

class LimitStep: public TraversalStep {
    private:
        uint64_t limit;

    public:
        LimitStep(uint64_t limit)
        : TraversalStep(FILTER, AS_STEP) {
            this->limit = limit;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
        virtual std::string getInfo() { return "LimitStep(" + std::to_string(limit) + ")"; }
        uint64_t get_limit() { return this->limit; }
};

inline void LimitStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    if(traversers.size() > this->limit) traversers.resize(limit);
}

#endif