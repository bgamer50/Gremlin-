#include "step/vertex/VertexStep.h"

#include "traversal/Traverser.h"
#include "traversal/GraphTraversal.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"

VertexStep::VertexStep(Direction dir, std::vector<std::string> edge_labels_arg, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
    direction = dir;
    std::for_each(edge_labels_arg.begin(), edge_labels_arg.end(), [&](std::string str){ this->edge_labels.insert(str); });
    this->gsType = gsType_arg;
}

VertexStep::VertexStep(Direction dir, GraphStepType gsType_arg)
: TraversalStep(MAP, VERTEX_STEP) {
    direction = dir;
    this->gsType = gsType_arg;
}

std::string VertexStep::getInfo() {
    std::string info = "VertexStep(";
    info += (direction == IN ? "IN" : direction == OUT ? "OUT" : "BOTH");
    info += ", ";
    if(!edge_labels.empty()) {
        info += "{";
        auto p = edge_labels.begin();
        for(int k = 0; k < edge_labels.size() - 1; k++) info = info + *(p++) + ", ";
        info = info + *p + "}";
    }
    else info += "{}";
    info = info + ", " + (gsType == VERTEX ? "VERTEX" : "EDGE");
    return info + ")";
}

void VertexStep::apply(GraphTraversal* traversal, TraverserSet& traversers) {
    bool label_required = !this->edge_labels.empty();

    TraverserSet new_traversers;
    
    std::for_each(traversers.begin(), traversers.end(), [&, this](Traverser& trv) {
        Vertex* v = boost::any_cast<Vertex*>(trv.get());
        std::vector<Edge*> edges = v->edges(direction);
        
        for(size_t k = 0; k < edges.size(); ++k) {
            Edge* e = edges[k];
            if(label_required && this->edge_labels.count(e->label()) == 0) continue;

            if(this->gsType == EDGE) {
                new_traversers.push_back(Traverser(e, trv.get_side_effects()));
            } 
            else {
                switch(direction) {
                    case IN: {
                        Vertex* w = e->outV();
                        new_traversers.push_back(Traverser(w, trv.get_side_effects()));
                        break;
                    }
                    case OUT: {
                        Vertex* w = e->inV();
                        new_traversers.push_back(Traverser(w, trv.get_side_effects()));
                        break;
                    }
                    case BOTH: {
                        Vertex* u = e->outV();
                        Vertex* w = u == v ? e->inV() : u;
                        new_traversers.push_back(Traverser(w, trv.get_side_effects()));
                        break;
                    }
                }
            }

        }
    });


    traversers.swap(new_traversers);
}