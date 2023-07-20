#pragma once
#include <any>
#include <vector>

namespace gremlinxx {

	/*
		The Element Structure
		All Elements in gremlin++ are Reference Elements
		All Elements must have a uint64_t id, including edges
	*/
	struct Element {
		public:
			std::string label = "";
			size_t id = 0;
	};

}