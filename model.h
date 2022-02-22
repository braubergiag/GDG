#ifndef MODEL_H
#define MODEL_H


#include "gradientdescent.h"
#include "functionhandler.h"
class Model
{
public:
    Model();

private:
    GradientDescent gd_;
    FunctionHandler functionHandler_;
    std::vector<Point> history_;
};

#endif // MODEL_H
