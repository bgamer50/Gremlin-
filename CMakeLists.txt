cmake_minimum_required(VERSION 3.10)

project(
    GREMLINXX
    VERSION 0.7
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(POSITION_INDEPENDENT_CODE True)
set(INTERFACE_POSITION_INDEPENDENT_CODE True)

add_library(
    gremlinxx

    structure/Element.cpp
    structure/Edge.cpp

    step/TraversalStep.cpp

    step/controlflow/CoalesceStep.cpp
    step/controlflow/EmitStep.cpp
    step/controlflow/InjectStep.cpp
    step/controlflow/LoopsStep.cpp
    step/controlflow/RepeatStep.cpp
    step/controlflow/TimesStep.cpp
    step/controlflow/UnionStep.cpp
    step/controlflow/UntilStep.cpp

    step/edge/AddEdgeStartStep.cpp
    step/edge/AddEdgeStep.cpp

    step/filter/IsStep.cpp
    step/filter/LimitStep.cpp
    step/filter/WhereStep.cpp

    step/graph/GraphStep.cpp
    step/graph/IdStep.cpp
    step/graph/SubgraphExtractionStep.cpp
    step/graph/SubgraphStep.cpp

    step/logic/DedupStep.cpp
    step/logic/FoldStep.cpp
    step/logic/IdentityStep.cpp
    step/logic/MapStep.cpp
    step/logic/NoOpStep.cpp
    step/logic/OrderStep.cpp
    step/logic/UnfoldStep.cpp

    step/math/CountStep.cpp
    step/math/GroupCountStep.cpp
    step/math/MinStep.cpp

    step/modulate/ByStep.cpp
    step/modulate/FromStep.cpp
    step/modulate/ToStep.cpp

    step/property/AddPropertyStep.cpp
    step/property/HasStep.cpp
    step/property/PropertyStep.cpp
    step/property/ValueMapStep.cpp

    step/sideeffect/AsStep.cpp
    step/sideeffect/SelectStep.cpp

    step/vertex/AddVertexStartStep.cpp
    step/vertex/AddVertexStep.cpp
    step/vertex/VertexStep.cpp

    strategy/ByModulatingStrategy.cpp
    strategy/FromToModulatingStrategy.cpp
    strategy/RepeatStepCompletionStrategy.cpp
    strategy/SubgraphStepCompletionStrategy.cpp
    
    traversal/Comparison.cpp
    traversal/GraphTraversal.cpp
    traversal/GraphTraversalSource.cpp
    traversal/Scope.cpp
    traversal/Traverser.cpp
)

target_compile_options(
    gremlinxx
    PUBLIC
        -O3
        -funsafe-math-optimizations
        -frename-registers
        -funroll-loops
        -fsized-deallocation
)

target_include_directories(
    gremlinxx
    PUBLIC
        "/mnt/gremlin++" # gremlinxx path
        "/mnt/maelstrom" # maelstrom path
)