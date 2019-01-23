// Copyright 2016 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#pragma once

#include <stdint.h>
#include <assert.h>
#include <zircon/compiler.h>

__BEGIN_CDECLS

// clang-format off

// KTRACE TAG 0xGGGEEEXZ
//
// 12 group flags
// 12 event id bits
//  4 flag bits
//  4 bit size (in uint64_t units)

#define KTRACE_TAG_EX(evt,grp,siz,flgs) \
        ( (((grp)&0xFFF)<<20) | (((evt)&0xFFF)<<8) | (((flgs)&0xF)<<4) | (((siz)>>3)&0x0F) )

#define KTRACE_TAG(evt,grp,siz)   KTRACE_TAG_EX(evt, grp, siz, 0)

#define KTRACE_TAG_16B(e,g)       KTRACE_TAG(e,g,16)
#define KTRACE_TAG_32B(e,g)       KTRACE_TAG(e,g,32)
#define KTRACE_TAG_NAME(e,g)      KTRACE_TAG(e,g,48)

#define KTRACE_TAG_FLAGS(tag, flags) ((tag) | (((flags)&0xF)<<4))

#define KTRACE_LEN(tag)           (((tag)&0xF)<<3)
#define KTRACE_GROUP(tag)         (((tag)>>20)&0xFFF)
#define KTRACE_EVENT(tag)         (((tag)>>8)&0xFFF)
#define KTRACE_FLAGS(tag)         (((tag)>>4)&0xF)

#define KTRACE_NAMED_EVENT_BIT    (0x800)

#define KTRACE_NAMED_EVENT(id)    ((id) | KTRACE_NAMED_EVENT_BIT)
#define KTRACE_EVENT_NAME_ID(tag) (KTRACE_EVENT(tag) & 0x7ff)

#define KTRACE_HDRSIZE            (16)
#define KTRACE_RECSIZE            (32)
#define KTRACE_NAMESIZE           (12)
#define KTRACE_NAMEOFF            (8)

#define KTRACE_VERSION            (0x00020000)

// Filter Groups
#define KTRACE_GRP_ALL            0xFFF
#define KTRACE_GRP_META           0x001
#define KTRACE_GRP_LIFECYCLE      0x002
#define KTRACE_GRP_SCHEDULER      0x004
#define KTRACE_GRP_TASKS          0x008
#define KTRACE_GRP_IPC            0x010
#define KTRACE_GRP_IRQ            0x020
#define KTRACE_GRP_PROBE          0x040
#define KTRACE_GRP_ARCH           0x080

#define KTRACE_GRP_TO_MASK(grp)   ((grp) << 20)

#define KTRACE_FLAGS_CPU          (0x1)
#define KTRACE_FLAGS_BEGIN        (0x2)
#define KTRACE_FLAGS_END          (0x4)

typedef struct ktrace_header {
    uint32_t tag;
    uint32_t tid;
    uint64_t ts;
} ktrace_header_t;

static_assert(sizeof(ktrace_header_t) == KTRACE_HDRSIZE,
              "ktrace_header_t is not KTRACE_HDRSIZE bytes");

typedef struct ktrace_rec_32b {
    uint32_t tag;
    uint32_t tid;
    uint64_t ts;
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
} ktrace_rec_32b_t;

typedef struct ktrace_rec_name {
    uint32_t tag;
    uint32_t id;
    uint32_t arg;
    char name[1];
} ktrace_rec_name_t;

#define KTRACE_DEF(num,type,name,group) TAG_##name = KTRACE_TAG_##type(num,KTRACE_GRP_##group),
enum {
#include <lib/zircon-internal/ktrace-def.h>
};

#define TAG_PROBE_16(id) KTRACE_TAG(KTRACE_NAMED_EVENT(id),KTRACE_GRP_PROBE,16)
#define TAG_PROBE_24(id) KTRACE_TAG(KTRACE_NAMED_EVENT(id),KTRACE_GRP_PROBE,24)
#define TAG_PROBE_32(id) KTRACE_TAG(KTRACE_NAMED_EVENT(id),KTRACE_GRP_PROBE,32)

#define TAG_BEGIN_DURATION_16(id) KTRACE_TAG_EX(KTRACE_NAMED_EVENT(id), \
                                                KTRACE_GRP_SCHEDULER,16,KTRACE_FLAGS_BEGIN)
#define TAG_END_DURATION_16(id)   KTRACE_TAG_EX(KTRACE_NAMED_EVENT(id), \
                                                KTRACE_GRP_SCHEDULER,16,KTRACE_FLAGS_END)
#define TAG_BEGIN_DURATION_32(id) KTRACE_TAG_EX(KTRACE_NAMED_EVENT(id), \
                                                KTRACE_GRP_SCHEDULER,32,KTRACE_FLAGS_BEGIN)
#define TAG_END_DURATION_32(id)   KTRACE_TAG_EX(KTRACE_NAMED_EVENT(id), \
                                                KTRACE_GRP_SCHEDULER,32,KTRACE_FLAGS_END)

// Actions for ktrace control
#define KTRACE_ACTION_START     1 // options = grpmask, 0 = all
#define KTRACE_ACTION_STOP      2 // options ignored
#define KTRACE_ACTION_REWIND    3 // options ignored
#define KTRACE_ACTION_NEW_PROBE 4 // options ignored, ptr = name

__END_CDECLS
