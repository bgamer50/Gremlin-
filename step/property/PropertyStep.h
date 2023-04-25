#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Property.h"
#include <vector>
#include <string>
#include <boost/any.hpp>

#define PROPERTY_STEP 0x67

enum PropertyStepType { VALUE, PROPERTY };

class PropertyStep: public TraversalStep {
    private:
        std::vector<std::string> keys; //duplicates are allowed, per api
        PropertyStepType ps_type;

    public:
        PropertyStep(PropertyStepType type, std::vector<std::string> property_keys);

        inline std::vector<std::string>& get_keys() { return keys; }

        inline PropertyStepType get_type() { return ps_type; }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);

        using TraversalStep::getInfo;
        std::string getInfo();
};
