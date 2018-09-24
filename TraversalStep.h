#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

#include <vector>
#include <string>

enum TraversalStepType {map, filter, barrier};

class TraversalStep {
private:
	TraversalStepType type;
public:
	unsigned int uid;
	TraversalStep(TraversalStepType tsType, unsigned int uid);
	virtual std::string getInfo();
};

#endif