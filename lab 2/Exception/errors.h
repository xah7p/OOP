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

class InvalidCapacityError:  public BaseError {
public:
    InvalidCapacityError(string filename, string classname, 
        int line, string time, string info = "Expired size pointer!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class InvalidIteratorIndex:  public BaseError {
public:
    InvalidIteratorIndex(string filename, string classname, 
        int line, string time, string info = "Invalid iterator index!\n")
        : BaseError(filename, classname, line, time, info) {};
};

class ComparingDifferentIterators:  public BaseError {
public:
    ComparingDifferentIterators(string filename, string classname, 
        int line, string time, string info = "comparing two different iterators!\n")
        : BaseError(filename, classname, line, time, info) {};
};
