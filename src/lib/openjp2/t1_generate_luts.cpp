/*
 * The copyright in this software is being made available under the 2-clauses
 * BSD License, included below. This software may be subject to other third
 * party and contributor rights, including patent rights, and no such rights
 * are granted under this license.
 *
 * Copyright (c) 2002-2014, Universite catholique de Louvain (UCL), Belgium
 * Copyright (c) 2002-2014, Professor Benoit Macq
 * Copyright (c) 2001-2003, David Janssens
 * Copyright (c) 2002-2003, Yannick Verschueren
 * Copyright (c) 2003-2007, Francois-Olivier Devaux
 * Copyright (c) 2003-2014, Antonin Descampe
 * Copyright (c) 2005, Herve Drolon, FreeImage Team
 * Copyright (c) 2007, Callum Lerwick <seg@haxxed.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS `AS IS'
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "opj_includes.h"

static int t1_init_ctxno_zc(int f, int orient)
{
    int h, v, d, n, t, hv;
    n = 0;
    h = ((f & T1_SIG_W) != 0) + ((f & T1_SIG_E) != 0);
    v = ((f & T1_SIG_N) != 0) + ((f & T1_SIG_S) != 0);
    d = ((f & T1_SIG_NW) != 0) + ((f & T1_SIG_NE) != 0) + ((f & T1_SIG_SE) != 0) + ((f & T1_SIG_SW) != 0);

    switch (orient) {
    case 2:
        t = h;
        h = v;
        v = t;
    case 0:
    case 1:
        if (!h) {
            if (!v) {
                if (!d)
                    n = 0;
                else if (d == 1)
                    n = 1;
                else
                    n = 2;
            } else if (v == 1) {
                n = 3;
            } else {
                n = 4;
            }
        } else if (h == 1) {
            if (!v) {
                if (!d)
                    n = 5;
                else
                    n = 6;
            } else {
                n = 7;
            }
        } else
            n = 8;
        break;
    case 3:
        hv = h + v;
        if (!d) {
            if (!hv) {
                n = 0;
            } else if (hv == 1) {
                n = 1;
            } else {
                n = 2;
            }
        } else if (d == 1) {
            if (!hv) {
                n = 3;
            } else if (hv == 1) {
                n = 4;
            } else {
                n = 5;
            }
        } else if (d == 2) {
            if (!hv) {
                n = 6;
            } else {
                n = 7;
            }
        } else {
            n = 8;
        }
        break;
    }

    return (T1_CTXNO_ZC + n);
}

static int t1_init_ctxno_zc_opt(int f, int orient)
{
    int h, v, d, n, t, hv;
    n = 0;
    h = ((f & T1_SIGMA_3) != 0) + ((f & T1_SIGMA_5) != 0);
    v = ((f & T1_SIGMA_1) != 0) + ((f & T1_SIGMA_7) != 0);
    d = ((f & T1_SIGMA_0) != 0) + ((f & T1_SIGMA_2) != 0) + ((f & T1_SIGMA_8) != 0) + ((f & T1_SIGMA_6) != 0);

    switch (orient) {
    case 2:
        t = h;
        h = v;
        v = t;
    case 0:
    case 1:
        if (!h) {
            if (!v) {
                if (!d)
                    n = 0;
                else if (d == 1)
                    n = 1;
                else
                    n = 2;
            } else if (v == 1) {
                n = 3;
            } else {
                n = 4;
            }
        } else if (h == 1) {
            if (!v) {
                if (!d)
                    n = 5;
                else
                    n = 6;
            } else {
                n = 7;
            }
        } else
            n = 8;
        break;
    case 3:
        hv = h + v;
        if (!d) {
            if (!hv) {
                n = 0;
            } else if (hv == 1) {
                n = 1;
            } else {
                n = 2;
            }
        } else if (d == 1) {
            if (!hv) {
                n = 3;
            } else if (hv == 1) {
                n = 4;
            } else {
                n = 5;
            }
        } else if (d == 2) {
            if (!hv) {
                n = 6;
            } else {
                n = 7;
            }
        } else {
            n = 8;
        }
        break;
    }

    return (T1_CTXNO_ZC + n);
}

static int t1_init_ctxno_sc(int f)
{
    int hc, vc, n;
    n = 0;

    hc = opj_int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
                      T1_SIG_E) + ((f & (T1_SIG_W | T1_SGN_W)) == T1_SIG_W),
                     1) - opj_int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
                                       (T1_SIG_E | T1_SGN_E)) +
                                      ((f & (T1_SIG_W | T1_SGN_W)) ==
                                       (T1_SIG_W | T1_SGN_W)), 1);

    vc = opj_int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
                      T1_SIG_N) + ((f & (T1_SIG_S | T1_SGN_S)) == T1_SIG_S),
                     1) - opj_int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
                                       (T1_SIG_N | T1_SGN_N)) +
                                      ((f & (T1_SIG_S | T1_SGN_S)) ==
                                       (T1_SIG_S | T1_SGN_S)), 1);

    if (hc < 0) {
        hc = -hc;
        vc = -vc;
    }
    if (!hc) {
        if (vc == -1)
            n = 1;
        else if (!vc)
            n = 0;
        else
            n = 1;
    } else if (hc == 1) {
        if (vc == -1)
            n = 2;
        else if (!vc)
            n = 3;
        else
            n = 4;
    }

    return (T1_CTXNO_SC + n);
}


static int t1_init_ctxno_sc_opt(int f)
{
    int hc, vc, n;
    n = 0;

    hc = opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                      T1_LUT_SIG_E) + ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) == T1_LUT_SIG_W),
                     1) - opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                                       (T1_LUT_SIG_E | T1_LUT_SGN_E)) +
                                      ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) ==
                                       (T1_LUT_SIG_W | T1_LUT_SGN_W)), 1);

    vc = opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                      T1_LUT_SIG_N) + ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) == T1_LUT_SIG_S),
                     1) - opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                                       (T1_LUT_SIG_N | T1_LUT_SGN_N)) +
                                      ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) ==
                                       (T1_LUT_SIG_S | T1_LUT_SGN_S)), 1);

    if (hc < 0) {
        hc = -hc;
        vc = -vc;
    }
    if (!hc) {
        if (vc == -1)
            n = 1;
        else if (!vc)
            n = 0;
        else
            n = 1;
    } else if (hc == 1) {
        if (vc == -1)
            n = 2;
        else if (!vc)
            n = 3;
        else
            n = 4;
    }

    return (T1_CTXNO_SC + n);
}

static int t1_init_spb(int f)
{
    int hc, vc, n;

    hc = opj_int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
                      T1_SIG_E) + ((f & (T1_SIG_W | T1_SGN_W)) == T1_SIG_W),
                     1) - opj_int_min(((f & (T1_SIG_E | T1_SGN_E)) ==
                                       (T1_SIG_E | T1_SGN_E)) +
                                      ((f & (T1_SIG_W | T1_SGN_W)) ==
                                       (T1_SIG_W | T1_SGN_W)), 1);

    vc = opj_int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
                      T1_SIG_N) + ((f & (T1_SIG_S | T1_SGN_S)) == T1_SIG_S),
                     1) - opj_int_min(((f & (T1_SIG_N | T1_SGN_N)) ==
                                       (T1_SIG_N | T1_SGN_N)) +
                                      ((f & (T1_SIG_S | T1_SGN_S)) ==
                                       (T1_SIG_S | T1_SGN_S)), 1);

    if (!hc && !vc)
        n = 0;
    else
        n = (!(hc > 0 || (!hc && vc > 0)));

    return n;
}


static int t1_init_spb_opt(int f)
{
    int hc, vc, n;

    hc = opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                      T1_LUT_SIG_E) + ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) == T1_LUT_SIG_W),
                     1) - opj_int_min(((f & (T1_LUT_SIG_E | T1_LUT_SGN_E)) ==
                                       (T1_LUT_SIG_E | T1_LUT_SGN_E)) +
                                      ((f & (T1_LUT_SIG_W | T1_LUT_SGN_W)) ==
                                       (T1_LUT_SIG_W | T1_LUT_SGN_W)), 1);

    vc = opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                      T1_LUT_SIG_N) + ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) == T1_LUT_SIG_S),
                     1) - opj_int_min(((f & (T1_LUT_SIG_N | T1_LUT_SGN_N)) ==
                                       (T1_LUT_SIG_N | T1_LUT_SGN_N)) +
                                      ((f & (T1_LUT_SIG_S | T1_LUT_SGN_S)) ==
                                       (T1_LUT_SIG_S | T1_LUT_SGN_S)), 1);

    if (!hc && !vc)
        n = 0;
    else
        n = (!(hc > 0 || (!hc && vc > 0)));

    return n;
}

static void dump_array16(int array[],int size)
{
    int i;
    --size;
    for (i = 0; i < size; ++i) {
        printf("0x%04x, ", array[i]);
        if(!((i+1)&0x7))
            printf("\n  ");
    }
    printf("0x%04x\n};\n\n", array[size]);
}

int main(int argc, char **argv)
{
    int i, j;
    double u, v, t;

    int lut_ctxno_zc[1024];
    int lut_ctxno_zc_opt[2048];
    int lut_nmsedec_sig[1 << T1_NMSEDEC_BITS];
    int lut_nmsedec_sig0[1 << T1_NMSEDEC_BITS];
    int lut_nmsedec_ref[1 << T1_NMSEDEC_BITS];
    int lut_nmsedec_ref0[1 << T1_NMSEDEC_BITS];
    (void)argc;
    (void)argv;

    printf("/* This file was automatically generated by t1_generate_luts.c */\n\n");

    /* lut_ctxno_zc */
    for (j = 0; j < 4; ++j) {
        for (i = 0; i < 256; ++i) {
            int orient = j;
            if (orient == 2) {
                orient = 1;
            } else if (orient == 1) {
                orient = 2;
            }
            lut_ctxno_zc[(orient << 8) | i] = t1_init_ctxno_zc(i, j);
        }
    }

    printf("static uint8_t lut_ctxno_zc[1024] = {\n  ");
    for (i = 0; i < 1023; ++i) {
        printf("%i, ", lut_ctxno_zc[i]);
        if(!((i+1)&0x1f))
            printf("\n  ");
    }
    printf("%i\n};\n\n", lut_ctxno_zc[1023]);

    /* lut_ctxno_zc_opt */
    for (j = 0; j < 4; ++j) {
        for (i = 0; i < 512; ++i) {
            int orient = j;
            if (orient == 2) {
                orient = 1;
            } else if (orient == 1) {
                orient = 2;
            }
            lut_ctxno_zc_opt[(orient << 9) | i] = t1_init_ctxno_zc_opt(i, j);
        }
    }

    printf("static uint8_t lut_ctxno_zc_opt[2048] = {\n  ");
    for (i = 0; i < 2047; ++i) {
        printf("%i, ", lut_ctxno_zc_opt[i]);
        if (!((i + 1) & 0x1f))
            printf("\n  ");
    }
    printf("%i\n};\n\n", lut_ctxno_zc_opt[2047]);

    /* lut_ctxno_sc */
    printf("static uint8_t lut_ctxno_sc[256] = {\n  ");
    for (i = 0; i < 255; ++i) {
        printf("0x%x, ", t1_init_ctxno_sc(i << 4));
        if(!((i+1)&0xf))
            printf("\n  ");
    }
    printf("0x%x\n};\n\n", t1_init_ctxno_sc(255 << 4));


    /* lut_ctxno_sc_opt */
    printf("static uint8_t lut_ctxno_sc_opt[256] = {\n  ");
    for (i = 0; i < 255; ++i) {
        printf("0x%x, ", t1_init_ctxno_sc_opt(i));
        if (!((i + 1) & 0xf))
            printf("\n  ");
    }
    printf("0x%x\n};\n\n", t1_init_ctxno_sc_opt(255));


    /* lut_spb */
    printf("static uint8_t lut_spb[256] = {\n  ");
    for (i = 0; i < 255; ++i) {
        printf("%i, ", t1_init_spb(i << 4));
        if(!((i+1)&0x1f))
            printf("\n  ");
    }
    printf("%i\n};\n\n", t1_init_spb(255 << 4));


    /* lut_spb_opt */
    printf("static uint8_t lut_spb_opt[256] = {\n  ");
    for (i = 0; i < 255; ++i) {
        printf("%i, ", t1_init_spb_opt(i));
        if (!((i + 1) & 0x1f))
            printf("\n  ");
    }
    printf("%i\n};\n\n", t1_init_spb_opt(255));

    /* FIXME FIXME FIXME */
    /* fprintf(stdout,"nmsedec luts:\n"); */
    for (i = 0; i < (1 << T1_NMSEDEC_BITS); ++i) {
        t = i / pow(2, T1_NMSEDEC_FRACBITS);
        u = t;
        v = t - 1.5;
        lut_nmsedec_sig[i] =
            opj_int_max(0,
                        (int) (floor((u * u - v * v) * pow(2, T1_NMSEDEC_FRACBITS) + 0.5) / pow(2, T1_NMSEDEC_FRACBITS) * 8192.0));
        lut_nmsedec_sig0[i] =
            opj_int_max(0,
                        (int) (floor((u * u) * pow(2, T1_NMSEDEC_FRACBITS) + 0.5) / pow(2, T1_NMSEDEC_FRACBITS) * 8192.0));
        u = t - 1.0;
        if (i & (1 << (T1_NMSEDEC_BITS - 1))) {
            v = t - 1.5;
        } else {
            v = t - 0.5;
        }
        lut_nmsedec_ref[i] =
            opj_int_max(0,
                        (int) (floor((u * u - v * v) * pow(2, T1_NMSEDEC_FRACBITS) + 0.5) / pow(2, T1_NMSEDEC_FRACBITS) * 8192.0));
        lut_nmsedec_ref0[i] =
            opj_int_max(0,
                        (int) (floor((u * u) * pow(2, T1_NMSEDEC_FRACBITS) + 0.5) / pow(2, T1_NMSEDEC_FRACBITS) * 8192.0));
    }

    printf("static int16_t lut_nmsedec_sig[1 << T1_NMSEDEC_BITS] = {\n  ");
    dump_array16(lut_nmsedec_sig, 1 << T1_NMSEDEC_BITS);

    printf("static int16_t lut_nmsedec_sig0[1 << T1_NMSEDEC_BITS] = {\n  ");
    dump_array16(lut_nmsedec_sig0, 1 << T1_NMSEDEC_BITS);

    printf("static int16_t lut_nmsedec_ref[1 << T1_NMSEDEC_BITS] = {\n  ");
    dump_array16(lut_nmsedec_ref, 1 << T1_NMSEDEC_BITS);

    printf("static int16_t lut_nmsedec_ref0[1 << T1_NMSEDEC_BITS] = {\n  ");
    dump_array16(lut_nmsedec_ref0, 1 << T1_NMSEDEC_BITS);

    return 0;
}