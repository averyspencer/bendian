#include <stdlib.h>
#include <limits.h>

/*

converts little to big endian

n: pointer to the value
l: length of the value in bits

successfully returns a pointer to the value converted to big endian (you must free it)

unsuccessfully returns NULL

*/
void *bendian(void *n, size_t l)
{
	/* return buffer */
	unsigned char *retb;

	/* linked list containing each byte of the little-endian value */
	struct bendian_l {
		unsigned char v;
		struct bendian_l *n;
	} *w_le;

	/* linked list containing each byte of the big-endian value */
	struct bendian_l *w_be;

	struct bendian_l *cur;

	/* initialize and allocate the linked lists */
	{
		/* number of bytes in the value */
		const size_t n_bytes = l / CHAR_BIT;

		/* initialize and allocate the little-endian linked list */
		{
			w_le = malloc(sizeof(struct bendian_l));
			if (w_le == NULL) {
				return NULL;
			}
			if (n_bytes == 1) {
				/* linked list only has one node */
				w_le->n = NULL;
			} else {
				/* allocate rest of linked list */
				signed i;
				cur = w_le;
				for (i = n_bytes - 1; i > 0; i--) {
					cur->n = malloc(sizeof(struct bendian_l));
					if (cur->n == NULL) {
						/* free the memory */
						struct bendian_l *p;
						cur = w_le;
						while (cur != NULL) {
							p = cur;
							cur = cur->n;
							free(p);
						}
						return NULL;
					}
					cur = cur->n;
				}
			}
		}

		/* initialize and allocate the big-endian linked list */
		{
			w_be = malloc(sizeof(struct bendian_l));
			if (w_be == NULL) {
				return NULL;
			}

			if (n_bytes == 1) {
				/* linked list only has one node */
				w_be->n = NULL;
			} else {
				/* allocate rest of linked list */
				signed i;
				cur = w_be;
				for (i = n_bytes - 1; i > 0; i--) {
					cur->n = malloc(sizeof(struct bendian_l));
					if (cur->n == NULL) {
						/* free the memory */
						struct bendian_l *p;
						cur = w_be;
						while (cur != NULL) {
							p = cur;
							cur = cur->n;
							free(p);
						}

						/* w_le must be freed also */
						cur = w_le;
						while (cur != NULL) {
							p = cur;
							cur = cur->n;
							free(p);
						}

						return NULL;
					}
					cur = cur->n;
				}
			}
		}
	}

	/* populate the little-endian linked list */
	{
		cur = w_le;
		unsigned n_pop; /* number of linked list nodes already populated */
		unsigned char* f;
		for(n_pop = 0; cur != NULL; n_pop++, cur = cur->n) {
			f = ((unsigned char *)n) + n_pop;
			cur->v = *f;
			f++;
		}
	}

	/* perform the little-endian to big-endian conversion */
	{
		struct bendian_l *cur_to;
		unsigned x, x_temp, le_len;

		/* initialize le_len with the length of the little-endian linked list */
		for (le_len = 0, cur = w_le; cur != NULL; le_len++, cur = cur->n) { ; }

		for (x = le_len, cur_to = w_be; x > 0; x--, cur_to = cur_to->n) {
			/* index into the little-endian linked list to x - 1 */
			for (cur = w_le, x_temp = x; (x_temp - 1) > 0; x_temp--, cur = cur->n) { ; }

			cur_to->v = cur->v;
		}
	}

	/* populate a buffer (to return) with the value represented by the big-endian linked list */
	{
		retb = malloc(l / CHAR_BIT);
		if (retb == NULL) {
			/* free the little-endian linked list */
			struct bendian_l *p;
			cur = w_le;
			while (cur != NULL) {
				p = cur;
				cur = cur->n;
				free(p);
			}

			/* free the big-endian linked list */
			cur = w_be;
			while (cur != NULL) {
				p = cur;
				cur = cur->n;
				free(p);
			}
		}

		unsigned char *retb_cur = retb;
		for (cur = w_be; cur != NULL; cur = cur->n, retb_cur++) {
			*retb_cur = cur->v;
		}
	}

	/* cleanup */
	{
		/* free the little-endian linked list */
		struct bendian_l *p;
		cur = w_le;
		while (cur != NULL) {
			p = cur;
			cur = cur->n;
			free(p);
		}

		/* free the big-endian linked list */
		cur = w_be;
		while (cur != NULL) {
			p = cur;
			cur = cur->n;
			free(p);
		}
	}

	return retb;
}
