#ifndef ADD_EDGE_STEP_COMPLETION_STRATEGY
#define ADD_EDGE_STEP_COMPLETION_STRATEGY

#include <vector>

class FromStep;
class ToStep;
class AddEdgeStep;
class AddEdgeStartStep;
class TraversalStep;

inline bool add_edge_gather(AddEdgeStep* aes, TraversalStep* next_step);
bool add_edge_start_gather(AddEdgeStartStep* aes, TraversalStep* next_step);
void add_edge_step_completion_strategy(std::vector<TraversalStep*>& steps);

#include "traversal/GraphTraversal.h"
#include "step/modulate/FromStep.h"
#include "step/modulate/ToStep.h"
#include "step/edge/AddEdgeStep.h"
#include "step/edge/AddEdgeStartStep.h"
#include "step/logic/NoOpStep.h"

/*
    Grabs the from or to step immediately following the AddEdgeStep.
    Returns true if the grab was successful; this indicates that
    the next_step should be replaced by a NoOp.
*/
inline bool add_edge_gather(AddEdgeStep* aes, TraversalStep* next_step) {
    if(next_step->uid == FROM_STEP) {
        FromStep* fs = reinterpret_cast<FromStep*>(next_step);
        aes->set_out_traversal(fs->getTraversal());
        delete next_step;
        return true;
    }
    else if(next_step->uid == TO_STEP) {
        ToStep* ts = reinterpret_cast<ToStep*>(next_step);
        aes->set_in_traversal(ts->getTraversal());
        delete next_step;
        return true;
    }

    return false;
}

/*
    Grabs the from or to step immediately following the AddEdgeStartStep.
    Returns true if the grab was successful; this indicates that
    the next_step should be replaced by a NoOp.
    
    Essentially equivalent to the similarly-named method for the AddEdgeStep
    but has to exist given current API limitations.
*/
inline bool add_edge_start_gather(AddEdgeStartStep* aes, TraversalStep* next_step) {
    if(next_step->uid == FROM_STEP) {
        FromStep* fs = static_cast<FromStep*>(next_step);
        aes->set_out_traversal(fs->getTraversal());
        delete next_step;
        return true;
    }
    else if(next_step->uid == TO_STEP) {
        ToStep* ts = static_cast<ToStep*>(next_step);
        aes->set_in_traversal(ts->getTraversal());
        delete next_step;
        return true;
    }

    return false;
}

/*
    Core strategy method; combines the two types of AddEdge steps with their
    from and to steps.
*/
void add_edge_step_completion_strategy(std::vector<TraversalStep*>& steps) {
    for(int k = 0; k < steps.size(); k++) {
		TraversalStep* currentStep = steps[k];
		switch(currentStep->uid) {
			case ADD_EDGE_STEP: {
				AddEdgeStep* aes = static_cast<AddEdgeStep*>(currentStep);
                if(k + 1 < steps.size() && add_edge_gather(aes, steps[k + 1])) { 
                    steps[++k] = new NoOpStep();
                    if(k + 1 < steps.size() && add_edge_gather(aes, steps[k + 1])) {
                        steps[++k] = new NoOpStep();
                    }
                }
				
                break;
			}
			case ADD_EDGE_START_STEP: {
				AddEdgeStartStep* aes = static_cast<AddEdgeStartStep*>(currentStep);
                if(k + 1 < steps.size() && add_edge_start_gather(aes, steps[k + 1])) { 
                    steps[++k] = new NoOpStep();
                    if(k + 1 < steps.size() && add_edge_start_gather(aes, steps[k + 1])) {
                        steps[++k] = new NoOpStep();
                    }
                }
				
                break;
			}
            default: {
                // do nothing (nop)
                break;
            }
		}
	}
}

#endif