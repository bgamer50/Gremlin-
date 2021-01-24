#ifndef VALUE_MAP_STEP_H
#define VALUE_MAP_STEP_H

#define VALUEMAP_STEP 0x68

#include <boost/any.hpp>
#include <vector>
#include <unordered_map>

#include "step/modulate/ByModulating.h"

class GraphTraversal;
class TraversalStep;

class ValueMapStep: public TraversalStep, virtual public ByModulating {
    private:
        std::vector<std::string> keys;
        GraphTraversal* by_traversal = nullptr;

    public:
        ValueMapStep(std::vector<std::string>& keys);
        virtual void apply(GraphTraversal* traversal, TraverserSet& traversers);
        
        void modulate_by(boost::any arg) { this->by_traversal = boost::any_cast<GraphTraversal*>(arg); }
};

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "structure/Property.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "util/gremlin_utils.hpp"
#include <boost/format.hpp>

ValueMapStep::ValueMapStep(std::vector<std::string>& keys)
: TraversalStep(MAP, VALUEMAP_STEP) {
    this->keys = std::vector<std::string>(keys.begin(), keys.end());
}

void ValueMapStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    for(Traverser& trv : traversers) {
        boost::any data = trv.get();
        if(data.type() == typeid(Edge*)) {
            throw std::runtime_error("ValueMap currently does not support edge properties!");
        }

        std::unordered_map<std::string, boost::any> vmap;
        Vertex* v = boost::any_cast<Vertex*>(data);
        for(std::string key : this->keys) {
            std::vector<boost::any> vec;

            auto* prop = v->property(key);
            if(prop == nullptr) throw std::runtime_error(str(boost::format("Property %1% does not exist on vertex.") % key));
            vec.push_back(prop->value());
            
            if(this->by_traversal == nullptr) {
                vmap[key] = vec;
            }
            else {
                GraphTraversal new_trv(traversal->getTraversalSource(), by_traversal);
                new_trv.setInitialTraversers({Traverser(vec)});
                vmap[key] = new_trv.next();
            }
        }

        trv.replace_data(vmap);
    }
}

#endif