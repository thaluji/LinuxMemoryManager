#include <stdint.h>
#include <stddef.h> /*for size_t*/
#define MM_MAX_STRUCT_NAME 32
#define ITERATE_PAGE_FAMILIES_BEGIN(vm_page_for_families_ptr, curr)   \
{                                                                     \
    uint32_t count = 0;                                               \
    for(curr = (vm_page_family_t *)&vm_page_for_families_ptr         \
        count != gb_no_of_vm_families_registered;                     \
        count++, curr++){                                             \
        if(count == N_PAGE_FAMILY_PER_VM_PAGE){                       \
            curr = (vm_page_family_t *)((char *)curr +                \
                VM_PAGE_FAMILY_RESIDUAL_SPACE);                       \
            count = 0;                                                \
        }

#define ITERATE_PAGE_FAMILIES_END(first_vm_page_family_ptr, curr)   }}
typedef struct vm_page_family_{
    char struct_name[MM_MAX_STRUCT_NAME];
    uint32_t struct_size;
}vm_page_family_t;
typedef struct vm_page_for_families_{
    struct vm_page_for_families_ * next;
    vm_page_family_t vm_page_family[0];

}vm_page_for_families_t;