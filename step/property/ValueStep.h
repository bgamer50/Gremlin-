#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Property.h"
#include <vector>
#include <string>
#include <boost/any.hpp>

#define VALUE_STEP 0x67

namespace gremlinxx {

    class ValueStep: public TraversalStep {
        private:
            std::vector<std::string> keys; //duplicates are allowed, per api

        public:
            ValueStep(std::vector<std::string> property_keys);

            inline std::vector<std::string>& get_keys() { return keys; }

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}