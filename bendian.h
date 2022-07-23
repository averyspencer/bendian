#ifndef BENDIAN_H_INCLUDED
#define BENDIAN_H_INCLUDED

/*

converts little to big endian

n: pointer to the value
l: length of the value in bits

successfully returns a pointer to the value converted to big endian (you must free it)

unsuccessfully returns NULL

*/
void *bendian(void *n, size_t l);

#endif

