#include "dijkstra.h"

int max_distance(int list_dist_vn2all[], int was_work[], int n)
{
    // Инициализация максимального значения
    int max = -1, max_index = -1;

    for (int v = 0; v < n; v++)
        if (was_work[v] == 0 && list_dist_vn2all[v] > max)
            max = list_dist_vn2all[v], max_index = v;
    /*if (max == -1)
        for (int v = 0; v < n; v++)
            if (was_work[v] == 2 && list_dist_vn2all[v] > max)
                max = list_dist_vn2all[v], max_index = v;*/
    return max_index;
}

void printSolution(int dist[], int n)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < n; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}

int *dijkstra(int **matrix, int v_now, int n)
{
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            printf("%d ", matrix[i][j]);
        printf("\n");
    }*/
    int *list_dist_vn2all = calloc(n, sizeof(int));
    // Массив для хранения кратчайших расстояний
    // list_dist_vn2all[i] будет содержать кратчайшее расстояние от v_now до i if (list_dist_vn2all == NULL) return NULL;

    int *was_work = calloc(n, sizeof(int));
    // was_work[i] будет 1, если вершина i включена
    // в дерево кратчайших путей или расстояние от v_now до i окончательно определено
    if (was_work == NULL)
        return NULL;

    // Инициализация всех расстояний как -1, а was_work[] как 0
    for (int i = 0; i < n; i++)
    {
        list_dist_vn2all[i] = -1;
        was_work[i] = 0;
    }
    for (int j = 0; j < n; j++)
    {
        was_work[j] = 1;
        for (int i = 0; i < n; i++)
            if (matrix[i][j])
                was_work[j] = 0;
    }

    // Расстояние от источника до самого себя всегда равно 0
    list_dist_vn2all[v_now] = 0;
    int flag = 1;

    // Нахождение кратчайших путей для всех вершин
    while (flag)
    {
        for (int j = 0; j < n; j++)
        {
            // Выбор вершины с максимальным расстоянием из множества
            // вершин, еще не включенных в дерево кратчайших путей.
            int u;
            if (j == 0)
                u = v_now;
            else 
                u = max_distance(list_dist_vn2all, was_work, n);
            //printf("u = %d\n", u);
            if (u == -1)
                break;

            // Отметить выбранную вершину как обработанную
            was_work[u] = 1;
            for (int i = 0; i < n; i++)
                if (matrix[i][u] && was_work[i] != 1)
                    was_work[u] = 2;

            // Обновление расстояния для смежных вершин выбранной вершины
            for (int v = 0; v < n; v++)
            {
                // Обновление list_dist_vn2all[v] только если вершина v не включена в дерево
                // кратчайших путей, существует ребро от u к v, и общий вес пути
                // от v_now до v через u больше текущего значения list_dist_vn2all[v]
                //printf("%d - %d %d / %d %d\n", u, v, list_dist_vn2all[u] + matrix[u][v], matrix[u][v], was_work[u]);
                if (matrix[u][v] && list_dist_vn2all[u] != -1 && ((list_dist_vn2all[u] + matrix[u][v]) > list_dist_vn2all[v]))
                    list_dist_vn2all[v] = list_dist_vn2all[u] + matrix[u][v];
                //printSolution(list_dist_vn2all, n);
                //getchar();
            }
        }
        //for (int i = 0; i < n; i++)
        //    printf("%d ", was_work[i]);
        for (int i = 0; i < n; i++)
        {
            if (was_work[i] == 0)
                was_work[i] = 1;
            if (was_work[i] == 2)
                was_work[i] = 0;
        }
        flag = 0;
        for (int i = 0; i < n; i++)
            if (was_work[i] != 1)
                flag = 1;
        //for (int i = 0; i < n; i++)
        //    printf("%d ", was_work[i]);
    }
    //printSolution(list_dist_vn2all, n);
    free(was_work);

    // Вернуть массива кратчайших расстояний
    return list_dist_vn2all;
}

int find_max_dist(int *dist, int n, int *ind)
{
    int max = -1;
    for (int i = 0; i < n; i++)
        if (dist[i] > max && dist[i] != INF)
        {
            max = dist[i];
            *ind = i;
        }
    return max;
}

void swap(int *v1, int *v2)
{
    int x = *v1;
    *v1 = *v2;
    *v2 = x;
}

// Основная функция
int dijkstra_all(int **matrix, int n, int *v1, int *v2, int *res)
{
    *res = -1;
    for (int i = 0; i < n; i++)
    {
        // Вызов функции Дейкстры
        //printf("\n!%d!\n", i);
        int *list_dist_vn2all = dijkstra(matrix, i, n);
        if (list_dist_vn2all == NULL)
        {
            printf("Ошибка выделения памяти!\n");
            return ERR_MEM;
        }
        int v1_now = 0;
        int max_now = find_max_dist(list_dist_vn2all, n, &v1_now);
        if (max_now > *res)
        {
            *res = max_now;
            *v1 = v1_now;
            *v2 = i;
        }
        free(list_dist_vn2all);
    }
    if (*v1 > *v2)
        swap(v1, v2);
    return OK;
}
