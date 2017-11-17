// htcache.h: Hash Tree Cache

#pragma once

#include <htcache/htpage.h>

#include <cstdio>
#include <cstdlib>
#include <vector>

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

	// TODO: Determine Addresses, Pages, VPNShift, VPNMask, OffsetMask

	// TODO: Initialize PageTable
    }

    ValueType	get(const KeyType &key) {
    	if (PageTable.empty()) {
    	    return Handler(key);
	}

	// TODO: Determine virtual address, VPN, offset

	// TODO: Retrieve value from HTPage
	ValueType value;
    	return value;
    }

    void	put(const KeyType &key, const ValueType &value) {
    	if (PageTable.empty()) {
    	    return;
	}

	// TODO: Determine virtual address, VPN, offset

	// TODO: Set key, value in HTPage
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
