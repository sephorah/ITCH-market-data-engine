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

static constexpr std::size_t BUFFER_SIZE = 64 * 1024;

class Engine
{
public:
    explicit Engine(const std::string &configFilename);
    void run();

private:
    std::string _itchFilename;
};

#endif /* !ENGINE_HPP_ */