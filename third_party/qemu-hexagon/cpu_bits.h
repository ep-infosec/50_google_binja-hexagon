/*
 *  Copyright(c) 2019-2020 Qualcomm Innovation Center, Inc. All Rights Reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>

#include "third_party/qemu-hexagon/bitops.h"

#ifdef __cplusplus
extern "C" {
#endif

#define HEX_EXCP_FETCH_NO_UPAGE 0x012
#define HEX_EXCP_INVALID_PACKET 0x015
#define HEX_EXCP_INVALID_OPCODE 0x015
#define HEX_EXCP_PRIV_NO_UREAD 0x024
#define HEX_EXCP_PRIV_NO_UWRITE 0x025

#define HEX_EXCP_TRAP0 0x172
#define HEX_EXCP_TRAP1 0x173

#define PACKET_WORDS_MAX 4

static inline uint32_t parse_bits(uint32_t encoding) {
  /* The parse bits are [15:14] */
  return extract32(encoding, 14, 2);
}

static inline uint32_t iclass_bits(uint32_t encoding) {
  /* The instruction class is encoded in bits [31:28] */
  uint32_t iclass = extract32(encoding, 28, 4);
  /* If parse bits are zero, this is a duplex */
  if (parse_bits(encoding) == 0) {
    iclass += 16;
  }
  return iclass;
}

static inline int is_packet_end(uint32_t endocing) {
  uint32_t bits = parse_bits(endocing);
  return ((bits == 0x3) || (bits == 0x0));
}

#ifdef __cplusplus
}
#endif
