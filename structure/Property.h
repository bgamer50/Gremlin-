#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

template<typename T>
class Property {
	public:		
		std::string key();

		T value();
};

#endif