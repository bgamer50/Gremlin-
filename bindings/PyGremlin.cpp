#include <nanobind/nanobind.h>
#include <nanobind/stl/string.h>
#include <nanobind/ndarray.h>
#include <nanobind/stl/vector.h>

#include "gremlinxx/gremlinxx.h"
#include "maelstrom/storage/datatype.h"
#include "maelstrom/util/any_utils.h"

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
    if(vec.empty()) {
        const size_t shape[] = {0L};
        return nb::cast(
            nb::ndarray<nb::numpy, const T>(
                nullptr,
                1,
                shape,
                nb::handle()
            )
        );
    }

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
    if(vec.get_dtype().name == "string") {
        auto host_view_or_copy = maelstrom::as_host_vector(vec);
        nb::list out;

        auto dtype = vec.get_dtype();
        for(size_t k = 0; k < vec.size(); ++k) {
            char* loc = static_cast<char*>(vec.data()) + (maelstrom::size_of(dtype) * k);
            out.append(std::any_cast<std::string>(dtype.deserialize(loc)));
        }

        auto np = nb::module_::import_("numpy");
        return np.attr("asarray")(out);
    }

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
    
    nb::class_<gremlinxx::P>(m, "P")
        .def_static("eq", [](uint64_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](uint32_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](uint8_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](int64_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](int32_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](int8_t val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](double val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](float val){ return gremlinxx::P::eq(val); })
        .def_static("eq", [](std::string val){ return gremlinxx::P::eq(val); })
        .def_static("neq", [](uint64_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](uint32_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](uint8_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](int64_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](int32_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](int8_t val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](double val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](float val){ return gremlinxx::P::neq(val); })
        .def_static("neq", [](std::string val){ return gremlinxx::P::neq(val); })
        .def_static("gt", [](uint64_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](uint32_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](uint8_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](int64_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](int32_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](int8_t val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](double val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](float val){ return gremlinxx::P::gt(val); })
        .def_static("gt", [](std::string val){ return gremlinxx::P::gt(val); })
        .def_static("gte", [](uint64_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](uint32_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](uint8_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](int64_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](int32_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](int8_t val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](double val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](float val){ return gremlinxx::P::gte(val); })
        .def_static("gte", [](std::string val){ return gremlinxx::P::gte(val); })
        .def_static("lt", [](uint64_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](uint32_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](uint8_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](int64_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](int32_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](int8_t val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](double val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](float val){ return gremlinxx::P::lt(val); })
        .def_static("lt", [](std::string val){ return gremlinxx::P::lt(val); })
        .def_static("lte", [](uint64_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](uint32_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](uint8_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](int64_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](int32_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](int8_t val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](double val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](float val){ return gremlinxx::P::lte(val); })
        .def_static("lte", [](std::string val){ return gremlinxx::P::lte(val); })
        .def_static("between", [](uint64_t val1, uint64_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](uint32_t val1, uint32_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](uint8_t val1, uint8_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](int64_t val1, int64_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](int32_t val1, int32_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](int8_t val1, int8_t val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](double val1, double val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](float val1, float val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("between", [](std::string val1, std::string val2){ return gremlinxx::P::between(val1, val2); })
        .def_static("inside", [](uint64_t val1, uint64_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](uint32_t val1, uint32_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](uint8_t val1, uint8_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](int64_t val1, int64_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](int32_t val1, int32_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](int8_t val1, int8_t val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](double val1, double val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](float val1, float val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("inside", [](std::string val1, std::string val2){ return gremlinxx::P::inside(val1, val2); })
        .def_static("outside", [](uint64_t val1, uint64_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](uint32_t val1, uint32_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](uint8_t val1, uint8_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](int64_t val1, int64_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](int32_t val1, int32_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](int8_t val1, int8_t val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](double val1, double val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](float val1, float val2){ return gremlinxx::P::outside(val1, val2); })
        .def_static("outside", [](std::string val1, std::string val2){ return gremlinxx::P::outside(val1, val2); });

    nb::class_<gremlinxx::TraversalStrategy>(m, "TraversalStrategy")
        .def_ro_static("RepeatStepCompletionStrategy", &gremlinxx::RepeatStepCompletionStrategy)
        .def_ro_static("ByModulatingStrategy", &gremlinxx::ByModulatingStrategy)
        .def_ro_static("FromToModulatingStrategy", &gremlinxx::FromToModulatingStrategy)
        .def_ro_static("LimitSupportingStrategy:", &gremlinxx::LimitSupportingStrategy)
        .def_ro_static("SubgraphStepCompletionStrategy", &gremlinxx::SubgraphStepCompletionStrategy)
        .def_ro_static("RepeatUnrollStrategy", &gremlinxx::RepeatUnrollStrategy)
        .def_ro_static("HasJoinStrategy", &gremlinxx::HasJoinStrategy)
        .def_ro_static("NoOpRemovalStrategy", &gremlinxx::NoOpRemovalStrategy)
        .def_ro_static("BasicPatternExtractionStrategy", &gremlinxx::BasicPatternExtractionStrategy);
        

    nb::class_<gremlinxx::GraphTraversalSource>(m, "GraphTraversalSource")
        .def("withoutStrategies", &gremlinxx::GraphTraversalSource::withoutStrategies)
        .def("withoutStrategy", &gremlinxx::GraphTraversalSource::withoutStrategy)
        .def("withStrategy", &gremlinxx::GraphTraversalSource::withStrategy)
        .def("V", [](gremlinxx::GraphTraversalSource& g){
            return g.V();
        })
        .def("V", [](gremlinxx::GraphTraversalSource& g, uint64_t v_id){
            return g.V(std::any(v_id));
        })
        .def("V", [](gremlinxx::GraphTraversalSource& g, std::vector<uint64_t> v_ids){
            std::vector<std::any> anys;
            anys.reserve(v_ids.size());
            for(uint64_t i : v_ids) anys.push_back(i);
            return g.V(anys);
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
        .def("V", [](gremlinxx::GraphTraversal& trv, uint64_t v_id){
            return trv.V(std::any(v_id));
        })
        .def("addV", [](gremlinxx::GraphTraversal& trv, std::string label){
            return trv.addV(label);
        })
        .def("addV", [](gremlinxx::GraphTraversal& trv) {
            return trv.addV();
        })
        .def("addE", &gremlinxx::GraphTraversal::addE)
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
        .def("property", [](gremlinxx::GraphTraversal& trv, std::string property_key, gremlinxx::GraphTraversal prop_traversal){
            return trv.property(property_key, prop_traversal);
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
        .def("_as", &gremlinxx::GraphTraversal::as)
        .def("by", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal mod){
            return trv.by(mod);
        })
        .def("by", [](gremlinxx::GraphTraversal& trv, std::string mod){
            return trv.by(mod);
        })
        .def("by", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal mod, std::string order_str){
            if(order_str == "ASC") return trv.by(mod, gremlinxx::Order::ASC);
            if(order_str == "DESC") return trv.by(mod, gremlinxx::Order::DESC);
            if(order_str == "SHUFFLE") return trv.by(mod, gremlinxx::Order::SHUFFLE);
            
            throw std::invalid_argument("Invalid order " + order_str);
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
        .def("_from", [](gremlinxx::GraphTraversal& trv, std::string side_effect_label){
            return trv.from(side_effect_label);
        })
        .def("_from", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal from_traversal){
            return trv.from(from_traversal);
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
        .def("has", [](gremlinxx::GraphTraversal& trv, std::string key, gremlinxx::P p){
            return trv.has(key, p);
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
        .def("to", [](gremlinxx::GraphTraversal& trv, gremlinxx::GraphTraversal to_traversal){
            return trv.to(to_traversal);
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
        .def("_in", [](gremlinxx::GraphTraversal& trv, std::vector<std::string> labels) {
            return trv.in(labels);
        })
        .def("_in", [](gremlinxx::GraphTraversal& trv) {
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
        })
        .def("getTraversalProperty", [](gremlinxx::GraphTraversal& trv, std::string property) {
            auto prop = trv.getTraversalProperty(property);
            auto graph = std::any_cast<std::shared_ptr<gremlinxx::Graph>>(prop);

            return graph.get();
        }, nb::rv_policy::reference_internal);
}