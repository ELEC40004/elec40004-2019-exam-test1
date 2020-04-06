#include "series_operations.hpp"

#include <cassert>
#include <string>
#include <iostream>

static bool is_constant(const string &value)
{
    try{
        return stod(value);
    }catch(const invalid_argument &){
        return false;
    }
}

Series *series_factory(const string &name, const vector<Series*> &args)
{
    if(is_constant(name)){
        assert(args.size()==0);
        return series_make_constant(stod(name));

    }else if(name=="x"){
        assert(args.size()==0);
        return series_make_variable();

    }else if(name=="+"){
        assert(args.size()==2);
        return series_sum(args[0], args[1]);

    }else if(name=="*"){
        assert(args.size()==2);
        return series_product(args[0], args[1]);

    }else if(name=="integral"){
        assert(args.size()==1);
        return series_integral(args[0]);

    }else if(name=="derivative"){
        assert(args.size()==1);
        return series_derivative(args[0]);

    }else if(name=="sin"){
        assert(args.size()==1);
        return series_sin(args[0]);

    }else if(name=="cos"){
        assert(args.size()==1);
        return series_cos(args[0]);

    }else if(name=="cache"){  
        assert(args.size()==1);
        return series_cache(args[0]);

    }else{
        cerr<<"Unknown power series : '"<<name<<"'"<<endl;
        exit(1);
    }
}
