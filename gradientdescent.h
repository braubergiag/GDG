#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H


#include <vector>
#include <functional>
#include <cmath>
#include <iostream>
#include <utility>
#include <map>


using Function = std::function<double(const std::vector<double> &)>;
using Point = std::vector<double>;

enum class StoppingCriterion {
    byGradientMagnitude,
    byDeltaChangeMagnitude,
    byValueChangeMagnitude
};





class GradientDescent {
public:
    GradientDescent();
    ~GradientDescent();
    void InitFunctions(const Function &  objectFunc,const std::vector<Function>& gradFunc);
    void Init(const Point& startPoint, double stepSize, uint maxIterations,double gradientThresh);
    bool Optimize(std::vector<double> & funcLoc, double & funcVal);


    // Setters
    void setStoppingCriterion(StoppingCriterion newStoppingCriterion);

    // Getters
    const std::vector<Point> &history() const;

    const std::vector<std::vector<double> > &historyByCoord() const;

    const std::vector<double> &functionValuesHistory() const;

private:
    double ComputeGradient (int dim);
    double ComputeGradientAnalytical(int dim);
    std::vector<double> ComputeGradientVector();
    // Stopping Critereis functions
    double ComputeGradientMagnitude();
    double ComputeDeltaChangeMagnitude();
    double ComputeValueChangeMagnitude();



    int nDims_;
    double alpha_;
    int maxIter_;
    double h_;
    double eps_;
    double stoppingMagnitude_ = 1.0;



    StoppingCriterion stoppingCriterion_;
    Point startPoint_,currentPoint_, prevPoint_;
    std::vector<Point> history_;
    std::vector<std::vector<double>> historyByCoord_;
    std::vector<double> functionValuesHistory_;
    std::vector<double> gradientVector_;
    Function objectFunc_;
    std::vector<Function> gradFunc_;

};


#endif // GRADIENTDESCENT_H
