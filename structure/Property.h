#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

class Property {
	private:
		std::string my_key;
		boost::any my_value;

	public:		
		Property(std::string new_key, boost::any new_value) {
			this->my_key = new_key;
			this->my_value = new_value;
		}

		std::string key() {
			return this->my_key;
		}

		boost::any value() {
			return this->my_value;
		}
};

#endif