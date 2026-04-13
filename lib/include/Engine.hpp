#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ConfigParser.hpp"
#include "ItchParser.hpp"
#include "Printer.hpp"

constexpr std::size_t BUFFER_SIZE = 64 * 1024;
constexpr std::size_t LENGTH_FIELD_SIZE = 2;

class Engine
{
public:
    explicit Engine(const std::string &configFilename);
    void run();
    std::size_t processMessages(std::unique_ptr<char[]> &buffer, std::size_t count, std::size_t &unknownCount);
    std::size_t getMessageLength(std::unique_ptr<char[]> &buffer, std::size_t &baseOffset) const;
    void processITCHFile(std::ifstream &itchFile);

private:
    std::string _itchFilename;
};

#endif /* !ENGINE_HPP_ */