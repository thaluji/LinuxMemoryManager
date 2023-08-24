#include<stdio.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>
static size_t SYSTEM_PAGE_SIZE = 0;
void mm_init(){
    SYSTEM_PAGE_SIZE = getpagesize();
}

static void * mm_get_new_vm_page_from_kernel(int units){
    char *vm_page = mmap(
        0,units * SYSTEM_PAGE_SIZE,
        PROT_READ | PROT_WRITE|PROT_EXEC,
        MAP_ANONYMOUS | MAP_PRIVATE,
        -1,0
    )
}