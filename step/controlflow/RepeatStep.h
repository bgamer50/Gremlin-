#ifndef REPEAT_STEP_H
#define REPEAT_STEP_H
#include "step/TraversalStep.h"

#define REPEAT_STEP 0x42

class RepeatStep: public TraversalStep {
    private:
        // Will emit anything out of the loop that passes through this traversal.
        GraphTraversal* emitTraversal = nullptr;
        
        // Will end the loop when this traversal is completed.
        GraphTraversal* untilTraversal = nullptr;

        // The action to be repeated.
        GraphTraversal* actionTraversal = nullptr;

    public:
        RepeatStep(GraphTraversal* actionTraversal);

        void setEmitTraversal(GraphTraversal* emitTraversal) { this->emitTraversal = emitTraversal; }

        void setUntilTraversal(GraphTraversal* untilTraversal) { this->untilTraversal = untilTraversal; }

        virtual void apply(GraphTraversal* trv, TraverserSet& traversers);
        

};

RepeatStep::RepeatStep(GraphTraversal* actionTraversal) 
: TraversalStep(true, MAP, REPEAT_STEP) {
    this->actionTraversal = actionTraversal;
}

// TODO for now "until" is checked only at the end, but per TinkerPop3 standard it can be either pre- or post-loop.
// TODO emit is also pre- or post-loop; right now it is pre-loop.
void RepeatStep::apply(GraphTraversal* trv, TraverserSet& traversers) {
    TraverserSet emittedTraversers;
    GraphTraversalSource* src = trv->getTraversalSource();
    
    bool cont;
    size_t loops = 0;
    do {
        // Build and evaulate the until traversal
        if(this->untilTraversal != nullptr) {
            GraphTraversal currentUntilTraversal(src, untilTraversal);
            currentUntilTraversal.setInitialTraversers(traversers);
            cont = currentUntilTraversal.hasNext();
        }

        // Build and evalulate the emit traversals
        if(this->emitTraversal != nullptr) {
            for(Traverser& trv : traversers) {
                GraphTraversal currentEmitTraversal(src, emitTraversal);
                currentEmitTraversal.setInitialTraversers({trv});
                if(currentEmitTraversal.hasNext()) emittedTraversers.push_back(trv);
            }
        }
        
        // Build and evaulate the action traversal
        //std::cout << "action " << actionTraversal->getSteps()[0]->uid << std::endl;
        GraphTraversal currentActionTraversal(src, actionTraversal);
        currentActionTraversal.setInitialTraversers(traversers);

        currentActionTraversal.iterate();
        TraverserSet new_traversers = currentActionTraversal.getTraversers();
        traversers.swap(new_traversers);

        ++loops;
    } while(traversers.size() > 0 && cont);

    traversers.insert(traversers.end(), emittedTraversers.begin(), emittedTraversers.end());
    //std::cout << "repeat step done" << std::endl;
}

#endif