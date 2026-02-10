#ifndef SIMULATOR_HPP_
#define SIMULATOR_HPP_

#include <string>
#include <fstream>
#include <iostream>
#define BUFFER_SIZE (64 * 1024)

class Simulator
{
public:
    explicit Simulator(const std::string &itchFilename);
    void run();

private:
    std::string _itchFilename;
    
};

#endif /* !SIMULATOR_HPP_ */