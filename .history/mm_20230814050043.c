#include<stdio.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>
static size_t SYSTEM_PAGE_SIZE = 0;
void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();
}