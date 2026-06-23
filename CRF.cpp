#include "CRF.h"

#include <openssl/sha.h>

#include <iomanip>
#include <sstream>

CRF::CRF(int size)
{
    outputSize = size;
}

std::string CRF::sha256(const std::string& input)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];

    SHA256(reinterpret_cast<const unsigned char*>(input.c_str()),input.size(),hash);

    std::stringstream ss;

    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex
           << std::setw(2)
           << std::setfill('0')
           << static_cast<int>(hash[i]);
    }

    return ss.str();
}

std::string CRF::Fn(const std::string& s)
{
    std::string hash = sha256(s);

    return hash.substr(0,outputSize);
}