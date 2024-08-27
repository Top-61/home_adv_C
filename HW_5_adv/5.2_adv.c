/* На стандартном потоке ввода задаются две символьные строки,
 разделённые символом перевода строки. Каждая из строк не превышает по
 длине 104. В строках не встречаются пробельные символы.
На стандартный поток вывода напечатайте два числа, разделённых пробелом:
 первое число — длина наибольшего префикса первой строки,
 являющегося суффиксом второй; второе число — наоборот,
 длина наибольшего суффикса первой строки, являющегося префиксом второй.
 Сравнение символов проводите с учётом регистра
(т.е. символы 'a' и 'A' различны).

Пример №1
Данные на входе:
don't_panic
nick_is_a_mastodon
Данные на выходе:   3 3
Пример №2
Данные на входе:
monty_python
python_has_list_comprehensions
Данные на выходе:   0 6
 */


#include <stdio.h>
#include <string.h>

int main(void)
{
    char str1[104], str2[104];
    int pref_value = 0, suf_value = 0;
    scanf("%s""%s", str1, str2);
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    for (int i = 1; i <= len1 && i <= len2; i++)
    {
        if (strncmp(str1, str2 + len2 - i, i) == 0)
        {
            pref_value = i;
        }
    }
    for (int i = 1; i <= len1 && i <= len2; i++) {
        if (strncmp(str1 + len1 - i, str2, i) == 0) {
            suf_value = i;
        }
    }
    printf("%d %d\n", pref_value, suf_value);
    return 0;
}
