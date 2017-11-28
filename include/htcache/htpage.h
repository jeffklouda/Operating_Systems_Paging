// htpage.h: Hash Tree Page

#pragma once

#include <algorithm>
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
    bool valid;
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
        offset = fifoQueue.front();
        fifoQueue.pop(); 	
        return offset;
    }

    size_t evict_random(size_t offset) {
    	// TODO: Implement random eviction policy
        offset = rand() % Entries.size();      
   	    return offset;
    }

    size_t evict_lru(size_t offset) {
    	// TODO: Implement LRU eviction policy
    	std::vector<time_t>::iterator lruIterator = std::min_element(lruVector.begin(), lruVector.end());
        offset = lruIterator - lruVector.begin();
    	return offset;
    }

    size_t evict_clock(size_t offset) {
    	// TODO: Implement clock eviction policy
        clockHand = offset;
        while (clockVector[clockHand] == 1) {
            clockVector[clockHand] = 0;
            clockHand = (clockHand+1) % clockVector.size();
        }
        offset = clockHand;
        return offset;
    }

public:
    HTPage(size_t n, EvictionPolicy p) {
    	// TODO: Initialize Entries
    	clockHand = 0;
        HTPageEntry <KeyType, ValueType> temp;
        temp.valid = false;
        for (size_t i = 0; i < n; i++) {
            Entries.push_back(temp);
            lruVector.push_back(0);
            clockVector.push_back(0);
        }
    }

    HTPage(const HTPage<KeyType, ValueType>& other) {
    	// TODO: Copy instance variables
    	clockHand = 0;
        

        //const std::vector<HTPageEntry<KeyType, ValueType>> *otherEntries = other.getEntries();
        
        EntriesType otherEntries = other.getEntries();
        
        for (size_t i = 0; i < otherEntries.size(); i++) {
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
            if (Entries[i].valid && key_hash == hash_func(Entries[i].Key)) {
                lruVector[i] = time(NULL);
                clockVector[i] = true;
                return Entries[i].Value;
            }
        }
        for (size_t i = 0; i < offset; i++) {
            if (Entries[i].valid && key_hash == hash_func(Entries[i].Key)) {
                lruVector[i] = time(NULL);
                clockVector[i] = true;
                return Entries[i].Value;
            }
        }
        throw std::out_of_range ("oor");
    }

    void put(const KeyType &key, const ValueType &value, size_t offset) {
    	// TODO: Use linear probing to locate key
        std::hash<KeyType> hash_func;
        size_t key_hash = hash_func(key);
        if (Entries[offset].valid == false) {
            fifoQueue.push(offset);
            lruVector[offset] = time(NULL);
            clockVector[offset] = true;
            
            Entries[offset].Key = key;
            Entries[offset].Value = value;
            Entries[offset].valid = true;
            return;
        }
        for (size_t i = offset; i < Entries.size(); i++) {
            if (Entries[i].valid == false || key_hash == hash_func(Entries[i].Key)) {
                clockVector[i] = true;
                lruVector[i] = time(NULL);
                
                if (Entries[i].valid == false)
                    fifoQueue.push(i);
                
                Entries[i].Key = key;
                Entries[i].Value = value;
                Entries[i].valid = true;
                return;
            }
        }
        for (size_t i = 0; i < offset; i++) {
            if (Entries[i].valid == false || key_hash == hash_func(Entries[i].Key)) {
                lruVector[i] = time(NULL);
                clockVector[i] = true;
                
                if (Entries[i].valid == false)
                    fifoQueue.push(i);
                
                Entries[i].Key = key;
                Entries[i].Value = value;
                Entries[i].valid = true;
                return;
            }
        }
    	// TODO: Evict an entry if HTPage is full
        switch (Policy) {
            
            case EVICT_FIFO:
                offset = evict_fifo(offset);
                break;
            case EVICT_RANDOM:
                offset = evict_random(offset);
                break;
            case EVICT_LRU:
                offset = evict_lru(offset);
                break;
            case EVICT_CLOCK:
                offset = evict_clock(offset);
                break;
            default:
                offset = evict_fifo(offset);
                break;
        }
	    // TODO: Update entry
        fifoQueue.push(offset);
        lruVector[offset] = time(NULL);
        clockVector[offset] = true;
        
        Entries[offset].Key = key;
        Entries[offset].Value = value;
        Entries[offset].valid = true;
        return;
    }

    EntriesType getEntries() const {
        return Entries;
    }
    
    EvictionPolicy getPolicy () const {
        return Policy;
    }

};
