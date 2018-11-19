#ifndef TRAVERSAL_STEP_H
#define TRAVERSAL_STEP_H

#include <vector>
#include <string>

enum TraversalStepType {MAP, FILTER, BARRIER, MODULATOR};

class TraversalStep {
private:
	TraversalStepType type;
public:
	unsigned int uid;
	TraversalStep(TraversalStepType tsType, unsigned int uid);
	virtual std::string getInfo();
};

#endif