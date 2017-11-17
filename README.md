CSE.30341.FA17: Project 05
==========================

This is the documentation for [Project 05] of [CSE.30341.FA17].

Members
-------

1. Domer McDomerson (dmcdomer@nd.edu)
2. Belle Fleur (bfleur@nd.edu)

Design
------

> 1. In the `HTCache` constructor, you will need to determine the following
>    values: `Addresses`, `Pages`, `VPNShift`, `VPNMask`, and `OffsetMask`.
>    How would you determine these values and what would they be used for?

Response.

> 2. In the `HTCache::get` method, you will need to determine the **VPN** and
>    **offset** based on the specified **key**.
> 
>       - How would you determine these values?
>       - How would you use these values to retrieve the specified value?
>       - What data would you need to update?
>       - What data would you need to synchronize?

Response.

> 3. In the `HTCache::put` method, you will need to determine the **VPN** and
>    **offset** based on the specified **key**.
> 
>       - How would you determine these values?
>       - How would you use these values to store the specified value?
>       - What data would you need to update?
>       - What data would you need to synchronize?

Response.

> 3. In the `HTPage` class, you will need to implement FIFO, Random, LRU, and
>    Clock eviction policies.  For each of these policies:
> 
>       - What bookkeeping do you need to implement the policy?
>       - How would you use this bookkeeping to implement the policy?

Response.

> 5. In the `HTPage::get`, you must use linear probing to locate an appropriate
>    `HTPageEntry`.
> 
>       - How would you determine if you found the correct `HTPageEntry`?

Response.

> 6. In the `HTPage::put`, you must use linear probing to locate an appropriate
>    `HTPageEntry`.
> 
>       - How would you determine if you need to update a value rather than add a new one?
>       - How would you determine if you need to perform an eviction?
>       - How would you perform an eviction?

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
