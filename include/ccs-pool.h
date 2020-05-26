/*
 * Coded Character Set Cache Pool
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_POOL_H
#define CCS_POOL_H  1

#include <ccs-charset.h>
#include <ccs-types.h>

struct ccs_pool *ccs_pool_alloc (void);
void ccs_pool_free (struct ccs_pool *o);

struct ccs_charset *
ccs_pool_get_charset (struct ccs_pool *o, const struct ccs_de *de);

#endif  /* CCS_POOL_H */
