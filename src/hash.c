/*
 * file : hash.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#include "hash.h" 
#include"common.h"

void print_data_struct(struct data_struct *data)
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
        printf("result: %s\n",lines[k]);
    return;
}

int hash_init(struct data_house*house)
{
    if(house==NULL)
        return -1;
    memset(house,0,sizeof(struct data_house));
}

int hash_load(char* filename,struct data_house* house)
{
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
    char *line=NULL;
    struct hash_table *tmp = NULL;
    char buf[LINE_LEN_MAX];
    fp=fopen(filename, "r");
    assert(NULL != fp);
    int i;
    int index;
    while(NULL != fgets(buf, LINE_LEN_MAX, fp))
    {
        if(buf[0]<'A'||buf[0]>'z'||(buf[0]>'Z'&&buf[0]<'a'))continue;
        line = malloc(strlen(buf)+1);
        assert(NULL != line);
        strcpy(line,buf);
        i=0;
        tmp =&house->top_table;
        while(i<strlen(line))
        {
            hash(line[i],index);
            /*printf("i=%d index=%d line=%s\n",i,index,line);*/
            if(line[i+1]!=' ' && line[i+1]!= '\n' && line[i+1]<=122 && line[i+1]>32)
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
                tmp->arr[index].data.lines[tmp->arr[index].data.cnt-1]=line;
                mem_manager_insert(&house->mem_manager,line);
                break;
            }
            i++;
        }
    }
    printf("house->words_cnt=%llu\n",house->words_cnt);
}

struct data_struct *hash_get(char* key,struct data_house* house)
{
    if(house==NULL)
        return NULL;
    if(key==NULL)
        return NULL;
    int i=0,index=-1;
    struct data_struct* ret=NULL;
    struct hash_table *tmp=&house->top_table;
    printf("strlen(%s)=%d\n",key,strlen(key)); 
    while(i<strlen(key)&&key[i]!='\n')
    {
        hash(key[i],index);
        printf("index=%d key=%s key[%d]=%c\n",index,key,i,key[i]);
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

int clean_data_house(struct data_house* house)
{
    if(house==NULL)
        return -1;    
    return mem_manager_clean(&house->mem_manager);
}
