/*
 * Coded Character Set's Character Set Interface
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_CHARSET_H
#define CCS_CHARSET_H  1

#include <stdio.h>

#include <ccs-types.h>

struct ccs_charset *ccs_charset_alloc (const char *name);
void ccs_charset_free (struct ccs_charset *o);

const char *ccs_charset_merge (struct ccs_charset *o, const char *name);

struct ccs_charset *ccs_charset_locate (const struct ccs_de *de);

#endif  /* CCS_CHARSET_H */
