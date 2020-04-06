#ifndef unbalanced_map_hpp
#define unbalanced_map_hpp

#include <string>
#include <cassert>

#include "tree_operations.hpp"

using namespace std;

template<class Key, class Value>
class UnBalancedMap
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
    Node *insert(Node *tree, const Key &key, Node *&res)
    {
        if(tree==nullptr){
            res=new Node{key, Value(), nullptr, nullptr};
            tree=res;
        }else{
            if(key < tree->key){
                tree->left = insert(tree->left, key, res);
            }else if(key > tree->key){
                tree->right = insert(tree->right, key,res );
            }else{
                assert(tree->key==key);
                res=tree;
            }
        }
        return tree;
    }

    Node *m_root;
public:
    UnBalancedMap()
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