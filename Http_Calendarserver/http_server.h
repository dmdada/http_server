#include<stdio.h>
#include<memory.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/wait.h>
#include<strings.h>
#include<sys/stat.h>
#include<sys/sendfile.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX 10240
#define SIZE 10240
 pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct Request{
  char first_line[MAX];//首行
  //这里忽略不管首行中的版本
  char * Method;//首行中的方法
  char * url;
  char *url_path;
  char *query_string;
  int content_length;//Headler中的content_length,
  // 为了简单，这里不展开其他headler,如果要展开的话，可以考虑哈希表
}Request;

