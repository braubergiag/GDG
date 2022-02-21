#ifndef FUNCTIONHANDLER_H
#define FUNCTIONHANDLER_H

using Function = std::function<double(const std::vector<double> &)>;
using Point = std::vector<double>;


class FunctionHandler
{
public:
    FunctionHandler();

    const std::string &getFunctionStrView() const;
    void setFunctionStrView(const std::string &newFunctionStrView);

private:

    Function objectFunction_;
    vector<Function> gradFunction_;
    std::string functionStrView;


};

#endif // FUNCTIONHANDLER_H
