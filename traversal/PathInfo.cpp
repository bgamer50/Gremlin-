#include "traversal/PathInfo.h"
#include "maelstrom/algorithms/remove_if.h"
#include "maelstrom/algorithms/select.h"
#include "maelstrom/algorithms/increment.h"
#include "maelstrom/algorithms/set.h"
#include "maelstrom/algorithms/unpack.h"

namespace gremlinxx {
    namespace traversal {

        void PathInfo::advance(maelstrom::vector prev_traverser_data, maelstrom::vector origin) {
            if(prev_traverser_data.empty()) {
                this->paths.clear();
                this->path_lengths.clear();
            }

            bool empty_start = false;
            if(paths.empty()) {
                empty_start = true;
            } else if(prev_traverser_data.size() != paths[0].size()) {
                throw std::runtime_error("next vector size must match path size");
            }

            this->paths.push_back(std::move(prev_traverser_data));

            // Step 1: update path lengths
            if(!empty_start) {
                if(!origin.empty()) {
                    maelstrom::vector new_path_lengths = maelstrom::select(
                        this->path_lengths,
                        origin
                    );

                    maelstrom::increment(new_path_lengths, static_cast<path_length_t>(1));
                    this->path_lengths.clear();
                    this->path_lengths = std::move(new_path_lengths);
                } else {
                    maelstrom::increment(this->path_lengths, static_cast<path_length_t>(1));
                }                
            } else {
                size_t starting_size = origin.empty() ? prev_traverser_data.size() : origin.size();
                this->path_lengths.resize(starting_size);
                maelstrom::set(
                    this->path_lengths,
                    0,
                    this->path_lengths.size(),
                    static_cast<path_length_t>(1)
                );
            }

            if(origin.empty()) return;

            // Step 2: perform selection
            for(size_t k = 0; k < this->paths.size(); ++k) {
                maelstrom::vector selected_traversers = maelstrom::select(
                    this->paths[k],
                    origin
                );

                this->paths[k].clear();
                this->paths[k] = std::move(selected_traversers);
            }         
            
        }

        std::vector<PathInfo> PathInfo::unpack() {
            std::vector<std::vector<maelstrom::vector>> unpacked_paths;
            unpacked_paths.resize(this->path_lengths.size());
            for(size_t k = 0; k < this->paths.size(); ++k) {
                unpacked_paths[k] = maelstrom::unpack(this->paths[k]);
            }

            auto unpacked_path_lengths = maelstrom::unpack(this->path_lengths);

            std::vector<PathInfo> unpacked_path_info;
            unpacked_path_info.resize(this->path_lengths.size());
            for(size_t k = 0; k < this->path_lengths.size(); ++k) {
                for(size_t p = 0; p < this->paths.size(); ++p) {
                    unpacked_path_info[k].paths[p] = std::move(unpacked_paths[p][k]);
                }
                unpacked_path_info[k].path_lengths = std::move(unpacked_path_lengths[k]);
            }

            return unpacked_path_info;
        }

        void PathInfo::add_paths(PathInfo& other_path_info) {
            if(other_path_info.paths.size() == 0) return;

            size_t sz = (this->paths.size() > 0) ? this->paths[0].size() : 0;
            size_t other_sz = other_path_info.paths[0].size();

            if(this->paths.size() < other_path_info.paths.size()) {
                size_t d = other_path_info.paths.size() - sz;

                for(size_t k = 0; k < d; ++k) {
                    auto dummy_path = maelstrom::make_vector_like(other_path_info.paths[k]);
                    dummy_path.resize(sz);
                    this->paths.insert(
                        this->paths.begin() + k,
                        std::move(dummy_path)
                    );
                }
            }

            // add from back to front even though k is being incremented
            for(size_t k = 0; k < other_path_info.paths.size(); ++k) {
                maelstrom::vector& current_path = this->paths[this->paths.size() - k - 1];
                maelstrom::vector& other_current_path = other_path_info.paths[other_path_info.paths.size() - k - 1];

                if(current_path.get_dtype() != other_current_path.get_dtype()) {
                    throw std::runtime_error("Can't merge paths with different data types!");
                }

                current_path.insert(
                    current_path.size(),
                    other_current_path
                );
            }

            if(other_path_info.paths.size() < this->paths.size()) {
                size_t d = this->paths.size() - other_path_info.paths.size();
                for(size_t k = 0; k < d; ++k) {
                    this->paths[k].resize(sz + other_sz);
                }
            }

            this->path_lengths.insert(
                this->path_lengths.size(),
                other_path_info.path_lengths
            );
            
        }

        void PathInfo::clear() {
            this->path_lengths.clear();
            this->paths.clear();
        }

    }
}