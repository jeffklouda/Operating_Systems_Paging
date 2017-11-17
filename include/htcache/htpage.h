// htpage.h: Hash Tree Page

#pragma once

#include <cstdlib>
#include <mutex>
#include <queue>
#include <random>
#include <stdexcept>
#include <vector>

enum EvictionPolicy {
    EVICT_FIFO,
    EVICT_RANDOM,
    EVICT_LRU,
    EVICT_CLOCK,
};

template <typename KeyType, typename ValueType>
struct HTPageEntry {
    KeyType	Key;
    ValueType	Value;
    // TODO: Add bookkeeping for eviction
};

template <typename KeyType, typename ValueType>
class HTPage {
    typedef std::vector<HTPageEntry<KeyType, ValueType>> EntriesType;

private:
    EntriesType		Entries;    // Individual entries
    EvictionPolicy	Policy;	    // Eviction policy
    mutable std::mutex	Lock;	    // Lock

    // TODO: Add bookkeeping for eviction

    size_t evict_fifo(size_t offset) {
    	// TODO: Implement FIFO eviction policy
    	return offset;
    }

    size_t evict_random(size_t offset) {
    	// TODO: Implement random eviction policy
    	return offset;
    }

    size_t evict_lru(size_t offset) {
    	// TODO: Implement LRU eviction policy
    	return offset;
    }

    size_t evict_clock(size_t offset) {
    	// TODO: Implement clock eviction policy
    	return offset;
    }

public:
    HTPage(size_t n, EvictionPolicy p) {
    	// TODO: Initialize Entries
    }

    HTPage(const HTPage<KeyType, ValueType>& other) {
    	// TODO: Copy instance variables
    }

    ValueType get(const KeyType &key, size_t offset) {
    	// TODO: Use linear probing to locate key
    }

    void put(const KeyType &key, const ValueType &value, size_t offset) {
    	// TODO: Use linear probing to locate key

    	// TODO: Evict an entry if HTPage is full

	// TODO: Update entry
    }
};
