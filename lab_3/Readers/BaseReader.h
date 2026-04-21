#pragma once

class BaseReader {
public:
    BaseReader() = default;
    virtual ~BaseReader() = 0;
};

inline BaseReader::~BaseReader() = default;

