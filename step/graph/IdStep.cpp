#include "step/graph/IdStep.h"

IdStep::IdStep()
: TraversalStep(MAP, ID_STEP) {}

std::string IdStep::getInfo() {
    return "IdStep()";
}

void IdStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
    std::for_each(traversers.begin(), traversers.end(), [](Traverser& trv) {
        const std::type_info& t = trv.get().type();
        if(t == typeid(Vertex*)) trv.replace_data(boost::any_cast<Vertex*>(trv.get())->id());
        else if(t == typeid(Edge*)) trv.replace_data(boost::any_cast<Edge*>(trv.get())->id());
        else throw std::runtime_error("Error: Traverser does not appear to contain an element.");
    });
}