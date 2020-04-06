#include "stl_map.hpp"
#include "naive_map.hpp"


#include <chrono>
#include <iostream>

// This expects the map to map from int to int
template<class TMap>
void test_map_performance(const string &name)
{
    auto check = std::chrono::high_resolution_clock::now();

    TMap map;
    int x=0;
    for(int i=8; i<=25; i++){
        auto start = std::chrono::high_resolution_clock::now();
        int todo=1<<i;
        for(int j=0; j<todo; j++){
            map[x]=x;
            x++;
        }
        auto finish = std::chrono::high_resolution_clock::now();
        double time= std::chrono::duration<double>(finish-start).count();

        cout<<name<<", "<<x<<", "<<time<<", "<<time/todo<<endl;

        //assert(tree_is_search_tree(map.get_root()));

        if(std::chrono::duration<double>(finish-check).count() > 10){
            break;
        }
    }
}

int main()
{
    cout<<"Name, Total, Inserted, Time/Insert"<<endl;

    test_map_performance<STLMap<unsigned,unsigned>>("STLMap");
    test_map_performance<NaiveMap<unsigned,unsigned>>("NaiveMap");
}