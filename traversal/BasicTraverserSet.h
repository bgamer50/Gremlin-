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

                inline void checkOutOfBounds(size_t i) {
                    if(i >= this->traverser_data.size()) {
                        std::stringstream sx;
                        sx << "Attempted to get traverser " << i;
                        sx << " but there are only " << this->traverser_data.size() << " traversers!";
                        throw std::runtime_error(sx.str());
                    }
                }

            public:
                /*
                    Enables path persistence (keeping track of each traversers's whole path)
                */
                using TraverserSet::enable_path_persistence;
                inline virtual void enable_path_persistence() {
                    this->persist_paths = true;
                }

                /*
                    Disables path persistence (keeping track of each traversers's whole path)
                */
                using TraverserSet::disable_path_persistence;
                inline virtual void disable_path_persistence() {
                    this->persist_paths = false;
                }

                /*
                    Realizes all traversers, and returns them.
                */
                using TraverserSet::toTraversers;
                virtual std::vector<Traverser> toTraversers();

                /*
                    Realizes and returns the ith traverser.
                */
                using TraverserSet::getTraverser;
                virtual Traverser getTraverser(size_t i);
                
                using TraverserSet::getData;
                virtual boost::any getData(size_t i);

                /*
                    Returns a copy of data associated with each traverser in this traverser set.
                */
                using TraverserSet::getTraverserData;
                inline virtual maelstrom::vector getTraverserData() {
                    return this->traverser_data;
                }

                /*
                    Returns a copy of the side effects of each traverser in this traverser set.
                */
                using TraverserSet::getSideEffects;
                inline virtual std::unordered_map<std::string, maelstrom::vector> getSideEffects() {
                    return this->side_effects;
                }

                /*
                    Returns a copy of the paths in this traverser set.
                */
                using TraverserSet::getPathInfo;
                inline virtual gremlinxx::traversal::PathInfo getPathInfo() {
                    return this->path_info;
                }

                using TraverserSet::getPathLength;
                inline virtual size_t getPathLength() {
                    return this->path_info.paths.size();
                }

                using TraverserSet::reinitialize;
                virtual void reinitialize(maelstrom::vector new_data, std::unordered_map<std::string, maelstrom::vector> side_effects, gremlinxx::traversal::PathInfo path_info);

                using TraverserSet::resize;
                virtual void resize(size_t new_size);

                /*
                    Advances the traversers in this traverser set.
                    The given input function will be passed the traverser data, traverser side effects, and traverser paths.
                    The input function must return the new traverser data and the originating traversers (in order to preserve paths if enabled).
                    Modifying side effects is allowed, but the traverser data and paths should not be changed.

                    Arguments
                    ---------
                    func: std::function
                        It should take the following parameters:
                            maelstrom::vector& traverser_data
                            std::unordered_map<std::string, maelstrom::vector>& traverser_side_effects
                            std::vector<maelstrom::vector>& paths
                    
                    Returns
                    -------
                    std::pair
                        First element: maelstrom::vector of new traverser data
                        Second element: maelstrom::vector of originating traversers.
                            If empty, it's assumed that the index of the new traversers corresponds to the index
                            of the old traversers (and the sizes must match in that case).
                */
                using TraverserSet::advance;
                virtual void advance(std::function<std::pair<maelstrom::vector, maelstrom::vector>(maelstrom::vector&, std::unordered_map<std::string, maelstrom::vector>&, gremlinxx::traversal::PathInfo&)> func);

                using TraverserSet::unpack;
                virtual std::vector<std::tuple<maelstrom::vector, std::unordered_map<std::string, maelstrom::vector>, gremlinxx::traversal::PathInfo>> unpack();

                using TraverserSet::trim_paths;
                inline virtual void trim_paths(size_t ix_start, size_t ix_end);

                /*
                    Updates the side effects for all traversers for the given key.
                */
               using TraverserSet::set_side_effects;
               virtual void set_side_effects(std::string se_key, maelstrom::vector values);

               /*
                    Inserts the traversers in the other traverser set into this traverser set.
               */
               using TraverserSet::addTraversers;
               virtual void addTraversers(maelstrom::vector& other_traverser_data, std::unordered_map<std::string, maelstrom::vector>& other_side_effects, gremlinxx::traversal::PathInfo& other_paths);
               virtual void addTraversers(TraverserSet& other_traversers);

               /*
                    Returns the number of traversers.
               */
               using TraverserSet::size;
               inline virtual size_t size() {
                    return this->traverser_data.size();
               }

               /*
                    Clears all traversers.
               */
               using TraverserSet::clear;
               virtual void clear();

               /*
                    Returns true if this traverser set is empty, false otherwise. 
               */
               using TraverserSet::empty;
               inline virtual bool empty() {
                    return this->traverser_data.size() > 0;
               }

               /*
                    Erases the ith traverser.
               */
               using TraverserSet::erase;
               inline virtual void erase(size_t i) {
                    throw std::runtime_error("erase currently unimplemented for BasicTraverserSet");
               }
        };
    }
}