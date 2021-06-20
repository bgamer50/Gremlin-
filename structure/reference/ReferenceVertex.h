#ifndef REFERENCE_VERTEX_H
#define REFERENCE_VERTEX_H

#include "structure/Vertex.h"
#include <optional>
#include <string>
#include <boost/any.hpp>

#define STR_NOT_SUPPORTED "not supported by ReferenceVertex"

class ReferenceVertex: public Vertex {
    private:
        boost::any vertex_id;
        std::optional<std::string> vertex_label;

    public:
        ReferenceVertex(boost::any vertex_id, std::string label) {
            this->vertex_id = vertex_id;
            this->vertex_label = label;
        }

        ReferenceVertex(boost::any vertex_id) {
            this->vertex_id = vertex_id;
        }


    	virtual Graph* getGraph() { throw std::runtime_error(std::string(__func__) + " " + STR_NOT_SUPPORTED);}

    	virtual boost::any id() { return this->vertex_id; }

    	virtual std::string label() { return this->vertex_label.value_or(nullptr); }

    	virtual std::vector<Edge*> edges(Direction dir) { throw std::runtime_error(std::string(__func__) + " "  + STR_NOT_SUPPORTED); }

    	virtual Property* property(std::string key) { throw std::runtime_error(std::string(__func__) + " "  + STR_NOT_SUPPORTED); }

    	virtual Property* property(Cardinality cardinality, std::string key, boost::any& value) { throw std::runtime_error(std::string(__func__) + " "  + STR_NOT_SUPPORTED); }

        virtual std::vector<Property*> properties(std::vector<std::string> keys) { throw std::runtime_error(std::string(__func__) + " "  + STR_NOT_SUPPORTED); } 
};

#undef STR_NOT_SUPPORTED

#endif