#ifndef REPEAT_STEP_H
#define REPEAT_STEP_H
#include "step/TraversalStep.h"

#define REPEAT_STEP 0x42

class RepeatStep: public TraversalStep {
    private:
        // Will emit anything out of the loop that passes through this traversal.
        GraphTraversal* emitTraversal;
        
        // Will end the loop when this traversal is completed.
        GraphTraversal* untilTraversal;

        // The action to be repeated.
        GraphTraversal* actionTraversal;

    public:
        RepeatStep(GraphTraversal* actionTraversal);

        void setEmitTraversal(GraphTraversal* emitTraversal) { this->emitTraversal = emitTraversal; }

        void setUntilTraversal(GraphTraversal* untilTraversal) { this->untilTraversal = untilTraversal; }

        virtual void apply(GraphTraversal* trv, TraverserSet& traversers);
        

};

RepeatStep::RepeatStep(GraphTraversal* actionTraversal) 
: TraversalStep(MAP, REPEAT_STEP) {
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
        // Gather current objects
        std::vector<boost::any> injects(traversers.size());
        for(size_t k = 0; k < traversers.size(); ++k) {
            injects[k] = traversers[k].get();
        }
        InjectStep injectStep(injects);

        // Build and evaulate the until traversal
        if(this->untilTraversal != nullptr) {
            GraphTraversal currentUntilTraversal(src, untilTraversal);
            currentUntilTraversal.insertStep(0, &injectStep);
            cont = currentUntilTraversal.hasNext();
        }

        // Build and evalulate the emit traversals
        if(this->emitTraversal != nullptr) {
            std::for_each(injects.begin(), injects.end(), [&,this](boost::any& b) {
                GraphTraversal currentEmitTraversal(src, emitTraversal);
                InjectStep step(b);
                currentEmitTraversal.insertStep(0, &step);
                if(currentEmitTraversal.hasNext()) emittedTraversers.push_back(Traverser(b));
            });
        }
        
        // Build and evaulate the action traversal
        std::cout << "action " << actionTraversal->getSteps()[0]->uid << std::endl;
        GraphTraversal currentActionTraversal(src, actionTraversal);
        currentActionTraversal.insertStep(0, &injectStep);
        std::vector<boost::any> new_objects = currentActionTraversal.toVector();
        std::cout << "got " << new_objects.size() << " objects\n";

        traversers.resize(new_objects.size());
        for(size_t k = 0; k < new_objects.size(); ++k) traversers[k] = Traverser(new_objects[k]);

        loops++;
    } while(traversers.size() > 0 && cont);

    traversers.insert(traversers.end(), emittedTraversers.begin(), emittedTraversers.end());
    std::cout << "repeat step done" << std::endl;
}

#endif