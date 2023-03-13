#include <iostream>
#include <fstream>
#include <algorithm>


bool isEven(std::uint64_t temp){
    return !(temp & 1);
}

int main(){

    std::ifstream inFile("input.txt");
    std::uint64_t people;
    std::uint64_t variants;
    int vasiaRow = -1;
    int vasiaPlace = -1;

    if (inFile.is_open()) {
        inFile >> people;
        inFile.get();//skip '\n'
        inFile >> variants;
        inFile.get();//skip '\n'
        inFile >> vasiaRow;
        inFile.get();//skip '\n'
        inFile >> vasiaPlace;
    }else{
        return -1;
    }
    inFile.close();
//solution
    auto outToFile = [](std::ostream& outFile ,std::uint64_t temp){//number of seat place
        if(temp % 2 == 1){
            outFile << (temp + 1) / 2 << ' ' << 1;
        }else{
            outFile <<  temp / 2 << ' ' << 2;
        }
    };

    bool isExistPlace = false;
    int placePetia = -1;
    std::uint64_t theNumberVasia = 0;
    if(variants != people){
        theNumberVasia = (vasiaRow-1)*2 + vasiaPlace;
        if(variants  < theNumberVasia || theNumberVasia <= people - variants){
            isExistPlace = true;
            int vasiaVariant = theNumberVasia % variants == 0 ? variants : theNumberVasia % variants;

            auto findDistanceBetweenFriends = [&vasiaRow]( int petiaPlace) -> size_t{
                int petiaRow = (petiaPlace - (isEven(petiaPlace) ? 2: 1)) / 2 + 1;
                return vasiaRow < petiaRow ? petiaRow - vasiaRow: vasiaRow - petiaRow;
            };
            size_t tempDistance = -1;
            for(int place = vasiaVariant; place <= people; place += variants){
                if(place == theNumberVasia){
                    continue;
                }
                auto distance = findDistanceBetweenFriends(place);
                if(tempDistance >= distance){
                    tempDistance = distance;
                    placePetia = place;
                }
            }
        }
    }


    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        if(isExistPlace){
            outToFile(outFile,placePetia);
        }else{
            outFile << -1;
        }
        outFile << '\n';
        outFile.close();
    }else{
        return -1;
    }


    return 0;
}