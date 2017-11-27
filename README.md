CSE.30341.FA17: Project 05
==========================

This is the documentation for [Project 05] of [CSE.30341.FA17].

Members
-------

1. Jeff Klouda (jklouda1@nd.edu)
2. Matthew D'Alonzo (mdalonz1@nd.edu)

Design
------

> 1. In the `HTCache` constructor, you will need to determine the following
>    values: `Addresses`, `Pages`, `VPNShift`, `VPNMask`, and `OffsetMask`.
>    How would you determine these values and what would they be used for?
>
>    We set Addresses to the value of 2^(addrlen), since this is the number of addresses that can be accessed with that number of bits. We use Addresses to know when your cache is full and you need to start evicting. 
>
>    We set Pages to Addresses/pagesize, since that gives you the the number total pages. We use Pages to determine the VPN of what you're trying to access. You need to know how many pages you can address.
>
>    We set VPNShift to addrlen-round_up(log2(Pages)). We use that to determine how many remaining bits there are after getting the VPN, which are the bits for the offset.
>
>    We set VPNMask such that the VPNShift LSB's are 0, and the rest are 1. We will AND this with the address to determine the VPN.
>
>    We set OffsetMask such that the VPNShift LSB's are 1, and the rest are 0. We will AND this with the address to get the address.
>

Response.

> 2. In the `HTCache::get` method, you will need to determine the **VPN** and
>    **offset** based on the specified **key**.
> 
>       - How would you determine these values?
>       - How would you use these values to retrieve the specified value?
>       - What data would you need to update?
>       - What data would you need to synchronize?
>
>    To determine these values, we hash the **key** and appy the requisite masks to get the **VPN** and **offset**
>
>    To retrieve the specified value, we use the **VPN** as an index for the Page Table. And then, we use the **offset** as an index inside of that Page Table. If the key at the index doesn't match the one you're trying to get for, you linearly probe until you either find it, or get back to where you were. If you get back to where you were, you throw an exception and call a handler to put it in the page table.
>
>    If the value isn't present, we would need to use the handler to add it. We also need to update Hits and Misses.
>
>    We need to synchronize the cache. Specifically, we need to make sure that only one thing is adding or evicting a Page Table Entry at a time. Also, we need to make sure Hits and Misses variables are synchronized. 
>
Response.

> 3. In the `HTCache::put` method, you will need to determine the **VPN** and
>    **offset** based on the specified **key**.
> 
>       - How would you determine these values?
>       - How would you use these values to store the specified value?
>       - What data would you need to update?
>       - What data would you need to synchronize?
>
>    To determine these values, we hash the **key** and appy the requisite masks to get the **VPN** and **offset**
>
>    To store the specified value, we use the **VPN** as an index for the Page Table. And then, we use the **offset** as an index inside of that Page Table. If the specified Page Table Entry location is not available, we will linearly probe until we find the next available entry. If it's full, we do an eviction and then store it.
>
>    We need to update the page table, with the new value added, and an evicted value removed if necessary.
>
>    We need to synchronize the cache. Specifically, we need to make sure that only one thing is adding or evicting a Page Table Entry at a time.
>
Response.

> 3. In the `HTPage` class, you will need to implement FIFO, Random, LRU, and
>    Clock eviction policies.  For each of these policies:
> 
>       - What bookkeeping do you need to implement the policy?
>       - How would you use this bookkeeping to implement the policy?
>
>    FIFO: Keep track of the order in which entries are added to a page. When you want to do an eviction, you just search through and find the value that was added first. When you add a value, you set its FIFO to Least Recently Added. 
>
>    Random: You don't need any bookkeeping to implement this policy. When you want to evict, choose a random number the size of the page, and evict that one.
>
>    LRU: You need to keep track of when each page table entry was accessed. When you want to evict, you take the LRU page table entry and evict that one. 
>
>    Clock: We need a bitmap to keep track of if a page table entry has been recently accessed. You also have an index for that bitmap that corresponds to the clock hand. When you want to evict, you check the bitmap at your clock hand index. If its value is 1, you set it to 0 and move to the next value, doing the same thing. If its 0, you evict it, and set the new value's bit to 1 and advance the clock hand. Whenever you access a value, if its bit isn't 1, you set it to 1. 
>

Response.

> 5. In the `HTPage::get`, you must use linear probing to locate an appropriate
>    `HTPageEntry`.
> 
>       - How would you determine if you found the correct `HTPageEntry`?
>
>  You can compare a hashed value of the key with a hashed value of the key in the HTPageEntry.  
>
Response.

> 6. In the `HTPage::put`, you must use linear probing to locate an appropriate
>    `HTPageEntry`.
> 
>       - How would you determine if you need to update a value rather than add a new one?
>       - How would you determine if you need to perform an eviction?
>       - How would you perform an eviction?
>
>    If the key matches but the values are different.
>
>    If, after linear probing, you find that there is no open space in the page.
>
>    You use your policy to determine which entry to evict. Then, you just replace the entry with your new one. 
>

Response.

Demonstration
-------------

> Place a link to your demonstration slides on [Google Drive].

Errata
------

> Describe any known errors, bugs, or deviations from the requirements.

Extra Credit
------------

> Describe what extra credit (if any) that you implemented.

[Project 05]:       https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/project05.html
[CSE.30341.FA17]:   https://www3.nd.edu/~pbui/teaching/cse.30341.fa17/
[Google Drive]:     https://drive.google.com
