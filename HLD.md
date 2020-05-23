# Caracter Code Structure and Extension Techniques

## Coding System

*  Function: parse input to sequence of codes.
*  Input: unspecified, depends on coding system.
*  Output: sequence of codes.

Standart ECMA-35 requires that, regardless of the encoding system used,
the following three characters always have fixed code positions:

*  Delete, DEL — 07/15.
*  Escape, ESC — 01/11.
*  Space,  SP  — 02/00.

We define two types of decoders, raw and unicode:

*  Raw: output 7- or 8-bit codes, ECMA-35 conditions are meet.
*  Unicode: output Unicode codes.

For unicode decoder input characters that have Unicode codes are mapped
to them, the rest are mapped into Private Use Area into window from U+F000
to U+F8FF. Since unicode decoder converts to Unicode, the ECMA-35 condition
is always fulfilled.

## Data Element

A data element is either a character encoded as a true Unicode character,
or a special control character, possibly with a an argument.

## Character Mapping

*  Function: convert sequence of codes.
*  Input: sequence of codes.
*  Output: sequence of Unicode codes.

The system has six mapping tables: two for converting control characters
(C0 and C1 sets) and four for converting graphic characters (G0 — G3 sets).

Standard ECMA-35 defines four disjoint code windows:

*  CL in range from 00/00 to 01/15 for designated and invoked C0 set.
*  GL in range from 02/01 to 07/14 for invoked graphic set, any of the sets
   from G0 — G3 can be invoken in this window.
*  CR in range from 08/00 to 09/15 for designated and invoked C1 set.
*  GR in range from 10/00 to 15/00 for invoked graphic set, any of the sets
   from G1 — G3 can be invoken in this window.

And, as stated earlier, the characters SP and DEL have fixed positions.
We add the U window to which all characters with codes over 15/15 fall.
This window always has a one-to-one mapping.

If there is no match for the active mapping for the input code, then such
code is silently discarded. If a graphic symbol is present in the invoked
set, but cannot be converted to a Unicode symbol, then symbol SUB is
substituted:

*  Substitute, SUB — 01/10.

## Escape Sequence Parser

*  Function: convert sequence of codes to sequence of data elements.
*  Input: sequence of codes.
*  Output: sequence of data elements.

If the input code is not part of the escape sequence, then it is mapped
to a character. Symbols NUL and SYN, if present in the input, are silently
discarded:

*  Null, NUL — 00/00.
*  Synchronous Idle, SYN — 01/06.

It is worth noting that the parser works with untransformed characters at
the input.

## Control Sequence Parser

*  Function: parse control sequences to sequence of data elements.
*  Input: sequence of data elements.
*  Output: sequence of data elements without control sequence introducers.

Will be defined later.

## Annex A: C Language Interface

This annex describes the C language interface for the Caracter Code
Structure library.

### Core Types

ccs-types — coded character set core types

#### Synopsis

```c
#include <ccs-types.h>

struct ccs_de {
	ccs_code_t	code;	/* character code		*/
	ccs_size_t	size;	/* argument buffer size		*/
	ccs_size_t	len;	/* actual length of argument	*/
	unsigned char	arg[];	/* argument buffer		*/
};
```

#### Description

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

### Character Set

ccs-charset — coded character set's character set interface

#### Synopsis

```c
#include <ccs-charset.h>

struct ccs_charset *ccs_charset_alloc (FILE *f);
void ccs_charset_free (struct ccs_charset *o);

struct ccs_charset *ccs_charset_locate (const struct ccs_de *de);
```

#### Description

The *ccs\_charset\_alloc*() function creates the character set object and
initializes it based on the description from the character set description
file.

The *ccs\_charset\_free*() function frees the allocated resources of the
specified character set object.

The *ccs\_charset\_locate*() function locates the character set by ISO-IR
code specified in data element and creates the character set object for it.

#### Return Value

The *ccs\_charset\_alloc*() and *ccs\_charset\_locate*() functions returns
a pointer to the allocated and initialized ccs\_charset structure.
On error, these functions return NULL.

#### Errors

*ccs\_charset\_alloc* and *ccs\_charset\_locate* can fail with
the following errors:

