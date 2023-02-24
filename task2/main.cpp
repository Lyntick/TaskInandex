#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_set>





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
        return -1;
    }
    inFile.close();
    //solution

    std::unordered_set<char> setSymbols(buf.begin(), buf.end());
    const size_t sizeOfAlphabet = setSymbols.size();
    std::vector<int> vec(sizeOfAlphabet,0);

    auto iterSet = setSymbols.begin();
    for(int index = 0; iterSet != setSymbols.end(); ++index, ++iterSet){//todo think how where can be runtime error
        int tempK = k;
        char theSymbol = *iterSet;
        for(int l = 0, r = 0; r < buf.size(); ){
            while(r < buf.size()){
                if(theSymbol != buf[r]){
                    if(tempK == 0){
                        if(vec[index] < r - l){//save size of beautiful substr
                            vec[index] = r - l;
                        }
                        break;
                    }else{
                        --tempK;
                    }
                }
                ++r;
            }

            if(r == buf.size()){//except situation in the end of buf
                if(vec[index] < r - l){
                    vec[index] = r - l;
                }
                r++;
                break;
            }

            if(tempK == 0){
                if(theSymbol != buf[l]){
                    ++tempK;
                }
                ++l;
            }
        }
    }


    auto result = std::max_element(vec.begin(), vec.end());
//
    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        outFile << *result;
    }

    return 0;
}


//#include <iostream>
//#include <fstream>
//#include <vector>
//#include <algorithm>
//
//
//
//
//
//int main(){
//    std::ifstream inFile("input.txt");
//    std::string buf;
//    int k = 0;
//
//    buf.reserve(200000);
//    if (inFile.is_open()) {
//        inFile >> k;
//        inFile.get();
//        std::getline(inFile, buf);
//    }else{
//        return 0;
//    }
//    inFile.close();
//    //solution
//    const int sizeOfAlphabet = 26;
//    std::vector<int> vec(sizeOfAlphabet,0);
//
//    for(int index = 0; index < sizeOfAlphabet; ++index){
//        int tempK = k;
//        int theSymbol = 'a' + index;
//        for(int l = 0, r = 0; r < buf.size(); ){
//            while(r < buf.size()){
//                if(static_cast<char>(theSymbol) != buf[r]){
//                    if(tempK == 0){
//                        if(vec[theSymbol - 'a'] < r - l){//save size of beautiful substr
//                            vec[theSymbol - 'a'] = r - l;
//                        }
//                        break;
//                    }else{
//                        --tempK;
//                    }
//                }
//                ++r;
//            }
//
//            if(r == buf.size()){//except situation in the end of buf
//                if(vec[theSymbol - 'a'] < r - l){
//                    vec[theSymbol - 'a'] = r - l;
//                }
//                r++;
//                break;
//            }
//
//            if(tempK == 0){
//                if(static_cast<char>(theSymbol) != buf[l]){
//                    ++tempK;
//                }
//                ++l;
//            }
//        }
//    }
//
//
//    auto result = std::max_element(vec.begin(), vec.end());
////
//    std::ofstream outFile("output.txt");
//    if (outFile.is_open()) {
//        outFile << *result;
//    }
//
//    return 0;
//}