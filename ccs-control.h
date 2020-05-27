/*
 * Coded Character Set Control Codes
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35, ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_CONTROL_H
#define CCS_CONTROL_H  1

/* ECMA-35 6.2 Fixed coded characters */

#define CCS_DEL		0x7f
#define CCS_SP		0x20

/* ECMA-48 5.2 Elements of C0 set */

#define CCS_NUL		0x00
#define CCS_SOH		0x01
#define CCS_STX		0x02
#define CCS_ETX		0x03
#define CCS_EOT		0x04
#define CCS_ENQ		0x05
#define CCS_ACK		0x06
#define CCS_BEL		0x07
#define CCS_BS		0x08
#define CCS_HT		0x09
#define CCS_LF		0x0a
#define CCS_VT		0x0b
#define CCS_FF		0x0c
#define CCS_CR		0x0d
#define CCS_SO		0x0e	/* ECMA-35 7.3 */
#define CCS_SI		0x0f	/* ECMA-35 7.3 */

#define CCS_LS0		CCS_SI	/* ECMA-35 7.3 */
#define CCS_LS1		CCS_SO	/* ECMA-35 7.3 */

#define CCS_DLE		0x10
#define CCS_DC1		0x11
#define CCS_DC2		0x12
#define CCS_DC3		0x13
#define CCS_DC4		0x14
#define CCS_NAK		0x15
#define CCS_SYN		0x16
#define CCS_ETB		0x17
#define CCS_CAN		0x18
#define CCS_EM		0x19
#define CCS_SUB		0x1a
#define CCS_ESC		0x1b	/* ECMA-35 6.2 */
#define CCS_IS4		0x1c
#define CCS_IS3		0x1d
#define CCS_IS2		0x1e
#define CCS_IS1		0x1f

/* ECMA-48 8.2.10 Information separators */

#define CCS_FS		CCS_IS4
#define CCS_GS		CCS_IS3
#define CCS_RS		CCS_IS2
#define CCS_US		CCS_IS1

/* ECMA-48 8.3.28 DC1, 8.3.30 DC3 */

#define CCS_XON		CCS_DC1
#define CCS_XOFF	CCS_DC3

/* ECMA-48 5.3 Elements of C1 set */

#define CCS_PAD		0x80	/* ISO 2022 padding character		*/
#define CCS_HOP		0x81	/* RFC 1342, high octet present		*/
#define CCS_BPH		0x82
#define CCS_NBH		0x83
#define CCS_IND		0x84	/* index, deprecated, f.8.2	*/
#define CCS_NEL		0x85
#define CCS_SSA		0x86	/* start of selected area, 6.5.1	*/
#define CCS_ESA		0x87	/* end of selected area, 6.5.1		*/
#define CCS_HTS		0x88	/* character tabulation set, 6.7	*/
#define CCS_HTJ		0x89
#define CCS_VTS		0x8a	/* line tabulation set, 6.7		*/
#define CCS_PLD		0x8b	/* partial line forward,  8.3.92	*/
#define CCS_PLU		0x8c	/* partial line backward, 8.3.93	*/
#define CCS_RI		0x8d
#define CCS_SS2		0x8e	/* ECMA-35 7.3 */
#define CCS_SS3		0x8f	/* ECMA-35 7.3 */

#define CCS_DCS		0x90	/* device control string, 5.6		*/
#define CCS_PU1		0x91
#define CCS_PU2		0x92
#define CCS_STS		0x93
#define CCS_CCH		0x94	/* cancel character, 8.3.8		*/
#define CCS_MW		0x95
#define CCS_SPA		0x96	/* start of guarded area, 6.5.2.2	*/
#define CCS_EPA		0x97	/* end of guarded area, 6.5.2.2		*/
#define CCS_SOS		0x98	/* start of string, 5.6			*/
#define CCS_SGCI	0x99	/* RFC 1345 single graphic char introd.	*/
#define CCS_SCI		0x9a
#define CCS_CSI		0x9b	/* control sequence introducer, 5.4	*/
#define CCS_ST		0x9c	/* string terminator, 5.6		*/
#define CCS_OSC		0x9d	/* operating system command, 5.6	*/
#define CCS_PM		0x9e	/* privacy message, 5.6			*/
#define CCS_APC		0x9f	/* application program command, 5.6	*/

/* ECMA-35 13.2 Types of escape sequences */

#define CCS_ACS		0xc0000020
#define CCS_CZD		0xc0000021
#define CCS_C1D		0xc0000022
#define CCS_GDM		0xc0000024
#define CCS_DOCS	0xc0000025
#define CCS_IRR		0xc0000026
#define CCS_GZD4	0xc0000028
#define CCS_G1D4	0xc0000029
#define CCS_G2D4	0xc000002a
#define CCS_G3D4	0xc000002b
#define CCS_G1D6	0xc000002d
#define CCS_G2D6	0xc000002e
#define CCS_G3D6	0xc000002f

#endif  /* CCS_CONTROL_H */
