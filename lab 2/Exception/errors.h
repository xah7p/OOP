#pragma once

#include "base_error.h"

class MemoryError: public BaseError {
public:
    MemoryError(string filename, string classname, 
        int line, string time, string info = "Failed memory allocation!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class DeletedObjectError:  public BaseError {
public:
    DeletedObjectError(string filename, string classname, 
        int line, string time, string info = "Deleted object!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class InvalidCPointerError:  public BaseError {
public:
    InvalidCPointerError(string filename, string classname, 
        int line, string time, string info = "Invalid C pointer t!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class InvalidSizeError:  public BaseError {
public:
    InvalidSizeError(string filename, string classname, 
        int line, string time, string info = "Invalid size!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class InvalidCapacityError:  public BaseError {
public:
    InvalidCapacityError(string filename, string classname, 
        int line, string time, string info = "Invalid capacity!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class InvalidIteratorIndexError:  public BaseError {
public:
    InvalidIteratorIndexError(string filename, string classname, 
        int line, string time, string info = "Invalid iterator index!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class ComparingDifferentIteratorsError:  public BaseError {
public:
    ComparingDifferentIteratorsError(string filename, string classname, 
        int line, string time, string info = "comparing two different iterators!\n")
        : BaseError(filename, classname, line, time, info) {};
};
