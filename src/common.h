/*
 * file : common.h
 * author : xiaozai
 * 28-9-2014
 * email: xiaozai05@163.com
 * */

#ifndef __COMMON__H__
#define __COMMON__H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<dirent.h>
#include<assert.h>

#ifdef DEDBG
#define __DEBUG printf("%s %d\n",__func__,__LINE__) 
#else
#define __DEBUG
#endif

#endif
