#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <chrono>

void readFile(std::ifstream& inFile, std::time_t& tSend) {
    std::string buf;
    if (inFile.is_open()) {
        char tempChar = inFile.get();
        while(tempChar != '\n')
        {
            buf += tempChar;
            tempChar = inFile.get();
        }
        std::tm tm;
        tm.tm_mday = 1;
        tm.tm_mon =0;
        tm.tm_year = 2000;
        tm.tm_isdst = -1;
        strptime(buf.c_str(), "%H:%M:%S", &tm);
        tSend = mktime(&tm);
    }
}




int main() {
    std::ifstream inFile("input.txt");
    std::time_t tSend{},tAccept{}, tServer{};
    readFile(inFile,tSend);
    readFile(inFile,tServer);
    readFile(inFile,tAccept);
    using namespace std::chrono_literals;
    auto tpSend = std::chrono::system_clock::from_time_t(tSend);
    auto tpServer = std::chrono::high_resolution_clock::from_time_t(tServer);
    auto tpAccept = std::chrono::high_resolution_clock::from_time_t(tAccept);
    //todo think - there is problem with system_clock, why time displays not correct
    auto resultTime = std::chrono::time_point<std::chrono::high_resolution_clock>(tpServer.time_since_epoch() + (tpAccept.time_since_epoch() - tpSend.time_since_epoch()) / 2);
    auto res =std::chrono::high_resolution_clock::to_time_t(resultTime);
    const size_t sizeBuf = 8;
    std::string buf(sizeBuf,'.');
    std::string_view format = "%T";
    std::strftime(buf.data(), sizeBuf, format.data(), std::localtime(&res));

    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        outFile << buf << '\n';
    }

    return 0;
}