#pragma once 
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>


    //��GET��POST���������ȡ����Ĳ���
    //1.GET��query_string�ж�ȡ
    //1.POST��body�ж�ȡ
    // ��ȡ�Ľ���ͷ��뻺����buf��

  int GetQueryString(char buf[]){
    //1.�ӻ��������ж�ȡ�ķ�����ʲô

  char* method=getenv("REQUEST_METHOD");
  if(NULL == method){
    //��ǰ��CGI�����Ӧ�ı�׼����ѱ��ض��򵽹ܵ�֮��
    //���ⲿ�����ݻᱻ���ص��ͻ���
    //�����ó����ڲ��Ĵ���¶����ͨ�û�
    //����ͨ��stderr��Ϊ������־���ֶ�
    fprintf(stderr,"method==NULL\n");
    return 0;
  }

  //2.�ж������� GET������POST
  //�����GET���ʹӻ����������ȡQUERY_STRING
  //�����POST������Ҫ�ӻ����������ȡCONTENT_LENGC
  
  if(strcasecmp(method,"GET")==0){
    char* query_string=getenv("QUERY_STRING");
    if(query_string == NULL){
      fprintf(stderr,"query_string == NULL\n");
      return 0;
    }
  //������ɺ�buf������������磺a=10&b=20
    fprintf(stderr,"[CGI-GET]query_string:%s\n",query_string);
    strcpy(buf,query_string);
  }
  else{
  //POST
    char* content_length_str=getenv("CONTENT_LENGTH");
    if(NULL == content_length_str){
      fprintf(stderr,"content_length == NULL\n");
      return 0;
    }
    int content_length = atoi(content_length_str);
    int i=0;
    
    fprintf(stderr,"[CGI-POST]body");
    for(;i<content_length;++i){
      fprintf(stderr,"%c",buf[i]);
      read(0,&buf[i],1);
    }
    fprintf(stderr,"\n");
    buf[i]='\0';
    
  }
  return 1;
  
}
