#pragma once

// TODO split these steps into their own files and remove this header

namespace gremlinxx {
        
    inline GraphTraversal addE(std::string label) { return GraphTraversal().addE(label); }
    inline GraphTraversal addV(std::string label) { return GraphTraversal().addV(label); }
    inline GraphTraversal addV() { return GraphTraversal().addV(); }
    inline GraphTraversal property(std::string property_key, std::any value) { return GraphTraversal().property(property_key, value); }
    inline GraphTraversal as(std::string sideEffectLabel) { return GraphTraversal().as(sideEffectLabel); }
    inline GraphTraversal by(std::any arg) { return GraphTraversal().by(arg); }
    inline GraphTraversal cap(std::string sideEffectLabel) { return GraphTraversal().cap(sideEffectLabel); }
    inline GraphTraversal coalesce(std::vector<GraphTraversal> traversals) { return GraphTraversal().coalesce(std::move(traversals)); }
    inline GraphTraversal count() { return GraphTraversal().count(); }
    inline GraphTraversal dedup() { return GraphTraversal().dedup(); }
    inline GraphTraversal emit() { return GraphTraversal().emit(); }
    inline GraphTraversal emit(GraphTraversal emitTraversal) { return GraphTraversal().emit(emitTraversal); }
    inline GraphTraversal from(std::string sideEffectLabel) { return GraphTraversal().from(sideEffectLabel); }
    inline GraphTraversal from(Vertex fromVertex) { return GraphTraversal().from(fromVertex); }
    inline GraphTraversal V() { return GraphTraversal().V(); }
    inline GraphTraversal V(Vertex vertex) { return GraphTraversal().V(vertex); }
    inline GraphTraversal V(std::vector<Vertex> vertices) { return GraphTraversal().V(vertices); }
    inline GraphTraversal V(std::any v_id) { return GraphTraversal().V(v_id); }
    inline GraphTraversal groupCount() { return GraphTraversal().groupCount(); }
    inline GraphTraversal has(std::string key, P pred) { return GraphTraversal().has(key, pred); }
    inline GraphTraversal has(std::string key, std::any value) { return GraphTraversal().has(key, value); }
    inline GraphTraversal has(std::string key) { return GraphTraversal().has(key); }
    inline GraphTraversal id() { return GraphTraversal().id(); }
    inline GraphTraversal identity() { return GraphTraversal().identity(); }
    inline GraphTraversal inject(std::vector<std::any> objects) { return GraphTraversal().inject(objects); }
    inline GraphTraversal is(std::any val) { return GraphTraversal().is(val); }
    inline GraphTraversal is(P predicate) { return GraphTraversal().is(predicate); }
    inline GraphTraversal limit(uint64_t the_limit) { return GraphTraversal().limit(the_limit); }
    inline GraphTraversal loops() { return GraphTraversal().loops(); }
    inline GraphTraversal min() { return GraphTraversal().min(); }
    inline GraphTraversal order() { return GraphTraversal().order(); }
    inline GraphTraversal repeat(GraphTraversal repeatTraversal) { return GraphTraversal().repeat(repeatTraversal); }
    inline GraphTraversal select(std::string sideEffectLabel) { return GraphTraversal().select(sideEffectLabel); }
    inline GraphTraversal subgraph(std::string sideEffectLabel) { return GraphTraversal().subgraph(sideEffectLabel); }
    inline GraphTraversal to(std::string sideEffectLabel) { return GraphTraversal().to(sideEffectLabel); }
    inline GraphTraversal to(Vertex toVertex) { return GraphTraversal().to(toVertex); }
    inline GraphTraversal _union(std::vector<GraphTraversal> unionTraversals) { return GraphTraversal()._union(std::move(unionTraversals)); }
    inline GraphTraversal until(GraphTraversal untilTraversal) { return GraphTraversal().until(untilTraversal); }
    inline GraphTraversal elementMap(std::vector<std::string> labels) { return GraphTraversal().elementMap(labels); }
    inline GraphTraversal values(std::vector<std::string> labels) { return GraphTraversal().values(labels); }
    inline GraphTraversal values(std::string label) { return GraphTraversal().values(label); }
    inline GraphTraversal both() { return GraphTraversal().both(); }
    inline GraphTraversal both(std::vector<std::string> labels) { return GraphTraversal().both(labels); }
    inline GraphTraversal bothE() { return GraphTraversal().bothE(); }
    inline GraphTraversal bothE(std::vector<std::string> labels) { return GraphTraversal().bothE(labels); }
    inline GraphTraversal out() { return GraphTraversal().out(); }
    inline GraphTraversal out(std::vector<std::string> labels) { return GraphTraversal().out(labels); }
    inline GraphTraversal in() { return GraphTraversal().in(); }
    inline GraphTraversal in(std::vector<std::string> labels) { return GraphTraversal().in(labels); }
    inline GraphTraversal outE() { return GraphTraversal().outE(); }
    inline GraphTraversal outE(std::vector<std::string> labels) { return GraphTraversal().outE(labels); }
    inline GraphTraversal inE() { return GraphTraversal().inE(); }
    inline GraphTraversal inE(std::vector<std::string> labels) { return GraphTraversal().inE(labels); }
    inline GraphTraversal times(size_t times) { return GraphTraversal().times(times); }
    inline GraphTraversal where(std::string label, P predicate) { return GraphTraversal().where(label, predicate); }

}