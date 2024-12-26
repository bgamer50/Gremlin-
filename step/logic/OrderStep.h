#pragma once

#define ORDER_STEP 0x47
#define ORDER_STEP_SIDE_EFFECT_KEY "__OrderStep__originating_traverser__"

#include <string>
#include <any>

#include "structure/Order.h"
#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"
#include "step/modulate/ByModulating.h"

namespace gremlinxx {    
    // In the future this may get optimized away for most traversals by moving
    // the barrier to the left of the step and testing each element upon appearance
    class OrderStep: public TraversalStep, virtual public ByModulating {
        private:
            std::optional<GraphTraversal> order_traversal;
            std::optional<Order> order;

        public:
            // This is a barrier step
            OrderStep();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
            virtual std::string getInfo(GraphTraversal* parent_traversal);

            virtual void modulate_by(std::any arg);
    };

}