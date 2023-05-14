#pragma once

#include <vector>
#include <sstream>
#include "traversal/TraverserSet.h"
#include "maelstrom/algorithms/select.h"

namespace gremlinxx {
    namespace traversal {

        class BasicTraverserSet : public TraverserSet {
            private:
                maelstrom::vector traverser_data;
                gremlinxx::traversal::PathInfo path_info;
                std::unordered_map<std::string, maelstrom::vector> side_effects;

                bool persist_paths;

                void checkOutOfBounds(size_t i) {
                    if(i >= traverser_data.size()) {
                        std::stringstream sx;
                        sx << "Attempted to get traverser " << i;
                        sx << " but there are only " << traverser_data.size() << " traversers!";
                        throw std::runtime_error(sx.str());
                    }
                }

            public:
                /*
                    Enables path persistence (keeping track of each traversers's whole path)
                */
                using TraverserSet::enable_path_persistence;
                virtual void enable_path_persistence() {
                    this->persist_paths = true;
                }

                /*
                    Disables path persistence (keeping track of each traversers's whole path)
                */
                using TraverserSet::disable_path_persistence;
                virtual void disable_path_persistence() {
                    this->persist_paths = false;
                }

                /*
                    Realizes all traversers, and returns them.
                */
                using TraverserSet::toTraversers;
                virtual std::vector<Traverser> toTraversers() {
                    std::vector<Traverser> traversers(this->size());

                    maelstrom::vector current_path_lengths = maelstrom::as_host_vector(this->path_info.path_lengths);

                    // Set the correct path length for each traverser.
                    for(size_t t = 0; t < traversers.size(); ++t) {
                        traversers[t].access_path().resize(
                            boost::any_cast<size_t>(current_path_lengths.get(t))
                        );
                    }

                    // Add paths backwards (last elements first).  This is necessary since path length
                    // may vary across traversers.
                    for(size_t k = 0; k < this->path_info.paths.size(); ++k) {
                        maelstrom::vector current_path_vec = maelstrom::as_host_vector(
                            this->path_info.paths[this->path_info.paths.size() - k - 1]
                        );

                        for(size_t t = 0; t < traversers.size(); ++t) {
                            Traverser& trv = traversers[t];
                            auto trv_path = trv.access_path();
                            
                            if(k < trv_path.size()) {
                                trv_path[k] = current_path_vec.get(t);
                            }
                        }
                    }
                }

                /*
                    Returns a copy of data associated with each traverser in this traverser set.
                */
                using TraverserSet::getTraverserData;
                virtual maelstrom::vector getTraverserData() {
                    return this->traverser_data;
                }

                /*
                    Advances the traversers in this traverser set.
                    The given input function will be passed the traverser data, traverser side effects, and traverser paths.
                    The input function must return the new traverser data and the originating traversers (in order to preserve paths if enabled).
                    Modifying side effects is allowed, but the traverser data and paths should not be changed.

                    Arguments
                    ---------
                    func: std::function
                        It should take the following parameters:
                            const maelstrom::vector& traverser_data
                            const std::unordered_map<std::string, maelstrom::vector>& traverser_side_effects
                            const std::vector<maelstrom::vector>& paths
                    
                    Returns
                    -------
                    std::pair
                        First element: maelstrom::vector of new traverser data
                        Second element: maelstrom::vector of originating traversers.
                            If empty, it's assumed that the index of the new traversers corresponds to the index
                            of the old traversers (and the sizes must match in that case).
                */
                using TraverserSet::advance;
                virtual void advance(std::function<std::pair<maelstrom::vector, maelstrom::vector>(const maelstrom::vector&, const std::unordered_map<std::string, maelstrom::vector>&, const gremlinxx::traversal::PathInfo&)> func) {
                    maelstrom::vector new_traverser_data;
                    maelstrom::vector output_origin;

                    // call function
                    std::tie(
                        new_traverser_data,
                        output_origin
                    ) = func(this->traverser_data, this->side_effects, this->path_info);
        
                    // Update side effects, do nothing if output origin was not set (assume 1 to 1 transformation)
                    if(!output_origin.empty()) {
                        for(auto it = this->side_effects.begin(); it != this->side_effects.end(); ++it) {
                            auto new_se = maelstrom::select(
                                it->second,
                                output_origin
                            );
                            it->second.clear();
                            it->second = std::move(new_se);
                        }
                    }

                    // Update paths, if output origin not provided, pass an empty vector instead
                    if(this->persist_paths) {
                        this->path_info.advance(
                            std::move(this->traverser_data),
                            std::move(output_origin)
                        );
                    }

                    // Update traverser data
                    this->traverser_data = std::move(new_traverser_data);
                }

                /*
                    Updates the side effects for all traversers for the given key.
                */
               using TraverserSet::set_side_effects;
               virtual void set_side_effects(std::string se_key, maelstrom::vector values) {
                    this->side_effects[se_key].clear();
                    this->side_effects[se_key] = std::move(values);
               }

               /*
                    Inserts the traversers in the other traverser set into this traverser set.
               */
               using TraverserSet::addTraversers;
               virtual void addTraversers(maelstrom::vector& other_traverser_data, std::unordered_map<std::string, maelstrom::vector>& other_side_effects, gremlinxx::traversal::PathInfo& other_paths) {
                    // Add the traverser data
                    this->traverser_data.insert(this->traverser_data.size(), other_traverser_data);

                    // Add the side effects
                    for(auto kv = other_side_effects.begin(); kv != other_side_effects.end(); ++kv) {
                        auto it = this->side_effects.find(kv->first);
                        if(it == this->side_effects.end()) {
                            this->side_effects[kv->first] = maelstrom::make_vector_like(kv->second);
                        }

                        maelstrom::vector& se_vec = this->side_effects[kv->first];
                        se_vec.insert(se_vec.size(), kv->second);
                    }

                    // Add the paths
                    if(this->persist_paths) {
                        this->path_info.add_paths(other_paths);
                    }
               }

               /*
                    Returns the number of traversers.
               */
               virtual size_t size() {
                    return this->traverser_data.size();
               }

               /*
                    Clears all traversers.
               */
               virtual void clear() {
                    this->traverser_data.clear();
                    this->side_effects.clear();
                    this->path_info.clear();
               }

               /*
                    Returns true if this traverser set is empty, false otherwise. 
               */
               virtual bool empty() {
                    return this->traverser_data.size() > 0;
               }

               /*
                    Erases the ith traverser.
               */
               virtual void erase(size_t i) {
                    throw std::runtime_error("erase currently unimplemented for BasicTraverserSet");
               }
        };
    }
}