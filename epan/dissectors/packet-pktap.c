/*
 * packet-pktap.c
 * Routines for dissecting Apple's PKTAP header
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 2007 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "config.h"

#include <epan/packet.h>
#include <epan/capture_dissectors.h>
#include <epan/expert.h>
#include <wsutil/pint.h>

#include "packet-eth.h"

static dissector_handle_t pcap_pktdata_handle;

void proto_register_pktap(void);
void proto_reg_handoff_pktap(void);

/*
 * Apple's PKTAP header.
 */

/*
 * Minimum header length.
 *
 * XXX - I'm assuming the header begins with a length field so that it
 * can be transparently *extended*, not so that fields in the current
 * header can be *omitted*.
 */
#define MIN_PKTAP_HDR_LEN	108

/*
 * Record types.
 */
#define PKT_REC_NONE	0	/* nothing follows the header */
#define PKT_REC_PACKET	1	/* a packet follows the header */

/* Protocol */
static int proto_pktap = -1;

static int hf_pktap_hdrlen = -1;
static int hf_pktap_rectype = -1;
static int hf_pktap_dlt = -1;
static int hf_pktap_ifname = -1;
static int hf_pktap_flags = -1;
static int hf_pktap_pfamily = -1;
static int hf_pktap_llhdrlen = -1;
static int hf_pktap_lltrlrlen = -1;
static int hf_pktap_pid = -1;
static int hf_pktap_cmdname = -1;
static int hf_pktap_svc_class = -1;
static int hf_pktap_iftype = -1;
static int hf_pktap_ifunit = -1;
static int hf_pktap_epid = -1;
static int hf_pktap_ecmdname = -1;

static gint ett_pktap = -1;

static expert_field ei_pktap_hdrlen_too_short = EI_INIT;

static dissector_handle_t pktap_handle;
static capture_dissector_handle_t eth_cap_handle;

/*
 * XXX - these are only little-endian because they've been created on
 * little-endian machines; the code in bsd/net/pktap.c in XNU writes
 * the structure out in host byte order.
 *
 * We haven't been treating it as host-endian in libpcap and libwiretap,
 * i.e. we haven't been byte-swapping its members when reading it on
 * a machine whose byte order differs from the byte order of the machine
 * on which the file is being read.
 *
 * Furthermore, the header is extensible, so we don't necessarily know
 * what fields to swap.
 *
 * Fortunately, the length of the PKTAP header is a 32-bit field and is
 * *presumably* never going to be 65536 or greater, so if any of the upper
 * 16 bits appear to be set, it means we're looking at it in the wrong
 * byte order, and it's never going to be zero, so those bits *will* be
 * set if it's >= 65536, so we can determine its byte order.
 *
 * We should do that here.
 */

static gboolean
capture_pktap(const guchar *pd, int offset _U_, int len, capture_packet_info_t *cpinfo, const union wtap_pseudo_header *pseudo_header _U_)
{
	guint32  hdrlen, rectype, dlt;

	hdrlen = pletoh32(pd);
	if (hdrlen < MIN_PKTAP_HDR_LEN || !BYTES_ARE_IN_FRAME(0, len, hdrlen))
		return FALSE;

	rectype = pletoh32(pd+4);
	if (rectype != PKT_REC_PACKET)
		return FALSE;

	dlt = pletoh32(pd+4);

	/* XXX - We should probably combine this with capture_info.c:capture_info_packet() */
	switch (dlt) {

	case 1: /* DLT_EN10MB */
		return call_capture_dissector(eth_cap_handle, pd, hdrlen, len, cpinfo, pseudo_header);

	}

	return FALSE;
}

