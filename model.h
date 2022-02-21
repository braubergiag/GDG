#ifndef MODEL_H
#define MODEL_H


#include "gradientdescent.h"

class Model
{
public:
    Model();

private:
    GradientDescent gd_;
    std::vector<Point> history_;
};

#endif // MODEL_H
