#include "step/filter/WhereStep.h"
#include "traversal/Traverser.h"
#include "traversal/P.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

WhereStep::WhereStep(std::string label, P predicate)
: TraversalStep(FILTER, WHERE_STEP) {
    this->label = label;
    this->predicate = predicate;
}

void WhereStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* src = traversal->getTraversalSource();
    std::string val_label;
    try { val_label = boost::any_cast<std::string>(this->predicate.operand); }
    catch(const std::exception& err) { val_label =  boost::any_cast<const char*>(this->predicate.operand);}

    TraverserSet new_traversers;
    for(Traverser& traverser: traversers)  {
        boost::any t = boost::any_cast<std::unordered_map<std::string, boost::any>>(traverser.get())[this->label];
        boost::any val = boost::any_cast<std::unordered_map<std::string, boost::any>>(traverser.get())[val_label];

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