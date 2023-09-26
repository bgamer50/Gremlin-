#pragma once

#include <stdlib.h>
#include <string>
#include <utility>

#include "structure/Element.h"
#include "structure/Vertex.h"

namespace gremlinxx {

	struct Edge : public Element {
		public:
			Vertex from;
			Vertex to;
	};

}