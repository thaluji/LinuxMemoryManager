#include<stdio.h>
#include<stdlib.h>
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
        MAP_ANON | MAP_PRIVATE,
        -1,0);
    if (vm_page == MAP_FAILED) {
    printf("mmap failed: ");
    return NULL;
}
    memset(vm_page,0,units * SYSTEM_PAGE_SIZE);
    return (void *)vm_page;

}
static void mm_return_vm_page_to_kernel(void *vm_page,int units){
    if(munmap(vm_page,units * SYSTEM_PAGE_SIZE) ){
        printf("munmap failed\n");
    }
}
int main(){
    mm_init();
    void *vm_page = mm_get_new_vm_page_from_kernel(1);
    printf("vm_page = %p\n",vm_page);
    mm_return_vm_page_to_kernel(vm_page,1);
    return 0;
}

