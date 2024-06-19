#include "in_out.h"

int clean_buf(void)
{
    char a = getchar();
    int count = 0;
    while (a != '\n' && a != EOF)
    {
        count++;
        a = getchar();
    }
    return count;
}

void file_choose(FILE **file)
{
    *file = NULL;
    char strk[SIZE_OF_BUF];
    memset(strk, '\0', SIZE_OF_BUF);
    printf("Введите путь к рабочему файлу (первое число - количество вершин в графе,\n\
затем ребра в формате вершина1 - вершина2 - вес ребра, граф неориентированный):\n");
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
                    *file = fopen(strk, "r");
                    if (*file == NULL)
                    {
                        printf("Ошибка: не удалось открыть файл. Попробуйте ввести путь ещё раз: ");
                    }
                    else
                    {
                        int n;
                        int a, b, c;
                        int err = 0;
                        if (fscanf(*file, "%d", &n) != 1 || n <= 0)
                        {
                            printf("Количество вершин в графе некорректно( Попробуйте ввести рабочий файл ещё раз: ");
                            fclose(*file);
                            *file = NULL;
                        }
                        int flag = 0;
                        while ((err = fscanf(*file, "%d%d%d", &a, &b, &c)) == 3 && c > 0 && a < n && b < n)
                            flag = 1;
                        if (err != EOF || flag == 0)
                        {
                            printf("Содержимое файла не корректно( Попробуйте ввести ещё раз: ");
                            fclose(*file);
                            *file = NULL;
                        }
                        else
                        {
                            fseek(*file, 0, SEEK_SET);
                            printf("Успешно прочитано.\n");
                        }
                    }
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

void free_matrix(int ***matrix, int n)
{
    if (*matrix != NULL)
    {
        for (int i = 0; i < n; i++)
            if ((*matrix)[i] != NULL)
            {
                free((*matrix)[i]);
                (*matrix)[i] = NULL;
            }
        free(*matrix);
        *matrix = NULL;
    }
}

int create_matrix(int ***matrix, int n)
{
    *matrix = calloc(n, sizeof(int *));
    if (*matrix == NULL)
        return ERR_MEM;
    for (int i = 0; i < n; i++)
    {
        (*matrix)[i] = calloc(n, sizeof(int));
        if ((*matrix)[i] == NULL)
        {
            free_matrix(matrix, i);
            return ERR_MEM;
        }
    }
    return OK;
}

int read_matrix(FILE *file, int ***matrix, int *n)
{
    int rc = OK;
    int a, b, c;
    fscanf(file, "%d", n);
    rc = create_matrix(matrix, *n);
    if (rc == ERR_MEM)
        printf("Ошибка выделения памяти!\n");
    else
    {
        while (fscanf(file, "%d%d%d", &a, &b, &c) == 3)
            (*matrix)[a][b] = c;
    }
    return rc;
}

// считали граф как матрицу смежностей
int input_graph(int ***matrix, int *n)
{
    int rc = OK;
    FILE *file_in = NULL;
    file_choose(&file_in);
    rc = read_matrix(file_in, matrix, n);
    fclose(file_in);
    return rc;
}

// Рёбра с весами
//    A -- B [label=4];
void graph_export_to_dot(FILE *f, const char *tree_name, int **matrix, int n)
{
    if (matrix != NULL)
    {
        fprintf(f, "digraph %s {\n", tree_name);
        for (int i = 0; i < n; i++)
            if (matrix[i] != NULL)
                for (int j = 0; j < n; j++)
                    if (matrix[i][j] != 0)
                        fprintf(f, "%d -> %d [label=%d];\n", i, j, matrix[i][j]);
        fprintf(f, "}\n");
        printf("Визуализировано.\n");
    }
}

// вывели граф красиво
void output_graph(int **matrix, int n, char *name_file)
{
    FILE *f = fopen(name_file, "w");
    graph_export_to_dot(f, "visual_graph", matrix, n);
    fclose(f);
}