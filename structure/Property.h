#pragma once

#include <string>
#include <any>

namespace gremlinxx {

	/*
		Deprecated
	*/
	class Property {
		private:
			std::string my_key;
			std::any my_value;

		public:		
			Property(std::string new_key, std::any new_value) {
				this->my_key = new_key;
				this->my_value = new_value;
			}

			virtual std::string key() {
				return this->my_key;
			}

			virtual std::any value() {
				return this->my_value;
			}
	};

}