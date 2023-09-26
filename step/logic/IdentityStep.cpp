#include "step/logic/IdentityStep.h"
namespace gremlinxx {

    IdentityStep::IdentityStep()
    : TraversalStep(MAP, IDENTITY_STEP) {}

    std::string IdentityStep::getInfo() { return "IdentityStep{}"; }

    void IdentityStep::apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers){
        traversers.advance([](auto& data, auto& se, auto& p){
            return std::make_pair(
                maelstrom::vector(data),
                maelstrom::vector()
            );
        });
    }

}