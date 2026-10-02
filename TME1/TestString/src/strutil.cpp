// strutil.cpp
#include "strutil.h"

namespace pr {

size_t length(const char* s) {
    size_t len = 0;
    for ( ; s[len] ; ++len) 
    return len;
}

char* newcopy(const char* s) {
    size_t len = length(s);
    char* copy = new char[len];
    char* cp = copy;
    while (*cp++ = *s++);
    return copy;
}

int compare(const char* a, const char* b) {
    const char* ca = a;
    const char* cb = b;

    while (ca && cb){
        if (*ca < *cb){
            return -1;
        } else if (*ca > *cb){
            return 1;
        } else {
            ca++; cb++;
        }
    }
    return 0;
}

}
