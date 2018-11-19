#ifndef APPLICABLE_STEP_H
#define APPLICABLE_STEP_H

class Vertex;

/*
	Interface for steps that do things that
	the interpreter may be unable to inspect
	at runtime.
*/
class ApplicableStep {
	public:
		virtual void apply(Vertex* v) = 0;
};

#endif