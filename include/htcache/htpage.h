// htpage.h: Hash Tree Page

#pragma once

#include <cstdlib>
#include <mutex>
#include <queue>
#include <random>
#include <stdexcept>
#include <vector>
#include <time.h>

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
    mutable std::mutex	Lock;   // Lock

    // TODO: Add bookkeeping for eviction
    std::queue<size_t>  fifoQueue;
    std::vector<time_t> lruVector;
    std::vector<bool>   clockVector;
    size_t              clockHand;

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
    	clockHand = 0;
        HTPageEntry<KeyType, ValueType> temp;
        temp.Key = NULL;
        temp.Value = NULL;
        for (size_t i = 0; i < n; i++) {
            Entries.push_back(temp);
            lruVector.push_back(0);
            clockVector.push_back(0);
        }
    }

    HTPage(const HTPage<KeyType, ValueType>& other) {
    	// TODO: Copy instance variables
    	clockHand = 0;
        EntriesType *otherEntries = other.getEntries();
        for (size_t i = 0; i < otherEntries->size(); i++) {
            Entries.push_back(otherEntries[i]);
            lruVector.push_back(0);
            clockVector.push_back(0);
        }
        Policy = other.getPolicy();
        
    }

    ValueType get(const KeyType &key, size_t offset) {
    	// TODO: Use linear probing to locate key
        std::hash<KeyType> hash_func;
        size_t key_hash = hash_func(key);
        for (size_t i = offset; i < Entries.size(); i++) {
            if (key_hash == hash_func(Entries[i].Key)) {
                return Entries[i].Value;
            }
        }
        for (size_t i = 0; i < offset; i++) {
            if (key_hash == hash_func(Entries[i].Key)) {
                return Entries[i].Value;
            }
        }
        throw std::out_of_range ("oor");
        return NULL;
    }

    void put(const KeyType &key, const ValueType &value, size_t offset) {
    	// TODO: Use linear probing to locate key
        std::hash<KeyType> hash_func;
        size_t key_hash = hash_func(key);
        if (Entries[offset].Key == NULL) {
            Entries[offset].Key = key;
            Entries[offset].Value = value;
            return;
        }
        for (size_t i = offset; i < Entries.size(); i++) {
            if (key_hash == hash_func(Entries[i].Key) || Entries[i].Key == NULL) {
                Entries[i].Key = key;
                Entries[i].Value = value;
                return;
            }
        }
        for (size_t i = 0; i < offset; i++) {
            if (key_hash == hash_func(Entries[i].Key) || Entries[i].Key == NULL) {
                Entries[i].Key = key;
                Entries[i].Value = value;
                return;
            }
        }
    	// TODO: Evict an entry if HTPage is full
           
	    // TODO: Update entry
    }

    *EntriesType getEntries() {
        return &Entries;
    }
    
    EvictionPolicy getPolicy () {
        return Policy;
    }

};
