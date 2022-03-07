#include "model.h"

Model::Model()
{

}

Point Model::functionLocation() const
{
    return functionLocation_;
}

void Model::setFunctionLocation(Point newFunctionLocation)
{
    functionLocation_ = newFunctionLocation;
}

double Model::functionValue() const
{
    return functionValue_;
}

void Model::setFunctionValue(double newFunctionValue)
{
    functionValue_ = newFunctionValue;
}

const std::vector<Point> &Model::history() const
{
    return history_;
}

void Model::setHistory(const std::vector<Point> &newHistory)
{
    history_ = newHistory;
}

const GradientDescent &Model::gd() const
{
    return gd_;
}

void Model::setFunctionHandler( FunctionHandler  newFunctionHandler)
{

    functionHandler_ = newFunctionHandler;
}

void Model::PrintResult()
{
        std::cout << "Function: " + functionHandler_.getFunctionStrView() << std::endl;
        std::cout << "Function start point: ";
        for (const auto & loc : startPoint_){
            std::cout << loc << " ";
        }
        std::cout << std::endl;
        std::cout << "Function location: ";
        for (const auto & funcLoc : functionLocation_){
            std::cout << funcLoc << " ";
        }
        std::cout << std::endl;
        std::cout << "Function value: " << functionValue_ << std::endl;

}

void Model::setAlpha(double newAlpha)
{
    alpha_ = newAlpha;
}

void Model::setGradientThreshHold(double newGradientThreshHold)
{
    gradientThreshHold_ = newGradientThreshHold;
}

void Model::setIterCount(int newIterCount)
{
    iterCount_ = newIterCount;
}

void Model::Run()
{
    gd_.InitFunctions(functionHandler_.objectFunction(),functionHandler_.gradFunction());
    gd_.Init(startPoint_,alpha_,
             iterCount_,gradientThreshHold_);
    gd_.setStoppingCriterion(this->stoppingCriterion_);
    gd_.Optimize(functionLocation_,functionValue_);
    PrintResult();
}

void Model::setStartPoint(Point newStartPoint)
{
    startPoint_ = newStartPoint;
}

const FunctionHandler &Model::functionHandler() const
{
    return functionHandler_;
}

void Model::setStoppingCriterion(StoppingCriterion newStoppingCriterion)
{
    stoppingCriterion_ = newStoppingCriterion;
}

