#include "step/controlflow/InjectStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "traversal/GraphTraversalSource.h"

#include <any>

namespace gremlinxx {
        
    InjectStep::InjectStep(std::vector<std::any>& injects) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
        std::copy(injects.begin(), injects.end(), std::back_inserter(objects));
    }

    InjectStep::InjectStep(std::any& b) : TraversalStep(SIDE_EFFECT, INJECT_STEP) {
        objects.push_back(b);
    }

    void InjectStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        if(this->objects.empty()) return;

        maelstrom::dtype_t dtype = trv->getTraversalSource()->get_dtype(this->objects.front());
        maelstrom::vector obj_vector = maelstrom::make_vector_from_anys(
            maelstrom::HOST,
            dtype,
            this->objects
        );

        GraphTraversal empty_trv(trv->getTraversalSource());
        empty_trv.getTraverserSet().advance([&obj_vector](maelstrom::vector& data, std::unordered_map<std::string, maelstrom::vector>& side_effects, gremlinxx::traversal::PathInfo& path_info){
            return std::make_pair(
                obj_vector,
                maelstrom::vector()
            );
        });

        // TODO might want to make sure memory type is what the backend expects
        traversers.addTraversers(empty_trv.getTraverserSet());
    }

}