/*
 基姆拉尔森计算公式
  	 W= (D+2*M+3*(M+1)/5+Y+Y/4-Y/100+Y/400) mod 7 + 1
 公式中的符号含义如下：
     Y：年
     M：月（M大于等于3，小于等于14，即在蔡勒公式中，某年的1、2月要看作上一年的
        13、14月来计算，比如2005年1月1日要看作2004年的13月1日来计算）
     D：日
     W：星期；1-星期一，2-星期二，3-星期三，4-星期四，5-星期五，6-星期六，7-星期日
*/

#include <stdio.h>

char *GetWeekDay(int n);

int WeekNum(int Y, int M, int D);

int print_week() {
    int n;
    int Y, M, D;
    char *weekday;

    printf("输入日期：\n");
    scanf("%d%d%d", &Y, &M, &D);

    n = WeekNum(Y, M, D);
    weekday = GetWeekDay(n);

    printf("%d\n", n);
    printf("%d年%d月%d日是%s\n", Y, M, D, weekday);
}

char *GetWeekDay(int n) {
    char *weekname[] = {
            "Illegal WeekDay!",
            "星期一",
            "星期二",
            "星期三",
            "星期四",
            "星期五",
            "星期六",
            "星期日"
    };

    return (n < 1 ? weekname[0] : weekname[n]);
}

int WeekNum(int Y, int M, int D) {
    if (M == 1 || M == 2) {
        M = M + 12;
        Y = Y - 1;
    }

    return ((D + 2 * M + 3 * (M + 1) / 5 + Y + (Y / 4) - Y / 100 + Y / 400) % 7 + 1);
}