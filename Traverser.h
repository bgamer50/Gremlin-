#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <list>
#include <map>
#include <stdlib.h>

template<typename T>
class Traverser {
	private:
		bool copy;
		T* my_data;
		std::list<void*> path;
		std::map<std::string, void*> side_effects;

	public:
		Traverser(T* addr) {
			my_data = addr;
			copy = false;
		}

		Traverser(T t) {
			my_data = malloc(sizeof(T));
			memcpy(my_data, &t, sizeof(T));
			copy = true;
		}

		//TODO write destructor

		virtual T* get() {
			return my_data;
		}
};

#endif