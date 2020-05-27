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

/* NATS control set */

#define CCS_FO		0xc0000709	/* formatting			*/
#define CCS_ECD		0xc000070b	/* end of instruction		*/
#define CCS_SCD		0xc000070c	/* start of instruction		*/
#define CCS_QL		0xc000070d	/* quad left			*/
#define CCS_UR		0xc000070e	/* upper rail			*/
#define CCS_LR		0xc000070f	/* lower rail			*/
#define CCS_KW		0xc0000718	/* kill word			*/
#define CCS_SS		0xc000071c	/* super shift			*/
#define CCS_QC		0xc000071d	/* quad centre			*/
#define CCS_QR		0xc000071e	/* quad right			*/
#define CCS_JY		0xc000071f	/* justify			*/

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

/* ECMA-48 5.5 Independent control functions, ESC Fs */

#define CCS_DMI		0xc0000060
#define CCS_INT		0xc0000061
#define CCS_EMI		0xc0000062
#define CCS_RIS		0xc0000063
#define CCS_CMD		0xc0000064	/* ECMA-35 15.3 */
#define CCS_LS2		0xc000006e	/* ECMA-35 7.3 */
#define CCS_LS3		0xc000006f	/* ECMA-35 7.3 */

#define CCS_LS3R	0xc000007c	/* ECMA-35 7.3 */
#define CCS_LS2R	0xc000007d	/* ECMA-35 7.3 */
#define CCS_LS1R	0xc000007e	/* ECMA-35 7.3 */

/* ECMA-48 5.4 Control sequences, Table 3, CSI F without I */

#define CCS_ICH		0xf0000040
#define CCS_CUU		0xf0000041
#define CCS_CUD		0xf0000042
#define CCS_CUF		0xf0000043
#define CCS_CUB		0xf0000044
#define CCS_CNL		0xf0000045
#define CCS_CPL		0xf0000046
#define CCS_CHA		0xf0000047
#define CCS_CUP		0xf0000048
#define CCS_CHT		0xf0000049
#define CCS_ED		0xf000004a
#define CCS_EL		0xf000004b
#define CCS_IL		0xf000004c
#define CCS_DL		0xf000004d
#define CCS_EF		0xf000004e
#define CCS_EA		0xf000004f

#define CCS_DCH		0xf0000050
#define CCS_SSE		0xf0000051
#define CCS_CPR		0xf0000052
#define CCS_SU		0xf0000053
#define CCS_SD		0xf0000054
#define CCS_NP		0xf0000055
#define CCS_PP		0xf0000056
#define CCS_CTC		0xf0000057
#define CCS_ECH		0xf0000058
#define CCS_CVT		0xf0000059
#define CCS_CBT		0xf000005a
#define CCS_SRS		0xf000005b
#define CCS_PTX		0xf000005c
#define CCS_SDS		0xf000005d
#define CCS_SIMD	0xf000005e

#define CCS_HPA		0xf0000060
#define CCS_HPR		0xf0000061
#define CCS_REP		0xf0000062
#define CCS_DA		0xf0000063
#define CCS_VPA		0xf0000064
#define CCS_VPR		0xf0000065
#define CCS_HVP		0xf0000066
#define CCS_TBC		0xf0000067
#define CCS_SM		0xf0000068
#define CCS_MC		0xf0000069
#define CCS_HPB		0xf000006a
#define CCS_VPB		0xf000006b
#define CCS_RM		0xf000006c
#define CCS_SGR		0xf000006d
#define CCS_DSR		0xf000006e
#define CCS_DAQ		0xf000006f

/* ECMA-48 5.4 Control sequences, Table 4, CSI F with I = 02/00 */

#define CCS_SL		0xf1000040
#define CCS_SR		0xf1000041
#define CCS_GSM		0xf1000042
#define CCS_GSS		0xf1000043
#define CCS_FNT		0xf1000044
#define CCS_TSS		0xf1000045
#define CCS_JFY		0xf1000046
#define CCS_SPI		0xf1000047
#define CCS_QUAD	0xf1000048
#define CCS_SSU		0xf1000049
#define CCS_PFS		0xf100004a
#define CCS_SHS		0xf100004b
#define CCS_SVS		0xf100004c
#define CCS_IGS		0xf100004d
#define CCS_HTSA	0xf100004e
#define CCS_IDCS	0xf100004f

#define CCS_PPA		0xf1000050
#define CCS_PPR		0xf1000051
#define CCS_PPB		0xf1000052
#define CCS_SPD		0xf1000053
#define CCS_DTA		0xf1000054
#define CCS_SLH		0xf1000055
#define CCS_SLL		0xf1000056
#define CCS_FNK		0xf1000057
#define CCS_SPQR	0xf1000058
#define CCS_SEF		0xf1000059
#define CCS_PEC		0xf100005a
#define CCS_SSW		0xf100005b
#define CCS_SACS	0xf100005c
#define CCS_SAPV	0xf100005d
#define CCS_STAB	0xf100005e
#define CCS_GCC		0xf100005f

#define CCS_TATE	0xf1000060
#define CCS_TALE	0xf1000061
#define CCS_TAC		0xf1000062
#define CCS_TCC		0xf1000063
#define CCS_TSR		0xf1000064
#define CCS_SCO		0xf1000065
#define CCS_SRCS	0xf1000066
#define CCS_SCS		0xf1000067
#define CCS_SLS		0xf1000068
#define CCS_SPH		0xf1000069
#define CCS_SPL		0xf100006a
#define CCS_SCP		0xf100006b

#endif  /* CCS_CONTROL_H */
