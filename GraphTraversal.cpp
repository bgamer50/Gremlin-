#include "GraphTraversalSource.h"
#include "Graph.h"
#include "VertexStep.h"
#include "GraphStep.h"
#include "HasStep.h"
#include "AddVertexStep.h"
#include "AddEdgeStep.h"
#include "AddEdgeStartStep.h"
#include "FromStep.h"
#include "ToStep.h"
#include "NoOpStep.h"
#include "Direction.h"
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>

/*
	JIT compilation is supposed to check to see if these steps are valid;
	this has to be implemented at the actual compilation rather than
	pre-compilation.
*/

/*
	The given traversal source is allowed to be null, in the case of an
	anomymous traversal.
*/
GraphTraversal::GraphTraversal(GraphTraversalSource* src) {
	source = src;
}

GraphTraversal::GraphTraversal(GraphTraversal<U,W>* trv) {
	this->steps = trv.getSteps();
	this->source = trv->getTraversalSource;
}

Graph* GraphTraversal::getGraph() {
	return (*source).getGraph();
}

GraphTraversalSource* GraphTraversal::getTraversalSource() {
	return source;
}

std::vector<TraversalStep*> GraphTraversal::getSteps() {
	return this->steps;
}

std::string GraphTraversal::explain() {
	this->getInitialTraversal();
	std::string explanation = "GraphTraversal {\n";
	for(int k = 0; k < steps.size(); k++) explanation += steps[k]->getInfo() + "\n";

	return explanation + "}";
}

GraphTraversal<U,W>* GraphTraversal::appendStep(TraversalStep* step) {
	steps.push_back(step);
	return this;
}

GraphTraversal<U, Edge>* GraphTraversal::addE(std::string label){ 
	return (GraphTraversal<U, Edge>*)this->appendStep(new AddEdgeStep(label));
}

GraphTraversal<U,Vertex>* GraphTraversal::addV() {
	return this->appendStep(new AddVertexStep());
}

GraphTraversal<U,Vertex>* GraphTraversal::addV(std::string label) {
	return this->appendStep(new AddVertexStep(label));
}

GraphTraversal<U,Vertex>* GraphTraversal::V() {
	return this->appendStep(new GraphStep(VERTEX, {}));
}

GraphTraversal<U,Vertex>* GraphTraversal::V(Vertex* vertex) {
	return this->appendStep(new GraphStep(VERTEX, {(void*)vertex->id()}));
}

GraphTraversal<U,Vertex>* GraphTraversal::V(std::vector<Vertex*> vertices) {
	std::vector<void*> ids;
	for(vector<Vertex*>::iterator v = vertices.begin(); v != vertices.end(); v++) {
		void* id = (void*)((*v)->id());
		ids.push_back(id);
	}
	return this->appendStep(new GraphStep(VERTEX, ids));
}

GraphTraversal<U,W>* GraphTraversal::outE() {
	return this->appendStep(new VertexStep(OUT, {}, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::outE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::inE() {
	return this->appendStep(new VertexStep(IN, {}, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::inE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::bothE() {
	return this->appendStep(new VertexStep(BOTH, {}, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::bothE(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, EDGE));
}

GraphTraversal<U,W>* GraphTraversal::out() {
	return this->appendStep(new VertexStep(OUT, {}, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::out(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(OUT, labels, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::in() {
	return this->appendStep(new VertexStep(IN, {}, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::in(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(IN, labels, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::both() {
	return this->appendStep(new VertexStep(BOTH, {}, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::both(std::vector<std::string> labels) {
	return this->appendStep(new VertexStep(BOTH, labels, VERTEX));
}

GraphTraversal<U,W>* GraphTraversal::has(std::string key, int value) {
	return this->appendStep(new HasStep<int>(key, new P<int>(EQ, value, value)));
}

GraphTraversal<U,W>* GraphTraversal::has(std::string key, std::string value) {
	return this->appendStep(new HasStep<std::string>(key, new P<std::string>(EQ, value, value)));
}

GraphTraversal<U,W>* GraphTraversal::from(std::string sideEffectLabel) {
	// Because from() uses void* (sigh) this awkward memory copy is necessary.
	const char* base_string = sideEffectLabel.c_str();
	size_t size = (1 + strlen(base_string));

	char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
	strncpy(sideEffectLabel_cpy, base_string, size);

	return this->appendStep(new FromStep(sideEffectLabel_cpy));
}

GraphTraversal<U,W>* GraphTraversal::from(Vertex* fromVertex) {
	return this->appendStep(new FromStep(fromVertex));
}

GraphTraversal<U,W>* GraphTraversal::to(std::string sideEffectLabel) {
	// Because to() uses void* (sigh) this awkward memory copy is necessary.
	const char* base_string = sideEffectLabel.c_str();
	size_t size = (1 + strlen(base_string));

	char* sideEffectLabel_cpy = (char*)malloc(sizeof(char) * size);
	strncpy(sideEffectLabel_cpy, base_string, size);

	return this->appendStep(new ToStep(sideEffectLabel_cpy));
}

GraphTraversal<U,W>* GraphTraversal::to(Vertex* toVertex) {
	return this->appendStep(new ToStep(toVertex));
}

template <typename T>
GraphTraversal<U,W>* GraphTraversal::has(std::string key, P<T> pred) {
	return this->appendStep(new HasStep<T>(key, pred));
}

GraphTraversal<U,W>* GraphTraversal::select(std::string sideEffectLabel) {
	//TODO write this
}

/*
	In general this should be called by the finalization steps in
	classes that extend GraphTraversal.
*/
void GraphTraversal::getInitialTraversal() {
	for(int k = 0; k < steps.size(); k++) {
		TraversalStep* currentStep = steps[k];
		switch(currentStep->uid) {
			case ADD_EDGE_STEP: {
				AddEdgeStep* aes = (AddEdgeStep*)currentStep;
				if(k + 1 < steps.size()) {
					if(steps[k + 1]->uid == FROM_STEP) {
						aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
						delete steps[k + 1];
						steps[++k] = new NoOpStep();
					}
					else if(steps[k + 1]->uid == TO_STEP) {
						aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
						delete steps[k + 1];
						steps[++k] = new NoOpStep();
					}
					if(k + 1 < steps.size()) {
						if(steps[k + 1]->uid == FROM_STEP) {
							aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						else if(steps[k + 1]->uid == TO_STEP) {
							aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
					}
				}
				break;
			}
			case ADD_EDGE_START_STEP: {
				AddEdgeStartStep* aes = (AddEdgeStartStep*)currentStep;
				if(k + 1 < steps.size()) {
					if(steps[k + 1]->uid == FROM_STEP) {
						aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
						delete steps[k + 1];
						steps[++k] = new NoOpStep();
					}
					else if(steps[k + 1]->uid == TO_STEP) {
						aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
						delete steps[k + 1];
						steps[++k] = new NoOpStep();
					}
					if(k + 1 < steps.size()) {
						if(steps[k + 1]->uid == FROM_STEP) {
							aes->set_out_traversal(((FromStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
						else if(steps[k + 1]->uid == TO_STEP) {
							aes->set_in_traversal(((ToStep*)steps[k + 1])->getTraversal());
							delete steps[k + 1];
							steps[++k] = new NoOpStep();
						}
					}
				}
				break;
			}
		}	
	}
}
