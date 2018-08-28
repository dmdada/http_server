#include"cgi_base.hpp"
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h> 
typedef struct today
{
	int day;
	int month;
	int year;
} today;

int day_cankao[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
};
char *week[] =
{
	"Sun", "Mon", "Tue", "Wen", "Thu", "Fir", "Sat"
};
struct tm *todayuse;//struct tm定义c语言中time的结构体  
today today_current;
int getweekday(today today_usenow)
{
	// w = y + [y/4] + [ c/4 ] – 2c+ [13 * (m+1) / 5] + d – 1  
	//其中，c是年份的前两位，y是年份的后两位，m是月份，d是日期，这里需要注意的是，如果是1月和2月，c和y需要按照上一年来取值。  
	int w = 0;

	int year = today_usenow.year;
	int month = today_usenow.month;
	if (today_usenow.month == 1 || today_usenow.month == 2)
	{
		month += 12;
		year--;
	}
	int y = year % 100;
	int c = year / 100;
	int m = month;

	w = y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + today_usenow.day - 1;
	while (w<0)
	{
		w += 7;
	}
	return (w % 7);

}
int is_leap(int year)
{

	if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
	{
		return 1;
	}
	else
		return 0;
}
int  getmonthdays(int year, int month)
{
	return day_cankao[is_leap(year)][month];
}


void print_calendar(today today_usenow)
{
	printf("<html>------------------------------------------<br></html>");
	printf("<html>Sun&ensp;&ensp;Mon&ensp;&ensp;Tue&ensp;Wen&ensp;Thu&ensp;&ensp;Fir&ensp;&ensp;Sat</html>");
	int firstday = 0;
	today today_usehere = today_usenow;
	today_usehere.day = 1;
	int day = getweekday(today_usehere);//日期前  
	//int  daysuseafter  
	int days = getmonthdays(today_usenow.year, today_usenow.month);//月总数  
    int i=0;
	int daysbefore = 0;
	if ((today_usenow.month - 1) == 0)
	{
		//现在为1月，去年的十二月份  
		daysbefore = getmonthdays(today_usenow.year - 1, 12);
	
	}
	else
	{
		daysbefore = getmonthdays(today_usenow.year, today_usenow.month - 1);
	}
	int daysbefoeit = daysbefore - day + 1;
	printf("<html><br></html>");
	int count = 1;
	if (day == 0)
	{
		daysbefoeit -= 7;
		for (i = 0; i<day + 7; i++)
		{

			printf("<html>%d&emsp;</html>", daysbefoeit);
			daysbefoeit++;

		}
		printf("<html><br></html>");
		count = 7;
	}
	else
	{
		for (i = 0; i<day; i++)
		{
			printf("<html>&ensp;%d&emsp;</html>", daysbefoeit);
			daysbefoeit++;
		}
		count = day;
	}
	int m = 1;
	for (i = 0; i <= 6 - day; i++)
	{
		if (m<10)
		{
			printf("<html>&emsp;%d&emsp;</html>", m);
		}
		else
		{


			printf("<html>%d&emsp;</html>", m);
		}

		m++;
	}
	printf("<html><br></html>");
	if (day == 0)
	{
		count = 14;
	}
	else
	{
		count = 7;
	}
	int hang = 0;
	while (m <= days)
	{
		if (m<10)
		{
			printf("<html>&emsp;%d&emsp;</html>", m);
		}
		else
		{


			printf("<html>&ensp;%d&emsp;</html>", m);
		}
		hang++;
		if (hang == 7)
		{
			printf("<html><br></html>");
			hang = 0;
		}

		m++;
	}
	if (day == 0)
	{
		count = days + 7;
	}
	else
	{
		count = day + days;
	}
	int newmonth = 1;
  int j=0;
	for (j = hang; j<7; j++)
	{

		if (newmonth<10)
		{
			printf("<html>&emsp;%d&emsp;</html>", newmonth);//1
		}
		else
		{


			printf("<html>%d&emsp;</html>", newmonth);
		}

		newmonth++;
	}
	printf("<br>");
	count = count + 7 - hang;
	for (j = 0; j< 42 - count; j++)
	{
		if (newmonth<10)
		{
			printf("<html>&emsp;%d&emsp;</html>", newmonth);
		}
		else
		{


			printf("<html>&emsp;%d&emsp;</html>", newmonth);
		}
		newmonth++;
	}


}
int main()
{
	time_t timep;
	struct tm *p;
	time(&timep);
	p = localtime(&timep); //此函数获得的tm结构体的时间，是已经进行过时区转化为本地时间     
	today_current.year = 1900 + p->tm_year;
	today_current.month = 1 + p->tm_mon;
	today_current.day = p->tm_mday;
	today use = today_current;
	printf("<head><meta http-equiv=\"content-Type\" content=\"text/html;charset=utf-8\"></head>""<html>当前时间为：</html>");
	printf("<html>%d</html>", 1900 + p->tm_year);/*获取当前年份,从1900开始，所以要加1900*/
	printf("<html>-%d</html>", 1 + p->tm_mon);/*获取当前月份,范围是0-11,所以要加1*/
	printf("<html>-%d </html>", p->tm_mday);/*获取当前月份日数,范围是1-31*/
	printf("<html>%d:</html>", p->tm_hour);/*获取当前时,这里获取西方的时间,刚好相差八个小时*/
	printf("<html>%d:</html>", p->tm_min); /*获取当前分*/
	printf("<html>%d</html>", p->tm_sec); /*获取当前秒*/
	printf("<head><meta http-equiv=\"content-Type\" content=\"text/html;charset=utf-8\"></head>""<html>&emsp;&emsp;今年已经过去%d天<br></html>", p->tm_yday); /*从今年1月1日算起至今的天数，范围为0-365*/
	int a=2017, b=5;
	fprintf(stderr, "CGI-Calendar.c\n");
	//1.调用封装好的函数，获取相应参数
	char buf[4 * 1024] = { 0 };

	int ret = GetQueryString(buf);
	if (ret == 0){
		fprintf(stderr, "[CGI]GetQueryString failed\n");
		return 1;
	}
	
	sscanf(buf, "a=%d&b=%d", &a, &b);
	fprintf(stderr, "[CGI-test]a=%d,b=%d\n", a, b);
	use = today_current;
	if (a == 0)
	{
		printf("<html>您已经退出系统</html>");
		
	}
	                use.year  = a;
			use.month = b;
			if (use.month > 12)
			{
			  printf("<head><meta http-equiv=\"content-Type\" content=\"text/html;charset=utf-8\"></head>""<h1>月份错误，请输入1-12月</h1>");
                          return 0;
			}
			printf("<head><meta http-equiv=\"content-Type\" content=\"text/html;charset=utf-8\"></head>""<html>&emsp;&emsp;&emsp;&emsp;&emsp;%d 年 %d 月 <br></html>", use.year, use.month); 
			print_calendar(use);
			printf("<html><br>------------------------------------------<br></html>");
	return 0;
}
