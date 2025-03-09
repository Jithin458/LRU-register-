# LRU Cache Implementation in C

## Overview
This project is an implementation of an LRU (Least Recently Used) cache using a combination of a hash table and a doubly linked list in C. The project was developed as a learning exercise to understand how caching mechanisms work and how different data structures can be integrated effectively.

## Features
- Stores a fixed number of key-value pairs.
- Implements a hash table for O(1) average-time complexity lookup.
- Uses a doubly linked list to efficiently track the least recently used entries.
- Supports `get()` and `put()` operations with LRU eviction when the cache is full.

## Learning Outcomes
During this project, I learned about:
- Integrating a hash table with a doubly linked list.
- Managing memory dynamically in C.
- Using efficient data structures to optimize performance.
- Implementing an LRU cache mechanism from scratch.

## Compilation & Execution
To compile and run the program, use the following commands:

```sh
gcc -o lru lru.c
./lru
```

## Usage
The program inserts and retrieves values from the cache. Example output:
```
Get 2: 20
Get 1: -1
Get 3: 30
```
This output shows that retrieving key `2` returns its value, while key `1` was evicted due to LRU policy.

## License
This project is for learning purposes and is free to use and modify.

