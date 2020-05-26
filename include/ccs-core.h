/*
 * Coded Character Set Escape and Control Sequence Parser
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35, ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_CORE_H
#define CCS_CORE_H  1

#include <ccs-types.h>

struct ccs_core *ccs_core_alloc (void);
void ccs_core_free (struct ccs_core *o);

int ccs_core_process (struct ccs_core *o, ccs_code_t c, struct ccs_de *de);

#endif  /* CCS_CORE_H */
