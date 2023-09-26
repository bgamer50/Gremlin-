#pragma once

#define ELEMENTMAP_STEP 0x68
#define ELEMENTMAP_ID_KEY "id"
#define ElEMENTMAP_LABEL_KEY "label"

#include <any>
#include <vector>
#include <unordered_map>

#include "step/TraversalStep.h"
#include "step/modulate/ByModulating.h"

namespace gremlinxx {

    /*
        Unlike the original ElementMapStep, in gremlin++, this step will throw out
        any vertices that don't have the given keys and output the element map
        as side effects.  Providing no keys will result in just the id and label
        going into the map.
    */
    class ElementMapStep: public TraversalStep, virtual public ByModulating {
        private:
            std::vector<std::string> keys;
            GraphTraversal* by_traversal = nullptr;

        public:
            ElementMapStep(std::vector<std::string>& keys);
            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);
            
            virtual void modulate_by(std::any arg);

            using TraversalStep::getInfo;
            std::string getInfo();
    };

}