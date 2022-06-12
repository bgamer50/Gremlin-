#ifndef SUBGRAPH_STEP_H
#define SUBGRAPH_STEP_H

#define SUBGRAPH_STEP 0x82

#include "step/TraversalStep.h"

#include <unordered_map>
#include <unordered_set>
#include <string>

#define SUBGRAPH_PREFIX std::string("TP_SUBGRAPH_")

class SubgraphStep: public TraversalStep {
    private:
        std::string subgraph_name;

    public:
        SubgraphStep(std::string name) : TraversalStep(SIDE_EFFECT, SUBGRAPH_STEP) {
            this->subgraph_name = name;
        }

        void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            boost::any subgraph_property = traversal->getTraversalProperty(SUBGRAPH_PREFIX + subgraph_name);
            if(subgraph_property.empty()) subgraph_property = std::unordered_set<Edge*>();
            
            std::unordered_set<Edge*> subgraph_edges = boost::any_cast<std::unordered_set<Edge*>>(subgraph_property);
            for(Traverser& trv : traversers) {
                subgraph_edges.insert(boost::any_cast<Edge*>(trv.get()));
            }

            traversal->setTraversalProperty(SUBGRAPH_PREFIX + subgraph_name, subgraph_edges);
        }

        inline std::string get_subgraph_name() { return this->subgraph_name; }
};

#endif