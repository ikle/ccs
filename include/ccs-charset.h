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

struct ccs_charset *ccs_charset_alloc (FILE *f);
void ccs_charset_free (struct ccs_charset *o);

struct ccs_charset *ccs_charset_locate (const struct ccs_de *de);

#endif  /* CCS_CHARSET_H */
