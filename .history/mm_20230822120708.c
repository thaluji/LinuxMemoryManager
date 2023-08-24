#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<unistd.h>
#include<sys/mman.h>
static vm_page_for_families_t * first_vm_page_for_families = NULL; // most recent virtual memory page
static size_t SYSTEM_PAGE_SIZE = 0;
void mm_init(){
   SYSTEM_PAGE_SIZE = sysconf(_SC_PAGESIZE);
}

static void * mm_get_new_vm_page_from_kernel(int units){
    char *vm_page = mmap(
        0,units * SYSTEM_PAGE_SIZE,
        PROT_READ | PROT_WRITE|PROT_EXEC,
        MAP_ANON | MAP_PRIVATE,
        -1,0);
    if (vm_page == MAP_FAILED) {
     perror("mmap failed");
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
mm_instantiate_new_page_family(char * struct_name,uint32_t struct_size){
    vm_page_family_t * vm_page_family_curr=NULL;
    vm_page_for_families_t *new_vm_page_for_families = NULL;
    if(struct_size>SYSTEM_PAGE_SIZE){
        printf("struct_size > SYSTEM_PAGE_SIZE\n");
        return;
    }
    if(first_vm_page_for_families == NULL){
        first_vm_page_for_families = mm_get_new_vm_page_from_kernel(1);
        if(first_vm_page_for_families == NULL){
            printf("mm_get_new_vm_page_from_kernel failed\n");
            return;
        }
        first_vm_page_for_families->next = NULL;
        strncpy(first_vm_page_for_families->vm_page_family[0].struct_name,struct_name,MM_MAX_STRUCT_NAME);
        first_vm_page_for_families->vm_page_family[0].struct_size = struct_size;
        first_vm_page_for_families->prev = NULL;
        first_vm_page_for_families->vm_page_family_curr = NULL;
    }
    uint32_t count=0;
    ITERATE_PAGE_FAMILIES_BEGIN(first_vm_page_for_families,vm_page_family_curr){
        if(strncmp(vm_page_Family_curr->struct_name,struct_name,MM_MAX_STRUCT_NAME)!=0){
            count++;
            continue;
        }
        assert(0);
    }ITERATE_PAGE_FAMILIES_END(first_vm_page_for_families,vm_page_family_curr);
    if(count==MAX_FAMILIES_PER_VM_PAGE){
        new_vm_page_for_families = (vm_page_for)
    }

}
int main(int argc,char **argv){
    mm_init();
    printf("SYSTEM_PAGE_SIZE = %ld\n",SYSTEM_PAGE_SIZE);
    void *add = mm_get_new_vm_page_from_kernel(1);
    printf("vm_page = %p\n",add);
    mm_return_vm_page_to_kernel(add,1);
    return 0;
}

