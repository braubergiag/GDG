#include "functionhandler.h"

FunctionHandler::FunctionHandler()
{

}

FunctionHandler::FunctionHandler(const Function &objectFunction,
                                 const std::vector<Function> &gradFunction,const std::string & functionStrView):
    objectFunction_(objectFunction),gradFunction_(gradFunction),functionStrView_(functionStrView){}

const std::string &FunctionHandler::getFunctionStrView() const
{
    return functionStrView_;
}

void FunctionHandler::setFunctionStrView(const std::string &newFunctionStrView)
{
    functionStrView_ = newFunctionStrView;
}
