#include "step/property/PropertyStep.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/VertexProperty.h"

PropertyStep::PropertyStep(PropertyStepType type, std::vector<std::string> property_keys)
: TraversalStep(MAP, PROPERTY_STEP) {
    this->keys = property_keys;
    this->ps_type = type;
}

std::string PropertyStep::getInfo() {
    std::string s = "PropertyStep{";
    s += (this->ps_type == VALUE ? "Value" : "Property");
    s += "}";
    return s;
}

void PropertyStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    TraverserSet new_traversers;
    bool get_value = this->ps_type == VALUE;

    for(Traverser& trv : traversers) {
        for(std::string key : keys) {
            boost::any x = trv.get();
            if(x.type() == typeid(Vertex*)) {
                Vertex* v = boost::any_cast<Vertex*>(x);
                VertexProperty* p = static_cast<VertexProperty*>(v->property(key)); //TODO multiproperties?
                if(p != nullptr) {
                    if(get_value) new_traversers.push_back(Traverser(p->value(), trv.get_side_effects()));
                    else new_traversers.push_back(Traverser(boost::any(p), trv.get_side_effects()));
                }
            }
            else if(x.type() == typeid(Edge*)) {
                Edge* e = boost::any_cast<Edge*>(x);
                Property* p = e->property(key);
            } else {
                throw std::runtime_error("Can only access properties on Vertices or Edges.");
            }
        }
    }

    traversers.swap(new_traversers);
}