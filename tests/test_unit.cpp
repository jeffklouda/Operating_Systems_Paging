#include <htcache/htcache.h>

#include <string>
#include <iostream>
#include <unistd.h>

int main () {
    size_t addrlen = 8;
    size_t pagesize = 64;
    EvictionPolicy p = EVICT_FIFO; 
    std::string str = "";
    
    // HTCache constructor
    HTCache<size_t, size_t> *test = NULL;
    test = new HTCache<size_t, size_t>(addrlen, pagesize, p, [](const size_t &key) {return key;});
    if (test) 
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HTCache constructor\n";
    
    // HTCache put() and get()
    test->put(42, 18);
    size_t result = test->get(42);
    if (result == 18)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HTCache put()\n";
    if (result == 18)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HTCache get()\n";
    
    // HTPage constructor
    HTPage<size_t, size_t> *pageTest;
    pageTest = new HTPage<size_t, size_t> (pagesize, p);
    if (pageTest)
        str += "[x] ";
    else
        str += "[ ] ";
    str += "HTPage constructor\n";
    
    // HTPage put() and get()
    pageTest->put(3, 7, 0);
    result = pageTest->get(3, 0);
    if (result == 7)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HTPage put()\n";
    if (result == 7)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HTPage get()\n";

    // FIFO Eviction
    HTPage<size_t, size_t> fifo_page (4, EVICT_FIFO);
    fifo_page.put (1, 1, 0);
    fifo_page.put (2, 2, 0);
    fifo_page.put (3, 3, 0);
    fifo_page.put (4, 4, 0);
    fifo_page.put (5, 5, 0);
    bool success = false;
    try {
        fifo_page.get(1, 0);
    }
    catch (const std::out_of_range& oor) {
        success = true;
    }
    if (success)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HT Page FIFO Eviction\n";

    // Random Eviction
    HTPage<size_t, size_t> rand_page (4, EVICT_RANDOM);
    rand_page.put (1, 1, 0);
    rand_page.put (2, 2, 0);
    rand_page.put (3, 3, 0);
    rand_page.put (4, 4, 0);
    rand_page.put (5, 5, 0);
    result = rand_page.get(5, 0);
    if (result == 5)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HT Page Random Eviction\n";
    
    // LRU Eviction
    HTPage<size_t, size_t> lru_page (4, EVICT_LRU);
    lru_page.put (1, 1, 0);
    lru_page.put (2, 2, 0);
    lru_page.put (3, 3, 0);
    lru_page.put (4, 4, 0);
    lru_page.get (1, 0);
    lru_page.get (2, 0);
    lru_page.get (3, 0);
    lru_page.put (5, 5, 0);
    success = false;
    try {
        lru_page.get(4, 0);
    }
    catch (const std::out_of_range& oor) {
        success = true;
    }
    if (success)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HT Page LRU Eviction\n";
    
    // Clock Eviction
    HTPage<size_t, size_t> clock_page (4, EVICT_CLOCK);
    clock_page.put (1, 1, 0);
    clock_page.put (2, 2, 0);
    clock_page.put (3, 3, 0);
    clock_page.put (4, 4, 0);
    clock_page.put (5, 5, 0);
    success = false;
    try {
        clock_page.get(1, 0);
    }
    catch (const std::out_of_range& oor) {
        success = true;
    }
    if (success)
        str += "[X] ";
    else
        str += "[ ] ";
    str += "HT Page Clock Eviction\n";
    
    std::cout << str << std::endl;
    return EXIT_SUCCESS;
}
