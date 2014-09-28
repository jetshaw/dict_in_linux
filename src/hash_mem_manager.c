/*
 * file : hash.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#include"hash_mem_manager.h"
#include"common.h"
int mem_manager_init(struct hash_mem_manager* mem_manager)
{
__DEBUG;
    mem_manager->ptr=NULL;
    mem_manager->cnt_ptr = 0;
}

int mem_manager_insert(struct hash_mem_manager* mem_manager, void* ptr)
{
    if( ptr==NULL || mem_manager==NULL)return -1;
    mem_manager->cnt_ptr++;
    mem_manager->ptr = realloc(mem_manager->ptr,sizeof(void*)*mem_manager->cnt_ptr);
    assert(mem_manager->ptr != NULL);
    mem_manager->ptr[mem_manager->cnt_ptr-1]= ptr;
    return 0;
}

int mem_manager_delete(struct hash_mem_manager* mem_manager, void* ptr)
{
    return 0; 
}

int mem_manager_clean(struct hash_mem_manager* mem_manager)
{
    if( mem_manager==NULL)
        return -1;
    int i;
    for(i=0;i<mem_manager->cnt_ptr;i++)
    {
        if( *(mem_manager->ptr+i)!=NULL )
        {
            free(*(mem_manager->ptr+i));
        }
    }
    return 0;
}

