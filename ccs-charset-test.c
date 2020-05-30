/*
 * Coded Character Set's Character Set Interface Test
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <ccs-charset.h>

int main (int argc, char *argv[])
{
	struct ccs_charset *set;
	const char *e;

	if (argc != 2) {
		fprintf (stderr, "usage:\n\tccs-charset-test <name>\n");
		return 1;
	}

	if ((set = ccs_charset_alloc (NULL)) == NULL) {
		fprintf (stderr, "E: no enough memory\n");
		return 1;
	}

	if ((e = ccs_charset_merge (set, argv[1])) != NULL)
		fprintf (stderr, "E: %s\n", e);

	ccs_charset_free (set);
	return 0;
}
