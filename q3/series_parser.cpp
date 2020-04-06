#include "series_operations.hpp"

#include <list>
#include <sstream>

Series *series_parse(list<string> &parts)
{
    string name;
    vector<Series*> args;

    if(parts.front()=="("){
        parts.pop_front();
        
        name=parts.front();
        parts.pop_front();

        while(parts.front()!=")"){
            args.push_back(series_parse(parts));
        }
        parts.pop_front();
    }else{
        name=parts.front();
        parts.pop_front();
    }
    return series_factory(name, args);
}

Series *series_parse(istream &src)
{
    string tmp;
    list<string> parts;
    while(src >> tmp){
        parts.push_back(tmp);
    }
    return series_parse(parts);
}

Series *series_parse(const string &x)
{
    stringstream src(x);
    return series_parse(src);
}