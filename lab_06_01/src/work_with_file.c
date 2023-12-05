#include "work_with_file.h"

void file_whoose(FILE **file)
{
    *file = NULL;
    char strk[SIZE_OF_BUF];
    memset(strk, '\0', SIZE_OF_BUF);
    printf("Введите путь к рабочему файлу: ");
    while (*file == NULL)
    {
        if (fgets(strk, SIZE_OF_BUF, stdin) != NULL)
        {
            //мы хоть что-то прочитали, иначе ошибка
            if (strk[0] != '\0')
            {
                //прочитали всю строчку до переноса строки и  заменяем его на конец строки "\0", иначе ошибка
                if (strk[strlen(strk) - 1] == L'\n')
                {
                    strk[strlen(strk) - 1] = '\0';
                    *file = fopen(strk, "r+");
                    if (*file == NULL)
                        printf("Ошибка: не удалось открыть файл. Попробуйте ввести путь ещё раз: ");
                    else
                        printf("Успешно прочитано.\n");
                }
                else
                {
                    printf("Ошибка: слишком длинный путь к файлу. Попробуйте ввести ещё раз: ");
                    clean_buf();
                }
            }
            else
                printf("Ошибка: пустой путь к файлу. Попробуйте ввести ещё раз: ");
        }
        else
            printf("Ошибка: не удалось прочитать путь к файлу. Попробуйте ввести ещё раз: ");
    }
}

void file_add_elem(FILE *file, int num)
{
    // перешли в конец файла
    fseek(file, 0, SEEK_END);
    // записали число в файл
    fprintf(file, "%d", num);  
}