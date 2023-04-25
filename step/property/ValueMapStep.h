#pragma once

#define VALUEMAP_STEP 0x68

#include <boost/any.hpp>
#include <vector>
#include <unordered_map>

#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"
#include "traversal/Traverser.h"

class GraphTraversal;
class TraversalStep;

class ValueMapStep: public TraversalStep, virtual public ByModulating {
    private:
        std::vector<std::string> keys;
        GraphTraversal* by_traversal = nullptr;

    public:
        ValueMapStep(std::vector<std::string>& keys);
        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
        
        virtual void modulate_by(boost::any arg);

        using TraversalStep::getInfo;
        std::string getInfo();
};


