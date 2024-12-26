#pragma once

#define DEGREE_STEP 0x7f

#include "step/TraversalStep.h"
#include "structure/Direction.h"

#include <string>
#include <set>

namespace gremlinxx {

    class DegreeStep: public TraversalStep {
        private:
            Direction direction;
            std::set<std::string> edge_labels;

        public:
            DegreeStep(Direction dir, std::set<std::string> edge_labels_arg);

            using TraversalStep::getInfo;
            virtual std::string getInfo();

            virtual void apply(GraphTraversal* traversal, gremlinxx::traversal::TraverserSet& traversers);

            inline virtual Direction get_direction() { return this->direction; }

            inline std::set<std::string> get_edge_labels() { return this->edge_labels; }
    };

}