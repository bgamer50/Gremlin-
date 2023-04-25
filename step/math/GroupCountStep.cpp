#include "step/math/GroupCountStep.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"

GroupCountStep::GroupCountStep()
: TraversalStep(true, MAP, GROUP_COUNT_STEP) {}

std::string GroupCountStep::getInfo() {
    return std::string("GroupCount{}");
}

void GroupCountStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
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