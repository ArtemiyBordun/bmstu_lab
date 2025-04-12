#include "str.h"

size_t countWords(const char* str, const char* sep)
{
    size_t count = 0;
    char* p = (char*)str;
    for (char* pSpase; (pSpase = strpbrk(p, sep)); p++)
        if (p != pSpase)
        {
            count++;
            p = pSpase;
        }
    if (strlen(p))
        count++;
    return count;
}

size_t parseWords(char*** words, char* str, const char* sep)
{
    size_t count = countWords(str, sep);
    char* p = str;
    *words = (char**)malloc(sizeof(char*) * count);
    if (*words == NULL)
        return 0;
    int i = 0;
    for (char* pSpase; (pSpase = strpbrk(p, sep)); p++)
        if (p != pSpase)
        {
            long len = pSpase - p;
            (*words)[i] = (char*)malloc(sizeof(char) * (len + 1));
            if ((*words)[i] == NULL)
                return 0;
            strSub((*words)[i], p, len);
            i++;
            p = pSpase;
        }
    if (strlen(p))
    {
        (*words)[i] = (char*)malloc(sizeof(char) * (strlen(p) + 1));
        if ((*words)[i] == NULL)
            return 0;
        strncpy((*words)[i], p, (strlen(p) + 1));
    }
    return count;
}

char* strSub(char* subs, const char* s, unsigned len)
{
    unsigned i;
    for (i = 0; i < len && (subs[i] = s[i]); i++);
    subs[i] = '\0';
    return subs;
}

