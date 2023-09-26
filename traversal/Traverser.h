#pragma once

#include <unordered_map>
#include <vector>
#include <string>
#include <any>

namespace gremlinxx {

	class Traverser {
		private:
			std::any my_data;
			std::vector<std::any> path;
			std::unordered_map<std::string, std::any> side_effects;

		public:
			Traverser(std::any t);

			Traverser(std::any t, std::unordered_map<std::string, std::any>& new_side_effects);

			Traverser();

			virtual std::any get();

			virtual void replace_data(std::any t);

			/**
			 * Returns a reference to this traverser's side effect map.
			 * **/
			virtual std::unordered_map<std::string, std::any>& access_side_effects();

			/*
				Returns a reference to this traverser's path info.
			*/
			virtual std::vector<std::any>& access_path();
	};

}