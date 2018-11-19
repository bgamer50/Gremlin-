#ifndef ELEMENT_H
#define ELEMENT_H

class Element {
	virtual void const* id() = 0;
	virtual std::string const* label() = 0;
};

#endif