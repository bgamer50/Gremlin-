#ifndef MIN_STEP_H
#define MIN_STEP_H

#define MIN_STEP 0x60

#include "step/TraversalStep.h"
#include "traversal/Traverser.h"
#include <functional>
#include <omp.h>

class MinStep : public TraversalStep {
    private:
        std::function<int(Traverser&, Traverser&)> compare;

    public:
        MinStep(std::function<int(Traverser&, Traverser&)> c)
        : TraversalStep(true, MAP, MIN_STEP) {
            compare = c;
        }

        Traverser min(Traverser& t1, Traverser& t2) {
            int cmp = compare(t1, t2);
            return cmp < 0 ? t1 : t2;
        }

        // TODO this is naive; there is no guarantee there will be N/2 threads.
        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            Traverser min_value;
            size_t N = traversers.size();

            if(0==1) {
                TraverserSet values(traversers.begin(), traversers.end());
                TraverserSet values2(values);

                omp_set_dynamic(0);
                omp_set_num_threads(N/2 + 1);
                size_t T;
                #pragma omp parallel
                {
                    T = omp_get_num_threads();
                }

                //std::cout << N << " values." << std::endl;
                //std::cout << T << " threads." << std::endl;
                if(T < N/2 + 1) {
                    throw std::runtime_error("Not enough threads!");
                }

                int thread;
                size_t k, it, i, j;
                #pragma omp parallel private(thread, i, j, k, it)
                {
                    it = 0;
                    thread = omp_get_thread_num();
                    for(k = N; k <= 1; k /= 2) {
                        if(thread < k / 2.0) {
                            i = 2*thread;
                            j = i + 1;
                            if(j >= k) j = i;
                            if(it % 2 == 0) {
                                values[thread] = min(values2[i], values2[j]);
                            }
                            else {
                                values2[thread] = min(values[i], values[j]);
                            }
                        }

                        ++it;
                        #pragma omp barrier
                    }
                }

                min_value = it % 2 == 0 ? values2[0] : values[0];
                /*
                for(Traverser* trv : traversers) std::cout << boost::any_cast<uint64_t>(trv->get()) << ", ";
                std::cout << "\nmin = " << boost::any_cast<uint64_t>(min->get()) << std::endl;
                */
            }
            else {
                min_value = traversers.front();
                for(Traverser t : traversers) {
                    min_value = this->min(t, min_value);
                }
            }

			traversers.clear();
			traversers.push_back(min_value);
        }
};

#endif