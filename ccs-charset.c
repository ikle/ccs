/*
 * Coded Character Set's Character Set Interface
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <ccs-charset.h>

struct ccs_charset {
	unsigned short size;
	unsigned char order, shift;
	ccs_code_t *data;
};

static const char *get_field (struct ccs_charset *o, FILE *f)
{
	int a;
	size_t i;
	char line[77 + 1];  /* one more for trailing NUL */
	unsigned n;

	for (i = 0; (a = getc (f)) != '\n'; ++i) {
		if (a == EOF)
			return "unexpected end of file";

		if (i >= sizeof (line))
			return "header line too long";

		line[i] = a;
	}

	line[i] = '\0';

	if (sscanf (line, " Size: %u", &n) == 1) {
		o->size = n;
	}
	else if (sscanf (line, " Order: %u", &n) == 1) {
		o->order = n;
	}
	else if (sscanf (line, " Shift: %u", &n) == 1) {
		o->shift = n;
	}

	return NULL;
}

static const char *get_header (struct ccs_charset *o, FILE *f)
{
	int a;
	const char *e;

	while ((a = getc (f)) == '#')
		if ((e = get_field (o, f)) != NULL)
			return e;

	if (a != EOF)
		ungetc (a, f);

	if (o->size == 0 || o->order == 0)
		return "no valid size and order defined";

	o->data = calloc (o->size * o->order, sizeof (o->data[0]));
	if (o->data == NULL)
		return "cannot allocate memory";

	return NULL;
}

static const char *drop_line (FILE *f)
{
	int a;

	while ((a = getc (f)) != '\n')
		if (a == EOF)
			return "unexpected end of file";

	return NULL;
}

static const char *get_hdigit (FILE *f, int *digit)
{
	int a = getc (f);

	if (a >= '0' && a <= '9') {
		*digit = a - '0';
		return NULL;
	}

	if (a >= 'a' && a <= 'f') {
		*digit = a - 'a' + 10;
		return NULL;
	}

	if (a != EOF)
		ungetc (a, f);

	return "hexadecimal digit expected";
}

static const char *get_octet (FILE *f, int *octet)
{
	const char *e;
	int h, l;

	if ((e = get_hdigit (f, &h)) != NULL ||
	    (e = get_hdigit (f, &l)) != NULL)
		return e;

	*octet = (h << 4) | l;
	return NULL;
}

static const char *
get_code (const struct ccs_charset *o, FILE *f, size_t *offset)
{
	size_t i, idx;
	int octet;
	const char *e;

	for (i = 0, idx = 0; i < o->order; ++i, idx = idx * o->size + octet) {
		if ((e = get_octet (f, &octet)) != NULL)
			return e;

		if ((octet -= o->shift) < 0 || octet >= o->size)
			return "octet value out of range";
	}

	*offset = idx;
	return NULL;
}

static const char *get_unicode (FILE *f, ccs_code_t *code)
{
	size_t i;
	ccs_code_t c;
	int digit;
	const char *e;

	for (i = 0, c = 0; i < 8; ++i, c = (c << 4) | digit)
		if ((e = get_hdigit (f, &digit)) != NULL) {
			if (i > 0)
				break;

			return e;
		}

	*code = c;
	return NULL;
}

static const char *get_space (FILE *f)
{
	int a;

	if ((a = getc (f)) != ' ' && a != '\t')
		return "space or tab character expected";

	while ((a = getc (f)) == ' ' || a == '\t') {}

	if (a != EOF)
		ungetc (a, f);

	return NULL;
}

static const char *get_eol (FILE *f)
{
	int a;

	while ((a = getc (f)) == ' ' || a == '\t') {}

	if (a == '#')
		return drop_line (f);

	return a == '\n' ? NULL : "end of line expected";
}

static const char *get_map (const struct ccs_charset *o, FILE *f)
{
	const char *e;
	size_t offset;
	ccs_code_t code;

	if ((e = get_code (o, f, &offset)) != NULL ||
	    (e = get_space (f))            != NULL ||
	    (e = get_unicode (f, &code))   != NULL ||
	    (e = get_eol (f))              != NULL)
		return e;

	o->data[offset] = code;
	return NULL;
}

static const char *parse (struct ccs_charset *o, FILE *f)
{
	const char *e;
	int a;

	o->size  = 0;
	o->order = 0;
	o->shift = 0;
	o->data  = NULL;

	if ((e = get_header (o, f)) != NULL)
		return e;

	while ((a = getc (f)) != EOF)
		switch (a) {
		case '\n':
			break;
		case '#':
			if ((e = drop_line (f)) != NULL)
				goto no_map;

			break;
		default:
			ungetc (a, f);

			if ((e = get_map (o, f)) != NULL)
				goto no_map;

			break;
		}

	return NULL;
no_map:
	free (o->data);
	return e;
}

struct ccs_charset *ccs_charset_alloc (FILE *f)
{
	struct ccs_charset *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	if (parse (o, f) != NULL)
		goto no_parse;

	return o;
no_parse:
	free (o);
	return NULL;
}

void ccs_charset_free (struct ccs_charset *o)
{
	if (o == NULL)
		return;

	free (o);
}

struct ccs_charset *ccs_charset_locate (const struct ccs_de *de)
{
	return NULL;  /* not implemented yet */
}
