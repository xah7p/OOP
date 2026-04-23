#pragma once

#include "base_error.h"

BaseError::BaseError(string filename, string classname, int line, string time, string info) {
    errorMsg = "[TIME]:" + time + 
                "\n[FILE_NAME]:" + filename + 
                "\n[LINE]:" + std::to_string(line) + 
                "\n[CLASS_NAME]:" + classname +
                "\n[INFO]:" + info + "\n";
}
