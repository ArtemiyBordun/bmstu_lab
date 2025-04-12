#include "facadeoperationresult.h"

void FacadeOperationResult::setErrorMessage(string error)
{
    _errorMessage = error;
}

string FacadeOperationResult::getErrorMessage()
{
    return _errorMessage;
}

bool FacadeOperationResult::isSuccess()
{
    return _errorMessage == "";
}
