#ifndef PROPERTY_STEP_H
#define PROPERTY_STEP_H

#include "TraversalStep.h"
#include "Property.h"
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
        PropertyStep(PropertyStepType type, std::vector<std::string> property_keys)
        : TraversalStep(MAP, PROPERTY_STEP) {
            this->keys = property_keys;
            this->ps_type = type;
        }

        std::vector<std::string>& get_keys() { return keys; }

        PropertyStepType get_type() { return ps_type; }
};

#endif