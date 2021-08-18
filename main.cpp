#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <algorithm>
#include <string>

#define LOCAL

using namespace std;

class No{
public:
    uint32_t move;
    bool x;//verifica se ja houve uma passagem por esse no
};

bool contains(uint32_t n,vector<No> v){
    for(auto i:v)
        if (n == i.move)
            return true;
    return false;
}

bool containsVector(uint32_t n,vector<uint32_t> v){
    for(auto i:v)
        if (n == i)
            return true;
    return false;
}

int main() {

    uint32_t N,S,bosses=0,start,x;

#ifdef LOCAL
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#endif

    cin>>N>>S;
    vector<No> node (N+1);
    for(uint32_t i=2;i<=N;i++){
        cin>>x;
      node[i].move = x;
    }

    while(S>0) {
        vector<uint32_t> s;
        uint32_t h=0;
        for(uint32_t i=2;i<=N;i++) {
            x=0;
            uint32_t y=i;
            while(y != 0 && !node[y].x && !containsVector(y,s)){
                s.push_back(y);
                x++;
                y = node[y].move;
            }
            s.clear();
            if(x>h){
                h = x;
                start = i;
            }
        }
        h=0;
        while(start != 1 && !node[start].x && !containsVector(start,s)){
            bosses++;
            node[start].x = true;
            s.push_back(start);
            start = node[start].move;
        }
        S--;
    }

    cout<<bosses+1<<endl;


#ifdef LOCAL
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds >(end - begin).count() << std::endl;
#endif
    return 0;
}
