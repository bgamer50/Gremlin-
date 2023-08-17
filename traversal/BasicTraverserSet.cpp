#include "traversal/BasicTraverserSet.h"
#include "maelstrom/algorithms/unpack.h"
#include "maelstrom/algorithms/increment.h"

#include <tuple>

namespace gremlinxx {
    namespace traversal {

        std::vector<Traverser> BasicTraverserSet::toTraversers() {
            std::vector<Traverser> traversers(this->size());

            // Data
            maelstrom::vector current_data = maelstrom::as_host_vector(this->traverser_data);
            for(size_t t = 0; t < traversers.size(); ++t) {
                traversers[t].replace_data(current_data.get(t));
            }

            // Side Effects
            for(auto it = this->side_effects.begin(); it != this->side_effects.end(); ++it) {
                maelstrom::vector current_se = maelstrom::as_host_vector(it->second);
                for(size_t t = 0; t < traversers.size(); ++t) {
                    traversers[t].access_side_effects()[it->first] = current_se.get(t);
                }
            }

            maelstrom::vector current_path_lengths = maelstrom::as_host_vector(this->path_info.path_lengths);

            // Set the correct path length for each traverser.
            for(size_t t = 0; t < traversers.size(); ++t) {
                traversers[t].access_path().resize(
                    std::any_cast<path_length_t>(current_path_lengths.get(t))
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
                    auto& trv_path = trv.access_path();
                    
                    if(k < trv_path.size()) {
                        trv_path[trv_path.size() - k - 1] = current_path_vec.get(t);
                    }
                }
            }

            return traversers;
        }

        Traverser BasicTraverserSet::getTraverser(size_t i) {
            Traverser trv;
            
            // Data
            trv.replace_data(this->traverser_data.get(i));
            
            // Side Effects
            for(auto it = this->side_effects.begin(); it != side_effects.end(); ++it) {
                trv.access_side_effects()[it->first] = it->second.get(i);
            }

            // Paths
            if(!this->path_info.path_lengths.empty()) {
                trv.access_path().reserve(
                    std::any_cast<path_length_t>(this->path_info.path_lengths.get(i))
                );

                for(size_t k = 0; k < trv.access_path().size(); ++k) {
                    trv.access_path().insert(
                        trv.access_path().begin(), 
                        this->path_info.paths[this->path_info.paths.size() - k - 1].get(i)
                    );
                }
            }

            return trv;
        }

        std::any BasicTraverserSet::getData(size_t i) {
            return this->traverser_data.get(i);
        }

        void BasicTraverserSet::reinitialize(maelstrom::vector new_data, std::unordered_map<std::string, maelstrom::vector> side_effects, gremlinxx::traversal::PathInfo path_info) {
            this->traverser_data = std::move(new_data);
            this->side_effects = std::move(side_effects);
            this->path_info = std::move(path_info);
        }

        void BasicTraverserSet::resize(size_t new_size) {
            if(new_size > this->size()) throw std::runtime_error("New size of traverser set cannot exceed existing size!");

            this->traverser_data.resize(new_size);
            this->traverser_data.shrink_to_fit();

            for(auto& se : this->side_effects) {
                se.second.resize(new_size);
                se.second.shrink_to_fit();
            }

            for(auto& pe : this->path_info.paths) {
                pe.resize(new_size);
                pe.shrink_to_fit();
            }
            
            this->path_info.path_lengths.resize(new_size);
            this->path_info.path_lengths.shrink_to_fit();
        }

