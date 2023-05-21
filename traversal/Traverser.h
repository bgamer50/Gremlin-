#pragma once

#include <unordered_map>
#include <vector>
#include <string.h>
#include <boost/any.hpp>

namespace gremlinxx {

	class Traverser {
		private:
			boost::any my_data;
			std::vector<boost::any> path;
			std::unordered_map<std::string, boost::any> side_effects;

		public:
			Traverser(boost::any t);

			Traverser(boost::any t, std::unordered_map<std::string, boost::any>& new_side_effects);

			Traverser();

			virtual boost::any get();

			virtual void replace_data(boost::any t);

			/**
			 * Returns a reference to this traverser's side effect map.
			 * **/
			virtual std::unordered_map<std::string, boost::any>& access_side_effects();

			/*
				Returns a reference to this traverser's path info.
			*/
			virtual std::vector<boost::any>& access_path();
	};

}