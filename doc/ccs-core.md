# Name

ccs-core — coded character set escape and control sequence parser

# Synopsis

```c
#include <ccs-core.h>

struct ccs_core *ccs_core_alloc (void);
void ccs_core_free (struct ccs_core *o);

int ccs_core_process (struct ccs_core *o, ccs_code_t c, struct ccs_de *de);
```

# Description

Escape and control sequence parser intended for parsing ECMA-35 escape
sequences and ECMA-48 control sequences.

The *ccs\_core\_alloc*() function creates the escape and control sequence
parser object.

The *ccs\_core\_free*() function frees the allocated resources of the
specified escape and control equencearser object.

The *ccs\_core\_process*() function parses ECMA-35 escape sequences and
ECMA-48 control sequences.

# Return Value

The *ccs\_core\_alloc*() function returns a pointer to the allocated and
initialized ccs\_core structure or NULL in case of errors.

The *ccs\_core\_process*() returns non-zero and resulting data element or
0 if input code consumed but the output data element is not available yet,
either NUL or SYN characters is given as an input code.

# Errors

*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
