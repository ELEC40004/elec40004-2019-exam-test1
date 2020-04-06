#include "mu0.hpp"

#include <fstream>

int main(int argc, char *argv[])
{
    ifstream a(argv[1]);
    ifstream b(argv[2]);

    if(!a.is_open() || !b.is_open()){
        cerr<<"Couldn't open one of the binaries.\n";
        exit(2);
    }

    vector<uint16_t> bin_a=mu0_read_binary(a);
    assert(bin_a.size()==4096);

    vector<uint16_t> bin_b=mu0_read_binary(b);
    assert(bin_b.size()==4096);

    for(int i=0; i<4096; i++){
        if(bin_a[i]!=bin_b[i]){
            cerr<<"Different at word address "<<i<<endl;
            exit(1);
        }
    }
    
    return 0;
}
