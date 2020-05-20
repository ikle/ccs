/*
 * Coded Character Set Escape and Control Sequence Finals
 *
 * Copyright (c) 2020 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * Standard: ECMA-35, ECMA-48
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef CCS_FINAL_H
#define CCS_FINAL_H  1

/* ECMA-35 13.2 Types of escape sequences */

#define CCS_T_ACS	0x20	/* Announce Code Structure		*/
#define CCS_T_CZD	0x21	/* C0-designate				*/
#define CCS_T_C1D	0x22	/* C1-designate				*/
#define CCS_T_3FP	0x23	/* single control function		*/
#define CCS_T_GDM	0x24	/* designation of miltiple-byte charsets */
#define CCS_T_DOCS	0x25	/* Designate Other Coding System	*/
#define CCS_T_IRR	0x26	/* Identity Revised Registration	*/
#define CCS_T_GZD4	0x28	/* G0-designate 94-set			*/
#define CCS_T_G1D4	0x29	/* G1-designate 94-set			*/
#define CCS_T_G2D4	0x2a	/* G2-designate 94-set			*/
#define CCS_T_G3D4	0x2b	/* G3-designate 94-set			*/
#define CCS_T_G1D6	0x2d	/* G1-designate 96-set			*/
#define CCS_T_G2D6	0x2e	/* G2-designate 96-set			*/
#define CCS_T_G3D6	0x2f	/* G3-designate 96-set			*/

#define CCS_T_FP	0x30	/* private control function		*/
#define CCS_T_FE	0x40	/* control function in C1 set		*/
#define CCS_T_FS	0x60	/* standardized control function	*/

/* ECMA-48 5.4 Control sequences, Table 3, CSI F without I */

#define CCS_F_ICH	0x40
#define CCS_F_CUU	0x41
#define CCS_F_CUD	0x42
#define CCS_F_CUF	0x43
#define CCS_F_CUB	0x44
#define CCS_F_CNL	0x45
#define CCS_F_CPL	0x46
#define CCS_F_CHA	0x47
#define CCS_F_CUP	0x48
#define CCS_F_CHT	0x49	/* cursor forward tabulation, 8.3.10	*/
#define CCS_F_ED	0x4a
#define CCS_F_EL	0x4b
#define CCS_F_IL	0x4c
#define CCS_F_DL	0x4d
#define CCS_F_EF	0x4e
#define CCS_F_EA	0x4f

#define CCS_F_DCH	0x50
#define CCS_F_SSE	0x51
#define CCS_F_CPR	0x52
#define CCS_F_SU	0x53	/* scroll up,   8.3.147	*/
#define CCS_F_SD	0x54	/* scroll down, 8.3.113	*/
#define CCS_F_NP	0x55
#define CCS_F_PP	0x56
#define CCS_F_CTC	0x57	/* cursor tabulation control, 6.7	*/
#define CCS_F_ECH	0x58
#define CCS_F_CVT	0x59	/* cursor line tabulation, 8.3.23	*/
#define CCS_F_CBT	0x5a	/* cursor backward tabulation, 8.3.7	*/
#define CCS_F_SRS	0x5b
#define CCS_F_PTX	0x5c
#define CCS_F_SDS	0x5d
#define CCS_F_SIMD	0x5e

#define CCS_F_HPA	0x60	/* character position absolute, 8.3.57	*/
#define CCS_F_HPR	0x61	/* character position forward, 8.3.59	*/
#define CCS_F_REP	0x62
#define CCS_F_DA	0x63
#define CCS_F_VPA	0x64	/* line position absolute, 8.3.158	*/
#define CCS_F_VPR	0x65	/* line position forward, 8.3.160	*/
#define CCS_F_HVP	0x66
#define CCS_F_TBC	0x67
#define CCS_F_SM	0x68	/* set mode, 7.1	*/
#define CCS_F_MC	0x69	/* media copy, 6.6	*/
#define CCS_F_HPB	0x6a	/* character position backward, 8.3.58	*/
#define CCS_F_VPB	0x6b	/* line position backward, 8.3.159	*/
#define CCS_F_RM	0x6c	/* reset mode, 7.1	*/
#define CCS_F_SGR	0x6d
#define CCS_F_DSR	0x6e
#define CCS_F_DAQ	0x6f	/* define area qualification, 6.5.2	*/

/* ECMA-48 5.4 Control sequences, Table 4, CSI F with I = 02/00 */

#define CCS_F_SL	0x40	/* scroll left,  8.3.121	*/
#define CCS_F_SR	0x41	/* scroll right, 8.3.135	*/
#define CCS_F_GSM	0x42
#define CCS_F_GSS	0x43
#define CCS_F_FNT	0x44
#define CCS_F_TSS	0x45
#define CCS_F_JFY	0x46
#define CCS_F_SPI	0x47
#define CCS_F_QUAD	0x48
#define CCS_F_SSU	0x49
#define CCS_F_PFS	0x4a
#define CCS_F_SHS	0x4b
#define CCS_F_SVS	0x4c
#define CCS_F_IGS	0x4d
#define CCS_F_HTSA	0x4e	/* char tab set abs, deprecated, f.8.3	*/
#define CCS_F_IDCS	0x4f

#define CCS_F_PPA	0x50	/* page position absolute, 8.3.96	*/
#define CCS_F_PPR	0x51	/* page position forward,  8.3.98	*/
#define CCS_F_PPB	0x52	/* page position backward, 8.3.97	*/
#define CCS_F_SPD	0x53
#define CCS_F_DTA	0x54	/* dimension text area, 8.3.36	*/
#define CCS_F_SLH	0x55	/* set line home,  8.3.122	*/
#define CCS_F_SLL	0x56	/* set line limit, 8.3.123	*/
#define CCS_F_FNK	0x57
#define CCS_F_SPQR	0x58
#define CCS_F_SEF	0x59
#define CCS_F_PEC	0x5a
#define CCS_F_SSW	0x5b
#define CCS_F_SACS	0x5c
#define CCS_F_SAPV	0x5d
#define CCS_F_STAB	0x5e
#define CCS_F_GCC	0x5f

#define CCS_F_TATE	0x60	/* tabulation aligned trailing edge, 6.7 */
#define CCS_F_TALE	0x61	/* tabulation aligned leading edge, 6.7	*/
#define CCS_F_TAC	0x62	/* tabulation aligned centered, 6.7	*/
#define CCS_F_TCC	0x63	/* tabulation centered on character, 6.7 */
#define CCS_F_TSR	0x64
#define CCS_F_SCO	0x65
#define CCS_F_SRCS	0x66
#define CCS_F_SCS	0x67
#define CCS_F_SLS	0x68
#define CCS_F_SPH	0x69	/* set page home,  8.3.131	*/
#define CCS_F_SPL	0x6a	/* set page limit, 8.3.133	*/
#define CCS_F_SCP	0x6b

/* ECMA-48 5.5 Independent control functions, ESC Fs */

#define CCS_F_DMI	0x60
#define CCS_F_INT	0x61
#define CCS_F_EMI	0x62
#define CCS_F_RIS	0x63
#define CCS_F_CMD	0x64	/* ECMA-35 15.3 */
#define CCS_F_LS2	0x6e	/* ECMA-35 7.3 */
#define CCS_F_LS3	0x6f	/* ECMA-35 7.3 */

#define CCS_F_LS3R	0x7c	/* ECMA-35 7.3 */
#define CCS_F_LS2R	0x7d	/* ECMA-35 7.3 */
#define CCS_F_LS1R	0x7e	/* ECMA-35 7.3 */

#endif  /* CCS_FINAL_H */
