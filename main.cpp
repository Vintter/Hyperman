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
    uint32_t height,prev;
    vector<uint32_t> next;
};

bool containsVector(uint32_t n,vector<uint32_t> v){
    for(uint32_t i:v)
        if (n == i)
            return true;
    return false;
}

int main() {

    uint32_t N,S,bosses=0,x;
    vector<uint32_t> root;

#ifdef LOCAL
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
#endif

    cin>>N>>S;
    vector<No> node (N+1);
    root.push_back(1);
    for(uint32_t i=2;i<=N;i++){
        cin>>x;
        node[i].prev = x;
    }

    for(uint32_t i=2; i<=N;i++){
        vector<uint32_t> s;
        uint32_t h=0;
        uint32_t j=i,a;
        bool y = false;
        while(!y){
            h++;
            if(node[j].height < h){
                if(!containsVector(j,s)){
                    node[j].height = h;
                    if(j != 1 && !containsVector(node[j].prev,s) && !containsVector(j,node[node[j].prev].next))
                        node[node[j].prev].next.push_back(j);
                    else if(j == 1)
                        y = true;
                }else{
                    if(!containsVector(a,root))
                        root.push_back(a);
                    y = true;
                }
                s.push_back(j);
                a=j;
                j=node[j].prev;
            }else{
                y = true;
            }
        }
        s.clear();
    }

    while(S>0){
        x = 0;
        for(uint32_t i : root){
            if(node[i].height > node[x].height){
                x = i;
            }
        }
        uint32_t l=node[x].height;
        while(l>0){
            uint32_t m=0;
            bosses++;
            for(uint32_t i : node[x].next){
                if(node[i].height > node[m].height){
                    m = i;
                }
                root.push_back(i);
            }
            if(containsVector(x,root)){
                erase(root,x);
            }
            node[x].height = 0;
            x = m;
            l--;
        }
        S--;
    }

    cout<<bosses<<endl;


#ifdef LOCAL
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds >(end - begin).count() << std::endl;
#endif
    return 0;
}
