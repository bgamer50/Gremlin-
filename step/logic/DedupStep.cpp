#include "step/logic/DedupStep.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"

// This is a barrier step
DedupStep::DedupStep()
: TraversalStep(true, FILTER, DEDUP_STEP) {}

void DedupStep::modulate_by(boost::any arg) { 
    this->dedup_by_key = boost::any_cast<std::string>(arg);
}

void DedupStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    GraphTraversalSource* source = traversal->getTraversalSource();

    auto hsh = [source](Traverser& t1){return source->test_hash(t1.get());};
    auto eql = [source](Traverser& t1, Traverser&t2){return source->test_equals(t1.get(), t2.get());};
    
    // We use the tried and true pure bucket hashing method here, as (hopefully) nobody tries to dedup massive sets in a traversal
    // If someone is stupid enough to attempt such a foolish operation, they will get the poor performance they deserve
    // Otherwise this should be very fast
    std::vector<std::vector<Traverser>> new_traversers;
    new_traversers.resize(10 + traversers.size() / 10);

    size_t total_size = 0;
    for(Traverser& trv : traversers) {
        size_t index = hsh(trv) % new_traversers.size();
        bool found = false;
        for(Traverser& trv2 : new_traversers[index]) if(eql(trv,trv2)) {found=true; break;};
        if(!found) {
            new_traversers[index].push_back(trv);
            ++total_size;
        }
    }

    traversers.clear();
    traversers.resize(total_size);
    for(std::vector<Traverser>& vec : new_traversers) 
        for(Traverser& trv : vec)
            traversers[--total_size] = trv;
}

std::string DedupStep::getInfo() {
    return "DedupStep(" + this->dedup_by_key.value_or("") + ")";
}