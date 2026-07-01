#pragma once

#include <exception>
#include <string>

using string = std::string;

class BaseError : public std::exception {
public:
    BaseError(string filename, string classname, int line, string time, string info = "Error!\n");

    virtual const char* what() const noexcept override {
        return errorMsg.c_str();
    }

    virtual ~BaseError() {};

protected:
    string errorMsg;
};

#include "base_error.hpp"
