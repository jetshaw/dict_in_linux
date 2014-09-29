#include"business_data.h"
#include "hash.h"
#include "common.h"

void * generate_key(void * const p_data)
{
    __DEBUG;
    if(p_data == NULL) return NULL;
    char *data = p_data;
    char *ret =NULL;
    int i; 
    if(data[0]<'A'||data[0]>'z'||(data[0]>'Z'&&data[0]<'a'))
        return NULL;
    __DEBUG;
    for(i=0;i<strlen(data);i++)
    {
    __DEBUG;
        if(!(data[i]!='\0'&&data[i]!=' '&&data[i]<127&&data[i]>32))
        {
            /*printf("i=%d data=%s\n ",i,data);*/
            break;
        }
    }
    if(i>0)
    {
    __DEBUG;
        ret = malloc((i+2)*sizeof(char));
        if(ret==NULL)
            return NULL;
        memcpy(ret,data,i);
        ret[i+1]='\0';
    }
    __DEBUG;
    return ret;
}

void print_data(void * const data)
{
    if(data==NULL)return;
    printf("data: %s",(char *)data);
    return;
}

void *assemble_data(void *const data)
{
    if(data==NULL)
        return NULL;
    char *struct_data =NULL;
    struct_data = malloc((strlen((char *)data)+1)*sizeof(char));
    if(struct_data==NULL)
        return NULL;
    strcpy(struct_data,data);
    return struct_data;
}
