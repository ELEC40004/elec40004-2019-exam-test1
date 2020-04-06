#ifndef stl_map_hpp
#define stl_map_hpp

#include <map>

using namespace std;

template<class Key, class Value>
class STLMap
{
private:
    map<Key,Value> m_map;
public:
    Value &operator[]( const Key &k )
    {
        return m_map[k];
    }
};

#endif