#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

enum TraversalStepType {map, filter, barrier};

class TraversalStep {
private:
	TraversalStepType type;
public:
	TraversalStep(TraversalStepType tsType, ...);
};

#endif