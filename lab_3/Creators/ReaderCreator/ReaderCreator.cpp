#include "ReaderCreator.h"

#include "CarcassModelReader.h"
#include "TxtCarcassModelReaderImpl.h"
#include "ObjCarcassModelReaderImpl.h"
#include "BinCarcassModelReaderImpl.h"
#include "DefaultCameraReader.h"
#include "TxtDefaultCameraReaderImpl.h"
#include "ObjDefaultCameraReaderImpl.h"
#include "BinDefaultCameraReaderImpl.h"

std::unique_ptr<BaseReader> TxtCarcassModelReaderCreator::create(const std::string& path) const
{
    return std::make_unique<CarcassModelReader>(std::make_shared<TxtCarcassModelReaderImpl>(path));
}

std::unique_ptr<BaseReader> ObjCarcassModelReaderCreator::create(const std::string& path) const
{
    return std::make_unique<CarcassModelReader>(std::make_shared<ObjCarcassModelReaderImpl>(path));
}

std::unique_ptr<BaseReader> BinCarcassModelReaderCreator::create(const std::string& path) const
{
    return std::make_unique<CarcassModelReader>(std::make_shared<BinCarcassModelReaderImpl>(path));
}

std::unique_ptr<BaseReader> TxtDefaultCameraReaderCreator::create(const std::string& path) const
{
    return std::make_unique<DefaultCameraReader>(std::make_shared<TxtDefaultCameraReaderImpl>(path));
}

std::unique_ptr<BaseReader> ObjDefaultCameraReaderCreator::create(const std::string& path) const
{
    return std::make_unique<DefaultCameraReader>(std::make_shared<ObjDefaultCameraReaderImpl>(path));
}

std::unique_ptr<BaseReader> BinDefaultCameraReaderCreator::create(const std::string& path) const
{
    return std::make_unique<DefaultCameraReader>(std::make_shared<BinDefaultCameraReaderImpl>(path));
}
