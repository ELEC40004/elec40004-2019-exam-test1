#ifndef balanced_map_hpp
#define balanced_map_hpp

#include <string>
#include <random>

#include "tree_operations.hpp"
#include "tree_rotations.hpp"

using namespace std;

template<class Key, class Value>
class BalancedMap
{
public:
    struct Node
    {
        Key key;
        Value value;
        Node *left;
        Node *right;
    };

private:
    mt19937 m_rng;

    uint32_t new_weight()
    {
        return m_rng();
    }

    Node *insert(Node *tree, const Key &key, Node *&res)
    {
        if(tree==nullptr){
            res=new Node{key, Value(), nullptr, nullptr};
            tree=res;
        }else{
            if(key < tree->key){
                tree->left = insert(tree->left, key, res);
            }else if(key > tree->key){
                tree->right = insert(tree->right, key, res);
            }else{
                assert(tree->key==key);
                res=tree;
            }
        }
        return tree;
    }

    Node *m_root;
public:
    BalancedMap()
        : m_root(nullptr)
    {}

    Value &operator[]( const Key &k )
    {
        Node *res=nullptr;
        m_root=insert(m_root, k, res);
        assert(res);
        return res->value;
    }

    // This is needed for assessment, but may be useful
    // for debugging too
    const Node *get_root() const
    { return m_root; }
};

#endif