#include <stdio.h>
int main(void)
{
    char ref[] = "isrveawhobpnutfg";
    char pass[] = "giants";
    char c = 'a';
    int i = 0;

    while (c < 123)
    {
        while (pass[i])
        {
            if (ref[c & 0xf] == pass[i])
                printf("char %c matches %c\n", c, ref[c & 0xf]);
            i++;
        }
        c++;
        i = 0;
    }
}