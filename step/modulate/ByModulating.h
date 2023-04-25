#pragma once

#include <boost/any.hpp>

class ByModulating {
    public:
        virtual void modulate_by(boost::any arg) = 0;
};

