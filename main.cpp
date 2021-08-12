#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <chrono>
#include <algorithm>
#include <unordered_map>

#define LOCAL

using namespace std;
typedef std::unordered_multimap<int,int> map;

int main() {

    map m1,m2;
    int N,S,i=0,x;

    vector<int> a,b;

#ifdef LOCAL
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
#endif

    cin>>N>>S;
    for(int j=2;j<=N;j++){
        cin>>i;
        m1.insert(map::value_type(i,j));
        m2.insert(map::value_type(j,i));
    }
    m2.insert(map::value_type(1,0));

    while(S > 0) {
        for (map::const_iterator it = m1.begin(); it != m1.end(); ++it) {
            if (m1.count(it->second) == 0 && it->second != 1) {
                x = it->second;
                map::const_iterator it2;
                while (m2.contains(x)) {
                    it2 = m2.find(x);
                    b.push_back(it2->first);
                    x = it2->second;
                }
                if (a.empty() || b.size() > a.size()) {
                    a = b;
                }
                b.clear();
            }
        }
        while (!a.empty()) {
            m2.erase(a[0]);
            erase(a, a[0]);
        }
        S--;
    }

    cout<<N-m2.size()<<endl;

#ifdef LOCAL
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds >(end - start).count() << std::endl;
#endif
    return 0;
}