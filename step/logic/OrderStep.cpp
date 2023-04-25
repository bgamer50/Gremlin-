#include "step/logic/OrderStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

// This is a barrier step
OrderStep::OrderStep()
: TraversalStep(true, MAP, ORDER_STEP) {}


void OrderStep::modulate_by(boost::any arg) { this->order_traversal = boost::any_cast<GraphTraversal*>(arg); }

std::string OrderStep::getInfo() {
    if(this->order_traversal == nullptr) return "OrderStep()";
    else return "OrderStep(" + this->order_traversal->explain() + ")";
}

void OrderStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* source = traversal->getTraversalSource();
    auto cmp = [source](Traverser& t1, Traverser& t2) {return source->test_compare(t1.get(), t2.get()) < 0;};

    std::sort(traversers.begin(), traversers.end(), cmp);
}