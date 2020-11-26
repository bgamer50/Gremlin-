#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <list>
#include <map>
#include <string.h>
#include <boost/any.hpp>

class Traverser {
	private:
		boost::any my_data;
		std::list<boost::any> path;
		std::map<std::string, boost::any> side_effects;

	public:
		Traverser(boost::any t) {
			my_data = boost::any(t);
		}

		Traverser(boost::any t, std::map<std::string, boost::any>& new_side_effects) {
			my_data = boost::any(t);
			this->side_effects = new_side_effects;
		}

		Traverser() : Traverser(boost::any()){}

		virtual boost::any get() {
			return my_data;
		}

		virtual Traverser replace_data(boost::any t) {
			my_data = t;
			return *this;
		}

		/**
		 * Returns a reference to this traverser's side effect map.
		 * **/
		virtual std::map<std::string, boost::any>& get_side_effects() {
			return this->side_effects;
		}
};

typedef std::vector<Traverser> TraverserSet;

#endif