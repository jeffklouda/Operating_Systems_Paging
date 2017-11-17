// fibonacci.cpp

#include <htcache/htcache.h>

#include <cstdio>
#include <thread>
    
int main(int argc, char *argv[]) {
    if (argc != 5) {
    	fprintf(stderr, "Usage: %s AddressLength PageSize EvictionPolicy Threads\n", argv[0]);
    	return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
