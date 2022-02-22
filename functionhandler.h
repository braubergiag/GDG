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
    FunctionHandler(const Function & objectFunction,
                    const std::vector<Function> & gradFunction,const std::string & functionStrView = "");

    const std::string &getFunctionStrView() const;
    void setFunctionStrView(const std::string &newFunctionStrView);

private:

    Function objectFunction_;
    std::vector<Function> gradFunction_;
    std::string functionStrView_;


};

using FunctionsLibrary = std::map<std::string, FunctionHandler>;



#endif // FUNCTIONHANDLER_H
