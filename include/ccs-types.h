/*
 * Coded Character Set Core Types
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_TYPES_H
#define CCS_TYPES_H  1

#include <limits.h>

#if UINT_MAX < 0xffffffffL
typedef unsigned long ccs_code_t;
#else
typedef unsigned ccs_code_t;
#endif

typedef unsigned short ccs_size_t;

struct ccs_de {
	ccs_code_t	code;	/* character code		*/
	ccs_size_t	size;	/* argument buffer size		*/
	ccs_size_t	len;	/* actual length of argument	*/
	unsigned char	arg[];	/* argument buffer		*/
};

#endif  /* CCS_TYPES_H */
