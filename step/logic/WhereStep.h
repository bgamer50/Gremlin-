#ifndef WHERE_STEP_H
#define WHERE_STEP_H

#define WHERE_STEP 0x45

#include "step/TraversalStep.h"
#include <unordered_map>
#include <string>

class WhereStep: public TraversalStep {
    private:
        std::string label;
        P predicate = P(P::Comparison::EQ, boost::any());

    public:
        WhereStep(std::string label, P predicate)
        : TraversalStep(MODULATOR, WHERE_STEP) {
            this->label = label;
            this->predicate = predicate;
        }

        std::string getLabel() { return this->label; }
        P getPredicate() { return this->predicate; }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
};

void WhereStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* src = traversal->getTraversalSource();
    boost::any val = this->predicate.operand;

    TraverserSet new_traversers;
    for(Traverser& traverser: traversers)  {
        boost::any t = boost::any_cast<std::unordered_map<std::string, boost::any>>(traverser.get())[this->label];
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
                throw std::runtime_error("Comparison type not supported by WhereStep.");
        }
    }

    traversers.swap(new_traversers);
}

#endif