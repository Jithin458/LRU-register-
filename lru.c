#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CACHE_SIZE 4
#define HASH_SIZE 10

typedef struct Node{
int key, value;
struct Node *prev, *next;
}Node;

typedef struct HashEntry{
int key;
Node *node;
struct HashEntry *next;
}HashEntry;

typedef struct LRU{
int capacity,size;
Node *head,*tail;
HashEntry *hashtable[HASH_SIZE];
}LRU;

Node* createNode(int key, int value){
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->key = key;
    newNode->value = value;
    newNode->prev=newNode->next=NULL;
    return newNode;
}

int HashFunction(int key){
    return key % HASH_SIZE;
}

HashEntry* findEntry(LRU *cache,int key){
   int index = HashFunction(key);
   HashEntry *entry = cache->hashtable[index];
   while(entry){
    if (entry->key == key){
        return entry;
    }
    entry = entry->next;
   }
  return NULL;
}

void insert(LRU *cache, int key, Node *node){
    int index = HashFunction(key);
    HashEntry * entry = (HashEntry*)malloc(sizeof(HashEntry));
    entry->key = key;
    entry->node = node;
    entry->next = cache->hashtable[index];
    cache->hashtable[index] = entry;
}

void delete(LRU *cache, int key){
    int index = HashFunction(key);
    HashEntry *entry = cache->hashtable[index];
    HashEntry* prev = NULL;
    while(entry){
    if (entry->key == key){
        if (prev) prev->next = entry->next;
        else cache->hashtable[index] = entry->next;
        free(entry);
        return;
    }
    prev = entry;
    entry = entry->next;
    }
    
   }

void moveToHead(LRU *cache,Node *node){
    if(cache->head == node) return;
    if(node->prev)node->prev->next = node->next;
    if(node->next)node->next->prev = node->prev;
    if(cache->tail==node)cache->tail= node->prev;
    node->next= cache->head;
    node->prev=NULL;
    if(cache->head)cache->head->prev=node;
    cache->head = node;
    if (!cache->tail) cache->tail = node;
}

int get(LRU *cache, int key){
    HashEntry *entry = findEntry(cache,key);
    if(!entry)return-1;
    moveToHead(cache, entry->node);
    return entry->node->value;   
}

void removeLRU(LRU *cache){
    if(!cache->tail)return;
    delete(cache, cache->tail->key);
    Node *temp = cache->tail;
    if(cache->tail->prev){
        cache->tail->prev->next=NULL;
        cache->tail=cache->tail->prev;
    }else{
        cache->head = cache->tail = NULL;
    }
    free(temp);
    cache->size--;

}

LRU *createCache(int capacity){
    LRU *cache =(LRU*)malloc(sizeof(LRU));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = cache->tail = NULL;
    memset(cache->hashtable,0,sizeof(cache->hashtable));
    return cache;
}

void put(LRU *cache, int key,int value){
    HashEntry *entry = findEntry(cache,key);
    if(entry){
        entry->node->value= value;
        moveToHead(cache,entry->node);
        return;
    }
    if(cache->capacity==cache->size){
        removeLRU(cache);
    }
    Node *newNode = createNode(key,value);
    insert(cache, key, newNode);
    newNode->next = cache->head;
    if(cache->head)cache->head->prev=newNode;
    cache->head = newNode;
    if(!cache->tail)cache->tail = newNode;
    cache->size++;

}
int main() {
    LRU* cache = createCache(CACHE_SIZE);

    put(cache, 1, 10);
    put(cache, 2, 20);
    put(cache, 3, 30);
    put(cache, 4, 40);

    printf("Get 2: %d\n", get(cache, 2)); 
    put(cache, 5, 50); 

    printf("Get 1: %d\n", get(cache, 1));
    printf("Get 3: %d\n", get(cache, 3)); 

    return 0;
}