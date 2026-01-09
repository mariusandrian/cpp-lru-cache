#include <list>
#include <unordered_map>
#include <optional>
#include <mutex>

#include "lru.h"

template <typename K, typename T>
class LRUCacheNaiveMutex
{
public:
    using iterator = typename LRUCache<K, T>::iterator;
    using value_type = typename LRUCache<K, T>::value_type;

    LRUCacheNaiveMutex(size_t capacity) : cache_{capacity} {}

    std::optional<T> find(const K &key)
    {
        std::lock_guard<std::mutex> lck(mutex_);
        return cache_.find(key);
    }

    std::pair<iterator, bool> set(const value_type &value)
    {
        std::lock_guard<std::mutex> lck(mutex_);
        return cache_.set(value);
    }

    std::size_t size()
    {
        return cache_.size();
    }

private:
    LRUCache<K, T> cache_;
    std::mutex mutex_;
};