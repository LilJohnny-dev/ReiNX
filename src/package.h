/*
* Copyright (c) 2018 naehrwert, CTCaer, Reisyukaku
*
* This program is free software; you can redistribute it and/or modify it
* under the terms and conditions of the GNU General Public License,
* version 2, as published by the Free Software Foundation.
*
* This program is distributed in the hope it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
* FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
* more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once
#include "hwinit.h"

#define PKG2_MAGIC 0x31324B50
#define PKG2_SEC_BASE 0x80000000
#define PKG2_SEC_KERNEL 0
#define PKG2_SEC_INI1 1

#define INI1_MAGIC 0x31494E49

#define NOP_v8 0xD503201F
#define NOP_v7 0xE320F000
#define ADRP(r, o) 0x90000000 | ((((o) >> 12) & 0x3) << 29) | ((((o) >> 12) & 0x1FFFFC) << 3) | ((r) & 0x1F)

typedef struct _pkg2_hdr_t
{
    u8 ctr[0x10];
    u8 sec_ctr[0x40];
    u32 magic;
    u32 base;
    u32 pad0;
    u16 version;
    u16 pad1;
    u32 sec_size[4];
    u32 sec_off[4];
    u8 sec_sha256[0x80];
    u8 data[];
} pkg2_hdr_t;

typedef struct _pkg2_ini1_t
{
    u32 magic;
    u32 size;
    u32 num_procs;
    u32 pad;
} pkg2_ini1_t;

typedef struct _pkg2_kip1_sec_t
{
    u32 offset;
    u32 size_decomp;
    u32 size_comp;
    u32 attrib;
} pkg2_kip1_sec_t;

#define KIP1_NUM_SECTIONS 6

typedef struct _pkg2_kip1_t
{
    u32 magic;
    char name[12];
    u64 tid;
    u32 proc_cat;
    u8 main_thrd_prio;
    u8 def_cpu_core;
    u8 res;
    u8 flags;
    pkg2_kip1_sec_t sections[KIP1_NUM_SECTIONS];
    u32 caps[0x20];
    u8 data[];
} pkg2_kip1_t;

typedef struct _pkg2_kip1_info_t
{
    pkg2_kip1_t *kip1;
    u32 size;
    link_t link;
} pkg2_kip1_info_t;

typedef struct {
    u32 kb;
    u32 tsec_off;
    u32 pkg11_off;
    u32 sec_map[3];
    u32 secmon_base;
    u32 warmboot_base;
} pk11_offs;

typedef struct {
    u32 magic;
    u32 wb_size;
    u32 wb_off;
    u32 pad;
    u32 ldr_size;
    u32 ldr_off;
    u32 sm_size;
    u32 sm_off;
} pk11_header;

typedef struct kipdiff_s {
  u64 offset;              // offset from start of kip's .text segment
  u32 len;                 // length of below strings, NULL signifies end of patch
  const char *orig_bytes;  // original byte string (this must match exactly)
  const char *patch_bytes; // replacement byte string (same length)
} kipdiff_t;

// a single patch for a particular kip version
typedef struct kippatch_s {
  const char *name;        // name/id of the patch, NULL signifies end of patchset
  kipdiff_t *diffs;        // array of kipdiff_t's to apply
} kippatch_t;

// a group of patches that patch several different things in a particular kip version
typedef struct kippatchset_s {
  const char *kip_name;    // name/id of the kip, NULL signifies end of patchset list
  const char *kip_hash;    // sha256 of the right version of the kip
  kippatch_t *patches;     // set of patches for this version of the kip
} kippatchset_t;

//FS_MITM
static u32 PRC_ID_SND_100[] =
{
    0xA9BF2FEA, 0x2A0E03EB, 0xD37EF56B, 0xF86B6B8B, 0x92FFFFE9, 0x8A090168, 0xD2FFFFE9, 0x8A09016B,
    0xD2FFFFC9, 0xEB09017F, 0x54000040, 0xF9412948, 0xA8C12FEA
};

static u32 PRC_ID_RCV_100[] =
{
    0xA9BF2FEA, 0x2A1C03EA, 0xD37EF54A, 0xF86A69AA, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A,
    0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9412968, 0xA8C12FEA
};

static u32 PRC_ID_SND_200[] =
{
    0xA9BF2FEA, 0x2A1803EB, 0xD37EF56B, 0xF86B6B8B, 0x92FFFFE9, 0x8A090168, 0xD2FFFFE9, 0x8A09016B,
    0xD2FFFFC9, 0xEB09017F, 0x54000040, 0xF9413148, 0xA8C12FEA
};

static u32 PRC_ID_RCV_200[] =
{
    0xA9BF2FEA, 0x2A0F03EA, 0xD37EF54A, 0xF9405FEB, 0xF86A696A, 0xF9407BEB, 0x92FFFFE9, 0x8A090148,
    0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9413168, 0xA8C12FEA
};

static u32 PRC_ID_SND_300[] =
{
    0xA9BF2FEA, 0x2A1803EB, 0xD37EF56B, 0xF86B6B8B, 0x92FFFFE9, 0x8A090168, 0xD2FFFFE9, 0x8A09016B,
    0xD2FFFFC9, 0xEB09017F, 0x54000040, 0xF9415548, 0xA8C12FEA
};

static u32 PRC_ID_RCV_300[] =
{
    0xA9BF2FEA, 0x2A0F03EA, 0xD37EF54A, 0xF9405FEB, 0xF86A696A, 0xF9407BEB, 0x92FFFFE9, 0x8A090148,
    0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9415568, 0xA8C12FEA
};

static u32 PRC_ID_SND_302[] =
{
    0xA9BF2FEA, 0x2A1803EB, 0xD37EF56B, 0xF86B6B8B, 0x92FFFFE9, 0x8A090168, 0xD2FFFFE9, 0x8A09016B,
    0xD2FFFFC9, 0xEB09017F, 0x54000040, 0xF9415548, 0xA8C12FEA
};

static u32 PRC_ID_RCV_302[] =
{
    0xA9BF2FEA, 0x2A0F03EA, 0xD37EF54A, 0xF9405FEB, 0xF86A696A, 0xF9407BEB, 0x92FFFFE9, 0x8A090148,
    0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9415568, 0xA8C12FEA
};

static u32 PRC_ID_SND_400[] =
{
    0x2A1703EA, 0xD37EF54A, 0xF86A6B8A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9,
    0xEB09015F, 0x54000060, 0xF94053EA, 0xF9415948, 0xF94053EA
};

static u32 PRC_ID_RCV_400[] =
{
    0xF9403BED, 0x2A0E03EA, 0xD37EF54A, 0xF86A69AA, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A,
    0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9415B28, 0xD503201F
};

static u32 PRC_ID_SND_500[] =
{
    0x2A1703EA, 0xD37EF54A, 0xF86A6B6A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9,
    0xEB09015F, 0x54000060, 0xF94043EA, 0xF9415948, 0xF94043EA
};

static u32 PRC_ID_RCV_500[] =
{
    0xF9403BED, 0x2A1503EA, 0xD37EF54A, 0xF86A69AA, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A,
    0xD2FFFFC9, 0xEB09015F, 0x54000040, 0xF9415B08, 0xF9406FEA
};

static u32 PRC_ID_SND_600[] =
{
    0xA9BF2FEA, 0xF94037EB, 0x2A1503EA, 0xD37EF54A, 0xF86A696A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000100, 0xA9BF27E8, 0xF9400308, 0xF9401D08, 0xAA1803E0, 0xD63F0100, 0xA8C127E8, 0xAA0003E8, 0xA8C12FEA, 0xAA0803E0
};

static u32 PRC_ID_RCV_600[] =
{
    0xA9BF2FEA, 0xF94043EB, 0x2A1503EA, 0xD37EF54A, 0xF86A696A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000100, 0xA9BF27E8, 0xF9400308, 0xF9401D08, 0xAA1803E0, 0xD63F0100, 0xA8C127E8, 0xAA0003E8, 0xA8C12FEA, 0xAA0803E0
};

static u32 PRC_ID_SND_700[] =
{
    0xA9BF2FEA, 0xF9403BEB, 0x2A1903EA, 0xD37EF54A, 0xF86A696A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000100, 0xA9BF27E8, 0xF94002A8, 0xF9401D08, 0xAA1503E0, 0xD63F0100, 0xA8C127E8, 0xAA0003E8, 0xA8C12FEA, 0xAA0803E0
};

static u32 PRC_ID_RCV_700[] =
{
    0xA9BF2FEA, 0xF9404FEB, 0x2A1603EA, 0xD37EF54A, 0xF86A696A, 0x92FFFFE9, 0x8A090148, 0xD2FFFFE9, 0x8A09014A, 0xD2FFFFC9, 0xEB09015F, 0x54000100, 0xA9BF27E8, 0xF9400368, 0xF9401D08, 0xAA1B03E0, 0xD63F0100, 0xA8C127E8, 0xAA0003E8, 0xA8C12FEA, 0xAA0803E0
};

extern kippatchset_t kip_patches[];

typedef struct {
    u8 Hash[0x20];
    u32 SvcVerify;
    u32 SvcDebug;
    u32 SendOff;
    u32 RcvOff;
    u32 GenericOff;
    u8 CodeSndOff;
    u8 CodeRcvOff;
} KernelMeta;

static const KernelMeta kernelInfo[] = {
    {   //1.0.0
        {0xB8, 0xC5, 0x0C, 0x68, 0x25, 0xA9, 0xB9, 0x5B, 0xD2, 0x4D, 0x2C, 0x7C, 0x81, 0x7F, 0xE6, 0x96,
        0xF2, 0x42, 0x4E, 0x1D, 0x78, 0xDF, 0x3B, 0xCA, 0x3D, 0x6B, 0x68, 0x12, 0xDD, 0xA9, 0xCB, 0x9C},
        0x3764C,
        0x44074,
        0x23CC0,
        0x219F0,
        0,
        4,
        4
    },
    {   //2.0.0
        {0x64, 0x0B, 0x51, 0xFF, 0x28, 0x01, 0xB8, 0x30, 0xA7, 0xA3, 0x60, 0x47, 0x86, 0x0D, 0x68, 0xAA,
        0x9A, 0x92, 0x10, 0x0D, 0xB9, 0xCC, 0xEC, 0x8B, 0x05, 0x80, 0x73, 0xBD, 0x33, 0xB4, 0x2C, 0x6C},
        0x54834,
        0x6086C,
        0x3F134,
        0x3D1A8,
        0,
        4,
        4
    },
    {   //3.0.0
        {0x50, 0x84, 0x23, 0xAC, 0x6F, 0xA1, 0x5D, 0x3B, 0x56, 0xC2, 0xFC, 0x95, 0x22, 0xCC, 0xD5, 0xA8,
        0x15, 0xD3, 0xB4, 0x6B, 0xA1, 0x2C, 0xF2, 0x93, 0xD3, 0x02, 0x05, 0xAB, 0x52, 0xEF, 0x73, 0xC5},
        0x3BD24,
        0x483FC,
        0x26080,
        0x240F0,
        0,
        4,
        4
    },
    {   //3.0.2
        {0x81, 0x9D, 0x08, 0xBE, 0xE4, 0x5E, 0x1F, 0xBB, 0x45, 0x5A, 0x6D, 0x70, 0x4B, 0xB2, 0x17, 0xA6,
        0x12, 0x69, 0xF8, 0xB8, 0x75, 0x1C, 0x71, 0x16, 0xF0, 0xE9, 0x79, 0x7F, 0xB0, 0xD1, 0x78, 0xB2},
        0x3BD24,
        0x48414,
        0x26080,
        0x240F0,
        0,
        4,
        4
    },
    {   //4.0.0
        {0xE6, 0xC0, 0xB7, 0xE3, 0x2F, 0xF9, 0x44, 0x51, 0xEC, 0xD5, 0x95, 0x79, 0xE3, 0x46, 0xB1, 0xDA,
        0x2E, 0xD9, 0x28, 0xC6, 0xF2, 0x31, 0x4F, 0x95, 0xD8, 0xC7, 0xD5, 0xBD, 0x15, 0xD5, 0xE2, 0x5A},
        0x41EB4,
        0x4EBFC,
        0x2AF64,
        0x28F6C,
        0,
        8,
        4
    },
    {   //5.0.0
        {0xB2, 0x38, 0x61, 0xA8, 0xE1, 0xE2, 0xE4, 0xE4, 0x17, 0x28, 0xED, 0xA9, 0xF6, 0xF6, 0xBD, 0xD2,
        0x59, 0xDB, 0x1F, 0xEF, 0x4A, 0x8B, 0x2F, 0x1C, 0x64, 0x46, 0x06, 0x40, 0xF5, 0x05, 0x9C, 0x43},
        0x45E6C,
        0x5513C,
        0x2AD34,
        0x28DAC,
        0x38C2C,
        8,
        8
    },
    {   //6.0.0
        {0x85, 0x97, 0x40, 0xF6, 0xC0, 0x3E, 0x3D, 0x44, 0xDE, 0xA4, 0xA0, 0x35, 0xFD, 0x12, 0x9C, 0xD4,
        0x4F, 0x9C, 0x36, 0x53, 0x74, 0x54, 0x2C, 0x9C, 0x55, 0x47, 0xC4, 0x25, 0xF1, 0x42, 0xFB, 0x97},
        0x47EA0,
        0x57548,
        0x2BB8C,
        0x29B6C,
        0x3A8CC,
        0x10,
        0x10
    },
    {   //7.0.0
        {0xA2, 0x5E, 0x47, 0x0C, 0x8E, 0x6D, 0x2F, 0xD7, 0x5D, 0xAD, 0x24, 0xD7, 0xD8, 0x24, 0x34, 0xFB,
        0xCD, 0x77, 0xBB, 0xE6, 0x66, 0x03, 0xCB, 0xAF, 0xAB, 0x85, 0x45, 0xA0, 0x91, 0xAF, 0x34, 0x25},
        0x49E5C,
        0x581B0,
        0x2D044,
        0x2B23C,
        0x3C6E0,
        0x10,
        0x10
    },
};

u8 *ReadBoot0(sdmmc_storage_t *storage);
u8 *ReadPackage1Ldr(sdmmc_storage_t *storage);
u8 *ReadPackage2(sdmmc_storage_t *storage);
int kippatch_apply(u8 *kipdata, u64 kipdata_len, kippatch_t *patch);
int kippatch_apply_set(u8 *kipdata, u64 kipdata_len, kippatchset_t *patchset);
kippatchset_t *kippatch_find_set(u8 *kiphash, kippatchset_t *patchsets);
pkg2_hdr_t *unpackFirmwarePackage(u8 *data);
void pkg1_unpack(pk11_offs *offs, u32 pkg1Off);
void buildFirmwarePackage(u8 *kernel, u32 kernel_size, link_t *kips_info);
size_t calcKipSize(pkg2_kip1_t *kip1);
void pkg2_parse_kips(link_t *info, pkg2_hdr_t *pkg2);
bool hasCustomKern();
bool hasCustomSecmon();
bool hasCustomWb();
u8 *LoadExtFile(char *path, size_t *size);
void loadKip(link_t *info, char *path);
u32 *getSndPayload(u32 id, size_t *size);
u32 *getRcvPayload(u32 id, size_t *size);
