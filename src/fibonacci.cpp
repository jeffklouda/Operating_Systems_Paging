// fibonacci.cpp

#include <htcache/htcache.h>

#include <cstdio>
#include <thread>
#include <iostream>
#include <iomanip>

typedef size_t fib_t;

fib_t fibs[100] = {0};
void fib_func(size_t tid, HTCache<fib_t, fib_t> *cache) {
    for (size_t i = 2; i < 100; i++){
        
        fibs[i] = cache->get(i-1) + cache->get(i-2);
        cache->put(i, fibs[i]);
    }
    return;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
    	fprintf(stderr, "Usage: %s AddressLength PageSize EvictionPolicy Threads\n", argv[0]);
    	return EXIT_FAILURE;
    }
    size_t addrlen      = strtol(argv[1], NULL, 10);
    size_t pagesize     = strtol(argv[2], NULL, 10);
    EvictionPolicy policy = static_cast<EvictionPolicy>(strtol(argv[3], NULL, 10));
    size_t nthreads     = strtol(argv[4], NULL, 10);

    //HTCache<fib_t, fib_t> cache(addrlen, pagesize, policy, [](const fib_t &key) {return (fibs[key-2] + fibs[key-1]); });
    HTCache<fib_t, fib_t> cache(addrlen, pagesize, policy, [](const fib_t &key) {return (fibs[key]); });
 
    fibs[1] = 1;
    //cache.put(0, 0);
    //cache.put(1, 1);
    std::thread t[nthreads];
    for (size_t i = 0; i < nthreads; i++) {
        t[i] = std::thread(fib_func, i, &cache);
    }

    for (size_t i = 0; i < nthreads; i++) {
        t[i].join();
    }
    
    for (size_t i = 0; i < 100; i++){
        std::cout << "0. Fibonacci(" << std::setw(2) << i << ") = " << fibs[i] << std::endl;
    }
    cache.stats(stdout);
    return EXIT_SUCCESS;
}
