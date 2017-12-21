/*
 * System.cpp
 *
 *  Created on: Sep 28, 2016
 *      Author: ivp
 */

#include "System.h"

using namespace std;

namespace tmx {
namespace utils {

std::string System::ExecCommand(const std::string& command)
{
    std::string result;

    FILE* pipe{popen(command.c_str(), "r")};
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr)
    {
        result += buffer;
    }

    pclose(pipe);

    // Trim the last line
    result = result.substr(0, result.size() - 1);
    return result;
}

} /* namespace utils */
} /* namespace tmx */
