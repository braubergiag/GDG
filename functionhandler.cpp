#include "functionhandler.h"

FunctionHandler::FunctionHandler()
{

}

const std::string &FunctionHandler::getFunctionStrView() const
{
    return functionStrView;
}

void FunctionHandler::setFunctionStrView(const std::string &newFunctionStrView)
{
    functionStrView = newFunctionStrView;
}
