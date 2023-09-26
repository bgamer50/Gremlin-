#pragma once

#include "maelstrom/containers/vector.h"

namespace gremlinxx {
    namespace traversal {

        typedef uint32_t path_length_t;

        class PathInfo {
            public:
                std::vector<maelstrom::vector> paths;
                maelstrom::vector path_lengths;

                /*
                    Appends prev_traverser_data to the paths.  Then, if origin is set,
                    properly transforms the original paths based on the originating
                    traversers of interest.  If not set, no transformation is performed.
                */
                void advance(maelstrom::vector prev_traverser_data, maelstrom::vector origin=maelstrom::vector());

                /*
                    For each traverser's path info p, creates a new PathInfo object
                    consisting only of the path info in p.  Returns a vector with the
                    new PathInfo objects.
                */
                std::vector<PathInfo> unpack();

                /*
                    Adds the path data in the other path info to this
                    path info object.
                */
                void add_paths(PathInfo& other_path_info);

                /*
                    Clears all data from this path info object.
                */
                void clear();
        };

    }
}