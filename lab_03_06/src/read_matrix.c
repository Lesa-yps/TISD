#include "read_matrix.h"

// функция вызывает вспомогательные  функции для заполнения матриц
int asc_input_func(void (*f)(struct Normal_mat *name_struct, struct Normal_arr *name_struct2, int user), struct Normal_mat *name_struct1, struct Normal_arr *name_struct2);

// разные методы ввода
void coord_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user);
void rand_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user);
void ord_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user);

// создание нового представления матрицы и массива
int matrix_to_vector(struct Normal_mat arr1, struct Vector_mat *vec1);
int array_to_vector(struct Normal_arr arr1, struct Vector_arr *vec1);

// функция читает целое число из диапазона
int read_int(int minik, int maxik);

// функция считает размерность матрицы
void read_sizes(int *n, int *m);


// чтение и создание матриц
int read_matrix(struct Normal_mat *comb_arr1, struct Vector_mat *comb_vec1, struct Normal_arr *comb_arr2, struct Vector_arr *comb_vec2)
{
    int user;
    int rc = OK;
    printf("\nПрограмма может принимать матрицу в трёх видах:\n\
1) координатном (вводите количество точек, затем индексы, остальные элементы заполнятся нулями;\n\
2) с рандомным заполнением по введённому проценту разряженности;\n\
3) вручную (сначала вводится количество строк и столбцов, а затем все элементы по столбцам.\n\
Введите выбранный ввод: ");
    // выбор метода ввода
    user = read_int(1, 3);
    // заполнение стандартного представления матриц
    // координатный метод
    if (user == 1)
        rc = asc_input_func(coord_input, comb_arr1, comb_arr2);
    // метод процентного заполнения
    else if (user == 2)
        rc = asc_input_func(rand_input, comb_arr1, comb_arr2);
    // метод обычного заполнения (всех элементов)
    else
        rc = asc_input_func(ord_input, comb_arr1, comb_arr2);
    if (rc == OK)
    {
        // создание нового представления матриц
        rc = matrix_to_vector(*comb_arr1, comb_vec1);
        if (rc == OK)
        {
            rc = array_to_vector(*comb_arr2, comb_vec2);
            if (rc != OK)
                free_vec_mat(comb_vec1);
        }
        if (rc != OK)
        {
            free(comb_arr1->mat);
            free(comb_arr2->arr);
        }
    }
    return rc;
}


// функция вызывает вспомогательные  функции для заполнения матриц
int asc_input_func(void (*f)(struct Normal_mat *name_struct1, struct Normal_arr *name_struct2, int user), struct Normal_mat *name_struct1, struct Normal_arr *name_arr1)
{
    printf("Введите размерности матрицы: \n");
    read_sizes(&(name_struct1->n), &(name_struct1->m));
    name_struct1->mat = calloc((name_struct1->n) * (name_struct1->m), sizeof(int));
    if (name_struct1->mat == NULL)
        return ERROR_MEM;
    name_arr1->n = name_struct1->n;
    name_arr1->arr = calloc(name_arr1->n, sizeof(int));
    if (name_arr1->arr == NULL)
    {
        free(name_struct1->mat);
        return ERROR_MEM;
    }
    f(name_struct1, name_arr1, MY_NULL);
    return OK;
}

