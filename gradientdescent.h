#ifndef GRADIENTDESCENT_H
#define GRADIENTDESCENT_H


#include <vector>
#include <functional>
#include <cmath>


using Function = std::function<double(std::vector<double> *)>;
using Point = std::vector<double>;


class GradientDescent {
public:
    GradientDescent();
    ~GradientDescent();
    void SetObjectFunc(const Function &  objectFunc);
    void SetGradFunc(const std::vector<Function>& gradFunc_);
    void SetStartPoint(const std::vector<double> startPoint);
    void SetStepSize(double stepSize);
    void SetMaxIterations(int maxIterations);
    void SetGradientThresh(double gradientThresh);
    bool Optimize(std::vector<double> * funcLoc, double *funcVal);


private:
    double ComputeGradient (int dim);
    double ComputeGradientAnalytical(int dim);
    std::vector<double> ComputeGradientVector();
    double ComputeGradientMagnitude(std::vector<double> gradientVector);

    std::vector<double> m_startPoint;
    std::vector<double> m_currentPoint;
    std::vector<Point> history_;

    int m_nDims;
    double m_stepSize;
    int m_maxIter;
    double m_h;
    double m_gradientThresh;

    Function objectFunc_;
    std::vector<Function> gradFunc_;

};


#endif // GRADIENTDESCENT_H
