#ifndef MAP_STEP_H
#define MAP_STEP_H

#define MAP_STEP 0x3c

#include "step/TraversalStep.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Traverser.h"

#include <vector>
#include <string>

class MapStep: public TraversalStep {
    private:
        GraphTraversal* map_traversal;
    
    public:
        MapStep(GraphTraversal* map_traversal) : TraversalStep(MAP, MAP_STEP) {
            this->map_traversal = map_traversal;
        }

        using TraversalStep::getInfo;
        virtual std::string getInfo() {
            return "MapStep{\n" + this->map_traversal->explain() + "\n}";
        }

        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers) {
            TraverserSet new_traversers;

            for(Traverser& trv : traversers) {
                GraphTraversal* trv_traversal = new GraphTraversal(traversal);
                trv_traversal->setInitialTraversers({trv});
                trv_traversal->iterate();
                
                TraverserSet traversers_to_add = trv_traversal->getTraversers();
                std::cout << traversers_to_add.size() << std::endl;
                new_traversers.insert(new_traversers.end(), traversers_to_add.begin(), traversers_to_add.end());
            }

            traversers.swap(new_traversers);
        }
};

#endif