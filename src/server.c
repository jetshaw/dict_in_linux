/*
 * file : hash.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#include"common.h"
#include"hash.h"
#define TXT_FILE_PATH "../conf"
#define FILENAME_LEN 128
#define WORD_SIZE 64
#include"business_data.h"
//服务循环，接受网络和本地的客户端情求并返回查询结果
void service_loop(struct data_house* house)
{

}

//测试数据仓库的函数
void test_data_house(struct data_house* house)
{
    __DEBUG;
    char buf[WORD_SIZE]={0};
    struct data_struct *tmp=NULL;
    while(1)
    {
    __DEBUG;
        printf("input:");
        memset(buf,0,WORD_SIZE);
        fgets(buf,WORD_SIZE,stdin);
        /*gets(buf);*/
        if(buf[0]=='\n')
            break;
        tmp = hash_get(buf,house);
        print_data_struct(tmp,print_data);
    }
    return;
}

int main(int argc,char** argv)
{
    if(argc > 2)
        return -1;
    char filename[FILENAME_LEN]={0};
    char txtdir[FILENAME_LEN]={0};

    if(1==argc)
        strcpy(txtdir,TXT_FILE_PATH);
    else
        strcpy(txtdir,argv[1]);

    //创建哈希数据仓库
    struct data_house house;
    assert(-1 != hash_init(&house));
    printf("txtdir=%s\n",txtdir);
    DIR *dirp = opendir(txtdir);
    assert(dirp!=NULL);
    struct dirent *dp=NULL;
    char fullfilename[FILENAME_LEN]={0};
    while(NULL != (dp=readdir(dirp)))
    {
    __DEBUG;
        if((dp->d_type != DT_REG)||(strcmp(".",dp->d_name)==0)||strcmp("..",dp->d_name)==0)
            continue;
        printf("filename=%s\n",dp->d_name);
        strcpy(fullfilename,txtdir);
        strcat(fullfilename,"/");
        strcat(fullfilename,dp->d_name);
        hash_load_from_file(fullfilename,&house,assemble_data);
    }
#if 1 
    //在本机上测试哈希数据仓库
    test_data_house(&house);
#else
    //进入服务循环，为网络和本地的客户端提供翻译服务
    service_loop(&house);
#endif
    //清空数据仓库
    clean_data_house(&house);
    return 0;
}
