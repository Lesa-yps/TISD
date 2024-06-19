#include "asc_file.h"

//пока не прочитает нормальный файл, будет просить ввести
void ask_file(wchar_t strk[], char mode[])
{
    FILE *file = NULL;
    char mbs[MAX_LEN + 1];
    wchar_t a;
    wchar_t *strk1;
    while (1)
    {
        strk1 = malloc(sizeof(wchar_t) * (MAX_LEN + 1));
        printf("Введите путь к рабочему файлу ([1; 25] символов): ");
        if (fgetws(strk1, MAX_LEN, stdin) != NULL)
        {
            //мы хоть что-то прочитали, иначе ошибка
            if (strk1[0] != '\0')
            {
                //прочитали всю строчку до переноса строки и  заменяем его на конец строки "\0", иначе ошибка
                if (strk1[wcslen(strk1) - 1] == L'\n')
                {
                    strk1[wcslen(strk1) - 1] = '\0';
                    wcscpy(strk, strk1);
                    wcsrtombs(mbs, (const wchar_t **)&strk1, sizeof(mbs), NULL);
                    file = fopen(mbs, mode);
                    if (file != NULL)
                    {
                        fclose(file);
                        free(strk1);
                        break;
                    }
                    else
                        printf("Ошибка: не удалось открыть файл на чтение. Попробуйте ввести ещё раз.\n");
                }
                else
                {
                    printf("Ошибка: слишком длинный путь к файлу. Попробуйте ввести ещё раз.\n");
                    a = fgetwc(stdin);
                    while (a != '\n')
                        a = fgetwc(stdin);

                }
            }
            else
                printf("Ошибка: пустой путь к файлу. Попробуйте ввести ещё раз.\n");
        }
        else
            printf("Ошибка: не удалось прочитать путь к файлу. Попробуйте ввести ещё раз.\n");
        free(strk1);
    }
}
