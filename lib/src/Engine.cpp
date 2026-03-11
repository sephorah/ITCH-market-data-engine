#include "Engine.hpp"

Engine::Engine(const std::string &configFilename)
{
    try
    {
        ConfigParser configParser(configFilename);
        Config config = configParser.parseConfig();

        // std::cout << "CONFIG" << std::endl;
        // std::cout << config.replaySpeed << std::endl
        //           << config.nasdaqHistoricalFilePath << std::endl;
        // for (const auto &[key, value] : config.instruments)
        // {
        //     std::cout << key << " " << value.symbol << " " << value.specs.depth << " " << value.specs.enabled << " " << std::endl;
        // }
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
    char *buffer = new char[BUFFER_SIZE];
    std::size_t leftoversBytes = 0;

    if (!itchFile)
    {
        throw std::runtime_error("Failed to open " + _itchFilename);
    }
    while (itchFile)
    {
        itchFile.read(buffer, BUFFER_SIZE);
        std::size_t count = itchFile.gcount();

        std::size_t baseOffset = leftoversBytes;

        while (baseOffset < count)
        {
            std::size_t length = count - baseOffset;
            Itch::ParseResult result = Itch::parse(buffer + baseOffset, length, Printer());

            if (result.status == Itch::ParseStatus::Truncated)
            {
                memmove(buffer, buffer + baseOffset, result.bytes);
                leftoversBytes = result.bytes;
                break;
            }
            else
            {
                baseOffset += result.bytes;
            }

            // count = 39;

            // offset = 0;
            // length = count - offset = 39;
            // "|oooooooooooooooooooooooooooooooooooooo";

            // message length => 5

            // offset += result.bytes = 0 + 5 = 5;
            // length = count - offset = 34;
            // "ooooo|ooooooooooooooooooooooooooooooooo";

            // message length => 17;

            // offset += result.bytes = 5 + 17 = 22;
            // length = count - offset = 39 - 22 = 17;
            // "oooooooooooooooooooooo|oooooooooooooooo";

            // message length => 17;

            // offset += result.bytes = 22 + 17 = 39;
            // length = count - offset = 39 - 39 = 0;
            // "oooooooooooooooooooooooooooooooooooooo|";

            // if result.status == truncated => quit loop, leftoverBytes = result.bytes;
            //  new loop with baseOffset = leftoverBytes;
        }

        // std::size_t baseOffset = 0;

        // std::size_t i = 0;

        // // while (buffer[i] != '\0') {
        // //     auto status = Itch::parse(buffer + baseOffset, )

        // // }

        // // for (size_t i = 0; buffer[i] != '\0'; ++i) {
        // //     auto status = Itch::parse(buffer)
        // // }

        // // auto status = Itch::parse(msg, sizeof msg, Printer());
        // if (!count)
        // {
        //     break;
        // }
    }
    delete[] buffer;
}