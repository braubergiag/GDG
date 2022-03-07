#ifndef MODEL_H
#define MODEL_H


#include "gradientdescent.h"
#include "functionhandler.h"
#include <iostream>
class Model
{
public:
    Model();

    Point functionLocation() const;
    void setFunctionLocation(Point newFunctionLocation);

    double functionValue() const;
    void setFunctionValue(double newFunctionValue);

    const std::vector<Point> &history() const;
    void setHistory(const std::vector<Point> &newHistory);

    const GradientDescent &gd() const;

    void setFunctionHandler(FunctionHandler newFunctionHandler);
    void PrintResult();


    double alpha() const;

    void setAlpha(double newAlpha);

    void setGradientThreshHold(double newGradientThreshHold);

    void setIterCount(int newIterCount);
    void Run();

    void setStartPoint(Point newStartPoint);



    const FunctionHandler &functionHandler() const;

    void setStoppingCriterion(StoppingCriterion newStoppingCriterion);

private:
    GradientDescent gd_;
    FunctionHandler  functionHandler_;
    std::vector<Point> history_;
    StoppingCriterion stoppingCriterion_;
    Point startPoint_;
    Point functionLocation_;

    double functionValue_ = 0;
    double alpha_ = 0;
    double gradientThreshHold_ = 0;
    int iterCount_ = 0;

};

#endif // MODEL_H
