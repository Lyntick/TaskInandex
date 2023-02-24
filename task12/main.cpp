#include <iostream>
#include <fstream>
#include <unordered_map>
#include <algorithm>





int main(){
    std::ifstream inFile("input.txt");
    std::string buf;
    int k = 0;

    buf.reserve(200000);
    if (inFile.is_open()) {
        inFile >> k;
        inFile.get();
        std::getline(inFile, buf);
    }else{
        return 0;
    }
    inFile.close();
    //solution
    std::unordered_map<char, int> unorderedMap;
    unorderedMap.reserve(23);
    int counter = k;
    char preChar = buf[0];
    int indexToStart = -1;
    int sizeOfsymbols = 1;
    for(int i = 0; i <= buf.size(); ++i){


        if(i == buf.size() || preChar != buf[i]){
            if(indexToStart == -1){
                indexToStart = i;
            }
            if(counter == 0){
                auto iterMap = unorderedMap.find(preChar);
                if(iterMap == unorderedMap.end()){
                    unorderedMap.insert({buf[i], sizeOfsymbols});
                }else{
                    if(iterMap->second < sizeOfsymbols){
                        iterMap->second = sizeOfsymbols;
                    }
                }
                sizeOfsymbols = 1;
                counter = k;
                preChar = buf[indexToStart];
                i = indexToStart;
                indexToStart = -1;
            }else{
                --counter;
                sizeOfsymbols++;

            }
        }else{
            auto iterMap = unorderedMap.find(buf[i]);
            if(iterMap == unorderedMap.end()){
                unorderedMap.insert({buf[i], 1});
            }else{
                sizeOfsymbols++;
            }
        }

    }

    auto result = std::max_element(unorderedMap.begin(), unorderedMap.end(),
                                   [](const auto el1, const auto el2){
        return el1.second < el2.second;
    });
//
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        outFile << result->second;
    }

    return 0;
}