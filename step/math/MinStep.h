#ifndef MIN_STEP_H
#define MIN_STEP_H

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <functional>
#include <omp.h>

class MinStep : public TraversalStep {
    private:
        std::function<int(Traverser&, Traverser&)> compare;

    public:
        MinStep(std::function<int(Traverser&, Traverser&)> c)
        : TraversalStep(true, MAP, MIN_STEP) {
            compare = c;
        }

        Traverser min(Traverser& t1, Traverser& t2) {
            int cmp = compare(t1, t2);
            return cmp < 0 ? t1 : t2;
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            if(!traversers.empty()) {
                Traverser min_value = traversers.front();
                for(Traverser t : traversers) {
                    min_value = this->min(t, min_value);
                }
                
                traversers.clear();
			    traversers.push_back(min_value);
            }
        }
};

#endif