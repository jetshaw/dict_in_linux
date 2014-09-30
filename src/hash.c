/*
 * file : hash.c
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#include "hash.h" 
#include"common.h"

//哈希节点上的数据域的打印函数
void print_data_struct(struct data_struct *data,common_callback_t print_func)
{
    __DEBUG;    
    if( data==NULL )
    {
        printf("print: data==NULL\n");
        return;
    }
    int k, i=data->cnt;
    char** lines=(char **)data->lines;
    for(k=0;k<i;k++)
        print_func(lines[k]);
    return;
}

//哈希数据仓库的初始化
int hash_init(struct data_house*house,p_common_callback_t generate_key_func,p_common_callback_t assemble_data_func)
{
    if(house==NULL)
        return -1;
    memset(house,0,sizeof(struct data_house));
    house->generate_key_func = generate_key_func;
    house->assemble_data_func = assemble_data_func;
}

//从业务数据中提取key值
char* generate_key_for_data(p_common_callback_t func,void *data)
{
    if( data ==NULL )return NULL;
    return(func(data));
    return NULL;
}

//加载文本文件，丰富哈希数据仓库
int hash_load_from_file(char* filename,struct data_house* house)
{
    __DEBUG;    
    if(filename == NULL)
    {
        printf("the filename is NULL\n");
        return -1;
    }
    if(house == NULL)
    {
        printf("the hash table is NULL\n");
        return -1;
    }
    FILE *fp =NULL;
    void *format_data=NULL;
    char buf[LINE_LEN_MAX];
    fp=fopen(filename, "r");
    assert(NULL != fp);
    while(NULL != fgets(buf, LINE_LEN_MAX, fp))
    {
        if(house->assemble_data_func != NULL)
            format_data = house->assemble_data_func(buf);
        else
        {
            format_data = malloc(LINE_LEN_MAX*sizeof(char));
            assert(format_data != NULL);
            memcpy(format_data,buf,LINE_LEN_MAX*sizeof(char));
        }
        if(NULL == format_data)continue;
        if( -1 == hash_insert(format_data,house) )
            continue;
    }
    return 0;
}

//将数据结构插入哈希数据仓库
int hash_insert(void *data,struct data_house* house)
{
    if(data==NULL)
        return -1;
    char *key = NULL;
    if(house->generate_key_func == NULL)return -1;
    key = generate_key_for_data(house->generate_key_func,data);
    if(key==NULL)
        return -1;
    struct hash_table *tmp = NULL;
    tmp =&house->top_table;
    int i=0;
    int index;
    while(i<strlen(key))
    {
        __DEBUG;
        hash(key[i],index);
        if(index == -1 )break;
        /*printf("i=%d index=%d line=%s\n",i,index,line);*/
        /*if(line[i+1]!=' ' && line[i+1]!= '\n' && line[i+1]<=122 && line[i+1]>32)*/
        if(key[i+1]!='\0')
        {
            if( tmp->arr[index].sub_table==NULL )
            {
                tmp->arr[index].sub_table = malloc(sizeof(struct hash_table));
                assert(NULL != tmp->arr[index].sub_table );
                memset(tmp->arr[index].sub_table,0,sizeof(struct hash_table));
                mem_manager_insert(&house->mem_manager,tmp->arr[index].sub_table);
            }
            tmp = tmp->arr[index].sub_table;
        }
        else
        {
            house->words_cnt++;
            tmp->arr[index].data.cnt++;
            tmp->arr[index].data.lines = realloc(tmp->arr[index].data.lines,tmp->arr[index].data.cnt*sizeof(void*)); 
            assert(NULL != tmp->arr[index].data.lines);
            tmp->arr[index].data.lines[tmp->arr[index].data.cnt-1]=data;
            mem_manager_insert(&house->mem_manager,data);
            break;
        }
        i++;
    }
    __DEBUG;
    free(key);
}

//从哈希数据仓库中查找Key对应的业务数据，并返回装有业务数据的结构指针data_struct×
struct data_struct *hash_get(char* key,struct data_house* house)
{
    if(house==NULL)
        return NULL;
    if(key==NULL)
        return NULL;
    int i=0,index=-1;
    struct data_struct* ret=NULL;
    struct hash_table *tmp=&house->top_table;
    /*printf("strlen(%s)=%d\n",key,(int)strlen(key)); */
    while(i<strlen(key)&&key[i]!='\n')
    {
        hash(key[i],index);
        /*printf("index=%d key=%s key[%d]=%c\n",index,key,i,key[i]);*/
        if(key[i+1]!='\0'&&key[i+1]!='\n')
        {
            if(tmp->arr[index].sub_table==NULL)
            {
                printf("the sub_table is NULL\n");
                break;
            }
            tmp = tmp->arr[index].sub_table;
            i++;
        }
        else
        {
            if(tmp->arr[index].data.cnt==0)
            {
                printf("cnt=0\n");
                break;
            }
            ret = &(tmp->arr[index].data);
            break;
        }
    }
    return ret;
}

//清空哈希数据仓库
int clean_data_house(struct data_house* house)
{
    if(house==NULL)
        return -1;    
    return mem_manager_clean(&house->mem_manager);
}
