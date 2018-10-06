#ifndef FROM_STEP_H
#define FROM_STEP_H

#define FROM_STEP 0x90

class FromStep : public TraversalStep {
	private:
		void* data;
	public:
		FromStep(void* arg)
		: TraversalStep(modulator, FROM_STEP) {
			data = arg;
		}

		void* getData() {
			return data;
		}
};

#endif