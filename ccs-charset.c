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

static int get_field (struct ccs_charset *o, FILE *f)
{
	int a;
	size_t i;
	char line[77 + 1];  /* one more for trailing NUL */
	unsigned n;

	for (i = 0; (a = getc (f)) != '\n'; ++i) {
		if (a == EOF)
			return 0;

		if (i >= sizeof (line))  /* line too long */
			return 0;

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

	return 1;
}

static int get_header (struct ccs_charset *o, FILE *f)
{
	int a;

	while ((a = getc (f)) == '#')
		if (!get_field (o, f))
			return 0;

	if (a != EOF)
		ungetc (a, f);

	if (o->size == 0 || o->order == 0)
		return 0;

	o->data = calloc (o->size * o->order, sizeof (o->data[0]));
	if (o->data == NULL)
		return 0;

	return 1;
}

static int drop_line (FILE *f)
{
	int a;

	while ((a = getc (f)) != '\n')
		if (a == EOF)
			return 0;

	return 1;
}

static int get_hdigit (FILE *f, int *digit)
{
	int a = getc (f);

	if (a >= '0' && a <= '9') {
		*digit = a - '0';
		return 1;
	}

	if (a >= 'a' && a <= 'f') {
		*digit = a - 'a' + 10;
		return 1;
	}

	return 0;
}

static int get_octet (FILE *f, int *octet)
{
	int h, l;

	if (get_hdigit (f, &h) && get_hdigit (f, &l)) {
		*octet = (h << 4) | l;
		return 1;
	}

	return 0;
}

static int get_code (const struct ccs_charset *o, FILE *f, size_t *offset)
{
	size_t i, offs;
	int octet;

	for (i = 0, offs = 0; i < o->order; ++i, offs = offs * o->size + octet)
		if (!get_octet (f, &octet) ||
		    (octet -= o->shift) < 0 || octet >= o->size)
			return 0;

	*offset = offs;
	return 1;
}

static int get_unicode (FILE *f, ccs_code_t *code)
{
	size_t i;
	ccs_code_t c;
	int digit;

	for (i = 0, c = 0; i < 8; ++i, c = (c << 4) | digit)
		if (!get_hdigit (f, &digit)) {
			if (i > 0)
				break;

			return 0;
		}

	*code = c;
	return 1;
}

static int get_space (FILE *f)
{
	int a;

	if ((a = getc (f)) != ' ' && a != '\t')
		return 0;

	while ((a = getc (f)) != EOF)
		if (a != ' ' && a != '\t') {
			ungetc (a, f);
			break;
		}

	return 1;
}

static int get_eol (FILE *f)
{
	int a;

	while ((a = getc (f)) == ' ' || a == '\t') {}

	return a == '#' ? drop_line (f) : a == '\n';
}

static int get_map (const struct ccs_charset *o, FILE *f)
{
	size_t offset;
	ccs_code_t code;
	int ret = get_code (o, f, &offset) && get_space (f) &&
		  get_unicode (f, &code) && get_eol (f);

	if (ret)
		o->data[offset] = code;

	return ret;
}

static int parse (struct ccs_charset *o, FILE *f)
{
	int a;

	o->size  = 0;
	o->order = 0;
	o->shift = 0;
	o->data  = NULL;

	if (!get_header (o, f))
		return 0;

	while ((a = getc (f)) != EOF)
		switch (a) {
		case '\n':
			break;
		case '#':
			if (!drop_line (f))
				goto no_map;

			break;
		default:
			ungetc (a, f);

			if (!get_map (o, f))
				goto no_map;

			break;
		}

	return 1;
no_map:
	free (o->data);
	return 0;
}

struct ccs_charset *ccs_charset_alloc (FILE *f)
{
	struct ccs_charset *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	if (!parse (o, f))
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
