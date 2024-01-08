
#include "subdir.h"
#include <stdio.h>

void subdir_cmd_add_sub(unsigned int *last_empty, unsigned int *count_free, struct Subscriber *subdir_base, char *subdir_list){
    if ((*last_empty) < SUBDIR_SIZE){
        // Данные абонента
        printf("(Max field size: %u symbols)\n", (unsigned)SUBSCRIBER_FIELD_SIZE - 1);
        printf("Name: ");
        fgets(subdir_base[*last_empty].name, SUBSCRIBER_FIELD_SIZE, stdin);
        printf("Second name: ");
        fgets(subdir_base[*last_empty].second_name, SUBSCRIBER_FIELD_SIZE, stdin);
        printf("Tel: ");
        fgets(subdir_base[*last_empty].tel, SUBSCRIBER_FIELD_SIZE, stdin);
        printf("Subscriber code: %u\n", *last_empty);
        // Пометить запись как не пустую
        subdir_list[*last_empty] = 1;
        (*count_free)--;
        // Если элемент был последний, прекратить добавлять
        if ((*count_free) == 0){
            *last_empty = SUBDIR_SIZE;
        // Если элемент был не последний, найти пустой справа
        }else{
            for (int i = (*last_empty) + 1; i < SUBDIR_SIZE; i++){
                if (subdir_list[i] == 0){
                    *last_empty = i;
                    break;
                }
            }
        }
    }else{
        printf("Subscriber directory is full\n");
    }
}

void subdir_cmd_remove_sub(unsigned int *last_empty, unsigned int *count_free, struct Subscriber *subdir_base, char *subdir_list){
    // Ввести код удаляемой записи 
    int index = -1;
    printf("Enter abonent code: ");
    scanf("%d", &index);
    getchar();

    // Проверить границы введённой величины
    if ( (index < 0) || (index >= SUBDIR_SIZE) ){
        printf("Subscriber code out of bounds\n");
        return;
    }

    // Если запись пуста, уведомить пользователя и выйти
    if (subdir_list[index] == 0){
        printf("Subscriber entry is already empty\n");
        return;
    // Если запись не пуста, удалить
    }else{
        // Пометить запись как пустую
        subdir_list[index] = 0;

        // Занулить структуру
        char* ptrByte = (char*)&(subdir_base[index]);
        for (int i = 0; i < sizeof(struct Subscriber); i++){
            *(ptrByte + i) = 0;
        }
        // Сдвинуть минимальный пустой индекс если нужно
        if (index < *last_empty)
            *last_empty = index;
        *count_free++;
        printf("Entry removed\n");
    }
}

void subdir_cmd_find_sub_by_name(struct Subscriber *subdir_base, char *subdir_list){
    char name[SUBSCRIBER_FIELD_SIZE] = {0};
    printf("Name: ");
    fgets(name, SUBSCRIBER_FIELD_SIZE, stdin);

    char match = 0;
    for (int i = 0; i < SUBDIR_SIZE; i++){
        if (subdir_list[i] != 0){
            char find = 1;

            for (int j = 0; j < SUBSCRIBER_FIELD_SIZE; j++){
                if (name[j] != subdir_base[i].name[j]){
                    find = 0;
                    break;
                }
            }

            if (find){
                match = 1;
                printf("\tSubscriber/ code [%-3u]\t", i);
                // Если дальше идут символы новой строки, заменить пробелами
                printf("Name: [");
                for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                    if ((subdir_base[i].name[j] == '\n') || (subdir_base[i].name[j] == '\0'))
                        printf(" ");
                    else
                        printf("%c", subdir_base[i].name[j]);
                printf("]\t");

                printf("Second name: [");
                for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                    if ((subdir_base[i].second_name[j] == '\n') || (subdir_base[i].second_name[j] == '\0'))
                        printf(" ");
                    else
                        printf("%c", subdir_base[i].second_name[j]);
                printf("]\t");

                printf("Tel: [");
                for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                    if ((subdir_base[i].tel[j] == '\n') || (subdir_base[i].tel[j] == '\0'))
                        printf(" ");
                    else
                        printf("%c", subdir_base[i].tel[j]);
                printf("]\n");
            }
            
        }
    }
    if (!match)
        printf("Subscriber not found\n");
}

void subdir_cmd_print_all_entries(struct Subscriber *subdir_base, char *subdir_list){
    for (unsigned int i = 0; i < SUBDIR_SIZE; i++){
        // Выводим данные в одну строку существующие записи
        if (subdir_list[i] != 0){
            printf("\tSubscriber code [%-3u]\t", i);
            // Если дальше идут символы новой строки, заменить пробелами
            printf("Name: [");
            for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                if ((subdir_base[i].name[j] == '\n') || (subdir_base[i].name[j] == '\0'))
                    printf(" ");
                else
                    printf("%c", subdir_base[i].name[j]);
            printf("]\t");

            printf("Second name: [");
            for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                if ((subdir_base[i].second_name[j] == '\n') || (subdir_base[i].second_name[j] == '\0'))
                    printf(" ");
                else
                    printf("%c", subdir_base[i].second_name[j]);
            printf("]\t");

            printf("Tel: [");
            for (int j = 0; j < SUBSCRIBER_FIELD_SIZE - 1; j++)
                if ((subdir_base[i].tel[j] == '\n') || (subdir_base[i].tel[j] == '\0'))
                    printf(" ");
                else
                    printf("%c", subdir_base[i].tel[j]);
            printf("]\n");
        }
    }
}