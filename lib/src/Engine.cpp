#include "Engine.hpp"

Engine::Engine(const std::string &configFilename)
{
    try
    {
        ConfigParser configParser(configFilename);
        Config config = configParser.parseConfig();
        _itchFilename = config.nasdaqHistoricalFilePath;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

std::size_t Engine::getMessageLength(std::unique_ptr<char[]> &buffer, std::size_t &baseOffset) const
{
    uint16_t bigEndianLength;

    std::memcpy(&bigEndianLength, buffer.get() + baseOffset, sizeof(bigEndianLength));
    std::size_t length = __builtin_bswap16(bigEndianLength);
    return length;
}

std::size_t Engine::processMessages(std::unique_ptr<char[]> &buffer, std::size_t count, std::size_t &unknownCount)
{
    std::size_t leftoversBytes = 0;
    std::size_t baseOffset = 0;
    Printer printer;

    while (true)
    {
        if (baseOffset + LENGTH_FIELD_SIZE > count)
        {
            leftoversBytes = count - baseOffset;
            std::memmove(buffer.get(), buffer.get() + baseOffset, leftoversBytes);
            return leftoversBytes;
        }
        std::size_t length = getMessageLength(buffer, baseOffset);
        baseOffset += LENGTH_FIELD_SIZE;
        if (baseOffset + length > count)
        {
            leftoversBytes = count - baseOffset + LENGTH_FIELD_SIZE;
            std::memmove(buffer.get(), buffer.get() + baseOffset - LENGTH_FIELD_SIZE, leftoversBytes);
            return leftoversBytes;
        }
        else
        {
            Itch::ParseResult result = Itch::parse(buffer.get() + baseOffset, length, printer);
            baseOffset += result.bytes;
            if (result.status == Itch::ParseStatus::UnknownMessageType)
                unknownCount++;
        }
    }
}

void Engine::processITCHFile(std::ifstream &itchFile)
{
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(BUFFER_SIZE);
    std::size_t leftoversBytes = 0;
    std::size_t bytesRead = 0;
    std::size_t count = 0;
    std::size_t baseOffset = 0;
    std::size_t unknownCount = 0;

    while (true)
    {
        itchFile.read(buffer.get() + leftoversBytes, BUFFER_SIZE - leftoversBytes);
        bytesRead = itchFile.gcount();
        if (bytesRead == 0)
        {
            break;
        }
        count = bytesRead + leftoversBytes;
        baseOffset = 0;
        leftoversBytes = processMessages(buffer, count, unknownCount);
    }
    std::cout << "Unknown messages count: " << unknownCount << std::endl;
}

void Engine::run()
{
    std::ifstream itchFile(_itchFilename, std::ios::binary);

    if (!itchFile)
    {
        throw std::runtime_error("Failed to open " + _itchFilename);
    }
    processITCHFile(itchFile);
}