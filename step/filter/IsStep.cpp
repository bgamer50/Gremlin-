#include "step/filter/IsStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

IsStep::IsStep(P predicate)
: TraversalStep(FILTER, IS_STEP) {
    this->predicate = predicate;
}

std::string IsStep::getInfo() { 
    std::string info = "IsStep{}";

    return info;
}

void IsStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* src = traversal->getTraversalSource();
    boost::any val = this->predicate.operand;

    TraverserSet new_traversers;
    for(Traverser& traverser: traversers)  {
        boost::any t = traverser.get();
        switch(this->predicate.comparison) {
            case P::Comparison::EQ:
                if(src->test_equals(t, val)) new_traversers.push_back(traverser);
                break;
            case P::Comparison::NEQ:
                if(!src->test_equals(t, val)) new_traversers.push_back(traverser);
                break;
            case P::Comparison::GT:
                if(src->test_compare(t, val) > 0) new_traversers.push_back(traverser);
                break;
            case P::Comparison::GTE:
                if(src->test_compare(t, val) >= 0) new_traversers.push_back(traverser);
                break;
            case P::Comparison::LT:
                if(src->test_compare(t, val) < 0) new_traversers.push_back(traverser);
                break;
            case P::Comparison::LTE:
                if(src->test_compare(t, val) <= 0) new_traversers.push_back(traverser);
                break;
            case P::Comparison::BETWEEN: {
                std::pair<boost::any, boost::any> p = boost::any_cast<std::pair<boost::any, boost::any>>(val);
                if(src->test_compare(t, p.first) >= 0 && src->test_compare(t, p.second) < 0) new_traversers.push_back(traverser);
                break;
            }
            default:
                throw std::runtime_error("Comparison type not supported by IsStep.");
        }
    }

    traversers.swap(new_traversers);
}