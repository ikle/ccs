# Name

ccs-map — coded character set character mapping

# Synopsis

```c
#include <ccs-map.h>

struct ccs_map *ccs_map_alloc (void);
void ccs_map_free (struct ccs_map *o);

int ccs_map_load_cs (struct ccs_map *o, int i, struct ccs_charset *s);
int ccs_map_load_gs (struct ccs_map *o, int i, struct ccs_charset *s);

int ccs_map_lock_gl  (struct ccs_map *o, int i);
int ccs_map_lock_gr  (struct ccs_map *o, int i);
int ccs_map_shift_gl (struct ccs_map *o, int i);

ccs_code_t ccs_map_process (struct ccs_map *o, ccs_code_t c);
```

# Description

The coded character set character mapping is intended for mapping character
codes to a specific character set codes.

The *ccs\_map\_alloc*() function creates the character set character mapping
object.

The *ccs\_map\_free*() function frees the allocated resources of the
specified character set character mapping object.

The *ccs\_map\_load\_cs*() and the *ccs\_map\_load\_gs*() functions
designates character set to Ci and Gi set, respectively. If s is NULL then
the identity mapping is loaded. By default, identity mapping is designated
to all sets.

The *ccs\_map\_lock\_gl*() and the *ccs\_map\_lock\_gr*() functions invokes
and locks designated character set into GL and GR, respectively. By default,
G0 is invoked and locked into GL and G1 is invoked and locked into GR.

The *ccs\_map\_shift\_gl*() function temporary invokes designated character
set into GL for a next one character mapping.

The *ccs\_map\_process*() function maps the specified characher code via
invoked character sets.

# Return Value

The *ccs\_map\_alloc*() function returns a pointer to the allocated and
initialized ccs\_map structure or NULL in case of errors.

Upon successful completion *ccs\_map\_load\_cs*() and *ccs\_map\_load\_gs*(),
as well as *ccs\_map\_lock\_gl*(), *ccs\_map\_lock\_gr*() and
*ccs\_map\_shift\_gl*() functions return non-zero. Otherwise, zero is
returned and errno is set to indicate the error.

The *ccs\_map\_process*() returns the converted code or 0 if input code
consumed but the output character is not available yet (in case of
a multibyte character set is invoked) or no match for input code found.

# Errors

*  EINVAL — Invalid set index is specified.
*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
