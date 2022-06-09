#include "allocator.h"

#include<stdlib.h>

int AlignSize(int sz, int n){
    return (sz + n - 1) & -n;
}

void* FastMalloc(int sz){
    unsigned char* data = (unsigned char*) malloc(sz);
    return data;
}
