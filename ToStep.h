#ifndef TO_STEP_H
#define TO_STEP_H

#define TO_STEP 0x91

class ToStep : public TraversalStep {
	private:
		void* data;
	public:
		ToStep(void* arg)
		: TraversalStep(modulator, FROM_STEP) {
			data = arg;
		}

		void* getData() {
			return data;
		}
};

#endif