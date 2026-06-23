#ifndef MISSINGTRANSACTIONEXCEPTION_H
#define MISSINGTRANSACTIONEXCEPTION_H

#include <exception>

class MissingTransactionException
    : public std::exception
{
public:

    const char* what() const noexcept override
    {
        return
        "Required transaction missing from blockchain!";
    }
};

#endif