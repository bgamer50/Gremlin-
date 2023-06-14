#include "step/property/ValueMapStep.h"

#include "traversal/GraphTraversal.h"
#include "step/TraversalStep.h"
#include "structure/Property.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "util/gremlin_utils.h"
#include <boost/format.hpp>

ValueMapStep::ValueMapStep(std::vector<std::string>& keys)
: TraversalStep(MAP, VALUEMAP_STEP) {
    this->keys = std::vector<std::string>(keys.begin(), keys.end());
}

void ValueMapStep::modulate_by(boost::any arg) { 
    this->by_traversal = boost::any_cast<GraphTraversal*>(arg);
}

std::string ValueMapStep::getInfo() {
    std::string s = "ValueMapStep{";
    for(std::string key : this->keys) s += key + ",";
    s += "}";
    return s;
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