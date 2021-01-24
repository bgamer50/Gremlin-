#ifndef ORDER_STEP_H
#define ORDER_STEP_H

#define ORDER_STEP 0x47

#include <string>
#include <boost/any.hpp>

#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"

// In the future this may get optimized away for most traversals by moving
// the barrier to the left of the step and testing each element upon appearance
class OrderStep: public TraversalStep, virtual public ByModulating {
    private:
        GraphTraversal* order_traversal = nullptr; // TODO make this do something

    public:
        // This is a barrier step
        OrderStep()
        : TraversalStep(true, MAP, ORDER_STEP) {}

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
        virtual std::string getInfo();

        virtual void modulate_by(boost::any arg) { this->order_traversal = boost::any_cast<GraphTraversal*>(arg); }
};

inline void OrderStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* source = traversal->getTraversalSource();
    auto cmp = [source](Traverser& t1, Traverser& t2) {return source->test_compare(t1.get(), t2.get()) < 0;};

    std::sort(traversers.begin(), traversers.end(), cmp);
}

inline std::string OrderStep::getInfo() {
    if(this->order_traversal == nullptr) return "OrderStep()";
    else return "OrderStep(" + this->order_traversal->explain() + ")";
}

#endif