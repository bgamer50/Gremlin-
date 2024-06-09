#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>

#include "gremlinxx/gremlinxx.h"
#include "maelstrom/storage/datatype.h"

namespace nb = nanobind;
using namespace nb::literals;

template <typename T>
std::any num_to_type(T val, std::string& type_name) {
    if("uint64" == type_name) return static_cast<uint64_t>(val);
    if("uint32" == type_name) return static_cast<uint32_t>(val);
    if("uint8" == type_name) return static_cast<uint8_t>(val);
    if("int64" == type_name)return static_cast<int64_t>(val);
    if("int32" == type_name)return static_cast<int32_t>(val);
    if("int8" == type_name) return static_cast<int8_t>(val);
    if("float64" == type_name) return static_cast<double>(val);
    if("float32" == type_name) return static_cast<float>(val);

    throw std::runtime_error("Invalid type name");
}

nb::object cast_type(std::any& a) {
    if(a.type() == typeid(gremlinxx::Vertex)) {
        throw std::runtime_error("Vertex return type currently unsupported");
    }

    maelstrom::primitive_t prim_type;
    try {
        prim_type = maelstrom::prim_type_of(a);
    } catch(std::runtime_error& ex) {
        throw std::runtime_error("Can't convert to Python type: " + std::string(ex.what()));
    }
    switch(prim_type) {
        case maelstrom::UINT64:
            return nb::cast(std::any_cast<uint64_t>(a));
        case maelstrom::UINT32:
            return nb::cast(std::any_cast<uint32_t>(a));
        case maelstrom::UINT8:
            return nb::cast(std::any_cast<uint8_t>(a));
        case maelstrom::INT64:
            return nb::cast(std::any_cast<int64_t>(a));
        case maelstrom::INT32:
            return nb::cast(std::any_cast<int32_t>(a));
        case maelstrom::INT8:  
            return nb::cast(std::any_cast<int8_t>(a));
        case maelstrom::FLOAT64:
            return nb::cast(std::any_cast<double>(a));
        case maelstrom::FLOAT32:
            return nb::cast(std::any_cast<float>(a));
    }
    throw std::runtime_error("invalid type");
}

template<typename T>
nb::object t_maelstrom_to_numpy(maelstrom::vector& vec) {
    T* data = static_cast<T*>(vec.data());
    vec.disown();
    nb::capsule owner(data, [](void* ptr) noexcept {
        maelstrom::vector tmp(maelstrom::HOST, maelstrom::uint64, ptr, 1, true);
        tmp.own(); // will free memory once tmp goes out of scope
    });

    nb::ndarray<nb::numpy, T> arr(
        data,
        {vec.size()},
        owner
    );

    return nb::cast(arr);
}

nb::object maelstrom_to_numpy(maelstrom::vector& vec) {
    switch(vec.get_dtype().prim_type) {
        case maelstrom::UINT64:
            return t_maelstrom_to_numpy<uint64_t>(vec);
        case maelstrom::UINT32:
            return t_maelstrom_to_numpy<uint32_t>(vec);
        case maelstrom::UINT8:
            return t_maelstrom_to_numpy<uint8_t>(vec);
        case maelstrom::INT64:
            return t_maelstrom_to_numpy<int64_t>(vec);
        case maelstrom::INT32:
            return t_maelstrom_to_numpy<int32_t>(vec);
        case maelstrom::INT8:
            return t_maelstrom_to_numpy<int8_t>(vec);
        case maelstrom::FLOAT64:
            return t_maelstrom_to_numpy<double>(vec);
        case maelstrom::FLOAT32:
            return t_maelstrom_to_numpy<float>(vec);
    }

    throw std::runtime_error("invalid primitive type");
}

