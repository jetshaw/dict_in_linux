/*
 * file : hash.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */
#ifndef __HASH_MEM_MANAGER_XZ__
#define __HASH_MEM_MANAGER_XZ__
//哈希内存的管理器结构，即一个指针指向一个线性表，这个线性表里的元素全是需要处理的指针，只限于动态分配的指针
typedef struct hash_mem_manager
{
    void ** ptr;//指针数组的指针
    int cnt_ptr;//指针数组的长度
} hash_memory_manager_t;
//初始化哈希内存的管理器
int mem_manager_init(struct hash_mem_manager* mem_manager);
//将需要用哈希内存管理器来管理的指针插入到这个哈希望内存管理器当中
int mem_manager_insert(struct hash_mem_manager* mem_manager, void* ptr);
//暂时没有实现mem_manager_delete这个函数，因为现在看来对整个哈希内存里的单个数据单元进行单独释放没有必要
int mem_manager_delete(struct hash_mem_manager* mem_manager, void* ptr);
//释放哈希内存管理器中管理的所有指针指向的内存。并将该管理器置于初始化状态。
int mem_manager_clean(struct hash_mem_manager* mem_manager);

#endif
