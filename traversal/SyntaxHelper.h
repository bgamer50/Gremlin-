#pragma once

// TODO split these steps into their own files and remove this header

namespace gremlinxx {
        
    inline GraphTraversal* addE(std::string label) { return (new GraphTraversal())->addE(label); }
    inline GraphTraversal* addV(std::string label) { return (new GraphTraversal())->addV(label); }
    inline GraphTraversal* addV() { return (new GraphTraversal())->addV(); }
    inline GraphTraversal* property(std::string property_key, boost::any value) { return (new GraphTraversal())->property(property_key, value); }
    inline GraphTraversal* as(std::string sideEffectLabel) { return (new GraphTraversal())->as(sideEffectLabel); }
    inline GraphTraversal* by(boost::any arg) { return (new GraphTraversal())->by(arg); }
    inline GraphTraversal* cap(std::string sideEffectLabel) { return (new GraphTraversal())->cap(sideEffectLabel); }
    inline GraphTraversal* coalesce(std::vector<GraphTraversal*> traversals) { return (new GraphTraversal())->coalesce(traversals); }
    inline GraphTraversal* count() { return (new GraphTraversal())->count(); }
    inline GraphTraversal* dedup() { return (new GraphTraversal())->dedup(); }
    inline GraphTraversal* emit() { return (new GraphTraversal())->emit(); }
    inline GraphTraversal* emit(GraphTraversal* emitTraversal) { return (new GraphTraversal())->emit(emitTraversal); }
    inline GraphTraversal* from(std::string sideEffectLabel) { return (new GraphTraversal())->from(sideEffectLabel); }
    inline GraphTraversal* from(Vertex* fromVertex) { return (new GraphTraversal())->from(fromVertex); }
    inline GraphTraversal* V() { return (new GraphTraversal())->V(); }
    inline GraphTraversal* V(Vertex* vertex) { return (new GraphTraversal())->V(vertex); }
    inline GraphTraversal* V(std::vector<Vertex*> vertices) { return (new GraphTraversal())->V(vertices); }
    inline GraphTraversal* V(boost::any v_id) { return (new GraphTraversal())->V(v_id); }
    inline GraphTraversal* groupCount() { return (new GraphTraversal())->groupCount(); }
    inline GraphTraversal* has(std::string key, P pred) { return (new GraphTraversal())->has(key, pred); }
    inline GraphTraversal* has(std::string key, boost::any value) { return (new GraphTraversal())->has(key, value); }
    inline GraphTraversal* has(std::string key) { return (new GraphTraversal())->has(key); }
    inline GraphTraversal* id() { return (new GraphTraversal())->id(); }
    inline GraphTraversal* identity() { return (new GraphTraversal())->identity(); }
    inline GraphTraversal* inject(std::vector<boost::any> objects) { return (new GraphTraversal())->inject(objects); }
    inline GraphTraversal* is(boost::any val) { return (new GraphTraversal())->is(val); }
    inline GraphTraversal* is(P predicate) { return (new GraphTraversal())->is(predicate); }
    inline GraphTraversal* limit(uint64_t the_limit) { return (new GraphTraversal())->limit(the_limit); }
    inline GraphTraversal* loops() { return (new GraphTraversal())->loops(); }
    template<typename T>
    inline GraphTraversal* min() { return (new GraphTraversal())->min<T>(); }
    inline GraphTraversal* order() { return (new GraphTraversal())->order(); }
    inline GraphTraversal* repeat(GraphTraversal* repeatTraversal) { return (new GraphTraversal())->repeat(repeatTraversal); }
    inline GraphTraversal* select(std::string sideEffectLabel) { return (new GraphTraversal())->select(sideEffectLabel); }
    inline GraphTraversal* subgraph(std::string sideEffectLabel) { return (new GraphTraversal())->subgraph(sideEffectLabel); }
    inline GraphTraversal* to(std::string sideEffectLabel) { return (new GraphTraversal())->to(sideEffectLabel); }
    inline GraphTraversal* to(Vertex* toVertex) { return (new GraphTraversal())->to(toVertex); }
    inline GraphTraversal* _union(std::vector<GraphTraversal*> unionTraversals) { return (new GraphTraversal())->_union(unionTraversals); }
    inline GraphTraversal* until(GraphTraversal* untilTraversal) { return (new GraphTraversal())->until(untilTraversal); }
    inline GraphTraversal* elementMap(std::vector<std::string> labels) { return (new GraphTraversal())->elementMap(labels); }
    inline GraphTraversal* values(std::vector<std::string> labels) { return (new GraphTraversal())->values(labels); }
    inline GraphTraversal* values(std::string label) { return (new GraphTraversal())->values(label); }
    inline GraphTraversal* map(GraphTraversal* map_traversal) { return (new GraphTraversal())->map(map_traversal); }
    inline GraphTraversal* both() { return (new GraphTraversal())->both(); }
    inline GraphTraversal* both(std::vector<std::string> labels) { return (new GraphTraversal())->both(labels); }
    inline GraphTraversal* bothE() { return (new GraphTraversal())->bothE(); }
    inline GraphTraversal* bothE(std::vector<std::string> labels) { return (new GraphTraversal())->bothE(labels); }
    inline GraphTraversal* out() { return (new GraphTraversal())->out(); }
    inline GraphTraversal* out(std::vector<std::string> labels) { return (new GraphTraversal())->out(labels); }
    inline GraphTraversal* in() { return (new GraphTraversal())->in(); }
    inline GraphTraversal* in(std::vector<std::string> labels) { return (new GraphTraversal())->in(labels); }
    inline GraphTraversal* outE() { return (new GraphTraversal())->outE(); }
    inline GraphTraversal* outE(std::vector<std::string> labels) { return (new GraphTraversal())->outE(labels); }
    inline GraphTraversal* inE() { return (new GraphTraversal())->inE(); }
    inline GraphTraversal* inE(std::vector<std::string> labels) { return (new GraphTraversal())->inE(labels); }
    inline GraphTraversal* times(size_t times) { return (new GraphTraversal())->times(times); }
    inline GraphTraversal* where(std::string label, P predicate) { return (new GraphTraversal())->where(label, predicate); }

}