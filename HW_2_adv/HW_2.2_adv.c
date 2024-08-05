/*Описана структура данных для хранения информации об использованной памяти:
typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

Требуется реализовать только одну функцию, которая анализирует данный
список и возвращает сколько всего памяти используется. Адрес хранится в
поле address, поле size - соответствующий размер данного блока.
Если список пустой, то функция должна возвращать NULL. Прототип функции:
size_t totalMemoryUsage(list *head)
Загрузите только текст данной функции
*/

#include <stdio.h>

typedef struct list
{
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

size_t totalMemoryUsage(list *head)
{
    if (head == NULL)
    {
        printf("NULL");
        return 0;
    }
    size_t total_mem = 0;
    while (head)
    {
        total_mem += head->size;
        head = head->next;
    }
    return total_mem;
}

