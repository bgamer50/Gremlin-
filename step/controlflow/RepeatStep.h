#ifndef REPEAT_STEP_H
#define REPEAT_STEP_H

#include "step/TraversalStep.h"

#include <optional>

#define REPEAT_STEP 0x42
#define LOOPS_TRAVERSAL_PROPERTY std::string("TRV_LOOPS")

class RepeatStep: public TraversalStep {
    private:
        // Will emit anything out of the loop that passes through this traversal.
        GraphTraversal* emitTraversal = nullptr;
        
        // Will end the loop when this traversal is completed.
        GraphTraversal* untilTraversal = nullptr;

        // The action to be repeated.
        GraphTraversal* actionTraversal = nullptr;

        // The # of times to run the loop
        std::optional<size_t> times;

    public:
        RepeatStep(GraphTraversal* actionTraversal);

        GraphTraversal* getActionTraversal() { return this->actionTraversal; }

        void setEmitTraversal(GraphTraversal* emitTraversal) { this->emitTraversal = emitTraversal; }
        GraphTraversal* getEmitTraversal() { return this->emitTraversal; }

        void setUntilTraversal(GraphTraversal* untilTraversal) { this->untilTraversal = untilTraversal; }
        GraphTraversal* getUntilTraversal() { return this->untilTraversal; }

        void setTimes(size_t times) {
            this->times = times;
        }

        virtual void apply(GraphTraversal* trv, TraverserSet& traversers);

        using TraversalStep::getInfo;
        virtual std::string getInfo() { 
            std::string info = "RepeatStep{\n" + actionTraversal->explain(1) ;
            //if(this->emitTraversal != nullptr) info += ",\nemit = " + emitTraversal->explain();
            //if(this->untilTraversal != nullptr) info += ",\nuntil = " + untilTraversal->explain();
            info += "\n}";

            return info;
        }
        

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

#endif