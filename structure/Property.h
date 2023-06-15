#pragma once

#include <string>
#include <boost/any.hpp>

namespace gremlinxx {

	/*
		Deprecated
	*/
	class Property {
		private:
			std::string my_key;
			boost::any my_value;

		public:		
			Property(std::string new_key, boost::any new_value) {
				this->my_key = new_key;
				this->my_value = new_value;
			}

			virtual std::string key() {
				return this->my_key;
			}

			virtual boost::any value() {
				return this->my_value;
			}
	};

}