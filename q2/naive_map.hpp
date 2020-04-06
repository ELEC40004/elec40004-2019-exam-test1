#ifndef naive_map_hpp
#define naive_map_hpp

#include <vector>

template<class Key, class Value>
class NaiveMap
{
private:
    vector<pair<Key,Value>> m_elements;
public:
    Value &operator[]( const Key &k )
    {
        for(unsigned i=0; i<m_elements.size(); i++){
            if(m_elements[i].first==k){
                return m_elements[i].second;
            }
        }
        m_elements.push_back({k,Value()});
        return m_elements.back().second;
    }
};

#endif
