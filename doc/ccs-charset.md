# Name

ccs-charset — coded character set's character set interface

# Synopsis

```c
#include <ccs-charset.h>

struct ccs_charset *ccs_charset_alloc (FILE *f);
void ccs_charset_free (struct ccs_charset *o);

struct ccs_charset *ccs_charset_locate (const struct ccs_de *de);
```

# Description

The *ccs\_charset\_alloc*() function creates the character set object and
initializes it based on the description from the character set description
file.

The *ccs\_charset\_free*() function frees the allocated resources of the
specified character set object.

The *ccs\_charset\_locate*() function locates the character set by ISO-IR
code specified in data element and creates the character set object for it.

# Return Value

The *ccs\_charset\_alloc*() and *ccs\_charset\_locate*() functions returns
a pointer to the allocated and initialized ccs\_charset structure.
On error, these functions return NULL.

# Errors

*ccs\_charset\_alloc* and *ccs\_charset\_locate* can fail with
the following errors:

*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
*  EPROTO — Character set description file read or parsing error.
