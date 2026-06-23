#ifndef CRF_H
#define CRF_H

#include <string>

class CRF {
private:
    int outputSize;

public:
    explicit CRF(int size);

    std::string Fn(const std::string& s);

private:
    std::string sha256(const std::string& input);
};

#endif