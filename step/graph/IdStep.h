#pragma once

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

#define ID_STEP 0x66

namespace gremlinxx {

    class IdStep : public TraversalStep {
        public:
            IdStep();
            
            using TraversalStep::getInfo;
            virtual std::string getInfo();

            virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);
            
    };

}