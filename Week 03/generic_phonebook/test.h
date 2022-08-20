#ifndef __TEST_H__
#define __TEST_H__

typedef struct
{
    void* key;
    void* value;
}Entry;

typedef struct
{
    Entry* entries;
    int size, total;
    Entry (*makeNode) (void*, void*);
    int (*compare)(void*, void*);
}SymTable;

#define INCREMENTAL_SIZE 10
#define INITIAL_SIZE 100

SymTable* makeTable( int (*compare)(void*, void*), Entry (*makeNode) (void*, void*) );
void DropTable(SymTable*S);
void addEntry(void* key, void* value, SymTable* S);
Entry* Search(void* key, SymTable* S);

#endif // __TEST_H__

