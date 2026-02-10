#include "FeedHandler.hpp"

FeedHandler::FeedHandler(const std::string &itchFilename) : _itchFilename(itchFilename)
{
}

void FeedHandler::replayItchFile()
{
    std::ifstream itchFile(_itchFilename, std::ios::binary);
    char *buffer = new char[BUFFER_SIZE];
    std::size_t leftoversBytes = 0;
    std::size_t baseOffset = 0;

    if (!itchFile)
    {
        throw std::runtime_error("Failed to open " + _itchFilename);
    }
    while (itchFile)
    {
        itchFile.read(buffer, BUFFER_SIZE);
        std::size_t count = itchFile.gcount();
        if (!count)
        {
            break;
        }
    }
    delete[] buffer;
}