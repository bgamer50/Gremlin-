#pragma once

#include <vector>
#include <string>

class GraphTraversal;
class Traverser;

enum TraversalStepType {MAP, FILTER, BARRIER, MODULATOR, SIDE_EFFECT};

class TraversalStep {
private:
	TraversalStepType type;

public:
	unsigned int uid;
	bool is_barrier;
	TraversalStep(TraversalStepType tsType, unsigned int id);
	TraversalStep(bool is_barrier, TraversalStepType tsType, unsigned int id);
	virtual std::string getInfo();
	virtual std::string getInfo(size_t indent);
	virtual void apply(GraphTraversal* trv, std::vector<Traverser>& traversers);

};
