#include <string.h>
unsigned int Strlen(const char* s)
{
    unsigned int cnt = 0;
    const char* p = s;
    while (*p++)
        cnt++;
    return cnt;
        
}

unsigned int Strlen1(const char* s)
{
    const char* eos = s;
    while(*eos++);
    return eos - s - 1;
}

void Strcpy(char* dst, const char* src)
{
    char* p = dst;
    const char* q = src;
    while (*q)
        *p++ = *q++;
}

int Strcmp(const char* s1, const char* s2)
{
    const char* p = s1;
    const char* q = s2;
    while (*p == *q && *p && *q)
    {
        p++;
        q++;
    }

    if (*p == 0 && *q == 0)
        return 0;
    if (*p == 0 && *q != 0)
        return 1;
    if (*p != 0 && *q == 0)
        return -1;
    if (*p > *q)
        return 1;
    else
        return -1;
}

int Strcmp1(const char* s1, const char* s2)
{
    int ret = 0;

    while (! (ret = *s1 - *s2))
        ++s1, ++s2;

    if (ret < 0)
        ret = -1;
    else if (ret > 0)
        ret = 1;
    return ret;
}

void f_6_10()
{

}
