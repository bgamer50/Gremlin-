#include "step/controlflow/RepeatStep.h"
#include "traversal/Traverser.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"

namespace gremlinxx {

    RepeatStep::RepeatStep(GraphTraversal* actionTraversal) 
    : TraversalStep(true, MAP, REPEAT_STEP) {
        this->actionTraversal = actionTraversal;
    }

    std::string RepeatStep::getInfo() { 
        std::string info = "RepeatStep{\n" + this->actionTraversal->explain(1) ;
        //if(this->emitTraversal != nullptr) info += ",\nemit = " + emitTraversal->explain();
        //if(this->untilTraversal != nullptr) info += ",\nuntil = " + untilTraversal->explain();
        info += "\n}";

        return info;
    }

    // TODO for now "until" is checked only at the end, but per TinkerPop3 standard it can be either pre- or post-loop.
    // TODO emit is also pre- or post-loop; right now it is pre-loop.
    void RepeatStep::apply(GraphTraversal* trv, gremlinxx::traversal::TraverserSet& traversers) {
        GraphTraversalSource* src = trv->getTraversalSource();
        GraphTraversal emissionTraversal(src);
        
        bool cont = true;
        size_t loops = 0;
        do {
            if(this->times && loops >= this->times.value()) break;

            // Build and evaulate the until traversal
            if(this->untilTraversal != nullptr) {
                GraphTraversal currentUntilTraversal(src, untilTraversal);
                currentUntilTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);
                currentUntilTraversal.setInitialTraversers(traversers);
                cont = currentUntilTraversal.hasNext();
            }

            // Build and evalulate the emit traversals
            if(this->emitTraversal != nullptr) {
                // TODO allow using streams to do this (somehow)
                gremlinxx::traversal::TraverserSet& emitted_traversers = emissionTraversal.getTraverserSet();

                std::vector<std::tuple<maelstrom::vector, std::unordered_map<std::string, maelstrom::vector>, gremlinxx::traversal::PathInfo>> unpacked_traversers = traversers.unpack();
                for(size_t i = 0; i < unpacked_traversers.size(); ++i) {
                    auto& t = unpacked_traversers[i];
                    GraphTraversal currentEmitTraversal(src, emitTraversal);
                    currentEmitTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);

                    // Should copy the data in t, not move it
                    currentEmitTraversal.getTraverserSet().reinitialize(
                        std::get<0>(t),
                        std::get<1>(t),
                        std::get<2>(t)
                    );

                    if(currentEmitTraversal.hasNext()) {
                        GraphTraversal bogusEmissionTraversal(src);
                        // Should move the data in t, not copy it
                        bogusEmissionTraversal.getTraverserSet().reinitialize(
                            std::move(std::get<0>(t)),
                            std::move(std::get<1>(t)),
                            std::move(std::get<2>(t))
                        );

                        emitted_traversers.addTraversers(bogusEmissionTraversal.getTraverserSet());
                    }
                }

            }
            
            // Build and evaulate the action traversal
            GraphTraversal currentActionTraversal(src, actionTraversal);
            currentActionTraversal.setTraversalProperty(LOOPS_TRAVERSAL_PROPERTY, loops);
            currentActionTraversal.setInitialTraversers(traversers);
            traversers.clear();

            currentActionTraversal.iterate();
            traversers.addTraversers(
                currentActionTraversal.getTraverserSet()
            );

            ++loops;
        } while(traversers.size() > 0 && cont);

        traversers.addTraversers(emissionTraversal.getTraverserSet());
        emissionTraversal.getTraverserSet().clear(); // not necessary but better to be explicit sometimes
    }

}