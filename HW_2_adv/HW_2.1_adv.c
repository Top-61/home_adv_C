/*Описана структура данных
typedef struct list {
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

Требуется реализовать только одну функцию, которая в данном списке
находит адрес блока памяти занимающий больше всего места.
 Адрес хранится в поле address, поле size - соответствующий размер
  данного блока. Если список пустой, то функция должна возвращать NULL.
  Если есть несколько таких блоков, то вернуть адрес любого из них.
  Прототип функции:
void * findMaxBlock(list *head)
*/

#include <stdio.h>

typedef struct list
{
    void *address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

void *findMaxBlock(list *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    list *MAX_adr = head;
    head = head->next;
    while (head!=NULL)
    {
        if (head->size > MAX_adr->size)
        {
           MAX_adr = head;
        }
        head = head->next;
    }
    return MAX_adr->address;
}
