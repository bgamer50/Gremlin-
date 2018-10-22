#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <list>
#include <map>
#include <string.h>

template<typename T>
class Traverser {
	private:
		T* my_data;
		std::list<void*> path;
		std::map<std::string, void*> side_effects;

	public:
		Traverser(T t) {
			my_data = (T*)malloc(sizeof(T));
			memcpy(my_data, &t, sizeof(T));
		}

		virtual T* get() {
			return my_data;
		}

		virtual void replace_data(T t) {
			memcpy(my_data, &t, sizeof(T));
		}
};

#endif