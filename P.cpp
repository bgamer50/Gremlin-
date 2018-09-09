#include "P.h"
#include <string>

template <typename T>
inline P<T>* eq(T t) { return new P<T>(EQ, t, t); }