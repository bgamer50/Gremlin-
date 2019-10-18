/*
    This header contains helper methods for comparisons of various property types.
    It is often used in conjunction with the min() and max() steps.
*/

#ifndef C_H
#define C_H

#include "inttypes.h"
#include <boost/any.hpp>
#include "traversal/Traverser.h"

template <typename T>
class C {
    public:
        static std::function<int(Traverser*, Traverser*)> compare() {
            return [](Traverser* t1, Traverser* t2) { return 1; };
        }
};

template <>
class C<uint64_t> {
    public:
        static std::function<int(Traverser*, Traverser*)> compare() {
            return [](Traverser* t1, Traverser* t2) {
                uint64_t u1 = boost::any_cast<uint64_t>(t1->get());
                uint64_t u2 = boost::any_cast<uint64_t>(t2->get());
                return u1 == u2 ? 0 : (u1 < u2 ? -1 : 1);
            };
        }
};

template <>
class C<std::string> {
    public:
        static std::function<int(Traverser*, Traverser*)> compare() {
            return [](Traverser* t1, Traverser* t2) {
                std::string s1 = boost::any_cast<std::string>(t1->get());
                std::string s2 = boost::any_cast<std::string>(t2->get());

                return s1.compare(s2);
            };
        }
};

#endif