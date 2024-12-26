#pragma once

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"

#include <optional>

#define REPEAT_STEP 0x42
#define LOOPS_TRAVERSAL_PROPERTY std::string("TRV_LOOPS")

namespace gremlinxx {
    
    class RepeatStep: public TraversalStep {
        private:
            // Will emit anything out of the loop that passes through this traversal.
            std::optional<GraphTraversal> emitTraversal;
            
            // Will end the loop when this traversal is completed.
            std::optional<GraphTraversal> untilTraversal;

            // The action to be repeated.
            GraphTraversal actionTraversal;

            // The # of times to run the loop
            std::optional<size_t> times;

        public:
            RepeatStep(GraphTraversal actionTraversal);

            inline GraphTraversal& getActionTraversal() { 
                return this->actionTraversal;
            }

            inline void setEmitTraversal(GraphTraversal emitTraversal) { this->emitTraversal.emplace(emitTraversal); }
            inline GraphTraversal& getEmitTraversal() { 
                if(!this->emitTraversal) throw std::runtime_error("Traversal does not have an emit traversal!");
                return this->emitTraversal.value(); 
            }
            inline bool hasEmitTraversal() { return emitTraversal.has_value(); }

            inline void setUntilTraversal(GraphTraversal untilTraversal) { this->untilTraversal.emplace(untilTraversal); }
            inline GraphTraversal& getUntilTraversal() { 
                if(!this->untilTraversal) throw std::runtime_error("Traversal does not have an until traversal!");
                return this->untilTraversal.value(); 
            }
            inline bool hasUntilTraversal() { return untilTraversal.has_value(); }

            inline void setTimes(size_t times) { this->times.emplace(times); }
            inline size_t getTimes() { 
                if(!this->times) throw std::runtime_error("Traversal does not have a times parameter!");
                return this->times.value();
            }
            inline bool hasTimes() { return times.has_value(); }


            virtual void apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers);

            using TraversalStep::getInfo;
            virtual std::string getInfo();
            

    };

}