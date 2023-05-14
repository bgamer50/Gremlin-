#pragma once
#include "traversal/Traverser.h"
#include "traversal/PathInfo.h"
#include "maelstrom/containers/vector.h"

#include <functional>

namespace gremlinxx {
    namespace traversal {

        class TraverserSet {
            public:
                /*
                    Enables path persistence (keeping track of each traversers's whole path)
                */
                virtual void enable_path_persistence() = 0;

                /*
                    Disables path persistence (keeping track of each traversers's whole path)
                */
                virtual void disable_path_persistence() = 0;

                /*
                    Realizes all traversers, and returns them.
                */
                virtual std::vector<Traverser> toTraversers() = 0;

                /*
                    Returns a copy of data associated with each traverser in this traverser set.
                */
                virtual maelstrom::vector getTraverserData() = 0;

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
                            const gremlinxx::traversal::PathInfo& paths
                    
                    Returns
                    -------
                    std::pair
                        First element: maelstrom::vector of new traverser data
                        Second element: maelstrom::vector of originating traversers.
                            If empty, it's assumed that the index of the new traversers corresponds to the index
                            of the old traversers (and the sizes must match in that case).
                */
                virtual void advance(std::function<std::pair<maelstrom::vector, maelstrom::vector>(const maelstrom::vector&, const std::unordered_map<std::string, maelstrom::vector>&, const gremlinxx::traversal::PathInfo&)> func) = 0;

                /*
                    Updates the side effects for all traversers for the given key.
                */
               virtual void set_side_effects(std::string se_key, maelstrom::vector values) = 0;

               /*
                    Inserts additional traversers into this traverser set.
               */
               virtual void addTraversers(maelstrom::vector& other_traverser_data, std::unordered_map<std::string, maelstrom::vector>& other_side_effects, gremlinxx::traversal::PathInfo& other_paths) = 0;

               /*
                    Returns the number of traversers.
               */
               virtual size_t size() = 0;

               /*
                    Clears all traversers.
               */
               virtual void clear() = 0;

               /*
                    Returns true if this traverser set is empty, false otherwise. 
               */
               virtual bool empty() = 0;

               /*
                    Erases the ith traverser.
               */
               virtual void erase(size_t i) = 0;
        };

    }
}