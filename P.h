#ifndef P_PREDICATE_H
#define P_PREDICATE_H

#include <string>
#include <iostream>
#include <boost/any.hpp>
#include <stdlib.h>
#include <functional>

/**
    Equivalent of P in Java-Gremlin.
**/
template<typename T>
class P {
	public:
		static std::function<bool(boost::any)> eq(T b) {
			std::cout << "wrong method!\n";
			return [b](boost::any a) {
				return false;
			};
		}
};

template<>
class P<uint64_t> {
	public:
		static std::function<bool(boost::any)> eq(uint64_t b) {
			return [b](boost::any a) {
				std::cout << "wrong method!\n";	
				return boost::any_cast<uint64_t>(a) == b;
			};
		}
};

template<>
class P<int64_t> {
	public:
		static std::function<bool(boost::any)> eq(uint64_t b) {
			return [b](boost::any a) {
				std::cout << "wrong method!\n";
				return boost::any_cast<int64_t>(a) == b;
			};
		}
};

template<>
class P<double> {
	public:
		static std::function<bool(boost::any)> eq(double b) {
			return [b](boost::any a) {
				std::cout << "wrong method!\n";
				return boost::any_cast<double>(a) == b;
			};
		}
};

template<>
class P<std::string> {
	public:
		static std::function<bool(boost::any)> eq(std::string b) {
			std::cout << "original value of b: " << b << "\n";
			return [b](boost::any a) {
				std::cout << "correct method!\n";
				return boost::any_cast<std::string>(a).compare(b) == 0;
			};
		}
};

template<>
class P<char*> {
	public:
		static std::function<bool(boost::any)> eq(char* b) {
			return [b](boost::any a) {
				std::cout << "wrong method!\n";
				std::string a_str = boost::any_cast<std::string>(a);
				return strncmp(a_str.c_str(), b, a_str.length()) == 0;
			};
		}
};

#endif
