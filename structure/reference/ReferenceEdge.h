#ifndef REFERENCE_EDGE_H
#define REFERENCE_EDGE_H

#include "structure/Edge.h"
#include "structure/reference/ReferenceVertex.h"
#include <inttypes.h>
#include <boost/any.hpp>

#define STR_NOT_SUPPORTED "Not supported by ReferenceEdge"

class ReferenceEdge : public Edge {
	private:
		boost::any edge_id;
        std::string edge_label; // not optional

		ReferenceVertex* out_vertex;
		ReferenceVertex* in_vertex;

	public:
        ReferenceEdge(boost::any edge_id, std::string edge_label, ReferenceVertex* out_vertex, ReferenceVertex* in_vertex) {
            this->edge_id = edge_id;
            this->edge_label = edge_label;
            this->out_vertex = out_vertex;
            this->in_vertex = in_vertex;
        }

		virtual boost::any id() { return this->edge_id; }
        virtual std::string label() { return this->edge_label; }

		virtual Graph* getGraph() { throw std::runtime_error(STR_NOT_SUPPORTED); }
		virtual Vertex* outV() { return this->out_vertex; }
		virtual Vertex* inV() { return this->in_vertex; }

		virtual Property* property(std::string key) { throw std::runtime_error(STR_NOT_SUPPORTED); }
		virtual Property* property(std::string key, boost::any& value) { throw std::runtime_error(STR_NOT_SUPPORTED); }
		virtual std::vector<Property*> properties(std::vector<std::string> keys) { throw std::runtime_error(STR_NOT_SUPPORTED); }
};

#undef STR_NOT_SUPPORTED

#endif