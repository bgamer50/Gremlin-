#pragma once

// TODO split these steps into their own files and remove this header

GraphTraversal* addE(std::string label) { return (new GraphTraversal())->addE(label); }
GraphTraversal* addV(std::string label) { return (new GraphTraversal())->addV(label); }
GraphTraversal* addV() { return (new GraphTraversal())->addV(); }
GraphTraversal* property(std::string property_key, boost::any value) { return (new GraphTraversal())->property(property_key, value); }
GraphTraversal* as(std::string sideEffectLabel) { return (new GraphTraversal())->as(sideEffectLabel); }
GraphTraversal* by(boost::any arg) { return (new GraphTraversal())->by(arg); }
GraphTraversal* cap(std::string sideEffectLabel) { return (new GraphTraversal())->cap(sideEffectLabel); }
GraphTraversal* coalesce(std::vector<GraphTraversal*> traversals) { return (new GraphTraversal())->coalesce(traversals); }
GraphTraversal* count() { return (new GraphTraversal())->count(); }
GraphTraversal* dedup() { return (new GraphTraversal())->dedup(); }
GraphTraversal* emit() { return (new GraphTraversal())->emit(); }
GraphTraversal* emit(GraphTraversal* emitTraversal) { return (new GraphTraversal())->emit(emitTraversal); }
GraphTraversal* fold() { return (new GraphTraversal())->fold(); }
GraphTraversal* from(std::string sideEffectLabel) { return (new GraphTraversal())->from(sideEffectLabel); }
GraphTraversal* from(Vertex* fromVertex) { return (new GraphTraversal())->from(fromVertex); }
GraphTraversal* V() { return (new GraphTraversal())->V(); }
GraphTraversal* V(Vertex* vertex) { return (new GraphTraversal())->V(vertex); }
GraphTraversal* V(std::vector<Vertex*> vertices) { return (new GraphTraversal())->V(vertices); }
GraphTraversal* V(boost::any v_id) { return (new GraphTraversal())->V(v_id); }
GraphTraversal* groupCount() { return (new GraphTraversal())->groupCount(); }
GraphTraversal* has(std::string key, P pred) { return (new GraphTraversal())->has(key, pred); }
GraphTraversal* has(std::string key, boost::any value) { return (new GraphTraversal())->has(key, value); }
GraphTraversal* has(std::string key) { return (new GraphTraversal())->has(key); }
GraphTraversal* id() { return (new GraphTraversal())->id(); }
GraphTraversal* identity() { return (new GraphTraversal())->identity(); }
GraphTraversal* inject(std::vector<boost::any> objects) { return (new GraphTraversal())->inject(objects); }
GraphTraversal* is(boost::any val) { return (new GraphTraversal())->is(val); }
GraphTraversal* is(P predicate) { return (new GraphTraversal())->is(predicate); }
GraphTraversal* limit(uint64_t the_limit) { return (new GraphTraversal())->limit(the_limit); }
GraphTraversal* loops() { return (new GraphTraversal())->loops(); }
template<typename T>
GraphTraversal* min() { return (new GraphTraversal())->min<T>(); }
GraphTraversal* order() { return (new GraphTraversal())->order(); }
GraphTraversal* repeat(GraphTraversal* repeatTraversal) { return (new GraphTraversal())->repeat(repeatTraversal); }
GraphTraversal* select(std::string sideEffectLabel) { return (new GraphTraversal())->select(sideEffectLabel); }
GraphTraversal* subgraph(std::string sideEffectLabel) { return (new GraphTraversal())->subgraph(sideEffectLabel); }
GraphTraversal* to(std::string sideEffectLabel) { return (new GraphTraversal())->to(sideEffectLabel); }
GraphTraversal* to(Vertex* toVertex) { return (new GraphTraversal())->to(toVertex); }
GraphTraversal* unfold() { return (new GraphTraversal())->unfold(); }
GraphTraversal* _union(std::vector<GraphTraversal*> unionTraversals) { return (new GraphTraversal())->_union(unionTraversals); }
GraphTraversal* until(GraphTraversal* untilTraversal) { return (new GraphTraversal())->until(untilTraversal); }
GraphTraversal* valueMap(std::vector<std::string> labels) { return (new GraphTraversal())->valueMap(labels); }
GraphTraversal* values(std::vector<std::string> labels) { return (new GraphTraversal())->values(labels); }
GraphTraversal* values(std::string label) { return (new GraphTraversal())->values(label); }
GraphTraversal* map(GraphTraversal* map_traversal) { return (new GraphTraversal())->map(map_traversal); }
GraphTraversal* both() { return (new GraphTraversal())->both(); }
GraphTraversal* both(std::vector<std::string> labels) { return (new GraphTraversal())->both(labels); }
GraphTraversal* bothE() { return (new GraphTraversal())->bothE(); }
GraphTraversal* bothE(std::vector<std::string> labels) { return (new GraphTraversal())->bothE(labels); }
GraphTraversal* out() { return (new GraphTraversal())->out(); }
GraphTraversal* out(std::vector<std::string> labels) { return (new GraphTraversal())->out(labels); }
GraphTraversal* in() { return (new GraphTraversal())->in(); }
GraphTraversal* in(std::vector<std::string> labels) { return (new GraphTraversal())->in(labels); }
GraphTraversal* outE() { return (new GraphTraversal())->outE(); }
GraphTraversal* outE(std::vector<std::string> labels) { return (new GraphTraversal())->outE(labels); }
GraphTraversal* inE() { return (new GraphTraversal())->inE(); }
GraphTraversal* inE(std::vector<std::string> labels) { return (new GraphTraversal())->inE(labels); }
GraphTraversal* times(size_t times) { return (new GraphTraversal())->times(times); }
GraphTraversal* where(std::string label, P predicate) { return (new GraphTraversal())->where(label, predicate); }
