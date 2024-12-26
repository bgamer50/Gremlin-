#include "strategy/TraversalStrategy.h"


namespace gremlinxx {
    std::unordered_map<TraversalStrategyType, std::string> strategy_type_names = {
        {DECORATION, "Decoration"},
        {OPTIMIZATION, "Optimization"},
        {PROVIDER, "Provider"},
        {FINALIZATON, "Finalization"},
        {VERIFICATION, "Verification"}
    };
}