*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
*  EPROTO — Character set description file read or parsing error.

### Pool

ccs-pool — coded character set cache pool

#### Synopsis

```c
#include <ccs-pool.h>

struct ccs_pool *ccs_pool_alloc (void);
void ccs_pool_free (struct ccs_pool *o);

struct ccs_charset *
ccs_pool_get_charset (struct ccs_pool *o, const struct ccs_de *de);
```

#### Description

The coded character set cache pool is intended for caching CCS objects,
such as character sets and coding system decoders.

The *ccs\_pool\_alloc*() function creates the cache pool object.

The *ccs\_pool\_free*() function frees the allocated resources of the
specified cache pool object.

The *ccs\_pool\_get\_charset*() function locates the character set
by ISO-IR code specified in data element and creates the character set
object for it and cache it. If the specified character set is already
present in the cache, then the existing object is returned.

#### Return Value

The *ccs\_pool\_alloc*() function returns a pointer to the allocated and
initialized ccs\_pool structure. The *ccs\_pool\_get\_charset*() function
returns a pointer to character set object. On error, these functions
return NULL.

#### Errors

*  ENOENT — No such file or directory. The character set specified by ISO-IR
   code does not found.
*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.
*  EPROTO — Character set description file read or parsing error.

### Character Mapping

ccs-map — coded character set character mapping

#### Synopsis

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

#### Description

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

#### Return Value

The *ccs\_map\_alloc*() function returns a pointer to the allocated and
initialized ccs\_map structure or NULL in case of errors.

Upon successful completion *ccs\_map\_load\_cs*() and *ccs\_map\_load\_gs*(),
as well as *ccs\_map\_lock\_gl*(), *ccs\_map\_lock\_gr*() and
*ccs\_map\_shift\_gl*() functions return non-zero. Otherwise, zero is
returned and errno is set to indicate the error.

The *ccs\_map\_process*() returns the converted code or 0 if input code
consumed but the output character is not available yet (in case of
a multibyte character set is invoked) or no match for input code found.

#### Errors

*  EINVAL — Invalid set index is specified.
*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.

### Escape and Control Sequence Parser

ccs-core — coded character set escape and control sequence parser

#### Synopsis

```c
#include <ccs-core.h>

struct ccs_core *ccs_core_alloc (void);
void ccs_core_free (struct ccs_core *o);

int ccs_core_process (struct ccs_core *o, ccs_code_t c, struct ccs_de *de);
```

#### Description

Escape and control sequence parser intended for parsing ECMA-35 escape
sequences and ECMA-48 control sequences.

The *ccs\_core\_alloc*() function creates the escape and control sequence
parser object.

The *ccs\_core\_free*() function frees the allocated resources of the
specified escape and control equencearser object.

The *ccs\_core\_process*() function parses ECMA-35 escape sequences and
ECMA-48 control sequences.

#### Return Value

The *ccs\_core\_alloc*() function returns a pointer to the allocated and
initialized ccs\_core structure or NULL in case of errors.

The *ccs\_core\_process*() returns non-zero and resulting data element or
0 if input code consumed but the output data element is not available yet,
either NUL or SYN characters is given as an input code.

#### Errors

*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.

### Upper Level Interface

ccs — coded character set processor

#### Synopsis

```c
#include <ccs.h>

struct ccs *ccs_alloc (void);
void ccs_free (struct ccs *o);

int ccs_process (struct ccs *o, ccs_code_t c, struct ccs_de *de);
```

#### Description

Constructor creates and incapsulates character mapping, escape sequence
parser and conrol sequence parser objects.

Process method:

1. parses escape and control sequences;
2. process character set designate, invoke, lock and shift operations;
3. maps characters;

#### Return Value

The *ccs\_alloc*() function returns a pointer to the allocated and
initialized ccs structure or NULL in case of errors.

The *ccs\_process*() returns non-zero and resulting data element or 0
if input code consumed but the output data element is not available yet,
either NUL or SYN characters is given as an input code.

#### Errors

*  ENOMEM — Out of memory. See *malloc*(3) for a more detailed description.

