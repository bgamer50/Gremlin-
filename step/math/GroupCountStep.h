#ifndef GROUP_COUNT_STEP_H
#define GROUP_COUNT_STEP_H

#define GROUP_COUNT_STEP 0x62

#include "step/TraversalStep.h"
#include <optional>

class GroupCountStep : public TraversalStep {
    private:
        std::optional<std::string> by_key;

        struct gc_global_hash {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p) const {
                return p.first->test_hash(p.second);
            }
        };

        struct gc_global_equals {
            size_t operator() (const std::pair<GraphTraversalSource*, boost::any>& p, const std::pair<GraphTraversalSource*, boost::any>& q) const {
                return p.first->test_equals(p.second, q.second);
            }
        };

    public:
        GroupCountStep()
        : TraversalStep(true, MAP, GROUP_COUNT_STEP) {}

        void set_by_key(std::string by_key) { this->by_key = by_key; }
        
        std::optional<std::string> get_by_key() { return this->by_key; }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            GraphTraversalSource* src = traversal->getTraversalSource();

            if(by_key) {
                throw std::runtime_error("By key is currently unsupported!");
            }

            std::unordered_map<std::pair<GraphTraversalSource*, boost::any>, size_t, gc_global_hash, gc_global_equals> counts;
            for(Traverser& trv : traversers) {
                auto key = std::make_pair(src, trv.get());
                auto f = counts.find(key);
                if(f != counts.end()) f->second += 1;
                else counts[key] = 1;
            }
            traversers.clear();

            std::vector<std::pair<boost::any, size_t>> count_vec;
            count_vec.resize(counts.size());
            size_t k = 0;
            for(auto p : counts) count_vec[k++] = std::make_pair(p.first.second, p.second);

            traversers.push_back(Traverser(count_vec));
        }

};

#endif