#include <stdio.h>

enum {
    NORMAL,
    LINE_COMMENT,
    BLOCK_COMMENT
};

int main()
{
    int c;
    int prevchar = 0;
    int state_sub_two = NORMAL;
    int state_sub_one = NORMAL;
    int state = NORMAL;
    while((c = getchar()) != EOF) {
        if (state == NORMAL) {
            if (prevchar == '/' && c == '/') {
                state = LINE_COMMENT;
            } else if (prevchar == '/' && c == '*') {
                state = BLOCK_COMMENT;
            }
        } else if (state == LINE_COMMENT) {
            if (c == '\n')
                state = NORMAL;
        } else {
            if (prevchar == '*' && c == '/')
                state = NORMAL;
        }
        if (prevchar == '/' && state_sub_two == NORMAL && state == NORMAL)
            printf("%c", prevchar);
        if (c != '/' && (state == NORMAL || c == '\n'))
            printf("%c", c);
        prevchar = c;
        state_sub_two = state_sub_one;
        state_sub_one = state;
    }
}

void func() {
    //////int a, b, c;
    //int a, b, c;
    //  /*int a, b, c;
    int a, b, c;

    /*
     *
     *
     */

    /*
     * test
     */


}