NB_MODULE(pygremlinxx, m) {
    nb::class_<gremlinxx::Graph>(m, "Graph")
        .def("traversal", &gremlinxx::Graph::traversal)
        .def("num_vertices", &gremlinxx::Graph::num_vertices)
        .def("num_edges", &gremlinxx::Graph::num_edges)
        .def("get_vertex_property_names", &gremlinxx::Graph::get_vertex_property_names)
        .def("get_edge_property_names", &gremlinxx::Graph::get_edge_property_names);

    nb::class_<gremlinxx::TraversalStrategy>(m, "TraversalStrategy")
        .def(nb::new_([](std::string name){
            if(name == "RepeatStepCompletionStrategy") {
                return gremlinxx::RepeatStepCompletionStrategy;
            } else if(name == "ByModulatingStrategy") {
                return gremlinxx::ByModulatingStrategy;
            } else if(name == "FromToModulatingStrategy") {
                return gremlinxx::FromToModulatingStrategy;
            } else if(name == "LimitSupportingStrategy") {
                return gremlinxx::LimitSupportingStrategy;
            } else if(name == "RepeatStepCompletionStrategy") {
                return gremlinxx::RepeatStepCompletionStrategy;
            }

            throw std::runtime_error(
                "Unknown strategy type - backend strategies can't be created in Python."
            );
        }));

    nb::class_<gremlinxx::GraphTraversalSource>(m, "GraphTraversalSource")
        .def("withoutStrategies", &gremlinxx::GraphTraversalSource::withoutStrategies)
        .def("V", [](gremlinxx::GraphTraversalSource& g){
            return g.V();
        })
        .def("E", [](gremlinxx::GraphTraversalSource& g){
            return g.E();
        })
        .def("addV", [](gremlinxx::GraphTraversalSource& g){
            return g.addV();
        })
        .def("addV", [](gremlinxx::GraphTraversalSource& g, std::string label){
            return g.addV(label);
        })
        .def("addE", &gremlinxx::GraphTraversalSource::addE);

    nb::class_<gremlinxx::GraphTraversal>(m, "GraphTraversal")
        .def("__init__",
            [](gremlinxx::GraphTraversal* traversal) {
                new (traversal) gremlinxx::GraphTraversal();
            }
        )
        .def("V", [](gremlinxx::GraphTraversal& trv){
            return trv.V();
        })
        .def("addV", [](gremlinxx::GraphTraversal& trv, std::string label){
            return trv.addV(label);
        })
        .def("addV", [](gremlinxx::GraphTraversal& trv) {
            return trv.addV();
        })
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, std::string value){
            return trv.property(property_key, value);
        })
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, int64_t value){
            return trv.property(property_key, value);
        })
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, double value){
            return trv.property(property_key, value);
        })
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, int64_t value, std::string type_name){
            return trv.property(property_key, num_to_type(value, type_name));
        })
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, double value, std::string type_name){
            return trv.property(property_key, num_to_type(value, type_name));
        })
        .def("sideEffect", [](gremlinxx::GraphTraversal& trv, std::string side_effect_key, std::string value){
            return trv.sideEffect(side_effect_key, value);
        })
        .def("sideEffect", [](gremlinxx::GraphTraversal& trv, std::string side_effect_key, int64_t value){
            return trv.sideEffect(side_effect_key, value);
        })
        .def("sideEffect", [](gremlinxx::GraphTraversal& trv, std::string side_effect_key, double value){
            return trv.sideEffect(side_effect_key, value);
        })
        .def("sideEffect", [](gremlinxx::GraphTraversal& trv, std::string side_effect_key, int64_t value, std::string type_name){
            return trv.sideEffect(side_effect_key, num_to_type(value, type_name));
        })
        .def("sideEffect", [](gremlinxx::GraphTraversal& trv, std::string side_effect_key, double value, std::string type_name){
            return trv.sideEffect(side_effect_key, num_to_type(value, type_name));
        })
        .def("as", &gremlinxx::GraphTraversal::as)
        .def("by", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal mod){
            return trv.by(mod);
        })
        .def("by", [](gremlinxx::GraphTraversal& trv, std::string mod){
            return trv.by(mod);
        })
        .def("cap", &gremlinxx::GraphTraversal::cap)
        .def("count", &gremlinxx::GraphTraversal::count)
        .def("dedup", &gremlinxx::GraphTraversal::dedup)
        .def("emit", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal emit_traversal){
            return trv.emit(emit_traversal);
        })
        .def("emit", [](gremlinxx::GraphTraversal& trv){
            return trv.emit();
        })
        .def("from", [](gremlinxx::GraphTraversal& trv, std::string side_effect_label){
            return trv.from(side_effect_label);
        })
        .def("groupCount", &gremlinxx::GraphTraversal::groupCount)
        .def("has", [](gremlinxx::GraphTraversal& trv, std::string key, int64_t value){
            return trv.has(key, value);
        })
        .def("has", [](gremlinxx::GraphTraversal& trv, std::string key, double value){
            return trv.has(key, value);
        })
        .def("has", [](gremlinxx::GraphTraversal& trv, std::string key, std::string value){
            return trv.has(key, value);
        })
        .def("has", [](gremlinxx::GraphTraversal& trv, std::string key){
            return trv.has(key);
        })
        .def("hasNot", &gremlinxx::GraphTraversal::hasNot)
        .def("id", &gremlinxx::GraphTraversal::id)
        .def("identity", &gremlinxx::GraphTraversal::identity)
        .def("is", [](gremlinxx::GraphTraversal& trv, int64_t value){
            return trv.is(value);
        })
        .def("is", [](gremlinxx::GraphTraversal& trv, double value){
            return trv.is(value);
        })
        .def("is", [](gremlinxx::GraphTraversal& trv, std::string value){
            return trv.is(value);
        })
        .def("limit", &gremlinxx::GraphTraversal::limit)
        .def("loops", &gremlinxx::GraphTraversal::loops)
        .def("min", [](gremlinxx::GraphTraversal& trv){
            return trv.min();
        })
        .def("order", &gremlinxx::GraphTraversal::order)
        .def("repeat", &gremlinxx::GraphTraversal::repeat)
        .def("sample", &gremlinxx::GraphTraversal::sample)
        .def("select", &gremlinxx::GraphTraversal::select)
        .def("subgraph", &gremlinxx::GraphTraversal::subgraph)
        .def("to", [](gremlinxx::GraphTraversal& trv, std::string side_effect_label){
            return trv.to(side_effect_label);
        })
        .def("_union", &gremlinxx::GraphTraversal::_union)
        .def("until", &gremlinxx::GraphTraversal::until)
        .def("values", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels){
            return trv.values(labels);
        })
        .def("values", [](gremlinxx::GraphTraversal& trv, std::string label){
            return trv.values(label);
        })
        .def("out", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels) {
            return trv.out(labels);
        })
        .def("out", [](gremlinxx::GraphTraversal& trv) {
            return trv.out();
        })
        .def("in", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels) {
            return trv.in(labels);
        })
        .def("in", [](gremlinxx::GraphTraversal& trv) {
            return trv.in();
        })
        .def("both", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels){
            return trv.both(labels);
        })
        .def("both", [](gremlinxx::GraphTraversal& trv){
            return trv.both();
        })
        .def("bothE", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels){
            return trv.bothE(labels);
        })
        .def("bothE", [](gremlinxx::GraphTraversal& trv){
            return trv.bothE();
        })
        .def("outE", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels){
            return trv.outE(labels);
        })
        .def("outE", [](gremlinxx::GraphTraversal& trv){
            return trv.outE();
        })
        .def("inE", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels){
            return trv.inE(labels);
        })
        .def("inE", [](gremlinxx::GraphTraversal& trv){
            return trv.inE();
        })
        .def("outV", &gremlinxx::GraphTraversal::outV)
        .def("inV", &gremlinxx::GraphTraversal::inV)
        .def("times", &gremlinxx::GraphTraversal::times)
        .def("elementMap", &gremlinxx::GraphTraversal::elementMap)
        .def("coalesce", &gremlinxx::GraphTraversal::coalesce)
        .def("hasNext", &gremlinxx::GraphTraversal::hasNext)
        .def("iterate", &gremlinxx::GraphTraversal::iterate)
        .def("next", [](gremlinxx::GraphTraversal& trv){
            std::any a = trv.next();

            if(a.type() == typeid(gremlinxx::Vertex)) {
                throw std::runtime_error("Vertex return type currently unsupported");
            }

            maelstrom::primitive_t prim_type;
            try {
                prim_type = maelstrom::prim_type_of(a);
            } catch(std::runtime_error& ex) {
                throw std::runtime_error("Can't convert to Python type: " + std::string(ex.what()));
            }
            switch(prim_type) {
                case maelstrom::UINT64:
                    return nb::cast(std::any_cast<uint64_t>(a));
                case maelstrom::UINT32:
                    return nb::cast(std::any_cast<uint32_t>(a));
                case maelstrom::UINT8:
                    return nb::cast(std::any_cast<uint8_t>(a));
                case maelstrom::INT64:
                    return nb::cast(std::any_cast<int64_t>(a));
                case maelstrom::INT32:
                    return nb::cast(std::any_cast<int32_t>(a));
                case maelstrom::INT8:  
                    return nb::cast(std::any_cast<int8_t>(a));
                case maelstrom::FLOAT64:
                    return nb::cast(std::any_cast<double>(a));
                case maelstrom::FLOAT32:
                    return nb::cast(std::any_cast<float>(a));
            }
            throw std::runtime_error("invalid type");
        })
        .def("toList", [](gremlinxx::GraphTraversal& trv){
            auto vec = trv.toVector();

            std::vector<nb::object> nvec;
            nvec.reserve(vec.size());
            for(auto & a : vec) nvec.push_back(cast_type(a));

            return nvec;
        })
        .def("toArray", [](gremlinxx::GraphTraversal& trv) {
            trv.iterate();
            auto traverser_data = trv.getTraverserSet().getTraverserData().to(maelstrom::HOST);
            return maelstrom_to_numpy(traverser_data);
        })
        .def("explain", [](gremlinxx::GraphTraversal& trv){
            return trv.explain();
        });
}