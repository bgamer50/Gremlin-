#ifndef PROPERTY_H
#define PROPERTY_H

class Property {
	private:
		std::string my_key;
		void* my_value;

	public:
		Property(std::string new_key, void* new_value);
		virtual std::string key();
		virtual void* value();
};

class VertexProperty : public Property {
	public:
		VertexProperty(std::string new_key, void* new_value);
		// TODO VertexProperty(std::string new_key, void* new_value, ...);
		virtual std::vector<std::string> keys();
		virtual std::vector<void*> values();
		virtual st
}

#endif