#ifndef FROM_TO_MODULATING_H
#define FROM_TO_MODULATING_H

class FromToModulating {
    public:
        virtual void modulate_from(boost::any arg) = 0;
        virtual void modulate_to(boost::any arg) = 0;
};

#endif