static int
dissect_pktap(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
	proto_tree *pktap_tree = NULL;
	proto_item *ti = NULL;
	tvbuff_t *next_tvb;
	int offset = 0;
	guint32 pkt_len, rectype, dlt;

	col_set_str(pinfo->cinfo, COL_PROTOCOL, "PKTAP");
	col_clear(pinfo->cinfo, COL_INFO);

	pkt_len = tvb_get_letohl(tvb, offset);
	col_add_fstr(pinfo->cinfo, COL_INFO, "PKTAP, %u byte header", pkt_len);

	/* Dissect the packet */
	ti = proto_tree_add_item(tree, proto_pktap, tvb, offset, pkt_len, ENC_NA);
	pktap_tree = proto_item_add_subtree(ti, ett_pktap);

	proto_tree_add_item(pktap_tree, hf_pktap_hdrlen, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	if (pkt_len < MIN_PKTAP_HDR_LEN) {
		proto_tree_add_expert(tree, pinfo, &ei_pktap_hdrlen_too_short,
		    tvb, offset, 4);
		return tvb_captured_length(tvb);
	}
	offset += 4;

	proto_tree_add_item(pktap_tree, hf_pktap_rectype, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	rectype = tvb_get_letohl(tvb, offset);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_dlt, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	dlt = tvb_get_letohl(tvb, offset);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_ifname, tvb, offset, 24,
	    ENC_ASCII|ENC_NA);
	offset += 24;
	proto_tree_add_item(pktap_tree, hf_pktap_flags, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_pfamily, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_llhdrlen, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_lltrlrlen, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_pid, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_cmdname, tvb, offset, 20,
	    ENC_UTF_8);
	offset += 20;
	proto_tree_add_item(pktap_tree, hf_pktap_svc_class, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_iftype, tvb, offset, 2,
	    ENC_LITTLE_ENDIAN);
	offset += 2;
	proto_tree_add_item(pktap_tree, hf_pktap_ifunit, tvb, offset, 2,
	    ENC_LITTLE_ENDIAN);
	offset += 2;
	proto_tree_add_item(pktap_tree, hf_pktap_epid, tvb, offset, 4,
	    ENC_LITTLE_ENDIAN);
	offset += 4;
	proto_tree_add_item(pktap_tree, hf_pktap_ecmdname, tvb, offset, 20,
	    ENC_UTF_8);
	/*offset += 20;*/

	if (rectype == PKT_REC_PACKET) {
		next_tvb = tvb_new_subset_remaining(tvb, pkt_len);
		call_dissector_with_data(pcap_pktdata_handle, next_tvb,
		    pinfo, tree, &dlt);
	}
	return tvb_captured_length(tvb);
}

void
proto_register_pktap(void)
{
	static hf_register_info hf[] = {
	  { &hf_pktap_hdrlen,
	    { "Header length", "pktap.hdrlen",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_rectype,
	    { "Record type", "pktap.rectype",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_dlt,
	    { "DLT", "pktap.dlt",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_ifname,	/* fixed length *and* null-terminated */
	    { "Interface name", "pktap.ifname",
	      FT_STRINGZ, BASE_NONE, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_flags,
	    { "Flags", "pktap.flags",
	      FT_UINT32, BASE_HEX, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_pfamily,
	    { "Protocol family", "pktap.pfamily",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_llhdrlen,
	    { "Link-layer header length", "pktap.llhdrlen",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_lltrlrlen,
	    { "Link-layer trailer length", "pktap.lltrlrlen",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_pid,
	    { "Process ID", "pktap.pid",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_cmdname,	/* fixed length *and* null-terminated */
	    { "Command name", "pktap.cmdname",
	      FT_STRINGZ, BASE_NONE, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_svc_class,
	    { "Service class", "pktap.svc_class",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_iftype,
	    { "Interface type", "pktap.iftype",
	      FT_UINT16, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_ifunit,
	    { "Interface unit", "pktap.ifunit",
	      FT_UINT16, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_epid,
	    { "Effective process ID", "pktap.epid",
	      FT_UINT32, BASE_DEC, NULL, 0x0, NULL, HFILL } },
	  { &hf_pktap_ecmdname,	/* fixed length *and* null-terminated */
	    { "Effective command name", "pktap.ecmdname",
	      FT_STRINGZ, BASE_NONE, NULL, 0x0, NULL, HFILL } },
	};

	static gint *ett[] = {
		&ett_pktap,
	};

	static ei_register_info ei[] = {
	    { &ei_pktap_hdrlen_too_short,
	      { "pktap.hdrlen_too_short", PI_MALFORMED, PI_ERROR,
	        "Header length is too short", EXPFILL }},
	};

	expert_module_t* expert_pktap;

	proto_pktap = proto_register_protocol("PKTAP packet header", "PKTAP",
	    "pktap");
	proto_register_field_array(proto_pktap, hf, array_length(hf));
	proto_register_subtree_array(ett, array_length(ett));
	expert_pktap = expert_register_protocol(proto_pktap);
	expert_register_field_array(expert_pktap, ei, array_length(ei));

	pktap_handle = register_dissector("pktap", dissect_pktap, proto_pktap);
}

void
proto_reg_handoff_pktap(void)
{
	capture_dissector_handle_t pktap_cap_handle;

	dissector_add_uint("wtap_encap", WTAP_ENCAP_PKTAP, pktap_handle);

	pcap_pktdata_handle = find_dissector_add_dependency("pcap_pktdata", proto_pktap);

	/* XXX - WTAP_ENCAP_USER2 to handle Mavericks' botch wherein it
		uses DLT_USER2 for PKTAP; if you are using DLT_USER2 for your
		own purposes, feel free to call your own capture_ routine for
		WTAP_ENCAP_USER2. */
	pktap_cap_handle = create_capture_dissector_handle(capture_pktap, proto_pktap);
	capture_dissector_add_uint("wtap_encap", WTAP_ENCAP_PKTAP, pktap_cap_handle);
	capture_dissector_add_uint("wtap_encap", WTAP_ENCAP_USER2, pktap_cap_handle);

	eth_cap_handle = find_capture_dissector("eth");
}

/*
 * Editor modelines  -  https://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 8
 * tab-width: 8
 * indent-tabs-mode: t
 * End:
 *
 * vi: set shiftwidth=8 tabstop=8 noexpandtab:
 * :indentSize=8:tabSize=8:noTabs=false:
 */
