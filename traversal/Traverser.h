#pragma once

#include <list>
#include <map>
#include <vector>
#include <string.h>
#include <boost/any.hpp>

class Traverser {
	private:
		boost::any my_data;
		std::list<boost::any> path;
		std::map<std::string, boost::any> side_effects;

	public:
		Traverser(boost::any t);

		Traverser(boost::any t, std::map<std::string, boost::any>& new_side_effects);

		Traverser();

		virtual boost::any get();

		virtual Traverser replace_data(boost::any t);

		/**
		 * Returns a reference to this traverser's side effect map.
		 * **/
		virtual std::map<std::string, boost::any>& get_side_effects();
};

typedef std::vector<Traverser> TraverserSet;

