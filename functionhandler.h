#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H


#include <vector>
#include <functional>
#include <map>
using Function = std::function<double(const std::vector<double> &)>;
using Point = std::vector<double>;

class FunctionHandler
{
public:
    FunctionHandler();
    FunctionHandler(const Function objectFunction,
                    const std::vector<Function>  gradFunction,int dim=1,const std::string functionStrView = "");

    const std::string &getFunctionStrView() const;
    void setFunctionStrView(const std::string &newFunctionStrView);

    const Function objectFunction() const;

    const std::vector<Function> gradFunction() const;

    void setObjectFunction(const Function &newObjectFunction);

    void setGradFunction(const std::vector<Function> &newGradFunction);

    int dim() const;
    void setDim(int newDim);

private:

    Function objectFunction_;
    std::vector<Function> gradFunction_;
    int dim_ = 0;
    std::string functionStrView_;




};

using FunctionsLibrary = std::map<std::string, FunctionHandler>;



#endif // FUNCTIONHANDLER_H
