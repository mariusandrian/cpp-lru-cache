#ifndef LRU_CACHE_H_
#define LRU_CACHE_H_

#include <list>
#include <unordered_map>
#include <optional>

#include "list_node.h"

template <typename K, typename T>
class LRUCache
{
public:
    using iterator = typename std::list<ListNode<K, T>>::iterator;
    using value_type = std::pair<const K, T>;

    explicit LRUCache(size_t capacity) : capacity_{capacity} {}

    std::optional<T> find(const K &key)
    {
        auto it = map_.find(key);
        if (it == map_.end())
        {
            return {};
        }

        iterator &listIt = it->second;
        if (listIt != list_.begin())
        {
            ListNode<K, T> temp = *(listIt);
            list_.erase(listIt);
            list_.push_front(temp);
            map_[temp.key] = list_.begin();
            return list_.begin()->data;
        }
        return it->second->data;
    }

    std::pair<iterator, bool> set(const value_type &value)
    {
        // std::cout << "---const ref set---" << "\n\n"
        //           << "kv: " << value.first << "|" << value.second << '\n';
        if (list_.size() == capacity_)
        {

            map_.erase(list_.back().key);
            list_.pop_back();
        }
        list_.emplace_front(value.first, value.second);
        map_.emplace(value.first, list_.begin());

        return {list_.begin(), true};
    }

    std::size_t size()
    {
        return list_.size();
    }

private:
    std::list<ListNode<K, T>> list_;
    std::unordered_map<K, iterator> map_;
    size_t capacity_;
};

#endif // LRU_CACHE_H_