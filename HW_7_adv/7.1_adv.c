/* Дана строка, состоящая из английских букв и пробелов.
 * В конце строки символ точка. Все слова разделены одним пробелом.
 * Необходимо составить из слов односвязный список и упорядочить по алфавиту.
Список необходимо удалить в конце программы. Для сравнение строк можно
использовать strcmp. Необходимо использовать данную структуры организации списка.

struct list
{
   char word[20];
   struct list *next;
}

Необходимо реализовать односвязный список и обслуживающие его функции.
 add_to_list
 swap_elements
 print_list
 delete_list
Формат ввода:
Строка из английских символов 'a'-'z' и пробелов.
В конце строки символ '.'. Длинна строки не более 1000 символов.
Формат вывода:
Упорядоченные по алфавиту слова.

Пример №1
Данные на входе:        efg abcd zzz.
Данные на выходе:   abcd efg zzz
Пример №2
Данные на входе:        fffff kkkkkk a.
Данные на выходе:   a fffff kkkkkk
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list
{
    char word[20];
    struct list *next;
};

void add_to_list(struct list **head, const char *word)
{
    struct list *new_order = (struct list *)malloc(sizeof(struct list));
    strcpy(new_order->word, word);
    new_order->next = *head;
    *head = new_order;
}

void swap_elements(struct list *ch1, struct list *ch2)
{
    char tmp[20];
    strcpy(tmp,ch1 ->word);
    strcpy(ch1->word, ch2->word);
    strcpy(ch2->word, tmp);
}

void sort_list(struct list *head)
{
    struct list *current, *next_order;
    int swap;
    if (head == NULL)
    {
        return;
    }
    do
    {
        swap = 0;
        current = head;
        while (current->next)
        {
            next_order = current->next;
            if (strcmp(current->word, next_order->word) > 0)
            {
                swap_elements(current, next_order);
                swap = 1;
            }
            current = next_order;
        }
    } while (swap);
}

void print_list(struct list *head)
{
    struct list *current = head;
    int first = 1;
    while (current)
    {
        if (!first)
        {
            printf(" ");
        }
        printf("%s", current->word);
        first = 0;
        current = current->next;
    }
    printf("\n");
}

void delete_list(struct list *head)
{
    struct list *current = head;
    struct list *next_order;
    while (current != NULL)
    {
        next_order = current->next;
        free(current);
        current = next_order;
    }
}

int main(void)
{
    struct list *head = NULL;
    char input[1001];
    char *word;
    fgets(input, sizeof(input), stdin);
    int len = strlen(input);
    if (input[len - 1] == '\n')
    {
        input[len - 1] = '\0';
        len--;
    }
    if (input[len - 1] == '.')
    {
        input[len - 1] = '\0';
    }
    word = strtok(input, " ");
    while (word)
    {
        add_to_list(&head, word);
        word = strtok(NULL, " ");
    }
    sort_list(head);
    print_list(head);
    delete_list(head);
    return 0;
}
