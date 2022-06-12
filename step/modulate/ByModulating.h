#ifndef BY_MODULATING_H
#define BY_MODULATING_H

#include <boost/any.hpp>

class ByModulating {
    public:
        virtual void modulate_by(boost::any arg) = 0;
};

#endif