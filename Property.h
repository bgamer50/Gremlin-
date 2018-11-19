#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>

template<typename T>
class Property {
	public:		
		virtual std::string key() = 0;

		virtual T value() = 0;
};

#endif