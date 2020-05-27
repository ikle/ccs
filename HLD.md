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

*  [ccs-types][] — coded character set core types
*  [ccs-charset][] — coded character set's character set interface
*  [ccs-pool][] — coded character set cache pool
*  [ccs-map][] — coded character set character mapping
*  [ccs-core][] — coded character set escape and control sequence parser

[ccs-types]:	doc/ccs-types.md
[ccs-charset]:	doc/ccs-charset.md
[ccs-pool]:	doc/ccs-pool.md
[ccs-map]:	doc/ccs-map.md
[ccs-core]:	doc/ccs-core.md

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

## Annex B: Character Set Mapping File Format

We use EBNF-like grammar with the following extensions:

*  α is any character;
*  ε is an empty string;
*  the character in single quotes is a character literal;
*  expression X .. Y defines any character in range from X to Y inclusive;
*  the full stop is the grammar terminator.

The grammar for character set mapping file format follows:

``` ebnf
digit		= '0' .. '9';
alpha		= 'a' .. 'z';
hex digit	= digit | 'a' .. 'f';

number		= (digit - '0'), {digit};		(* non-zero *)
name		= alpha, {['-'], (alpha | digit)};
space		= {SP | TAB} - ε;

size		= "# Size:",   space, number, LF;
order		= "# Order:",  space, number, LF;
parent		= "# Parent:", space, name,   LF;

define		= size | order | parent;
comment		= ('#', {α - LF}, LF) - define;

code		= {hex digit, hex digit} - ε;	(* should be: order times *)
code-point	= {hex digit} - ε;		(* should be: from 1 to 6 *)

map		= code, space, code-point, [space], comment | LF;

charset		= {define | comment | LF | map} - ε.
```

Any line must be no more than 77 characters. The size and order (degree) of
the character are taken from the first encountered fields Size and Order
(specified directly or in the parent file), all others are ignored.

## Annex C: Private Code Construction

Unicode codes occupy a space of 21 bits, and type for ccs\_code\_t has
a size of at least 32 bits. The space unused by Unicode codes will be used
as follows:

1. C0yy'yyxx — the leading hexadecimal digit of the number is C for control
   characters.
2. Enii'iixx — the leading digit is E for escape sequences.
3. Fnii'iixx — the leading digit is F for CSI control sequences (control
   functions in terms of ECMA-48).

The two least significant hexadecimal digits (xx) represent the original
serial number of the control code for control characters. The next four
(yyyy) are binary-coded decimal representing the registration number for
this control code group.

Example for NATS (ISO-IR-007):
```c
#define CCS_FO		0xc0000709
#define CCS_ECD		0xc000070b
#define CCS_SCD		0xc000070c
...
#define CCS_JY		0xc000071f
```

Codes for escape sequences of type Fe are mapped directly to equivalent C1
codes. Codes for type Fs and type nF other than 3F (first intermediate byte
is 02/03) are allocated as control codes with registration number 0.

Example for Fs (lower byte equals to final):
```c
#define CCS_DMI		0xc0000060	/* ESC 06/00 */
...
#define CCS_RIS		0xc0000063	/* ESC 06/03 */
```

Example for nF other than 3F (lower byte equals to type byte):
```c
#define CCS_ACS		0xc0000020	/* ESC 02/00 ... */
#define CCS_CZD		0xc0000021	/* ESC 02/01 ... */
#define CCS_C1D		0xc0000022	/* ESC 02/02 ... */
...
#define CCS_DOCS	0xc0000025	/* ESC 02/05 ... */
```

Note that all additional intermediate bytes and the final byte for type nF
other than 3F (3Fp and Ft) are parameter bytes.

The two least significant hexadecimal digits (xx) for escape and control
functions represent the final byte for such sequences. The next four
(iiii) are intermediate byte lower digits, excluding the first intermediate
byte (02/03) for escape sequences. And penultimate one (n) is a number of
intermediate bytes coded.

Example for 3Fp without extra intermediate bytes:
```c
#define CCS_XXX		0xe0000030	/* ESC 02/03 03/00 */
```

Example for Ft with one extra intermediate byte:
```c
#define CCS_YYY		0xe1000642	/* ESC 02/03 02/06 04/02 */
```

Example for Ft with two extra intermediate bytes:
```c
#define CCS_ZZZ		0xe200736d	/* ESC 02/03 02/07 02/03 06/13 */
```

Examples for CSI code encoding:
```c
#define CCS_CUD		0xf0000043	/* CSI ... 04/03 */
...
#define CCS_SGR		0xf000006d	/* CSI ... 06/13 */
...
#define CCS_GCC		0xf100005f	/* CSI ... 02/00 05/15 */
```
