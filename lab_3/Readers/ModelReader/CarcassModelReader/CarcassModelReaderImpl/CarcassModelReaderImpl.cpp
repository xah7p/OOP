#include "CarcassModelReaderImpl.h"
#include "ModelException.h"

BaseCarcassModelReaderImpl::BaseCarcassModelReaderImpl(const std::string& path):
    file(path, std::ios::binary)
{
    if (!file.is_open())
        throw ModelInvalidFileFormat("Failed to open model file.");
}
