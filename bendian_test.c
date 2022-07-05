/* test whether the bendian function for converting from little endian into big endian produces the right results */

#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

extern void *bendian(void *n, size_t l);

int main(void)
{
    uint32_t deadbeef = 0xDEADBEEF;     /* little-endian deadbeef */
    uint32_t *be_deadbeef;              /* big-endian deadbeef */
    bool did_it_succeed = false;
    
    be_deadbeef = bendian(&deadbeef, sizeof(uint32_t) * CHAR_BIT);
    if (be_deadbeef == NULL) {
        return EXIT_FAILURE;
    }

    if (*be_deadbeef == 0xEFBEADDE) {
        did_it_succeed = true;
    } else {
        did_it_succeed = false;
    }

    free(be_deadbeef);

    if (did_it_succeed == true) {
        return EXIT_SUCCESS;
    } else {
        return EXIT_FAILURE;
    }
}
