#ifndef MIN_STEP_H
#define MIN_STEP_H

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "Traverser.h"
#include <functional>

class MinStep : public TraversalStep {
    private:
        std::function<int(Traverser*, Traverser*)> compare;

    public:
        MinStep(std::function<int(Traverser*, Traverser*)> c)
        : TraversalStep(MAP, MIN_STEP) {
            compare = c;
        }

        Traverser* min(Traverser* t1, Traverser* t2) {
            int cmp = compare(t1, t2);
            return cmp < 0 ? t1 : t2;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) { 
            Traverser* min = traversers.front();
			for(auto it = traversers.begin(); it != traversers.end(); ++it) {
				min = this->min(*it, min);
			}

			traversers.clear();
			traversers.push_back(min);
        }
};

#endif