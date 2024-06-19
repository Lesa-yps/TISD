#include "clean_buf.h"

//функция чистит буфер
void clean_buf(void)
{
    wchar_t c[100];
    fgetws(c, sizeof(c), stdin);
}
