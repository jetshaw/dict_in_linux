/*
 * file : hash.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#ifndef __HASH_H____
#define __HASH_H____
#include"hash_mem_manager.h"
#define LINE_LEN_MAX 512
#define HASH_LEN 74 //"A-Z" "a-z" "-",...


//哈希函数，将key哈希成val
#define hash(key,val)  {    if((key>='A'&&key<='Z')||(key>='a'&&key<='z'))\
                            {\
                                val = ((key>96)?(key-'a'+26):(key-'A'));\
                            }\
                            else\
                            {\
                                switch (key)\
                                {\
                                    case '[':val=73;break;\
                                    case ']':val=72;break;\
                                    case '%':val=71;break;\
                                    case ',':val=70;break;\
                                    case '9':val=69;break;\
                                    case '8':val=68;break;\
                                    case '7':val=67;break;\
                                    case '6':val=66;break;\
                                    case '5':val=65;break;\
                                    case '4':val=64;break;\
                                    case '3':val=63;break;\
                                    case '2':val=62;break;\
                                    case '1':val=61;break;\
                                    case '0':val=60;break;\
                                    case 39 :val=59;break;\
                                    case 41 :val=58;break;\
                                    case 40 :val=57;break;\
                                    case 46 :val=56;break;\
                                    case '&':val=55;break;\
                                    case '/':val=53;break;\
                                    case 96 :val=54;break;\
                                    case '-':val=52;break;\
                                    default: val=-1;break;\
                                }\
                            }\
                        }
typedef void * (p_common_callback_t)(void *);
typedef void (common_callback_t)(void *);
//哈希节点上的数据域结构
struct data_struct
{
    void** lines;//指针数组，指向的是实际业务数据的地址
    int cnt;//指针的数量
};

//哈希节点上的数据域的打印函数
void print_data_struct(struct data_struct *data,common_callback_t func);
//基本哈希表，在下边有定义
struct hash_table;

//哈希节点
struct hash_node
{
    struct data_struct data;//哈希节点上的数据域
    struct hash_table *sub_table;//哈希节点的下一级哈希表的地址
    int has_sub_table;//拥有下一级哈希表时的拥有标示，置1为真
};

//基本哈希表，其实质就是由上边定义的哈希节点组成的数组，数组长度的来历参考宏定义中的哈希函数hash(x)
struct hash_table
{
    struct hash_node arr[HASH_LEN];//哈希节点数组
};

//由所有哈希表组成的数据仓库
struct data_house
{
    struct hash_table top_table;//数据仓库的顶级哈希表
    unsigned long long int words_cnt;//数据仓库中的业务数据的总条数
    struct hash_mem_manager mem_manager;//哈希内存的管理器结构
    p_common_callback_t *generate_key_func;//产生key的回调函数 
    p_common_callback_t *assemble_data_func;//组装业务数据结构的回调函数
};

//哈希数据仓库的初始化,必要条件：将产生key的回调函数，组装业务数据结构的回调函数赋值
int hash_init(struct data_house* house,p_common_callback_t generate_key_func,p_common_callback_t assemble_data_func);

//从哈希数据仓库中查找Key对应的业务数据，并返回装有业务数据的结构指针data_struct*
struct data_struct *hash_get(char*key,struct data_house* house);

//从业务数据中提取key值
char* generate_key_for_data(p_common_callback_t * callback,void *data);

//加载文本文件，丰富哈希数据仓库
int hash_load_from_file(char* filename,struct data_house* house);

//将数据结构插入哈希数据仓库
int hash_insert(void * data,struct data_house* house);

//清空哈希数据仓库
int clean_data_house(struct data_house* house);
#endif //__HASH_H____
