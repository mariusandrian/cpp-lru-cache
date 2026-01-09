#ifndef LRU_CACHE_LISTNODE_H_
#define LRU_CACHE_LISTNODE_H_

template <typename K, typename T>
struct ListNode
{
    K key;
    T data;
};

#endif // LRU_CACHE_LISTNODE_H_