// координатный метод заполнения матрицы
void coord_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user)
{
    int count;
    int i;
    int j;
    printf("Введите количество координат для матрицы, которые хотите ввести: ");
    count = read_int(0, (name_struct1->n) * (name_struct1->m));
    for (int k = 0; k < count; k++)
    {
        printf("\nВведите индекс строки элемента №%d [0 - %d]: ", k + 1, name_struct1->n - 1);
        i = read_int(0, name_struct1->n - 1);
        printf("\nВведите индекс столбца элемента №%d [0 - %d]: ", k + 1, name_struct1->m - 1);
        j = read_int(0, name_struct1->m - 1);
        printf("\nВведите элемент №%d (отсчёт с 0): ", k + 1);
        name_struct1->mat[i * (name_struct1->m) + j] = read_int(INT_MIN, INT_MAX);
    }
    printf("Введите количество координат для массива, которые хотите ввести: ");
    count = read_int(0, name_arr1->n);
    for (int k = 0; k < count; k++)
    {
        printf("\nВведите индекс элемента №%d [0 - %d]: ", k + 1, name_arr1->n - 1);
        i = read_int(0, name_arr1->n - 1);
        printf("\nВведите элемент №%d (отсчёт с 0): ", k + 1);
        name_arr1->arr[i] = read_int(INT_MIN, INT_MAX);
    }
    (void) user;
}
// метод процентного заполнения матрицы
void rand_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user)
{
    int perc;
    int perc_arr;
    int i;
    int j;
    int x;
    int k = 0;
    // Инициализация генератора случайных чисел
    srand(time(NULL));
    if (user == MY_NULL)
    {
        printf("Введите процент элементов для матрицы, которые должны быть не нулевыми: ");
        perc = read_int(0, 100);
        printf("Введите процент элементов для массива, которые должны быть не нулевыми: ");
        perc_arr = read_int(0, 100);
    }
    else
        perc_arr = perc = user;
    perc = ((name_struct1->n) * (name_struct1->m)) * perc / 100;
    perc_arr = name_arr1->n * perc_arr / 100;
    // заполнение матрицы
    while (k < perc)
    {
        // Генерация случайного числа
        x = (rand() % ((name_struct1->n * name_struct1->m) - 1)) + 1;
        i = x / name_struct1->m;
        j = x % name_struct1->m;
        while ((name_struct1->mat[i * (name_struct1->m) + j]) != 0)
        {
            x = (x + 1) % (name_struct1->n * name_struct1->m);
            i = x / name_struct1->m;
            j = x % name_struct1->m;/*
            printf("    x = %d\n", x);
            for (int a1 = 0; a1 < name_struct1->n; a1++)
            {
                for (int a2 = 0; a2 < name_struct1->m; a2++)
                    printf("%d ", name_struct1->mat[a1 * (name_struct1->m) + a2]);
                printf("\n");
            }*/
        }
        (name_struct1->mat[i * (name_struct1->m) + j]) = (rand() % (MAX_RAND)) + 1;
        //printf("i = %d j = %d x = %d\n", i, j, (name_struct1->mat[i * (comb_arr1->m) + j]));
        k++;
    }
    //  заполнение массива
    k = 0;
    while (k < perc_arr)
    {
        // Генерация случайного числа
        x = (rand() % (name_arr1->n - 1)) + 1;
        while ((name_arr1->arr[x]) != 0)
        {
            x = (x + 1) % (name_arr1->n);
            /*for (int a2 = 0; a2 < name_arr1->n; a2++)
                printf("%d ", name_arr1->arr[a2]);
            printf("    x = %d k = %d perc_arr = %d\n", x, k, perc_arr);*/
        }
        (name_arr1->arr[x]) = (rand() % (MAX_RAND)) + 1;
        //printf("i = %d j = %d x = %d\n", i, j, (name_struct1->mat[i * (comb_arr1->m) + j]));
        k++;
    }
}

// метод обычного заполнения  матрицы(всех элементов вручную)
void ord_input(struct Normal_mat *name_struct1, struct Normal_arr *name_arr1, int user)
{
    printf("Введите элементы матрицы по строкам:\n");
    for (int i = 0; i < name_struct1->n; i++)
        for (int j = 0; j < name_struct1->m; j++)
            name_struct1->mat[i * (name_struct1->m) + j] = read_int(INT_MIN, INT_MAX);
    printf("Введите элементы массива: ");
    for (int i = 0; i < name_arr1->n; i++)
        name_arr1->arr[i] = read_int(INT_MIN, INT_MAX);
    (void) user;
}

// создание нового представления матрицы
int matrix_to_vector(struct Normal_mat arr1, struct Vector_mat *vec1)
{
    if (create_vec_mat(vec1, arr1.n, arr1.m) != OK)
    {
        free_vec_mat(vec1);
        return ERROR_MEM;
    }
    for (int i = 0; i < arr1.m; i++)
    {
        vec1->ind_elems_col[i] = MY_NULL;
        for (int j = 0; j < arr1.n; j++)
            if (arr1.mat[j * (arr1.m) + i] != 0)
            {
                if (vec1->ind_elems_col[i] == MY_NULL)
                    vec1->ind_elems_col[i] = vec1->count_elems;
                vec1->elems[vec1->count_elems] = arr1.mat[j * (arr1.m) + i];
                vec1->num_str[vec1->count_elems] = j;
                (vec1->count_elems)++;
            }
    }
    return OK;
}

int array_to_vector(struct Normal_arr arr1, struct Vector_arr *vec1)
{
    if (create_vec_arr(vec1, arr1.n))
    {
        free_vec_arr(vec1);
        return ERROR_MEM;
    }
    for (int i = 0; i < arr1.n; i++)
    {
        if (arr1.arr[i] != 0)
        {
            vec1->elems[vec1->count_elems] = arr1.arr[i];
            vec1->num_str[vec1->count_elems] = i;
            (vec1->count_elems)++;
        }
    }
    return OK;
}

// функция считает размерность матрицы
void read_sizes(int *n, int *m)
{
    printf("Введите количество строк матрицы: ");
    *n = read_int(1, MAX_N);
    printf("Введите количество столбцов матрицы: ");
    *m = read_int(1, MAX_N);
}

// функция читает целое число из диапазона
int read_int(int minik, int maxik)
{
    int x;
    char a;
    while (1)
        if (scanf("%d", &x) != 1 || x < minik || x > maxik)
        {
            printf("Ошибка ввода. Повторите ввод целого числа в диапазоне %d - %d: ", minik, maxik);
            a = getchar();
            while (a != '\n')
                a = getchar();
        }
        else
            break;
    return x;
}
