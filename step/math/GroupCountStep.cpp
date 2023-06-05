#include "step/math/GroupCountStep.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

#include "maelstrom/algorithms/sort.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/count_unique.h"

#include <sstream>

namespace gremlinxx {

    GroupCountStep::GroupCountStep()
    : TraversalStep(true, MAP, GROUP_COUNT_STEP) {}

    std::string GroupCountStep::getInfo() {
        return std::string("GroupCount{}");
    }

    void GroupCountStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers) {
        if(by_key) {
            std::string key = *(this->by_key);
            traversers.advance([key](auto traverser_data, auto traverser_se, auto traverser_paths){
                if(traverser_se.find(key) == traverser_se.end()) {
                    std::stringstream sx;
                    sx << "Invalid side effect key " << key;
                    throw std::runtime_error(sx.str());
                }
                maelstrom::vector keys = std::move(traverser_se[key]);

                traverser_se.clear();
                traverser_paths.clear();

                maelstrom::sort(keys);

                return maelstrom::count_unique(
                    keys,
                    true
                );  
            });

            traversers.trim_paths(0,0);
        } else {
            traversers.advance([](auto traverser_data, auto traverser_se, auto traverser_paths){
                traverser_se.clear();
                traverser_paths.clear();

                maelstrom::sort(traverser_data);

                return maelstrom::count_unique(
                    traverser_data,
                    true
                );  
            });

            traversers.trim_paths(0,0);
        }
    }

}