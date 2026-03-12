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

void Engine::run()
{
    std::ifstream itchFile(_itchFilename, std::ios::binary);
    auto buffer = std::make_unique<char[]>(BUFFER_SIZE);
    Printer printer;

    if (!itchFile)
    {
        throw std::runtime_error("Failed to open " + _itchFilename);
    }
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
            break;
        count = bytesRead + leftoversBytes;
        baseOffset = 0;
        while (true)
        {
            if (baseOffset + 2 > count)
            {
                leftoversBytes = count - baseOffset;
                std::memmove(buffer.get(), buffer.get() + baseOffset, leftoversBytes);
                break;
            }
            uint16_t bigEndianLength;
            std::memcpy(&bigEndianLength, buffer.get() + baseOffset, sizeof(bigEndianLength));
            std::size_t length = __builtin_bswap16(bigEndianLength);
            baseOffset += 2;
            if (baseOffset + length > count)
            {
                leftoversBytes = count - baseOffset + 2;
                std::memmove(buffer.get(), buffer.get() + baseOffset - 2, leftoversBytes);
                break;
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
    std::cout << "Unknown messages count: " << unknownCount << std::endl;
}