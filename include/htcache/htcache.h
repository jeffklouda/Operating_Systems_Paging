// htcache.h: Hash Tree Cache

#pragma once

#include <htcache/htpage.h>

#include <cstdio>
#include <cstdlib>
#include <vector>
#include <math.h>

template <typename KeyType, typename ValueType>
class HTCache {
    typedef ValueType (*HandlerFunc)(const KeyType&);
    typedef std::vector<HTPage<KeyType, ValueType>> TableType;

private:
    size_t	    AddressLength;  // Length of virtual address
    size_t	    PageSize;	    // Number of entries per page
    EvictionPolicy  Policy;	    // Eviction policy
    HandlerFunc	    Handler;	    // Handler for misses
    TableType	    PageTable;	    // Page table

    size_t	    Addresses;	    // Number of addresses
    size_t	    Pages;	    // Number of pages
    size_t	    VPNShift;	    // VPN Bit Shift
    size_t	    VPNMask;	    // VPN Bit Mask
    size_t	    OffsetMask;	    // Offset Bit Mask

    size_t	    Hits;	    // Number of cache hits
    size_t	    Misses;	    // Number of cache misses

    std::mutex	    Lock;	    // Lock

public:
    HTCache(size_t addrlen, size_t pagesize, EvictionPolicy policy, HandlerFunc handler) {
    	if (addrlen == 0) {
    	    return;
	    }

        // TODO Determine Addresses, Pages, VPNShift, VPNMask, OffsetMask
        Addresses = 1<<addrlen;
        if (pagesize == 0)
            pagesize = 1;
        Pages = (Addresses / pagesize);
        VPNShift = addrlen - ceil(log2(Pages));
        VPNMask = (Pages-1)<<VPNShift;
        OffsetMask = pagesize-1;

        // TODO Initialize PageTable
        HTPage<KeyType, ValueType> temp(pagesize, policy);
        for (size_t i = 0; i < Pages; i++) {
            PageTable.push_back(temp);
        }

    }

    ValueType	get(const KeyType &key) {
    	if (PageTable.empty()) {
    	    return Handler(key);
        }

        // TODO Determine virtual address, VPN, offset
        std::hash<KeyType> hash_func;
        size_t va = hash_func(key);
        size_t vpn = va>>VPNShift;
        size_t offset = va & OffsetMask;

        // TODO Retrieve value from HTPage
        ValueType value = PageTable[vpn].get(key, offset);
    	return value;
    }

    void	put(const KeyType &key, const ValueType &value) {
    	if (PageTable.empty()) {
    	    return;
	    }

        // TODO Determine virtual address, VPN, offset
        std::hash<KeyType> hash_func;
        size_t va = hash_func(key);
        size_t vpn = va>>VPNShift;
        size_t offset = va & OffsetMask;

        // TODO: Set key, value in HTPage
        PageTable[vpn].put(key, value, offset);
    }

    void stats(FILE *stream) {
        fprintf(stream, "Addresses : %lu\n"  , Addresses);
        fprintf(stream, "Pages     : %lu\n"  , Pages);
        fprintf(stream, "VPNShift  : %lu\n"  , VPNShift);
        fprintf(stream, "VPNMask   : 0x%lX\n", VPNMask);
        fprintf(stream, "OffsetMask: 0x%lX\n", OffsetMask);
        fprintf(stream, "Hits      : %lu\n"  , Hits);
        fprintf(stream, "Misses    : %lu\n"  , Misses);
    }
};
