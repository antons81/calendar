//
//  main.c
//  calendar
//
//  Created by flutesa on 19.07.12.
//  Copyright (c) 2012 Alexandra Burkova. All rights reserved.
//


#include <stdio.h>  //стандартная библиотека ввода-вывода
#include <time.h>   //содержит функции и типы для работы с датой и временем
#include <locale.h> //стандартная библиотека для работы с локализацией
#include <string.h> //стандартная библиотека для работы со строками

int main() {   
    time_t ctime;   //переменная, в которой будет храниться календарное время
    struct tm * timestr;    
    int year, month, day, wday, sl, i, j, q;
    char *locale;   //переменная для считывания локализации
    char mname[10]; //для хранения наименования месяца в текущей локали
    char wname[20]; //для хранения сокращённых названий дней недели в текущей локали
    year = 9999; month = 12; //предопределение переменных для отображения подсказок в нужный момент
    
    
    locale = setlocale(LC_ALL, "");     //получение текущей локализации в системе
    
    if (!strncmp(locale, "bg_BG", 4) || !strncmp(locale, "ca_ES", 4) || !strncmp(locale, "cs_CZ", 4) || !strncmp(locale, "da_DK", 4) || !strncmp(locale, "de_AT", 4) || !strncmp(locale, "de_CH", 4) || !strncmp(locale, "de_DE", 4)|| !strncmp(locale, "el_GR", 4) || !strncmp(locale, "en_CA", 4) || !strncmp(locale, "en_GB", 4) || !strncmp(locale, "es_ES", 4) || !strncmp(locale, "et_EE", 4) || !strncmp(locale, "eu_ES", 4) || !strncmp(locale, "fi_FI", 4) || !strncmp(locale, "fr_BE", 4) || !strncmp(locale, "fr_CA", 4) || !strncmp(locale, "fr_CH", 4) || !strncmp(locale, "fr_FR", 4) || !strncmp(locale, "hr_HR", 4) || !strncmp(locale, "hu_HU", 4) || !strncmp(locale, "hy_AM", 4) || !strncmp(locale, "is_IS", 4) || !strncmp(locale, "it_CH", 4) || !strncmp(locale, "it_IT", 4) || !strncmp(locale, "kk_KZ", 4) || !strncmp(locale, "lt_LT", 4) || !strncmp(locale, "nl_BE", 4) || !strncmp(locale, "nl_NL", 4) || !strncmp(locale, "no_NO", 4) || !strncmp(locale, "pl_PL", 4) || !strncmp(locale, "pt_PT", 4) || !strncmp(locale, "ro_RO", 4) || !strncmp(locale, "ru_RU", 4) || !strncmp(locale, "sk_SK", 4) || !strncmp(locale, "sl_SI", 4) || !strncmp(locale, "sr_YU", 4) || !strncmp(locale, "sv_SE", 4) || !strncmp(locale, "tr_TR", 4) || !strncmp(locale, "uk_UA", 4)) 
        sl = 1;     //в случае, если локаль - страна, где пн - начало недели, то метка локализации = 1
    
    else if (!strncmp(locale, "en_AU", 4) || !strncmp(locale, "en_US", 4) || !strncmp(locale, "be_BY", 4) || !strncmp(locale, "zh_CN", 4) || !strncmp(locale, "am_ET", 4) || !strncmp(locale, "zh_HK", 4) || !strncmp(locale, "en_IE", 4) || !strncmp(locale, "he_IL", 4) || !strncmp(locale, "ja_JP", 4) || !strncmp(locale, "ko_KR", 4) || !strncmp(locale, "en_NZ", 4) || !strncmp(locale, "zh_TW", 4) || !strncmp(locale, "pt_BR", 4) || !strncmp(locale, "af_ZA", 4)) 
        sl = 0;     //в случае, если локаль - страна, где вс - первый день недели, то метка локализации = 0
    else {locale = "en_US"; sl = 0;}    //если локаль не определена, то значение по умолчанию
    
    do {    //запрос месяца и года до тех пор, пока не будут получены корректные данные
        if (year<1970) printf("Календарь можно просмотреть с 1970 года\n");     //подсказка пользователю в случае ошибки в указании года
        if (!(month>0 && month<13)) printf("Примечание: 1 - январь ... 12 - декабрь\n");    //подсказка пользователю в случае ошибки при указании месяца
        printf("Введите месяц и год в формате mm.YYYY ");   //форматированный вывод
		scanf("%d.%d", &month, &year);  //запись значений переменных int в десятичном формате
        printf("\n");
    } while (!(month>0 && month<13 && year>=1970));     //месяцев строго 12 и год с 1970, так как системное время все реализации UNIX отсчитывают с 1 января 1970    
    
    time(&ctime);   //функция возвращает текущее календарное время
    timestr = localtime(&ctime);    //наполнение структуры данными о времени в форме, разделённой на компоненты
    timestr->tm_year = year-1900;   //корректировка текущего года
    timestr->tm_mon = month-1;  //корректировка текущего месяца
    day = timestr->tm_mday;     //фиксирование текущего дня для выделения скобками    
    
    printf("\n");
    
    if (sl == 1) {
        setlocale(LC_ALL, locale);
        
        for(q=0; q<=6; q++) {   //формирование заголовка календаря с сокращёнными названиями дней недели, если первый - пн
            timestr -> tm_wday = sl + q;
            if ((sl + q) == 7) timestr -> tm_wday = 0;
            strftime(wname, 20, "  %a", timestr);
            printf("%4s", wname);
        }
    }        
    else {
        setlocale(LC_ALL, locale);
        
        for(q=0; q<=6; q++) {   //формирование заголовка календаря с сокращёнными названиями дней недели, если первый - вс
            timestr -> tm_wday = sl + q;
            strftime(wname, 20, " %a", timestr);
            printf("%4s", wname);
        }
    }
    
    printf("\n");
    printf("______________________________\n\n");
    
    for (i=1; i<32; i++) {      //заполнение календаря датами
        timestr->tm_mday = i;   //вызов функции, возвращающей календарный эквивалент времени, которое задано пользователем
        mktime(timestr);    //дню месяца в структуре времени присваивается текущий в цикле номер дня
        wday = timestr->tm_wday;    //фиксирование дня недели для отступа первого числа в месяце
        
        if (timestr->tm_mon == month)   //факт завершения чисел в месяце и выход из цикла
            break;
        
        if (i == 1 && sl == 1 && wday == 0) {   //реализация отступа первого числа месяца в соответствии с днём пн-недели
            for (j=1; j<=6; j++)    //если день недели воскресение (wday==0) реализовать 6 отступов
                printf("    ");
        } else if (i == 1 && sl == 1 && wday != 0) {
            for (j=1; j<=(wday-1); j++)
                printf("    ");
        }
        
        if (i == 1 && sl == 0) {    //реализация отступа первого числа месяца в соответствии с днём вс-недели
            for (j=1; j<=(wday); j++) 
                printf("    ");
        }
        
        if (timestr->tm_mday == day && timestr->tm_mday < 10) printf("  [%d]", timestr->tm_mday);   //если число текущее и одноразрядное - выделить скобками с дополнительным отступом
        else if (timestr->tm_mday == day) printf(" [%d]", timestr->tm_mday);    //если число текущее и двухразрядное (другого уже быть не может) - выделить скобками
        else if (sl == 1 && timestr->tm_mday == day+1 && (timestr->tm_mday-1 <= 8 || timestr->tm_mday-1 > 8) &&
                 (timestr->tm_wday == 0 || timestr->tm_wday-1 == 1 || timestr->tm_wday-1 == 2 || timestr->tm_wday-1 == 3 || timestr->tm_wday-1 == 4 || timestr->tm_wday-1 == 5 || timestr->tm_wday-1 == 6 || timestr->tm_wday == 6)) printf("%3d", timestr->tm_mday);    //если число следует за текущим в пн-неделе, в зависимости от разрядности и дня недели - сокращённый отступ
        else if (sl == 0 && timestr->tm_mday == day+1 && (timestr->tm_mday-1 <= 8 || timestr->tm_mday-1 > 8) &&
                 (timestr->tm_wday == 1 || timestr->tm_wday == 2 || timestr->tm_wday == 3 || timestr->tm_wday == 4 || timestr->tm_wday == 5 || timestr->tm_wday == 6)) printf("%3d", timestr->tm_mday);     //если число следует за текущим в вс-неделе, в зависимости от разрядности и дня недели - сокращённый отступ
        else printf("%4d", timestr->tm_mday);   //если число не текущее и не следует за текущим - стандартные отступы                    
        
        if (timestr->tm_wday == 0 && sl == 1)   //факт завершения пн-недели и перевод курсора на новую строку
            printf("\n");
        if (timestr->tm_wday == 6 && sl == 0)   //факт завершения вс-недели и перевод курсора на новую строку
            printf("\n");
    }
    
    //формирование подписи под календарём
    strftime(mname, 70, "%B", timestr);     //получение названия месяца
    printf("\n______________________________\n");
    printf("\n  %d %s %d\n\n", day, mname, year);   //текущий день, и указанные пользователем месяц и год
    
    return 0;
}