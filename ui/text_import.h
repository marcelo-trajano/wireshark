/** @file
 *
 * text_import.h
 * State machine for text import
 * November 2010, Jaap Keuter <jaap.keuter@xs4all.nl>
 * Modified February 2021, Paul Weiß
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * Based on text2pcap.h by Ashok Narayanan <ashokn@cisco.com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later*
 *******************************************************************************/


#ifndef __TEXT_IMPORT_H__
#define __TEXT_IMPORT_H__

#include <stdio.h>
#include <wireshark.h>

#include <wiretap/wtap.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* The parameter interface */

enum offset_type
{
    OFFSET_NONE = 0,
    OFFSET_HEX,
    OFFSET_OCT,
    OFFSET_DEC
};

enum data_encoding {
  ENCODING_PLAIN_HEX,
  ENCODING_PLAIN_OCT,
  ENCODING_PLAIN_BIN,
  ENCODING_BASE64
};

enum dummy_header_type
{
    HEADER_NONE,
    HEADER_ETH,
    HEADER_IPV4,
    HEADER_UDP,
    HEADER_TCP,
    HEADER_SCTP,
    HEADER_SCTP_DATA,
    HEADER_EXPORT_PDU
};

enum text_import_mode {
    TEXT_IMPORT_HEXDUMP,
    TEXT_IMPORT_REGEX
};

typedef struct
{
    int debug;

    /* Input info */
    // TODO: add const, as this way string constants can't be used
    // BUT: the other way clang-check complaines when you free them
    /* const */ char *import_text_filename;
    char *output_filename;
    enum text_import_mode mode;

    struct {
        FILE *import_text_FILE;
        enum offset_type offset_type;
        gboolean has_direction;
        gboolean identify_ascii;
    } hexdump;
    struct {
        GMappedFile* import_text_GMappedFile;
        /* const */ GRegex* format;
        enum data_encoding encoding;
        /* const */ gchar* in_indication;
        /* const */ gchar* out_indication;
    } regex;
    const char* timestamp_format;

    /* Import info */
    /* Wiretap encapsulation type; see wiretap/wtap.h for details */
    guint encapsulation;
    wtap_dumper* wdh;

    /* Dummy header info (if encapsulation == 1) */
    enum dummy_header_type dummy_header_type;
    guint pid;
    gboolean ipv6;
    union {
        ws_in4_addr ipv4;
        ws_in6_addr ipv6;
    } ip_src_addr;
    union {
        ws_in4_addr ipv4;
        ws_in6_addr ipv6;
    } ip_dest_addr;
    guint protocol;
    guint src_port;
    guint dst_port;
    guint tag;
    guint ppi;
    /* const */ gchar* payload;

    guint max_frame_length;

    /* Output info */
    guint num_packets_read;
    guint num_packets_written;
} text_import_info_t;

int text_import(text_import_info_t * const info);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TEXT_IMPORT_H__ */
