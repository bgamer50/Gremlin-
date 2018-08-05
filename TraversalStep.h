#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

enum TraversalStepType {GRAPH_STEP, VERTEX_STEP, DEDUP_STEP};

class TraversalStep {
public:
	TraversalStep(TraversalStepType type, ...);
};

#endif