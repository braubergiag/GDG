#ifndef MODEL_H
#define MODEL_H


#include "gradientdescent.h"
#include "functionhandler.h"
#include <iostream>
class Model
{
public:
    Model();

    FunctionHandler& functionHandler();
    Point getFunctionLocation() const;

    std::vector<Point> history() const;
    const GradientDescent &gd() const;
    double alpha() const;


    void setFunctionLocation(Point newFunctionLocation);
    void setHistory(const std::vector<Point> &newHistory);
    void setFunctionHandler(FunctionHandler newFunctionHandler);
    void setAlpha(double newAlpha);
    void setMagnitudeThreshHold(double newMagnitudeThreshHold);
    void setIterCount(int newIterCount);
    void setStartPoint(Point newStartPoint);
    void setStoppingCriterion(StoppingCriterion newStoppingCriterion);

    void PrintResult();


    void Run();







    bool isInitialized() const;

   double functionValue() const;

   int iterCount() const;

   StoppingCriterion stoppingCriterion() const;

   double magnitude() const;
   void setMagnitude(double newMagnitude);

   const std::string &getMagnitudeENotation() const;
   void setMagnitudeENotation(const std::string &newMagnitudeENotation);
   void setFunctionsLibrary();
   void setIsInitialized(bool newIsInitialized);

   const FunctionsLibrary &functionsLibrary() const;

private:
    GradientDescent gd_;
    FunctionHandler  functionHandler_;
    std::vector<Point> history_;
    StoppingCriterion stoppingCriterion_;
    std::string magnitudeENotation;
    Point startPoint_;
    Point functionLocation_;
    FunctionsLibrary functionsLibrary_;

    double functionValue_ {0};
    double magnitude_ {0};
    double alpha_{0};
    double magnitudeThreshHold_ {0};
    int iterCount_{0};

    bool isInitialized_;

};

#endif // MODEL_H
