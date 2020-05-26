# Name

ccs-pool — coded character set cache pool

# Synopsis

```c
#include <ccs-pool.h>

struct ccs_pool *ccs_pool_alloc (void);
void ccs_pool_free (struct ccs_pool *o);

struct ccs_charset *
ccs_pool_get_charset (struct ccs_pool *o, const struct ccs_de *de);
```

# Description

The coded character set cache pool is intended for caching CCS objects,
such as character sets and coding system decoders.

The *ccs\_pool\_alloc*() function creates the cache pool object.

The *ccs\_pool\_free*() function frees the allocated resources of the
specified cache pool object.

The *ccs\_pool\_get\_charset*() function locates the character set
by ISO-IR code specified in data element and creates the character set
object for it and cache it. If the specified character set is already
present in the cache, then the existing object is returned.

# Return Value

The *ccs\_pool\_alloc*() function returns a pointer to the allocated and
initialized ccs\_pool structure. The *ccs\_pool\_get\_charset*() function
returns a pointer to character set object. On error, these functions
return NULL.

# Errors

*  ENOENT — No such file or directory. The character set specified by ISO-IR
   code does not found.
*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
*  EPROTO — Character set description file read or parsing error.
