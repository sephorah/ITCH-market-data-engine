#ifndef FEEDHANDLER_HPP_
#define FEEDHANDLER_HPP_

#include <string>
#include <fstream>

#define BUFFER_SIZE (64 * 1024)

class FeedHandler
{
public:
    explicit FeedHandler(const std::string &itchFilename);
    void replayItchFile();

private:
    std::string _itchFilename;
};

#endif /* !FEEDHANDLER_HPP_ */