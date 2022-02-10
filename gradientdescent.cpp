#include "gradientdescent.h"


#include "GradientDescent.h"





GradientDescent::GradientDescent() {

    m_nDims = 0;
    m_stepSize = 0.0;
    m_maxIter = 1;
    m_h = 0.001;
    m_gradientThresh = 1e-09;
}

GradientDescent::~GradientDescent() {

}
void GradientDescent::SetObjectFunc(const Function & objectFunc){
    objectFunc_ = objectFunc;
}
void GradientDescent::SetStartPoint(const std::vector<double> startPoint) {
    m_startPoint = startPoint;
    m_nDims = m_startPoint.size();
}

void GradientDescent::SetStepSize(double stepSize) {
    m_stepSize = stepSize;
}

void GradientDescent::SetMaxIterations(int maxIterations) {
    m_maxIter = maxIterations;
}

void GradientDescent::SetGradientThresh(double gradientThresh) {
    m_gradientThresh = gradientThresh;
}

bool GradientDescent::Optimize(std::vector<double> * funcLoc, double *funcVal) {

    m_currentPoint = m_startPoint;
    int iterCount = 0;
    double gradientMagnitude = 1.0;

    while ((iterCount < m_maxIter) && (gradientMagnitude > m_gradientThresh)) {
        std::vector<double> gradientVector = ComputeGradientVector();
        gradientMagnitude = ComputeGradientMagnitude(gradientVector);

        std::vector<double> newPoint  = m_currentPoint;
        for (int i = 0; i < m_nDims; ++i) {
            newPoint[i]  += -(gradientVector[i] * m_stepSize);
        }
        history_.push_back(m_currentPoint);
        m_currentPoint = newPoint;
        iterCount++;
    }
   *funcLoc = m_currentPoint;
    *funcVal = objectFunc_(&m_currentPoint);


    return 0;
}

double GradientDescent::ComputeGradient(int dim) {
    std::vector<double> newPoint = m_currentPoint;
    newPoint[dim] += m_h;
    double functionVal_1 = objectFunc_(&m_currentPoint);
    double functionVal_2 = objectFunc_(&newPoint);

    return (functionVal_2 - functionVal_1) / m_h;

}
double GradientDescent::ComputeGradientAnalytical(int dim) {
    std::vector<double> newPoint = m_currentPoint;
    newPoint[dim] += m_h;
    return gradFunc_.at(dim)(&newPoint);

}

std::vector<double> GradientDescent::ComputeGradientVector() {
    std::vector<double> gradientVector = m_currentPoint;
    for (int i = 0; i < m_nDims; ++i){
        gradientVector[i] = ComputeGradientAnalytical(i);
    }

    return  gradientVector;
}

double GradientDescent::ComputeGradientMagnitude(std::vector<double> gradientVector) {
    double vectorMagnitude = 0.0;
    for (int i = 0; i < m_nDims; ++i) {
        vectorMagnitude += gradientVector[i] * gradientVector[i];
    }
    return sqrt(vectorMagnitude);

}

void GradientDescent::SetGradFunc(const std::vector<Function> & gradFunc) {
    gradFunc_ = gradFunc;

}

