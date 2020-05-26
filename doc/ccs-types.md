# Name

ccs-types — coded character set core types

# Synopsis

```c
#include <ccs-types.h>

struct ccs_de {
	ccs_code_t	code;	/* character code		*/
	ccs_size_t	size;	/* argument buffer size		*/
	ccs_size_t	len;	/* actual length of argument	*/
	unsigned char	arg[];	/* argument buffer		*/
};
```

# Description

The *ccs\_code\_t* is a unsigned integer capable to store Unicode codes.
It is intended to store control and graphic character codes. If a character
have a Unicode code then this code is used, overwise codes from Unicode
Private Use Area used.

The *ccs\_size\_t* is a unsigned integer used to store at least 16-bit values.
It is intended to store size of variable sized units of CCS library.

The *ccs\_de* structure represent a data element — CCS character with
an optional argument. This structure consists of the following fields:

*  code — a control or graphic character code;
*  size — the size of the argument buffer in characters, specified by
   the caller;
*  len  — the argument string length;
*  arg  — the argument buffer allocated by the caller.

Note that argument if present (length > 0) is the NUL-terminated string
and the field len specifies the length of that string without terminating
NUL character. In case of buffer overflow, field len will be equal to
the size of buffer and terminating character will not be written.
