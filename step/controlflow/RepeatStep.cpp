#include "step/controlflow/RepeatStep.h"
#include "traversal/Traverser.h"

RepeatStep::RepeatStep(GraphTraversal* actionTraversal) 
: TraversalStep(true, MAP, REPEAT_STEP) {
    this->actionTraversal = actionTraversal;
}

std::string RepeatStep::getInfo() { 
    std::string info = "RepeatStep{\n" + this->actionTraversal->explain(1) ;
    //if(this->emitTraversal != nullptr) info += ",\nemit = " + emitTraversal->explain();
    //if(this->untilTraversal != nullptr) info += ",\nuntil = " + untilTraversal->explain();
    info += "\n}";

    return info;
}

// TODO for now "until" is checked only at the end, but per TinkerPop3 standard it can be either pre- or post-loop.
// TODO emit is also pre- or post-loop; right now it is pre-loop.
void RepeatStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet* traversers) {
    gremlinxx::traversal::TraverserSet* emittedTraversers;
    GraphTraversalSource* src = trv->getTraversalSource();
    
    bool cont = true;
    size_t loops = 0;
    do {
        if(this->times && loops >= this->times.value()) break;

        // Build and evaulate the until traversal
        if(this->untilTraversal != nullptr) {
            GraphTraversal currentUntilTraversal(src, untilTraversal);
            currentUntilTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);
            currentUntilTraversal.setInitialTraversers(traversers);
            cont = currentUntilTraversal.hasNext();
        }

        // Build and evalulate the emit traversals
        if(this->emitTraversal != nullptr) {
            for(Traverser& trv : traversers) {
                GraphTraversal currentEmitTraversal(src, emitTraversal);
                currentEmitTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);
                currentEmitTraversal.setInitialTraversers({trv});
                if(currentEmitTraversal.hasNext()) emittedTraversers.push_back(trv);
            }
        }
        
        // Build and evaulate the action traversal
        //std::cout << "action " << actionTraversal->getSteps()[0]->uid << std::endl;
        GraphTraversal currentActionTraversal(src, actionTraversal);
        currentActionTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);
        currentActionTraversal.setInitialTraversers(traversers);

        currentActionTraversal.iterate();
        TraverserSet new_traversers = currentActionTraversal.getTraversers();
        traversers.swap(new_traversers);

        ++loops;
    } while(traversers.size() > 0 && cont);

    traversers.insert(traversers.end(), emittedTraversers.begin(), emittedTraversers.end());
}