        void BasicTraverserSet::advance(std::function<std::pair<maelstrom::vector, maelstrom::vector>(maelstrom::vector&, std::unordered_map<std::string, maelstrom::vector>&, gremlinxx::traversal::PathInfo&)> func) {
            maelstrom::vector new_traverser_data;
            maelstrom::vector output_origin;

            // call function
            std::tie(
                new_traverser_data,
                output_origin
            ) = func(this->traverser_data, this->side_effects, this->path_info);

            // Update side effects, do nothing if output origin was not set (assume 1 to 1 transformation without reordering)
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

        std::vector<std::tuple<maelstrom::vector, std::unordered_map<std::string, maelstrom::vector>, gremlinxx::traversal::PathInfo>> BasicTraverserSet::unpack() {
            std::vector<maelstrom::vector> unpacked_data = maelstrom::unpack(this->traverser_data);
            
            std::unordered_map<std::string, std::vector<maelstrom::vector>> unpacked_side_effects;
            for(auto it = this->side_effects.begin(); it != this->side_effects.end(); ++it) {
                unpacked_side_effects[it->first] = maelstrom::unpack(it->second);
            }

            std::vector<gremlinxx::traversal::PathInfo> unpacked_path_info;
            if(this->persist_paths) {
                unpacked_path_info = this->path_info.unpack();
            } 

            std::vector<std::tuple<maelstrom::vector, std::unordered_map<std::string, maelstrom::vector>, gremlinxx::traversal::PathInfo>> unpacked_tuples;
            unpacked_tuples.reserve(unpacked_data.size());

            for(size_t k = 0; k < unpacked_data.size(); ++k) {
                std::unordered_map<std::string, maelstrom::vector> se_map;
                for(auto it = unpacked_side_effects.begin(); it != unpacked_side_effects.end(); ++it) {
                    se_map[it->first] = std::move(it->second[k]);
                }

                unpacked_tuples.push_back(
                    std::make_tuple(
                        std::move(unpacked_data[k]),
                        std::move(se_map),
                        this->persist_paths ? std::move(unpacked_path_info[k]) : gremlinxx::traversal::PathInfo()
                    )
                );
            }

            return unpacked_tuples;
        }

        void BasicTraverserSet::trim_paths(size_t ix_start, size_t ix_end) {
            // TODO figure out a clean way to do this without a host copy

            size_t current_max_path_length = this->path_info.paths.size();
            if(ix_start >= current_max_path_length) throw std::runtime_error("Start out of bounds!");
            if(ix_end > current_max_path_length) throw std::runtime_error("End out of bounds!");
            if(ix_end < ix_start) throw std::runtime_error("Start index must be <= end index!");

            if(ix_start == 0 && ix_end == current_max_path_length) return;
            
            // Now we need to figure out how much to subtract from the beginning.
            if(ix_start > 0) {
                std::cerr << "Warning: truncating paths from the left is not efficient. Consider an alternate approach if possible." << std::endl;
                auto host_lengths_vec = maelstrom::as_host_vector(this->path_info.path_lengths);
                size_t* host_lengths = static_cast<size_t*>(host_lengths_vec.data());
                for(size_t k = 0; k < host_lengths_vec.size(); ++k) {
                    if(host_lengths[k] >= current_max_path_length - 2) {
                        host_lengths[k] -= current_max_path_length - 2;
                    }
                }
                this->path_info.path_lengths = host_lengths_vec.to(this->path_info.path_lengths.get_mem_type());
            }

            // Increment corresponding to the part of the path truncated from the end.
            if(ix_end < current_max_path_length) {
                maelstrom::increment(
                    this->path_info.path_lengths,
                    static_cast<size_t>(current_max_path_length - ix_end)
                );
            }
            
            std::vector<maelstrom::vector> new_paths(
                this->path_info.paths.begin() + ix_start,
                this->path_info.paths.begin() + ix_end
            );
            this->path_info.paths = std::move(new_paths);
        }

        void BasicTraverserSet::set_side_effects(std::string se_key, maelstrom::vector values) {
            this->side_effects[se_key].clear();
            this->side_effects[se_key] = std::move(values);
        }

        void BasicTraverserSet::addTraversers(maelstrom::vector& other_traverser_data, std::unordered_map<std::string, maelstrom::vector>& other_side_effects, gremlinxx::traversal::PathInfo& other_paths) {
            // Add the traverser data
            if(this->traverser_data.empty()) {
                this->traverser_data = maelstrom::vector(other_traverser_data, false);
            } else {
                this->traverser_data.insert(this->traverser_data.size(), other_traverser_data);
            }

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

        void BasicTraverserSet::addTraversers(TraverserSet& other_traversers) {
            auto traverser_data = other_traversers.getTraverserData();
            auto side_effects = other_traversers.getSideEffects();
            auto paths = other_traversers.getPathInfo();
            return this->addTraversers(
                traverser_data,
                side_effects,
                paths
            );
        }

        void BasicTraverserSet::clear() {
            this->traverser_data.clear();
            this->side_effects.clear();
            this->path_info.clear();
        }

    }
}