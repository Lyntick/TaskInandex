#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>


int binaryS(int l , int r, std::uint64_t elem, const std::vector<std::uint64_t>& diegoCarts){// -2 less, -1 bigger


    int middle = (l + r) / 2;


    if(elem == diegoCarts[middle]){
        return  middle;
    }else if(elem < diegoCarts[middle]){
        binaryS(l , middle, elem, diegoCarts);
    }else{
        binaryS(middle, r, elem, diegoCarts);
    }
};

int main(){
    std::ifstream inFile("input.txt");
    int n = 0, k = 0;// n - number diego carts, k - number collectors
    std::vector<std::uint64_t> diegoCarts;
    std::vector<int> collectorsCarts;

    if (inFile.is_open()) {
        inFile >> n;
        diegoCarts.reserve(n);
        inFile.get();//skip '\n'
        diegoCarts.resize(n);
        for(int i = 0; i < n; ++i){
            inFile >> diegoCarts[i];
        }
        inFile.get();//skip '\n'
        inFile >> k;
        collectorsCarts.reserve(k);
        collectorsCarts.resize(k);
        for(int i = 0; i < k; ++i){
            inFile >> collectorsCarts[i];
        }
    }else{
        return -1;
    }
    inFile.close();
    std::vector<int> result;
    if(n != 0 && k != 0){
        result.resize(k);
        //sorting
        std::sort(diegoCarts.begin(), diegoCarts.end());
        //for solution use std::unique(iter.begin, iter.end);
        auto last = std::unique(diegoCarts.begin(),diegoCarts.end());
        diegoCarts.erase(last, diegoCarts.end());// it's not necessary, just print from begin to last;
        //binary search then
        auto binaryS = [&diegoCarts](int l , int r, std::uint64_t elem, bool& isExist) -> int{
            while(l <= r){

                if(diegoCarts[diegoCarts.size() -1] < elem){
                    return -1;
                }

                if(diegoCarts[0] > elem){
                    return -2;
                }


                int mid = l + (r - l) / 2;

                if (diegoCarts[mid] == elem){
                    isExist = true;
                    return mid;
                }
                else if (diegoCarts[mid] < elem){
                    l = mid + 1;
                }
                else{
                    r = mid - 1;
                }
            }
            return r;

        };
//        std::cout << diegoCarts.size();
        for(int i = 0; i < k; ++i){
            bool isExist = false;
            int temp = binaryS(0,diegoCarts.size(),collectorsCarts[i],isExist);
            if(temp == -1){
                result[i] = diegoCarts.size();
            }else if(temp == -2){
                result[i] = 0;
            }else if(isExist){
                result[i] = temp;
            }else{
                result[i] = temp + 1;
            }
        }
    }else{
        result.push_back(0);
    }





    std::ofstream outFile("output.txt");
    if (outFile.is_open()) {
        for(int iter: result)
            outFile << iter << '\n';
    }

    return 0;
}