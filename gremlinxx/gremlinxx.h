#pragma once

#include "structure/Direction.h"
#include "structure/Property.h"
#include "structure/VertexProperty.h"
#include "structure/Element.h"
#include "structure/Vertex.h"
#include "structure/Edge.h"
#include "structure/Graph.h"

#include "traversal/Traverser.h"
#include "traversal/GraphTraversalSource.h"
#include "traversal/GraphTraversal.h"
#include "traversal/Comparison.h"
#include "traversal/P.h"
#include "traversal/Scope.h"
#include "traversal/SyntaxHelper.h"

#include "step/TraversalStep.h"
#include "step/controlflow/CoalesceStep.h"
#include "step/controlflow/EmitStep.h"
#include "step/controlflow/InjectStep.h"
#include "step/controlflow/LoopsStep.h"
#include "step/controlflow/RepeatStep.h"
#include "step/controlflow/TimesStep.h"
#include "step/controlflow/UnionStep.h"
#include "step/controlflow/UntilStep.h"

#include "step/edge/AddEdgeStartStep.h"
#include "step/edge/AddEdgeStep.h"

#include "step/filter/IsStep.h"
#include "step/filter/LimitStep.h"
#include "step/filter/WhereStep.h"

#include "step/graph/VStep.h"
#include "step/graph/IdStep.h"
#include "step/graph/SubgraphExtractionStep.h"
#include "step/graph/SubgraphStep.h"

#include "step/logic/DedupStep.h"
#include "step/logic/IdentityStep.h"
#include "step/logic/NoOpStep.h"
#include "step/logic/OrderStep.h"

#include "step/math/CountStep.h"
#include "step/math/MinStep.h"
#include "step/math/GroupCountStep.h"

#include "step/modulate/ByModulating.h"
#include "step/modulate/ByStep.h"
#include "step/modulate/FromStep.h"
#include "step/modulate/FromToModulating.h"
#include "step/modulate/ToStep.h"

#include "step/property/PropertyStep.h"
#include "step/property/HasStep.h"
#include "step/property/PropertyStep.h"
#include "step/property/ValueStep.h"
#include "step/property/ElementMapStep.h"

#include "step/sideeffect/AsStep.h"
#include "step/sideeffect/SelectStep.h"

#include "step/vertex/AddVertexStartStep.h"
#include "step/vertex/AddVertexStep.h"
#include "step/vertex/VertexStep.h"

#include "strategy/TraversalStrategy.h"
#include "strategy/ByModulatingStrategy.h"
#include "strategy/FromToModulatingStrategy.h"
#include "strategy/RepeatStepCompletionStrategy.h"
#include "strategy/SubgraphStepCompletionStrategy.h"