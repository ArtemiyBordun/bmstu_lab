#ifndef FACADEOPERATIONRESULT_H
#define FACADEOPERATIONRESULT_H
#include "string"

using namespace std;

class FacadeOperationResult {
private:
    string _errorMessage;
    bool _isSuccess;
public:
    FacadeOperationResult() = default;
    string getErrorMessage();
    void setErrorMessage(string error);
    bool isSuccess();
};

#endif // FACADEOPERATIONRESULT_H
