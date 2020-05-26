/*
 * Coded Character Set Character Mapping
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_MAP_H
#define CCS_MAP_H  1

#include <ccs-charset.h>
#include <ccs-types.h>

struct ccs_map *ccs_map_alloc (void);
void ccs_map_free (struct ccs_map *o);

int ccs_map_load_cs (struct ccs_map *o, int i, struct ccs_charset *s);
int ccs_map_load_gs (struct ccs_map *o, int i, struct ccs_charset *s);

int ccs_map_lock_gl  (struct ccs_map *o, int i);
int ccs_map_lock_gr  (struct ccs_map *o, int i);
int ccs_map_shift_gl (struct ccs_map *o, int i);

ccs_code_t ccs_map_process (struct ccs_map *o, ccs_code_t c);

#endif  /* CCS_MAP_H */
