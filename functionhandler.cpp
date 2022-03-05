#include "functionhandler.h"

FunctionHandler::FunctionHandler()
{

}

FunctionHandler::FunctionHandler( Function objectFunction,
                                  std::vector<Function> gradFunction,int dim, std::string  functionStrView):
    objectFunction_(objectFunction),gradFunction_(gradFunction),dim_(dim),functionStrView_(functionStrView){}



const std::string &FunctionHandler::getFunctionStrView() const
{
    return functionStrView_;
}

void FunctionHandler::setFunctionStrView(const std::string &newFunctionStrView)
{
    functionStrView_ = newFunctionStrView;
}

const Function FunctionHandler::objectFunction() const
{
    return objectFunction_;
}

const std::vector<Function> FunctionHandler::gradFunction() const
{
    return gradFunction_;
}

void FunctionHandler::setObjectFunction(const Function &newObjectFunction)
{
    objectFunction_ = newObjectFunction;
}

void FunctionHandler::setGradFunction(const std::vector<Function> &newGradFunction)
{
    gradFunction_ = newGradFunction;
}

int FunctionHandler::dim() const
{
    return dim_;
}

void FunctionHandler::setDim(int newDim)
{
    dim_ = newDim;
}
