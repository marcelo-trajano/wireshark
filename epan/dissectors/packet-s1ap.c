/* Do not modify this file. Changes will be overwritten.                      */
/* Generated automatically by the ASN.1 to Wireshark dissector compiler       */
/* packet-s1ap.c                                                              */
/* asn2wrs.py -p s1ap -c ./s1ap.cnf -s ./packet-s1ap-template -D . -O ../.. S1AP-CommonDataTypes.asn S1AP-Constants.asn S1AP-Containers.asn S1AP-IEs.asn S1AP-PDU-Contents.asn S1AP-PDU-Descriptions.asn S1AP-SonTransfer-IEs.asn */

/* Input file: packet-s1ap-template.c */

#line 1 "./asn1/s1ap/packet-s1ap-template.c"
/* packet-s1ap.c
 * Routines for E-UTRAN S1 Application Protocol (S1AP) packet dissection
 * Copyright 2007-2016, Anders Broman <anders.broman@ericsson.com>
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Based on the RANAP dissector
 *
 * References: 3GPP TS 36.413 V16.7.0 (2021-10)
 */

#include "config.h"

#include <epan/packet.h>

#include <epan/strutil.h>
#include <epan/asn1.h>
#include <epan/prefs.h>
#include <epan/sctpppids.h>
#include <epan/expert.h>
#include <epan/conversation.h>
#include <epan/proto_data.h>
#include <epan/exceptions.h>
#include <epan/show_exception.h>

#include "packet-ber.h"
#include "packet-per.h"
#include "packet-e212.h"
#include "packet-sccp.h"
#include "packet-lte-rrc.h"
#include "packet-ranap.h"
#include "packet-bssgp.h"
#include "packet-s1ap.h"
#include "packet-a21.h"
#include "packet-gsm_map.h"
#include "packet-cell_broadcast.h"
#include "packet-gsm_a_common.h"
#include "packet-ntp.h"
#include "packet-ngap.h"

#define PNAME  "S1 Application Protocol"
#define PSNAME "S1AP"
#define PFNAME "s1ap"

/* Dissector will use SCTP PPID 18 or SCTP port. IANA assigned port = 36412 */
#define SCTP_PORT_S1AP 36412

void proto_register_s1ap(void);
void proto_reg_handoff_s1ap(void);

static dissector_handle_t gcsna_handle;
static dissector_handle_t nas_eps_handle;
static dissector_handle_t lppa_handle;
static dissector_handle_t bssgp_handle;
static dissector_handle_t lte_rrc_ue_radio_access_cap_info_handle;
static dissector_handle_t lte_rrc_ue_radio_access_cap_info_nb_handle;
static dissector_handle_t nr_rrc_ue_radio_access_cap_info_handle;
static dissector_handle_t lte_rrc_ue_radio_paging_info_handle;
static dissector_handle_t lte_rrc_ue_radio_paging_info_nb_handle;


/*--- Included file: packet-s1ap-val.h ---*/
#line 1 "./asn1/s1ap/packet-s1ap-val.h"
#define maxPrivateIEs                  65535
#define maxProtocolExtensions          65535
#define maxProtocolIEs                 65535
#define maxnoofCSGs                    256
#define maxnoofE_RABs                  256
#define maxnoofTAIs                    256
#define maxnoofTACs                    256
#define maxnoofErrors                  256
#define maxnoofBPLMNs                  6
#define maxnoofPLMNsPerMME             32
#define maxnoofEPLMNs                  15
#define maxnoofEPLMNsPlusOne           16
#define maxnoofForbLACs                4096
#define maxnoofForbTACs                4096
#define maxnoofIndividualS1ConnectionsToReset 256
#define maxnoofCellsinUEHistoryInfo    16
#define maxnoofCellsineNB              256
#define maxnoofTAIforWarning           65535
#define maxnoofCellID                  65535
#define maxnoofDCNs                    32
#define maxnoofEmergencyAreaID         65535
#define maxnoofCellinTAI               65535
#define maxnoofCellinEAI               65535
#define maxnoofeNBX2TLAs               2
#define maxnoofeNBX2ExtTLAs            16
#define maxnoofeNBX2GTPTLAs            16
#define maxnoofRATs                    8
#define maxnoofGroupIDs                65535
#define maxnoofMMECs                   256
#define maxnoofCellIDforMDT            32
#define maxnoofTAforMDT                8
#define maxnoofMDTPLMNs                16
#define maxnoofCellsforRestart         256
#define maxnoofRestartTAIs             2048
#define maxnoofRestartEmergencyAreaIDs 256
#define maxEARFCN                      262143
#define maxnoofMBSFNAreaMDT            8
#define maxnoofRecommendedCells        16
#define maxnoofRecommendedENBs         16
#define maxnooftimeperiods             2
#define maxnoofCellIDforQMC            32
#define maxnoofTAforQMC                8
#define maxnoofPLMNforQMC              16
#define maxnoofBluetoothName           4
#define maxnoofWLANName                4
#define maxnoofConnectedengNBs         256
#define maxnoofPC5QoSFlows             2048
#define maxnooffrequencies             64
#define maxNARFCN                      32
#define maxRS_IndexCellQual            16
#define maxnoofIRATReportingCells      128
#define maxnoofcandidateCells          16
#define maxnoofCellineNB               256

typedef enum _ProcedureCode_enum {
  id_HandoverPreparation =   0,
  id_HandoverResourceAllocation =   1,
  id_HandoverNotification =   2,
  id_PathSwitchRequest =   3,
  id_HandoverCancel =   4,
  id_E_RABSetup =   5,
  id_E_RABModify =   6,
  id_E_RABRelease =   7,
  id_E_RABReleaseIndication =   8,
  id_InitialContextSetup =   9,
  id_Paging    =  10,
  id_downlinkNASTransport =  11,
  id_initialUEMessage =  12,
  id_uplinkNASTransport =  13,
  id_Reset     =  14,
  id_ErrorIndication =  15,
  id_NASNonDeliveryIndication =  16,
  id_S1Setup   =  17,
  id_UEContextReleaseRequest =  18,
  id_DownlinkS1cdma2000tunnelling =  19,
  id_UplinkS1cdma2000tunnelling =  20,
  id_UEContextModification =  21,
  id_UECapabilityInfoIndication =  22,
  id_UEContextRelease =  23,
  id_eNBStatusTransfer =  24,
  id_MMEStatusTransfer =  25,
  id_DeactivateTrace =  26,
  id_TraceStart =  27,
  id_TraceFailureIndication =  28,
  id_ENBConfigurationUpdate =  29,
  id_MMEConfigurationUpdate =  30,
  id_LocationReportingControl =  31,
  id_LocationReportingFailureIndication =  32,
  id_LocationReport =  33,
  id_OverloadStart =  34,
  id_OverloadStop =  35,
  id_WriteReplaceWarning =  36,
  id_eNBDirectInformationTransfer =  37,
  id_MMEDirectInformationTransfer =  38,
  id_PrivateMessage =  39,
  id_eNBConfigurationTransfer =  40,
  id_MMEConfigurationTransfer =  41,
  id_CellTrafficTrace =  42,
  id_Kill      =  43,
  id_downlinkUEAssociatedLPPaTransport =  44,
  id_uplinkUEAssociatedLPPaTransport =  45,
  id_downlinkNonUEAssociatedLPPaTransport =  46,
  id_uplinkNonUEAssociatedLPPaTransport =  47,
  id_UERadioCapabilityMatch =  48,
  id_PWSRestartIndication =  49,
  id_E_RABModificationIndication =  50,
  id_PWSFailureIndication =  51,
  id_RerouteNASRequest =  52,
  id_UEContextModificationIndication =  53,
  id_ConnectionEstablishmentIndication =  54,
  id_UEContextSuspend =  55,
  id_UEContextResume =  56,
  id_NASDeliveryIndication =  57,
  id_RetrieveUEInformation =  58,
  id_UEInformationTransfer =  59,
  id_eNBCPRelocationIndication =  60,
  id_MMECPRelocationIndication =  61,
  id_SecondaryRATDataUsageReport =  62,
  id_UERadioCapabilityIDMapping =  63,
  id_HandoverSuccess =  64,
  id_eNBEarlyStatusTransfer =  65,
  id_MMEEarlyStatusTransfer =  66
} ProcedureCode_enum;

typedef enum _ProtocolIE_ID_enum {
  id_MME_UE_S1AP_ID =   0,
  id_HandoverType =   1,
  id_Cause     =   2,
  id_SourceID  =   3,
  id_TargetID  =   4,
  id_Unknown_5 =   5,
  id_Unknown_6 =   6,
  id_Unknown_7 =   7,
  id_eNB_UE_S1AP_ID =   8,
  id_Unknown_9 =   9,
  id_Unknown_10 =  10,
  id_Unknown_11 =  11,
  id_E_RABSubjecttoDataForwardingList =  12,
  id_E_RABtoReleaseListHOCmd =  13,
  id_E_RABDataForwardingItem =  14,
  id_E_RABReleaseItemBearerRelComp =  15,
  id_E_RABToBeSetupListBearerSUReq =  16,
  id_E_RABToBeSetupItemBearerSUReq =  17,
  id_E_RABAdmittedList =  18,
  id_E_RABFailedToSetupListHOReqAck =  19,
  id_E_RABAdmittedItem =  20,
  id_E_RABFailedtoSetupItemHOReqAck =  21,
  id_E_RABToBeSwitchedDLList =  22,
  id_E_RABToBeSwitchedDLItem =  23,
  id_E_RABToBeSetupListCtxtSUReq =  24,
  id_TraceActivation =  25,
  id_NAS_PDU   =  26,
  id_E_RABToBeSetupItemHOReq =  27,
  id_E_RABSetupListBearerSURes =  28,
  id_E_RABFailedToSetupListBearerSURes =  29,
  id_E_RABToBeModifiedListBearerModReq =  30,
  id_E_RABModifyListBearerModRes =  31,
  id_E_RABFailedToModifyList =  32,
  id_E_RABToBeReleasedList =  33,
  id_E_RABFailedToReleaseList =  34,
  id_E_RABItem =  35,
  id_E_RABToBeModifiedItemBearerModReq =  36,
  id_E_RABModifyItemBearerModRes =  37,
  id_E_RABReleaseItem =  38,
  id_E_RABSetupItemBearerSURes =  39,
  id_SecurityContext =  40,
  id_HandoverRestrictionList =  41,
  id_Unknown_42 =  42,
  id_UEPagingID =  43,
  id_pagingDRX =  44,
  id_Unknown_45 =  45,
  id_TAIList   =  46,
  id_TAIItem   =  47,
  id_E_RABFailedToSetupListCtxtSURes =  48,
  id_E_RABReleaseItemHOCmd =  49,
  id_E_RABSetupItemCtxtSURes =  50,
  id_E_RABSetupListCtxtSURes =  51,
  id_E_RABToBeSetupItemCtxtSUReq =  52,
  id_E_RABToBeSetupListHOReq =  53,
  id_Unknown_54 =  54,
  id_GERANtoLTEHOInformationRes =  55,
  id_Unknown_56 =  56,
  id_UTRANtoLTEHOInformationRes =  57,
  id_CriticalityDiagnostics =  58,
  id_Global_ENB_ID =  59,
  id_eNBname   =  60,
  id_MMEname   =  61,
  id_Unknown_62 =  62,
  id_ServedPLMNs =  63,
  id_SupportedTAs =  64,
  id_TimeToWait =  65,
  id_uEaggregateMaximumBitrate =  66,
  id_TAI       =  67,
  id_Unknown_68 =  68,
  id_E_RABReleaseListBearerRelComp =  69,
  id_cdma2000PDU =  70,
  id_cdma2000RATType =  71,
  id_cdma2000SectorID =  72,
  id_SecurityKey =  73,
  id_UERadioCapability =  74,
  id_GUMMEI_ID =  75,
  id_Unknown_76 =  76,
  id_Unknown_77 =  77,
  id_E_RABInformationListItem =  78,
  id_Direct_Forwarding_Path_Availability =  79,
  id_UEIdentityIndexValue =  80,
  id_Unknown_81 =  81,
  id_Unknown_82 =  82,
  id_cdma2000HOStatus =  83,
  id_cdma2000HORequiredIndication =  84,
  id_Unknown_85 =  85,
  id_E_UTRAN_Trace_ID =  86,
  id_RelativeMMECapacity =  87,
  id_SourceMME_UE_S1AP_ID =  88,
  id_Bearers_SubjectToStatusTransfer_Item =  89,
  id_eNB_StatusTransfer_TransparentContainer =  90,
  id_UE_associatedLogicalS1_ConnectionItem =  91,
  id_ResetType =  92,
  id_UE_associatedLogicalS1_ConnectionListResAck =  93,
  id_E_RABToBeSwitchedULItem =  94,
  id_E_RABToBeSwitchedULList =  95,
  id_S_TMSI    =  96,
  id_cdma2000OneXRAND =  97,
  id_RequestType =  98,
  id_UE_S1AP_IDs =  99,
  id_EUTRAN_CGI = 100,
  id_OverloadResponse = 101,
  id_cdma2000OneXSRVCCInfo = 102,
  id_E_RABFailedToBeReleasedList = 103,
  id_Source_ToTarget_TransparentContainer = 104,
  id_ServedGUMMEIs = 105,
  id_SubscriberProfileIDforRFP = 106,
  id_UESecurityCapabilities = 107,
  id_CSFallbackIndicator = 108,
  id_CNDomain  = 109,
  id_E_RABReleasedList = 110,
  id_MessageIdentifier = 111,
  id_SerialNumber = 112,
  id_WarningAreaList = 113,
  id_RepetitionPeriod = 114,
  id_NumberofBroadcastRequest = 115,
  id_WarningType = 116,
  id_WarningSecurityInfo = 117,
  id_DataCodingScheme = 118,
  id_WarningMessageContents = 119,
  id_BroadcastCompletedAreaList = 120,
  id_Inter_SystemInformationTransferTypeEDT = 121,
  id_Inter_SystemInformationTransferTypeMDT = 122,
  id_Target_ToSource_TransparentContainer = 123,
  id_SRVCCOperationPossible = 124,
  id_SRVCCHOIndication = 125,
  id_NAS_DownlinkCount = 126,
  id_CSG_Id    = 127,
  id_CSG_IdList = 128,
  id_SONConfigurationTransferECT = 129,
  id_SONConfigurationTransferMCT = 130,
  id_TraceCollectionEntityIPAddress = 131,
  id_MSClassmark2 = 132,
  id_MSClassmark3 = 133,
  id_RRC_Establishment_Cause = 134,
  id_NASSecurityParametersfromE_UTRAN = 135,
  id_NASSecurityParameterstoE_UTRAN = 136,
  id_DefaultPagingDRX = 137,
  id_Source_ToTarget_TransparentContainer_Secondary = 138,
  id_Target_ToSource_TransparentContainer_Secondary = 139,
  id_EUTRANRoundTripDelayEstimationInfo = 140,
  id_BroadcastCancelledAreaList = 141,
  id_ConcurrentWarningMessageIndicator = 142,
  id_Data_Forwarding_Not_Possible = 143,
  id_ExtendedRepetitionPeriod = 144,
  id_CellAccessMode = 145,
  id_CSGMembershipStatus = 146,
  id_LPPa_PDU  = 147,
  id_Routing_ID = 148,
  id_Time_Synchronisation_Info = 149,
  id_PS_ServiceNotAvailable = 150,
  id_PagingPriority = 151,
  id_x2TNLConfigurationInfo = 152,
  id_eNBX2ExtendedTransportLayerAddresses = 153,
  id_GUMMEIList = 154,
  id_GW_TransportLayerAddress = 155,
  id_Correlation_ID = 156,
  id_SourceMME_GUMMEI = 157,
  id_MME_UE_S1AP_ID_2 = 158,
  id_RegisteredLAI = 159,
  id_RelayNode_Indicator = 160,
  id_TrafficLoadReductionIndication = 161,
  id_MDTConfiguration = 162,
  id_MMERelaySupportIndicator = 163,
  id_GWContextReleaseIndication = 164,
  id_ManagementBasedMDTAllowed = 165,
  id_PrivacyIndicator = 166,
  id_Time_UE_StayedInCell_EnhancedGranularity = 167,
  id_HO_Cause  = 168,
  id_VoiceSupportMatchIndicator = 169,
  id_GUMMEIType = 170,
  id_M3Configuration = 171,
  id_M4Configuration = 172,
  id_M5Configuration = 173,
  id_MDT_Location_Info = 174,
  id_MobilityInformation = 175,
  id_Tunnel_Information_for_BBF = 176,
  id_ManagementBasedMDTPLMNList = 177,
  id_SignallingBasedMDTPLMNList = 178,
  id_ULCOUNTValueExtended = 179,
  id_DLCOUNTValueExtended = 180,
  id_ReceiveStatusOfULPDCPSDUsExtended = 181,
  id_ECGIListForRestart = 182,
  id_SIPTO_Correlation_ID = 183,
  id_SIPTO_L_GW_TransportLayerAddress = 184,
  id_TransportInformation = 185,
  id_LHN_ID    = 186,
  id_AdditionalCSFallbackIndicator = 187,
  id_TAIListForRestart = 188,
  id_UserLocationInformation = 189,
  id_EmergencyAreaIDListForRestart = 190,
  id_KillAllWarningMessages = 191,
  id_Masked_IMEISV = 192,
  id_eNBIndirectX2TransportLayerAddresses = 193,
  id_uE_HistoryInformationFromTheUE = 194,
  id_ProSeAuthorized = 195,
  id_ExpectedUEBehaviour = 196,
  id_LoggedMBSFNMDT = 197,
  id_UERadioCapabilityForPaging = 198,
  id_E_RABToBeModifiedListBearerModInd = 199,
  id_E_RABToBeModifiedItemBearerModInd = 200,
  id_E_RABNotToBeModifiedListBearerModInd = 201,
  id_E_RABNotToBeModifiedItemBearerModInd = 202,
  id_E_RABModifyListBearerModConf = 203,
  id_E_RABModifyItemBearerModConf = 204,
  id_E_RABFailedToModifyListBearerModConf = 205,
  id_SON_Information_Report = 206,
  id_Muting_Availability_Indication = 207,
  id_Muting_Pattern_Information = 208,
  id_Synchronisation_Information = 209,
  id_E_RABToBeReleasedListBearerModConf = 210,
  id_AssistanceDataForPaging = 211,
  id_CellIdentifierAndCELevelForCECapableUEs = 212,
  id_InformationOnRecommendedCellsAndENBsForPaging = 213,
  id_RecommendedCellItem = 214,
  id_RecommendedENBItem = 215,
  id_ProSeUEtoNetworkRelaying = 216,
  id_ULCOUNTValuePDCP_SNlength18 = 217,
  id_DLCOUNTValuePDCP_SNlength18 = 218,
  id_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18 = 219,
  id_M6Configuration = 220,
  id_M7Configuration = 221,
  id_PWSfailedECGIList = 222,
  id_MME_Group_ID = 223,
  id_Additional_GUTI = 224,
  id_S1_Message = 225,
  id_CSGMembershipInfo = 226,
  id_Paging_eDRXInformation = 227,
  id_UE_RetentionInformation = 228,
  id_Unknown_229 = 229,
  id_UE_Usage_Type = 230,
  id_extended_UEIdentityIndexValue = 231,
  id_RAT_Type  = 232,
  id_BearerType = 233,
  id_NB_IoT_DefaultPagingDRX = 234,
  id_E_RABFailedToResumeListResumeReq = 235,
  id_E_RABFailedToResumeItemResumeReq = 236,
  id_E_RABFailedToResumeListResumeRes = 237,
  id_E_RABFailedToResumeItemResumeRes = 238,
  id_NB_IoT_Paging_eDRXInformation = 239,
  id_V2XServicesAuthorized = 240,
  id_UEUserPlaneCIoTSupportIndicator = 241,
  id_CE_mode_B_SupportIndicator = 242,
  id_SRVCCOperationNotPossible = 243,
  id_NB_IoT_UEIdentityIndexValue = 244,
  id_RRC_Resume_Cause = 245,
  id_DCN_ID    = 246,
  id_ServedDCNs = 247,
  id_UESidelinkAggregateMaximumBitrate = 248,
  id_DLNASPDUDeliveryAckRequest = 249,
  id_Coverage_Level = 250,
  id_EnhancedCoverageRestricted = 251,
  id_UE_Level_QoS_Parameters = 252,
  id_DL_CP_SecurityInformation = 253,
  id_UL_CP_SecurityInformation = 254,
  id_extended_e_RAB_MaximumBitrateDL = 255,
  id_extended_e_RAB_MaximumBitrateUL = 256,
  id_extended_e_RAB_GuaranteedBitrateDL = 257,
  id_extended_e_RAB_GuaranteedBitrateUL = 258,
  id_extended_uEaggregateMaximumBitRateDL = 259,
  id_extended_uEaggregateMaximumBitRateUL = 260,
  id_NRrestrictioninEPSasSecondaryRAT = 261,
  id_UEAppLayerMeasConfig = 262,
  id_UE_Application_Layer_Measurement_Capability = 263,
  id_SecondaryRATDataUsageReportList = 264,
  id_SecondaryRATDataUsageReportItem = 265,
  id_HandoverFlag = 266,
  id_E_RABUsageReportItem = 267,
  id_SecondaryRATDataUsageRequest = 268,
  id_NRUESecurityCapabilities = 269,
  id_UnlicensedSpectrumRestriction = 270,
  id_CE_ModeBRestricted = 271,
  id_LTE_M_Indication = 272,
  id_DownlinkPacketLossRate = 273,
  id_UplinkPacketLossRate = 274,
  id_UECapabilityInfoRequest = 275,
  id_serviceType = 276,
  id_AerialUEsubscriptionInformation = 277,
  id_Subscription_Based_UE_DifferentiationInfo = 278,
  id_Unknown_279 = 279,
  id_EndIndication = 280,
  id_EDT_Session = 281,
  id_CNTypeRestrictions = 282,
  id_PendingDataIndication = 283,
  id_BluetoothMeasurementConfiguration = 284,
  id_WLANMeasurementConfiguration = 285,
  id_WarningAreaCoordinates = 286,
  id_NRrestrictionin5GS = 287,
  id_PSCellInformation = 288,
  id_Unknown_289 = 289,
  id_LastNG_RANPLMNIdentity = 290,
  id_ConnectedengNBList = 291,
  id_ConnectedengNBToAddList = 292,
  id_ConnectedengNBToRemoveList = 293,
  id_EN_DCSONConfigurationTransfer_ECT = 294,
  id_EN_DCSONConfigurationTransfer_MCT = 295,
  id_IMSvoiceEPSfallbackfrom5G = 296,
  id_TimeSinceSecondaryNodeRelease = 297,
  id_RequestTypeAdditionalInfo = 298,
  id_AdditionalRRMPriorityIndex = 299,
  id_ContextatSource = 300,
  id_IAB_Authorized = 301,
  id_IAB_Node_Indication = 302,
  id_IAB_Supported = 303,
  id_DataSize  = 304,
  id_Ethernet_Type = 305,
  id_NRV2XServicesAuthorized = 306,
  id_NRUESidelinkAggregateMaximumBitrate = 307,
  id_PC5QoSParameters = 308,
  id_IntersystemSONConfigurationTransferMCT = 309,
  id_IntersystemSONConfigurationTransferECT = 310,
  id_IntersystemMeasurementConfiguration = 311,
  id_SourceNodeID = 312,
  id_NB_IoT_RLF_Report_Container = 313,
  id_UERadioCapabilityID = 314,
  id_UERadioCapability_NR_Format = 315,
  id_MDTConfigurationNR = 316,
  id_DAPSRequestInfo = 317,
  id_DAPSResponseInfoList = 318,
  id_DAPSResponseInfoItem = 319,
  id_NotifySourceeNB = 320,
  id_eNB_EarlyStatusTransfer_TransparentContainer = 321,
  id_Bearers_SubjectToEarlyStatusTransfer_Item = 322,
  id_WUS_Assistance_Information = 323,
  id_NB_IoT_PagingDRX = 324,
  id_TraceCollectionEntityURI = 325,
  id_EmergencyIndicator = 326
} ProtocolIE_ID_enum;

typedef enum _HandoverType_enum {
  intralte     =   0,
  ltetoutran   =   1,
  ltetogeran   =   2,
  utrantolte   =   3,
  gerantolte   =   4,
  eps_to_5gs   =   5,
  fivegs_to_eps =   6
} HandoverType_enum;

typedef enum _RAT_Type_enum {
  nbiot        =   0
} RAT_Type_enum;

typedef enum _SRVCCHOIndication_enum {
  pSandCS      =   0,
  cSonly       =   1
} SRVCCHOIndication_enum;

/*--- End of included file: packet-s1ap-val.h ---*/
#line 66 "./asn1/s1ap/packet-s1ap-template.c"

/* Initialize the protocol and registered fields */
static int proto_s1ap = -1;

static int hf_s1ap_transportLayerAddressIPv4 = -1;
static int hf_s1ap_transportLayerAddressIPv6 = -1;
static int hf_s1ap_E_UTRAN_Trace_ID_TraceID = -1;
static int hf_s1ap_E_UTRAN_Trace_ID_TraceRecordingSessionReference = -1;
static int hf_s1ap_interfacesToTrace_S1_MME = -1;
static int hf_s1ap_interfacesToTrace_X2 = -1;
static int hf_s1ap_interfacesToTrace_Uu = -1;
static int hf_s1ap_interfacesToTrace_F1_C = -1;
static int hf_s1ap_interfacesToTrace_E1 = -1;
static int hf_s1ap_interfacesToTrace_Reserved = -1;
static int hf_s1ap_encryptionAlgorithms_EEA1 = -1;
static int hf_s1ap_encryptionAlgorithms_EEA2 = -1;
static int hf_s1ap_encryptionAlgorithms_EEA3 = -1;
static int hf_s1ap_encryptionAlgorithms_Reserved = -1;
static int hf_s1ap_integrityProtectionAlgorithms_EIA1 = -1;
static int hf_s1ap_integrityProtectionAlgorithms_EIA2 = -1;
static int hf_s1ap_integrityProtectionAlgorithms_EIA3 = -1;
static int hf_s1ap_integrityProtectionAlgorithms_Reserved = -1;
static int hf_s1ap_SerialNumber_gs = -1;
static int hf_s1ap_SerialNumber_msg_code = -1;
static int hf_s1ap_SerialNumber_upd_nb = -1;
static int hf_s1ap_WarningType_value = -1;
static int hf_s1ap_WarningType_emergency_user_alert = -1;
static int hf_s1ap_WarningType_popup = -1;
static int hf_s1ap_WarningMessageContents_nb_pages = -1;
static int hf_s1ap_WarningMessageContents_decoded_page = -1;
static int hf_s1ap_measurementsToActivate_M1 = -1;
static int hf_s1ap_measurementsToActivate_M2 = -1;
static int hf_s1ap_measurementsToActivate_M3 = -1;
static int hf_s1ap_measurementsToActivate_M4 = -1;
static int hf_s1ap_measurementsToActivate_M5 = -1;
static int hf_s1ap_measurementsToActivate_LoggingM1FromEventTriggered = -1;
static int hf_s1ap_measurementsToActivate_M6 = -1;
static int hf_s1ap_measurementsToActivate_M7 = -1;
static int hf_s1ap_MDT_Location_Info_GNSS = -1;
static int hf_s1ap_MDT_Location_Info_E_CID = -1;
static int hf_s1ap_MDT_Location_Info_Reserved = -1;
static int hf_s1ap_NRencryptionAlgorithms_NEA1 = -1;
static int hf_s1ap_NRencryptionAlgorithms_NEA2 = -1;
static int hf_s1ap_NRencryptionAlgorithms_NEA3 = -1;
static int hf_s1ap_NRencryptionAlgorithms_Reserved = -1;
static int hf_s1ap_NRintegrityProtectionAlgorithms_NIA1 = -1;
static int hf_s1ap_NRintegrityProtectionAlgorithms_NIA2 = -1;
static int hf_s1ap_NRintegrityProtectionAlgorithms_NIA3 = -1;
static int hf_s1ap_NRintegrityProtectionAlgorithms_Reserved = -1;
static int hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_streaming_service = -1;
static int hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_MTSI_service = -1;
static int hf_s1ap_UE_Application_Layer_Measurement_Capability_Reserved = -1;

/*--- Included file: packet-s1ap-hf.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-hf.c"
static int hf_s1ap_Additional_GUTI_PDU = -1;      /* Additional_GUTI */
static int hf_s1ap_AdditionalRRMPriorityIndex_PDU = -1;  /* AdditionalRRMPriorityIndex */
static int hf_s1ap_AerialUEsubscriptionInformation_PDU = -1;  /* AerialUEsubscriptionInformation */
static int hf_s1ap_AssistanceDataForPaging_PDU = -1;  /* AssistanceDataForPaging */
static int hf_s1ap_Bearers_SubjectToStatusTransfer_Item_PDU = -1;  /* Bearers_SubjectToStatusTransfer_Item */
static int hf_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item_PDU = -1;  /* Bearers_SubjectToEarlyStatusTransfer_Item */
static int hf_s1ap_BearerType_PDU = -1;           /* BearerType */
static int hf_s1ap_BluetoothMeasurementConfiguration_PDU = -1;  /* BluetoothMeasurementConfiguration */
static int hf_s1ap_BroadcastCancelledAreaList_PDU = -1;  /* BroadcastCancelledAreaList */
static int hf_s1ap_BroadcastCompletedAreaList_PDU = -1;  /* BroadcastCompletedAreaList */
static int hf_s1ap_Cause_PDU = -1;                /* Cause */
static int hf_s1ap_CellAccessMode_PDU = -1;       /* CellAccessMode */
static int hf_s1ap_CellIdentifierAndCELevelForCECapableUEs_PDU = -1;  /* CellIdentifierAndCELevelForCECapableUEs */
static int hf_s1ap_CE_mode_B_SupportIndicator_PDU = -1;  /* CE_mode_B_SupportIndicator */
static int hf_s1ap_Cdma2000PDU_PDU = -1;          /* Cdma2000PDU */
static int hf_s1ap_Cdma2000RATType_PDU = -1;      /* Cdma2000RATType */
static int hf_s1ap_Cdma2000SectorID_PDU = -1;     /* Cdma2000SectorID */
static int hf_s1ap_Cdma2000HOStatus_PDU = -1;     /* Cdma2000HOStatus */
static int hf_s1ap_Cdma2000HORequiredIndication_PDU = -1;  /* Cdma2000HORequiredIndication */
static int hf_s1ap_Cdma2000OneXSRVCCInfo_PDU = -1;  /* Cdma2000OneXSRVCCInfo */
static int hf_s1ap_Cdma2000OneXRAND_PDU = -1;     /* Cdma2000OneXRAND */
static int hf_s1ap_CNDomain_PDU = -1;             /* CNDomain */
static int hf_s1ap_CNTypeRestrictions_PDU = -1;   /* CNTypeRestrictions */
static int hf_s1ap_ConcurrentWarningMessageIndicator_PDU = -1;  /* ConcurrentWarningMessageIndicator */
static int hf_s1ap_ConnectedengNBList_PDU = -1;   /* ConnectedengNBList */
static int hf_s1ap_ContextatSource_PDU = -1;      /* ContextatSource */
static int hf_s1ap_Correlation_ID_PDU = -1;       /* Correlation_ID */
static int hf_s1ap_CSFallbackIndicator_PDU = -1;  /* CSFallbackIndicator */
static int hf_s1ap_AdditionalCSFallbackIndicator_PDU = -1;  /* AdditionalCSFallbackIndicator */
static int hf_s1ap_CSG_Id_PDU = -1;               /* CSG_Id */
static int hf_s1ap_CSG_IdList_PDU = -1;           /* CSG_IdList */
static int hf_s1ap_CSGMembershipStatus_PDU = -1;  /* CSGMembershipStatus */
static int hf_s1ap_COUNTValueExtended_PDU = -1;   /* COUNTValueExtended */
static int hf_s1ap_COUNTvaluePDCP_SNlength18_PDU = -1;  /* COUNTvaluePDCP_SNlength18 */
static int hf_s1ap_Coverage_Level_PDU = -1;       /* Coverage_Level */
static int hf_s1ap_CriticalityDiagnostics_PDU = -1;  /* CriticalityDiagnostics */
static int hf_s1ap_DAPSRequestInfo_PDU = -1;      /* DAPSRequestInfo */
static int hf_s1ap_DAPSResponseInfoList_PDU = -1;  /* DAPSResponseInfoList */
static int hf_s1ap_DAPSResponseInfoItem_PDU = -1;  /* DAPSResponseInfoItem */
static int hf_s1ap_DataCodingScheme_PDU = -1;     /* DataCodingScheme */
static int hf_s1ap_DataSize_PDU = -1;             /* DataSize */
static int hf_s1ap_DCN_ID_PDU = -1;               /* DCN_ID */
static int hf_s1ap_ServedDCNs_PDU = -1;           /* ServedDCNs */
static int hf_s1ap_DL_CP_SecurityInformation_PDU = -1;  /* DL_CP_SecurityInformation */
static int hf_s1ap_Direct_Forwarding_Path_Availability_PDU = -1;  /* Direct_Forwarding_Path_Availability */
static int hf_s1ap_Data_Forwarding_Not_Possible_PDU = -1;  /* Data_Forwarding_Not_Possible */
static int hf_s1ap_DLNASPDUDeliveryAckRequest_PDU = -1;  /* DLNASPDUDeliveryAckRequest */
static int hf_s1ap_PWSfailedECGIList_PDU = -1;    /* PWSfailedECGIList */
static int hf_s1ap_EDT_Session_PDU = -1;          /* EDT_Session */
static int hf_s1ap_EmergencyAreaIDListForRestart_PDU = -1;  /* EmergencyAreaIDListForRestart */
static int hf_s1ap_EmergencyIndicator_PDU = -1;   /* EmergencyIndicator */
static int hf_s1ap_ENB_EarlyStatusTransfer_TransparentContainer_PDU = -1;  /* ENB_EarlyStatusTransfer_TransparentContainer */
static int hf_s1ap_s1ap_Global_ENB_ID_PDU = -1;   /* Global_ENB_ID */
static int hf_s1ap_GUMMEIList_PDU = -1;           /* GUMMEIList */
static int hf_s1ap_s1ap_ENB_StatusTransfer_TransparentContainer_PDU = -1;  /* ENB_StatusTransfer_TransparentContainer */
static int hf_s1ap_ENB_UE_S1AP_ID_PDU = -1;       /* ENB_UE_S1AP_ID */
static int hf_s1ap_ENBname_PDU = -1;              /* ENBname */
static int hf_s1ap_s1ap_EN_DCSONConfigurationTransfer_PDU = -1;  /* EN_DCSONConfigurationTransfer */
static int hf_s1ap_EndIndication_PDU = -1;        /* EndIndication */
static int hf_s1ap_EnhancedCoverageRestricted_PDU = -1;  /* EnhancedCoverageRestricted */
static int hf_s1ap_CE_ModeBRestricted_PDU = -1;   /* CE_ModeBRestricted */
static int hf_s1ap_E_RABInformationListItem_PDU = -1;  /* E_RABInformationListItem */
static int hf_s1ap_E_RABList_PDU = -1;            /* E_RABList */
static int hf_s1ap_E_RABItem_PDU = -1;            /* E_RABItem */
static int hf_s1ap_E_RABLevelQoSParameters_PDU = -1;  /* E_RABLevelQoSParameters */
static int hf_s1ap_E_RABUsageReportItem_PDU = -1;  /* E_RABUsageReportItem */
static int hf_s1ap_Ethernet_Type_PDU = -1;        /* Ethernet_Type */
static int hf_s1ap_s1ap_EUTRAN_CGI_PDU = -1;      /* EUTRAN_CGI */
static int hf_s1ap_EUTRANRoundTripDelayEstimationInfo_PDU = -1;  /* EUTRANRoundTripDelayEstimationInfo */
static int hf_s1ap_ExpectedUEBehaviour_PDU = -1;  /* ExpectedUEBehaviour */
static int hf_s1ap_ExtendedBitRate_PDU = -1;      /* ExtendedBitRate */
static int hf_s1ap_ExtendedRepetitionPeriod_PDU = -1;  /* ExtendedRepetitionPeriod */
static int hf_s1ap_Extended_UEIdentityIndexValue_PDU = -1;  /* Extended_UEIdentityIndexValue */
static int hf_s1ap_GUMMEI_PDU = -1;               /* GUMMEI */
static int hf_s1ap_GUMMEIType_PDU = -1;           /* GUMMEIType */
static int hf_s1ap_GWContextReleaseIndication_PDU = -1;  /* GWContextReleaseIndication */
static int hf_s1ap_HandoverFlag_PDU = -1;         /* HandoverFlag */
static int hf_s1ap_s1ap_HandoverRestrictionList_PDU = -1;  /* HandoverRestrictionList */
static int hf_s1ap_HandoverType_PDU = -1;         /* HandoverType */
static int hf_s1ap_Masked_IMEISV_PDU = -1;        /* Masked_IMEISV */
static int hf_s1ap_s1ap_ImmediateMDT_PDU = -1;    /* ImmediateMDT */
static int hf_s1ap_InformationOnRecommendedCellsAndENBsForPaging_PDU = -1;  /* InformationOnRecommendedCellsAndENBsForPaging */
static int hf_s1ap_IntersystemMeasurementConfiguration_PDU = -1;  /* IntersystemMeasurementConfiguration */
static int hf_s1ap_IntersystemSONConfigurationTransfer_PDU = -1;  /* IntersystemSONConfigurationTransfer */
static int hf_s1ap_IMSvoiceEPSfallbackfrom5G_PDU = -1;  /* IMSvoiceEPSfallbackfrom5G */
static int hf_s1ap_IAB_Authorized_PDU = -1;       /* IAB_Authorized */
static int hf_s1ap_IAB_Node_Indication_PDU = -1;  /* IAB_Node_Indication */
static int hf_s1ap_IAB_Supported_PDU = -1;        /* IAB_Supported */
static int hf_s1ap_KillAllWarningMessages_PDU = -1;  /* KillAllWarningMessages */
static int hf_s1ap_LAI_PDU = -1;                  /* LAI */
static int hf_s1ap_s1ap_LastVisitedEUTRANCellInformation_PDU = -1;  /* LastVisitedEUTRANCellInformation */
static int hf_s1ap_s1ap_LastVisitedGERANCellInformation_PDU = -1;  /* LastVisitedGERANCellInformation */
static int hf_s1ap_LPPa_PDU_PDU = -1;             /* LPPa_PDU */
static int hf_s1ap_LHN_ID_PDU = -1;               /* LHN_ID */
static int hf_s1ap_LoggedMBSFNMDT_PDU = -1;       /* LoggedMBSFNMDT */
static int hf_s1ap_LTE_M_Indication_PDU = -1;     /* LTE_M_Indication */
static int hf_s1ap_M3Configuration_PDU = -1;      /* M3Configuration */
static int hf_s1ap_M4Configuration_PDU = -1;      /* M4Configuration */
static int hf_s1ap_M5Configuration_PDU = -1;      /* M5Configuration */
static int hf_s1ap_M6Configuration_PDU = -1;      /* M6Configuration */
static int hf_s1ap_M7Configuration_PDU = -1;      /* M7Configuration */
static int hf_s1ap_MDT_Location_Info_PDU = -1;    /* MDT_Location_Info */
static int hf_s1ap_MDT_Configuration_PDU = -1;    /* MDT_Configuration */
static int hf_s1ap_ManagementBasedMDTAllowed_PDU = -1;  /* ManagementBasedMDTAllowed */
static int hf_s1ap_MDTPLMNList_PDU = -1;          /* MDTPLMNList */
static int hf_s1ap_PrivacyIndicator_PDU = -1;     /* PrivacyIndicator */
static int hf_s1ap_s1ap_MDTMode_PDU = -1;         /* MDTMode */
static int hf_s1ap_MessageIdentifier_PDU = -1;    /* MessageIdentifier */
static int hf_s1ap_MobilityInformation_PDU = -1;  /* MobilityInformation */
static int hf_s1ap_MMEname_PDU = -1;              /* MMEname */
static int hf_s1ap_MMERelaySupportIndicator_PDU = -1;  /* MMERelaySupportIndicator */
static int hf_s1ap_MME_Group_ID_PDU = -1;         /* MME_Group_ID */
static int hf_s1ap_MME_UE_S1AP_ID_PDU = -1;       /* MME_UE_S1AP_ID */
static int hf_s1ap_MSClassmark2_PDU = -1;         /* MSClassmark2 */
static int hf_s1ap_MSClassmark3_PDU = -1;         /* MSClassmark3 */
static int hf_s1ap_MutingAvailabilityIndication_PDU = -1;  /* MutingAvailabilityIndication */
static int hf_s1ap_MutingPatternInformation_PDU = -1;  /* MutingPatternInformation */
static int hf_s1ap_MDT_ConfigurationNR_PDU = -1;  /* MDT_ConfigurationNR */
static int hf_s1ap_NAS_PDU_PDU = -1;              /* NAS_PDU */
static int hf_s1ap_NASSecurityParametersfromE_UTRAN_PDU = -1;  /* NASSecurityParametersfromE_UTRAN */
static int hf_s1ap_NASSecurityParameterstoE_UTRAN_PDU = -1;  /* NASSecurityParameterstoE_UTRAN */
static int hf_s1ap_NB_IoT_DefaultPagingDRX_PDU = -1;  /* NB_IoT_DefaultPagingDRX */
static int hf_s1ap_NB_IoT_PagingDRX_PDU = -1;     /* NB_IoT_PagingDRX */
static int hf_s1ap_NB_IoT_Paging_eDRXInformation_PDU = -1;  /* NB_IoT_Paging_eDRXInformation */
static int hf_s1ap_NB_IoT_RLF_Report_Container_PDU = -1;  /* NB_IoT_RLF_Report_Container */
static int hf_s1ap_NB_IoT_UEIdentityIndexValue_PDU = -1;  /* NB_IoT_UEIdentityIndexValue */
static int hf_s1ap_NotifySourceeNB_PDU = -1;      /* NotifySourceeNB */
static int hf_s1ap_NRrestrictioninEPSasSecondaryRAT_PDU = -1;  /* NRrestrictioninEPSasSecondaryRAT */
static int hf_s1ap_NRrestrictionin5GS_PDU = -1;   /* NRrestrictionin5GS */
static int hf_s1ap_NRUESecurityCapabilities_PDU = -1;  /* NRUESecurityCapabilities */
static int hf_s1ap_NumberofBroadcastRequest_PDU = -1;  /* NumberofBroadcastRequest */
static int hf_s1ap_NRV2XServicesAuthorized_PDU = -1;  /* NRV2XServicesAuthorized */
static int hf_s1ap_NRUESidelinkAggregateMaximumBitrate_PDU = -1;  /* NRUESidelinkAggregateMaximumBitrate */
static int hf_s1ap_OverloadResponse_PDU = -1;     /* OverloadResponse */
static int hf_s1ap_Packet_LossRate_PDU = -1;      /* Packet_LossRate */
static int hf_s1ap_Paging_eDRXInformation_PDU = -1;  /* Paging_eDRXInformation */
static int hf_s1ap_PagingDRX_PDU = -1;            /* PagingDRX */
static int hf_s1ap_PagingPriority_PDU = -1;       /* PagingPriority */
static int hf_s1ap_PC5QoSParameters_PDU = -1;     /* PC5QoSParameters */
static int hf_s1ap_PendingDataIndication_PDU = -1;  /* PendingDataIndication */
static int hf_s1ap_PLMNidentity_PDU = -1;         /* PLMNidentity */
static int hf_s1ap_ProSeAuthorized_PDU = -1;      /* ProSeAuthorized */
static int hf_s1ap_ProSeUEtoNetworkRelaying_PDU = -1;  /* ProSeUEtoNetworkRelaying */
static int hf_s1ap_PS_ServiceNotAvailable_PDU = -1;  /* PS_ServiceNotAvailable */
static int hf_s1ap_PSCellInformation_PDU = -1;    /* PSCellInformation */
static int hf_s1ap_ReceiveStatusOfULPDCPSDUsExtended_PDU = -1;  /* ReceiveStatusOfULPDCPSDUsExtended */
static int hf_s1ap_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18_PDU = -1;  /* ReceiveStatusOfULPDCPSDUsPDCP_SNlength18 */
static int hf_s1ap_RecommendedCellItem_PDU = -1;  /* RecommendedCellItem */
static int hf_s1ap_RecommendedENBItem_PDU = -1;   /* RecommendedENBItem */
static int hf_s1ap_RelativeMMECapacity_PDU = -1;  /* RelativeMMECapacity */
static int hf_s1ap_RelayNode_Indicator_PDU = -1;  /* RelayNode_Indicator */
static int hf_s1ap_RAT_Type_PDU = -1;             /* RAT_Type */
static int hf_s1ap_RequestType_PDU = -1;          /* RequestType */
static int hf_s1ap_RequestTypeAdditionalInfo_PDU = -1;  /* RequestTypeAdditionalInfo */
static int hf_s1ap_RepetitionPeriod_PDU = -1;     /* RepetitionPeriod */
static int hf_s1ap_RRC_Establishment_Cause_PDU = -1;  /* RRC_Establishment_Cause */
static int hf_s1ap_ECGIListForRestart_PDU = -1;   /* ECGIListForRestart */
static int hf_s1ap_Routing_ID_PDU = -1;           /* Routing_ID */
static int hf_s1ap_SecurityKey_PDU = -1;          /* SecurityKey */
static int hf_s1ap_SecurityContext_PDU = -1;      /* SecurityContext */
static int hf_s1ap_SecondaryRATDataUsageRequest_PDU = -1;  /* SecondaryRATDataUsageRequest */
static int hf_s1ap_SecondaryRATDataUsageReportList_PDU = -1;  /* SecondaryRATDataUsageReportList */
static int hf_s1ap_SecondaryRATDataUsageReportItem_PDU = -1;  /* SecondaryRATDataUsageReportItem */
static int hf_s1ap_SerialNumber_PDU = -1;         /* SerialNumber */
static int hf_s1ap_ServiceType_PDU = -1;          /* ServiceType */
static int hf_s1ap_SONInformationReport_PDU = -1;  /* SONInformationReport */
static int hf_s1ap_s1ap_SONConfigurationTransfer_PDU = -1;  /* SONConfigurationTransfer */
static int hf_s1ap_SynchronisationInformation_PDU = -1;  /* SynchronisationInformation */
static int hf_s1ap_Source_ToTarget_TransparentContainer_PDU = -1;  /* Source_ToTarget_TransparentContainer */
static int hf_s1ap_SRVCCOperationNotPossible_PDU = -1;  /* SRVCCOperationNotPossible */
static int hf_s1ap_SRVCCOperationPossible_PDU = -1;  /* SRVCCOperationPossible */
static int hf_s1ap_SRVCCHOIndication_PDU = -1;    /* SRVCCHOIndication */
static int hf_s1ap_SourceNodeID_PDU = -1;         /* SourceNodeID */
static int hf_s1ap_s1ap_SourceeNB_ToTargeteNB_TransparentContainer_PDU = -1;  /* SourceeNB_ToTargeteNB_TransparentContainer */
static int hf_s1ap_ServedGUMMEIs_PDU = -1;        /* ServedGUMMEIs */
static int hf_s1ap_ServedPLMNs_PDU = -1;          /* ServedPLMNs */
static int hf_s1ap_SubscriberProfileIDforRFP_PDU = -1;  /* SubscriberProfileIDforRFP */
static int hf_s1ap_Subscription_Based_UE_DifferentiationInfo_PDU = -1;  /* Subscription_Based_UE_DifferentiationInfo */
static int hf_s1ap_SupportedTAs_PDU = -1;         /* SupportedTAs */
static int hf_s1ap_TimeSynchronisationInfo_PDU = -1;  /* TimeSynchronisationInfo */
static int hf_s1ap_S_TMSI_PDU = -1;               /* S_TMSI */
static int hf_s1ap_TAI_PDU = -1;                  /* TAI */
static int hf_s1ap_TargetID_PDU = -1;             /* TargetID */
static int hf_s1ap_s1ap_TargeteNB_ToSourceeNB_TransparentContainer_PDU = -1;  /* TargeteNB_ToSourceeNB_TransparentContainer */
static int hf_s1ap_Target_ToSource_TransparentContainer_PDU = -1;  /* Target_ToSource_TransparentContainer */
static int hf_s1ap_TimeToWait_PDU = -1;           /* TimeToWait */
static int hf_s1ap_Time_UE_StayedInCell_EnhancedGranularity_PDU = -1;  /* Time_UE_StayedInCell_EnhancedGranularity */
static int hf_s1ap_TimeSinceSecondaryNodeRelease_PDU = -1;  /* TimeSinceSecondaryNodeRelease */
static int hf_s1ap_TransportInformation_PDU = -1;  /* TransportInformation */
static int hf_s1ap_TransportLayerAddress_PDU = -1;  /* TransportLayerAddress */
static int hf_s1ap_TraceActivation_PDU = -1;      /* TraceActivation */
static int hf_s1ap_E_UTRAN_Trace_ID_PDU = -1;     /* E_UTRAN_Trace_ID */
static int hf_s1ap_TrafficLoadReductionIndication_PDU = -1;  /* TrafficLoadReductionIndication */
static int hf_s1ap_TunnelInformation_PDU = -1;    /* TunnelInformation */
static int hf_s1ap_TAIListForRestart_PDU = -1;    /* TAIListForRestart */
static int hf_s1ap_UEAggregateMaximumBitrate_PDU = -1;  /* UEAggregateMaximumBitrate */
static int hf_s1ap_UEAppLayerMeasConfig_PDU = -1;  /* UEAppLayerMeasConfig */
static int hf_s1ap_UECapabilityInfoRequest_PDU = -1;  /* UECapabilityInfoRequest */
static int hf_s1ap_UE_RetentionInformation_PDU = -1;  /* UE_RetentionInformation */
static int hf_s1ap_UE_S1AP_IDs_PDU = -1;          /* UE_S1AP_IDs */
static int hf_s1ap_UE_associatedLogicalS1_ConnectionItem_PDU = -1;  /* UE_associatedLogicalS1_ConnectionItem */
static int hf_s1ap_UEIdentityIndexValue_PDU = -1;  /* UEIdentityIndexValue */
static int hf_s1ap_s1ap_UE_HistoryInformation_PDU = -1;  /* UE_HistoryInformation */
static int hf_s1ap_UE_HistoryInformationFromTheUE_PDU = -1;  /* UE_HistoryInformationFromTheUE */
static int hf_s1ap_UEPagingID_PDU = -1;           /* UEPagingID */
static int hf_s1ap_UERadioCapability_PDU = -1;    /* UERadioCapability */
static int hf_s1ap_UERadioCapabilityForPaging_PDU = -1;  /* UERadioCapabilityForPaging */
static int hf_s1ap_UERadioCapabilityID_PDU = -1;  /* UERadioCapabilityID */
static int hf_s1ap_UESecurityCapabilities_PDU = -1;  /* UESecurityCapabilities */
static int hf_s1ap_UESidelinkAggregateMaximumBitrate_PDU = -1;  /* UESidelinkAggregateMaximumBitrate */
static int hf_s1ap_UE_Usage_Type_PDU = -1;        /* UE_Usage_Type */
static int hf_s1ap_UL_CP_SecurityInformation_PDU = -1;  /* UL_CP_SecurityInformation */
static int hf_s1ap_UnlicensedSpectrumRestriction_PDU = -1;  /* UnlicensedSpectrumRestriction */
static int hf_s1ap_URI_Address_PDU = -1;          /* URI_Address */
static int hf_s1ap_UserLocationInformation_PDU = -1;  /* UserLocationInformation */
static int hf_s1ap_UEUserPlaneCIoTSupportIndicator_PDU = -1;  /* UEUserPlaneCIoTSupportIndicator */
static int hf_s1ap_UE_Application_Layer_Measurement_Capability_PDU = -1;  /* UE_Application_Layer_Measurement_Capability */
static int hf_s1ap_VoiceSupportMatchIndicator_PDU = -1;  /* VoiceSupportMatchIndicator */
static int hf_s1ap_V2XServicesAuthorized_PDU = -1;  /* V2XServicesAuthorized */
static int hf_s1ap_WarningAreaCoordinates_PDU = -1;  /* WarningAreaCoordinates */
static int hf_s1ap_WarningAreaList_PDU = -1;      /* WarningAreaList */
static int hf_s1ap_WarningType_PDU = -1;          /* WarningType */
static int hf_s1ap_WarningSecurityInfo_PDU = -1;  /* WarningSecurityInfo */
static int hf_s1ap_WarningMessageContents_PDU = -1;  /* WarningMessageContents */
static int hf_s1ap_WLANMeasurementConfiguration_PDU = -1;  /* WLANMeasurementConfiguration */
static int hf_s1ap_WUS_Assistance_Information_PDU = -1;  /* WUS_Assistance_Information */
static int hf_s1ap_X2TNLConfigurationInfo_PDU = -1;  /* X2TNLConfigurationInfo */
static int hf_s1ap_ENBX2ExtTLAs_PDU = -1;         /* ENBX2ExtTLAs */
static int hf_s1ap_ENBIndirectX2TransportLayerAddresses_PDU = -1;  /* ENBIndirectX2TransportLayerAddresses */
static int hf_s1ap_HandoverRequired_PDU = -1;     /* HandoverRequired */
static int hf_s1ap_HandoverCommand_PDU = -1;      /* HandoverCommand */
static int hf_s1ap_E_RABSubjecttoDataForwardingList_PDU = -1;  /* E_RABSubjecttoDataForwardingList */
static int hf_s1ap_E_RABDataForwardingItem_PDU = -1;  /* E_RABDataForwardingItem */
static int hf_s1ap_HandoverPreparationFailure_PDU = -1;  /* HandoverPreparationFailure */
static int hf_s1ap_HandoverRequest_PDU = -1;      /* HandoverRequest */
static int hf_s1ap_E_RABToBeSetupListHOReq_PDU = -1;  /* E_RABToBeSetupListHOReq */
static int hf_s1ap_E_RABToBeSetupItemHOReq_PDU = -1;  /* E_RABToBeSetupItemHOReq */
static int hf_s1ap_HandoverRequestAcknowledge_PDU = -1;  /* HandoverRequestAcknowledge */
static int hf_s1ap_E_RABAdmittedList_PDU = -1;    /* E_RABAdmittedList */
static int hf_s1ap_E_RABAdmittedItem_PDU = -1;    /* E_RABAdmittedItem */
static int hf_s1ap_E_RABFailedtoSetupListHOReqAck_PDU = -1;  /* E_RABFailedtoSetupListHOReqAck */
static int hf_s1ap_E_RABFailedToSetupItemHOReqAck_PDU = -1;  /* E_RABFailedToSetupItemHOReqAck */
static int hf_s1ap_HandoverFailure_PDU = -1;      /* HandoverFailure */
static int hf_s1ap_HandoverNotify_PDU = -1;       /* HandoverNotify */
static int hf_s1ap_PathSwitchRequest_PDU = -1;    /* PathSwitchRequest */
static int hf_s1ap_E_RABToBeSwitchedDLList_PDU = -1;  /* E_RABToBeSwitchedDLList */
static int hf_s1ap_E_RABToBeSwitchedDLItem_PDU = -1;  /* E_RABToBeSwitchedDLItem */
static int hf_s1ap_PathSwitchRequestAcknowledge_PDU = -1;  /* PathSwitchRequestAcknowledge */
static int hf_s1ap_E_RABToBeSwitchedULList_PDU = -1;  /* E_RABToBeSwitchedULList */
static int hf_s1ap_E_RABToBeSwitchedULItem_PDU = -1;  /* E_RABToBeSwitchedULItem */
static int hf_s1ap_PathSwitchRequestFailure_PDU = -1;  /* PathSwitchRequestFailure */
static int hf_s1ap_HandoverCancel_PDU = -1;       /* HandoverCancel */
static int hf_s1ap_HandoverCancelAcknowledge_PDU = -1;  /* HandoverCancelAcknowledge */
static int hf_s1ap_HandoverSuccess_PDU = -1;      /* HandoverSuccess */
static int hf_s1ap_ENBEarlyStatusTransfer_PDU = -1;  /* ENBEarlyStatusTransfer */
static int hf_s1ap_MMEEarlyStatusTransfer_PDU = -1;  /* MMEEarlyStatusTransfer */
static int hf_s1ap_E_RABSetupRequest_PDU = -1;    /* E_RABSetupRequest */
static int hf_s1ap_E_RABToBeSetupListBearerSUReq_PDU = -1;  /* E_RABToBeSetupListBearerSUReq */
static int hf_s1ap_E_RABToBeSetupItemBearerSUReq_PDU = -1;  /* E_RABToBeSetupItemBearerSUReq */
static int hf_s1ap_E_RABSetupResponse_PDU = -1;   /* E_RABSetupResponse */
static int hf_s1ap_E_RABSetupListBearerSURes_PDU = -1;  /* E_RABSetupListBearerSURes */
static int hf_s1ap_E_RABSetupItemBearerSURes_PDU = -1;  /* E_RABSetupItemBearerSURes */
static int hf_s1ap_E_RABModifyRequest_PDU = -1;   /* E_RABModifyRequest */
static int hf_s1ap_E_RABToBeModifiedListBearerModReq_PDU = -1;  /* E_RABToBeModifiedListBearerModReq */
static int hf_s1ap_E_RABToBeModifiedItemBearerModReq_PDU = -1;  /* E_RABToBeModifiedItemBearerModReq */
static int hf_s1ap_E_RABModifyResponse_PDU = -1;  /* E_RABModifyResponse */
static int hf_s1ap_E_RABModifyListBearerModRes_PDU = -1;  /* E_RABModifyListBearerModRes */
static int hf_s1ap_E_RABModifyItemBearerModRes_PDU = -1;  /* E_RABModifyItemBearerModRes */
static int hf_s1ap_E_RABReleaseCommand_PDU = -1;  /* E_RABReleaseCommand */
static int hf_s1ap_E_RABReleaseResponse_PDU = -1;  /* E_RABReleaseResponse */
static int hf_s1ap_E_RABReleaseListBearerRelComp_PDU = -1;  /* E_RABReleaseListBearerRelComp */
static int hf_s1ap_E_RABReleaseItemBearerRelComp_PDU = -1;  /* E_RABReleaseItemBearerRelComp */
static int hf_s1ap_E_RABReleaseIndication_PDU = -1;  /* E_RABReleaseIndication */
static int hf_s1ap_InitialContextSetupRequest_PDU = -1;  /* InitialContextSetupRequest */
static int hf_s1ap_E_RABToBeSetupListCtxtSUReq_PDU = -1;  /* E_RABToBeSetupListCtxtSUReq */
static int hf_s1ap_E_RABToBeSetupItemCtxtSUReq_PDU = -1;  /* E_RABToBeSetupItemCtxtSUReq */
static int hf_s1ap_InitialContextSetupResponse_PDU = -1;  /* InitialContextSetupResponse */
static int hf_s1ap_E_RABSetupListCtxtSURes_PDU = -1;  /* E_RABSetupListCtxtSURes */
static int hf_s1ap_E_RABSetupItemCtxtSURes_PDU = -1;  /* E_RABSetupItemCtxtSURes */
static int hf_s1ap_InitialContextSetupFailure_PDU = -1;  /* InitialContextSetupFailure */
static int hf_s1ap_Paging_PDU = -1;               /* Paging */
static int hf_s1ap_TAIList_PDU = -1;              /* TAIList */
static int hf_s1ap_TAIItem_PDU = -1;              /* TAIItem */
static int hf_s1ap_UEContextReleaseRequest_PDU = -1;  /* UEContextReleaseRequest */
static int hf_s1ap_UEContextReleaseCommand_PDU = -1;  /* UEContextReleaseCommand */
static int hf_s1ap_UEContextReleaseComplete_PDU = -1;  /* UEContextReleaseComplete */
static int hf_s1ap_UEContextModificationRequest_PDU = -1;  /* UEContextModificationRequest */
static int hf_s1ap_UEContextModificationResponse_PDU = -1;  /* UEContextModificationResponse */
static int hf_s1ap_UEContextModificationFailure_PDU = -1;  /* UEContextModificationFailure */
static int hf_s1ap_UERadioCapabilityMatchRequest_PDU = -1;  /* UERadioCapabilityMatchRequest */
static int hf_s1ap_UERadioCapabilityMatchResponse_PDU = -1;  /* UERadioCapabilityMatchResponse */
static int hf_s1ap_DownlinkNASTransport_PDU = -1;  /* DownlinkNASTransport */
static int hf_s1ap_InitialUEMessage_PDU = -1;     /* InitialUEMessage */
static int hf_s1ap_UplinkNASTransport_PDU = -1;   /* UplinkNASTransport */
static int hf_s1ap_NASNonDeliveryIndication_PDU = -1;  /* NASNonDeliveryIndication */
static int hf_s1ap_RerouteNASRequest_PDU = -1;    /* RerouteNASRequest */
static int hf_s1ap_S1_Message_PDU = -1;           /* S1_Message */
static int hf_s1ap_NASDeliveryIndication_PDU = -1;  /* NASDeliveryIndication */
static int hf_s1ap_Reset_PDU = -1;                /* Reset */
static int hf_s1ap_ResetType_PDU = -1;            /* ResetType */
static int hf_s1ap_ResetAcknowledge_PDU = -1;     /* ResetAcknowledge */
static int hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_PDU = -1;  /* UE_associatedLogicalS1_ConnectionListResAck */
static int hf_s1ap_ErrorIndication_PDU = -1;      /* ErrorIndication */
static int hf_s1ap_S1SetupRequest_PDU = -1;       /* S1SetupRequest */
static int hf_s1ap_S1SetupResponse_PDU = -1;      /* S1SetupResponse */
static int hf_s1ap_S1SetupFailure_PDU = -1;       /* S1SetupFailure */
static int hf_s1ap_ENBConfigurationUpdate_PDU = -1;  /* ENBConfigurationUpdate */
static int hf_s1ap_ENBConfigurationUpdateAcknowledge_PDU = -1;  /* ENBConfigurationUpdateAcknowledge */
static int hf_s1ap_ENBConfigurationUpdateFailure_PDU = -1;  /* ENBConfigurationUpdateFailure */
static int hf_s1ap_MMEConfigurationUpdate_PDU = -1;  /* MMEConfigurationUpdate */
static int hf_s1ap_MMEConfigurationUpdateAcknowledge_PDU = -1;  /* MMEConfigurationUpdateAcknowledge */
static int hf_s1ap_MMEConfigurationUpdateFailure_PDU = -1;  /* MMEConfigurationUpdateFailure */
static int hf_s1ap_DownlinkS1cdma2000tunnelling_PDU = -1;  /* DownlinkS1cdma2000tunnelling */
static int hf_s1ap_UplinkS1cdma2000tunnelling_PDU = -1;  /* UplinkS1cdma2000tunnelling */
static int hf_s1ap_UECapabilityInfoIndication_PDU = -1;  /* UECapabilityInfoIndication */
static int hf_s1ap_ENBStatusTransfer_PDU = -1;    /* ENBStatusTransfer */
static int hf_s1ap_MMEStatusTransfer_PDU = -1;    /* MMEStatusTransfer */
static int hf_s1ap_TraceStart_PDU = -1;           /* TraceStart */
static int hf_s1ap_TraceFailureIndication_PDU = -1;  /* TraceFailureIndication */
static int hf_s1ap_DeactivateTrace_PDU = -1;      /* DeactivateTrace */
static int hf_s1ap_CellTrafficTrace_PDU = -1;     /* CellTrafficTrace */
static int hf_s1ap_LocationReportingControl_PDU = -1;  /* LocationReportingControl */
static int hf_s1ap_LocationReportingFailureIndication_PDU = -1;  /* LocationReportingFailureIndication */
static int hf_s1ap_LocationReport_PDU = -1;       /* LocationReport */
static int hf_s1ap_OverloadStart_PDU = -1;        /* OverloadStart */
static int hf_s1ap_OverloadStop_PDU = -1;         /* OverloadStop */
static int hf_s1ap_WriteReplaceWarningRequest_PDU = -1;  /* WriteReplaceWarningRequest */
static int hf_s1ap_WriteReplaceWarningResponse_PDU = -1;  /* WriteReplaceWarningResponse */
static int hf_s1ap_ENBDirectInformationTransfer_PDU = -1;  /* ENBDirectInformationTransfer */
static int hf_s1ap_Inter_SystemInformationTransferType_PDU = -1;  /* Inter_SystemInformationTransferType */
static int hf_s1ap_MMEDirectInformationTransfer_PDU = -1;  /* MMEDirectInformationTransfer */
static int hf_s1ap_ENBConfigurationTransfer_PDU = -1;  /* ENBConfigurationTransfer */
static int hf_s1ap_MMEConfigurationTransfer_PDU = -1;  /* MMEConfigurationTransfer */
static int hf_s1ap_PrivateMessage_PDU = -1;       /* PrivateMessage */
static int hf_s1ap_KillRequest_PDU = -1;          /* KillRequest */
static int hf_s1ap_KillResponse_PDU = -1;         /* KillResponse */
static int hf_s1ap_PWSRestartIndication_PDU = -1;  /* PWSRestartIndication */
static int hf_s1ap_PWSFailureIndication_PDU = -1;  /* PWSFailureIndication */
static int hf_s1ap_DownlinkUEAssociatedLPPaTransport_PDU = -1;  /* DownlinkUEAssociatedLPPaTransport */
static int hf_s1ap_UplinkUEAssociatedLPPaTransport_PDU = -1;  /* UplinkUEAssociatedLPPaTransport */
static int hf_s1ap_DownlinkNonUEAssociatedLPPaTransport_PDU = -1;  /* DownlinkNonUEAssociatedLPPaTransport */
static int hf_s1ap_UplinkNonUEAssociatedLPPaTransport_PDU = -1;  /* UplinkNonUEAssociatedLPPaTransport */
static int hf_s1ap_E_RABModificationIndication_PDU = -1;  /* E_RABModificationIndication */
static int hf_s1ap_E_RABToBeModifiedListBearerModInd_PDU = -1;  /* E_RABToBeModifiedListBearerModInd */
static int hf_s1ap_E_RABToBeModifiedItemBearerModInd_PDU = -1;  /* E_RABToBeModifiedItemBearerModInd */
static int hf_s1ap_E_RABNotToBeModifiedListBearerModInd_PDU = -1;  /* E_RABNotToBeModifiedListBearerModInd */
static int hf_s1ap_E_RABNotToBeModifiedItemBearerModInd_PDU = -1;  /* E_RABNotToBeModifiedItemBearerModInd */
static int hf_s1ap_CSGMembershipInfo_PDU = -1;    /* CSGMembershipInfo */
static int hf_s1ap_E_RABModificationConfirm_PDU = -1;  /* E_RABModificationConfirm */
static int hf_s1ap_E_RABModifyListBearerModConf_PDU = -1;  /* E_RABModifyListBearerModConf */
static int hf_s1ap_E_RABModifyItemBearerModConf_PDU = -1;  /* E_RABModifyItemBearerModConf */
static int hf_s1ap_UEContextModificationIndication_PDU = -1;  /* UEContextModificationIndication */
static int hf_s1ap_UEContextModificationConfirm_PDU = -1;  /* UEContextModificationConfirm */
static int hf_s1ap_UEContextSuspendRequest_PDU = -1;  /* UEContextSuspendRequest */
static int hf_s1ap_UEContextSuspendResponse_PDU = -1;  /* UEContextSuspendResponse */
static int hf_s1ap_UEContextResumeRequest_PDU = -1;  /* UEContextResumeRequest */
static int hf_s1ap_E_RABFailedToResumeListResumeReq_PDU = -1;  /* E_RABFailedToResumeListResumeReq */
static int hf_s1ap_E_RABFailedToResumeItemResumeReq_PDU = -1;  /* E_RABFailedToResumeItemResumeReq */
static int hf_s1ap_UEContextResumeResponse_PDU = -1;  /* UEContextResumeResponse */
static int hf_s1ap_E_RABFailedToResumeListResumeRes_PDU = -1;  /* E_RABFailedToResumeListResumeRes */
static int hf_s1ap_E_RABFailedToResumeItemResumeRes_PDU = -1;  /* E_RABFailedToResumeItemResumeRes */
static int hf_s1ap_UEContextResumeFailure_PDU = -1;  /* UEContextResumeFailure */
static int hf_s1ap_ConnectionEstablishmentIndication_PDU = -1;  /* ConnectionEstablishmentIndication */
static int hf_s1ap_RetrieveUEInformation_PDU = -1;  /* RetrieveUEInformation */
static int hf_s1ap_UEInformationTransfer_PDU = -1;  /* UEInformationTransfer */
static int hf_s1ap_ENBCPRelocationIndication_PDU = -1;  /* ENBCPRelocationIndication */
static int hf_s1ap_MMECPRelocationIndication_PDU = -1;  /* MMECPRelocationIndication */
static int hf_s1ap_SecondaryRATDataUsageReport_PDU = -1;  /* SecondaryRATDataUsageReport */
static int hf_s1ap_UERadioCapabilityIDMappingRequest_PDU = -1;  /* UERadioCapabilityIDMappingRequest */
static int hf_s1ap_UERadioCapabilityIDMappingResponse_PDU = -1;  /* UERadioCapabilityIDMappingResponse */
static int hf_s1ap_S1AP_PDU_PDU = -1;             /* S1AP_PDU */
static int hf_s1ap_s1ap_SONtransferApplicationIdentity_PDU = -1;  /* SONtransferApplicationIdentity */
static int hf_s1ap_s1ap_SONtransferRequestContainer_PDU = -1;  /* SONtransferRequestContainer */
static int hf_s1ap_s1ap_SONtransferResponseContainer_PDU = -1;  /* SONtransferResponseContainer */
static int hf_s1ap_s1ap_SONtransferCause_PDU = -1;  /* SONtransferCause */
static int hf_s1ap_local = -1;                    /* INTEGER_0_65535 */
static int hf_s1ap_global = -1;                   /* T_global */
static int hf_s1ap_ProtocolIE_Container_item = -1;  /* ProtocolIE_Field */
static int hf_s1ap_id = -1;                       /* ProtocolIE_ID */
static int hf_s1ap_criticality = -1;              /* Criticality */
static int hf_s1ap_ie_field_value = -1;           /* T_ie_field_value */
static int hf_s1ap_ProtocolIE_ContainerList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_ProtocolExtensionContainer_item = -1;  /* ProtocolExtensionField */
static int hf_s1ap_ext_id = -1;                   /* ProtocolExtensionID */
static int hf_s1ap_extensionValue = -1;           /* T_extensionValue */
static int hf_s1ap_PrivateIE_Container_item = -1;  /* PrivateIE_Field */
static int hf_s1ap_private_id = -1;               /* PrivateIE_ID */
static int hf_s1ap_value = -1;                    /* T_value */
static int hf_s1ap_gUMMEI = -1;                   /* GUMMEI */
static int hf_s1ap_m_TMSI = -1;                   /* M_TMSI */
static int hf_s1ap_iE_Extensions = -1;            /* ProtocolExtensionContainer */
static int hf_s1ap_cellBased = -1;                /* CellBasedMDT */
static int hf_s1ap_tABased = -1;                  /* TABasedMDT */
static int hf_s1ap_pLMNWide = -1;                 /* NULL */
static int hf_s1ap_tAIBased = -1;                 /* TAIBasedMDT */
static int hf_s1ap_cellBased_01 = -1;             /* CellBasedQMC */
static int hf_s1ap_tABased_01 = -1;               /* TABasedQMC */
static int hf_s1ap_tAIBased_01 = -1;              /* TAIBasedQMC */
static int hf_s1ap_pLMNAreaBased = -1;            /* PLMNAreaBasedQMC */
static int hf_s1ap_priorityLevel = -1;            /* PriorityLevel */
static int hf_s1ap_pre_emptionCapability = -1;    /* Pre_emptionCapability */
static int hf_s1ap_pre_emptionVulnerability = -1;  /* Pre_emptionVulnerability */
static int hf_s1ap_cellIdentifierAndCELevelForCECapableUEs = -1;  /* CellIdentifierAndCELevelForCECapableUEs */
static int hf_s1ap_assistanceDataForRecommendedCells = -1;  /* AssistanceDataForRecommendedCells */
static int hf_s1ap_assistanceDataForCECapableUEs = -1;  /* AssistanceDataForCECapableUEs */
static int hf_s1ap_pagingAttemptInformation = -1;  /* PagingAttemptInformation */
static int hf_s1ap_recommendedCellsForPaging = -1;  /* RecommendedCellsForPaging */
static int hf_s1ap_Bearers_SubjectToStatusTransferList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_e_RAB_ID = -1;                 /* E_RAB_ID */
static int hf_s1ap_uL_COUNTvalue = -1;            /* COUNTvalue */
static int hf_s1ap_dL_COUNTvalue = -1;            /* COUNTvalue */
static int hf_s1ap_receiveStatusofULPDCPSDUs = -1;  /* ReceiveStatusofULPDCPSDUs */
static int hf_s1ap_Bearers_SubjectToEarlyStatusTransferList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_dLCOUNT_PDCP_SNlength = -1;    /* DLCOUNT_PDCP_SNlength */
static int hf_s1ap_bluetoothMeasConfig = -1;      /* BluetoothMeasConfig */
static int hf_s1ap_bluetoothMeasConfigNameList = -1;  /* BluetoothMeasConfigNameList */
static int hf_s1ap_bt_rssi = -1;                  /* T_bt_rssi */
static int hf_s1ap_BluetoothMeasConfigNameList_item = -1;  /* BluetoothName */
static int hf_s1ap_BPLMNs_item = -1;              /* PLMNidentity */
static int hf_s1ap_cellID_Cancelled = -1;         /* CellID_Cancelled */
static int hf_s1ap_tAI_Cancelled = -1;            /* TAI_Cancelled */
static int hf_s1ap_emergencyAreaID_Cancelled = -1;  /* EmergencyAreaID_Cancelled */
static int hf_s1ap_cellID_Broadcast = -1;         /* CellID_Broadcast */
static int hf_s1ap_tAI_Broadcast = -1;            /* TAI_Broadcast */
static int hf_s1ap_emergencyAreaID_Broadcast = -1;  /* EmergencyAreaID_Broadcast */
static int hf_s1ap_CancelledCellinEAI_item = -1;  /* CancelledCellinEAI_Item */
static int hf_s1ap_eCGI = -1;                     /* EUTRAN_CGI */
static int hf_s1ap_numberOfBroadcasts = -1;       /* NumberOfBroadcasts */
static int hf_s1ap_CancelledCellinTAI_item = -1;  /* CancelledCellinTAI_Item */
static int hf_s1ap_radioNetwork = -1;             /* CauseRadioNetwork */
static int hf_s1ap_transport = -1;                /* CauseTransport */
static int hf_s1ap_nas = -1;                      /* CauseNas */
static int hf_s1ap_protocol = -1;                 /* CauseProtocol */
static int hf_s1ap_misc = -1;                     /* CauseMisc */
static int hf_s1ap_global_Cell_ID = -1;           /* EUTRAN_CGI */
static int hf_s1ap_cELevel = -1;                  /* CELevel */
static int hf_s1ap_CellID_Broadcast_item = -1;    /* CellID_Broadcast_Item */
static int hf_s1ap_CellID_Cancelled_item = -1;    /* CellID_Cancelled_Item */
static int hf_s1ap_cellIdListforMDT = -1;         /* CellIdListforMDT */
static int hf_s1ap_CellIdListforMDT_item = -1;    /* EUTRAN_CGI */
static int hf_s1ap_cellIdListforQMC = -1;         /* CellIdListforQMC */
static int hf_s1ap_CellIdListforQMC_item = -1;    /* EUTRAN_CGI */
static int hf_s1ap_cdma2000OneXMEID = -1;         /* Cdma2000OneXMEID */
static int hf_s1ap_cdma2000OneXMSI = -1;          /* Cdma2000OneXMSI */
static int hf_s1ap_cdma2000OneXPilot = -1;        /* Cdma2000OneXPilot */
static int hf_s1ap_cell_Size = -1;                /* Cell_Size */
static int hf_s1ap_pLMNidentity = -1;             /* PLMNidentity */
static int hf_s1ap_lAC = -1;                      /* LAC */
static int hf_s1ap_cI = -1;                       /* CI */
static int hf_s1ap_rAC = -1;                      /* RAC */
static int hf_s1ap_CNTypeRestrictions_item = -1;  /* CNTypeRestrictions_Item */
static int hf_s1ap_pLMN_Identity = -1;            /* PLMNidentity */
static int hf_s1ap_cNType = -1;                   /* CNType */
static int hf_s1ap_ConnectedengNBList_item = -1;  /* ConnectedengNBItem */
static int hf_s1ap_en_gNB_ID = -1;                /* En_gNB_ID */
static int hf_s1ap_supportedTAs = -1;             /* SupportedTAs */
static int hf_s1ap_sourceNG_RAN_node_ID = -1;     /* Global_RAN_NODE_ID */
static int hf_s1ap_rAN_UE_NGAP_ID = -1;           /* RAN_UE_NGAP_ID */
static int hf_s1ap_CSG_IdList_item = -1;          /* CSG_IdList_Item */
static int hf_s1ap_cSG_Id = -1;                   /* CSG_Id */
static int hf_s1ap_pDCP_SN = -1;                  /* PDCP_SN */
static int hf_s1ap_hFN = -1;                      /* HFN */
static int hf_s1ap_pDCP_SNExtended = -1;          /* PDCP_SNExtended */
static int hf_s1ap_hFNModified = -1;              /* HFNModified */
static int hf_s1ap_pDCP_SNlength18 = -1;          /* PDCP_SNlength18 */
static int hf_s1ap_hFNforPDCP_SNlength18 = -1;    /* HFNforPDCP_SNlength18 */
static int hf_s1ap_procedureCode = -1;            /* ProcedureCode */
static int hf_s1ap_triggeringMessage = -1;        /* TriggeringMessage */
static int hf_s1ap_procedureCriticality = -1;     /* Criticality */
static int hf_s1ap_iEsCriticalityDiagnostics = -1;  /* CriticalityDiagnostics_IE_List */
static int hf_s1ap_CriticalityDiagnostics_IE_List_item = -1;  /* CriticalityDiagnostics_IE_Item */
static int hf_s1ap_iECriticality = -1;            /* Criticality */
static int hf_s1ap_iE_ID = -1;                    /* ProtocolIE_ID */
static int hf_s1ap_typeOfError = -1;              /* TypeOfError */
static int hf_s1ap_dAPSIndicator = -1;            /* T_dAPSIndicator */
static int hf_s1ap_DAPSResponseInfoList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_dAPSResponseInfo = -1;         /* DAPSResponseInfo */
static int hf_s1ap_dapsresponseindicator = -1;    /* T_dapsresponseindicator */
static int hf_s1ap_ServedDCNs_item = -1;          /* ServedDCNsItem */
static int hf_s1ap_dCN_ID = -1;                   /* DCN_ID */
static int hf_s1ap_relativeDCNCapacity = -1;      /* RelativeMMECapacity */
static int hf_s1ap_dl_NAS_MAC = -1;               /* DL_NAS_MAC */
static int hf_s1ap_dLCOUNTValuePDCP_SNlength12 = -1;  /* COUNTvalue */
static int hf_s1ap_dLCOUNTValuePDCP_SNlength15 = -1;  /* COUNTValueExtended */
static int hf_s1ap_dLCOUNTValuePDCP_SNlength18 = -1;  /* COUNTvaluePDCP_SNlength18 */
static int hf_s1ap_ECGIList_item = -1;            /* EUTRAN_CGI */
static int hf_s1ap_PWSfailedECGIList_item = -1;   /* EUTRAN_CGI */
static int hf_s1ap_EmergencyAreaIDList_item = -1;  /* EmergencyAreaID */
static int hf_s1ap_EmergencyAreaID_Broadcast_item = -1;  /* EmergencyAreaID_Broadcast_Item */
static int hf_s1ap_emergencyAreaID = -1;          /* EmergencyAreaID */
static int hf_s1ap_completedCellinEAI = -1;       /* CompletedCellinEAI */
static int hf_s1ap_EmergencyAreaID_Cancelled_item = -1;  /* EmergencyAreaID_Cancelled_Item */
static int hf_s1ap_cancelledCellinEAI = -1;       /* CancelledCellinEAI */
static int hf_s1ap_CompletedCellinEAI_item = -1;  /* CompletedCellinEAI_Item */
static int hf_s1ap_ECGI_List_item = -1;           /* EUTRAN_CGI */
static int hf_s1ap_EmergencyAreaIDListForRestart_item = -1;  /* EmergencyAreaID */
static int hf_s1ap_bearers_SubjectToEarlyStatusTransferList = -1;  /* Bearers_SubjectToEarlyStatusTransferList */
static int hf_s1ap_macroENB_ID = -1;              /* BIT_STRING_SIZE_20 */
static int hf_s1ap_homeENB_ID = -1;               /* BIT_STRING_SIZE_28 */
static int hf_s1ap_short_macroENB_ID = -1;        /* BIT_STRING_SIZE_18 */
static int hf_s1ap_long_macroENB_ID = -1;         /* BIT_STRING_SIZE_21 */
static int hf_s1ap_lAI = -1;                      /* LAI */
static int hf_s1ap_eNB_ID = -1;                   /* ENB_ID */
static int hf_s1ap_GUMMEIList_item = -1;          /* GUMMEI */
static int hf_s1ap_bearers_SubjectToStatusTransferList = -1;  /* Bearers_SubjectToStatusTransferList */
static int hf_s1ap_ENBX2TLAs_item = -1;           /* TransportLayerAddress */
static int hf_s1ap_transfertype = -1;             /* EN_DCSONTransferType */
static int hf_s1ap_sONInformation = -1;           /* SONInformation */
static int hf_s1ap_x2TNLConfigInfo = -1;          /* X2TNLConfigurationInfo */
static int hf_s1ap_request = -1;                  /* EN_DCTransferTypeRequest */
static int hf_s1ap_reply = -1;                    /* EN_DCTransferTypeReply */
static int hf_s1ap_sourceeNB = -1;                /* EN_DCSONeNBIdentification */
static int hf_s1ap_targetengNB = -1;              /* EN_DCSONengNBIdentification */
static int hf_s1ap_targeteNB = -1;                /* EN_DCSONeNBIdentification */
static int hf_s1ap_associatedTAI = -1;            /* TAI */
static int hf_s1ap_broadcast5GSTAI = -1;          /* FiveGSTAI */
static int hf_s1ap_sourceengNB = -1;              /* EN_DCSONengNBIdentification */
static int hf_s1ap_globaleNBID = -1;              /* Global_ENB_ID */
static int hf_s1ap_selectedTAI = -1;              /* TAI */
static int hf_s1ap_globalengNBID = -1;            /* Global_en_gNB_ID */
static int hf_s1ap_EPLMNs_item = -1;              /* PLMNidentity */
static int hf_s1ap_E_RABInformationList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_dL_Forwarding = -1;            /* DL_Forwarding */
static int hf_s1ap_E_RABList_item = -1;           /* ProtocolIE_SingleContainer */
static int hf_s1ap_cause = -1;                    /* Cause */
static int hf_s1ap_qCI = -1;                      /* QCI */
static int hf_s1ap_allocationRetentionPriority = -1;  /* AllocationAndRetentionPriority */
static int hf_s1ap_gbrQosInformation = -1;        /* GBR_QosInformation */
static int hf_s1ap_E_RABUsageReportList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_startTimestamp = -1;           /* T_startTimestamp */
static int hf_s1ap_endTimestamp = -1;             /* T_endTimestamp */
static int hf_s1ap_usageCountUL = -1;             /* INTEGER_0_18446744073709551615 */
static int hf_s1ap_usageCountDL = -1;             /* INTEGER_0_18446744073709551615 */
static int hf_s1ap_cell_ID = -1;                  /* CellIdentity */
static int hf_s1ap_expectedActivity = -1;         /* ExpectedUEActivityBehaviour */
static int hf_s1ap_expectedHOInterval = -1;       /* ExpectedHOInterval */
static int hf_s1ap_expectedActivityPeriod = -1;   /* ExpectedActivityPeriod */
static int hf_s1ap_expectedIdlePeriod = -1;       /* ExpectedIdlePeriod */
static int hf_s1ap_sourceofUEActivityBehaviourInformation = -1;  /* SourceOfUEActivityBehaviourInformation */
static int hf_s1ap_fiveGSTAC = -1;                /* FiveGSTAC */
static int hf_s1ap_ForbiddenTAs_item = -1;        /* ForbiddenTAs_Item */
static int hf_s1ap_forbiddenTACs = -1;            /* ForbiddenTACs */
static int hf_s1ap_ForbiddenTACs_item = -1;       /* TAC */
static int hf_s1ap_ForbiddenLAs_item = -1;        /* ForbiddenLAs_Item */
static int hf_s1ap_forbiddenLACs = -1;            /* ForbiddenLACs */
static int hf_s1ap_ForbiddenLACs_item = -1;       /* LAC */
static int hf_s1ap_e_RAB_MaximumBitrateDL = -1;   /* BitRate */
static int hf_s1ap_e_RAB_MaximumBitrateUL = -1;   /* BitRate */
static int hf_s1ap_e_RAB_GuaranteedBitrateDL = -1;  /* BitRate */
static int hf_s1ap_e_RAB_GuaranteedBitrateUL = -1;  /* BitRate */
static int hf_s1ap_mME_Group_ID = -1;             /* MME_Group_ID */
static int hf_s1ap_mME_Code = -1;                 /* MME_Code */
static int hf_s1ap_servingPLMN = -1;              /* PLMNidentity */
static int hf_s1ap_equivalentPLMNs = -1;          /* EPLMNs */
static int hf_s1ap_forbiddenTAs = -1;             /* ForbiddenTAs */
static int hf_s1ap_forbiddenLAs = -1;             /* ForbiddenLAs */
static int hf_s1ap_forbiddenInterRATs = -1;       /* ForbiddenInterRATs */
static int hf_s1ap_measurementsToActivate = -1;   /* MeasurementsToActivate */
static int hf_s1ap_m1reportingTrigger = -1;       /* M1ReportingTrigger */
static int hf_s1ap_m1thresholdeventA2 = -1;       /* M1ThresholdEventA2 */
static int hf_s1ap_m1periodicReporting = -1;      /* M1PeriodicReporting */
static int hf_s1ap_recommendENBsForPaging = -1;   /* RecommendedENBsForPaging */
static int hf_s1ap_rSRP = -1;                     /* INTEGER_0_127 */
static int hf_s1ap_rSRQ = -1;                     /* INTEGER_0_127 */
static int hf_s1ap_sINR = -1;                     /* INTEGER_0_127 */
static int hf_s1ap_interSystemMeasurementParameters = -1;  /* InterSystemMeasurementParameters */
static int hf_s1ap_measurementDuration = -1;      /* INTEGER_1_100 */
static int hf_s1ap_interSystemMeasurementList = -1;  /* InterSystemMeasurementList */
static int hf_s1ap_InterSystemMeasurementList_item = -1;  /* InterSystemMeasurementItem */
static int hf_s1ap_freqBandIndicatorNR = -1;      /* INTEGER_1_1024 */
static int hf_s1ap_sSBfrequencies = -1;           /* INTEGER_0_maxNARFCN */
static int hf_s1ap_subcarrierSpacingSSB = -1;     /* T_subcarrierSpacingSSB */
static int hf_s1ap_maxRSIndexCellQual = -1;       /* INTEGER_1_maxRS_IndexCellQual */
static int hf_s1ap_sMTC = -1;                     /* T_sMTC */
static int hf_s1ap_threshRS_Index_r15 = -1;       /* T_threshRS_Index_r15 */
static int hf_s1ap_sSBToMeasure = -1;             /* T_sSBToMeasure */
static int hf_s1ap_sSRSSIMeasurement = -1;        /* T_sSRSSIMeasurement */
static int hf_s1ap_quantityConfigNR_R15 = -1;     /* T_quantityConfigNR_R15 */
static int hf_s1ap_blackCellsToAddModList = -1;   /* T_blackCellsToAddModList */
static int hf_s1ap_e_UTRAN_Cell = -1;             /* LastVisitedEUTRANCellInformation */
static int hf_s1ap_uTRAN_Cell = -1;               /* LastVisitedUTRANCellInformation */
static int hf_s1ap_gERAN_Cell = -1;               /* LastVisitedGERANCellInformation */
static int hf_s1ap_nG_RAN_Cell = -1;              /* LastVisitedNGRANCellInformation */
static int hf_s1ap_cellType = -1;                 /* CellType */
static int hf_s1ap_time_UE_StayedInCell = -1;     /* Time_UE_StayedInCell */
static int hf_s1ap_undefined = -1;                /* NULL */
static int hf_s1ap_pattern_period = -1;           /* T_pattern_period */
static int hf_s1ap_pattern_offset = -1;           /* INTEGER_0_10239_ */
static int hf_s1ap_loggingInterval = -1;          /* LoggingInterval */
static int hf_s1ap_loggingDuration = -1;          /* LoggingDuration */
static int hf_s1ap_mBSFN_ResultToLog = -1;        /* MBSFN_ResultToLog */
static int hf_s1ap_m3period = -1;                 /* M3period */
static int hf_s1ap_m4period = -1;                 /* M4period */
static int hf_s1ap_m4_links_to_log = -1;          /* Links_to_log */
static int hf_s1ap_m5period = -1;                 /* M5period */
static int hf_s1ap_m5_links_to_log = -1;          /* Links_to_log */
static int hf_s1ap_m6report_Interval = -1;        /* M6report_Interval */
static int hf_s1ap_m6delay_threshold = -1;        /* M6delay_threshold */
static int hf_s1ap_m6_links_to_log = -1;          /* Links_to_log */
static int hf_s1ap_m7period = -1;                 /* M7period */
static int hf_s1ap_m7_links_to_log = -1;          /* Links_to_log */
static int hf_s1ap_mdt_Activation = -1;           /* MDT_Activation */
static int hf_s1ap_areaScopeOfMDT = -1;           /* AreaScopeOfMDT */
static int hf_s1ap_mDTMode = -1;                  /* MDTMode */
static int hf_s1ap_MBSFN_ResultToLog_item = -1;   /* MBSFN_ResultToLogInfo */
static int hf_s1ap_mBSFN_AreaId = -1;             /* INTEGER_0_255 */
static int hf_s1ap_carrierFreq = -1;              /* EARFCN */
static int hf_s1ap_MDTPLMNList_item = -1;         /* PLMNidentity */
static int hf_s1ap_immediateMDT = -1;             /* ImmediateMDT */
static int hf_s1ap_loggedMDT = -1;                /* LoggedMDT */
static int hf_s1ap_mDTMode_Extension = -1;        /* MDTMode_Extension */
static int hf_s1ap_threshold_RSRP = -1;           /* Threshold_RSRP */
static int hf_s1ap_threshold_RSRQ = -1;           /* Threshold_RSRQ */
static int hf_s1ap_global_ENB_ID = -1;            /* Global_ENB_ID */
static int hf_s1ap_tAI = -1;                      /* TAI */
static int hf_s1ap_muting_pattern_period = -1;    /* T_muting_pattern_period */
static int hf_s1ap_muting_pattern_offset = -1;    /* INTEGER_0_10239_ */
static int hf_s1ap_nB_IoT_paging_eDRX_Cycle = -1;  /* NB_IoT_Paging_eDRX_Cycle */
static int hf_s1ap_nB_IoT_pagingTimeWindow = -1;  /* NB_IoT_PagingTimeWindow */
static int hf_s1ap_pLMNIdentity = -1;             /* PLMNidentity */
static int hf_s1ap_nRCellIdentity = -1;           /* NRCellIdentity */
static int hf_s1ap_nRencryptionAlgorithms = -1;   /* NRencryptionAlgorithms */
static int hf_s1ap_nRintegrityProtectionAlgorithms = -1;  /* NRintegrityProtectionAlgorithms */
static int hf_s1ap_vehicleUE = -1;                /* VehicleUE */
static int hf_s1ap_pedestrianUE = -1;             /* PedestrianUE */
static int hf_s1ap_uEaggregateMaximumBitRate = -1;  /* BitRate */
static int hf_s1ap_overloadAction = -1;           /* OverloadAction */
static int hf_s1ap_pagingAttemptCount = -1;       /* PagingAttemptCount */
static int hf_s1ap_intendedNumberOfPagingAttempts = -1;  /* IntendedNumberOfPagingAttempts */
static int hf_s1ap_nextPagingAreaScope = -1;      /* NextPagingAreaScope */
static int hf_s1ap_paging_eDRX_Cycle = -1;        /* Paging_eDRX_Cycle */
static int hf_s1ap_pagingTimeWindow = -1;         /* PagingTimeWindow */
static int hf_s1ap_pc5QoSFlowList = -1;           /* PC5QoSFlowList */
static int hf_s1ap_pc5LinkAggregatedBitRates = -1;  /* BitRate */
static int hf_s1ap_PC5QoSFlowList_item = -1;      /* PC5QoSFlowItem */
static int hf_s1ap_pQI = -1;                      /* FiveQI */
static int hf_s1ap_pc5FlowBitRates = -1;          /* PC5FlowBitRates */
static int hf_s1ap_range = -1;                    /* Range */
static int hf_s1ap_guaranteedFlowBitRate = -1;    /* BitRate */
static int hf_s1ap_maximumFlowBitRate = -1;       /* BitRate */
static int hf_s1ap_reportInterval = -1;           /* ReportIntervalMDT */
static int hf_s1ap_reportAmount = -1;             /* ReportAmountMDT */
static int hf_s1ap_plmnListforQMC = -1;           /* PLMNListforQMC */
static int hf_s1ap_PLMNListforQMC_item = -1;      /* PLMNidentity */
static int hf_s1ap_proSeDirectDiscovery = -1;     /* ProSeDirectDiscovery */
static int hf_s1ap_proSeDirectCommunication = -1;  /* ProSeDirectCommunication */
static int hf_s1ap_nCGI = -1;                     /* NR_CGI */
static int hf_s1ap_recommendedCellList = -1;      /* RecommendedCellList */
static int hf_s1ap_RecommendedCellList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_eUTRAN_CGI = -1;               /* EUTRAN_CGI */
static int hf_s1ap_timeStayedInCell = -1;         /* INTEGER_0_4095 */
static int hf_s1ap_recommendedENBList = -1;       /* RecommendedENBList */
static int hf_s1ap_RecommendedENBList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_mMEPagingTarget = -1;          /* MMEPagingTarget */
static int hf_s1ap_eventType = -1;                /* EventType */
static int hf_s1ap_reportArea = -1;               /* ReportArea */
static int hf_s1ap_rIMInformation = -1;           /* RIMInformation */
static int hf_s1ap_rIMRoutingAddress = -1;        /* RIMRoutingAddress */
static int hf_s1ap_gERAN_Cell_ID = -1;            /* GERAN_Cell_ID */
static int hf_s1ap_targetRNC_ID = -1;             /* TargetRNC_ID */
static int hf_s1ap_eHRPD_Sector_ID = -1;          /* OCTET_STRING_SIZE_16 */
static int hf_s1ap_uE_RLF_Report_Container = -1;  /* UE_RLF_Report_Container */
static int hf_s1ap_uE_RLF_Report_Container_for_extended_bands = -1;  /* UE_RLF_Report_Container_for_extended_bands */
static int hf_s1ap_ECGIListForRestart_item = -1;  /* EUTRAN_CGI */
static int hf_s1ap_nextHopChainingCount = -1;     /* INTEGER_0_7 */
static int hf_s1ap_nextHopParameter = -1;         /* SecurityKey */
static int hf_s1ap_SecondaryRATDataUsageReportList_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_secondaryRATType = -1;         /* SecondaryRATType */
static int hf_s1ap_e_RABUsageReportList = -1;     /* E_RABUsageReportList */
static int hf_s1ap_sONInformationRequest = -1;    /* SONInformationRequest */
static int hf_s1ap_sONInformationReply = -1;      /* SONInformationReply */
static int hf_s1ap_sONInformation_Extension = -1;  /* SONInformation_Extension */
static int hf_s1ap_x2TNLConfigurationInfo = -1;   /* X2TNLConfigurationInfo */
static int hf_s1ap_rLFReportInformation = -1;     /* RLFReportInformation */
static int hf_s1ap_targeteNB_ID = -1;             /* TargeteNB_ID */
static int hf_s1ap_sourceeNB_ID = -1;             /* SourceeNB_ID */
static int hf_s1ap_sourceStratumLevel = -1;       /* StratumLevel */
static int hf_s1ap_listeningSubframePattern = -1;  /* ListeningSubframePattern */
static int hf_s1ap_aggressoreCGI_List = -1;       /* ECGI_List */
static int hf_s1ap_selected_TAI = -1;             /* TAI */
static int hf_s1ap_sourceNgRanNode_ID = -1;       /* SourceNgRanNode_ID */
static int hf_s1ap_sourceNodeID_Extension = -1;   /* SourceNodeID_Extension */
static int hf_s1ap_rRC_Container = -1;            /* RRC_Container */
static int hf_s1ap_e_RABInformationList = -1;     /* E_RABInformationList */
static int hf_s1ap_targetCell_ID = -1;            /* EUTRAN_CGI */
static int hf_s1ap_subscriberProfileIDforRFP = -1;  /* SubscriberProfileIDforRFP */
static int hf_s1ap_uE_HistoryInformation = -1;    /* UE_HistoryInformation */
static int hf_s1ap_global_RAN_NODE_ID = -1;       /* Global_RAN_NODE_ID */
static int hf_s1ap_selected_TAI_01 = -1;          /* FiveGSTAI */
static int hf_s1ap_ServedGUMMEIs_item = -1;       /* ServedGUMMEIsItem */
static int hf_s1ap_servedPLMNs = -1;              /* ServedPLMNs */
static int hf_s1ap_servedGroupIDs = -1;           /* ServedGroupIDs */
static int hf_s1ap_servedMMECs = -1;              /* ServedMMECs */
static int hf_s1ap_ServedGroupIDs_item = -1;      /* MME_Group_ID */
static int hf_s1ap_ServedMMECs_item = -1;         /* MME_Code */
static int hf_s1ap_ServedPLMNs_item = -1;         /* PLMNidentity */
static int hf_s1ap_periodicCommunicationIndicator = -1;  /* T_periodicCommunicationIndicator */
static int hf_s1ap_periodicTime = -1;             /* INTEGER_1_3600_ */
static int hf_s1ap_scheduledCommunicationTime = -1;  /* ScheduledCommunicationTime */
static int hf_s1ap_stationaryIndication = -1;     /* T_stationaryIndication */
static int hf_s1ap_trafficProfile = -1;           /* T_trafficProfile */
static int hf_s1ap_batteryIndication = -1;        /* T_batteryIndication */
static int hf_s1ap_dayofWeek = -1;                /* BIT_STRING_SIZE_7 */
static int hf_s1ap_timeofDayStart = -1;           /* INTEGER_0_86399_ */
static int hf_s1ap_timeofDayEnd = -1;             /* INTEGER_0_86399_ */
static int hf_s1ap_SupportedTAs_item = -1;        /* SupportedTAs_Item */
static int hf_s1ap_tAC = -1;                      /* TAC */
static int hf_s1ap_broadcastPLMNs = -1;           /* BPLMNs */
static int hf_s1ap_stratumLevel = -1;             /* StratumLevel */
static int hf_s1ap_synchronisationStatus = -1;    /* SynchronisationStatus */
static int hf_s1ap_mMEC = -1;                     /* MME_Code */
static int hf_s1ap_tAIListforMDT = -1;            /* TAIListforMDT */
static int hf_s1ap_TAIListforMDT_item = -1;       /* TAI */
static int hf_s1ap_TAIListforWarning_item = -1;   /* TAI */
static int hf_s1ap_TAI_Broadcast_item = -1;       /* TAI_Broadcast_Item */
static int hf_s1ap_completedCellinTAI = -1;       /* CompletedCellinTAI */
static int hf_s1ap_TAI_Cancelled_item = -1;       /* TAI_Cancelled_Item */
static int hf_s1ap_cancelledCellinTAI = -1;       /* CancelledCellinTAI */
static int hf_s1ap_tAListforMDT = -1;             /* TAListforMDT */
static int hf_s1ap_TAListforMDT_item = -1;        /* TAC */
static int hf_s1ap_tAListforQMC = -1;             /* TAListforQMC */
static int hf_s1ap_TAListforQMC_item = -1;        /* TAC */
static int hf_s1ap_tAIListforQMC = -1;            /* TAIListforQMC */
static int hf_s1ap_TAIListforQMC_item = -1;       /* TAI */
static int hf_s1ap_CompletedCellinTAI_item = -1;  /* CompletedCellinTAI_Item */
static int hf_s1ap_cGI = -1;                      /* CGI */
static int hf_s1ap_targetgNgRanNode_ID = -1;      /* TargetNgRanNode_ID */
static int hf_s1ap_rNC_ID = -1;                   /* RNC_ID */
static int hf_s1ap_extendedRNC_ID = -1;           /* ExtendedRNC_ID */
static int hf_s1ap_gNB = -1;                      /* GNB */
static int hf_s1ap_ng_eNB = -1;                   /* NG_eNB */
static int hf_s1ap_global_gNB_ID = -1;            /* Global_GNB_ID */
static int hf_s1ap_gNB_ID = -1;                   /* GNB_Identity */
static int hf_s1ap_gNB_ID_01 = -1;                /* GNB_ID */
static int hf_s1ap_global_ng_eNB_ID = -1;         /* Global_ENB_ID */
static int hf_s1ap_measurementThreshold = -1;     /* MeasurementThresholdA2 */
static int hf_s1ap_transportLayerAddress = -1;    /* TransportLayerAddress */
static int hf_s1ap_uL_GTP_TEID = -1;              /* GTP_TEID */
static int hf_s1ap_e_UTRAN_Trace_ID = -1;         /* E_UTRAN_Trace_ID */
static int hf_s1ap_interfacesToTrace = -1;        /* InterfacesToTrace */
static int hf_s1ap_traceDepth = -1;               /* TraceDepth */
static int hf_s1ap_traceCollectionEntityIPAddress = -1;  /* TransportLayerAddress */
static int hf_s1ap_uDP_Port_Number = -1;          /* Port_Number */
static int hf_s1ap_TAIListForRestart_item = -1;   /* TAI */
static int hf_s1ap_uEaggregateMaximumBitRateDL = -1;  /* BitRate */
static int hf_s1ap_uEaggregateMaximumBitRateUL = -1;  /* BitRate */
static int hf_s1ap_containerForAppLayerMeasConfig = -1;  /* OCTET_STRING_SIZE_1_1000 */
static int hf_s1ap_areaScopeOfQMC = -1;           /* AreaScopeOfQMC */
static int hf_s1ap_uE_S1AP_ID_pair = -1;          /* UE_S1AP_ID_pair */
static int hf_s1ap_mME_UE_S1AP_ID = -1;           /* MME_UE_S1AP_ID */
static int hf_s1ap_eNB_UE_S1AP_ID = -1;           /* ENB_UE_S1AP_ID */
static int hf_s1ap_UE_HistoryInformation_item = -1;  /* LastVisitedCell_Item */
static int hf_s1ap_s_TMSI = -1;                   /* S_TMSI */
static int hf_s1ap_iMSI = -1;                     /* IMSI */
static int hf_s1ap_encryptionAlgorithms = -1;     /* EncryptionAlgorithms */
static int hf_s1ap_integrityProtectionAlgorithms = -1;  /* IntegrityProtectionAlgorithms */
static int hf_s1ap_uESidelinkAggregateMaximumBitRate = -1;  /* BitRate */
static int hf_s1ap_ul_NAS_MAC = -1;               /* UL_NAS_MAC */
static int hf_s1ap_ul_NAS_Count = -1;             /* UL_NAS_Count */
static int hf_s1ap_eutran_cgi = -1;               /* EUTRAN_CGI */
static int hf_s1ap_tai = -1;                      /* TAI */
static int hf_s1ap_cellIDList = -1;               /* ECGIList */
static int hf_s1ap_trackingAreaListforWarning = -1;  /* TAIListforWarning */
static int hf_s1ap_emergencyAreaIDList = -1;      /* EmergencyAreaIDList */
static int hf_s1ap_wlanMeasConfig = -1;           /* WLANMeasConfig */
static int hf_s1ap_wlanMeasConfigNameList = -1;   /* WLANMeasConfigNameList */
static int hf_s1ap_wlan_rssi = -1;                /* T_wlan_rssi */
static int hf_s1ap_wlan_rtt = -1;                 /* T_wlan_rtt */
static int hf_s1ap_WLANMeasConfigNameList_item = -1;  /* WLANName */
static int hf_s1ap_pagingProbabilityInformation = -1;  /* PagingProbabilityInformation */
static int hf_s1ap_eNBX2TransportLayerAddresses = -1;  /* ENBX2TLAs */
static int hf_s1ap_ENBX2ExtTLAs_item = -1;        /* ENBX2ExtTLA */
static int hf_s1ap_iPsecTLA = -1;                 /* TransportLayerAddress */
static int hf_s1ap_gTPTLAa = -1;                  /* ENBX2GTPTLAs */
static int hf_s1ap_ENBX2GTPTLAs_item = -1;        /* TransportLayerAddress */
static int hf_s1ap_ENBIndirectX2TransportLayerAddresses_item = -1;  /* TransportLayerAddress */
static int hf_s1ap_protocolIEs = -1;              /* ProtocolIE_Container */
static int hf_s1ap_dL_transportLayerAddress = -1;  /* TransportLayerAddress */
static int hf_s1ap_dL_gTP_TEID = -1;              /* GTP_TEID */
static int hf_s1ap_uL_TransportLayerAddress = -1;  /* TransportLayerAddress */
static int hf_s1ap_gTP_TEID = -1;                 /* GTP_TEID */
static int hf_s1ap_e_RABlevelQosParameters = -1;  /* E_RABLevelQoSParameters */
static int hf_s1ap_E_RABToBeSetupListBearerSUReq_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_e_RABlevelQoSParameters = -1;  /* E_RABLevelQoSParameters */
static int hf_s1ap_nAS_PDU = -1;                  /* NAS_PDU */
static int hf_s1ap_E_RABSetupListBearerSURes_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_E_RABToBeModifiedListBearerModReq_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_e_RABLevelQoSParameters = -1;  /* E_RABLevelQoSParameters */
static int hf_s1ap_E_RABModifyListBearerModRes_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_E_RABReleaseListBearerRelComp_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_E_RABToBeSetupListCtxtSUReq_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_E_RABSetupListCtxtSURes_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_TAIList_item = -1;             /* ProtocolIE_SingleContainer */
static int hf_s1ap_s1_Interface = -1;             /* ResetAll */
static int hf_s1ap_partOfS1_Interface = -1;       /* UE_associatedLogicalS1_ConnectionListRes */
static int hf_s1ap_UE_associatedLogicalS1_ConnectionListRes_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_rIMTransfer = -1;              /* RIMTransfer */
static int hf_s1ap_privateIEs = -1;               /* PrivateIE_Container */
static int hf_s1ap_dL_GTP_TEID = -1;              /* GTP_TEID */
static int hf_s1ap_cSGMembershipStatus = -1;      /* CSGMembershipStatus */
static int hf_s1ap_cellAccessMode = -1;           /* CellAccessMode */
static int hf_s1ap_E_RABModifyListBearerModConf_item = -1;  /* ProtocolIE_SingleContainer */
static int hf_s1ap_initiatingMessage = -1;        /* InitiatingMessage */
static int hf_s1ap_successfulOutcome = -1;        /* SuccessfulOutcome */
static int hf_s1ap_unsuccessfulOutcome = -1;      /* UnsuccessfulOutcome */
static int hf_s1ap_initiatingMessagevalue = -1;   /* InitiatingMessage_value */
static int hf_s1ap_successfulOutcome_value = -1;  /* SuccessfulOutcome_value */
static int hf_s1ap_unsuccessfulOutcome_value = -1;  /* UnsuccessfulOutcome_value */
static int hf_s1ap_cellLoadReporting = -1;        /* NULL */
static int hf_s1ap_multiCellLoadReporting = -1;   /* MultiCellLoadReportingRequest */
static int hf_s1ap_eventTriggeredCellLoadReporting = -1;  /* EventTriggeredCellLoadReportingRequest */
static int hf_s1ap_hOReporting = -1;              /* HOReport */
static int hf_s1ap_eutranCellActivation = -1;     /* CellActivationRequest */
static int hf_s1ap_energySavingsIndication = -1;  /* CellStateIndication */
static int hf_s1ap_failureEventReporting = -1;    /* FailureEventReport */
static int hf_s1ap_cellLoadReporting_01 = -1;     /* CellLoadReportingResponse */
static int hf_s1ap_multiCellLoadReporting_01 = -1;  /* MultiCellLoadReportingResponse */
static int hf_s1ap_eventTriggeredCellLoadReporting_01 = -1;  /* EventTriggeredCellLoadReportingResponse */
static int hf_s1ap_hOReporting_01 = -1;           /* NULL */
static int hf_s1ap_eutranCellActivation_01 = -1;  /* CellActivationResponse */
static int hf_s1ap_energySavingsIndication_01 = -1;  /* NULL */
static int hf_s1ap_failureEventReporting_01 = -1;  /* NULL */
static int hf_s1ap_cellLoadReporting_02 = -1;     /* CellLoadReportingCause */
static int hf_s1ap_multiCellLoadReporting_02 = -1;  /* CellLoadReportingCause */
static int hf_s1ap_eventTriggeredCellLoadReporting_02 = -1;  /* CellLoadReportingCause */
static int hf_s1ap_hOReporting_02 = -1;           /* HOReportingCause */
static int hf_s1ap_eutranCellActivation_02 = -1;  /* CellActivationCause */
static int hf_s1ap_energySavingsIndication_02 = -1;  /* CellStateIndicationCause */
static int hf_s1ap_failureEventReporting_02 = -1;  /* FailureEventReportingCause */
static int hf_s1ap_eUTRAN = -1;                   /* EUTRANcellLoadReportingResponse */
static int hf_s1ap_uTRAN = -1;                    /* OCTET_STRING */
static int hf_s1ap_gERAN = -1;                    /* OCTET_STRING */
static int hf_s1ap_eHRPD = -1;                    /* EHRPDSectorLoadReportingResponse */
static int hf_s1ap_compositeAvailableCapacityGroup = -1;  /* CompositeAvailableCapacityGroup */
static int hf_s1ap_cell_ID_01 = -1;               /* OCTET_STRING */
static int hf_s1ap_eUTRANcellLoadReportingResponse = -1;  /* EUTRANcellLoadReportingResponse */
static int hf_s1ap_eUTRAN_01 = -1;                /* OCTET_STRING */
static int hf_s1ap_eHRPD_01 = -1;                 /* EHRPD_Sector_ID */
static int hf_s1ap_RequestedCellList_item = -1;   /* IRAT_Cell_ID */
static int hf_s1ap_requestedCellList = -1;        /* RequestedCellList */
static int hf_s1ap_cell_ID_02 = -1;               /* IRAT_Cell_ID */
static int hf_s1ap_ReportingCellList_item = -1;   /* ReportingCellList_Item */
static int hf_s1ap_MultiCellLoadReportingResponse_item = -1;  /* MultiCellLoadReportingResponse_Item */
static int hf_s1ap_eUTRANResponse = -1;           /* EUTRANResponse */
static int hf_s1ap_uTRANResponse = -1;            /* OCTET_STRING */
static int hf_s1ap_gERANResponse = -1;            /* OCTET_STRING */
static int hf_s1ap_eHRPD_02 = -1;                 /* EHRPDMultiSectorLoadReportingResponseItem */
static int hf_s1ap_numberOfMeasurementReportingLevels = -1;  /* NumberOfMeasurementReportingLevels */
static int hf_s1ap_cellLoadReportingResponse = -1;  /* CellLoadReportingResponse */
static int hf_s1ap_overloadFlag = -1;             /* OverloadFlag */
static int hf_s1ap_hoType = -1;                   /* HoType */
static int hf_s1ap_hoReportType = -1;             /* HoReportType */
static int hf_s1ap_hosourceID = -1;               /* IRAT_Cell_ID */
static int hf_s1ap_hoTargetID = -1;               /* IRAT_Cell_ID */
static int hf_s1ap_candidateCellList = -1;        /* CandidateCellList */
static int hf_s1ap_candidatePCIList = -1;         /* CandidatePCIList */
static int hf_s1ap_CandidateCellList_item = -1;   /* IRAT_Cell_ID */
static int hf_s1ap_CandidatePCIList_item = -1;    /* CandidatePCI */
static int hf_s1ap_pCI = -1;                      /* INTEGER_0_503 */
static int hf_s1ap_eARFCN = -1;                   /* OCTET_STRING */
static int hf_s1ap_cellsToActivateList = -1;      /* CellsToActivateList */
static int hf_s1ap_minimumActivationTime = -1;    /* INTEGER_1_60 */
static int hf_s1ap_CellsToActivateList_item = -1;  /* CellsToActivateList_Item */
static int hf_s1ap_activatedCellsList = -1;       /* ActivatedCellsList */
static int hf_s1ap_ActivatedCellsList_item = -1;  /* ActivatedCellsList_Item */
static int hf_s1ap_notificationCellList = -1;     /* NotificationCellList */
static int hf_s1ap_NotificationCellList_item = -1;  /* NotificationCellList_Item */
static int hf_s1ap_notifyFlag = -1;               /* NotifyFlag */
static int hf_s1ap_tooEarlyInterRATHOReportFromEUTRAN = -1;  /* TooEarlyInterRATHOReportReportFromEUTRAN */
static int hf_s1ap_uERLFReportContainer = -1;     /* T_uERLFReportContainer */
static int hf_s1ap_mobilityInformation = -1;      /* MobilityInformation */
static int hf_s1ap_dL_EHRPD_CompositeAvailableCapacity = -1;  /* EHRPDCompositeAvailableCapacity */
static int hf_s1ap_uL_EHRPD_CompositeAvailableCapacity = -1;  /* EHRPDCompositeAvailableCapacity */
static int hf_s1ap_eHRPDSectorCapacityClassValue = -1;  /* EHRPDSectorCapacityClassValue */
static int hf_s1ap_eHRPDCapacityValue = -1;       /* EHRPDCapacityValue */
static int hf_s1ap_eHRPD_Sector_ID_01 = -1;       /* EHRPD_Sector_ID */
static int hf_s1ap_eHRPDSectorLoadReportingResponse = -1;  /* EHRPDSectorLoadReportingResponse */

/*--- End of included file: packet-s1ap-hf.c ---*/
#line 119 "./asn1/s1ap/packet-s1ap-template.c"

/* Initialize the subtree pointers */
static int ett_s1ap = -1;
static int ett_s1ap_TransportLayerAddress = -1;
static int ett_s1ap_ToTargetTransparentContainer = -1;
static int ett_s1ap_ToSourceTransparentContainer = -1;
static int ett_s1ap_RRCContainer = -1;
static int ett_s1ap_UERadioCapability = -1;
static int ett_s1ap_RIMInformation = -1;
static int ett_s1ap_Cdma2000PDU = -1;
static int ett_s1ap_Cdma2000SectorID = -1;
static int ett_s1ap_UERadioPagingInformation = -1;
static int ett_s1ap_UE_HistoryInformationFromTheUE = -1;
static int ett_s1ap_CELevel = -1;
static int ett_s1ap_UE_RLF_Report_Container = -1;
static int ett_s1ap_UE_RLF_Report_Container_for_extended_bands = -1;
static int ett_s1ap_S1_Message = -1;
static int ett_s1ap_E_UTRAN_Trace_ID = -1;
static int ett_s1ap_InterfacesToTrace = -1;
static int ett_s1ap_EncryptionAlgorithms = -1;
static int ett_s1ap_IntegrityProtectionAlgorithms = -1;
static int ett_s1ap_LastVisitedNGRANCellInformation = -1;
static int ett_s1ap_LastVisitedUTRANCellInformation = -1;
static int ett_s1ap_SerialNumber = -1;
static int ett_s1ap_WarningType = -1;
static int ett_s1ap_DataCodingScheme = -1;
static int ett_s1ap_WarningMessageContents = -1;
static int ett_s1ap_MSClassmark = -1;
static int ett_s1ap_MeasurementsToActivate = -1;
static int ett_s1ap_MDT_Location_Info = -1;
static int ett_s1ap_IMSI = -1;
static int ett_s1ap_NASSecurityParameters = -1;
static int ett_s1ap_NRencryptionAlgorithms = -1;
static int ett_s1ap_NRintegrityProtectionAlgorithms = -1;
static int ett_s1ap_UE_Application_Layer_Measurement_Capability = -1;
static int ett_s1ap_sMTC = -1;
static int ett_s1ap_threshRS_Index_r15 = -1;
static int ett_s1ap_sSBToMeasure = -1;
static int ett_s1ap_sSRSSIMeasurement = -1;
static int ett_s1ap_quantityConfigNR_R15 = -1;
static int ett_s1ap_blackCellsToAddModList = -1;
static int ett_s1ap_NB_IoT_RLF_Report_Container = -1;
static int ett_s1ap_MDT_ConfigurationNR = -1;
static int ett_s1ap_IntersystemSONConfigurationTransfer = -1;

/*--- Included file: packet-s1ap-ett.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-ett.c"
static gint ett_s1ap_PrivateIE_ID = -1;
static gint ett_s1ap_ProtocolIE_Container = -1;
static gint ett_s1ap_ProtocolIE_Field = -1;
static gint ett_s1ap_ProtocolIE_ContainerList = -1;
static gint ett_s1ap_ProtocolExtensionContainer = -1;
static gint ett_s1ap_ProtocolExtensionField = -1;
static gint ett_s1ap_PrivateIE_Container = -1;
static gint ett_s1ap_PrivateIE_Field = -1;
static gint ett_s1ap_Additional_GUTI = -1;
static gint ett_s1ap_AreaScopeOfMDT = -1;
static gint ett_s1ap_AreaScopeOfQMC = -1;
static gint ett_s1ap_AllocationAndRetentionPriority = -1;
static gint ett_s1ap_AssistanceDataForCECapableUEs = -1;
static gint ett_s1ap_AssistanceDataForPaging = -1;
static gint ett_s1ap_AssistanceDataForRecommendedCells = -1;
static gint ett_s1ap_Bearers_SubjectToStatusTransferList = -1;
static gint ett_s1ap_Bearers_SubjectToStatusTransfer_Item = -1;
static gint ett_s1ap_Bearers_SubjectToEarlyStatusTransferList = -1;
static gint ett_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item = -1;
static gint ett_s1ap_BluetoothMeasurementConfiguration = -1;
static gint ett_s1ap_BluetoothMeasConfigNameList = -1;
static gint ett_s1ap_BPLMNs = -1;
static gint ett_s1ap_BroadcastCancelledAreaList = -1;
static gint ett_s1ap_BroadcastCompletedAreaList = -1;
static gint ett_s1ap_CancelledCellinEAI = -1;
static gint ett_s1ap_CancelledCellinEAI_Item = -1;
static gint ett_s1ap_CancelledCellinTAI = -1;
static gint ett_s1ap_CancelledCellinTAI_Item = -1;
static gint ett_s1ap_Cause = -1;
static gint ett_s1ap_CellIdentifierAndCELevelForCECapableUEs = -1;
static gint ett_s1ap_CellID_Broadcast = -1;
static gint ett_s1ap_CellID_Broadcast_Item = -1;
static gint ett_s1ap_CellID_Cancelled = -1;
static gint ett_s1ap_CellID_Cancelled_Item = -1;
static gint ett_s1ap_CellBasedMDT = -1;
static gint ett_s1ap_CellIdListforMDT = -1;
static gint ett_s1ap_CellBasedQMC = -1;
static gint ett_s1ap_CellIdListforQMC = -1;
static gint ett_s1ap_Cdma2000OneXSRVCCInfo = -1;
static gint ett_s1ap_CellType = -1;
static gint ett_s1ap_CGI = -1;
static gint ett_s1ap_CNTypeRestrictions = -1;
static gint ett_s1ap_CNTypeRestrictions_Item = -1;
static gint ett_s1ap_ConnectedengNBList = -1;
static gint ett_s1ap_ConnectedengNBItem = -1;
static gint ett_s1ap_ContextatSource = -1;
static gint ett_s1ap_CSG_IdList = -1;
static gint ett_s1ap_CSG_IdList_Item = -1;
static gint ett_s1ap_COUNTvalue = -1;
static gint ett_s1ap_COUNTValueExtended = -1;
static gint ett_s1ap_COUNTvaluePDCP_SNlength18 = -1;
static gint ett_s1ap_CriticalityDiagnostics = -1;
static gint ett_s1ap_CriticalityDiagnostics_IE_List = -1;
static gint ett_s1ap_CriticalityDiagnostics_IE_Item = -1;
static gint ett_s1ap_DAPSRequestInfo = -1;
static gint ett_s1ap_DAPSResponseInfoList = -1;
static gint ett_s1ap_DAPSResponseInfoItem = -1;
static gint ett_s1ap_DAPSResponseInfo = -1;
static gint ett_s1ap_ServedDCNs = -1;
static gint ett_s1ap_ServedDCNsItem = -1;
static gint ett_s1ap_DL_CP_SecurityInformation = -1;
static gint ett_s1ap_DLCOUNT_PDCP_SNlength = -1;
static gint ett_s1ap_ECGIList = -1;
static gint ett_s1ap_PWSfailedECGIList = -1;
static gint ett_s1ap_EmergencyAreaIDList = -1;
static gint ett_s1ap_EmergencyAreaID_Broadcast = -1;
static gint ett_s1ap_EmergencyAreaID_Broadcast_Item = -1;
static gint ett_s1ap_EmergencyAreaID_Cancelled = -1;
static gint ett_s1ap_EmergencyAreaID_Cancelled_Item = -1;
static gint ett_s1ap_CompletedCellinEAI = -1;
static gint ett_s1ap_CompletedCellinEAI_Item = -1;
static gint ett_s1ap_ECGI_List = -1;
static gint ett_s1ap_EmergencyAreaIDListForRestart = -1;
static gint ett_s1ap_ENB_EarlyStatusTransfer_TransparentContainer = -1;
static gint ett_s1ap_ENB_ID = -1;
static gint ett_s1ap_GERAN_Cell_ID = -1;
static gint ett_s1ap_Global_ENB_ID = -1;
static gint ett_s1ap_Global_en_gNB_ID = -1;
static gint ett_s1ap_GUMMEIList = -1;
static gint ett_s1ap_ENB_StatusTransfer_TransparentContainer = -1;
static gint ett_s1ap_ENBX2TLAs = -1;
static gint ett_s1ap_EN_DCSONConfigurationTransfer = -1;
static gint ett_s1ap_EN_DCSONTransferType = -1;
static gint ett_s1ap_EN_DCTransferTypeRequest = -1;
static gint ett_s1ap_EN_DCTransferTypeReply = -1;
static gint ett_s1ap_EN_DCSONeNBIdentification = -1;
static gint ett_s1ap_EN_DCSONengNBIdentification = -1;
static gint ett_s1ap_EPLMNs = -1;
static gint ett_s1ap_E_RABInformationList = -1;
static gint ett_s1ap_E_RABInformationListItem = -1;
static gint ett_s1ap_E_RABList = -1;
static gint ett_s1ap_E_RABItem = -1;
static gint ett_s1ap_E_RABLevelQoSParameters = -1;
static gint ett_s1ap_E_RABUsageReportList = -1;
static gint ett_s1ap_E_RABUsageReportItem = -1;
static gint ett_s1ap_EUTRAN_CGI = -1;
static gint ett_s1ap_ExpectedUEBehaviour = -1;
static gint ett_s1ap_ExpectedUEActivityBehaviour = -1;
static gint ett_s1ap_FiveGSTAI = -1;
static gint ett_s1ap_ForbiddenTAs = -1;
static gint ett_s1ap_ForbiddenTAs_Item = -1;
static gint ett_s1ap_ForbiddenTACs = -1;
static gint ett_s1ap_ForbiddenLAs = -1;
static gint ett_s1ap_ForbiddenLAs_Item = -1;
static gint ett_s1ap_ForbiddenLACs = -1;
static gint ett_s1ap_GBR_QosInformation = -1;
static gint ett_s1ap_GUMMEI = -1;
static gint ett_s1ap_HandoverRestrictionList = -1;
static gint ett_s1ap_ImmediateMDT = -1;
static gint ett_s1ap_InformationOnRecommendedCellsAndENBsForPaging = -1;
static gint ett_s1ap_IntersystemMeasurementConfiguration = -1;
static gint ett_s1ap_InterSystemMeasurementParameters = -1;
static gint ett_s1ap_InterSystemMeasurementList = -1;
static gint ett_s1ap_InterSystemMeasurementItem = -1;
static gint ett_s1ap_LAI = -1;
static gint ett_s1ap_LastVisitedCell_Item = -1;
static gint ett_s1ap_LastVisitedEUTRANCellInformation = -1;
static gint ett_s1ap_LastVisitedGERANCellInformation = -1;
static gint ett_s1ap_ListeningSubframePattern = -1;
static gint ett_s1ap_LoggedMDT = -1;
static gint ett_s1ap_LoggedMBSFNMDT = -1;
static gint ett_s1ap_M3Configuration = -1;
static gint ett_s1ap_M4Configuration = -1;
static gint ett_s1ap_M5Configuration = -1;
static gint ett_s1ap_M6Configuration = -1;
static gint ett_s1ap_M7Configuration = -1;
static gint ett_s1ap_MDT_Configuration = -1;
static gint ett_s1ap_MBSFN_ResultToLog = -1;
static gint ett_s1ap_MBSFN_ResultToLogInfo = -1;
static gint ett_s1ap_MDTPLMNList = -1;
static gint ett_s1ap_MDTMode = -1;
static gint ett_s1ap_MeasurementThresholdA2 = -1;
static gint ett_s1ap_MMEPagingTarget = -1;
static gint ett_s1ap_MutingPatternInformation = -1;
static gint ett_s1ap_NB_IoT_Paging_eDRXInformation = -1;
static gint ett_s1ap_NR_CGI = -1;
static gint ett_s1ap_NRUESecurityCapabilities = -1;
static gint ett_s1ap_NRV2XServicesAuthorized = -1;
static gint ett_s1ap_NRUESidelinkAggregateMaximumBitrate = -1;
static gint ett_s1ap_OverloadResponse = -1;
static gint ett_s1ap_PagingAttemptInformation = -1;
static gint ett_s1ap_Paging_eDRXInformation = -1;
static gint ett_s1ap_PC5QoSParameters = -1;
static gint ett_s1ap_PC5QoSFlowList = -1;
static gint ett_s1ap_PC5QoSFlowItem = -1;
static gint ett_s1ap_PC5FlowBitRates = -1;
static gint ett_s1ap_M1PeriodicReporting = -1;
static gint ett_s1ap_PLMNAreaBasedQMC = -1;
static gint ett_s1ap_PLMNListforQMC = -1;
static gint ett_s1ap_ProSeAuthorized = -1;
static gint ett_s1ap_PSCellInformation = -1;
static gint ett_s1ap_RecommendedCellsForPaging = -1;
static gint ett_s1ap_RecommendedCellList = -1;
static gint ett_s1ap_RecommendedCellItem = -1;
static gint ett_s1ap_RecommendedENBsForPaging = -1;
static gint ett_s1ap_RecommendedENBList = -1;
static gint ett_s1ap_RecommendedENBItem = -1;
static gint ett_s1ap_RequestType = -1;
static gint ett_s1ap_RIMTransfer = -1;
static gint ett_s1ap_RIMRoutingAddress = -1;
static gint ett_s1ap_RLFReportInformation = -1;
static gint ett_s1ap_ECGIListForRestart = -1;
static gint ett_s1ap_SecurityContext = -1;
static gint ett_s1ap_SecondaryRATDataUsageReportList = -1;
static gint ett_s1ap_SecondaryRATDataUsageReportItem = -1;
static gint ett_s1ap_SONInformation = -1;
static gint ett_s1ap_SONInformationReply = -1;
static gint ett_s1ap_SONInformationReport = -1;
static gint ett_s1ap_SONConfigurationTransfer = -1;
static gint ett_s1ap_SynchronisationInformation = -1;
static gint ett_s1ap_SourceeNB_ID = -1;
static gint ett_s1ap_SourceNodeID = -1;
static gint ett_s1ap_SourceeNB_ToTargeteNB_TransparentContainer = -1;
static gint ett_s1ap_SourceNgRanNode_ID = -1;
static gint ett_s1ap_ServedGUMMEIs = -1;
static gint ett_s1ap_ServedGUMMEIsItem = -1;
static gint ett_s1ap_ServedGroupIDs = -1;
static gint ett_s1ap_ServedMMECs = -1;
static gint ett_s1ap_ServedPLMNs = -1;
static gint ett_s1ap_Subscription_Based_UE_DifferentiationInfo = -1;
static gint ett_s1ap_ScheduledCommunicationTime = -1;
static gint ett_s1ap_SupportedTAs = -1;
static gint ett_s1ap_SupportedTAs_Item = -1;
static gint ett_s1ap_TimeSynchronisationInfo = -1;
static gint ett_s1ap_S_TMSI = -1;
static gint ett_s1ap_TAIBasedMDT = -1;
static gint ett_s1ap_TAIListforMDT = -1;
static gint ett_s1ap_TAIListforWarning = -1;
static gint ett_s1ap_TAI = -1;
static gint ett_s1ap_TAI_Broadcast = -1;
static gint ett_s1ap_TAI_Broadcast_Item = -1;
static gint ett_s1ap_TAI_Cancelled = -1;
static gint ett_s1ap_TAI_Cancelled_Item = -1;
static gint ett_s1ap_TABasedMDT = -1;
static gint ett_s1ap_TAListforMDT = -1;
static gint ett_s1ap_TABasedQMC = -1;
static gint ett_s1ap_TAListforQMC = -1;
static gint ett_s1ap_TAIBasedQMC = -1;
static gint ett_s1ap_TAIListforQMC = -1;
static gint ett_s1ap_CompletedCellinTAI = -1;
static gint ett_s1ap_CompletedCellinTAI_Item = -1;
static gint ett_s1ap_TargetID = -1;
static gint ett_s1ap_TargeteNB_ID = -1;
static gint ett_s1ap_TargetRNC_ID = -1;
static gint ett_s1ap_TargetNgRanNode_ID = -1;
static gint ett_s1ap_Global_RAN_NODE_ID = -1;
static gint ett_s1ap_GNB = -1;
static gint ett_s1ap_Global_GNB_ID = -1;
static gint ett_s1ap_GNB_Identity = -1;
static gint ett_s1ap_NG_eNB = -1;
static gint ett_s1ap_TargeteNB_ToSourceeNB_TransparentContainer = -1;
static gint ett_s1ap_M1ThresholdEventA2 = -1;
static gint ett_s1ap_TransportInformation = -1;
static gint ett_s1ap_TraceActivation = -1;
static gint ett_s1ap_TunnelInformation = -1;
static gint ett_s1ap_TAIListForRestart = -1;
static gint ett_s1ap_UEAggregateMaximumBitrate = -1;
static gint ett_s1ap_UEAppLayerMeasConfig = -1;
static gint ett_s1ap_UE_S1AP_IDs = -1;
static gint ett_s1ap_UE_S1AP_ID_pair = -1;
static gint ett_s1ap_UE_associatedLogicalS1_ConnectionItem = -1;
static gint ett_s1ap_UE_HistoryInformation = -1;
static gint ett_s1ap_UEPagingID = -1;
static gint ett_s1ap_UESecurityCapabilities = -1;
static gint ett_s1ap_UESidelinkAggregateMaximumBitrate = -1;
static gint ett_s1ap_UL_CP_SecurityInformation = -1;
static gint ett_s1ap_UserLocationInformation = -1;
static gint ett_s1ap_V2XServicesAuthorized = -1;
static gint ett_s1ap_WarningAreaList = -1;
static gint ett_s1ap_WLANMeasurementConfiguration = -1;
static gint ett_s1ap_WLANMeasConfigNameList = -1;
static gint ett_s1ap_WUS_Assistance_Information = -1;
static gint ett_s1ap_X2TNLConfigurationInfo = -1;
static gint ett_s1ap_ENBX2ExtTLAs = -1;
static gint ett_s1ap_ENBX2ExtTLA = -1;
static gint ett_s1ap_ENBX2GTPTLAs = -1;
static gint ett_s1ap_ENBIndirectX2TransportLayerAddresses = -1;
static gint ett_s1ap_HandoverRequired = -1;
static gint ett_s1ap_HandoverCommand = -1;
static gint ett_s1ap_E_RABDataForwardingItem = -1;
static gint ett_s1ap_HandoverPreparationFailure = -1;
static gint ett_s1ap_HandoverRequest = -1;
static gint ett_s1ap_E_RABToBeSetupItemHOReq = -1;
static gint ett_s1ap_HandoverRequestAcknowledge = -1;
static gint ett_s1ap_E_RABAdmittedItem = -1;
static gint ett_s1ap_E_RABFailedToSetupItemHOReqAck = -1;
static gint ett_s1ap_HandoverFailure = -1;
static gint ett_s1ap_HandoverNotify = -1;
static gint ett_s1ap_PathSwitchRequest = -1;
static gint ett_s1ap_E_RABToBeSwitchedDLItem = -1;
static gint ett_s1ap_PathSwitchRequestAcknowledge = -1;
static gint ett_s1ap_E_RABToBeSwitchedULItem = -1;
static gint ett_s1ap_PathSwitchRequestFailure = -1;
static gint ett_s1ap_HandoverCancel = -1;
static gint ett_s1ap_HandoverCancelAcknowledge = -1;
static gint ett_s1ap_HandoverSuccess = -1;
static gint ett_s1ap_ENBEarlyStatusTransfer = -1;
static gint ett_s1ap_MMEEarlyStatusTransfer = -1;
static gint ett_s1ap_E_RABSetupRequest = -1;
static gint ett_s1ap_E_RABToBeSetupListBearerSUReq = -1;
static gint ett_s1ap_E_RABToBeSetupItemBearerSUReq = -1;
static gint ett_s1ap_E_RABSetupResponse = -1;
static gint ett_s1ap_E_RABSetupListBearerSURes = -1;
static gint ett_s1ap_E_RABSetupItemBearerSURes = -1;
static gint ett_s1ap_E_RABModifyRequest = -1;
static gint ett_s1ap_E_RABToBeModifiedListBearerModReq = -1;
static gint ett_s1ap_E_RABToBeModifiedItemBearerModReq = -1;
static gint ett_s1ap_E_RABModifyResponse = -1;
static gint ett_s1ap_E_RABModifyListBearerModRes = -1;
static gint ett_s1ap_E_RABModifyItemBearerModRes = -1;
static gint ett_s1ap_E_RABReleaseCommand = -1;
static gint ett_s1ap_E_RABReleaseResponse = -1;
static gint ett_s1ap_E_RABReleaseListBearerRelComp = -1;
static gint ett_s1ap_E_RABReleaseItemBearerRelComp = -1;
static gint ett_s1ap_E_RABReleaseIndication = -1;
static gint ett_s1ap_InitialContextSetupRequest = -1;
static gint ett_s1ap_E_RABToBeSetupListCtxtSUReq = -1;
static gint ett_s1ap_E_RABToBeSetupItemCtxtSUReq = -1;
static gint ett_s1ap_InitialContextSetupResponse = -1;
static gint ett_s1ap_E_RABSetupListCtxtSURes = -1;
static gint ett_s1ap_E_RABSetupItemCtxtSURes = -1;
static gint ett_s1ap_InitialContextSetupFailure = -1;
static gint ett_s1ap_Paging = -1;
static gint ett_s1ap_TAIList = -1;
static gint ett_s1ap_TAIItem = -1;
static gint ett_s1ap_UEContextReleaseRequest = -1;
static gint ett_s1ap_UEContextReleaseCommand = -1;
static gint ett_s1ap_UEContextReleaseComplete = -1;
static gint ett_s1ap_UEContextModificationRequest = -1;
static gint ett_s1ap_UEContextModificationResponse = -1;
static gint ett_s1ap_UEContextModificationFailure = -1;
static gint ett_s1ap_UERadioCapabilityMatchRequest = -1;
static gint ett_s1ap_UERadioCapabilityMatchResponse = -1;
static gint ett_s1ap_DownlinkNASTransport = -1;
static gint ett_s1ap_InitialUEMessage = -1;
static gint ett_s1ap_UplinkNASTransport = -1;
static gint ett_s1ap_NASNonDeliveryIndication = -1;
static gint ett_s1ap_RerouteNASRequest = -1;
static gint ett_s1ap_NASDeliveryIndication = -1;
static gint ett_s1ap_Reset = -1;
static gint ett_s1ap_ResetType = -1;
static gint ett_s1ap_UE_associatedLogicalS1_ConnectionListRes = -1;
static gint ett_s1ap_ResetAcknowledge = -1;
static gint ett_s1ap_UE_associatedLogicalS1_ConnectionListResAck = -1;
static gint ett_s1ap_ErrorIndication = -1;
static gint ett_s1ap_S1SetupRequest = -1;
static gint ett_s1ap_S1SetupResponse = -1;
static gint ett_s1ap_S1SetupFailure = -1;
static gint ett_s1ap_ENBConfigurationUpdate = -1;
static gint ett_s1ap_ENBConfigurationUpdateAcknowledge = -1;
static gint ett_s1ap_ENBConfigurationUpdateFailure = -1;
static gint ett_s1ap_MMEConfigurationUpdate = -1;
static gint ett_s1ap_MMEConfigurationUpdateAcknowledge = -1;
static gint ett_s1ap_MMEConfigurationUpdateFailure = -1;
static gint ett_s1ap_DownlinkS1cdma2000tunnelling = -1;
static gint ett_s1ap_UplinkS1cdma2000tunnelling = -1;
static gint ett_s1ap_UECapabilityInfoIndication = -1;
static gint ett_s1ap_ENBStatusTransfer = -1;
static gint ett_s1ap_MMEStatusTransfer = -1;
static gint ett_s1ap_TraceStart = -1;
static gint ett_s1ap_TraceFailureIndication = -1;
static gint ett_s1ap_DeactivateTrace = -1;
static gint ett_s1ap_CellTrafficTrace = -1;
static gint ett_s1ap_LocationReportingControl = -1;
static gint ett_s1ap_LocationReportingFailureIndication = -1;
static gint ett_s1ap_LocationReport = -1;
static gint ett_s1ap_OverloadStart = -1;
static gint ett_s1ap_OverloadStop = -1;
static gint ett_s1ap_WriteReplaceWarningRequest = -1;
static gint ett_s1ap_WriteReplaceWarningResponse = -1;
static gint ett_s1ap_ENBDirectInformationTransfer = -1;
static gint ett_s1ap_Inter_SystemInformationTransferType = -1;
static gint ett_s1ap_MMEDirectInformationTransfer = -1;
static gint ett_s1ap_ENBConfigurationTransfer = -1;
static gint ett_s1ap_MMEConfigurationTransfer = -1;
static gint ett_s1ap_PrivateMessage = -1;
static gint ett_s1ap_KillRequest = -1;
static gint ett_s1ap_KillResponse = -1;
static gint ett_s1ap_PWSRestartIndication = -1;
static gint ett_s1ap_PWSFailureIndication = -1;
static gint ett_s1ap_DownlinkUEAssociatedLPPaTransport = -1;
static gint ett_s1ap_UplinkUEAssociatedLPPaTransport = -1;
static gint ett_s1ap_DownlinkNonUEAssociatedLPPaTransport = -1;
static gint ett_s1ap_UplinkNonUEAssociatedLPPaTransport = -1;
static gint ett_s1ap_E_RABModificationIndication = -1;
static gint ett_s1ap_E_RABToBeModifiedItemBearerModInd = -1;
static gint ett_s1ap_E_RABNotToBeModifiedItemBearerModInd = -1;
static gint ett_s1ap_CSGMembershipInfo = -1;
static gint ett_s1ap_E_RABModificationConfirm = -1;
static gint ett_s1ap_E_RABModifyListBearerModConf = -1;
static gint ett_s1ap_E_RABModifyItemBearerModConf = -1;
static gint ett_s1ap_UEContextModificationIndication = -1;
static gint ett_s1ap_UEContextModificationConfirm = -1;
static gint ett_s1ap_UEContextSuspendRequest = -1;
static gint ett_s1ap_UEContextSuspendResponse = -1;
static gint ett_s1ap_UEContextResumeRequest = -1;
static gint ett_s1ap_E_RABFailedToResumeItemResumeReq = -1;
static gint ett_s1ap_UEContextResumeResponse = -1;
static gint ett_s1ap_E_RABFailedToResumeItemResumeRes = -1;
static gint ett_s1ap_UEContextResumeFailure = -1;
static gint ett_s1ap_ConnectionEstablishmentIndication = -1;
static gint ett_s1ap_RetrieveUEInformation = -1;
static gint ett_s1ap_UEInformationTransfer = -1;
static gint ett_s1ap_ENBCPRelocationIndication = -1;
static gint ett_s1ap_MMECPRelocationIndication = -1;
static gint ett_s1ap_SecondaryRATDataUsageReport = -1;
static gint ett_s1ap_UERadioCapabilityIDMappingRequest = -1;
static gint ett_s1ap_UERadioCapabilityIDMappingResponse = -1;
static gint ett_s1ap_S1AP_PDU = -1;
static gint ett_s1ap_InitiatingMessage = -1;
static gint ett_s1ap_SuccessfulOutcome = -1;
static gint ett_s1ap_UnsuccessfulOutcome = -1;
static gint ett_s1ap_SONtransferRequestContainer = -1;
static gint ett_s1ap_SONtransferResponseContainer = -1;
static gint ett_s1ap_SONtransferCause = -1;
static gint ett_s1ap_CellLoadReportingResponse = -1;
static gint ett_s1ap_EUTRANcellLoadReportingResponse = -1;
static gint ett_s1ap_EUTRANResponse = -1;
static gint ett_s1ap_IRAT_Cell_ID = -1;
static gint ett_s1ap_RequestedCellList = -1;
static gint ett_s1ap_MultiCellLoadReportingRequest = -1;
static gint ett_s1ap_ReportingCellList_Item = -1;
static gint ett_s1ap_ReportingCellList = -1;
static gint ett_s1ap_MultiCellLoadReportingResponse = -1;
static gint ett_s1ap_MultiCellLoadReportingResponse_Item = -1;
static gint ett_s1ap_EventTriggeredCellLoadReportingRequest = -1;
static gint ett_s1ap_EventTriggeredCellLoadReportingResponse = -1;
static gint ett_s1ap_HOReport = -1;
static gint ett_s1ap_CandidateCellList = -1;
static gint ett_s1ap_CandidatePCIList = -1;
static gint ett_s1ap_CandidatePCI = -1;
static gint ett_s1ap_CellActivationRequest = -1;
static gint ett_s1ap_CellsToActivateList = -1;
static gint ett_s1ap_CellsToActivateList_Item = -1;
static gint ett_s1ap_CellActivationResponse = -1;
static gint ett_s1ap_ActivatedCellsList = -1;
static gint ett_s1ap_ActivatedCellsList_Item = -1;
static gint ett_s1ap_CellStateIndication = -1;
static gint ett_s1ap_NotificationCellList = -1;
static gint ett_s1ap_NotificationCellList_Item = -1;
static gint ett_s1ap_FailureEventReport = -1;
static gint ett_s1ap_TooEarlyInterRATHOReportReportFromEUTRAN = -1;
static gint ett_s1ap_EHRPDSectorLoadReportingResponse = -1;
static gint ett_s1ap_EHRPDCompositeAvailableCapacity = -1;
static gint ett_s1ap_EHRPDMultiSectorLoadReportingResponseItem = -1;

/*--- End of included file: packet-s1ap-ett.c ---*/
#line 164 "./asn1/s1ap/packet-s1ap-template.c"

static expert_field ei_s1ap_number_pages_le15 = EI_INIT;

enum{
  INITIATING_MESSAGE,
  SUCCESSFUL_OUTCOME,
  UNSUCCESSFUL_OUTCOME
};

struct s1ap_conv_info {
  wmem_map_t *nbiot_ta;
  wmem_tree_t *nbiot_enb_ue_s1ap_id;
};

struct s1ap_supported_ta {
  guint16 tac;
  wmem_array_t *plmn;
};

struct s1ap_tai {
  guint32 plmn;
  guint16 tac;
};

struct s1ap_private_data {
  struct s1ap_conv_info *s1ap_conv;
  guint32 procedure_code;
  guint32 protocol_ie_id;
  guint32 protocol_extension_id;
  guint32 handover_type_value;
  guint32 message_type;
  guint8 data_coding_scheme;
  struct s1ap_supported_ta *supported_ta;
  const char *obj_id;
  struct s1ap_tai *tai;
  guint16 enb_ue_s1ap_id;
  gboolean srvcc_ho_cs_only;
  guint8 transparent_container_type;
  e212_number_type_t number_type;
};

enum {
  S1AP_LTE_CONTAINER_AUTOMATIC,
  S1AP_LTE_CONTAINER_LEGACY,
  S1AP_LTE_CONTAINER_NBIOT
};

static const enum_val_t s1ap_lte_container_vals[] = {
  {"automatic", "Automatic", S1AP_LTE_CONTAINER_AUTOMATIC},
  {"legacy", "Legacy LTE", S1AP_LTE_CONTAINER_LEGACY},
  {"nb-iot","NB-IoT", S1AP_LTE_CONTAINER_NBIOT},
  {NULL, NULL, -1}
};

enum {
  SOURCE_TO_TARGET_TRANSPARENT_CONTAINER = 1,
  TARGET_TO_SOURCE_TRANSPARENT_CONTAINER
};

/* Global variables */
static guint gbl_s1apSctpPort=SCTP_PORT_S1AP;
static gboolean g_s1ap_dissect_container = TRUE;
static gint g_s1ap_dissect_lte_container_as = S1AP_LTE_CONTAINER_AUTOMATIC;

static dissector_handle_t s1ap_handle;

/* Dissector tables */
static dissector_table_t s1ap_ies_dissector_table;
static dissector_table_t s1ap_ies_p1_dissector_table;
static dissector_table_t s1ap_ies_p2_dissector_table;
static dissector_table_t s1ap_extension_dissector_table;
static dissector_table_t s1ap_proc_imsg_dissector_table;
static dissector_table_t s1ap_proc_sout_dissector_table;
static dissector_table_t s1ap_proc_uout_dissector_table;

static int dissect_ProtocolIEFieldValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
/* Currently not used
static int dissect_ProtocolIEFieldPairFirstValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
static int dissect_ProtocolIEFieldPairSecondValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
*/
static int dissect_ProtocolExtensionFieldExtensionValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_InitiatingMessageValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_SuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);
static int dissect_UnsuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *);

static int dissect_InitialUEMessage_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data);
#if 0
static int dissect_SourceRNC_ToTargetRNC_TransparentContainer_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
static int dissect_TargetRNC_ToSourceRNC_TransparentContainer_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
static int dissect_SourceBSS_ToTargetBSS_TransparentContainer_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
static int dissect_TargetBSS_ToSourceBSS_TransparentContainer_PDU(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
#endif

static void
s1ap_Threshold_RSRP_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%ddBm (%u)", (gint32)v-140, v);
}

static void
s1ap_Threshold_RSRQ_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%.1fdB (%u)", ((float)v/2)-20, v);
}

static const true_false_string s1ap_tfs_interfacesToTrace = {
  "Should be traced",
  "Should not be traced"
};

static void
s1ap_Time_UE_StayedInCell_EnhancedGranularity_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%.1fs", ((float)v)/10);
}

const value_string s1ap_serialNumber_gs_vals[] = {
  { 0, "Display mode immediate, cell wide"},
  { 1, "Display mode normal, PLMN wide"},
  { 2, "Display mode normal, tracking area wide"},
  { 3, "Display mode normal, cell wide"},
  { 0, NULL},
};

const value_string s1ap_warningType_vals[] = {
  { 0, "Earthquake"},
  { 1, "Tsunami"},
  { 2, "Earthquake and Tsunami"},
  { 3, "Test"},
  { 4, "Other"},
  { 0, NULL},
};

void
dissect_s1ap_warningMessageContents(tvbuff_t *warning_msg_tvb, proto_tree *tree, packet_info *pinfo, guint8 dcs, int hf_nb_pages, int hf_decoded_page)
{
  guint32 offset;
  guint8 nb_of_pages, length, *str;
  proto_item *ti;
  tvbuff_t *cb_data_page_tvb, *cb_data_tvb;
  int i;

  nb_of_pages = tvb_get_guint8(warning_msg_tvb, 0);
  ti = proto_tree_add_uint(tree, hf_nb_pages, warning_msg_tvb, 0, 1, nb_of_pages);
  if (nb_of_pages > 15) {
    expert_add_info_format(pinfo, ti, &ei_s1ap_number_pages_le15,
                           "Number of pages should be <=15 (found %u)", nb_of_pages);
    nb_of_pages = 15;
  }
  for (i = 0, offset = 1; i < nb_of_pages; i++) {
    length = tvb_get_guint8(warning_msg_tvb, offset+82);
    cb_data_page_tvb = tvb_new_subset_length(warning_msg_tvb, offset, length);
    cb_data_tvb = dissect_cbs_data(dcs, cb_data_page_tvb, tree, pinfo, 0);
    if (cb_data_tvb) {
      str = tvb_get_string_enc(pinfo->pool, cb_data_tvb, 0, tvb_reported_length(cb_data_tvb), ENC_UTF_8|ENC_NA);
      proto_tree_add_string_format(tree, hf_decoded_page, warning_msg_tvb, offset, 83,
                                   str, "Decoded Page %u: %s", i+1, str);
    }
    offset += 83;
  }
}

static void
s1ap_EUTRANRoundTripDelayEstimationInfo_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%uTs (%u)", 16*v, v);
}

static const true_false_string s1ap_tfs_activate_do_not_activate = {
  "Activate",
  "Do not activate"
};

static void
s1ap_Packet_LossRate_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%.1f %% (%u)", (float)v/10, v);
}

static void
s1ap_threshold_nr_rsrp_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%ddBm (%u)", (gint32)v-156, v);
}

static void
s1ap_threshold_nr_rsrq_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%.1fdB (%u)", ((float)v/2)-43, v);
}

static void
s1ap_threshold_nr_sinr_fmt(gchar *s, guint32 v)
{
  snprintf(s, ITEM_LABEL_LENGTH, "%.1fdB (%u)", ((float)v/2)-23, v);
}

static struct s1ap_private_data*
s1ap_get_private_data(packet_info *pinfo)
{
  struct s1ap_private_data *s1ap_data = (struct s1ap_private_data*)p_get_proto_data(pinfo->pool, pinfo, proto_s1ap, 0);
  if (!s1ap_data) {
    s1ap_data = wmem_new0(pinfo->pool, struct s1ap_private_data);
    p_add_proto_data(pinfo->pool, pinfo, proto_s1ap, 0, s1ap_data);
  }
  return s1ap_data;
}

static gboolean
s1ap_is_nbiot_ue(packet_info *pinfo)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  if (s1ap_data->s1ap_conv) {
    wmem_tree_key_t tree_key[3];
    guint32 *id;
    guint32 enb_ue_s1ap_id = s1ap_data->enb_ue_s1ap_id;

    tree_key[0].length = 1;
    tree_key[0].key = &enb_ue_s1ap_id;
    tree_key[1].length = 1;
    tree_key[1].key = &pinfo->num;
    tree_key[2].length = 0;
    tree_key[2].key = NULL;
    id = (guint32*)wmem_tree_lookup32_array_le(s1ap_data->s1ap_conv->nbiot_enb_ue_s1ap_id, tree_key);
    if (id && (*id == enb_ue_s1ap_id)) {
      return TRUE;
    }
  }
  return FALSE;
}


/*--- Included file: packet-s1ap-fn.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-fn.c"

static const value_string s1ap_Criticality_vals[] = {
  {   0, "reject" },
  {   1, "ignore" },
  {   2, "notify" },
  { 0, NULL }
};


static int
dissect_s1ap_Criticality(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_65535(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_T_global(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 231 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_object_identifier_str(tvb, offset, actx, tree, hf_index, &s1ap_data->obj_id);




  return offset;
}


static const value_string s1ap_PrivateIE_ID_vals[] = {
  {   0, "local" },
  {   1, "global" },
  { 0, NULL }
};

static const per_choice_t PrivateIE_ID_choice[] = {
  {   0, &hf_s1ap_local          , ASN1_NO_EXTENSIONS     , dissect_s1ap_INTEGER_0_65535 },
  {   1, &hf_s1ap_global         , ASN1_NO_EXTENSIONS     , dissect_s1ap_T_global },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_PrivateIE_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 227 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->obj_id = NULL;


  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_PrivateIE_ID, PrivateIE_ID_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_ProcedureCode_vals[] = {
  { id_HandoverPreparation, "id-HandoverPreparation" },
  { id_HandoverResourceAllocation, "id-HandoverResourceAllocation" },
  { id_HandoverNotification, "id-HandoverNotification" },
  { id_PathSwitchRequest, "id-PathSwitchRequest" },
  { id_HandoverCancel, "id-HandoverCancel" },
  { id_E_RABSetup, "id-E-RABSetup" },
  { id_E_RABModify, "id-E-RABModify" },
  { id_E_RABRelease, "id-E-RABRelease" },
  { id_E_RABReleaseIndication, "id-E-RABReleaseIndication" },
  { id_InitialContextSetup, "id-InitialContextSetup" },
  { id_Paging, "id-Paging" },
  { id_downlinkNASTransport, "id-downlinkNASTransport" },
  { id_initialUEMessage, "id-initialUEMessage" },
  { id_uplinkNASTransport, "id-uplinkNASTransport" },
  { id_Reset, "id-Reset" },
  { id_ErrorIndication, "id-ErrorIndication" },
  { id_NASNonDeliveryIndication, "id-NASNonDeliveryIndication" },
  { id_S1Setup, "id-S1Setup" },
  { id_UEContextReleaseRequest, "id-UEContextReleaseRequest" },
  { id_DownlinkS1cdma2000tunnelling, "id-DownlinkS1cdma2000tunnelling" },
  { id_UplinkS1cdma2000tunnelling, "id-UplinkS1cdma2000tunnelling" },
  { id_UEContextModification, "id-UEContextModification" },
  { id_UECapabilityInfoIndication, "id-UECapabilityInfoIndication" },
  { id_UEContextRelease, "id-UEContextRelease" },
  { id_eNBStatusTransfer, "id-eNBStatusTransfer" },
  { id_MMEStatusTransfer, "id-MMEStatusTransfer" },
  { id_DeactivateTrace, "id-DeactivateTrace" },
  { id_TraceStart, "id-TraceStart" },
  { id_TraceFailureIndication, "id-TraceFailureIndication" },
  { id_ENBConfigurationUpdate, "id-ENBConfigurationUpdate" },
  { id_MMEConfigurationUpdate, "id-MMEConfigurationUpdate" },
  { id_LocationReportingControl, "id-LocationReportingControl" },
  { id_LocationReportingFailureIndication, "id-LocationReportingFailureIndication" },
  { id_LocationReport, "id-LocationReport" },
  { id_OverloadStart, "id-OverloadStart" },
  { id_OverloadStop, "id-OverloadStop" },
  { id_WriteReplaceWarning, "id-WriteReplaceWarning" },
  { id_eNBDirectInformationTransfer, "id-eNBDirectInformationTransfer" },
  { id_MMEDirectInformationTransfer, "id-MMEDirectInformationTransfer" },
  { id_PrivateMessage, "id-PrivateMessage" },
  { id_eNBConfigurationTransfer, "id-eNBConfigurationTransfer" },
  { id_MMEConfigurationTransfer, "id-MMEConfigurationTransfer" },
  { id_CellTrafficTrace, "id-CellTrafficTrace" },
  { id_Kill, "id-Kill" },
  { id_downlinkUEAssociatedLPPaTransport, "id-downlinkUEAssociatedLPPaTransport" },
  { id_uplinkUEAssociatedLPPaTransport, "id-uplinkUEAssociatedLPPaTransport" },
  { id_downlinkNonUEAssociatedLPPaTransport, "id-downlinkNonUEAssociatedLPPaTransport" },
  { id_uplinkNonUEAssociatedLPPaTransport, "id-uplinkNonUEAssociatedLPPaTransport" },
  { id_UERadioCapabilityMatch, "id-UERadioCapabilityMatch" },
  { id_PWSRestartIndication, "id-PWSRestartIndication" },
  { id_E_RABModificationIndication, "id-E-RABModificationIndication" },
  { id_PWSFailureIndication, "id-PWSFailureIndication" },
  { id_RerouteNASRequest, "id-RerouteNASRequest" },
  { id_UEContextModificationIndication, "id-UEContextModificationIndication" },
  { id_ConnectionEstablishmentIndication, "id-ConnectionEstablishmentIndication" },
  { id_UEContextSuspend, "id-UEContextSuspend" },
  { id_UEContextResume, "id-UEContextResume" },
  { id_NASDeliveryIndication, "id-NASDeliveryIndication" },
  { id_RetrieveUEInformation, "id-RetrieveUEInformation" },
  { id_UEInformationTransfer, "id-UEInformationTransfer" },
  { id_eNBCPRelocationIndication, "id-eNBCPRelocationIndication" },
  { id_MMECPRelocationIndication, "id-MMECPRelocationIndication" },
  { id_SecondaryRATDataUsageReport, "id-SecondaryRATDataUsageReport" },
  { id_UERadioCapabilityIDMapping, "id-UERadioCapabilityIDMapping" },
  { id_HandoverSuccess, "id-HandoverSuccess" },
  { id_eNBEarlyStatusTransfer, "id-eNBEarlyStatusTransfer" },
  { id_MMEEarlyStatusTransfer, "id-MMEEarlyStatusTransfer" },
  { 0, NULL }
};

static value_string_ext s1ap_ProcedureCode_vals_ext = VALUE_STRING_EXT_INIT(s1ap_ProcedureCode_vals);


static int
dissect_s1ap_ProcedureCode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 145 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, &s1ap_data->procedure_code, FALSE);



  return offset;
}



static int
dissect_s1ap_ProtocolExtensionID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 139 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, &s1ap_data->protocol_extension_id, FALSE);




  return offset;
}


static const value_string s1ap_ProtocolIE_ID_vals[] = {
  { id_MME_UE_S1AP_ID, "id-MME-UE-S1AP-ID" },
  { id_HandoverType, "id-HandoverType" },
  { id_Cause, "id-Cause" },
  { id_SourceID, "id-SourceID" },
  { id_TargetID, "id-TargetID" },
  { id_Unknown_5, "id-Unknown-5" },
  { id_Unknown_6, "id-Unknown-6" },
  { id_Unknown_7, "id-Unknown-7" },
  { id_eNB_UE_S1AP_ID, "id-eNB-UE-S1AP-ID" },
  { id_Unknown_9, "id-Unknown-9" },
  { id_Unknown_10, "id-Unknown-10" },
  { id_Unknown_11, "id-Unknown-11" },
  { id_E_RABSubjecttoDataForwardingList, "id-E-RABSubjecttoDataForwardingList" },
  { id_E_RABtoReleaseListHOCmd, "id-E-RABtoReleaseListHOCmd" },
  { id_E_RABDataForwardingItem, "id-E-RABDataForwardingItem" },
  { id_E_RABReleaseItemBearerRelComp, "id-E-RABReleaseItemBearerRelComp" },
  { id_E_RABToBeSetupListBearerSUReq, "id-E-RABToBeSetupListBearerSUReq" },
  { id_E_RABToBeSetupItemBearerSUReq, "id-E-RABToBeSetupItemBearerSUReq" },
  { id_E_RABAdmittedList, "id-E-RABAdmittedList" },
  { id_E_RABFailedToSetupListHOReqAck, "id-E-RABFailedToSetupListHOReqAck" },
  { id_E_RABAdmittedItem, "id-E-RABAdmittedItem" },
  { id_E_RABFailedtoSetupItemHOReqAck, "id-E-RABFailedtoSetupItemHOReqAck" },
  { id_E_RABToBeSwitchedDLList, "id-E-RABToBeSwitchedDLList" },
  { id_E_RABToBeSwitchedDLItem, "id-E-RABToBeSwitchedDLItem" },
  { id_E_RABToBeSetupListCtxtSUReq, "id-E-RABToBeSetupListCtxtSUReq" },
  { id_TraceActivation, "id-TraceActivation" },
  { id_NAS_PDU, "id-NAS-PDU" },
  { id_E_RABToBeSetupItemHOReq, "id-E-RABToBeSetupItemHOReq" },
  { id_E_RABSetupListBearerSURes, "id-E-RABSetupListBearerSURes" },
  { id_E_RABFailedToSetupListBearerSURes, "id-E-RABFailedToSetupListBearerSURes" },
  { id_E_RABToBeModifiedListBearerModReq, "id-E-RABToBeModifiedListBearerModReq" },
  { id_E_RABModifyListBearerModRes, "id-E-RABModifyListBearerModRes" },
  { id_E_RABFailedToModifyList, "id-E-RABFailedToModifyList" },
  { id_E_RABToBeReleasedList, "id-E-RABToBeReleasedList" },
  { id_E_RABFailedToReleaseList, "id-E-RABFailedToReleaseList" },
  { id_E_RABItem, "id-E-RABItem" },
  { id_E_RABToBeModifiedItemBearerModReq, "id-E-RABToBeModifiedItemBearerModReq" },
  { id_E_RABModifyItemBearerModRes, "id-E-RABModifyItemBearerModRes" },
  { id_E_RABReleaseItem, "id-E-RABReleaseItem" },
  { id_E_RABSetupItemBearerSURes, "id-E-RABSetupItemBearerSURes" },
  { id_SecurityContext, "id-SecurityContext" },
  { id_HandoverRestrictionList, "id-HandoverRestrictionList" },
  { id_Unknown_42, "id-Unknown-42" },
  { id_UEPagingID, "id-UEPagingID" },
  { id_pagingDRX, "id-pagingDRX" },
  { id_Unknown_45, "id-Unknown-45" },
  { id_TAIList, "id-TAIList" },
  { id_TAIItem, "id-TAIItem" },
  { id_E_RABFailedToSetupListCtxtSURes, "id-E-RABFailedToSetupListCtxtSURes" },
  { id_E_RABReleaseItemHOCmd, "id-E-RABReleaseItemHOCmd" },
  { id_E_RABSetupItemCtxtSURes, "id-E-RABSetupItemCtxtSURes" },
  { id_E_RABSetupListCtxtSURes, "id-E-RABSetupListCtxtSURes" },
  { id_E_RABToBeSetupItemCtxtSUReq, "id-E-RABToBeSetupItemCtxtSUReq" },
  { id_E_RABToBeSetupListHOReq, "id-E-RABToBeSetupListHOReq" },
  { id_Unknown_54, "id-Unknown-54" },
  { id_GERANtoLTEHOInformationRes, "id-GERANtoLTEHOInformationRes" },
  { id_Unknown_56, "id-Unknown-56" },
  { id_UTRANtoLTEHOInformationRes, "id-UTRANtoLTEHOInformationRes" },
  { id_CriticalityDiagnostics, "id-CriticalityDiagnostics" },
  { id_Global_ENB_ID, "id-Global-ENB-ID" },
  { id_eNBname, "id-eNBname" },
  { id_MMEname, "id-MMEname" },
  { id_Unknown_62, "id-Unknown-62" },
  { id_ServedPLMNs, "id-ServedPLMNs" },
  { id_SupportedTAs, "id-SupportedTAs" },
  { id_TimeToWait, "id-TimeToWait" },
  { id_uEaggregateMaximumBitrate, "id-uEaggregateMaximumBitrate" },
  { id_TAI, "id-TAI" },
  { id_Unknown_68, "id-Unknown-68" },
  { id_E_RABReleaseListBearerRelComp, "id-E-RABReleaseListBearerRelComp" },
  { id_cdma2000PDU, "id-cdma2000PDU" },
  { id_cdma2000RATType, "id-cdma2000RATType" },
  { id_cdma2000SectorID, "id-cdma2000SectorID" },
  { id_SecurityKey, "id-SecurityKey" },
  { id_UERadioCapability, "id-UERadioCapability" },
  { id_GUMMEI_ID, "id-GUMMEI-ID" },
  { id_Unknown_76, "id-Unknown-76" },
  { id_Unknown_77, "id-Unknown-77" },
  { id_E_RABInformationListItem, "id-E-RABInformationListItem" },
  { id_Direct_Forwarding_Path_Availability, "id-Direct-Forwarding-Path-Availability" },
  { id_UEIdentityIndexValue, "id-UEIdentityIndexValue" },
  { id_Unknown_81, "id-Unknown-81" },
  { id_Unknown_82, "id-Unknown-82" },
  { id_cdma2000HOStatus, "id-cdma2000HOStatus" },
  { id_cdma2000HORequiredIndication, "id-cdma2000HORequiredIndication" },
  { id_Unknown_85, "id-Unknown-85" },
  { id_E_UTRAN_Trace_ID, "id-E-UTRAN-Trace-ID" },
  { id_RelativeMMECapacity, "id-RelativeMMECapacity" },
  { id_SourceMME_UE_S1AP_ID, "id-SourceMME-UE-S1AP-ID" },
  { id_Bearers_SubjectToStatusTransfer_Item, "id-Bearers-SubjectToStatusTransfer-Item" },
  { id_eNB_StatusTransfer_TransparentContainer, "id-eNB-StatusTransfer-TransparentContainer" },
  { id_UE_associatedLogicalS1_ConnectionItem, "id-UE-associatedLogicalS1-ConnectionItem" },
  { id_ResetType, "id-ResetType" },
  { id_UE_associatedLogicalS1_ConnectionListResAck, "id-UE-associatedLogicalS1-ConnectionListResAck" },
  { id_E_RABToBeSwitchedULItem, "id-E-RABToBeSwitchedULItem" },
  { id_E_RABToBeSwitchedULList, "id-E-RABToBeSwitchedULList" },
  { id_S_TMSI, "id-S-TMSI" },
  { id_cdma2000OneXRAND, "id-cdma2000OneXRAND" },
  { id_RequestType, "id-RequestType" },
  { id_UE_S1AP_IDs, "id-UE-S1AP-IDs" },
  { id_EUTRAN_CGI, "id-EUTRAN-CGI" },
  { id_OverloadResponse, "id-OverloadResponse" },
  { id_cdma2000OneXSRVCCInfo, "id-cdma2000OneXSRVCCInfo" },
  { id_E_RABFailedToBeReleasedList, "id-E-RABFailedToBeReleasedList" },
  { id_Source_ToTarget_TransparentContainer, "id-Source-ToTarget-TransparentContainer" },
  { id_ServedGUMMEIs, "id-ServedGUMMEIs" },
  { id_SubscriberProfileIDforRFP, "id-SubscriberProfileIDforRFP" },
  { id_UESecurityCapabilities, "id-UESecurityCapabilities" },
  { id_CSFallbackIndicator, "id-CSFallbackIndicator" },
  { id_CNDomain, "id-CNDomain" },
  { id_E_RABReleasedList, "id-E-RABReleasedList" },
  { id_MessageIdentifier, "id-MessageIdentifier" },
  { id_SerialNumber, "id-SerialNumber" },
  { id_WarningAreaList, "id-WarningAreaList" },
  { id_RepetitionPeriod, "id-RepetitionPeriod" },
  { id_NumberofBroadcastRequest, "id-NumberofBroadcastRequest" },
  { id_WarningType, "id-WarningType" },
  { id_WarningSecurityInfo, "id-WarningSecurityInfo" },
  { id_DataCodingScheme, "id-DataCodingScheme" },
  { id_WarningMessageContents, "id-WarningMessageContents" },
  { id_BroadcastCompletedAreaList, "id-BroadcastCompletedAreaList" },
  { id_Inter_SystemInformationTransferTypeEDT, "id-Inter-SystemInformationTransferTypeEDT" },
  { id_Inter_SystemInformationTransferTypeMDT, "id-Inter-SystemInformationTransferTypeMDT" },
  { id_Target_ToSource_TransparentContainer, "id-Target-ToSource-TransparentContainer" },
  { id_SRVCCOperationPossible, "id-SRVCCOperationPossible" },
  { id_SRVCCHOIndication, "id-SRVCCHOIndication" },
  { id_NAS_DownlinkCount, "id-NAS-DownlinkCount" },
  { id_CSG_Id, "id-CSG-Id" },
  { id_CSG_IdList, "id-CSG-IdList" },
  { id_SONConfigurationTransferECT, "id-SONConfigurationTransferECT" },
  { id_SONConfigurationTransferMCT, "id-SONConfigurationTransferMCT" },
  { id_TraceCollectionEntityIPAddress, "id-TraceCollectionEntityIPAddress" },
  { id_MSClassmark2, "id-MSClassmark2" },
  { id_MSClassmark3, "id-MSClassmark3" },
  { id_RRC_Establishment_Cause, "id-RRC-Establishment-Cause" },
  { id_NASSecurityParametersfromE_UTRAN, "id-NASSecurityParametersfromE-UTRAN" },
  { id_NASSecurityParameterstoE_UTRAN, "id-NASSecurityParameterstoE-UTRAN" },
  { id_DefaultPagingDRX, "id-DefaultPagingDRX" },
  { id_Source_ToTarget_TransparentContainer_Secondary, "id-Source-ToTarget-TransparentContainer-Secondary" },
  { id_Target_ToSource_TransparentContainer_Secondary, "id-Target-ToSource-TransparentContainer-Secondary" },
  { id_EUTRANRoundTripDelayEstimationInfo, "id-EUTRANRoundTripDelayEstimationInfo" },
  { id_BroadcastCancelledAreaList, "id-BroadcastCancelledAreaList" },
  { id_ConcurrentWarningMessageIndicator, "id-ConcurrentWarningMessageIndicator" },
  { id_Data_Forwarding_Not_Possible, "id-Data-Forwarding-Not-Possible" },
  { id_ExtendedRepetitionPeriod, "id-ExtendedRepetitionPeriod" },
  { id_CellAccessMode, "id-CellAccessMode" },
  { id_CSGMembershipStatus, "id-CSGMembershipStatus" },
  { id_LPPa_PDU, "id-LPPa-PDU" },
  { id_Routing_ID, "id-Routing-ID" },
  { id_Time_Synchronisation_Info, "id-Time-Synchronisation-Info" },
  { id_PS_ServiceNotAvailable, "id-PS-ServiceNotAvailable" },
  { id_PagingPriority, "id-PagingPriority" },
  { id_x2TNLConfigurationInfo, "id-x2TNLConfigurationInfo" },
  { id_eNBX2ExtendedTransportLayerAddresses, "id-eNBX2ExtendedTransportLayerAddresses" },
  { id_GUMMEIList, "id-GUMMEIList" },
  { id_GW_TransportLayerAddress, "id-GW-TransportLayerAddress" },
  { id_Correlation_ID, "id-Correlation-ID" },
  { id_SourceMME_GUMMEI, "id-SourceMME-GUMMEI" },
  { id_MME_UE_S1AP_ID_2, "id-MME-UE-S1AP-ID-2" },
  { id_RegisteredLAI, "id-RegisteredLAI" },
  { id_RelayNode_Indicator, "id-RelayNode-Indicator" },
  { id_TrafficLoadReductionIndication, "id-TrafficLoadReductionIndication" },
  { id_MDTConfiguration, "id-MDTConfiguration" },
  { id_MMERelaySupportIndicator, "id-MMERelaySupportIndicator" },
  { id_GWContextReleaseIndication, "id-GWContextReleaseIndication" },
  { id_ManagementBasedMDTAllowed, "id-ManagementBasedMDTAllowed" },
  { id_PrivacyIndicator, "id-PrivacyIndicator" },
  { id_Time_UE_StayedInCell_EnhancedGranularity, "id-Time-UE-StayedInCell-EnhancedGranularity" },
  { id_HO_Cause, "id-HO-Cause" },
  { id_VoiceSupportMatchIndicator, "id-VoiceSupportMatchIndicator" },
  { id_GUMMEIType, "id-GUMMEIType" },
  { id_M3Configuration, "id-M3Configuration" },
  { id_M4Configuration, "id-M4Configuration" },
  { id_M5Configuration, "id-M5Configuration" },
  { id_MDT_Location_Info, "id-MDT-Location-Info" },
  { id_MobilityInformation, "id-MobilityInformation" },
  { id_Tunnel_Information_for_BBF, "id-Tunnel-Information-for-BBF" },
  { id_ManagementBasedMDTPLMNList, "id-ManagementBasedMDTPLMNList" },
  { id_SignallingBasedMDTPLMNList, "id-SignallingBasedMDTPLMNList" },
  { id_ULCOUNTValueExtended, "id-ULCOUNTValueExtended" },
  { id_DLCOUNTValueExtended, "id-DLCOUNTValueExtended" },
  { id_ReceiveStatusOfULPDCPSDUsExtended, "id-ReceiveStatusOfULPDCPSDUsExtended" },
  { id_ECGIListForRestart, "id-ECGIListForRestart" },
  { id_SIPTO_Correlation_ID, "id-SIPTO-Correlation-ID" },
  { id_SIPTO_L_GW_TransportLayerAddress, "id-SIPTO-L-GW-TransportLayerAddress" },
  { id_TransportInformation, "id-TransportInformation" },
  { id_LHN_ID, "id-LHN-ID" },
  { id_AdditionalCSFallbackIndicator, "id-AdditionalCSFallbackIndicator" },
  { id_TAIListForRestart, "id-TAIListForRestart" },
  { id_UserLocationInformation, "id-UserLocationInformation" },
  { id_EmergencyAreaIDListForRestart, "id-EmergencyAreaIDListForRestart" },
  { id_KillAllWarningMessages, "id-KillAllWarningMessages" },
  { id_Masked_IMEISV, "id-Masked-IMEISV" },
  { id_eNBIndirectX2TransportLayerAddresses, "id-eNBIndirectX2TransportLayerAddresses" },
  { id_uE_HistoryInformationFromTheUE, "id-uE-HistoryInformationFromTheUE" },
  { id_ProSeAuthorized, "id-ProSeAuthorized" },
  { id_ExpectedUEBehaviour, "id-ExpectedUEBehaviour" },
  { id_LoggedMBSFNMDT, "id-LoggedMBSFNMDT" },
  { id_UERadioCapabilityForPaging, "id-UERadioCapabilityForPaging" },
  { id_E_RABToBeModifiedListBearerModInd, "id-E-RABToBeModifiedListBearerModInd" },
  { id_E_RABToBeModifiedItemBearerModInd, "id-E-RABToBeModifiedItemBearerModInd" },
  { id_E_RABNotToBeModifiedListBearerModInd, "id-E-RABNotToBeModifiedListBearerModInd" },
  { id_E_RABNotToBeModifiedItemBearerModInd, "id-E-RABNotToBeModifiedItemBearerModInd" },
  { id_E_RABModifyListBearerModConf, "id-E-RABModifyListBearerModConf" },
  { id_E_RABModifyItemBearerModConf, "id-E-RABModifyItemBearerModConf" },
  { id_E_RABFailedToModifyListBearerModConf, "id-E-RABFailedToModifyListBearerModConf" },
  { id_SON_Information_Report, "id-SON-Information-Report" },
  { id_Muting_Availability_Indication, "id-Muting-Availability-Indication" },
  { id_Muting_Pattern_Information, "id-Muting-Pattern-Information" },
  { id_Synchronisation_Information, "id-Synchronisation-Information" },
  { id_E_RABToBeReleasedListBearerModConf, "id-E-RABToBeReleasedListBearerModConf" },
  { id_AssistanceDataForPaging, "id-AssistanceDataForPaging" },
  { id_CellIdentifierAndCELevelForCECapableUEs, "id-CellIdentifierAndCELevelForCECapableUEs" },
  { id_InformationOnRecommendedCellsAndENBsForPaging, "id-InformationOnRecommendedCellsAndENBsForPaging" },
  { id_RecommendedCellItem, "id-RecommendedCellItem" },
  { id_RecommendedENBItem, "id-RecommendedENBItem" },
  { id_ProSeUEtoNetworkRelaying, "id-ProSeUEtoNetworkRelaying" },
  { id_ULCOUNTValuePDCP_SNlength18, "id-ULCOUNTValuePDCP-SNlength18" },
  { id_DLCOUNTValuePDCP_SNlength18, "id-DLCOUNTValuePDCP-SNlength18" },
  { id_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18, "id-ReceiveStatusOfULPDCPSDUsPDCP-SNlength18" },
  { id_M6Configuration, "id-M6Configuration" },
  { id_M7Configuration, "id-M7Configuration" },
  { id_PWSfailedECGIList, "id-PWSfailedECGIList" },
  { id_MME_Group_ID, "id-MME-Group-ID" },
  { id_Additional_GUTI, "id-Additional-GUTI" },
  { id_S1_Message, "id-S1-Message" },
  { id_CSGMembershipInfo, "id-CSGMembershipInfo" },
  { id_Paging_eDRXInformation, "id-Paging-eDRXInformation" },
  { id_UE_RetentionInformation, "id-UE-RetentionInformation" },
  { id_Unknown_229, "id-Unknown-229" },
  { id_UE_Usage_Type, "id-UE-Usage-Type" },
  { id_extended_UEIdentityIndexValue, "id-extended-UEIdentityIndexValue" },
  { id_RAT_Type, "id-RAT-Type" },
  { id_BearerType, "id-BearerType" },
  { id_NB_IoT_DefaultPagingDRX, "id-NB-IoT-DefaultPagingDRX" },
  { id_E_RABFailedToResumeListResumeReq, "id-E-RABFailedToResumeListResumeReq" },
  { id_E_RABFailedToResumeItemResumeReq, "id-E-RABFailedToResumeItemResumeReq" },
  { id_E_RABFailedToResumeListResumeRes, "id-E-RABFailedToResumeListResumeRes" },
  { id_E_RABFailedToResumeItemResumeRes, "id-E-RABFailedToResumeItemResumeRes" },
  { id_NB_IoT_Paging_eDRXInformation, "id-NB-IoT-Paging-eDRXInformation" },
  { id_V2XServicesAuthorized, "id-V2XServicesAuthorized" },
  { id_UEUserPlaneCIoTSupportIndicator, "id-UEUserPlaneCIoTSupportIndicator" },
  { id_CE_mode_B_SupportIndicator, "id-CE-mode-B-SupportIndicator" },
  { id_SRVCCOperationNotPossible, "id-SRVCCOperationNotPossible" },
  { id_NB_IoT_UEIdentityIndexValue, "id-NB-IoT-UEIdentityIndexValue" },
  { id_RRC_Resume_Cause, "id-RRC-Resume-Cause" },
  { id_DCN_ID, "id-DCN-ID" },
  { id_ServedDCNs, "id-ServedDCNs" },
  { id_UESidelinkAggregateMaximumBitrate, "id-UESidelinkAggregateMaximumBitrate" },
  { id_DLNASPDUDeliveryAckRequest, "id-DLNASPDUDeliveryAckRequest" },
  { id_Coverage_Level, "id-Coverage-Level" },
  { id_EnhancedCoverageRestricted, "id-EnhancedCoverageRestricted" },
  { id_UE_Level_QoS_Parameters, "id-UE-Level-QoS-Parameters" },
  { id_DL_CP_SecurityInformation, "id-DL-CP-SecurityInformation" },
  { id_UL_CP_SecurityInformation, "id-UL-CP-SecurityInformation" },
  { id_extended_e_RAB_MaximumBitrateDL, "id-extended-e-RAB-MaximumBitrateDL" },
  { id_extended_e_RAB_MaximumBitrateUL, "id-extended-e-RAB-MaximumBitrateUL" },
  { id_extended_e_RAB_GuaranteedBitrateDL, "id-extended-e-RAB-GuaranteedBitrateDL" },
  { id_extended_e_RAB_GuaranteedBitrateUL, "id-extended-e-RAB-GuaranteedBitrateUL" },
  { id_extended_uEaggregateMaximumBitRateDL, "id-extended-uEaggregateMaximumBitRateDL" },
  { id_extended_uEaggregateMaximumBitRateUL, "id-extended-uEaggregateMaximumBitRateUL" },
  { id_NRrestrictioninEPSasSecondaryRAT, "id-NRrestrictioninEPSasSecondaryRAT" },
  { id_UEAppLayerMeasConfig, "id-UEAppLayerMeasConfig" },
  { id_UE_Application_Layer_Measurement_Capability, "id-UE-Application-Layer-Measurement-Capability" },
  { id_SecondaryRATDataUsageReportList, "id-SecondaryRATDataUsageReportList" },
  { id_SecondaryRATDataUsageReportItem, "id-SecondaryRATDataUsageReportItem" },
  { id_HandoverFlag, "id-HandoverFlag" },
  { id_E_RABUsageReportItem, "id-E-RABUsageReportItem" },
  { id_SecondaryRATDataUsageRequest, "id-SecondaryRATDataUsageRequest" },
  { id_NRUESecurityCapabilities, "id-NRUESecurityCapabilities" },
  { id_UnlicensedSpectrumRestriction, "id-UnlicensedSpectrumRestriction" },
  { id_CE_ModeBRestricted, "id-CE-ModeBRestricted" },
  { id_LTE_M_Indication, "id-LTE-M-Indication" },
  { id_DownlinkPacketLossRate, "id-DownlinkPacketLossRate" },
  { id_UplinkPacketLossRate, "id-UplinkPacketLossRate" },
  { id_UECapabilityInfoRequest, "id-UECapabilityInfoRequest" },
  { id_serviceType, "id-serviceType" },
  { id_AerialUEsubscriptionInformation, "id-AerialUEsubscriptionInformation" },
  { id_Subscription_Based_UE_DifferentiationInfo, "id-Subscription-Based-UE-DifferentiationInfo" },
  { id_Unknown_279, "id-Unknown-279" },
  { id_EndIndication, "id-EndIndication" },
  { id_EDT_Session, "id-EDT-Session" },
  { id_CNTypeRestrictions, "id-CNTypeRestrictions" },
  { id_PendingDataIndication, "id-PendingDataIndication" },
  { id_BluetoothMeasurementConfiguration, "id-BluetoothMeasurementConfiguration" },
  { id_WLANMeasurementConfiguration, "id-WLANMeasurementConfiguration" },
  { id_WarningAreaCoordinates, "id-WarningAreaCoordinates" },
  { id_NRrestrictionin5GS, "id-NRrestrictionin5GS" },
  { id_PSCellInformation, "id-PSCellInformation" },
  { id_Unknown_289, "id-Unknown-289" },
  { id_LastNG_RANPLMNIdentity, "id-LastNG-RANPLMNIdentity" },
  { id_ConnectedengNBList, "id-ConnectedengNBList" },
  { id_ConnectedengNBToAddList, "id-ConnectedengNBToAddList" },
  { id_ConnectedengNBToRemoveList, "id-ConnectedengNBToRemoveList" },
  { id_EN_DCSONConfigurationTransfer_ECT, "id-EN-DCSONConfigurationTransfer-ECT" },
  { id_EN_DCSONConfigurationTransfer_MCT, "id-EN-DCSONConfigurationTransfer-MCT" },
  { id_IMSvoiceEPSfallbackfrom5G, "id-IMSvoiceEPSfallbackfrom5G" },
  { id_TimeSinceSecondaryNodeRelease, "id-TimeSinceSecondaryNodeRelease" },
  { id_RequestTypeAdditionalInfo, "id-RequestTypeAdditionalInfo" },
  { id_AdditionalRRMPriorityIndex, "id-AdditionalRRMPriorityIndex" },
  { id_ContextatSource, "id-ContextatSource" },
  { id_IAB_Authorized, "id-IAB-Authorized" },
  { id_IAB_Node_Indication, "id-IAB-Node-Indication" },
  { id_IAB_Supported, "id-IAB-Supported" },
  { id_DataSize, "id-DataSize" },
  { id_Ethernet_Type, "id-Ethernet-Type" },
  { id_NRV2XServicesAuthorized, "id-NRV2XServicesAuthorized" },
  { id_NRUESidelinkAggregateMaximumBitrate, "id-NRUESidelinkAggregateMaximumBitrate" },
  { id_PC5QoSParameters, "id-PC5QoSParameters" },
  { id_IntersystemSONConfigurationTransferMCT, "id-IntersystemSONConfigurationTransferMCT" },
  { id_IntersystemSONConfigurationTransferECT, "id-IntersystemSONConfigurationTransferECT" },
  { id_IntersystemMeasurementConfiguration, "id-IntersystemMeasurementConfiguration" },
  { id_SourceNodeID, "id-SourceNodeID" },
  { id_NB_IoT_RLF_Report_Container, "id-NB-IoT-RLF-Report-Container" },
  { id_UERadioCapabilityID, "id-UERadioCapabilityID" },
  { id_UERadioCapability_NR_Format, "id-UERadioCapability-NR-Format" },
  { id_MDTConfigurationNR, "id-MDTConfigurationNR" },
  { id_DAPSRequestInfo, "id-DAPSRequestInfo" },
  { id_DAPSResponseInfoList, "id-DAPSResponseInfoList" },
  { id_DAPSResponseInfoItem, "id-DAPSResponseInfoItem" },
  { id_NotifySourceeNB, "id-NotifySourceeNB" },
  { id_eNB_EarlyStatusTransfer_TransparentContainer, "id-eNB-EarlyStatusTransfer-TransparentContainer" },
  { id_Bearers_SubjectToEarlyStatusTransfer_Item, "id-Bearers-SubjectToEarlyStatusTransfer-Item" },
  { id_WUS_Assistance_Information, "id-WUS-Assistance-Information" },
  { id_NB_IoT_PagingDRX, "id-NB-IoT-PagingDRX" },
  { id_TraceCollectionEntityURI, "id-TraceCollectionEntityURI" },
  { id_EmergencyIndicator, "id-EmergencyIndicator" },
  { 0, NULL }
};

static value_string_ext s1ap_ProtocolIE_ID_vals_ext = VALUE_STRING_EXT_INIT(s1ap_ProtocolIE_ID_vals);


static int
dissect_s1ap_ProtocolIE_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 121 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, &s1ap_data->protocol_ie_id, FALSE);




#line 125 "./asn1/s1ap/s1ap.cnf"
  if (tree) {
    proto_item_append_text(proto_item_get_parent_nth(actx->created_item, 2), ": %s",
                           val_to_str_ext(s1ap_data->protocol_ie_id, &s1ap_ProtocolIE_ID_vals_ext, "unknown (%d)"));
  }

  return offset;
}


static const value_string s1ap_TriggeringMessage_vals[] = {
  {   0, "initiating-message" },
  {   1, "successful-outcome" },
  {   2, "unsuccessfull-outcome" },
  { 0, NULL }
};


static int
dissect_s1ap_TriggeringMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_T_ie_field_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_ProtocolIEFieldValue);

  return offset;
}


static const per_sequence_t ProtocolIE_Field_sequence[] = {
  { &hf_s1ap_id             , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_ID },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_ie_field_value , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_T_ie_field_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ProtocolIE_Field(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ProtocolIE_Field, ProtocolIE_Field_sequence);

  return offset;
}


static const per_sequence_t ProtocolIE_Container_sequence_of[1] = {
  { &hf_s1ap_ProtocolIE_Container_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Field },
};

static int
dissect_s1ap_ProtocolIE_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ProtocolIE_Container, ProtocolIE_Container_sequence_of,
                                                  0, maxProtocolIEs, FALSE);

  return offset;
}



static int
dissect_s1ap_ProtocolIE_SingleContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_ProtocolIE_Field(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t ProtocolIE_ContainerList_sequence_of[1] = {
  { &hf_s1ap_ProtocolIE_ContainerList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_ProtocolIE_ContainerList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 172 "./asn1/s1ap/s1ap.cnf"
  static const asn1_par_def_t ProtocolIE_ContainerList_pars[] = {
    { "lowerBound", ASN1_PAR_INTEGER },
    { "upperBound", ASN1_PAR_INTEGER },
    { NULL, (asn1_par_type)0 }
  };
  asn1_stack_frame_check(actx, "ProtocolIE-ContainerList", ProtocolIE_ContainerList_pars);

  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ProtocolIE_ContainerList, ProtocolIE_ContainerList_sequence_of,
                                                  asn1_param_get_integer(actx,"lowerBound"), asn1_param_get_integer(actx,"upperBound"), FALSE);

  return offset;
}



static int
dissect_s1ap_T_extensionValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_ProtocolExtensionFieldExtensionValue);

  return offset;
}


static const per_sequence_t ProtocolExtensionField_sequence[] = {
  { &hf_s1ap_ext_id         , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolExtensionID },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_extensionValue , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_T_extensionValue },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ProtocolExtensionField(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ProtocolExtensionField, ProtocolExtensionField_sequence);

  return offset;
}


static const per_sequence_t ProtocolExtensionContainer_sequence_of[1] = {
  { &hf_s1ap_ProtocolExtensionContainer_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolExtensionField },
};

static int
dissect_s1ap_ProtocolExtensionContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ProtocolExtensionContainer, ProtocolExtensionContainer_sequence_of,
                                                  1, maxProtocolExtensions, FALSE);

  return offset;
}



static int
dissect_s1ap_T_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 235 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  if (s1ap_data->obj_id) {
    offset = call_per_oid_callback(s1ap_data->obj_id, tvb, actx->pinfo, tree, offset, actx, hf_index);
  } else {
  offset = dissect_per_open_type(tvb, offset, actx, tree, hf_index, NULL);

  }





  return offset;
}


static const per_sequence_t PrivateIE_Field_sequence[] = {
  { &hf_s1ap_private_id     , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PrivateIE_ID },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_value          , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_T_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PrivateIE_Field(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PrivateIE_Field, PrivateIE_Field_sequence);

  return offset;
}


static const per_sequence_t PrivateIE_Container_sequence_of[1] = {
  { &hf_s1ap_PrivateIE_Container_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PrivateIE_Field },
};

static int
dissect_s1ap_PrivateIE_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_PrivateIE_Container, PrivateIE_Container_sequence_of,
                                                  1, maxPrivateIEs, FALSE);

  return offset;
}




static int
dissect_s1ap_PLMNidentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 248 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb=NULL;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  e212_number_type_t number_type = s1ap_data->number_type;
  s1ap_data->number_type = E212_NONE;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 3, FALSE, &parameter_tvb);
  if(tvb_reported_length(tvb)==0)
    return offset;

  if (!parameter_tvb)
    return offset;
  dissect_e212_mcc_mnc(parameter_tvb, actx->pinfo, tree, 0, number_type, FALSE);
  if (s1ap_data->supported_ta) {
    guint32 plmn = tvb_get_ntoh24(parameter_tvb, 0);
    wmem_array_append_one(s1ap_data->supported_ta->plmn, plmn);
  } else if (s1ap_data->tai) {
    s1ap_data->tai->plmn = tvb_get_ntoh24(parameter_tvb, 0);
  }


  return offset;
}



static int
dissect_s1ap_MME_Group_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1022 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_MME_Code(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1013 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       1, 1, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 1, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const per_sequence_t GUMMEI_sequence[] = {
  { &hf_s1ap_pLMN_Identity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_mME_Group_ID   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_Group_ID },
  { &hf_s1ap_mME_Code       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_Code },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_GUMMEI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1006 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_GUMMEI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_GUMMEI, GUMMEI_sequence);




  return offset;
}



static int
dissect_s1ap_M_TMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1361 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  proto_item *ti;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       4, 4, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 4, ENC_BIG_ENDIAN);
    ti = proto_tree_add_item(tree, hf_3gpp_tmsi, tvb, 0, 4, ENC_BIG_ENDIAN);
    proto_item_set_hidden(ti);

  }



  return offset;
}


static const per_sequence_t Additional_GUTI_sequence[] = {
  { &hf_s1ap_gUMMEI         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GUMMEI },
  { &hf_s1ap_m_TMSI         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M_TMSI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Additional_GUTI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Additional_GUTI, Additional_GUTI_sequence);

  return offset;
}



static int
dissect_s1ap_AdditionalRRMPriorityIndex(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string s1ap_AerialUEsubscriptionInformation_vals[] = {
  {   0, "allowed" },
  {   1, "not-allowed" },
  { 0, NULL }
};


static int
dissect_s1ap_AerialUEsubscriptionInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_CellIdentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2623 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *cell_id_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, -1,
                                     28, 28, FALSE, NULL, 0, &cell_id_tvb, NULL);

  if (cell_id_tvb) {
    guint32 cell_id = tvb_get_bits32(cell_id_tvb, 0, 28, ENC_BIG_ENDIAN);
    actx->created_item = proto_tree_add_uint(tree, hf_index, cell_id_tvb, 0, 4, cell_id);
  }


  return offset;
}


static const per_sequence_t EUTRAN_CGI_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_cell_ID        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellIdentity },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EUTRAN_CGI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2616 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_ECGI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EUTRAN_CGI, EUTRAN_CGI_sequence);




  return offset;
}


static const per_sequence_t CellIdListforMDT_sequence_of[1] = {
  { &hf_s1ap_CellIdListforMDT_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_CellIdListforMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CellIdListforMDT, CellIdListforMDT_sequence_of,
                                                  1, maxnoofCellIDforMDT, FALSE);

  return offset;
}


static const per_sequence_t CellBasedMDT_sequence[] = {
  { &hf_s1ap_cellIdListforMDT, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellIdListforMDT },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellBasedMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellBasedMDT, CellBasedMDT_sequence);

  return offset;
}



static int
dissect_s1ap_TAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1309 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
    if (s1ap_data->supported_ta) {
      s1ap_data->supported_ta->tac = tvb_get_ntohs(parameter_tvb, 0);
    } else if (s1ap_data->tai) {
      s1ap_data->tai->tac = tvb_get_ntohs(parameter_tvb, 0);
    }
  }



  return offset;
}


static const per_sequence_t TAListforMDT_sequence_of[1] = {
  { &hf_s1ap_TAListforMDT_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAC },
};

static int
dissect_s1ap_TAListforMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAListforMDT, TAListforMDT_sequence_of,
                                                  1, maxnoofTAforMDT, FALSE);

  return offset;
}


static const per_sequence_t TABasedMDT_sequence[] = {
  { &hf_s1ap_tAListforMDT   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAListforMDT },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TABasedMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TABasedMDT, TABasedMDT_sequence);

  return offset;
}



static int
dissect_s1ap_NULL(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_null(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t TAI_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_tAC            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1446 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_TAI;
  s1ap_data->tai = wmem_new0(actx->pinfo->pool, struct s1ap_tai);
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAI, TAI_sequence);

  if (!PINFO_FD_VISITED(actx->pinfo) && s1ap_data->s1ap_conv &&
      (s1ap_data->message_type == INITIATING_MESSAGE) &&
      (s1ap_data->procedure_code == id_initialUEMessage)) {
    guint64 key = (s1ap_data->tai->plmn << 16) | s1ap_data->tai->tac;

    if (wmem_map_lookup(s1ap_data->s1ap_conv->nbiot_ta, &key)) {
      wmem_tree_key_t tree_key[3];
      guint32 *id = wmem_new(wmem_file_scope(), guint32);

      *id = s1ap_data->enb_ue_s1ap_id;
      tree_key[0].length = 1;
      tree_key[0].key = id;
      tree_key[1].length = 1;
      tree_key[1].key = &actx->pinfo->num;
      tree_key[2].length = 0;
      tree_key[2].key = NULL;
      wmem_tree_insert32_array(s1ap_data->s1ap_conv->nbiot_enb_ue_s1ap_id, tree_key, id);
    }
  }



  return offset;
}


static const per_sequence_t TAIListforMDT_sequence_of[1] = {
  { &hf_s1ap_TAIListforMDT_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
};

static int
dissect_s1ap_TAIListforMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAIListforMDT, TAIListforMDT_sequence_of,
                                                  1, maxnoofTAforMDT, FALSE);

  return offset;
}


static const per_sequence_t TAIBasedMDT_sequence[] = {
  { &hf_s1ap_tAIListforMDT  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAIListforMDT },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAIBasedMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAIBasedMDT, TAIBasedMDT_sequence);

  return offset;
}


static const value_string s1ap_AreaScopeOfMDT_vals[] = {
  {   0, "cellBased" },
  {   1, "tABased" },
  {   2, "pLMNWide" },
  {   3, "tAIBased" },
  { 0, NULL }
};

static const per_choice_t AreaScopeOfMDT_choice[] = {
  {   0, &hf_s1ap_cellBased      , ASN1_EXTENSION_ROOT    , dissect_s1ap_CellBasedMDT },
  {   1, &hf_s1ap_tABased        , ASN1_EXTENSION_ROOT    , dissect_s1ap_TABasedMDT },
  {   2, &hf_s1ap_pLMNWide       , ASN1_EXTENSION_ROOT    , dissect_s1ap_NULL },
  {   3, &hf_s1ap_tAIBased       , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_TAIBasedMDT },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_AreaScopeOfMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_AreaScopeOfMDT, AreaScopeOfMDT_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CellIdListforQMC_sequence_of[1] = {
  { &hf_s1ap_CellIdListforQMC_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_CellIdListforQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CellIdListforQMC, CellIdListforQMC_sequence_of,
                                                  1, maxnoofCellIDforQMC, FALSE);

  return offset;
}


static const per_sequence_t CellBasedQMC_sequence[] = {
  { &hf_s1ap_cellIdListforQMC, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellIdListforQMC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellBasedQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellBasedQMC, CellBasedQMC_sequence);

  return offset;
}


static const per_sequence_t TAListforQMC_sequence_of[1] = {
  { &hf_s1ap_TAListforQMC_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAC },
};

static int
dissect_s1ap_TAListforQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAListforQMC, TAListforQMC_sequence_of,
                                                  1, maxnoofTAforQMC, FALSE);

  return offset;
}


static const per_sequence_t TABasedQMC_sequence[] = {
  { &hf_s1ap_tAListforQMC   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAListforQMC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TABasedQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TABasedQMC, TABasedQMC_sequence);

  return offset;
}


static const per_sequence_t TAIListforQMC_sequence_of[1] = {
  { &hf_s1ap_TAIListforQMC_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
};

static int
dissect_s1ap_TAIListforQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAIListforQMC, TAIListforQMC_sequence_of,
                                                  1, maxnoofTAforQMC, FALSE);

  return offset;
}


static const per_sequence_t TAIBasedQMC_sequence[] = {
  { &hf_s1ap_tAIListforQMC  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAIListforQMC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAIBasedQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAIBasedQMC, TAIBasedQMC_sequence);

  return offset;
}


static const per_sequence_t PLMNListforQMC_sequence_of[1] = {
  { &hf_s1ap_PLMNListforQMC_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
};

static int
dissect_s1ap_PLMNListforQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_PLMNListforQMC, PLMNListforQMC_sequence_of,
                                                  1, maxnoofPLMNforQMC, FALSE);

  return offset;
}


static const per_sequence_t PLMNAreaBasedQMC_sequence[] = {
  { &hf_s1ap_plmnListforQMC , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNListforQMC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PLMNAreaBasedQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PLMNAreaBasedQMC, PLMNAreaBasedQMC_sequence);

  return offset;
}


static const value_string s1ap_AreaScopeOfQMC_vals[] = {
  {   0, "cellBased" },
  {   1, "tABased" },
  {   2, "tAIBased" },
  {   3, "pLMNAreaBased" },
  { 0, NULL }
};

static const per_choice_t AreaScopeOfQMC_choice[] = {
  {   0, &hf_s1ap_cellBased_01   , ASN1_EXTENSION_ROOT    , dissect_s1ap_CellBasedQMC },
  {   1, &hf_s1ap_tABased_01     , ASN1_EXTENSION_ROOT    , dissect_s1ap_TABasedQMC },
  {   2, &hf_s1ap_tAIBased_01    , ASN1_EXTENSION_ROOT    , dissect_s1ap_TAIBasedQMC },
  {   3, &hf_s1ap_pLMNAreaBased  , ASN1_EXTENSION_ROOT    , dissect_s1ap_PLMNAreaBasedQMC },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_AreaScopeOfQMC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_AreaScopeOfQMC, AreaScopeOfQMC_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_PriorityLevel_vals[] = {
  {   0, "spare" },
  {   1, "highest" },
  {  14, "lowest" },
  {  15, "no-priority" },
  { 0, NULL }
};


static int
dissect_s1ap_PriorityLevel(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 15U, NULL, FALSE);

  return offset;
}


static const value_string s1ap_Pre_emptionCapability_vals[] = {
  {   0, "shall-not-trigger-pre-emption" },
  {   1, "may-trigger-pre-emption" },
  { 0, NULL }
};


static int
dissect_s1ap_Pre_emptionCapability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string s1ap_Pre_emptionVulnerability_vals[] = {
  {   0, "not-pre-emptable" },
  {   1, "pre-emptable" },
  { 0, NULL }
};


static int
dissect_s1ap_Pre_emptionVulnerability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t AllocationAndRetentionPriority_sequence[] = {
  { &hf_s1ap_priorityLevel  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PriorityLevel },
  { &hf_s1ap_pre_emptionCapability, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Pre_emptionCapability },
  { &hf_s1ap_pre_emptionVulnerability, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Pre_emptionVulnerability },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_AllocationAndRetentionPriority(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_AllocationAndRetentionPriority, AllocationAndRetentionPriority_sequence);

  return offset;
}



static int
dissect_s1ap_CELevel(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 794 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_CELevel);
    if ((s1ap_is_nbiot_ue(actx->pinfo) && (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_AUTOMATIC)) ||
        (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_NBIOT)) {
      TRY {
        dissect_lte_rrc_UEPagingCoverageInformation_NB_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      }
      CATCH_BOUNDS_ERRORS {
        show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
      }
      ENDTRY;
    } else {
      TRY {
        dissect_lte_rrc_UEPagingCoverageInformation_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      }
      CATCH_BOUNDS_ERRORS {
        show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
      }
      ENDTRY;
    }
  }



  return offset;
}


static const per_sequence_t CellIdentifierAndCELevelForCECapableUEs_sequence[] = {
  { &hf_s1ap_global_Cell_ID , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_cELevel        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CELevel },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellIdentifierAndCELevelForCECapableUEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellIdentifierAndCELevelForCECapableUEs, CellIdentifierAndCELevelForCECapableUEs_sequence);

  return offset;
}


static const per_sequence_t AssistanceDataForCECapableUEs_sequence[] = {
  { &hf_s1ap_cellIdentifierAndCELevelForCECapableUEs, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellIdentifierAndCELevelForCECapableUEs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_AssistanceDataForCECapableUEs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_AssistanceDataForCECapableUEs, AssistanceDataForCECapableUEs_sequence);

  return offset;
}


static const per_sequence_t RecommendedCellList_sequence_of[1] = {
  { &hf_s1ap_RecommendedCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_RecommendedCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_RecommendedCellList, RecommendedCellList_sequence_of,
                                                  1, maxnoofRecommendedCells, FALSE);

  return offset;
}


static const per_sequence_t RecommendedCellsForPaging_sequence[] = {
  { &hf_s1ap_recommendedCellList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RecommendedCellList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RecommendedCellsForPaging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RecommendedCellsForPaging, RecommendedCellsForPaging_sequence);

  return offset;
}


static const per_sequence_t AssistanceDataForRecommendedCells_sequence[] = {
  { &hf_s1ap_recommendedCellsForPaging, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RecommendedCellsForPaging },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_AssistanceDataForRecommendedCells(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_AssistanceDataForRecommendedCells, AssistanceDataForRecommendedCells_sequence);

  return offset;
}



static int
dissect_s1ap_PagingAttemptCount(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 16U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_IntendedNumberOfPagingAttempts(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 16U, NULL, TRUE);

  return offset;
}


static const value_string s1ap_NextPagingAreaScope_vals[] = {
  {   0, "same" },
  {   1, "changed" },
  { 0, NULL }
};


static int
dissect_s1ap_NextPagingAreaScope(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t PagingAttemptInformation_sequence[] = {
  { &hf_s1ap_pagingAttemptCount, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PagingAttemptCount },
  { &hf_s1ap_intendedNumberOfPagingAttempts, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_IntendedNumberOfPagingAttempts },
  { &hf_s1ap_nextPagingAreaScope, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_NextPagingAreaScope },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PagingAttemptInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PagingAttemptInformation, PagingAttemptInformation_sequence);

  return offset;
}


static const per_sequence_t AssistanceDataForPaging_sequence[] = {
  { &hf_s1ap_assistanceDataForRecommendedCells, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_AssistanceDataForRecommendedCells },
  { &hf_s1ap_assistanceDataForCECapableUEs, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_AssistanceDataForCECapableUEs },
  { &hf_s1ap_pagingAttemptInformation, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PagingAttemptInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_AssistanceDataForPaging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_AssistanceDataForPaging, AssistanceDataForPaging_sequence);

  return offset;
}


static const per_sequence_t Bearers_SubjectToStatusTransferList_sequence_of[1] = {
  { &hf_s1ap_Bearers_SubjectToStatusTransferList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_Bearers_SubjectToStatusTransferList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_Bearers_SubjectToStatusTransferList, Bearers_SubjectToStatusTransferList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}



static int
dissect_s1ap_E_RAB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 15U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_PDCP_SN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_HFN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1048575U, NULL, FALSE);

  return offset;
}


static const per_sequence_t COUNTvalue_sequence[] = {
  { &hf_s1ap_pDCP_SN        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PDCP_SN },
  { &hf_s1ap_hFN            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_HFN },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_COUNTvalue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_COUNTvalue, COUNTvalue_sequence);

  return offset;
}



static int
dissect_s1ap_ReceiveStatusofULPDCPSDUs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     4096, 4096, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t Bearers_SubjectToStatusTransfer_Item_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_uL_COUNTvalue  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_COUNTvalue },
  { &hf_s1ap_dL_COUNTvalue  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_COUNTvalue },
  { &hf_s1ap_receiveStatusofULPDCPSDUs, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ReceiveStatusofULPDCPSDUs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Bearers_SubjectToStatusTransfer_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Bearers_SubjectToStatusTransfer_Item, Bearers_SubjectToStatusTransfer_Item_sequence);

  return offset;
}


static const per_sequence_t Bearers_SubjectToEarlyStatusTransferList_sequence_of[1] = {
  { &hf_s1ap_Bearers_SubjectToEarlyStatusTransferList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_Bearers_SubjectToEarlyStatusTransferList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_Bearers_SubjectToEarlyStatusTransferList, Bearers_SubjectToEarlyStatusTransferList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}



static int
dissect_s1ap_PDCP_SNExtended(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 32767U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_HFNModified(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 131071U, NULL, FALSE);

  return offset;
}


static const per_sequence_t COUNTValueExtended_sequence[] = {
  { &hf_s1ap_pDCP_SNExtended, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PDCP_SNExtended },
  { &hf_s1ap_hFNModified    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_HFNModified },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_COUNTValueExtended(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_COUNTValueExtended, COUNTValueExtended_sequence);

  return offset;
}



static int
dissect_s1ap_PDCP_SNlength18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 262143U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_HFNforPDCP_SNlength18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 16383U, NULL, FALSE);

  return offset;
}


static const per_sequence_t COUNTvaluePDCP_SNlength18_sequence[] = {
  { &hf_s1ap_pDCP_SNlength18, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PDCP_SNlength18 },
  { &hf_s1ap_hFNforPDCP_SNlength18, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_HFNforPDCP_SNlength18 },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_COUNTvaluePDCP_SNlength18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_COUNTvaluePDCP_SNlength18, COUNTvaluePDCP_SNlength18_sequence);

  return offset;
}


static const value_string s1ap_DLCOUNT_PDCP_SNlength_vals[] = {
  {   0, "dLCOUNTValuePDCP-SNlength12" },
  {   1, "dLCOUNTValuePDCP-SNlength15" },
  {   2, "dLCOUNTValuePDCP-SNlength18" },
  { 0, NULL }
};

static const per_choice_t DLCOUNT_PDCP_SNlength_choice[] = {
  {   0, &hf_s1ap_dLCOUNTValuePDCP_SNlength12, ASN1_EXTENSION_ROOT    , dissect_s1ap_COUNTvalue },
  {   1, &hf_s1ap_dLCOUNTValuePDCP_SNlength15, ASN1_EXTENSION_ROOT    , dissect_s1ap_COUNTValueExtended },
  {   2, &hf_s1ap_dLCOUNTValuePDCP_SNlength18, ASN1_EXTENSION_ROOT    , dissect_s1ap_COUNTvaluePDCP_SNlength18 },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_DLCOUNT_PDCP_SNlength(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_DLCOUNT_PDCP_SNlength, DLCOUNT_PDCP_SNlength_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t Bearers_SubjectToEarlyStatusTransfer_Item_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_dLCOUNT_PDCP_SNlength, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_DLCOUNT_PDCP_SNlength },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item, Bearers_SubjectToEarlyStatusTransfer_Item_sequence);

  return offset;
}


static const value_string s1ap_BearerType_vals[] = {
  {   0, "non-IP" },
  { 0, NULL }
};


static int
dissect_s1ap_BearerType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_BitRate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer_64b(tvb, offset, actx, tree, hf_index,
                                                            0U, G_GUINT64_CONSTANT(10000000000), NULL, FALSE);

  return offset;
}


static const value_string s1ap_BluetoothMeasConfig_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_s1ap_BluetoothMeasConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_BluetoothName(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1476 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       1, 248, FALSE, &parameter_tvb);

  actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, -1, ENC_UTF_8|ENC_NA);


  return offset;
}


static const per_sequence_t BluetoothMeasConfigNameList_sequence_of[1] = {
  { &hf_s1ap_BluetoothMeasConfigNameList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_BluetoothName },
};

static int
dissect_s1ap_BluetoothMeasConfigNameList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_BluetoothMeasConfigNameList, BluetoothMeasConfigNameList_sequence_of,
                                                  1, maxnoofBluetoothName, FALSE);

  return offset;
}


static const value_string s1ap_T_bt_rssi_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_T_bt_rssi(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t BluetoothMeasurementConfiguration_sequence[] = {
  { &hf_s1ap_bluetoothMeasConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BluetoothMeasConfig },
  { &hf_s1ap_bluetoothMeasConfigNameList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_BluetoothMeasConfigNameList },
  { &hf_s1ap_bt_rssi        , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_bt_rssi },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_BluetoothMeasurementConfiguration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_BluetoothMeasurementConfiguration, BluetoothMeasurementConfiguration_sequence);

  return offset;
}


static const per_sequence_t BPLMNs_sequence_of[1] = {
  { &hf_s1ap_BPLMNs_item    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
};

static int
dissect_s1ap_BPLMNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_BPLMNs, BPLMNs_sequence_of,
                                                  1, maxnoofBPLMNs, FALSE);

  return offset;
}



static int
dissect_s1ap_NumberOfBroadcasts(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellID_Cancelled_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_numberOfBroadcasts, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NumberOfBroadcasts },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellID_Cancelled_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellID_Cancelled_Item, CellID_Cancelled_Item_sequence);

  return offset;
}


static const per_sequence_t CellID_Cancelled_sequence_of[1] = {
  { &hf_s1ap_CellID_Cancelled_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CellID_Cancelled_Item },
};

static int
dissect_s1ap_CellID_Cancelled(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CellID_Cancelled, CellID_Cancelled_sequence_of,
                                                  1, maxnoofCellID, FALSE);

  return offset;
}


static const per_sequence_t CancelledCellinTAI_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_numberOfBroadcasts, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NumberOfBroadcasts },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CancelledCellinTAI_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CancelledCellinTAI_Item, CancelledCellinTAI_Item_sequence);

  return offset;
}


static const per_sequence_t CancelledCellinTAI_sequence_of[1] = {
  { &hf_s1ap_CancelledCellinTAI_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CancelledCellinTAI_Item },
};

static int
dissect_s1ap_CancelledCellinTAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CancelledCellinTAI, CancelledCellinTAI_sequence_of,
                                                  1, maxnoofCellinTAI, FALSE);

  return offset;
}


static const per_sequence_t TAI_Cancelled_Item_sequence[] = {
  { &hf_s1ap_tAI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_cancelledCellinTAI, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CancelledCellinTAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAI_Cancelled_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAI_Cancelled_Item, TAI_Cancelled_Item_sequence);

  return offset;
}


static const per_sequence_t TAI_Cancelled_sequence_of[1] = {
  { &hf_s1ap_TAI_Cancelled_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI_Cancelled_Item },
};

static int
dissect_s1ap_TAI_Cancelled(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAI_Cancelled, TAI_Cancelled_sequence_of,
                                                  1, maxnoofTAIforWarning, FALSE);

  return offset;
}



static int
dissect_s1ap_EmergencyAreaID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 3, FALSE, NULL);

  return offset;
}


static const per_sequence_t CancelledCellinEAI_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_numberOfBroadcasts, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NumberOfBroadcasts },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CancelledCellinEAI_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CancelledCellinEAI_Item, CancelledCellinEAI_Item_sequence);

  return offset;
}


static const per_sequence_t CancelledCellinEAI_sequence_of[1] = {
  { &hf_s1ap_CancelledCellinEAI_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CancelledCellinEAI_Item },
};

static int
dissect_s1ap_CancelledCellinEAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CancelledCellinEAI, CancelledCellinEAI_sequence_of,
                                                  1, maxnoofCellinEAI, FALSE);

  return offset;
}


static const per_sequence_t EmergencyAreaID_Cancelled_Item_sequence[] = {
  { &hf_s1ap_emergencyAreaID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID },
  { &hf_s1ap_cancelledCellinEAI, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CancelledCellinEAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EmergencyAreaID_Cancelled_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EmergencyAreaID_Cancelled_Item, EmergencyAreaID_Cancelled_Item_sequence);

  return offset;
}


static const per_sequence_t EmergencyAreaID_Cancelled_sequence_of[1] = {
  { &hf_s1ap_EmergencyAreaID_Cancelled_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID_Cancelled_Item },
};

static int
dissect_s1ap_EmergencyAreaID_Cancelled(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_EmergencyAreaID_Cancelled, EmergencyAreaID_Cancelled_sequence_of,
                                                  1, maxnoofEmergencyAreaID, FALSE);

  return offset;
}


static const value_string s1ap_BroadcastCancelledAreaList_vals[] = {
  {   0, "cellID-Cancelled" },
  {   1, "tAI-Cancelled" },
  {   2, "emergencyAreaID-Cancelled" },
  { 0, NULL }
};

static const per_choice_t BroadcastCancelledAreaList_choice[] = {
  {   0, &hf_s1ap_cellID_Cancelled, ASN1_EXTENSION_ROOT    , dissect_s1ap_CellID_Cancelled },
  {   1, &hf_s1ap_tAI_Cancelled  , ASN1_EXTENSION_ROOT    , dissect_s1ap_TAI_Cancelled },
  {   2, &hf_s1ap_emergencyAreaID_Cancelled, ASN1_EXTENSION_ROOT    , dissect_s1ap_EmergencyAreaID_Cancelled },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_BroadcastCancelledAreaList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_BroadcastCancelledAreaList, BroadcastCancelledAreaList_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t CellID_Broadcast_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellID_Broadcast_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellID_Broadcast_Item, CellID_Broadcast_Item_sequence);

  return offset;
}


static const per_sequence_t CellID_Broadcast_sequence_of[1] = {
  { &hf_s1ap_CellID_Broadcast_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CellID_Broadcast_Item },
};

static int
dissect_s1ap_CellID_Broadcast(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CellID_Broadcast, CellID_Broadcast_sequence_of,
                                                  1, maxnoofCellID, FALSE);

  return offset;
}


static const per_sequence_t CompletedCellinTAI_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CompletedCellinTAI_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CompletedCellinTAI_Item, CompletedCellinTAI_Item_sequence);

  return offset;
}


static const per_sequence_t CompletedCellinTAI_sequence_of[1] = {
  { &hf_s1ap_CompletedCellinTAI_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CompletedCellinTAI_Item },
};

static int
dissect_s1ap_CompletedCellinTAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CompletedCellinTAI, CompletedCellinTAI_sequence_of,
                                                  1, maxnoofCellinTAI, FALSE);

  return offset;
}


static const per_sequence_t TAI_Broadcast_Item_sequence[] = {
  { &hf_s1ap_tAI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_completedCellinTAI, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CompletedCellinTAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAI_Broadcast_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAI_Broadcast_Item, TAI_Broadcast_Item_sequence);

  return offset;
}


static const per_sequence_t TAI_Broadcast_sequence_of[1] = {
  { &hf_s1ap_TAI_Broadcast_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI_Broadcast_Item },
};

static int
dissect_s1ap_TAI_Broadcast(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAI_Broadcast, TAI_Broadcast_sequence_of,
                                                  1, maxnoofTAIforWarning, FALSE);

  return offset;
}


static const per_sequence_t CompletedCellinEAI_Item_sequence[] = {
  { &hf_s1ap_eCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CompletedCellinEAI_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CompletedCellinEAI_Item, CompletedCellinEAI_Item_sequence);

  return offset;
}


static const per_sequence_t CompletedCellinEAI_sequence_of[1] = {
  { &hf_s1ap_CompletedCellinEAI_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CompletedCellinEAI_Item },
};

static int
dissect_s1ap_CompletedCellinEAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CompletedCellinEAI, CompletedCellinEAI_sequence_of,
                                                  1, maxnoofCellinEAI, FALSE);

  return offset;
}


static const per_sequence_t EmergencyAreaID_Broadcast_Item_sequence[] = {
  { &hf_s1ap_emergencyAreaID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID },
  { &hf_s1ap_completedCellinEAI, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CompletedCellinEAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EmergencyAreaID_Broadcast_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EmergencyAreaID_Broadcast_Item, EmergencyAreaID_Broadcast_Item_sequence);

  return offset;
}


static const per_sequence_t EmergencyAreaID_Broadcast_sequence_of[1] = {
  { &hf_s1ap_EmergencyAreaID_Broadcast_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID_Broadcast_Item },
};

static int
dissect_s1ap_EmergencyAreaID_Broadcast(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_EmergencyAreaID_Broadcast, EmergencyAreaID_Broadcast_sequence_of,
                                                  1, maxnoofEmergencyAreaID, FALSE);

  return offset;
}


static const value_string s1ap_BroadcastCompletedAreaList_vals[] = {
  {   0, "cellID-Broadcast" },
  {   1, "tAI-Broadcast" },
  {   2, "emergencyAreaID-Broadcast" },
  { 0, NULL }
};

static const per_choice_t BroadcastCompletedAreaList_choice[] = {
  {   0, &hf_s1ap_cellID_Broadcast, ASN1_EXTENSION_ROOT    , dissect_s1ap_CellID_Broadcast },
  {   1, &hf_s1ap_tAI_Broadcast  , ASN1_EXTENSION_ROOT    , dissect_s1ap_TAI_Broadcast },
  {   2, &hf_s1ap_emergencyAreaID_Broadcast, ASN1_EXTENSION_ROOT    , dissect_s1ap_EmergencyAreaID_Broadcast },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_BroadcastCompletedAreaList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_BroadcastCompletedAreaList, BroadcastCompletedAreaList_choice,
                                 NULL);

  return offset;
}


const value_string s1ap_CauseRadioNetwork_vals[] = {
  {   0, "unspecified" },
  {   1, "tx2relocoverall-expiry" },
  {   2, "successful-handover" },
  {   3, "release-due-to-eutran-generated-reason" },
  {   4, "handover-cancelled" },
  {   5, "partial-handover" },
  {   6, "ho-failure-in-target-EPC-eNB-or-target-system" },
  {   7, "ho-target-not-allowed" },
  {   8, "tS1relocoverall-expiry" },
  {   9, "tS1relocprep-expiry" },
  {  10, "cell-not-available" },
  {  11, "unknown-targetID" },
  {  12, "no-radio-resources-available-in-target-cell" },
  {  13, "unknown-mme-ue-s1ap-id" },
  {  14, "unknown-enb-ue-s1ap-id" },
  {  15, "unknown-pair-ue-s1ap-id" },
  {  16, "handover-desirable-for-radio-reason" },
  {  17, "time-critical-handover" },
  {  18, "resource-optimisation-handover" },
  {  19, "reduce-load-in-serving-cell" },
  {  20, "user-inactivity" },
  {  21, "radio-connection-with-ue-lost" },
  {  22, "load-balancing-tau-required" },
  {  23, "cs-fallback-triggered" },
  {  24, "ue-not-available-for-ps-service" },
  {  25, "radio-resources-not-available" },
  {  26, "failure-in-radio-interface-procedure" },
  {  27, "invalid-qos-combination" },
  {  28, "interrat-redirection" },
  {  29, "interaction-with-other-procedure" },
  {  30, "unknown-E-RAB-ID" },
  {  31, "multiple-E-RAB-ID-instances" },
  {  32, "encryption-and-or-integrity-protection-algorithms-not-supported" },
  {  33, "s1-intra-system-handover-triggered" },
  {  34, "s1-inter-system-handover-triggered" },
  {  35, "x2-handover-triggered" },
  {  36, "redirection-towards-1xRTT" },
  {  37, "not-supported-QCI-value" },
  {  38, "invalid-CSG-Id" },
  {  39, "release-due-to-pre-emption" },
  {  40, "n26-interface-not-available" },
  {  41, "insufficient-ue-capabilities" },
  { 0, NULL }
};

static value_string_ext s1ap_CauseRadioNetwork_vals_ext = VALUE_STRING_EXT_INIT(s1ap_CauseRadioNetwork_vals);


static int
dissect_s1ap_CauseRadioNetwork(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2584 "./asn1/s1ap/s1ap.cnf"
  guint32 value;
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     36, &value, TRUE, 6, NULL);

  col_append_fstr(actx->pinfo->cinfo, COL_INFO, " [RadioNetwork-cause=%s]", val_to_str_const(value, s1ap_CauseRadioNetwork_vals, "Unknown"));



  return offset;
}


const value_string s1ap_CauseTransport_vals[] = {
  {   0, "transport-resource-unavailable" },
  {   1, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_CauseTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2589 "./asn1/s1ap/s1ap.cnf"
  guint32 value;
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, &value, TRUE, 0, NULL);

  col_append_fstr(actx->pinfo->cinfo, COL_INFO, " [Transport-cause=%s]", val_to_str_const(value, s1ap_CauseTransport_vals, "Unknown"));



  return offset;
}


const value_string s1ap_CauseNas_vals[] = {
  {   0, "normal-release" },
  {   1, "authentication-failure" },
  {   2, "detach" },
  {   3, "unspecified" },
  {   4, "csg-subscription-expiry" },
  { 0, NULL }
};


static int
dissect_s1ap_CauseNas(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2594 "./asn1/s1ap/s1ap.cnf"
  guint32 value;
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, &value, TRUE, 1, NULL);

  col_append_fstr(actx->pinfo->cinfo, COL_INFO, " [NAS-cause=%s]", val_to_str_const(value, s1ap_CauseNas_vals, "Unknown"));



  return offset;
}


const value_string s1ap_CauseProtocol_vals[] = {
  {   0, "transfer-syntax-error" },
  {   1, "abstract-syntax-error-reject" },
  {   2, "abstract-syntax-error-ignore-and-notify" },
  {   3, "message-not-compatible-with-receiver-state" },
  {   4, "semantic-error" },
  {   5, "abstract-syntax-error-falsely-constructed-message" },
  {   6, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_CauseProtocol(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2599 "./asn1/s1ap/s1ap.cnf"
  guint32 value;
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, &value, TRUE, 0, NULL);

  col_append_fstr(actx->pinfo->cinfo, COL_INFO, " [Protocol-cause=%s]", val_to_str_const(value, s1ap_CauseProtocol_vals, "Unknown"));



  return offset;
}


const value_string s1ap_CauseMisc_vals[] = {
  {   0, "control-processing-overload" },
  {   1, "not-enough-user-plane-processing-resources" },
  {   2, "hardware-failure" },
  {   3, "om-intervention" },
  {   4, "unspecified" },
  {   5, "unknown-PLMN" },
  { 0, NULL }
};


static int
dissect_s1ap_CauseMisc(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2604 "./asn1/s1ap/s1ap.cnf"
  guint32 value;
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, &value, TRUE, 0, NULL);

  col_append_fstr(actx->pinfo->cinfo, COL_INFO, " [Misc-cause=%s]", val_to_str_const(value, s1ap_CauseMisc_vals, "Unknown"));



  return offset;
}


const value_string s1ap_Cause_vals[] = {
  {   0, "radioNetwork" },
  {   1, "transport" },
  {   2, "nas" },
  {   3, "protocol" },
  {   4, "misc" },
  { 0, NULL }
};

static const per_choice_t Cause_choice[] = {
  {   0, &hf_s1ap_radioNetwork   , ASN1_EXTENSION_ROOT    , dissect_s1ap_CauseRadioNetwork },
  {   1, &hf_s1ap_transport      , ASN1_EXTENSION_ROOT    , dissect_s1ap_CauseTransport },
  {   2, &hf_s1ap_nas            , ASN1_EXTENSION_ROOT    , dissect_s1ap_CauseNas },
  {   3, &hf_s1ap_protocol       , ASN1_EXTENSION_ROOT    , dissect_s1ap_CauseProtocol },
  {   4, &hf_s1ap_misc           , ASN1_EXTENSION_ROOT    , dissect_s1ap_CauseMisc },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_Cause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_Cause, Cause_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_CellAccessMode_vals[] = {
  {   0, "hybrid" },
  { 0, NULL }
};


static int
dissect_s1ap_CellAccessMode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_CE_mode_B_SupportIndicator_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_s1ap_CE_mode_B_SupportIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Cdma2000PDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 728 "./asn1/s1ap/s1ap.cnf"

  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

if (gcsna_handle) {
        subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_Cdma2000PDU);
        call_dissector(gcsna_handle, parameter_tvb, actx->pinfo, subtree);
}




  return offset;
}


static const value_string s1ap_Cdma2000RATType_vals[] = {
  {   0, "hRPD" },
  {   1, "onexRTT" },
  { 0, NULL }
};


static int
dissect_s1ap_Cdma2000RATType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Cdma2000SectorID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 743 "./asn1/s1ap/s1ap.cnf"
/* 9.2.1.25
 * This IE is set to CDMA2000 Reference Cell ID
 * corresponding to the HRPD/1xRTT sector under
 * the HRPD AN/1xBS to which the eNB has initiated the UE
 * to handover to. The CDMA2000 Reference Cell
 * ID is statically configured in the eNB.
 */
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_Cdma2000SectorID);
  dissect_a21_ie_common(parameter_tvb, actx->pinfo, NULL/* Top tree not needed */, subtree, 0,  0 /* message_type not needed */);



  return offset;
}


static const value_string s1ap_Cdma2000HOStatus_vals[] = {
  {   0, "hOSuccess" },
  {   1, "hOFailure" },
  { 0, NULL }
};


static int
dissect_s1ap_Cdma2000HOStatus(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_Cdma2000HORequiredIndication_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_Cdma2000HORequiredIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Cdma2000OneXMEID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}



static int
dissect_s1ap_Cdma2000OneXMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}



static int
dissect_s1ap_Cdma2000OneXPilot(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const per_sequence_t Cdma2000OneXSRVCCInfo_sequence[] = {
  { &hf_s1ap_cdma2000OneXMEID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cdma2000OneXMEID },
  { &hf_s1ap_cdma2000OneXMSI, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cdma2000OneXMSI },
  { &hf_s1ap_cdma2000OneXPilot, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cdma2000OneXPilot },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Cdma2000OneXSRVCCInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Cdma2000OneXSRVCCInfo, Cdma2000OneXSRVCCInfo_sequence);

  return offset;
}



static int
dissect_s1ap_Cdma2000OneXRAND(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const value_string s1ap_Cell_Size_vals[] = {
  {   0, "verysmall" },
  {   1, "small" },
  {   2, "medium" },
  {   3, "large" },
  { 0, NULL }
};


static int
dissect_s1ap_Cell_Size(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t CellType_sequence[] = {
  { &hf_s1ap_cell_Size      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cell_Size },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellType, CellType_sequence);

  return offset;
}



static int
dissect_s1ap_LAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1329 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_CI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       2, 2, FALSE, NULL);

  return offset;
}



static int
dissect_s1ap_RAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1338 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       1, 1, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 1, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const per_sequence_t CGI_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_lAC            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LAC },
  { &hf_s1ap_cI             , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CI },
  { &hf_s1ap_rAC            , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_RAC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CGI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2611 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_CGI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CGI, CGI_sequence);




  return offset;
}


static const value_string s1ap_CNDomain_vals[] = {
  {   0, "ps" },
  {   1, "cs" },
  { 0, NULL }
};


static int
dissect_s1ap_CNDomain(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string s1ap_CNType_vals[] = {
  {   0, "fiveGCForbidden" },
  {   1, "epc-Forbiddden" },
  { 0, NULL }
};


static int
dissect_s1ap_CNType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 1, NULL);

  return offset;
}


static const per_sequence_t CNTypeRestrictions_Item_sequence[] = {
  { &hf_s1ap_pLMN_Identity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_cNType         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CNType },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CNTypeRestrictions_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CNTypeRestrictions_Item, CNTypeRestrictions_Item_sequence);

  return offset;
}


static const per_sequence_t CNTypeRestrictions_sequence_of[1] = {
  { &hf_s1ap_CNTypeRestrictions_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CNTypeRestrictions_Item },
};

static int
dissect_s1ap_CNTypeRestrictions(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CNTypeRestrictions, CNTypeRestrictions_sequence_of,
                                                  1, maxnoofEPLMNsPlusOne, FALSE);

  return offset;
}


static const value_string s1ap_ConcurrentWarningMessageIndicator_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_ConcurrentWarningMessageIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_En_gNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     22, 32, TRUE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t SupportedTAs_Item_sequence[] = {
  { &hf_s1ap_tAC            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAC },
  { &hf_s1ap_broadcastPLMNs , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BPLMNs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SupportedTAs_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1396 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);

  if (!PINFO_FD_VISITED(actx->pinfo) &&
      (s1ap_data->message_type == INITIATING_MESSAGE) &&
      ((s1ap_data->procedure_code == id_S1Setup) ||
       (s1ap_data->procedure_code == id_ENBConfigurationUpdate))) {
    s1ap_data->supported_ta = wmem_new0(actx->pinfo->pool, struct s1ap_supported_ta);
    s1ap_data->supported_ta->plmn = wmem_array_new(actx->pinfo->pool, sizeof(guint32));
  }


  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SupportedTAs_Item, SupportedTAs_Item_sequence);

#line 1407 "./asn1/s1ap/s1ap.cnf"
  s1ap_data->supported_ta = NULL;


  return offset;
}


static const per_sequence_t SupportedTAs_sequence_of[1] = {
  { &hf_s1ap_SupportedTAs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_SupportedTAs_Item },
};

static int
dissect_s1ap_SupportedTAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_SupportedTAs, SupportedTAs_sequence_of,
                                                  1, maxnoofTACs, FALSE);

  return offset;
}


static const per_sequence_t ConnectedengNBItem_sequence[] = {
  { &hf_s1ap_en_gNB_ID      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_En_gNB_ID },
  { &hf_s1ap_supportedTAs   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SupportedTAs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ConnectedengNBItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ConnectedengNBItem, ConnectedengNBItem_sequence);

  return offset;
}


static const per_sequence_t ConnectedengNBList_sequence_of[1] = {
  { &hf_s1ap_ConnectedengNBList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ConnectedengNBItem },
};

static int
dissect_s1ap_ConnectedengNBList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ConnectedengNBList, ConnectedengNBList_sequence_of,
                                                  1, maxnoofConnectedengNBs, FALSE);

  return offset;
}



static int
dissect_s1ap_GNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     22, 32, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string s1ap_GNB_Identity_vals[] = {
  {   0, "gNB-ID" },
  { 0, NULL }
};

static const per_choice_t GNB_Identity_choice[] = {
  {   0, &hf_s1ap_gNB_ID_01      , ASN1_EXTENSION_ROOT    , dissect_s1ap_GNB_ID },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_GNB_Identity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_GNB_Identity, GNB_Identity_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t Global_GNB_ID_sequence[] = {
  { &hf_s1ap_pLMN_Identity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_gNB_ID         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GNB_Identity },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Global_GNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Global_GNB_ID, Global_GNB_ID_sequence);

  return offset;
}


static const per_sequence_t GNB_sequence[] = {
  { &hf_s1ap_global_gNB_ID  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_GNB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_GNB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_GNB, GNB_sequence);

  return offset;
}



static int
dissect_s1ap_BIT_STRING_SIZE_20(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     20, 20, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_BIT_STRING_SIZE_28(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     28, 28, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_BIT_STRING_SIZE_18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     18, 18, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_BIT_STRING_SIZE_21(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     21, 21, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string s1ap_ENB_ID_vals[] = {
  {   0, "macroENB-ID" },
  {   1, "homeENB-ID" },
  {   2, "short-macroENB-ID" },
  {   3, "long-macroENB-ID" },
  { 0, NULL }
};

static const per_choice_t ENB_ID_choice[] = {
  {   0, &hf_s1ap_macroENB_ID    , ASN1_EXTENSION_ROOT    , dissect_s1ap_BIT_STRING_SIZE_20 },
  {   1, &hf_s1ap_homeENB_ID     , ASN1_EXTENSION_ROOT    , dissect_s1ap_BIT_STRING_SIZE_28 },
  {   2, &hf_s1ap_short_macroENB_ID, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_BIT_STRING_SIZE_18 },
  {   3, &hf_s1ap_long_macroENB_ID, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_BIT_STRING_SIZE_21 },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_ENB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_ENB_ID, ENB_ID_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t Global_ENB_ID_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_eNB_ID         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ENB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

int
dissect_s1ap_Global_ENB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Global_ENB_ID, Global_ENB_ID_sequence);

  return offset;
}


static const per_sequence_t NG_eNB_sequence[] = {
  { &hf_s1ap_global_ng_eNB_ID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_ENB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NG_eNB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NG_eNB, NG_eNB_sequence);

  return offset;
}


static const value_string s1ap_Global_RAN_NODE_ID_vals[] = {
  {   0, "gNB" },
  {   1, "ng-eNB" },
  { 0, NULL }
};

static const per_choice_t Global_RAN_NODE_ID_choice[] = {
  {   0, &hf_s1ap_gNB            , ASN1_EXTENSION_ROOT    , dissect_s1ap_GNB },
  {   1, &hf_s1ap_ng_eNB         , ASN1_EXTENSION_ROOT    , dissect_s1ap_NG_eNB },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_Global_RAN_NODE_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_Global_RAN_NODE_ID, Global_RAN_NODE_ID_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_RAN_UE_NGAP_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4294967295U, NULL, FALSE);

  return offset;
}


static const per_sequence_t ContextatSource_sequence[] = {
  { &hf_s1ap_sourceNG_RAN_node_ID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_RAN_NODE_ID },
  { &hf_s1ap_rAN_UE_NGAP_ID , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RAN_UE_NGAP_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ContextatSource(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ContextatSource, ContextatSource_sequence);

  return offset;
}



static int
dissect_s1ap_Correlation_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, FALSE, NULL);

  return offset;
}


static const value_string s1ap_CSFallbackIndicator_vals[] = {
  {   0, "cs-fallback-required" },
  {   1, "cs-fallback-high-priority" },
  { 0, NULL }
};


static int
dissect_s1ap_CSFallbackIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 1, NULL);

  return offset;
}


static const value_string s1ap_AdditionalCSFallbackIndicator_vals[] = {
  {   0, "no-restriction" },
  {   1, "restriction" },
  { 0, NULL }
};


static int
dissect_s1ap_AdditionalCSFallbackIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_CSG_Id(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     27, 27, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t CSG_IdList_Item_sequence[] = {
  { &hf_s1ap_cSG_Id         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CSG_Id },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CSG_IdList_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CSG_IdList_Item, CSG_IdList_Item_sequence);

  return offset;
}


static const per_sequence_t CSG_IdList_sequence_of[1] = {
  { &hf_s1ap_CSG_IdList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CSG_IdList_Item },
};

static int
dissect_s1ap_CSG_IdList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CSG_IdList, CSG_IdList_sequence_of,
                                                  1, maxnoofCSGs, FALSE);

  return offset;
}


static const value_string s1ap_CSGMembershipStatus_vals[] = {
  {   0, "member" },
  {   1, "not-member" },
  { 0, NULL }
};


static int
dissect_s1ap_CSGMembershipStatus(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string s1ap_Coverage_Level_vals[] = {
  {   0, "extendedcoverage" },
  { 0, NULL }
};


static int
dissect_s1ap_Coverage_Level(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_TypeOfError_vals[] = {
  {   0, "not-understood" },
  {   1, "missing" },
  { 0, NULL }
};


static int
dissect_s1ap_TypeOfError(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_IE_Item_sequence[] = {
  { &hf_s1ap_iECriticality  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_iE_ID          , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_ID },
  { &hf_s1ap_typeOfError    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TypeOfError },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CriticalityDiagnostics_IE_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CriticalityDiagnostics_IE_Item, CriticalityDiagnostics_IE_Item_sequence);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_IE_List_sequence_of[1] = {
  { &hf_s1ap_CriticalityDiagnostics_IE_List_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CriticalityDiagnostics_IE_Item },
};

static int
dissect_s1ap_CriticalityDiagnostics_IE_List(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CriticalityDiagnostics_IE_List, CriticalityDiagnostics_IE_List_sequence_of,
                                                  1, maxnoofErrors, FALSE);

  return offset;
}


static const per_sequence_t CriticalityDiagnostics_sequence[] = {
  { &hf_s1ap_procedureCode  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProcedureCode },
  { &hf_s1ap_triggeringMessage, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TriggeringMessage },
  { &hf_s1ap_procedureCriticality, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_Criticality },
  { &hf_s1ap_iEsCriticalityDiagnostics, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_CriticalityDiagnostics_IE_List },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CriticalityDiagnostics(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CriticalityDiagnostics, CriticalityDiagnostics_sequence);

  return offset;
}


static const value_string s1ap_T_dAPSIndicator_vals[] = {
  {   0, "dAPS-HO-required" },
  { 0, NULL }
};


static int
dissect_s1ap_T_dAPSIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t DAPSRequestInfo_sequence[] = {
  { &hf_s1ap_dAPSIndicator  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_dAPSIndicator },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DAPSRequestInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DAPSRequestInfo, DAPSRequestInfo_sequence);

  return offset;
}


static const per_sequence_t DAPSResponseInfoList_sequence_of[1] = {
  { &hf_s1ap_DAPSResponseInfoList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_DAPSResponseInfoList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_DAPSResponseInfoList, DAPSResponseInfoList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const value_string s1ap_T_dapsresponseindicator_vals[] = {
  {   0, "dAPS-HO-accepted" },
  {   1, "dAPS-HO-not-accepted" },
  { 0, NULL }
};


static int
dissect_s1ap_T_dapsresponseindicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t DAPSResponseInfo_sequence[] = {
  { &hf_s1ap_dapsresponseindicator, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_dapsresponseindicator },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DAPSResponseInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DAPSResponseInfo, DAPSResponseInfo_sequence);

  return offset;
}


static const per_sequence_t DAPSResponseInfoItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_dAPSResponseInfo, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_DAPSResponseInfo },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DAPSResponseInfoItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DAPSResponseInfoItem, DAPSResponseInfoItem_sequence);

  return offset;
}



static int
dissect_s1ap_DataCodingScheme(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1144 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL, 0, &parameter_tvb, NULL);

  if (parameter_tvb) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    proto_tree *subtree;

    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_DataCodingScheme);
    s1ap_data->data_coding_scheme = dissect_cbs_data_coding_scheme(parameter_tvb, actx->pinfo, subtree, 0);
  }



  return offset;
}



static int
dissect_s1ap_DataSize(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 4095U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_DCN_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_RelativeMMECapacity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}


static const per_sequence_t ServedDCNsItem_sequence[] = {
  { &hf_s1ap_dCN_ID         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_DCN_ID },
  { &hf_s1ap_relativeDCNCapacity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RelativeMMECapacity },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ServedDCNsItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ServedDCNsItem, ServedDCNsItem_sequence);

  return offset;
}


static const per_sequence_t ServedDCNs_sequence_of[1] = {
  { &hf_s1ap_ServedDCNs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ServedDCNsItem },
};

static int
dissect_s1ap_ServedDCNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ServedDCNs, ServedDCNs_sequence_of,
                                                  0, maxnoofDCNs, FALSE);

  return offset;
}



static int
dissect_s1ap_DL_NAS_MAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t DL_CP_SecurityInformation_sequence[] = {
  { &hf_s1ap_dl_NAS_MAC     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_DL_NAS_MAC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DL_CP_SecurityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DL_CP_SecurityInformation, DL_CP_SecurityInformation_sequence);

  return offset;
}


static const value_string s1ap_DL_Forwarding_vals[] = {
  {   0, "dL-Forwarding-proposed" },
  { 0, NULL }
};


static int
dissect_s1ap_DL_Forwarding(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_Direct_Forwarding_Path_Availability_vals[] = {
  {   0, "directPathAvailable" },
  { 0, NULL }
};


static int
dissect_s1ap_Direct_Forwarding_Path_Availability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_Data_Forwarding_Not_Possible_vals[] = {
  {   0, "data-Forwarding-not-Possible" },
  { 0, NULL }
};


static int
dissect_s1ap_Data_Forwarding_Not_Possible(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_DLNASPDUDeliveryAckRequest_vals[] = {
  {   0, "requested" },
  { 0, NULL }
};


static int
dissect_s1ap_DLNASPDUDeliveryAckRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_EARFCN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxEARFCN, NULL, TRUE);

  return offset;
}


static const per_sequence_t ECGIList_sequence_of[1] = {
  { &hf_s1ap_ECGIList_item  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_ECGIList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ECGIList, ECGIList_sequence_of,
                                                  1, maxnoofCellID, FALSE);

  return offset;
}


static const per_sequence_t PWSfailedECGIList_sequence_of[1] = {
  { &hf_s1ap_PWSfailedECGIList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_PWSfailedECGIList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_PWSfailedECGIList, PWSfailedECGIList_sequence_of,
                                                  1, maxnoofCellsineNB, FALSE);

  return offset;
}


static const value_string s1ap_EDT_Session_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_EDT_Session(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t EmergencyAreaIDList_sequence_of[1] = {
  { &hf_s1ap_EmergencyAreaIDList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID },
};

static int
dissect_s1ap_EmergencyAreaIDList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_EmergencyAreaIDList, EmergencyAreaIDList_sequence_of,
                                                  1, maxnoofEmergencyAreaID, FALSE);

  return offset;
}


static const per_sequence_t ECGI_List_sequence_of[1] = {
  { &hf_s1ap_ECGI_List_item , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_ECGI_List(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ECGI_List, ECGI_List_sequence_of,
                                                  1, maxnoofCellsineNB, FALSE);

  return offset;
}


static const per_sequence_t EmergencyAreaIDListForRestart_sequence_of[1] = {
  { &hf_s1ap_EmergencyAreaIDListForRestart_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EmergencyAreaID },
};

static int
dissect_s1ap_EmergencyAreaIDListForRestart(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_EmergencyAreaIDListForRestart, EmergencyAreaIDListForRestart_sequence_of,
                                                  1, maxnoofRestartEmergencyAreaIDs, FALSE);

  return offset;
}


static const value_string s1ap_EmergencyIndicator_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_EmergencyIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t ENB_EarlyStatusTransfer_TransparentContainer_sequence[] = {
  { &hf_s1ap_bearers_SubjectToEarlyStatusTransferList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Bearers_SubjectToEarlyStatusTransferList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENB_EarlyStatusTransfer_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENB_EarlyStatusTransfer_TransparentContainer, ENB_EarlyStatusTransfer_TransparentContainer_sequence);

  return offset;
}


static const per_sequence_t LAI_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_lAC            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LAC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1322 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_LAI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LAI, LAI_sequence);




  return offset;
}


static const per_sequence_t GERAN_Cell_ID_sequence[] = {
  { &hf_s1ap_lAI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LAI },
  { &hf_s1ap_rAC            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RAC },
  { &hf_s1ap_cI             , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_GERAN_Cell_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_GERAN_Cell_ID, GERAN_Cell_ID_sequence);

  return offset;
}


static const per_sequence_t Global_en_gNB_ID_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_en_gNB_ID      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_En_gNB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Global_en_gNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Global_en_gNB_ID, Global_en_gNB_ID_sequence);

  return offset;
}


static const per_sequence_t GUMMEIList_sequence_of[1] = {
  { &hf_s1ap_GUMMEIList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_GUMMEI },
};

static int
dissect_s1ap_GUMMEIList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_GUMMEIList, GUMMEIList_sequence_of,
                                                  1, maxnoofMMECs, FALSE);

  return offset;
}


static const per_sequence_t ENB_StatusTransfer_TransparentContainer_sequence[] = {
  { &hf_s1ap_bearers_SubjectToStatusTransferList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Bearers_SubjectToStatusTransferList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENB_StatusTransfer_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENB_StatusTransfer_TransparentContainer, ENB_StatusTransfer_TransparentContainer_sequence);

  return offset;
}



static int
dissect_s1ap_ENB_UE_S1AP_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1425 "./asn1/s1ap/s1ap.cnf"
  guint32 enb_ue_s1ap_id;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 16777215U, &enb_ue_s1ap_id, FALSE);

  if (hf_index == hf_s1ap_eNB_UE_S1AP_ID) {
    proto_item *item;
    item = proto_tree_add_uint(tree, hf_s1ap_ENB_UE_S1AP_ID_PDU, tvb, offset, 0 , enb_ue_s1ap_id );
    proto_item_set_hidden(item);
  }

  s1ap_data->enb_ue_s1ap_id = (guint16)enb_ue_s1ap_id;



  return offset;
}



static int
dissect_s1ap_ENBname(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 270 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb=NULL;
  int length;
  gboolean is_ascii;

  offset = dissect_per_PrintableString(tvb, offset, actx, tree, hf_index,
                                          1, 150, TRUE);


  if (!parameter_tvb)
    return offset;

  length = tvb_reported_length(parameter_tvb);

  is_ascii = tvb_ascii_isprint(parameter_tvb, 0, length);
  if (is_ascii)
     proto_item_append_text(actx->created_item," (%s)",tvb_format_text(actx->pinfo->pool, parameter_tvb, 0, length));



  return offset;
}



static int
dissect_s1ap_TransportLayerAddress(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 323 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb=NULL;
  proto_tree *subtree;
  gint tvb_len;

  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     1, 160, TRUE, NULL, 0, &parameter_tvb, NULL);

  if (!parameter_tvb)
    return offset;

  /* Get the length */
  tvb_len = tvb_reported_length(parameter_tvb);
  subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_TransportLayerAddress);
  if (tvb_len==4) {
    /* IPv4 */
     proto_tree_add_item(subtree, hf_s1ap_transportLayerAddressIPv4, parameter_tvb, 0, 4, ENC_BIG_ENDIAN);
  } else if (tvb_len==16) {
    /* IPv6 */
     proto_tree_add_item(subtree, hf_s1ap_transportLayerAddressIPv6, parameter_tvb, 0, 16, ENC_NA);
  } else if (tvb_len==20) {
    /* IPv4 */
     proto_tree_add_item(subtree, hf_s1ap_transportLayerAddressIPv4, parameter_tvb, 0, 4, ENC_BIG_ENDIAN);
    /* IPv6 */
     proto_tree_add_item(subtree, hf_s1ap_transportLayerAddressIPv6, parameter_tvb, 4, 16, ENC_NA);
  }



  return offset;
}


static const per_sequence_t ENBX2TLAs_sequence_of[1] = {
  { &hf_s1ap_ENBX2TLAs_item , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
};

static int
dissect_s1ap_ENBX2TLAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ENBX2TLAs, ENBX2TLAs_sequence_of,
                                                  1, maxnoofeNBX2TLAs, FALSE);

  return offset;
}



static int
dissect_s1ap_EncryptionAlgorithms(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1029 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, TRUE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_encryptionAlgorithms_EEA1,
      &hf_s1ap_encryptionAlgorithms_EEA2,
      &hf_s1ap_encryptionAlgorithms_EEA3,
      &hf_s1ap_encryptionAlgorithms_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_EncryptionAlgorithms);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 2, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const per_sequence_t EN_DCSONeNBIdentification_sequence[] = {
  { &hf_s1ap_globaleNBID    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_ENB_ID },
  { &hf_s1ap_selectedTAI    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EN_DCSONeNBIdentification(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EN_DCSONeNBIdentification, EN_DCSONeNBIdentification_sequence);

  return offset;
}


static const per_sequence_t EN_DCSONengNBIdentification_sequence[] = {
  { &hf_s1ap_globalengNBID  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_en_gNB_ID },
  { &hf_s1ap_selectedTAI    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EN_DCSONengNBIdentification(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EN_DCSONengNBIdentification, EN_DCSONengNBIdentification_sequence);

  return offset;
}



static int
dissect_s1ap_FiveGSTAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1352 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       3, 3, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 3, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const per_sequence_t FiveGSTAI_sequence[] = {
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_fiveGSTAC      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_FiveGSTAC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_FiveGSTAI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1345 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_5GSTAI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_FiveGSTAI, FiveGSTAI_sequence);




  return offset;
}


static const per_sequence_t EN_DCTransferTypeRequest_sequence[] = {
  { &hf_s1ap_sourceeNB      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EN_DCSONeNBIdentification },
  { &hf_s1ap_targetengNB    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EN_DCSONengNBIdentification },
  { &hf_s1ap_targeteNB      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_EN_DCSONeNBIdentification },
  { &hf_s1ap_associatedTAI  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TAI },
  { &hf_s1ap_broadcast5GSTAI, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_FiveGSTAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EN_DCTransferTypeRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EN_DCTransferTypeRequest, EN_DCTransferTypeRequest_sequence);

  return offset;
}


static const per_sequence_t EN_DCTransferTypeReply_sequence[] = {
  { &hf_s1ap_sourceengNB    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EN_DCSONengNBIdentification },
  { &hf_s1ap_targeteNB      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EN_DCSONeNBIdentification },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EN_DCTransferTypeReply(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EN_DCTransferTypeReply, EN_DCTransferTypeReply_sequence);

  return offset;
}


static const value_string s1ap_EN_DCSONTransferType_vals[] = {
  {   0, "request" },
  {   1, "reply" },
  { 0, NULL }
};

static const per_choice_t EN_DCSONTransferType_choice[] = {
  {   0, &hf_s1ap_request        , ASN1_EXTENSION_ROOT    , dissect_s1ap_EN_DCTransferTypeRequest },
  {   1, &hf_s1ap_reply          , ASN1_EXTENSION_ROOT    , dissect_s1ap_EN_DCTransferTypeReply },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_EN_DCSONTransferType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_EN_DCSONTransferType, EN_DCSONTransferType_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_SONInformationRequest_vals[] = {
  {   0, "x2TNL-Configuration-Info" },
  {   1, "time-Synchronisation-Info" },
  {   2, "activate-Muting" },
  {   3, "deactivate-Muting" },
  { 0, NULL }
};


static int
dissect_s1ap_SONInformationRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 3, NULL);

  return offset;
}


static const per_sequence_t X2TNLConfigurationInfo_sequence[] = {
  { &hf_s1ap_eNBX2TransportLayerAddresses, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ENBX2TLAs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_X2TNLConfigurationInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_X2TNLConfigurationInfo, X2TNLConfigurationInfo_sequence);

  return offset;
}


static const per_sequence_t SONInformationReply_sequence[] = {
  { &hf_s1ap_x2TNLConfigurationInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_X2TNLConfigurationInfo },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SONInformationReply(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SONInformationReply, SONInformationReply_sequence);

  return offset;
}



static int
dissect_s1ap_SONInformation_Extension(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_ProtocolIE_SingleContainer(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const value_string s1ap_SONInformation_vals[] = {
  {   0, "sONInformationRequest" },
  {   1, "sONInformationReply" },
  {   2, "sONInformation-Extension" },
  { 0, NULL }
};

static const per_choice_t SONInformation_choice[] = {
  {   0, &hf_s1ap_sONInformationRequest, ASN1_EXTENSION_ROOT    , dissect_s1ap_SONInformationRequest },
  {   1, &hf_s1ap_sONInformationReply, ASN1_EXTENSION_ROOT    , dissect_s1ap_SONInformationReply },
  {   2, &hf_s1ap_sONInformation_Extension, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_SONInformation_Extension },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_SONInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SONInformation, SONInformation_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t EN_DCSONConfigurationTransfer_sequence[] = {
  { &hf_s1ap_transfertype   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EN_DCSONTransferType },
  { &hf_s1ap_sONInformation , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SONInformation },
  { &hf_s1ap_x2TNLConfigInfo, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_X2TNLConfigurationInfo },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EN_DCSONConfigurationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EN_DCSONConfigurationTransfer, EN_DCSONConfigurationTransfer_sequence);

  return offset;
}


static const value_string s1ap_EndIndication_vals[] = {
  {   0, "no-further-data" },
  {   1, "further-data-exists" },
  { 0, NULL }
};


static int
dissect_s1ap_EndIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_EnhancedCoverageRestricted_vals[] = {
  {   0, "restricted" },
  { 0, NULL }
};


static int
dissect_s1ap_EnhancedCoverageRestricted(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_CE_ModeBRestricted_vals[] = {
  {   0, "restricted" },
  {   1, "not-restricted" },
  { 0, NULL }
};


static int
dissect_s1ap_CE_ModeBRestricted(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t EPLMNs_sequence_of[1] = {
  { &hf_s1ap_EPLMNs_item    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
};

static int
dissect_s1ap_EPLMNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_EPLMNs, EPLMNs_sequence_of,
                                                  1, maxnoofEPLMNs, FALSE);

  return offset;
}


static const value_string s1ap_EventType_vals[] = {
  {   0, "direct" },
  {   1, "change-of-serve-cell" },
  {   2, "stop-change-of-serve-cell" },
  { 0, NULL }
};


static int
dissect_s1ap_EventType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t E_RABInformationList_sequence_of[1] = {
  { &hf_s1ap_E_RABInformationList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABInformationList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABInformationList, E_RABInformationList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABInformationListItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_dL_Forwarding  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_DL_Forwarding },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABInformationListItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABInformationListItem, E_RABInformationListItem_sequence);

  return offset;
}


static const per_sequence_t E_RABList_sequence_of[1] = {
  { &hf_s1ap_E_RABList_item , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABList, E_RABList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_cause          , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cause },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABItem, E_RABItem_sequence);

  return offset;
}



static int
dissect_s1ap_QCI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}


static const per_sequence_t GBR_QosInformation_sequence[] = {
  { &hf_s1ap_e_RAB_MaximumBitrateDL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_e_RAB_MaximumBitrateUL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_e_RAB_GuaranteedBitrateDL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_e_RAB_GuaranteedBitrateUL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_GBR_QosInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_GBR_QosInformation, GBR_QosInformation_sequence);

  return offset;
}


static const per_sequence_t E_RABLevelQoSParameters_sequence[] = {
  { &hf_s1ap_qCI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_QCI },
  { &hf_s1ap_allocationRetentionPriority, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_AllocationAndRetentionPriority },
  { &hf_s1ap_gbrQosInformation, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_GBR_QosInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABLevelQoSParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABLevelQoSParameters, E_RABLevelQoSParameters_sequence);

  return offset;
}


static const per_sequence_t E_RABUsageReportList_sequence_of[1] = {
  { &hf_s1ap_E_RABUsageReportList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABUsageReportList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABUsageReportList, E_RABUsageReportList_sequence_of,
                                                  1, maxnooftimeperiods, FALSE);

  return offset;
}



static int
dissect_s1ap_T_startTimestamp(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1236 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *timestamp_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, FALSE, &timestamp_tvb);




#line 1240 "./asn1/s1ap/s1ap.cnf"
  if (timestamp_tvb) {
    proto_item_append_text(actx->created_item, " (%s)", tvb_ntp_fmt_ts_sec(timestamp_tvb, 0));
  }


  return offset;
}



static int
dissect_s1ap_T_endTimestamp(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1245 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *timestamp_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, FALSE, &timestamp_tvb);




#line 1249 "./asn1/s1ap/s1ap.cnf"
  if (timestamp_tvb) {
    proto_item_append_text(actx->created_item, " (%s)", tvb_ntp_fmt_ts_sec(timestamp_tvb, 0));
  }


  return offset;
}



static int
dissect_s1ap_INTEGER_0_18446744073709551615(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer_64b(tvb, offset, actx, tree, hf_index,
                                                            0U, G_GUINT64_CONSTANT(18446744073709551615), NULL, FALSE);

  return offset;
}


static const per_sequence_t E_RABUsageReportItem_sequence[] = {
  { &hf_s1ap_startTimestamp , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_startTimestamp },
  { &hf_s1ap_endTimestamp   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_endTimestamp },
  { &hf_s1ap_usageCountUL   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_18446744073709551615 },
  { &hf_s1ap_usageCountDL   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_18446744073709551615 },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABUsageReportItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABUsageReportItem, E_RABUsageReportItem_sequence);

  return offset;
}


static const value_string s1ap_Ethernet_Type_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_Ethernet_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_EUTRANRoundTripDelayEstimationInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 2047U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_ExpectedActivityPeriod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 181U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_ExpectedIdlePeriod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 181U, NULL, TRUE);

  return offset;
}


static const value_string s1ap_SourceOfUEActivityBehaviourInformation_vals[] = {
  {   0, "subscription-information" },
  {   1, "statistics" },
  { 0, NULL }
};


static int
dissect_s1ap_SourceOfUEActivityBehaviourInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t ExpectedUEActivityBehaviour_sequence[] = {
  { &hf_s1ap_expectedActivityPeriod, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ExpectedActivityPeriod },
  { &hf_s1ap_expectedIdlePeriod, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ExpectedIdlePeriod },
  { &hf_s1ap_sourceofUEActivityBehaviourInformation, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_SourceOfUEActivityBehaviourInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ExpectedUEActivityBehaviour(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ExpectedUEActivityBehaviour, ExpectedUEActivityBehaviour_sequence);

  return offset;
}


static const value_string s1ap_ExpectedHOInterval_vals[] = {
  {   0, "sec15" },
  {   1, "sec30" },
  {   2, "sec60" },
  {   3, "sec90" },
  {   4, "sec120" },
  {   5, "sec180" },
  {   6, "long-time" },
  { 0, NULL }
};


static int
dissect_s1ap_ExpectedHOInterval(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     7, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t ExpectedUEBehaviour_sequence[] = {
  { &hf_s1ap_expectedActivity, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ExpectedUEActivityBehaviour },
  { &hf_s1ap_expectedHOInterval, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ExpectedHOInterval },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ExpectedUEBehaviour(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ExpectedUEBehaviour, ExpectedUEBehaviour_sequence);

  return offset;
}



static int
dissect_s1ap_ExtendedBitRate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer_64b(tvb, offset, actx, tree, hf_index,
                                                            10000000001U, G_GUINT64_CONSTANT(4000000000000), NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_ExtendedRNC_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            4096U, 65535U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_ExtendedRepetitionPeriod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            4096U, 131071U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_Extended_UEIdentityIndexValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     14, 14, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_FiveQI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, TRUE);

  return offset;
}


static const value_string s1ap_ForbiddenInterRATs_vals[] = {
  {   0, "all" },
  {   1, "geran" },
  {   2, "utran" },
  {   3, "cdma2000" },
  {   4, "geranandutran" },
  {   5, "cdma2000andutran" },
  { 0, NULL }
};


static int
dissect_s1ap_ForbiddenInterRATs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 2, NULL);

  return offset;
}


static const per_sequence_t ForbiddenTACs_sequence_of[1] = {
  { &hf_s1ap_ForbiddenTACs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAC },
};

static int
dissect_s1ap_ForbiddenTACs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ForbiddenTACs, ForbiddenTACs_sequence_of,
                                                  1, maxnoofForbTACs, FALSE);

  return offset;
}


static const per_sequence_t ForbiddenTAs_Item_sequence[] = {
  { &hf_s1ap_pLMN_Identity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_forbiddenTACs  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ForbiddenTACs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ForbiddenTAs_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ForbiddenTAs_Item, ForbiddenTAs_Item_sequence);

  return offset;
}


static const per_sequence_t ForbiddenTAs_sequence_of[1] = {
  { &hf_s1ap_ForbiddenTAs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ForbiddenTAs_Item },
};

static int
dissect_s1ap_ForbiddenTAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ForbiddenTAs, ForbiddenTAs_sequence_of,
                                                  1, maxnoofEPLMNsPlusOne, FALSE);

  return offset;
}


static const per_sequence_t ForbiddenLACs_sequence_of[1] = {
  { &hf_s1ap_ForbiddenLACs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_LAC },
};

static int
dissect_s1ap_ForbiddenLACs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ForbiddenLACs, ForbiddenLACs_sequence_of,
                                                  1, maxnoofForbLACs, FALSE);

  return offset;
}


static const per_sequence_t ForbiddenLAs_Item_sequence[] = {
  { &hf_s1ap_pLMN_Identity  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_forbiddenLACs  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ForbiddenLACs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ForbiddenLAs_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ForbiddenLAs_Item, ForbiddenLAs_Item_sequence);

  return offset;
}


static const per_sequence_t ForbiddenLAs_sequence_of[1] = {
  { &hf_s1ap_ForbiddenLAs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ForbiddenLAs_Item },
};

static int
dissect_s1ap_ForbiddenLAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ForbiddenLAs, ForbiddenLAs_sequence_of,
                                                  1, maxnoofEPLMNsPlusOne, FALSE);

  return offset;
}



static int
dissect_s1ap_GTP_TEID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       4, 4, FALSE, NULL);

  return offset;
}


static const value_string s1ap_GUMMEIType_vals[] = {
  {   0, "native" },
  {   1, "mapped" },
  {   2, "mappedFrom5G" },
  { 0, NULL }
};


static int
dissect_s1ap_GUMMEIType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 1, NULL);

  return offset;
}


static const value_string s1ap_GWContextReleaseIndication_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_GWContextReleaseIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_HandoverFlag_vals[] = {
  {   0, "handoverPreparation" },
  { 0, NULL }
};


static int
dissect_s1ap_HandoverFlag(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t HandoverRestrictionList_sequence[] = {
  { &hf_s1ap_servingPLMN    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_equivalentPLMNs, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_EPLMNs },
  { &hf_s1ap_forbiddenTAs   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ForbiddenTAs },
  { &hf_s1ap_forbiddenLAs   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ForbiddenLAs },
  { &hf_s1ap_forbiddenInterRATs, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ForbiddenInterRATs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverRestrictionList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverRestrictionList, HandoverRestrictionList_sequence);

  return offset;
}


static const value_string s1ap_HandoverType_vals[] = {
  { intralte, "intralte" },
  { ltetoutran, "ltetoutran" },
  { ltetogeran, "ltetogeran" },
  { utrantolte, "utrantolte" },
  { gerantolte, "gerantolte" },
  { eps_to_5gs, "eps-to-5gs" },
  { fivegs_to_eps, "fivegs-to-eps" },
  { 0, NULL }
};


static int
dissect_s1ap_HandoverType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 373 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, &s1ap_data->handover_type_value, TRUE, 2, NULL);




  return offset;
}



static int
dissect_s1ap_Masked_IMEISV(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     64, 64, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_MeasurementsToActivate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1189 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_measurementsToActivate_M1,
      &hf_s1ap_measurementsToActivate_M2,
      &hf_s1ap_measurementsToActivate_M3,
      &hf_s1ap_measurementsToActivate_M4,
      &hf_s1ap_measurementsToActivate_M5,
      &hf_s1ap_measurementsToActivate_LoggingM1FromEventTriggered,
      &hf_s1ap_measurementsToActivate_M6,
      &hf_s1ap_measurementsToActivate_M7,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_MeasurementsToActivate);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 1, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const value_string s1ap_M1ReportingTrigger_vals[] = {
  {   0, "periodic" },
  {   1, "a2eventtriggered" },
  {   2, "a2eventtriggered-periodic" },
  { 0, NULL }
};


static int
dissect_s1ap_M1ReportingTrigger(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 1, NULL);

  return offset;
}



static int
dissect_s1ap_Threshold_RSRP(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 97U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_Threshold_RSRQ(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 34U, NULL, FALSE);

  return offset;
}


static const value_string s1ap_MeasurementThresholdA2_vals[] = {
  {   0, "threshold-RSRP" },
  {   1, "threshold-RSRQ" },
  { 0, NULL }
};

static const per_choice_t MeasurementThresholdA2_choice[] = {
  {   0, &hf_s1ap_threshold_RSRP , ASN1_EXTENSION_ROOT    , dissect_s1ap_Threshold_RSRP },
  {   1, &hf_s1ap_threshold_RSRQ , ASN1_EXTENSION_ROOT    , dissect_s1ap_Threshold_RSRQ },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_MeasurementThresholdA2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_MeasurementThresholdA2, MeasurementThresholdA2_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t M1ThresholdEventA2_sequence[] = {
  { &hf_s1ap_measurementThreshold, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MeasurementThresholdA2 },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M1ThresholdEventA2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M1ThresholdEventA2, M1ThresholdEventA2_sequence);

  return offset;
}


static const value_string s1ap_ReportIntervalMDT_vals[] = {
  {   0, "ms120" },
  {   1, "ms240" },
  {   2, "ms480" },
  {   3, "ms640" },
  {   4, "ms1024" },
  {   5, "ms2048" },
  {   6, "ms5120" },
  {   7, "ms10240" },
  {   8, "min1" },
  {   9, "min6" },
  {  10, "min12" },
  {  11, "min30" },
  {  12, "min60" },
  { 0, NULL }
};


static int
dissect_s1ap_ReportIntervalMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     13, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string s1ap_ReportAmountMDT_vals[] = {
  {   0, "r1" },
  {   1, "r2" },
  {   2, "r4" },
  {   3, "r8" },
  {   4, "r16" },
  {   5, "r32" },
  {   6, "r64" },
  {   7, "rinfinity" },
  { 0, NULL }
};


static int
dissect_s1ap_ReportAmountMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t M1PeriodicReporting_sequence[] = {
  { &hf_s1ap_reportInterval , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ReportIntervalMDT },
  { &hf_s1ap_reportAmount   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ReportAmountMDT },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M1PeriodicReporting(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M1PeriodicReporting, M1PeriodicReporting_sequence);

  return offset;
}


static const per_sequence_t ImmediateMDT_sequence[] = {
  { &hf_s1ap_measurementsToActivate, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MeasurementsToActivate },
  { &hf_s1ap_m1reportingTrigger, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M1ReportingTrigger },
  { &hf_s1ap_m1thresholdeventA2, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_M1ThresholdEventA2 },
  { &hf_s1ap_m1periodicReporting, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_M1PeriodicReporting },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ImmediateMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ImmediateMDT, ImmediateMDT_sequence);

  return offset;
}



static int
dissect_s1ap_IMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1372 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       3, 8, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_IMSI);
    dissect_e212_imsi(parameter_tvb, actx->pinfo, subtree, 0, tvb_reported_length(parameter_tvb), FALSE);
  }



  return offset;
}


static const per_sequence_t RecommendedENBList_sequence_of[1] = {
  { &hf_s1ap_RecommendedENBList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_RecommendedENBList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_RecommendedENBList, RecommendedENBList_sequence_of,
                                                  1, maxnoofRecommendedENBs, FALSE);

  return offset;
}


static const per_sequence_t RecommendedENBsForPaging_sequence[] = {
  { &hf_s1ap_recommendedENBList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RecommendedENBList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RecommendedENBsForPaging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RecommendedENBsForPaging, RecommendedENBsForPaging_sequence);

  return offset;
}


static const per_sequence_t InformationOnRecommendedCellsAndENBsForPaging_sequence[] = {
  { &hf_s1ap_recommendedCellsForPaging, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RecommendedCellsForPaging },
  { &hf_s1ap_recommendENBsForPaging, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RecommendedENBsForPaging },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InformationOnRecommendedCellsAndENBsForPaging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InformationOnRecommendedCellsAndENBsForPaging, InformationOnRecommendedCellsAndENBsForPaging_sequence);

  return offset;
}



static int
dissect_s1ap_IntegrityProtectionAlgorithms(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1044 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, TRUE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_integrityProtectionAlgorithms_EIA1,
      &hf_s1ap_integrityProtectionAlgorithms_EIA2,
      &hf_s1ap_integrityProtectionAlgorithms_EIA3,
      &hf_s1ap_integrityProtectionAlgorithms_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_IntegrityProtectionAlgorithms);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 2, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_InterfacesToTrace(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 926 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_interfacesToTrace_S1_MME,
      &hf_s1ap_interfacesToTrace_X2,
      &hf_s1ap_interfacesToTrace_Uu,
      &hf_s1ap_interfacesToTrace_F1_C,
      &hf_s1ap_interfacesToTrace_E1,
      &hf_s1ap_interfacesToTrace_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_InterfacesToTrace);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 1, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_INTEGER_0_127(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 127U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_INTEGER_1_100(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 100U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_INTEGER_1_1024(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 1024U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_maxNARFCN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, maxNARFCN, NULL, FALSE);

  return offset;
}


static const value_string s1ap_T_subcarrierSpacingSSB_vals[] = {
  {   0, "kHz15" },
  {   1, "kHz30" },
  {   2, "kHz60" },
  {   3, "kHz120" },
  {   4, "kHz240" },
  { 0, NULL }
};


static int
dissect_s1ap_T_subcarrierSpacingSSB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_1_maxRS_IndexCellQual(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, maxRS_IndexCellQual, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_T_sMTC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 958 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *ssb_mtc_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &ssb_mtc_tvb);

  if (ssb_mtc_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_sMTC);
    dissect_lte_rrc_MTC_SSB_NR_r15_PDU(ssb_mtc_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_T_threshRS_Index_r15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 966 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *threshold_list_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &threshold_list_tvb);

  if (threshold_list_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_threshRS_Index_r15);
    dissect_lte_rrc_ThresholdListNR_r15_PDU(threshold_list_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_T_sSBToMeasure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 974 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *ssb_to_meas_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &ssb_to_meas_tvb);

  if (ssb_to_meas_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_sSBToMeasure);
    dissect_lte_rrc_SSB_ToMeasure_r15_PDU(ssb_to_meas_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_T_sSRSSIMeasurement(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 982 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *ss_rssi_meas_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &ss_rssi_meas_tvb);

  if (ss_rssi_meas_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_sSRSSIMeasurement);
    dissect_lte_rrc_SS_RSSI_Measurement_r15_PDU(ss_rssi_meas_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_T_quantityConfigNR_R15(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 990 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *quantity_config_nr_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &quantity_config_nr_tvb);

  if (quantity_config_nr_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_quantityConfigNR_R15);
    dissect_lte_rrc_QuantityConfigNR_r15_PDU(quantity_config_nr_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_T_blackCellsToAddModList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 998 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *black_cells_list_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &black_cells_list_tvb);

  if (black_cells_list_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_blackCellsToAddModList);
    dissect_lte_rrc_CellsToAddModListNR_r15_PDU(black_cells_list_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}


static const per_sequence_t InterSystemMeasurementItem_sequence[] = {
  { &hf_s1ap_freqBandIndicatorNR, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_1_1024 },
  { &hf_s1ap_sSBfrequencies , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_maxNARFCN },
  { &hf_s1ap_subcarrierSpacingSSB, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_T_subcarrierSpacingSSB },
  { &hf_s1ap_maxRSIndexCellQual, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_1_maxRS_IndexCellQual },
  { &hf_s1ap_sMTC           , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_sMTC },
  { &hf_s1ap_threshRS_Index_r15, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_threshRS_Index_r15 },
  { &hf_s1ap_sSBToMeasure   , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_sSBToMeasure },
  { &hf_s1ap_sSRSSIMeasurement, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_sSRSSIMeasurement },
  { &hf_s1ap_quantityConfigNR_R15, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_quantityConfigNR_R15 },
  { &hf_s1ap_blackCellsToAddModList, ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_T_blackCellsToAddModList },
  { &hf_s1ap_iE_Extensions  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InterSystemMeasurementItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InterSystemMeasurementItem, InterSystemMeasurementItem_sequence);

  return offset;
}


static const per_sequence_t InterSystemMeasurementList_sequence_of[1] = {
  { &hf_s1ap_InterSystemMeasurementList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_InterSystemMeasurementItem },
};

static int
dissect_s1ap_InterSystemMeasurementList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_InterSystemMeasurementList, InterSystemMeasurementList_sequence_of,
                                                  1, maxnooffrequencies, FALSE);

  return offset;
}


static const per_sequence_t InterSystemMeasurementParameters_sequence[] = {
  { &hf_s1ap_measurementDuration, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_1_100 },
  { &hf_s1ap_interSystemMeasurementList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_InterSystemMeasurementList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InterSystemMeasurementParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InterSystemMeasurementParameters, InterSystemMeasurementParameters_sequence);

  return offset;
}


static const per_sequence_t IntersystemMeasurementConfiguration_sequence[] = {
  { &hf_s1ap_rSRP           , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_127 },
  { &hf_s1ap_rSRQ           , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_127 },
  { &hf_s1ap_sINR           , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_127 },
  { &hf_s1ap_interSystemMeasurementParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_InterSystemMeasurementParameters },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_IntersystemMeasurementConfiguration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_IntersystemMeasurementConfiguration, IntersystemMeasurementConfiguration_sequence);

  return offset;
}



static int
dissect_s1ap_IntersystemSONConfigurationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1511 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_IntersystemSONConfigurationTransfer);
    dissect_ngap_SONConfigurationTransfer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}


static const value_string s1ap_IMSvoiceEPSfallbackfrom5G_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_IMSvoiceEPSfallbackfrom5G(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_IAB_Authorized_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_IAB_Authorized(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_IAB_Node_Indication_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_IAB_Node_Indication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_IAB_Supported_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_IAB_Supported(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_KillAllWarningMessages_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_KillAllWarningMessages(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, FALSE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Time_UE_StayedInCell(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}


static const per_sequence_t LastVisitedEUTRANCellInformation_sequence[] = {
  { &hf_s1ap_global_Cell_ID , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_cellType       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellType },
  { &hf_s1ap_time_UE_StayedInCell, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Time_UE_StayedInCell },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LastVisitedEUTRANCellInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LastVisitedEUTRANCellInformation, LastVisitedEUTRANCellInformation_sequence);

  return offset;
}



static int
dissect_s1ap_LastVisitedUTRANCellInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1093 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_LastVisitedUTRANCellInformation);
    TRY {
      dissect_ranap_LastVisitedUTRANCell_Item_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}


static const value_string s1ap_LastVisitedGERANCellInformation_vals[] = {
  {   0, "undefined" },
  { 0, NULL }
};

static const per_choice_t LastVisitedGERANCellInformation_choice[] = {
  {   0, &hf_s1ap_undefined      , ASN1_EXTENSION_ROOT    , dissect_s1ap_NULL },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_LastVisitedGERANCellInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_LastVisitedGERANCellInformation, LastVisitedGERANCellInformation_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_LastVisitedNGRANCellInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1075 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_LastVisitedNGRANCellInformation);
    TRY {
      dissect_ngap_LastVisitedNGRANCellInformation_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}


static const value_string s1ap_LastVisitedCell_Item_vals[] = {
  {   0, "e-UTRAN-Cell" },
  {   1, "uTRAN-Cell" },
  {   2, "gERAN-Cell" },
  {   3, "nG-RAN-Cell" },
  { 0, NULL }
};

static const per_choice_t LastVisitedCell_Item_choice[] = {
  {   0, &hf_s1ap_e_UTRAN_Cell   , ASN1_EXTENSION_ROOT    , dissect_s1ap_LastVisitedEUTRANCellInformation },
  {   1, &hf_s1ap_uTRAN_Cell     , ASN1_EXTENSION_ROOT    , dissect_s1ap_LastVisitedUTRANCellInformation },
  {   2, &hf_s1ap_gERAN_Cell     , ASN1_EXTENSION_ROOT    , dissect_s1ap_LastVisitedGERANCellInformation },
  {   3, &hf_s1ap_nG_RAN_Cell    , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_LastVisitedNGRANCellInformation },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_LastVisitedCell_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_LastVisitedCell_Item, LastVisitedCell_Item_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_LPPa_PDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 314 "./asn1/s1ap/s1ap.cnf"

  tvbuff_t *parameter_tvb=NULL;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);


  if ((tvb_reported_length(parameter_tvb)>0)&&(lppa_handle))
    call_dissector(lppa_handle, parameter_tvb, actx->pinfo, tree);



  return offset;
}



static int
dissect_s1ap_LHN_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1224 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       32, 256, FALSE, &parameter_tvb);

  actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, -1, ENC_UTF_8|ENC_NA);


  return offset;
}


static const value_string s1ap_Links_to_log_vals[] = {
  {   0, "uplink" },
  {   1, "downlink" },
  {   2, "both-uplink-and-downlink" },
  { 0, NULL }
};


static int
dissect_s1ap_Links_to_log(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_T_pattern_period_vals[] = {
  {   0, "ms1280" },
  {   1, "ms2560" },
  {   2, "ms5120" },
  {   3, "ms10240" },
  { 0, NULL }
};


static int
dissect_s1ap_T_pattern_period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_10239_(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 10239U, NULL, TRUE);

  return offset;
}


static const per_sequence_t ListeningSubframePattern_sequence[] = {
  { &hf_s1ap_pattern_period , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_pattern_period },
  { &hf_s1ap_pattern_offset , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_10239_ },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ListeningSubframePattern(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ListeningSubframePattern, ListeningSubframePattern_sequence);

  return offset;
}


static const value_string s1ap_LoggingInterval_vals[] = {
  {   0, "ms128" },
  {   1, "ms256" },
  {   2, "ms512" },
  {   3, "ms1024" },
  {   4, "ms2048" },
  {   5, "ms3072" },
  {   6, "ms4096" },
  {   7, "ms6144" },
  { 0, NULL }
};


static int
dissect_s1ap_LoggingInterval(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, FALSE, 0, NULL);

  return offset;
}


static const value_string s1ap_LoggingDuration_vals[] = {
  {   0, "m10" },
  {   1, "m20" },
  {   2, "m40" },
  {   3, "m60" },
  {   4, "m90" },
  {   5, "m120" },
  { 0, NULL }
};


static int
dissect_s1ap_LoggingDuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, FALSE, 0, NULL);

  return offset;
}


static const per_sequence_t LoggedMDT_sequence[] = {
  { &hf_s1ap_loggingInterval, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LoggingInterval },
  { &hf_s1ap_loggingDuration, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LoggingDuration },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LoggedMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LoggedMDT, LoggedMDT_sequence);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_255(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}


static const per_sequence_t MBSFN_ResultToLogInfo_sequence[] = {
  { &hf_s1ap_mBSFN_AreaId   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_255 },
  { &hf_s1ap_carrierFreq    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EARFCN },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MBSFN_ResultToLogInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MBSFN_ResultToLogInfo, MBSFN_ResultToLogInfo_sequence);

  return offset;
}


static const per_sequence_t MBSFN_ResultToLog_sequence_of[1] = {
  { &hf_s1ap_MBSFN_ResultToLog_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_MBSFN_ResultToLogInfo },
};

static int
dissect_s1ap_MBSFN_ResultToLog(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_MBSFN_ResultToLog, MBSFN_ResultToLog_sequence_of,
                                                  1, maxnoofMBSFNAreaMDT, FALSE);

  return offset;
}


static const per_sequence_t LoggedMBSFNMDT_sequence[] = {
  { &hf_s1ap_loggingInterval, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LoggingInterval },
  { &hf_s1ap_loggingDuration, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LoggingDuration },
  { &hf_s1ap_mBSFN_ResultToLog, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_MBSFN_ResultToLog },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LoggedMBSFNMDT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LoggedMBSFNMDT, LoggedMBSFNMDT_sequence);

  return offset;
}


static const value_string s1ap_LTE_M_Indication_vals[] = {
  {   0, "lte-m" },
  { 0, NULL }
};


static int
dissect_s1ap_LTE_M_Indication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_M3period_vals[] = {
  {   0, "ms100" },
  {   1, "ms1000" },
  {   2, "ms10000" },
  {   3, "ms1024" },
  {   4, "ms1280" },
  {   5, "ms2048" },
  {   6, "ms2560" },
  {   7, "ms5120" },
  {   8, "ms10240" },
  {   9, "min1" },
  { 0, NULL }
};


static int
dissect_s1ap_M3period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 7, NULL);

  return offset;
}


static const per_sequence_t M3Configuration_sequence[] = {
  { &hf_s1ap_m3period       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M3period },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M3Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M3Configuration, M3Configuration_sequence);

  return offset;
}


static const value_string s1ap_M4period_vals[] = {
  {   0, "ms1024" },
  {   1, "ms2048" },
  {   2, "ms5120" },
  {   3, "ms10240" },
  {   4, "min1" },
  { 0, NULL }
};


static int
dissect_s1ap_M4period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t M4Configuration_sequence[] = {
  { &hf_s1ap_m4period       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M4period },
  { &hf_s1ap_m4_links_to_log, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Links_to_log },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M4Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M4Configuration, M4Configuration_sequence);

  return offset;
}


static const value_string s1ap_M5period_vals[] = {
  {   0, "ms1024" },
  {   1, "ms2048" },
  {   2, "ms5120" },
  {   3, "ms10240" },
  {   4, "min1" },
  { 0, NULL }
};


static int
dissect_s1ap_M5period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t M5Configuration_sequence[] = {
  { &hf_s1ap_m5period       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M5period },
  { &hf_s1ap_m5_links_to_log, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Links_to_log },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M5Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M5Configuration, M5Configuration_sequence);

  return offset;
}


static const value_string s1ap_M6report_Interval_vals[] = {
  {   0, "ms1024" },
  {   1, "ms2048" },
  {   2, "ms5120" },
  {   3, "ms10240" },
  { 0, NULL }
};


static int
dissect_s1ap_M6report_Interval(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_M6delay_threshold_vals[] = {
  {   0, "ms30" },
  {   1, "ms40" },
  {   2, "ms50" },
  {   3, "ms60" },
  {   4, "ms70" },
  {   5, "ms80" },
  {   6, "ms90" },
  {   7, "ms100" },
  {   8, "ms150" },
  {   9, "ms300" },
  {  10, "ms500" },
  {  11, "ms750" },
  { 0, NULL }
};


static int
dissect_s1ap_M6delay_threshold(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     12, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t M6Configuration_sequence[] = {
  { &hf_s1ap_m6report_Interval, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M6report_Interval },
  { &hf_s1ap_m6delay_threshold, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_M6delay_threshold },
  { &hf_s1ap_m6_links_to_log, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Links_to_log },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M6Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M6Configuration, M6Configuration_sequence);

  return offset;
}



static int
dissect_s1ap_M7period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 60U, NULL, TRUE);

  return offset;
}


static const per_sequence_t M7Configuration_sequence[] = {
  { &hf_s1ap_m7period       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M7period },
  { &hf_s1ap_m7_links_to_log, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Links_to_log },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_M7Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_M7Configuration, M7Configuration_sequence);

  return offset;
}


static const value_string s1ap_MDT_Activation_vals[] = {
  {   0, "immediate-MDT-only" },
  {   1, "immediate-MDT-and-Trace" },
  {   2, "logged-MDT-only" },
  {   3, "logged-MBSFN-MDT" },
  { 0, NULL }
};


static int
dissect_s1ap_MDT_Activation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 1, NULL);

  return offset;
}



static int
dissect_s1ap_MDT_Location_Info(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1208 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_MDT_Location_Info_GNSS,
      &hf_s1ap_MDT_Location_Info_E_CID,
      &hf_s1ap_MDT_Location_Info_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_MDT_Location_Info);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 1, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_MDTMode_Extension(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_ProtocolIE_SingleContainer(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const value_string s1ap_MDTMode_vals[] = {
  {   0, "immediateMDT" },
  {   1, "loggedMDT" },
  {   2, "mDTMode-Extension" },
  { 0, NULL }
};

static const per_choice_t MDTMode_choice[] = {
  {   0, &hf_s1ap_immediateMDT   , ASN1_EXTENSION_ROOT    , dissect_s1ap_ImmediateMDT },
  {   1, &hf_s1ap_loggedMDT      , ASN1_EXTENSION_ROOT    , dissect_s1ap_LoggedMDT },
  {   2, &hf_s1ap_mDTMode_Extension, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_MDTMode_Extension },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_MDTMode(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_MDTMode, MDTMode_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MDT_Configuration_sequence[] = {
  { &hf_s1ap_mdt_Activation , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MDT_Activation },
  { &hf_s1ap_areaScopeOfMDT , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_AreaScopeOfMDT },
  { &hf_s1ap_mDTMode        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MDTMode },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MDT_Configuration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MDT_Configuration, MDT_Configuration_sequence);

  return offset;
}


static const value_string s1ap_ManagementBasedMDTAllowed_vals[] = {
  {   0, "allowed" },
  { 0, NULL }
};


static int
dissect_s1ap_ManagementBasedMDTAllowed(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t MDTPLMNList_sequence_of[1] = {
  { &hf_s1ap_MDTPLMNList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
};

static int
dissect_s1ap_MDTPLMNList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_MDTPLMNList, MDTPLMNList_sequence_of,
                                                  1, maxnoofMDTPLMNs, FALSE);

  return offset;
}


static const value_string s1ap_PrivacyIndicator_vals[] = {
  {   0, "immediate-MDT" },
  {   1, "logged-MDT" },
  { 0, NULL }
};


static int
dissect_s1ap_PrivacyIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_MessageIdentifier(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1114 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, -1,
                                     16, 16, FALSE, NULL, 0, &parameter_tvb, NULL);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_MobilityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     32, 32, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_MMEname(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 286 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb=NULL;
  int length;
  gboolean is_ascii;

  offset = dissect_per_PrintableString(tvb, offset, actx, tree, hf_index,
                                          1, 150, TRUE);


  if (!parameter_tvb)
    return offset;

  length = tvb_reported_length(parameter_tvb);

  is_ascii = tvb_ascii_isprint(parameter_tvb, 0, length);
  if (is_ascii)
     proto_item_append_text(actx->created_item," (%s)",tvb_format_text(actx->pinfo->pool, parameter_tvb, 0, length));



  return offset;
}


static const value_string s1ap_MMEPagingTarget_vals[] = {
  {   0, "global-ENB-ID" },
  {   1, "tAI" },
  { 0, NULL }
};

static const per_choice_t MMEPagingTarget_choice[] = {
  {   0, &hf_s1ap_global_ENB_ID  , ASN1_EXTENSION_ROOT    , dissect_s1ap_Global_ENB_ID },
  {   1, &hf_s1ap_tAI            , ASN1_EXTENSION_ROOT    , dissect_s1ap_TAI },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_MMEPagingTarget(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_MMEPagingTarget, MMEPagingTarget_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_MMERelaySupportIndicator_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_MMERelaySupportIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_MME_UE_S1AP_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1437 "./asn1/s1ap/s1ap.cnf"
  guint32 mme_ue_s1ap_id;
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4294967295U, &mme_ue_s1ap_id, FALSE);

  if (hf_index == hf_s1ap_mME_UE_S1AP_ID) {
    proto_item *item;
    item = proto_tree_add_uint(tree, hf_s1ap_MME_UE_S1AP_ID_PDU, tvb, offset, 0 , mme_ue_s1ap_id );
    proto_item_set_hidden(item);
  }



  return offset;
}



static int
dissect_s1ap_MSClassmark2(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1167 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_MSClassmark);
    de_ms_cm_2(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
  }



  return offset;
}



static int
dissect_s1ap_MSClassmark3(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1175 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_MSClassmark);
    de_ms_cm_3(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
  }



  return offset;
}


static const value_string s1ap_MutingAvailabilityIndication_vals[] = {
  {   0, "available" },
  {   1, "unavailable" },
  { 0, NULL }
};


static int
dissect_s1ap_MutingAvailabilityIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_T_muting_pattern_period_vals[] = {
  {   0, "ms0" },
  {   1, "ms1280" },
  {   2, "ms2560" },
  {   3, "ms5120" },
  {   4, "ms10240" },
  { 0, NULL }
};


static int
dissect_s1ap_T_muting_pattern_period(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t MutingPatternInformation_sequence[] = {
  { &hf_s1ap_muting_pattern_period, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_muting_pattern_period },
  { &hf_s1ap_muting_pattern_offset, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_10239_ },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MutingPatternInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MutingPatternInformation, MutingPatternInformation_sequence);

  return offset;
}



static int
dissect_s1ap_MDT_ConfigurationNR(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1502 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_MDT_ConfigurationNR);
    dissect_ngap_MDT_Configuration_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
  }



  return offset;
}



static int
dissect_s1ap_NAS_PDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 305 "./asn1/s1ap/s1ap.cnf"

tvbuff_t *parameter_tvb=NULL;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);


  if ((tvb_reported_length(parameter_tvb)>0)&&(nas_eps_handle))
    call_dissector(nas_eps_handle,parameter_tvb,actx->pinfo, tree);



  return offset;
}



static int
dissect_s1ap_NASSecurityParametersfromE_UTRAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1380 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_NASSecurityParameters);
    de_emm_sec_par_from_eutra(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
  }



  return offset;
}



static int
dissect_s1ap_NASSecurityParameterstoE_UTRAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1388 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_NASSecurityParameters);
    de_emm_sec_par_to_eutra(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
  }



  return offset;
}


static const value_string s1ap_NB_IoT_DefaultPagingDRX_vals[] = {
  {   0, "v128" },
  {   1, "v256" },
  {   2, "v512" },
  {   3, "v1024" },
  { 0, NULL }
};


static int
dissect_s1ap_NB_IoT_DefaultPagingDRX(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_NB_IoT_PagingDRX_vals[] = {
  {   0, "v32" },
  {   1, "v64" },
  {   2, "v128" },
  {   3, "v256" },
  {   4, "v512" },
  {   5, "v1024" },
  { 0, NULL }
};


static int
dissect_s1ap_NB_IoT_PagingDRX(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_NB_IoT_Paging_eDRX_Cycle_vals[] = {
  {   0, "hf2" },
  {   1, "hf4" },
  {   2, "hf6" },
  {   3, "hf8" },
  {   4, "hf10" },
  {   5, "hf12" },
  {   6, "hf14" },
  {   7, "hf16" },
  {   8, "hf32" },
  {   9, "hf64" },
  {  10, "hf128" },
  {  11, "hf256" },
  {  12, "hf512" },
  {  13, "hf1024" },
  { 0, NULL }
};


static int
dissect_s1ap_NB_IoT_Paging_eDRX_Cycle(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     14, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_NB_IoT_PagingTimeWindow_vals[] = {
  {   0, "s1" },
  {   1, "s2" },
  {   2, "s3" },
  {   3, "s4" },
  {   4, "s5" },
  {   5, "s6" },
  {   6, "s7" },
  {   7, "s8" },
  {   8, "s9" },
  {   9, "s10" },
  {  10, "s11" },
  {  11, "s12" },
  {  12, "s13" },
  {  13, "s14" },
  {  14, "s15" },
  {  15, "s16" },
  { 0, NULL }
};


static int
dissect_s1ap_NB_IoT_PagingTimeWindow(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t NB_IoT_Paging_eDRXInformation_sequence[] = {
  { &hf_s1ap_nB_IoT_paging_eDRX_Cycle, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NB_IoT_Paging_eDRX_Cycle },
  { &hf_s1ap_nB_IoT_pagingTimeWindow, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_NB_IoT_PagingTimeWindow },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NB_IoT_Paging_eDRXInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NB_IoT_Paging_eDRXInformation, NB_IoT_Paging_eDRXInformation_sequence);

  return offset;
}



static int
dissect_s1ap_NB_IoT_RLF_Report_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 863 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_NB_IoT_RLF_Report_Container);
    TRY {
      dissect_lte_rrc_RLF_Report_NB_r16_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}



static int
dissect_s1ap_NB_IoT_UEIdentityIndexValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     12, 12, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const value_string s1ap_NotifySourceeNB_vals[] = {
  {   0, "notifySource" },
  { 0, NULL }
};


static int
dissect_s1ap_NotifySourceeNB(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_NRCellIdentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     36, 36, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t NR_CGI_sequence[] = {
  { &hf_s1ap_pLMNIdentity   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
  { &hf_s1ap_nRCellIdentity , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NRCellIdentity },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NR_CGI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2632 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->number_type = E212_NRCGI;
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NR_CGI, NR_CGI_sequence);




  return offset;
}



static int
dissect_s1ap_NRencryptionAlgorithms(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1263 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, TRUE, NULL, 0, &parameter_tvb, NULL);

  if (parameter_tvb) {
    static int * const fields[] = {
      &hf_s1ap_NRencryptionAlgorithms_NEA1,
      &hf_s1ap_NRencryptionAlgorithms_NEA2,
      &hf_s1ap_NRencryptionAlgorithms_NEA3,
      &hf_s1ap_NRencryptionAlgorithms_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_NRencryptionAlgorithms);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 2, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_NRintegrityProtectionAlgorithms(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1278 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, TRUE, NULL, 0, &parameter_tvb, NULL);

  if (parameter_tvb) {
    static int * const fields[] = {
      &hf_s1ap_NRintegrityProtectionAlgorithms_NIA1,
      &hf_s1ap_NRintegrityProtectionAlgorithms_NIA2,
      &hf_s1ap_NRintegrityProtectionAlgorithms_NIA3,
      &hf_s1ap_NRintegrityProtectionAlgorithms_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_NRintegrityProtectionAlgorithms);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 2, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const value_string s1ap_NRrestrictioninEPSasSecondaryRAT_vals[] = {
  {   0, "nRrestrictedinEPSasSecondaryRAT" },
  { 0, NULL }
};


static int
dissect_s1ap_NRrestrictioninEPSasSecondaryRAT(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_NRrestrictionin5GS_vals[] = {
  {   0, "nRrestrictedin5GS" },
  { 0, NULL }
};


static int
dissect_s1ap_NRrestrictionin5GS(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t NRUESecurityCapabilities_sequence[] = {
  { &hf_s1ap_nRencryptionAlgorithms, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NRencryptionAlgorithms },
  { &hf_s1ap_nRintegrityProtectionAlgorithms, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NRintegrityProtectionAlgorithms },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NRUESecurityCapabilities(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NRUESecurityCapabilities, NRUESecurityCapabilities_sequence);

  return offset;
}



static int
dissect_s1ap_NumberofBroadcastRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 65535U, NULL, FALSE);

  return offset;
}


static const value_string s1ap_VehicleUE_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_VehicleUE(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_PedestrianUE_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_PedestrianUE(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t NRV2XServicesAuthorized_sequence[] = {
  { &hf_s1ap_vehicleUE      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_VehicleUE },
  { &hf_s1ap_pedestrianUE   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PedestrianUE },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NRV2XServicesAuthorized(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NRV2XServicesAuthorized, NRV2XServicesAuthorized_sequence);

  return offset;
}


static const per_sequence_t NRUESidelinkAggregateMaximumBitrate_sequence[] = {
  { &hf_s1ap_uEaggregateMaximumBitRate, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NRUESidelinkAggregateMaximumBitrate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NRUESidelinkAggregateMaximumBitrate, NRUESidelinkAggregateMaximumBitrate_sequence);

  return offset;
}


static const value_string s1ap_OverloadAction_vals[] = {
  {   0, "reject-non-emergency-mo-dt" },
  {   1, "reject-rrc-cr-signalling" },
  {   2, "permit-emergency-sessions-and-mobile-terminated-services-only" },
  {   3, "permit-high-priority-sessions-and-mobile-terminated-services-only" },
  {   4, "reject-delay-tolerant-access" },
  {   5, "permit-high-priority-sessions-and-exception-reporting-and-mobile-terminated-services-only" },
  {   6, "not-accept-mo-data-or-delay-tolerant-access-from-CP-CIoT" },
  { 0, NULL }
};


static int
dissect_s1ap_OverloadAction(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 4, NULL);

  return offset;
}


static const value_string s1ap_OverloadResponse_vals[] = {
  {   0, "overloadAction" },
  { 0, NULL }
};

static const per_choice_t OverloadResponse_choice[] = {
  {   0, &hf_s1ap_overloadAction , ASN1_EXTENSION_ROOT    , dissect_s1ap_OverloadAction },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_OverloadResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_OverloadResponse, OverloadResponse_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_Packet_LossRate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 1000U, NULL, FALSE);

  return offset;
}


static const value_string s1ap_Paging_eDRX_Cycle_vals[] = {
  {   0, "hfhalf" },
  {   1, "hf1" },
  {   2, "hf2" },
  {   3, "hf4" },
  {   4, "hf6" },
  {   5, "hf8" },
  {   6, "hf10" },
  {   7, "hf12" },
  {   8, "hf14" },
  {   9, "hf16" },
  {  10, "hf32" },
  {  11, "hf64" },
  {  12, "hf128" },
  {  13, "hf256" },
  { 0, NULL }
};


static int
dissect_s1ap_Paging_eDRX_Cycle(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     14, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_PagingTimeWindow_vals[] = {
  {   0, "s1" },
  {   1, "s2" },
  {   2, "s3" },
  {   3, "s4" },
  {   4, "s5" },
  {   5, "s6" },
  {   6, "s7" },
  {   7, "s8" },
  {   8, "s9" },
  {   9, "s10" },
  {  10, "s11" },
  {  11, "s12" },
  {  12, "s13" },
  {  13, "s14" },
  {  14, "s15" },
  {  15, "s16" },
  { 0, NULL }
};


static int
dissect_s1ap_PagingTimeWindow(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     16, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t Paging_eDRXInformation_sequence[] = {
  { &hf_s1ap_paging_eDRX_Cycle, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Paging_eDRX_Cycle },
  { &hf_s1ap_pagingTimeWindow, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PagingTimeWindow },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Paging_eDRXInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Paging_eDRXInformation, Paging_eDRXInformation_sequence);

  return offset;
}


static const value_string s1ap_PagingDRX_vals[] = {
  {   0, "v32" },
  {   1, "v64" },
  {   2, "v128" },
  {   3, "v256" },
  { 0, NULL }
};


static int
dissect_s1ap_PagingDRX(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     4, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_PagingPriority_vals[] = {
  {   0, "priolevel1" },
  {   1, "priolevel2" },
  {   2, "priolevel3" },
  {   3, "priolevel4" },
  {   4, "priolevel5" },
  {   5, "priolevel6" },
  {   6, "priolevel7" },
  {   7, "priolevel8" },
  { 0, NULL }
};


static int
dissect_s1ap_PagingPriority(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     8, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_PagingProbabilityInformation_vals[] = {
  {   0, "p00" },
  {   1, "p05" },
  {   2, "p10" },
  {   3, "p15" },
  {   4, "p20" },
  {   5, "p25" },
  {   6, "p30" },
  {   7, "p35" },
  {   8, "p40" },
  {   9, "p45" },
  {  10, "p50" },
  {  11, "p55" },
  {  12, "p60" },
  {  13, "p65" },
  {  14, "p70" },
  {  15, "p75" },
  {  16, "p80" },
  {  17, "p85" },
  {  18, "p90" },
  {  19, "p95" },
  {  20, "p100" },
  { 0, NULL }
};


static int
dissect_s1ap_PagingProbabilityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     21, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t PC5FlowBitRates_sequence[] = {
  { &hf_s1ap_guaranteedFlowBitRate, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_maximumFlowBitRate, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PC5FlowBitRates(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PC5FlowBitRates, PC5FlowBitRates_sequence);

  return offset;
}


static const value_string s1ap_Range_vals[] = {
  {   0, "m50" },
  {   1, "m80" },
  {   2, "m180" },
  {   3, "m200" },
  {   4, "m350" },
  {   5, "m400" },
  {   6, "m500" },
  {   7, "m700" },
  {   8, "m1000" },
  { 0, NULL }
};


static int
dissect_s1ap_Range(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     9, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t PC5QoSFlowItem_sequence[] = {
  { &hf_s1ap_pQI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_FiveQI },
  { &hf_s1ap_pc5FlowBitRates, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PC5FlowBitRates },
  { &hf_s1ap_range          , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_Range },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PC5QoSFlowItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PC5QoSFlowItem, PC5QoSFlowItem_sequence);

  return offset;
}


static const per_sequence_t PC5QoSFlowList_sequence_of[1] = {
  { &hf_s1ap_PC5QoSFlowList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PC5QoSFlowItem },
};

static int
dissect_s1ap_PC5QoSFlowList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_PC5QoSFlowList, PC5QoSFlowList_sequence_of,
                                                  1, maxnoofPC5QoSFlows, FALSE);

  return offset;
}


static const per_sequence_t PC5QoSParameters_sequence[] = {
  { &hf_s1ap_pc5QoSFlowList , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PC5QoSFlowList },
  { &hf_s1ap_pc5LinkAggregatedBitRates, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PC5QoSParameters(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PC5QoSParameters, PC5QoSParameters_sequence);

  return offset;
}


static const value_string s1ap_PendingDataIndication_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_PendingDataIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Port_Number(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 354 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       2, 2, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const value_string s1ap_ProSeDirectDiscovery_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_ProSeDirectDiscovery(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_ProSeDirectCommunication_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_ProSeDirectCommunication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t ProSeAuthorized_sequence[] = {
  { &hf_s1ap_proSeDirectDiscovery, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProSeDirectDiscovery },
  { &hf_s1ap_proSeDirectCommunication, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProSeDirectCommunication },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ProSeAuthorized(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ProSeAuthorized, ProSeAuthorized_sequence);

  return offset;
}


static const value_string s1ap_ProSeUEtoNetworkRelaying_vals[] = {
  {   0, "authorized" },
  {   1, "not-authorized" },
  { 0, NULL }
};


static int
dissect_s1ap_ProSeUEtoNetworkRelaying(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_PS_ServiceNotAvailable_vals[] = {
  {   0, "ps-service-not-available" },
  { 0, NULL }
};


static int
dissect_s1ap_PS_ServiceNotAvailable(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t PSCellInformation_sequence[] = {
  { &hf_s1ap_nCGI           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NR_CGI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PSCellInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PSCellInformation, PSCellInformation_sequence);

  return offset;
}



static int
dissect_s1ap_ReceiveStatusOfULPDCPSDUsExtended(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     1, 16384, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     1, 131072, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_4095(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}


static const per_sequence_t RecommendedCellItem_sequence[] = {
  { &hf_s1ap_eUTRAN_CGI     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_timeStayedInCell, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_4095 },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RecommendedCellItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RecommendedCellItem, RecommendedCellItem_sequence);

  return offset;
}


static const per_sequence_t RecommendedENBItem_sequence[] = {
  { &hf_s1ap_mMEPagingTarget, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MMEPagingTarget },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RecommendedENBItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RecommendedENBItem, RecommendedENBItem_sequence);

  return offset;
}


static const value_string s1ap_RelayNode_Indicator_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_RelayNode_Indicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_RAT_Type_vals[] = {
  { nbiot, "nbiot" },
  { 0, NULL }
};


static int
dissect_s1ap_RAT_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1410 "./asn1/s1ap/s1ap.cnf"
  guint32 rat_type = 0xffffffff;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, &rat_type, TRUE, 0, NULL);

  if (s1ap_data->s1ap_conv && s1ap_data->supported_ta && (rat_type == nbiot)) {
    guint64 *key;
    guint i;

    for (i = 0; i < wmem_array_get_count(s1ap_data->supported_ta->plmn); i++) {
      key = wmem_new(wmem_file_scope(), guint64);
      *key = ((*(guint32*)wmem_array_index(s1ap_data->supported_ta->plmn, i)) << 16) | s1ap_data->supported_ta->tac;
      wmem_map_insert(s1ap_data->s1ap_conv->nbiot_ta, key, GUINT_TO_POINTER(1));
    }
  }



  return offset;
}


static const value_string s1ap_ReportArea_vals[] = {
  {   0, "ecgi" },
  { 0, NULL }
};


static int
dissect_s1ap_ReportArea(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t RequestType_sequence[] = {
  { &hf_s1ap_eventType      , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EventType },
  { &hf_s1ap_reportArea     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ReportArea },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RequestType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RequestType, RequestType_sequence);

  return offset;
}


static const value_string s1ap_RequestTypeAdditionalInfo_vals[] = {
  {   0, "includePSCell" },
  { 0, NULL }
};


static int
dissect_s1ap_RequestTypeAdditionalInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_RIMInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 712 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);


  if (!parameter_tvb)
    return offset;

  subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_RIMInformation);
  if ((tvb_reported_length(parameter_tvb)>0)&&(bssgp_handle)){
    col_set_fence(actx->pinfo->cinfo, COL_INFO);
    call_dissector(bssgp_handle,parameter_tvb,actx->pinfo, subtree);
  }




  return offset;
}



static int
dissect_s1ap_RNC_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}


static const per_sequence_t TargetRNC_ID_sequence[] = {
  { &hf_s1ap_lAI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_LAI },
  { &hf_s1ap_rAC            , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_RAC },
  { &hf_s1ap_rNC_ID         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RNC_ID },
  { &hf_s1ap_extendedRNC_ID , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ExtendedRNC_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TargetRNC_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TargetRNC_ID, TargetRNC_ID_sequence);

  return offset;
}



static int
dissect_s1ap_OCTET_STRING_SIZE_16(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       16, 16, FALSE, NULL);

  return offset;
}


static const value_string s1ap_RIMRoutingAddress_vals[] = {
  {   0, "gERAN-Cell-ID" },
  {   1, "targetRNC-ID" },
  {   2, "eHRPD-Sector-ID" },
  { 0, NULL }
};

static const per_choice_t RIMRoutingAddress_choice[] = {
  {   0, &hf_s1ap_gERAN_Cell_ID  , ASN1_EXTENSION_ROOT    , dissect_s1ap_GERAN_Cell_ID },
  {   1, &hf_s1ap_targetRNC_ID   , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_TargetRNC_ID },
  {   2, &hf_s1ap_eHRPD_Sector_ID, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_OCTET_STRING_SIZE_16 },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_RIMRoutingAddress(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_RIMRoutingAddress, RIMRoutingAddress_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RIMTransfer_sequence[] = {
  { &hf_s1ap_rIMInformation , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RIMInformation },
  { &hf_s1ap_rIMRoutingAddress, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_RIMRoutingAddress },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RIMTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RIMTransfer, RIMTransfer_sequence);

  return offset;
}



static int
dissect_s1ap_RepetitionPeriod(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 4095U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_UE_RLF_Report_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 825 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UE_RLF_Report_Container);
      TRY {
        dissect_lte_rrc_RLF_Report_r9_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      }
      CATCH_BOUNDS_ERRORS {
        show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
      }
      ENDTRY;
  }



  return offset;
}



static int
dissect_s1ap_UE_RLF_Report_Container_for_extended_bands(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 845 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UE_RLF_Report_Container_for_extended_bands);
    TRY {
      dissect_lte_rrc_RLF_Report_v9e0_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}


static const per_sequence_t RLFReportInformation_sequence[] = {
  { &hf_s1ap_uE_RLF_Report_Container, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_UE_RLF_Report_Container },
  { &hf_s1ap_uE_RLF_Report_Container_for_extended_bands, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_UE_RLF_Report_Container_for_extended_bands },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RLFReportInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RLFReportInformation, RLFReportInformation_sequence);

  return offset;
}



static int
dissect_s1ap_RRC_Container(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 573 "./asn1/s1ap/s1ap.cnf"


  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_RRCContainer);

    switch(s1ap_data->transparent_container_type){
      case SOURCE_TO_TARGET_TRANSPARENT_CONTAINER:
        /* 9.2.1.7 Source eNB to Target eNB Transparent Container */
        if ((s1ap_is_nbiot_ue(actx->pinfo) && (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_AUTOMATIC)) ||
            (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_NBIOT)) {
          TRY {
            dissect_lte_rrc_HandoverPreparationInformation_NB_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
          }
          CATCH_BOUNDS_ERRORS {
            show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
          }
          ENDTRY;
        } else {
          TRY {
            dissect_lte_rrc_HandoverPreparationInformation_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
          }
          CATCH_BOUNDS_ERRORS {
            show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
          }
          ENDTRY;
        }
        break;
      case TARGET_TO_SOURCE_TRANSPARENT_CONTAINER:
        /* 9.2.1.8 Target eNB to Source eNB Transparent Container */
          TRY {
            dissect_lte_rrc_HandoverCommand_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
          }
          CATCH_BOUNDS_ERRORS {
            show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
          }
          ENDTRY;
        break;
      default:
        break;
    }
  }



  return offset;
}


static const value_string s1ap_RRC_Establishment_Cause_vals[] = {
  {   0, "emergency" },
  {   1, "highPriorityAccess" },
  {   2, "mt-Access" },
  {   3, "mo-Signalling" },
  {   4, "mo-Data" },
  {   5, "delay-TolerantAccess" },
  {   6, "mo-VoiceCall" },
  {   7, "mo-ExceptionData" },
  { 0, NULL }
};


static int
dissect_s1ap_RRC_Establishment_Cause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 3, NULL);

  return offset;
}


static const per_sequence_t ECGIListForRestart_sequence_of[1] = {
  { &hf_s1ap_ECGIListForRestart_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
};

static int
dissect_s1ap_ECGIListForRestart(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ECGIListForRestart, ECGIListForRestart_sequence_of,
                                                  1, maxnoofCellsforRestart, FALSE);

  return offset;
}



static int
dissect_s1ap_Routing_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_SecurityKey(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     256, 256, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 7U, NULL, FALSE);

  return offset;
}


static const per_sequence_t SecurityContext_sequence[] = {
  { &hf_s1ap_nextHopChainingCount, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_7 },
  { &hf_s1ap_nextHopParameter, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SecurityKey },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SecurityContext(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SecurityContext, SecurityContext_sequence);

  return offset;
}


static const value_string s1ap_SecondaryRATType_vals[] = {
  {   0, "nR" },
  {   1, "unlicensed" },
  { 0, NULL }
};


static int
dissect_s1ap_SecondaryRATType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 1, NULL);

  return offset;
}


static const value_string s1ap_SecondaryRATDataUsageRequest_vals[] = {
  {   0, "requested" },
  { 0, NULL }
};


static int
dissect_s1ap_SecondaryRATDataUsageRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t SecondaryRATDataUsageReportList_sequence_of[1] = {
  { &hf_s1ap_SecondaryRATDataUsageReportList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_SecondaryRATDataUsageReportList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_SecondaryRATDataUsageReportList, SecondaryRATDataUsageReportList_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t SecondaryRATDataUsageReportItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_secondaryRATType, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SecondaryRATType },
  { &hf_s1ap_e_RABUsageReportList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RABUsageReportList },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SecondaryRATDataUsageReportItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SecondaryRATDataUsageReportItem, SecondaryRATDataUsageReportItem_sequence);

  return offset;
}



static int
dissect_s1ap_SerialNumber(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1121 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL, 0, &parameter_tvb, NULL);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_SerialNumber);
    proto_tree_add_item(subtree, hf_s1ap_SerialNumber_gs, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
    proto_tree_add_item(subtree, hf_s1ap_SerialNumber_msg_code, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
    proto_tree_add_item(subtree, hf_s1ap_SerialNumber_upd_nb, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const value_string s1ap_ServiceType_vals[] = {
  {   0, "qMC-for-streaming-service" },
  {   1, "qMC-for-MTSI-service" },
  { 0, NULL }
};


static int
dissect_s1ap_ServiceType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_SONInformationReport_vals[] = {
  {   0, "rLFReportInformation" },
  { 0, NULL }
};

static const per_choice_t SONInformationReport_choice[] = {
  {   0, &hf_s1ap_rLFReportInformation, ASN1_EXTENSION_ROOT    , dissect_s1ap_RLFReportInformation },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_SONInformationReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SONInformationReport, SONInformationReport_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t TargeteNB_ID_sequence[] = {
  { &hf_s1ap_global_ENB_ID  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_ENB_ID },
  { &hf_s1ap_selected_TAI   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TargeteNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TargeteNB_ID, TargeteNB_ID_sequence);

  return offset;
}


static const per_sequence_t SourceeNB_ID_sequence[] = {
  { &hf_s1ap_global_ENB_ID  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_ENB_ID },
  { &hf_s1ap_selected_TAI   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_NO_EXTENSIONS     , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SourceeNB_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SourceeNB_ID, SourceeNB_ID_sequence);

  return offset;
}


static const per_sequence_t SONConfigurationTransfer_sequence[] = {
  { &hf_s1ap_targeteNB_ID   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TargeteNB_ID },
  { &hf_s1ap_sourceeNB_ID   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SourceeNB_ID },
  { &hf_s1ap_sONInformation , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SONInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SONConfigurationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SONConfigurationTransfer, SONConfigurationTransfer_sequence);

  return offset;
}



static int
dissect_s1ap_StratumLevel(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 3U, NULL, TRUE);

  return offset;
}


static const per_sequence_t SynchronisationInformation_sequence[] = {
  { &hf_s1ap_sourceStratumLevel, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_StratumLevel },
  { &hf_s1ap_listeningSubframePattern, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ListeningSubframePattern },
  { &hf_s1ap_aggressoreCGI_List, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ECGI_List },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SynchronisationInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SynchronisationInformation, SynchronisationInformation_sequence);

  return offset;
}



static int
dissect_s1ap_Source_ToTarget_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 424 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

    offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);


  if ((g_s1ap_dissect_container)&&(parameter_tvb) && (tvb_reported_length(parameter_tvb) > 0)) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    /* Don't want elements inside container to write to info column */
    col_set_writable(actx->pinfo->cinfo, COL_INFO, FALSE);
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_ToTargetTransparentContainer);

    switch(s1ap_data->handover_type_value){
      /*
      HandoverType ::= ENUMERATED {
      intralte,
      ltetoutran,
      ltetogeran,
      utrantolte,
      gerantolte,
      ...
      eps_to_5gs,
      fivegs_to_eps
      } */
      case intralte:
      /* intralte
        Intra E-UTRAN handover Source eNB to Target eNB
        Transparent Container 36.413
      */
      case utrantolte:
      /* utrantolte */
      case gerantolte:
      /* gerantolte */
      case fivegs_to_eps:
      /* fivegs_to_eps */
      dissect_s1ap_SourceeNB_ToTargeteNB_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      case ltetoutran:
      /* ltetoutran
        Source RNC to Target RNC
        Transparent Container 25.413
      */
      dissect_ranap_SourceRNC_ToTargetRNC_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      case ltetogeran:
      /* ltetogeran
        Source BSS to Target BSS
        Transparent Container 48.018
        or
        Old BSS to New BSS information elements
        Transparent Container 48.008
      */
      if (s1ap_data->srvcc_ho_cs_only)
        bssmap_old_bss_to_new_bss_info(parameter_tvb, subtree, actx->pinfo);
      else
        de_bssgp_source_BSS_to_target_BSS_transp_cont(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
      break;
      case eps_to_5gs:
      /* eps_to_5gs */
      dissect_ngap_SourceNGRANNode_ToTargetNGRANNode_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      default:
      break;
    }
    /* Enable writing of the column again */
    col_set_writable(actx->pinfo->cinfo, COL_INFO, TRUE);
  }



  return offset;
}



static const value_string s1ap_SRVCCOperationNotPossible_vals[] = {
  {   0, "notPossible" },
  { 0, NULL }
};


static int
dissect_s1ap_SRVCCOperationNotPossible(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_SRVCCOperationPossible_vals[] = {
  {   0, "possible" },
  { 0, NULL }
};


static int
dissect_s1ap_SRVCCOperationPossible(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_SRVCCHOIndication_vals[] = {
  { pSandCS, "pSandCS" },
  { cSonly, "cSonly" },
  { 0, NULL }
};


static int
dissect_s1ap_SRVCCHOIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 377 "./asn1/s1ap/s1ap.cnf"
  guint32 srvcc_ho_ind;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, &srvcc_ho_ind, TRUE, 0, NULL);

  if (srvcc_ho_ind == cSonly)
    s1ap_data->srvcc_ho_cs_only = TRUE;



  return offset;
}


static const per_sequence_t SourceNgRanNode_ID_sequence[] = {
  { &hf_s1ap_global_RAN_NODE_ID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_RAN_NODE_ID },
  { &hf_s1ap_selected_TAI_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_FiveGSTAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SourceNgRanNode_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SourceNgRanNode_ID, SourceNgRanNode_ID_sequence);

  return offset;
}



static int
dissect_s1ap_SourceNodeID_Extension(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_ProtocolIE_SingleContainer(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const value_string s1ap_SourceNodeID_vals[] = {
  {   0, "sourceNgRanNode-ID" },
  {   1, "sourceNodeID-Extension" },
  { 0, NULL }
};

static const per_choice_t SourceNodeID_choice[] = {
  {   0, &hf_s1ap_sourceNgRanNode_ID, ASN1_NO_EXTENSIONS     , dissect_s1ap_SourceNgRanNode_ID },
  {   1, &hf_s1ap_sourceNodeID_Extension, ASN1_NO_EXTENSIONS     , dissect_s1ap_SourceNodeID_Extension },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_SourceNodeID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SourceNodeID, SourceNodeID_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_SubscriberProfileIDforRFP(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 256U, NULL, FALSE);

  return offset;
}


static const per_sequence_t UE_HistoryInformation_sequence_of[1] = {
  { &hf_s1ap_UE_HistoryInformation_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_LastVisitedCell_Item },
};

static int
dissect_s1ap_UE_HistoryInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_UE_HistoryInformation, UE_HistoryInformation_sequence_of,
                                                  1, maxnoofCellsinUEHistoryInfo, FALSE);

  return offset;
}


static const per_sequence_t SourceeNB_ToTargeteNB_TransparentContainer_sequence[] = {
  { &hf_s1ap_rRC_Container  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RRC_Container },
  { &hf_s1ap_e_RABInformationList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_E_RABInformationList },
  { &hf_s1ap_targetCell_ID  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_subscriberProfileIDforRFP, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_SubscriberProfileIDforRFP },
  { &hf_s1ap_uE_HistoryInformation, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_UE_HistoryInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SourceeNB_ToTargeteNB_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 399 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  volatile guint32 _offset;

  s1ap_data->transparent_container_type = SOURCE_TO_TARGET_TRANSPARENT_CONTAINER;
  _offset = offset;
   TRY {

  offset = dissect_per_sequence(tvb, _offset, actx, tree, hf_index,
                                   ett_s1ap_SourceeNB_ToTargeteNB_TransparentContainer, SourceeNB_ToTargeteNB_TransparentContainer_sequence);
  } CATCH_ALL {
    show_exception(tvb, actx->pinfo, tree, EXCEPT_CODE, GET_MESSAGE);
  }
  ENDTRY;
    offset = _offset;





  return offset;
}




static const per_sequence_t ServedPLMNs_sequence_of[1] = {
  { &hf_s1ap_ServedPLMNs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_PLMNidentity },
};

static int
dissect_s1ap_ServedPLMNs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ServedPLMNs, ServedPLMNs_sequence_of,
                                                  1, maxnoofPLMNsPerMME, FALSE);

  return offset;
}


static const per_sequence_t ServedGroupIDs_sequence_of[1] = {
  { &hf_s1ap_ServedGroupIDs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_Group_ID },
};

static int
dissect_s1ap_ServedGroupIDs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ServedGroupIDs, ServedGroupIDs_sequence_of,
                                                  1, maxnoofGroupIDs, FALSE);

  return offset;
}


static const per_sequence_t ServedMMECs_sequence_of[1] = {
  { &hf_s1ap_ServedMMECs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_Code },
};

static int
dissect_s1ap_ServedMMECs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ServedMMECs, ServedMMECs_sequence_of,
                                                  1, maxnoofMMECs, FALSE);

  return offset;
}


static const per_sequence_t ServedGUMMEIsItem_sequence[] = {
  { &hf_s1ap_servedPLMNs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ServedPLMNs },
  { &hf_s1ap_servedGroupIDs , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ServedGroupIDs },
  { &hf_s1ap_servedMMECs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ServedMMECs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ServedGUMMEIsItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ServedGUMMEIsItem, ServedGUMMEIsItem_sequence);

  return offset;
}


static const per_sequence_t ServedGUMMEIs_sequence_of[1] = {
  { &hf_s1ap_ServedGUMMEIs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ServedGUMMEIsItem },
};

static int
dissect_s1ap_ServedGUMMEIs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ServedGUMMEIs, ServedGUMMEIs_sequence_of,
                                                  1, maxnoofRATs, FALSE);

  return offset;
}


static const value_string s1ap_T_periodicCommunicationIndicator_vals[] = {
  {   0, "periodically" },
  {   1, "ondemand" },
  { 0, NULL }
};


static int
dissect_s1ap_T_periodicCommunicationIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_1_3600_(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 3600U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_BIT_STRING_SIZE_7(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     7, 7, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_86399_(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 86399U, NULL, TRUE);

  return offset;
}


static const per_sequence_t ScheduledCommunicationTime_sequence[] = {
  { &hf_s1ap_dayofWeek      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_BIT_STRING_SIZE_7 },
  { &hf_s1ap_timeofDayStart , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_86399_ },
  { &hf_s1ap_timeofDayEnd   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_0_86399_ },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ScheduledCommunicationTime(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ScheduledCommunicationTime, ScheduledCommunicationTime_sequence);

  return offset;
}


static const value_string s1ap_T_stationaryIndication_vals[] = {
  {   0, "stationary" },
  {   1, "mobile" },
  { 0, NULL }
};


static int
dissect_s1ap_T_stationaryIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_T_trafficProfile_vals[] = {
  {   0, "single-packet" },
  {   1, "dual-packets" },
  {   2, "multiple-packets" },
  { 0, NULL }
};


static int
dissect_s1ap_T_trafficProfile(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_T_batteryIndication_vals[] = {
  {   0, "battery-powered" },
  {   1, "battery-powered-not-rechargeable-or-replaceable" },
  {   2, "not-battery-powered" },
  { 0, NULL }
};


static int
dissect_s1ap_T_batteryIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t Subscription_Based_UE_DifferentiationInfo_sequence[] = {
  { &hf_s1ap_periodicCommunicationIndicator, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_periodicCommunicationIndicator },
  { &hf_s1ap_periodicTime   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_1_3600_ },
  { &hf_s1ap_scheduledCommunicationTime, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ScheduledCommunicationTime },
  { &hf_s1ap_stationaryIndication, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_stationaryIndication },
  { &hf_s1ap_trafficProfile , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_trafficProfile },
  { &hf_s1ap_batteryIndication, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_batteryIndication },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Subscription_Based_UE_DifferentiationInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Subscription_Based_UE_DifferentiationInfo, Subscription_Based_UE_DifferentiationInfo_sequence);

  return offset;
}


static const value_string s1ap_SynchronisationStatus_vals[] = {
  {   0, "synchronous" },
  {   1, "asynchronous" },
  { 0, NULL }
};


static int
dissect_s1ap_SynchronisationStatus(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t TimeSynchronisationInfo_sequence[] = {
  { &hf_s1ap_stratumLevel   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_StratumLevel },
  { &hf_s1ap_synchronisationStatus, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_SynchronisationStatus },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TimeSynchronisationInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TimeSynchronisationInfo, TimeSynchronisationInfo_sequence);

  return offset;
}


static const per_sequence_t S_TMSI_sequence[] = {
  { &hf_s1ap_mMEC           , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_Code },
  { &hf_s1ap_m_TMSI         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_M_TMSI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_S_TMSI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_S_TMSI, S_TMSI_sequence);

  return offset;
}


static const per_sequence_t TAIListforWarning_sequence_of[1] = {
  { &hf_s1ap_TAIListforWarning_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
};

static int
dissect_s1ap_TAIListforWarning(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAIListforWarning, TAIListforWarning_sequence_of,
                                                  1, maxnoofTAIforWarning, FALSE);

  return offset;
}


static const per_sequence_t TargetNgRanNode_ID_sequence[] = {
  { &hf_s1ap_global_RAN_NODE_ID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Global_RAN_NODE_ID },
  { &hf_s1ap_selected_TAI_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_FiveGSTAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TargetNgRanNode_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TargetNgRanNode_ID, TargetNgRanNode_ID_sequence);

  return offset;
}


static const value_string s1ap_TargetID_vals[] = {
  {   0, "targeteNB-ID" },
  {   1, "targetRNC-ID" },
  {   2, "cGI" },
  {   3, "targetgNgRanNode-ID" },
  { 0, NULL }
};

static const per_choice_t TargetID_choice[] = {
  {   0, &hf_s1ap_targeteNB_ID   , ASN1_EXTENSION_ROOT    , dissect_s1ap_TargeteNB_ID },
  {   1, &hf_s1ap_targetRNC_ID   , ASN1_EXTENSION_ROOT    , dissect_s1ap_TargetRNC_ID },
  {   2, &hf_s1ap_cGI            , ASN1_EXTENSION_ROOT    , dissect_s1ap_CGI },
  {   3, &hf_s1ap_targetgNgRanNode_ID, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_TargetNgRanNode_ID },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_TargetID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_TargetID, TargetID_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t TargeteNB_ToSourceeNB_TransparentContainer_sequence[] = {
  { &hf_s1ap_rRC_Container  , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RRC_Container },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TargeteNB_ToSourceeNB_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 492 "./asn1/s1ap/s1ap.cnf"
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    volatile guint32 _offset;

  s1ap_data->transparent_container_type = TARGET_TO_SOURCE_TRANSPARENT_CONTAINER;
  _offset = offset;
     TRY {

  _offset = dissect_per_sequence(tvb, _offset, actx, tree, hf_index,
                                   ett_s1ap_TargeteNB_ToSourceeNB_TransparentContainer, TargeteNB_ToSourceeNB_TransparentContainer_sequence);
  } CATCH_ALL {
    show_exception(tvb, actx->pinfo, tree, EXCEPT_CODE, GET_MESSAGE);
  }
  ENDTRY;
    offset = _offset;



  return offset;
}



static int
dissect_s1ap_Target_ToSource_TransparentContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 510 "./asn1/s1ap/s1ap.cnf"

  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);


  if ((g_s1ap_dissect_container)&&(parameter_tvb) && (tvb_reported_length(parameter_tvb) > 0)) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_ToSourceTransparentContainer);

    switch(s1ap_data->handover_type_value){
    /*
      HandoverType ::= ENUMERATED {
      intralte,
      ltetoutran,
      ltetogeran,
      utrantolte,
      gerantolte,
      ...
      eps_to_5gs,
      fivegs_to_eps
      } */
      case intralte:
      /* intralte
        Intra E-UTRAN handover Target eNB to Source eNB
        Transparent Container 36.413
      */
      case utrantolte:
      /* utrantolte */
      case gerantolte:
      /* gerantolte */
      case fivegs_to_eps:
      /* fivegs_to_eps */
      dissect_s1ap_TargeteNB_ToSourceeNB_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      case ltetoutran:
      /* ltetoutran
        Target RNC to Source RNC
        Transparent Container 25.413
      */
      dissect_ranap_TargetRNC_ToSourceRNC_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      case ltetogeran:
      /* ltetogeran
        Target BSS to Source BSS
        Transparent Container 48.018
      */
      de_bssgp_target_BSS_to_source_BSS_transp_cont(parameter_tvb, subtree, actx->pinfo, 0, tvb_reported_length(parameter_tvb), NULL, 0);
      break;
      case eps_to_5gs:
      /* eps_to_5gs */
      dissect_ngap_TargetNGRANNode_ToSourceNGRANNode_TransparentContainer_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
      break;
      default:
      break;
    }
  }



  return offset;
}





static const value_string s1ap_TimeToWait_vals[] = {
  {   0, "v1s" },
  {   1, "v2s" },
  {   2, "v5s" },
  {   3, "v10s" },
  {   4, "v20s" },
  {   5, "v60s" },
  { 0, NULL }
};


static int
dissect_s1ap_TimeToWait(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_Time_UE_StayedInCell_EnhancedGranularity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 40950U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_TimeSinceSecondaryNodeRelease(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1065 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       4, 4, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, 4, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const per_sequence_t TransportInformation_sequence[] = {
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_uL_GTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TransportInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TransportInformation, TransportInformation_sequence);

  return offset;
}



static int
dissect_s1ap_E_UTRAN_Trace_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 915 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       8, 8, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;
  subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_E_UTRAN_Trace_ID);
  dissect_e212_mcc_mnc(parameter_tvb, actx->pinfo, subtree, 0, E212_NONE, FALSE);
  proto_tree_add_item(subtree, hf_s1ap_E_UTRAN_Trace_ID_TraceID, parameter_tvb, 3, 3, ENC_BIG_ENDIAN);
  proto_tree_add_item(subtree, hf_s1ap_E_UTRAN_Trace_ID_TraceRecordingSessionReference, parameter_tvb, 6, 2, ENC_BIG_ENDIAN);



  return offset;
}


static const value_string s1ap_TraceDepth_vals[] = {
  {   0, "minimum" },
  {   1, "medium" },
  {   2, "maximum" },
  {   3, "minimumWithoutVendorSpecificExtension" },
  {   4, "mediumWithoutVendorSpecificExtension" },
  {   5, "maximumWithoutVendorSpecificExtension" },
  { 0, NULL }
};


static int
dissect_s1ap_TraceDepth(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     6, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t TraceActivation_sequence[] = {
  { &hf_s1ap_e_UTRAN_Trace_ID, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_UTRAN_Trace_ID },
  { &hf_s1ap_interfacesToTrace, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_InterfacesToTrace },
  { &hf_s1ap_traceDepth     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TraceDepth },
  { &hf_s1ap_traceCollectionEntityIPAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TraceActivation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TraceActivation, TraceActivation_sequence);

  return offset;
}



static int
dissect_s1ap_TrafficLoadReductionIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 99U, NULL, FALSE);

  return offset;
}


static const per_sequence_t TunnelInformation_sequence[] = {
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_uDP_Port_Number, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_Port_Number },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TunnelInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TunnelInformation, TunnelInformation_sequence);

  return offset;
}


static const per_sequence_t TAIListForRestart_sequence_of[1] = {
  { &hf_s1ap_TAIListForRestart_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
};

static int
dissect_s1ap_TAIListForRestart(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAIListForRestart, TAIListForRestart_sequence_of,
                                                  1, maxnoofRestartTAIs, FALSE);

  return offset;
}


static const per_sequence_t UEAggregateMaximumBitrate_sequence[] = {
  { &hf_s1ap_uEaggregateMaximumBitRateDL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_uEaggregateMaximumBitRateUL, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEAggregateMaximumBitrate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEAggregateMaximumBitrate, UEAggregateMaximumBitrate_sequence);

  return offset;
}



static int
dissect_s1ap_OCTET_STRING_SIZE_1_1000(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 1000, FALSE, NULL);

  return offset;
}


static const per_sequence_t UEAppLayerMeasConfig_sequence[] = {
  { &hf_s1ap_containerForAppLayerMeasConfig, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING_SIZE_1_1000 },
  { &hf_s1ap_areaScopeOfQMC , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_AreaScopeOfQMC },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEAppLayerMeasConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEAppLayerMeasConfig, UEAppLayerMeasConfig_sequence);

  return offset;
}


static const value_string s1ap_UECapabilityInfoRequest_vals[] = {
  {   0, "requested" },
  { 0, NULL }
};


static int
dissect_s1ap_UECapabilityInfoRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_UE_RetentionInformation_vals[] = {
  {   0, "ues-retained" },
  { 0, NULL }
};


static int
dissect_s1ap_UE_RetentionInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t UE_S1AP_ID_pair_sequence[] = {
  { &hf_s1ap_mME_UE_S1AP_ID , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_MME_UE_S1AP_ID },
  { &hf_s1ap_eNB_UE_S1AP_ID , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ENB_UE_S1AP_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UE_S1AP_ID_pair(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UE_S1AP_ID_pair, UE_S1AP_ID_pair_sequence);

  return offset;
}


static const value_string s1ap_UE_S1AP_IDs_vals[] = {
  {   0, "uE-S1AP-ID-pair" },
  {   1, "mME-UE-S1AP-ID" },
  { 0, NULL }
};

static const per_choice_t UE_S1AP_IDs_choice[] = {
  {   0, &hf_s1ap_uE_S1AP_ID_pair, ASN1_EXTENSION_ROOT    , dissect_s1ap_UE_S1AP_ID_pair },
  {   1, &hf_s1ap_mME_UE_S1AP_ID , ASN1_EXTENSION_ROOT    , dissect_s1ap_MME_UE_S1AP_ID },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_UE_S1AP_IDs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_UE_S1AP_IDs, UE_S1AP_IDs_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t UE_associatedLogicalS1_ConnectionItem_sequence[] = {
  { &hf_s1ap_mME_UE_S1AP_ID , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_MME_UE_S1AP_ID },
  { &hf_s1ap_eNB_UE_S1AP_ID , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ENB_UE_S1AP_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UE_associatedLogicalS1_ConnectionItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UE_associatedLogicalS1_ConnectionItem, UE_associatedLogicalS1_ConnectionItem_sequence);

  return offset;
}



static int
dissect_s1ap_UEIdentityIndexValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     10, 10, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_UE_HistoryInformationFromTheUE(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 654 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UE_HistoryInformationFromTheUE);
    TRY {
      dissect_lte_rrc_VisitedCellInfoList_r12_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}


static const value_string s1ap_UEPagingID_vals[] = {
  {   0, "s-TMSI" },
  {   1, "iMSI" },
  { 0, NULL }
};

static const per_choice_t UEPagingID_choice[] = {
  {   0, &hf_s1ap_s_TMSI         , ASN1_EXTENSION_ROOT    , dissect_s1ap_S_TMSI },
  {   1, &hf_s1ap_iMSI           , ASN1_EXTENSION_ROOT    , dissect_s1ap_IMSI },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_UEPagingID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_UEPagingID, UEPagingID_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_UERadioCapability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 673 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    volatile dissector_handle_t handle;
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UERadioCapability);
    if (s1ap_data->protocol_ie_id == id_UERadioCapability_NR_Format) {
      handle = nr_rrc_ue_radio_access_cap_info_handle;
    } else if ((s1ap_is_nbiot_ue(actx->pinfo) && (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_AUTOMATIC)) ||
        (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_NBIOT)) {
      handle = lte_rrc_ue_radio_access_cap_info_nb_handle;
    } else {
      handle = lte_rrc_ue_radio_access_cap_info_handle;
    }
    if (handle) {
      TRY {
        call_dissector(handle, parameter_tvb, actx->pinfo, subtree);
      }
      CATCH_BOUNDS_ERRORS {
        show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
      }
      ENDTRY;
    }
  }



  return offset;
}



static int
dissect_s1ap_UERadioCapabilityForPaging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 763 "./asn1/s1ap/s1ap.cnf"

  tvbuff_t *parameter_tvb;
  proto_tree *subtree;

  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    volatile dissector_handle_t handle;
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UERadioPagingInformation);
    if ((s1ap_is_nbiot_ue(actx->pinfo) && (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_AUTOMATIC)) ||
        (g_s1ap_dissect_lte_container_as == S1AP_LTE_CONTAINER_NBIOT)) {
      handle = lte_rrc_ue_radio_paging_info_nb_handle;
    } else {
      handle = lte_rrc_ue_radio_paging_info_handle;
    }
    if (handle) {
      TRY {
        call_dissector(handle, parameter_tvb, actx->pinfo, subtree);
      }
      CATCH_BOUNDS_ERRORS {
        show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
      }
      ENDTRY;
    }
  }



  return offset;
}



static int
dissect_s1ap_UERadioCapabilityID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const per_sequence_t UESecurityCapabilities_sequence[] = {
  { &hf_s1ap_encryptionAlgorithms, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EncryptionAlgorithms },
  { &hf_s1ap_integrityProtectionAlgorithms, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_IntegrityProtectionAlgorithms },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UESecurityCapabilities(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UESecurityCapabilities, UESecurityCapabilities_sequence);

  return offset;
}


static const per_sequence_t UESidelinkAggregateMaximumBitrate_sequence[] = {
  { &hf_s1ap_uESidelinkAggregateMaximumBitRate, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_BitRate },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UESidelinkAggregateMaximumBitrate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UESidelinkAggregateMaximumBitrate, UESidelinkAggregateMaximumBitrate_sequence);

  return offset;
}



static int
dissect_s1ap_UE_Usage_Type(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 255U, NULL, FALSE);

  return offset;
}



static int
dissect_s1ap_UL_NAS_MAC(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     16, 16, FALSE, NULL, 0, NULL, NULL);

  return offset;
}



static int
dissect_s1ap_UL_NAS_Count(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     5, 5, FALSE, NULL, 0, NULL, NULL);

  return offset;
}


static const per_sequence_t UL_CP_SecurityInformation_sequence[] = {
  { &hf_s1ap_ul_NAS_MAC     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_UL_NAS_MAC },
  { &hf_s1ap_ul_NAS_Count   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_UL_NAS_Count },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UL_CP_SecurityInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UL_CP_SecurityInformation, UL_CP_SecurityInformation_sequence);

  return offset;
}


static const value_string s1ap_UnlicensedSpectrumRestriction_vals[] = {
  {   0, "unlicensed-restricted" },
  { 0, NULL }
};


static int
dissect_s1ap_UnlicensedSpectrumRestriction(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_URI_Address(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_VisibleString(tvb, offset, actx, tree, hf_index,
                                          NO_BOUND, NO_BOUND, FALSE);

  return offset;
}


static const per_sequence_t UserLocationInformation_sequence[] = {
  { &hf_s1ap_eutran_cgi     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRAN_CGI },
  { &hf_s1ap_tai            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UserLocationInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UserLocationInformation, UserLocationInformation_sequence);

  return offset;
}


static const value_string s1ap_UEUserPlaneCIoTSupportIndicator_vals[] = {
  {   0, "supported" },
  { 0, NULL }
};


static int
dissect_s1ap_UEUserPlaneCIoTSupportIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_UE_Application_Layer_Measurement_Capability(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1293 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_bit_string(tvb, offset, actx, tree, hf_index,
                                     8, 8, FALSE, NULL, 0, &parameter_tvb, NULL);

  if(parameter_tvb){
    static int * const fields[] = {
      &hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_streaming_service,
      &hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_MTSI_service,
      &hf_s1ap_UE_Application_Layer_Measurement_Capability_Reserved,
      NULL
    };
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UE_Application_Layer_Measurement_Capability);
    proto_tree_add_bitmask_list(subtree, parameter_tvb, 0, 1, fields, ENC_BIG_ENDIAN);
  }



  return offset;
}


static const value_string s1ap_VoiceSupportMatchIndicator_vals[] = {
  {   0, "supported" },
  {   1, "not-supported" },
  { 0, NULL }
};


static int
dissect_s1ap_VoiceSupportMatchIndicator(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t V2XServicesAuthorized_sequence[] = {
  { &hf_s1ap_vehicleUE      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_VehicleUE },
  { &hf_s1ap_pedestrianUE   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PedestrianUE },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_V2XServicesAuthorized(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_V2XServicesAuthorized, V2XServicesAuthorized_sequence);

  return offset;
}



static int
dissect_s1ap_WarningAreaCoordinates(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 1024, FALSE, NULL);

  return offset;
}


static const value_string s1ap_WarningAreaList_vals[] = {
  {   0, "cellIDList" },
  {   1, "trackingAreaListforWarning" },
  {   2, "emergencyAreaIDList" },
  { 0, NULL }
};

static const per_choice_t WarningAreaList_choice[] = {
  {   0, &hf_s1ap_cellIDList     , ASN1_EXTENSION_ROOT    , dissect_s1ap_ECGIList },
  {   1, &hf_s1ap_trackingAreaListforWarning, ASN1_EXTENSION_ROOT    , dissect_s1ap_TAIListforWarning },
  {   2, &hf_s1ap_emergencyAreaIDList, ASN1_EXTENSION_ROOT    , dissect_s1ap_EmergencyAreaIDList },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_WarningAreaList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_WarningAreaList, WarningAreaList_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_WarningType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1134 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       2, 2, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_WarningType);
    proto_tree_add_item(subtree, hf_s1ap_WarningType_value, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
    proto_tree_add_item(subtree, hf_s1ap_WarningType_emergency_user_alert, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
    proto_tree_add_item(subtree, hf_s1ap_WarningType_popup, parameter_tvb, 0, 2, ENC_BIG_ENDIAN);
  }



  return offset;
}



static int
dissect_s1ap_WarningSecurityInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       50, 50, FALSE, NULL);

  return offset;
}



static int
dissect_s1ap_WarningMessageContents(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1158 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       1, 9600, FALSE, &parameter_tvb);

  if (parameter_tvb) {
    struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
    proto_tree *subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_WarningMessageContents);
    dissect_s1ap_warningMessageContents(parameter_tvb, subtree, actx->pinfo, s1ap_data->data_coding_scheme, hf_s1ap_WarningMessageContents_nb_pages, hf_s1ap_WarningMessageContents_decoded_page);
  }



  return offset;
}


static const value_string s1ap_WLANMeasConfig_vals[] = {
  {   0, "setup" },
  { 0, NULL }
};


static int
dissect_s1ap_WLANMeasConfig(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}



static int
dissect_s1ap_WLANName(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 1484 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb = NULL;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, -1,
                                       1, 32, FALSE, &parameter_tvb);

  actx->created_item = proto_tree_add_item(tree, hf_index, parameter_tvb, 0, -1, ENC_UTF_8|ENC_NA);


  return offset;
}


static const per_sequence_t WLANMeasConfigNameList_sequence_of[1] = {
  { &hf_s1ap_WLANMeasConfigNameList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_WLANName },
};

static int
dissect_s1ap_WLANMeasConfigNameList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_WLANMeasConfigNameList, WLANMeasConfigNameList_sequence_of,
                                                  1, maxnoofWLANName, FALSE);

  return offset;
}


static const value_string s1ap_T_wlan_rssi_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_T_wlan_rssi(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_T_wlan_rtt_vals[] = {
  {   0, "true" },
  { 0, NULL }
};


static int
dissect_s1ap_T_wlan_rtt(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t WLANMeasurementConfiguration_sequence[] = {
  { &hf_s1ap_wlanMeasConfig , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_WLANMeasConfig },
  { &hf_s1ap_wlanMeasConfigNameList, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_WLANMeasConfigNameList },
  { &hf_s1ap_wlan_rssi      , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_wlan_rssi },
  { &hf_s1ap_wlan_rtt       , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_T_wlan_rtt },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_WLANMeasurementConfiguration(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_WLANMeasurementConfiguration, WLANMeasurementConfiguration_sequence);

  return offset;
}


static const per_sequence_t WUS_Assistance_Information_sequence[] = {
  { &hf_s1ap_pagingProbabilityInformation, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PagingProbabilityInformation },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_WUS_Assistance_Information(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_WUS_Assistance_Information, WUS_Assistance_Information_sequence);

  return offset;
}


static const per_sequence_t ENBX2GTPTLAs_sequence_of[1] = {
  { &hf_s1ap_ENBX2GTPTLAs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
};

static int
dissect_s1ap_ENBX2GTPTLAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ENBX2GTPTLAs, ENBX2GTPTLAs_sequence_of,
                                                  1, maxnoofeNBX2GTPTLAs, FALSE);

  return offset;
}


static const per_sequence_t ENBX2ExtTLA_sequence[] = {
  { &hf_s1ap_iPsecTLA       , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTPTLAa        , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ENBX2GTPTLAs },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBX2ExtTLA(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBX2ExtTLA, ENBX2ExtTLA_sequence);

  return offset;
}


static const per_sequence_t ENBX2ExtTLAs_sequence_of[1] = {
  { &hf_s1ap_ENBX2ExtTLAs_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ENBX2ExtTLA },
};

static int
dissect_s1ap_ENBX2ExtTLAs(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ENBX2ExtTLAs, ENBX2ExtTLAs_sequence_of,
                                                  1, maxnoofeNBX2ExtTLAs, FALSE);

  return offset;
}


static const per_sequence_t ENBIndirectX2TransportLayerAddresses_sequence_of[1] = {
  { &hf_s1ap_ENBIndirectX2TransportLayerAddresses_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
};

static int
dissect_s1ap_ENBIndirectX2TransportLayerAddresses(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ENBIndirectX2TransportLayerAddresses, ENBIndirectX2TransportLayerAddresses_sequence_of,
                                                  1, maxnoofeNBX2TLAs, FALSE);

  return offset;
}



static int
dissect_s1ap_E_RAB_IE_ContainerList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 199 "./asn1/s1ap/s1ap.cnf"
  asn1_stack_frame_push(actx, "ProtocolIE-ContainerList");
  asn1_param_push_integer(actx, 1);
  asn1_param_push_integer(actx, maxnoofE_RABs);
  offset = dissect_s1ap_ProtocolIE_ContainerList(tvb, offset, actx, tree, hf_index);

  asn1_stack_frame_pop(actx, "ProtocolIE-ContainerList");


  return offset;
}


static const per_sequence_t HandoverRequired_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverRequired(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 385 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->handover_type_value = 0xff;
  s1ap_data->srvcc_ho_cs_only = FALSE;
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverRequired");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverRequired, HandoverRequired_sequence);

  return offset;
}


static const per_sequence_t HandoverCommand_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverCommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 389 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->handover_type_value = 0xff;
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverCommand");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverCommand, HandoverCommand_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABSubjecttoDataForwardingList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABDataForwardingItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_dL_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_dL_gTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_GTP_TEID },
  { &hf_s1ap_uL_TransportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_uL_GTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABDataForwardingItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABDataForwardingItem, E_RABDataForwardingItem_sequence);

  return offset;
}


static const per_sequence_t HandoverPreparationFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverPreparationFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2388 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverPreparationFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverPreparationFailure, HandoverPreparationFailure_sequence);

  return offset;
}


static const per_sequence_t HandoverRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 392 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->handover_type_value = 0xff;
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverRequest, HandoverRequest_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABToBeSetupListHOReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABToBeSetupItemHOReq_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_e_RABlevelQosParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RABLevelQoSParameters },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeSetupItemHOReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeSetupItemHOReq, E_RABToBeSetupItemHOReq_sequence);

  return offset;
}


static const per_sequence_t HandoverRequestAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverRequestAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 395 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->handover_type_value = 0xff;

  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverRequestAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverRequestAcknowledge, HandoverRequestAcknowledge_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABAdmittedList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABAdmittedItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_dL_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_dL_gTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_GTP_TEID },
  { &hf_s1ap_uL_TransportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_uL_GTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABAdmittedItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABAdmittedItem, E_RABAdmittedItem_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABFailedtoSetupListHOReqAck(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABFailedToSetupItemHOReqAck_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_cause          , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cause },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABFailedToSetupItemHOReqAck(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABFailedToSetupItemHOReqAck, E_RABFailedToSetupItemHOReqAck_sequence);

  return offset;
}


static const per_sequence_t HandoverFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2394 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverFailure, HandoverFailure_sequence);

  return offset;
}


static const per_sequence_t HandoverNotify_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverNotify(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2396 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverNotify");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverNotify, HandoverNotify_sequence);

  return offset;
}


static const per_sequence_t PathSwitchRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PathSwitchRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2398 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PathSwitchRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PathSwitchRequest, PathSwitchRequest_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABToBeSwitchedDLList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABToBeSwitchedDLItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeSwitchedDLItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeSwitchedDLItem, E_RABToBeSwitchedDLItem_sequence);

  return offset;
}


static const per_sequence_t PathSwitchRequestAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PathSwitchRequestAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2400 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PathSwitchRequestAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PathSwitchRequestAcknowledge, PathSwitchRequestAcknowledge_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABToBeSwitchedULList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABToBeSwitchedULItem_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeSwitchedULItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeSwitchedULItem, E_RABToBeSwitchedULItem_sequence);

  return offset;
}


static const per_sequence_t PathSwitchRequestFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PathSwitchRequestFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2402 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PathSwitchRequestFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PathSwitchRequestFailure, PathSwitchRequestFailure_sequence);

  return offset;
}


static const per_sequence_t HandoverCancel_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverCancel(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2404 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverCancel");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverCancel, HandoverCancel_sequence);

  return offset;
}


static const per_sequence_t HandoverCancelAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverCancelAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2406 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverCancelAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverCancelAcknowledge, HandoverCancelAcknowledge_sequence);

  return offset;
}


static const per_sequence_t HandoverSuccess_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HandoverSuccess(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2574 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "HandoverSuccess");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HandoverSuccess, HandoverSuccess_sequence);

  return offset;
}


static const per_sequence_t ENBEarlyStatusTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBEarlyStatusTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2576 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBEarlyStatusTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBEarlyStatusTransfer, ENBEarlyStatusTransfer_sequence);

  return offset;
}


static const per_sequence_t MMEEarlyStatusTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEEarlyStatusTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2578 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEEarlyStatusTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEEarlyStatusTransfer, MMEEarlyStatusTransfer_sequence);

  return offset;
}


static const per_sequence_t E_RABSetupRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABSetupRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2408 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABSetupRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABSetupRequest, E_RABSetupRequest_sequence);

  return offset;
}


static const per_sequence_t E_RABToBeSetupListBearerSUReq_sequence_of[1] = {
  { &hf_s1ap_E_RABToBeSetupListBearerSUReq_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABToBeSetupListBearerSUReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABToBeSetupListBearerSUReq, E_RABToBeSetupListBearerSUReq_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABToBeSetupItemBearerSUReq_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_e_RABlevelQoSParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RABLevelQoSParameters },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_nAS_PDU        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NAS_PDU },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeSetupItemBearerSUReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeSetupItemBearerSUReq, E_RABToBeSetupItemBearerSUReq_sequence);

  return offset;
}


static const per_sequence_t E_RABSetupResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABSetupResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2410 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABSetupResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABSetupResponse, E_RABSetupResponse_sequence);

  return offset;
}


static const per_sequence_t E_RABSetupListBearerSURes_sequence_of[1] = {
  { &hf_s1ap_E_RABSetupListBearerSURes_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABSetupListBearerSURes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABSetupListBearerSURes, E_RABSetupListBearerSURes_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABSetupItemBearerSURes_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABSetupItemBearerSURes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABSetupItemBearerSURes, E_RABSetupItemBearerSURes_sequence);

  return offset;
}


static const per_sequence_t E_RABModifyRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModifyRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2412 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABModifyRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModifyRequest, E_RABModifyRequest_sequence);

  return offset;
}


static const per_sequence_t E_RABToBeModifiedListBearerModReq_sequence_of[1] = {
  { &hf_s1ap_E_RABToBeModifiedListBearerModReq_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABToBeModifiedListBearerModReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABToBeModifiedListBearerModReq, E_RABToBeModifiedListBearerModReq_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABToBeModifiedItemBearerModReq_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_e_RABLevelQoSParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RABLevelQoSParameters },
  { &hf_s1ap_nAS_PDU        , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NAS_PDU },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeModifiedItemBearerModReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeModifiedItemBearerModReq, E_RABToBeModifiedItemBearerModReq_sequence);

  return offset;
}


static const per_sequence_t E_RABModifyResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModifyResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2414 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABModifyResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModifyResponse, E_RABModifyResponse_sequence);

  return offset;
}


static const per_sequence_t E_RABModifyListBearerModRes_sequence_of[1] = {
  { &hf_s1ap_E_RABModifyListBearerModRes_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABModifyListBearerModRes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABModifyListBearerModRes, E_RABModifyListBearerModRes_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABModifyItemBearerModRes_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModifyItemBearerModRes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModifyItemBearerModRes, E_RABModifyItemBearerModRes_sequence);

  return offset;
}


static const per_sequence_t E_RABReleaseCommand_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABReleaseCommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2416 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABReleaseCommand");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABReleaseCommand, E_RABReleaseCommand_sequence);

  return offset;
}


static const per_sequence_t E_RABReleaseResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABReleaseResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2418 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABReleaseResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABReleaseResponse, E_RABReleaseResponse_sequence);

  return offset;
}


static const per_sequence_t E_RABReleaseListBearerRelComp_sequence_of[1] = {
  { &hf_s1ap_E_RABReleaseListBearerRelComp_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABReleaseListBearerRelComp(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABReleaseListBearerRelComp, E_RABReleaseListBearerRelComp_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABReleaseItemBearerRelComp_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABReleaseItemBearerRelComp(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABReleaseItemBearerRelComp, E_RABReleaseItemBearerRelComp_sequence);

  return offset;
}


static const per_sequence_t E_RABReleaseIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABReleaseIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2420 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABReleaseIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABReleaseIndication, E_RABReleaseIndication_sequence);

  return offset;
}


static const per_sequence_t InitialContextSetupRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InitialContextSetupRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2422 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "InitialContextSetupRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InitialContextSetupRequest, InitialContextSetupRequest_sequence);

  return offset;
}


static const per_sequence_t E_RABToBeSetupListCtxtSUReq_sequence_of[1] = {
  { &hf_s1ap_E_RABToBeSetupListCtxtSUReq_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABToBeSetupListCtxtSUReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABToBeSetupListCtxtSUReq, E_RABToBeSetupListCtxtSUReq_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABToBeSetupItemCtxtSUReq_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_e_RABlevelQoSParameters, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RABLevelQoSParameters },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_nAS_PDU        , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_NAS_PDU },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeSetupItemCtxtSUReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeSetupItemCtxtSUReq, E_RABToBeSetupItemCtxtSUReq_sequence);

  return offset;
}


static const per_sequence_t InitialContextSetupResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InitialContextSetupResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2424 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "InitialContextSetupResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InitialContextSetupResponse, InitialContextSetupResponse_sequence);

  return offset;
}


static const per_sequence_t E_RABSetupListCtxtSURes_sequence_of[1] = {
  { &hf_s1ap_E_RABSetupListCtxtSURes_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABSetupListCtxtSURes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABSetupListCtxtSURes, E_RABSetupListCtxtSURes_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABSetupItemCtxtSURes_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_gTP_TEID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABSetupItemCtxtSURes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABSetupItemCtxtSURes, E_RABSetupItemCtxtSURes_sequence);

  return offset;
}


static const per_sequence_t InitialContextSetupFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InitialContextSetupFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2426 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "InitialContextSetupFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InitialContextSetupFailure, InitialContextSetupFailure_sequence);

  return offset;
}


static const per_sequence_t Paging_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Paging(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2428 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "Paging");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Paging, Paging_sequence);

  return offset;
}


static const per_sequence_t TAIList_sequence_of[1] = {
  { &hf_s1ap_TAIList_item   , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_TAIList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_TAIList, TAIList_sequence_of,
                                                  1, maxnoofTAIs, FALSE);

  return offset;
}


static const per_sequence_t TAIItem_sequence[] = {
  { &hf_s1ap_tAI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TAI },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TAIItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TAIItem, TAIItem_sequence);

  return offset;
}


static const per_sequence_t UEContextReleaseRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextReleaseRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2430 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextReleaseRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextReleaseRequest, UEContextReleaseRequest_sequence);

  return offset;
}


static const per_sequence_t UEContextReleaseCommand_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextReleaseCommand(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2432 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextReleaseCommand");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextReleaseCommand, UEContextReleaseCommand_sequence);

  return offset;
}


static const per_sequence_t UEContextReleaseComplete_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextReleaseComplete(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2434 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextReleaseComplete");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextReleaseComplete, UEContextReleaseComplete_sequence);

  return offset;
}


static const per_sequence_t UEContextModificationRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextModificationRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2436 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextModificationRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextModificationRequest, UEContextModificationRequest_sequence);

  return offset;
}


static const per_sequence_t UEContextModificationResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextModificationResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2438 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextModificationResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextModificationResponse, UEContextModificationResponse_sequence);

  return offset;
}


static const per_sequence_t UEContextModificationFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextModificationFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2440 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextModificationFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextModificationFailure, UEContextModificationFailure_sequence);

  return offset;
}


static const per_sequence_t UERadioCapabilityMatchRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UERadioCapabilityMatchRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2442 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UERadioCapabilityMatchRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UERadioCapabilityMatchRequest, UERadioCapabilityMatchRequest_sequence);

  return offset;
}


static const per_sequence_t UERadioCapabilityMatchResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UERadioCapabilityMatchResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2444 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UERadioCapabilityMatchResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UERadioCapabilityMatchResponse, UERadioCapabilityMatchResponse_sequence);

  return offset;
}


static const per_sequence_t DownlinkNASTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DownlinkNASTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 365 "./asn1/s1ap/s1ap.cnf"
  /* Set the direction of the message */
  actx->pinfo->link_dir=P2P_DIR_DL;

  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "DownlinkNASTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DownlinkNASTransport, DownlinkNASTransport_sequence);

  return offset;
}


static const per_sequence_t InitialUEMessage_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InitialUEMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 361 "./asn1/s1ap/s1ap.cnf"
  /* Set the direction of the message */
  actx->pinfo->link_dir=P2P_DIR_UL;

  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "InitialUEMessage");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InitialUEMessage, InitialUEMessage_sequence);

  return offset;
}


static const per_sequence_t UplinkNASTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UplinkNASTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 369 "./asn1/s1ap/s1ap.cnf"
  /* Set the direction of the message */
  actx->pinfo->link_dir=P2P_DIR_UL;

  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UplinkNASTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UplinkNASTransport, UplinkNASTransport_sequence);

  return offset;
}


static const per_sequence_t NASNonDeliveryIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NASNonDeliveryIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2452 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "NASNonDeliveryIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NASNonDeliveryIndication, NASNonDeliveryIndication_sequence);

  return offset;
}


static const per_sequence_t RerouteNASRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RerouteNASRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2454 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "RerouteNASRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RerouteNASRequest, RerouteNASRequest_sequence);

  return offset;
}



static int
dissect_s1ap_S1_Message(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 904 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_S1_Message);
  col_set_fence(actx->pinfo->cinfo, COL_INFO);
  call_dissector(s1ap_handle, parameter_tvb, actx->pinfo, subtree);



  return offset;
}


static const per_sequence_t NASDeliveryIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NASDeliveryIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2558 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "NASDeliveryIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NASDeliveryIndication, NASDeliveryIndication_sequence);

  return offset;
}


static const per_sequence_t Reset_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_Reset(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2456 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "Reset");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_Reset, Reset_sequence);

  return offset;
}


static const value_string s1ap_ResetAll_vals[] = {
  {   0, "reset-all" },
  { 0, NULL }
};


static int
dissect_s1ap_ResetAll(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t UE_associatedLogicalS1_ConnectionListRes_sequence_of[1] = {
  { &hf_s1ap_UE_associatedLogicalS1_ConnectionListRes_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_UE_associatedLogicalS1_ConnectionListRes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_UE_associatedLogicalS1_ConnectionListRes, UE_associatedLogicalS1_ConnectionListRes_sequence_of,
                                                  1, maxnoofIndividualS1ConnectionsToReset, FALSE);

  return offset;
}


static const value_string s1ap_ResetType_vals[] = {
  {   0, "s1-Interface" },
  {   1, "partOfS1-Interface" },
  { 0, NULL }
};

static const per_choice_t ResetType_choice[] = {
  {   0, &hf_s1ap_s1_Interface   , ASN1_EXTENSION_ROOT    , dissect_s1ap_ResetAll },
  {   1, &hf_s1ap_partOfS1_Interface, ASN1_EXTENSION_ROOT    , dissect_s1ap_UE_associatedLogicalS1_ConnectionListRes },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_ResetType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_ResetType, ResetType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t ResetAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ResetAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2458 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ResetAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ResetAcknowledge, ResetAcknowledge_sequence);

  return offset;
}


static const per_sequence_t UE_associatedLogicalS1_ConnectionListResAck_sequence_of[1] = {
  { &hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_UE_associatedLogicalS1_ConnectionListResAck(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_UE_associatedLogicalS1_ConnectionListResAck, UE_associatedLogicalS1_ConnectionListResAck_sequence_of,
                                                  1, maxnoofIndividualS1ConnectionsToReset, FALSE);

  return offset;
}


static const per_sequence_t ErrorIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ErrorIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2460 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ErrorIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ErrorIndication, ErrorIndication_sequence);

  return offset;
}


static const per_sequence_t S1SetupRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_S1SetupRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2462 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "S1SetupRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_S1SetupRequest, S1SetupRequest_sequence);

  return offset;
}


static const per_sequence_t S1SetupResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_S1SetupResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2464 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "S1SetupResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_S1SetupResponse, S1SetupResponse_sequence);

  return offset;
}


static const per_sequence_t S1SetupFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_S1SetupFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2466 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "S1SetupFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_S1SetupFailure, S1SetupFailure_sequence);

  return offset;
}


static const per_sequence_t ENBConfigurationUpdate_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBConfigurationUpdate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2468 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBConfigurationUpdate");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBConfigurationUpdate, ENBConfigurationUpdate_sequence);

  return offset;
}


static const per_sequence_t ENBConfigurationUpdateAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBConfigurationUpdateAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2470 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBConfigurationUpdateAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBConfigurationUpdateAcknowledge, ENBConfigurationUpdateAcknowledge_sequence);

  return offset;
}


static const per_sequence_t ENBConfigurationUpdateFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBConfigurationUpdateFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2472 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBConfigurationUpdateFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBConfigurationUpdateFailure, ENBConfigurationUpdateFailure_sequence);

  return offset;
}


static const per_sequence_t MMEConfigurationUpdate_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEConfigurationUpdate(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2474 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEConfigurationUpdate");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEConfigurationUpdate, MMEConfigurationUpdate_sequence);

  return offset;
}


static const per_sequence_t MMEConfigurationUpdateAcknowledge_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEConfigurationUpdateAcknowledge(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2476 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEConfigurationUpdateAcknowledge");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEConfigurationUpdateAcknowledge, MMEConfigurationUpdateAcknowledge_sequence);

  return offset;
}


static const per_sequence_t MMEConfigurationUpdateFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEConfigurationUpdateFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2478 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEConfigurationUpdateFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEConfigurationUpdateFailure, MMEConfigurationUpdateFailure_sequence);

  return offset;
}


static const per_sequence_t DownlinkS1cdma2000tunnelling_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DownlinkS1cdma2000tunnelling(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2480 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "DownlinkS1cdma2000tunnelling");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DownlinkS1cdma2000tunnelling, DownlinkS1cdma2000tunnelling_sequence);

  return offset;
}


static const per_sequence_t UplinkS1cdma2000tunnelling_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UplinkS1cdma2000tunnelling(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2482 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UplinkS1cdma2000tunnelling");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UplinkS1cdma2000tunnelling, UplinkS1cdma2000tunnelling_sequence);

  return offset;
}


static const per_sequence_t UECapabilityInfoIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UECapabilityInfoIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2484 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UECapabilityInfoIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UECapabilityInfoIndication, UECapabilityInfoIndication_sequence);

  return offset;
}


static const per_sequence_t ENBStatusTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBStatusTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2486 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBStatusTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBStatusTransfer, ENBStatusTransfer_sequence);

  return offset;
}


static const per_sequence_t MMEStatusTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEStatusTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2488 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEStatusTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEStatusTransfer, MMEStatusTransfer_sequence);

  return offset;
}


static const per_sequence_t TraceStart_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TraceStart(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2490 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "TraceStart");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TraceStart, TraceStart_sequence);

  return offset;
}


static const per_sequence_t TraceFailureIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TraceFailureIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2492 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "TraceFailureIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TraceFailureIndication, TraceFailureIndication_sequence);

  return offset;
}


static const per_sequence_t DeactivateTrace_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DeactivateTrace(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2494 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "DeactivateTrace");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DeactivateTrace, DeactivateTrace_sequence);

  return offset;
}


static const per_sequence_t CellTrafficTrace_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellTrafficTrace(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2496 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "CellTrafficTrace");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellTrafficTrace, CellTrafficTrace_sequence);

  return offset;
}


static const per_sequence_t LocationReportingControl_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LocationReportingControl(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2498 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "LocationReportingControl");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LocationReportingControl, LocationReportingControl_sequence);

  return offset;
}


static const per_sequence_t LocationReportingFailureIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LocationReportingFailureIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2500 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "LocationReportingFailureIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LocationReportingFailureIndication, LocationReportingFailureIndication_sequence);

  return offset;
}


static const per_sequence_t LocationReport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_LocationReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2502 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "LocationReport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_LocationReport, LocationReport_sequence);

  return offset;
}


static const per_sequence_t OverloadStart_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_OverloadStart(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2504 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "OverloadStart");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_OverloadStart, OverloadStart_sequence);

  return offset;
}


static const per_sequence_t OverloadStop_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_OverloadStop(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2506 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "OverloadStop");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_OverloadStop, OverloadStop_sequence);

  return offset;
}


static const per_sequence_t WriteReplaceWarningRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_WriteReplaceWarningRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2508 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "WriteReplaceWarningRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_WriteReplaceWarningRequest, WriteReplaceWarningRequest_sequence);

  return offset;
}


static const per_sequence_t WriteReplaceWarningResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_WriteReplaceWarningResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2510 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "WriteReplaceWarningResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_WriteReplaceWarningResponse, WriteReplaceWarningResponse_sequence);

  return offset;
}


static const per_sequence_t ENBDirectInformationTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBDirectInformationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2512 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBDirectInformationTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBDirectInformationTransfer, ENBDirectInformationTransfer_sequence);

  return offset;
}


static const value_string s1ap_Inter_SystemInformationTransferType_vals[] = {
  {   0, "rIMTransfer" },
  { 0, NULL }
};

static const per_choice_t Inter_SystemInformationTransferType_choice[] = {
  {   0, &hf_s1ap_rIMTransfer    , ASN1_EXTENSION_ROOT    , dissect_s1ap_RIMTransfer },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_Inter_SystemInformationTransferType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_Inter_SystemInformationTransferType, Inter_SystemInformationTransferType_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MMEDirectInformationTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEDirectInformationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2514 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEDirectInformationTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEDirectInformationTransfer, MMEDirectInformationTransfer_sequence);

  return offset;
}


static const per_sequence_t ENBConfigurationTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBConfigurationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2516 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBConfigurationTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBConfigurationTransfer, ENBConfigurationTransfer_sequence);

  return offset;
}


static const per_sequence_t MMEConfigurationTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMEConfigurationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2518 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMEConfigurationTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMEConfigurationTransfer, MMEConfigurationTransfer_sequence);

  return offset;
}


static const per_sequence_t PrivateMessage_sequence[] = {
  { &hf_s1ap_privateIEs     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_PrivateIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PrivateMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2520 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PrivateMessage");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PrivateMessage, PrivateMessage_sequence);

  return offset;
}


static const per_sequence_t KillRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_KillRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2522 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "KillRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_KillRequest, KillRequest_sequence);

  return offset;
}


static const per_sequence_t KillResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_KillResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2524 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "KillResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_KillResponse, KillResponse_sequence);

  return offset;
}


static const per_sequence_t PWSRestartIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PWSRestartIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2526 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PWSRestartIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PWSRestartIndication, PWSRestartIndication_sequence);

  return offset;
}


static const per_sequence_t PWSFailureIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_PWSFailureIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2528 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "PWSFailureIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_PWSFailureIndication, PWSFailureIndication_sequence);

  return offset;
}


static const per_sequence_t DownlinkUEAssociatedLPPaTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DownlinkUEAssociatedLPPaTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2530 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "DownlinkUEAssociatedLPPaTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DownlinkUEAssociatedLPPaTransport, DownlinkUEAssociatedLPPaTransport_sequence);

  return offset;
}


static const per_sequence_t UplinkUEAssociatedLPPaTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UplinkUEAssociatedLPPaTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2532 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UplinkUEAssociatedLPPaTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UplinkUEAssociatedLPPaTransport, UplinkUEAssociatedLPPaTransport_sequence);

  return offset;
}


static const per_sequence_t DownlinkNonUEAssociatedLPPaTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_DownlinkNonUEAssociatedLPPaTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2534 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "DownlinkNonUEAssociatedLPPaTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_DownlinkNonUEAssociatedLPPaTransport, DownlinkNonUEAssociatedLPPaTransport_sequence);

  return offset;
}


static const per_sequence_t UplinkNonUEAssociatedLPPaTransport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UplinkNonUEAssociatedLPPaTransport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2536 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UplinkNonUEAssociatedLPPaTransport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UplinkNonUEAssociatedLPPaTransport, UplinkNonUEAssociatedLPPaTransport_sequence);

  return offset;
}


static const per_sequence_t E_RABModificationIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModificationIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2538 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABModificationIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModificationIndication, E_RABModificationIndication_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABToBeModifiedListBearerModInd(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABToBeModifiedItemBearerModInd_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_dL_GTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABToBeModifiedItemBearerModInd(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABToBeModifiedItemBearerModInd, E_RABToBeModifiedItemBearerModInd_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABNotToBeModifiedListBearerModInd(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABNotToBeModifiedItemBearerModInd_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_transportLayerAddress, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_TransportLayerAddress },
  { &hf_s1ap_dL_GTP_TEID    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_GTP_TEID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABNotToBeModifiedItemBearerModInd(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABNotToBeModifiedItemBearerModInd, E_RABNotToBeModifiedItemBearerModInd_sequence);

  return offset;
}


static const per_sequence_t CSGMembershipInfo_sequence[] = {
  { &hf_s1ap_cSGMembershipStatus, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CSGMembershipStatus },
  { &hf_s1ap_cSG_Id         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CSG_Id },
  { &hf_s1ap_cellAccessMode , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_CellAccessMode },
  { &hf_s1ap_pLMNidentity   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_PLMNidentity },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CSGMembershipInfo(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CSGMembershipInfo, CSGMembershipInfo_sequence);

  return offset;
}


static const per_sequence_t E_RABModificationConfirm_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModificationConfirm(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2540 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "E-RABModificationConfirm");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModificationConfirm, E_RABModificationConfirm_sequence);

  return offset;
}


static const per_sequence_t E_RABModifyListBearerModConf_sequence_of[1] = {
  { &hf_s1ap_E_RABModifyListBearerModConf_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_SingleContainer },
};

static int
dissect_s1ap_E_RABModifyListBearerModConf(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_E_RABModifyListBearerModConf, E_RABModifyListBearerModConf_sequence_of,
                                                  1, maxnoofE_RABs, FALSE);

  return offset;
}


static const per_sequence_t E_RABModifyItemBearerModConf_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABModifyItemBearerModConf(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABModifyItemBearerModConf, E_RABModifyItemBearerModConf_sequence);

  return offset;
}


static const per_sequence_t UEContextModificationIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextModificationIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2542 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextModificationIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextModificationIndication, UEContextModificationIndication_sequence);

  return offset;
}


static const per_sequence_t UEContextModificationConfirm_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextModificationConfirm(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2544 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextModificationConfirm");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextModificationConfirm, UEContextModificationConfirm_sequence);

  return offset;
}


static const per_sequence_t UEContextSuspendRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextSuspendRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2546 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextSuspendRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextSuspendRequest, UEContextSuspendRequest_sequence);

  return offset;
}


static const per_sequence_t UEContextSuspendResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextSuspendResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2548 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextSuspendResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextSuspendResponse, UEContextSuspendResponse_sequence);

  return offset;
}


static const per_sequence_t UEContextResumeRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextResumeRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2550 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextResumeRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextResumeRequest, UEContextResumeRequest_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABFailedToResumeListResumeReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABFailedToResumeItemResumeReq_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_cause          , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cause },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABFailedToResumeItemResumeReq(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABFailedToResumeItemResumeReq, E_RABFailedToResumeItemResumeReq_sequence);

  return offset;
}


static const per_sequence_t UEContextResumeResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextResumeResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2552 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextResumeResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextResumeResponse, UEContextResumeResponse_sequence);

  return offset;
}



static int
dissect_s1ap_E_RABFailedToResumeListResumeRes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_s1ap_E_RAB_IE_ContainerList(tvb, offset, actx, tree, hf_index);

  return offset;
}


static const per_sequence_t E_RABFailedToResumeItemResumeRes_sequence[] = {
  { &hf_s1ap_e_RAB_ID       , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_E_RAB_ID },
  { &hf_s1ap_cause          , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_Cause },
  { &hf_s1ap_iE_Extensions  , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_ProtocolExtensionContainer },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_E_RABFailedToResumeItemResumeRes(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_E_RABFailedToResumeItemResumeRes, E_RABFailedToResumeItemResumeRes_sequence);

  return offset;
}


static const per_sequence_t UEContextResumeFailure_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEContextResumeFailure(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2554 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEContextResumeFailure");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEContextResumeFailure, UEContextResumeFailure_sequence);

  return offset;
}


static const per_sequence_t ConnectionEstablishmentIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ConnectionEstablishmentIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2556 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ConnectionEstablishmentIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ConnectionEstablishmentIndication, ConnectionEstablishmentIndication_sequence);

  return offset;
}


static const per_sequence_t RetrieveUEInformation_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_RetrieveUEInformation(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2560 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "RetrieveUEInformation");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_RetrieveUEInformation, RetrieveUEInformation_sequence);

  return offset;
}


static const per_sequence_t UEInformationTransfer_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UEInformationTransfer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2562 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UEInformationTransfer");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UEInformationTransfer, UEInformationTransfer_sequence);

  return offset;
}


static const per_sequence_t ENBCPRelocationIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ENBCPRelocationIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2564 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "ENBCPRelocationIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ENBCPRelocationIndication, ENBCPRelocationIndication_sequence);

  return offset;
}


static const per_sequence_t MMECPRelocationIndication_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MMECPRelocationIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2566 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "MMECPRelocationIndication");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MMECPRelocationIndication, MMECPRelocationIndication_sequence);

  return offset;
}


static const per_sequence_t SecondaryRATDataUsageReport_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SecondaryRATDataUsageReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2568 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "SecondaryRATDataUsageReport");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SecondaryRATDataUsageReport, SecondaryRATDataUsageReport_sequence);

  return offset;
}


static const per_sequence_t UERadioCapabilityIDMappingRequest_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UERadioCapabilityIDMappingRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2570 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UERadioCapabilityIDMappingRequest");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UERadioCapabilityIDMappingRequest, UERadioCapabilityIDMappingRequest_sequence);

  return offset;
}


static const per_sequence_t UERadioCapabilityIDMappingResponse_sequence[] = {
  { &hf_s1ap_protocolIEs    , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ProtocolIE_Container },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UERadioCapabilityIDMappingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 2572 "./asn1/s1ap/s1ap.cnf"
  col_append_sep_str(actx->pinfo->cinfo, COL_INFO, NULL, "UERadioCapabilityIDMappingResponse");

  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UERadioCapabilityIDMappingResponse, UERadioCapabilityIDMappingResponse_sequence);

  return offset;
}



static int
dissect_s1ap_InitiatingMessage_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 151 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->message_type = INITIATING_MESSAGE;

  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_InitiatingMessageValue);

  return offset;
}


static const per_sequence_t InitiatingMessage_sequence[] = {
  { &hf_s1ap_procedureCode  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProcedureCode },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_initiatingMessagevalue, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_InitiatingMessage_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_InitiatingMessage(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_InitiatingMessage, InitiatingMessage_sequence);

  return offset;
}



static int
dissect_s1ap_SuccessfulOutcome_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 155 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->message_type = SUCCESSFUL_OUTCOME;

  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_SuccessfulOutcomeValue);

  return offset;
}


static const per_sequence_t SuccessfulOutcome_sequence[] = {
  { &hf_s1ap_procedureCode  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProcedureCode },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_successfulOutcome_value, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_SuccessfulOutcome_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_SuccessfulOutcome(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_SuccessfulOutcome, SuccessfulOutcome_sequence);

  return offset;
}



static int
dissect_s1ap_UnsuccessfulOutcome_value(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 159 "./asn1/s1ap/s1ap.cnf"
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(actx->pinfo);
  s1ap_data->message_type = UNSUCCESSFUL_OUTCOME;




  offset = dissect_per_open_type_pdu_new(tvb, offset, actx, tree, hf_index, dissect_UnsuccessfulOutcomeValue);

  return offset;
}


static const per_sequence_t UnsuccessfulOutcome_sequence[] = {
  { &hf_s1ap_procedureCode  , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ProcedureCode },
  { &hf_s1ap_criticality    , ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_Criticality },
  { &hf_s1ap_unsuccessfulOutcome_value, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_UnsuccessfulOutcome_value },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_UnsuccessfulOutcome(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_UnsuccessfulOutcome, UnsuccessfulOutcome_sequence);

  return offset;
}


static const value_string s1ap_S1AP_PDU_vals[] = {
  {   0, "initiatingMessage" },
  {   1, "successfulOutcome" },
  {   2, "unsuccessfulOutcome" },
  { 0, NULL }
};

static const per_choice_t S1AP_PDU_choice[] = {
  {   0, &hf_s1ap_initiatingMessage, ASN1_EXTENSION_ROOT    , dissect_s1ap_InitiatingMessage },
  {   1, &hf_s1ap_successfulOutcome, ASN1_EXTENSION_ROOT    , dissect_s1ap_SuccessfulOutcome },
  {   2, &hf_s1ap_unsuccessfulOutcome, ASN1_EXTENSION_ROOT    , dissect_s1ap_UnsuccessfulOutcome },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_S1AP_PDU(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_S1AP_PDU, S1AP_PDU_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_SONtransferApplicationIdentity_vals[] = {
  {   0, "cell-load-reporting" },
  {   1, "multi-cell-load-reporting" },
  {   2, "event-triggered-cell-load-reporting" },
  {   3, "ho-reporting" },
  {   4, "eutran-cell-activation" },
  {   5, "energy-savings-indication" },
  {   6, "failure-event-reporting" },
  { 0, NULL }
};


static int
dissect_s1ap_SONtransferApplicationIdentity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 6, NULL);

  return offset;
}



static int
dissect_s1ap_OCTET_STRING(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}



static int
dissect_s1ap_EHRPD_Sector_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       16, 16, FALSE, NULL);

  return offset;
}


static const value_string s1ap_IRAT_Cell_ID_vals[] = {
  {   0, "eUTRAN" },
  {   1, "uTRAN" },
  {   2, "gERAN" },
  {   3, "eHRPD" },
  { 0, NULL }
};

static const per_choice_t IRAT_Cell_ID_choice[] = {
  {   0, &hf_s1ap_eUTRAN_01      , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   1, &hf_s1ap_uTRAN          , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   2, &hf_s1ap_gERAN          , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   3, &hf_s1ap_eHRPD_01       , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_EHRPD_Sector_ID },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_IRAT_Cell_ID(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_IRAT_Cell_ID, IRAT_Cell_ID_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t RequestedCellList_sequence_of[1] = {
  { &hf_s1ap_RequestedCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_IRAT_Cell_ID },
};

static int
dissect_s1ap_RequestedCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_RequestedCellList, RequestedCellList_sequence_of,
                                                  1, maxnoofIRATReportingCells, FALSE);

  return offset;
}


static const per_sequence_t MultiCellLoadReportingRequest_sequence[] = {
  { &hf_s1ap_requestedCellList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_RequestedCellList },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_MultiCellLoadReportingRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_MultiCellLoadReportingRequest, MultiCellLoadReportingRequest_sequence);

  return offset;
}


static const value_string s1ap_NumberOfMeasurementReportingLevels_vals[] = {
  {   0, "rl2" },
  {   1, "rl3" },
  {   2, "rl4" },
  {   3, "rl5" },
  {   4, "rl10" },
  { 0, NULL }
};


static int
dissect_s1ap_NumberOfMeasurementReportingLevels(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     5, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t EventTriggeredCellLoadReportingRequest_sequence[] = {
  { &hf_s1ap_numberOfMeasurementReportingLevels, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NumberOfMeasurementReportingLevels },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EventTriggeredCellLoadReportingRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EventTriggeredCellLoadReportingRequest, EventTriggeredCellLoadReportingRequest_sequence);

  return offset;
}


static const value_string s1ap_HoType_vals[] = {
  {   0, "ltetoutran" },
  {   1, "ltetogeran" },
  { 0, NULL }
};


static int
dissect_s1ap_HoType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_HoReportType_vals[] = {
  {   0, "unnecessaryhotoanotherrat" },
  {   1, "earlyirathandover" },
  { 0, NULL }
};


static int
dissect_s1ap_HoReportType(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 1, NULL);

  return offset;
}


static const per_sequence_t CandidateCellList_sequence_of[1] = {
  { &hf_s1ap_CandidateCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_IRAT_Cell_ID },
};

static int
dissect_s1ap_CandidateCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CandidateCellList, CandidateCellList_sequence_of,
                                                  1, maxnoofcandidateCells, FALSE);

  return offset;
}



static int
dissect_s1ap_INTEGER_0_503(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 503U, NULL, FALSE);

  return offset;
}


static const per_sequence_t CandidatePCI_sequence[] = {
  { &hf_s1ap_pCI            , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_INTEGER_0_503 },
  { &hf_s1ap_eARFCN         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CandidatePCI(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CandidatePCI, CandidatePCI_sequence);

  return offset;
}


static const per_sequence_t CandidatePCIList_sequence_of[1] = {
  { &hf_s1ap_CandidatePCIList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CandidatePCI },
};

static int
dissect_s1ap_CandidatePCIList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CandidatePCIList, CandidatePCIList_sequence_of,
                                                  1, maxnoofcandidateCells, FALSE);

  return offset;
}


static const per_sequence_t HOReport_sequence[] = {
  { &hf_s1ap_hoType         , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_HoType },
  { &hf_s1ap_hoReportType   , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_HoReportType },
  { &hf_s1ap_hosourceID     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_IRAT_Cell_ID },
  { &hf_s1ap_hoTargetID     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_IRAT_Cell_ID },
  { &hf_s1ap_candidateCellList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CandidateCellList },
  { &hf_s1ap_candidatePCIList, ASN1_NOT_EXTENSION_ROOT, ASN1_OPTIONAL    , dissect_s1ap_CandidatePCIList },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_HOReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_HOReport, HOReport_sequence);

  return offset;
}


static const per_sequence_t CellsToActivateList_Item_sequence[] = {
  { &hf_s1ap_cell_ID_01     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellsToActivateList_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellsToActivateList_Item, CellsToActivateList_Item_sequence);

  return offset;
}


static const per_sequence_t CellsToActivateList_sequence_of[1] = {
  { &hf_s1ap_CellsToActivateList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_CellsToActivateList_Item },
};

static int
dissect_s1ap_CellsToActivateList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_CellsToActivateList, CellsToActivateList_sequence_of,
                                                  1, maxnoofCellineNB, FALSE);

  return offset;
}



static int
dissect_s1ap_INTEGER_1_60(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 60U, NULL, FALSE);

  return offset;
}


static const per_sequence_t CellActivationRequest_sequence[] = {
  { &hf_s1ap_cellsToActivateList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellsToActivateList },
  { &hf_s1ap_minimumActivationTime, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_INTEGER_1_60 },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellActivationRequest(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellActivationRequest, CellActivationRequest_sequence);

  return offset;
}


static const value_string s1ap_NotifyFlag_vals[] = {
  {   0, "activated" },
  {   1, "deactivated" },
  { 0, NULL }
};


static int
dissect_s1ap_NotifyFlag(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     2, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t NotificationCellList_Item_sequence[] = {
  { &hf_s1ap_cell_ID_01     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING },
  { &hf_s1ap_notifyFlag     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NotifyFlag },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_NotificationCellList_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_NotificationCellList_Item, NotificationCellList_Item_sequence);

  return offset;
}


static const per_sequence_t NotificationCellList_sequence_of[1] = {
  { &hf_s1ap_NotificationCellList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_NotificationCellList_Item },
};

static int
dissect_s1ap_NotificationCellList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_NotificationCellList, NotificationCellList_sequence_of,
                                                  1, maxnoofCellineNB, FALSE);

  return offset;
}


static const per_sequence_t CellStateIndication_sequence[] = {
  { &hf_s1ap_notificationCellList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_NotificationCellList },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellStateIndication(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellStateIndication, CellStateIndication_sequence);

  return offset;
}



static int
dissect_s1ap_T_uERLFReportContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
#line 883 "./asn1/s1ap/s1ap.cnf"
  tvbuff_t *parameter_tvb;
  proto_tree *subtree;
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, &parameter_tvb);

  if (!parameter_tvb)
    return offset;

  if (g_s1ap_dissect_container) {
    subtree = proto_item_add_subtree(actx->created_item, ett_s1ap_UE_RLF_Report_Container);
    TRY {
      dissect_lte_rrc_RLF_Report_r9_PDU(parameter_tvb, actx->pinfo, subtree, NULL);
    }
    CATCH_BOUNDS_ERRORS {
      show_exception(parameter_tvb, actx->pinfo, subtree, EXCEPT_CODE, GET_MESSAGE);
    }
    ENDTRY;
  }



  return offset;
}


static const per_sequence_t TooEarlyInterRATHOReportReportFromEUTRAN_sequence[] = {
  { &hf_s1ap_uERLFReportContainer, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_T_uERLFReportContainer },
  { &hf_s1ap_mobilityInformation, ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_MobilityInformation },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_TooEarlyInterRATHOReportReportFromEUTRAN(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_TooEarlyInterRATHOReportReportFromEUTRAN, TooEarlyInterRATHOReportReportFromEUTRAN_sequence);

  return offset;
}


static const value_string s1ap_FailureEventReport_vals[] = {
  {   0, "tooEarlyInterRATHOReportFromEUTRAN" },
  { 0, NULL }
};

static const per_choice_t FailureEventReport_choice[] = {
  {   0, &hf_s1ap_tooEarlyInterRATHOReportFromEUTRAN, ASN1_EXTENSION_ROOT    , dissect_s1ap_TooEarlyInterRATHOReportReportFromEUTRAN },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_FailureEventReport(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_FailureEventReport, FailureEventReport_choice,
                                 NULL);

  return offset;
}


const value_string s1ap_SONtransferRequestContainer_vals[] = {
  {   0, "cellLoadReporting" },
  {   1, "multiCellLoadReporting" },
  {   2, "eventTriggeredCellLoadReporting" },
  {   3, "hOReporting" },
  {   4, "eutranCellActivation" },
  {   5, "energySavingsIndication" },
  {   6, "failureEventReporting" },
  { 0, NULL }
};

static const per_choice_t SONtransferRequestContainer_choice[] = {
  {   0, &hf_s1ap_cellLoadReporting, ASN1_EXTENSION_ROOT    , dissect_s1ap_NULL },
  {   1, &hf_s1ap_multiCellLoadReporting, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_MultiCellLoadReportingRequest },
  {   2, &hf_s1ap_eventTriggeredCellLoadReporting, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_EventTriggeredCellLoadReportingRequest },
  {   3, &hf_s1ap_hOReporting    , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_HOReport },
  {   4, &hf_s1ap_eutranCellActivation, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellActivationRequest },
  {   5, &hf_s1ap_energySavingsIndication, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellStateIndication },
  {   6, &hf_s1ap_failureEventReporting, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_FailureEventReport },
  { 0, NULL, 0, NULL }
};

int
dissect_s1ap_SONtransferRequestContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SONtransferRequestContainer, SONtransferRequestContainer_choice,
                                 NULL);

  return offset;
}



static int
dissect_s1ap_CompositeAvailableCapacityGroup(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_octet_string(tvb, offset, actx, tree, hf_index,
                                       NO_BOUND, NO_BOUND, FALSE, NULL);

  return offset;
}


static const per_sequence_t EUTRANcellLoadReportingResponse_sequence[] = {
  { &hf_s1ap_compositeAvailableCapacityGroup, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CompositeAvailableCapacityGroup },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EUTRANcellLoadReportingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EUTRANcellLoadReportingResponse, EUTRANcellLoadReportingResponse_sequence);

  return offset;
}



static int
dissect_s1ap_EHRPDSectorCapacityClassValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            1U, 100U, NULL, TRUE);

  return offset;
}



static int
dissect_s1ap_EHRPDCapacityValue(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_integer(tvb, offset, actx, tree, hf_index,
                                                            0U, 100U, NULL, FALSE);

  return offset;
}


static const per_sequence_t EHRPDCompositeAvailableCapacity_sequence[] = {
  { &hf_s1ap_eHRPDSectorCapacityClassValue, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPDSectorCapacityClassValue },
  { &hf_s1ap_eHRPDCapacityValue, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPDCapacityValue },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EHRPDCompositeAvailableCapacity(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EHRPDCompositeAvailableCapacity, EHRPDCompositeAvailableCapacity_sequence);

  return offset;
}


static const per_sequence_t EHRPDSectorLoadReportingResponse_sequence[] = {
  { &hf_s1ap_dL_EHRPD_CompositeAvailableCapacity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPDCompositeAvailableCapacity },
  { &hf_s1ap_uL_EHRPD_CompositeAvailableCapacity, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPDCompositeAvailableCapacity },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EHRPDSectorLoadReportingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EHRPDSectorLoadReportingResponse, EHRPDSectorLoadReportingResponse_sequence);

  return offset;
}


static const value_string s1ap_CellLoadReportingResponse_vals[] = {
  {   0, "eUTRAN" },
  {   1, "uTRAN" },
  {   2, "gERAN" },
  {   3, "eHRPD" },
  { 0, NULL }
};

static const per_choice_t CellLoadReportingResponse_choice[] = {
  {   0, &hf_s1ap_eUTRAN         , ASN1_EXTENSION_ROOT    , dissect_s1ap_EUTRANcellLoadReportingResponse },
  {   1, &hf_s1ap_uTRAN          , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   2, &hf_s1ap_gERAN          , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   3, &hf_s1ap_eHRPD          , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_EHRPDSectorLoadReportingResponse },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_CellLoadReportingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_CellLoadReportingResponse, CellLoadReportingResponse_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t EUTRANResponse_sequence[] = {
  { &hf_s1ap_cell_ID_01     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING },
  { &hf_s1ap_eUTRANcellLoadReportingResponse, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EUTRANcellLoadReportingResponse },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EUTRANResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EUTRANResponse, EUTRANResponse_sequence);

  return offset;
}


static const per_sequence_t EHRPDMultiSectorLoadReportingResponseItem_sequence[] = {
  { &hf_s1ap_eHRPD_Sector_ID_01, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPD_Sector_ID },
  { &hf_s1ap_eHRPDSectorLoadReportingResponse, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_EHRPDSectorLoadReportingResponse },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EHRPDMultiSectorLoadReportingResponseItem(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EHRPDMultiSectorLoadReportingResponseItem, EHRPDMultiSectorLoadReportingResponseItem_sequence);

  return offset;
}


static const value_string s1ap_MultiCellLoadReportingResponse_Item_vals[] = {
  {   0, "eUTRANResponse" },
  {   1, "uTRANResponse" },
  {   2, "gERANResponse" },
  {   3, "eHRPD" },
  { 0, NULL }
};

static const per_choice_t MultiCellLoadReportingResponse_Item_choice[] = {
  {   0, &hf_s1ap_eUTRANResponse , ASN1_EXTENSION_ROOT    , dissect_s1ap_EUTRANResponse },
  {   1, &hf_s1ap_uTRANResponse  , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   2, &hf_s1ap_gERANResponse  , ASN1_EXTENSION_ROOT    , dissect_s1ap_OCTET_STRING },
  {   3, &hf_s1ap_eHRPD_02       , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_EHRPDMultiSectorLoadReportingResponseItem },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_MultiCellLoadReportingResponse_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_MultiCellLoadReportingResponse_Item, MultiCellLoadReportingResponse_Item_choice,
                                 NULL);

  return offset;
}


static const per_sequence_t MultiCellLoadReportingResponse_sequence_of[1] = {
  { &hf_s1ap_MultiCellLoadReportingResponse_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_MultiCellLoadReportingResponse_Item },
};

static int
dissect_s1ap_MultiCellLoadReportingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_MultiCellLoadReportingResponse, MultiCellLoadReportingResponse_sequence_of,
                                                  1, maxnoofIRATReportingCells, FALSE);

  return offset;
}


static const value_string s1ap_OverloadFlag_vals[] = {
  {   0, "overload" },
  { 0, NULL }
};


static int
dissect_s1ap_OverloadFlag(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     1, NULL, TRUE, 0, NULL);

  return offset;
}


static const per_sequence_t EventTriggeredCellLoadReportingResponse_sequence[] = {
  { &hf_s1ap_cellLoadReportingResponse, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_CellLoadReportingResponse },
  { &hf_s1ap_overloadFlag   , ASN1_EXTENSION_ROOT    , ASN1_OPTIONAL    , dissect_s1ap_OverloadFlag },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_EventTriggeredCellLoadReportingResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_EventTriggeredCellLoadReportingResponse, EventTriggeredCellLoadReportingResponse_sequence);

  return offset;
}


static const per_sequence_t ActivatedCellsList_Item_sequence[] = {
  { &hf_s1ap_cell_ID_01     , ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_OCTET_STRING },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_ActivatedCellsList_Item(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_ActivatedCellsList_Item, ActivatedCellsList_Item_sequence);

  return offset;
}


static const per_sequence_t ActivatedCellsList_sequence_of[1] = {
  { &hf_s1ap_ActivatedCellsList_item, ASN1_NO_EXTENSIONS     , ASN1_NOT_OPTIONAL, dissect_s1ap_ActivatedCellsList_Item },
};

static int
dissect_s1ap_ActivatedCellsList(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_constrained_sequence_of(tvb, offset, actx, tree, hf_index,
                                                  ett_s1ap_ActivatedCellsList, ActivatedCellsList_sequence_of,
                                                  0, maxnoofCellineNB, FALSE);

  return offset;
}


static const per_sequence_t CellActivationResponse_sequence[] = {
  { &hf_s1ap_activatedCellsList, ASN1_EXTENSION_ROOT    , ASN1_NOT_OPTIONAL, dissect_s1ap_ActivatedCellsList },
  { NULL, 0, 0, NULL }
};

static int
dissect_s1ap_CellActivationResponse(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_sequence(tvb, offset, actx, tree, hf_index,
                                   ett_s1ap_CellActivationResponse, CellActivationResponse_sequence);

  return offset;
}


const value_string s1ap_SONtransferResponseContainer_vals[] = {
  {   0, "cellLoadReporting" },
  {   1, "multiCellLoadReporting" },
  {   2, "eventTriggeredCellLoadReporting" },
  {   3, "hOReporting" },
  {   4, "eutranCellActivation" },
  {   5, "energySavingsIndication" },
  {   6, "failureEventReporting" },
  { 0, NULL }
};

static const per_choice_t SONtransferResponseContainer_choice[] = {
  {   0, &hf_s1ap_cellLoadReporting_01, ASN1_EXTENSION_ROOT    , dissect_s1ap_CellLoadReportingResponse },
  {   1, &hf_s1ap_multiCellLoadReporting_01, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_MultiCellLoadReportingResponse },
  {   2, &hf_s1ap_eventTriggeredCellLoadReporting_01, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_EventTriggeredCellLoadReportingResponse },
  {   3, &hf_s1ap_hOReporting_01 , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_NULL },
  {   4, &hf_s1ap_eutranCellActivation_01, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellActivationResponse },
  {   5, &hf_s1ap_energySavingsIndication_01, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_NULL },
  {   6, &hf_s1ap_failureEventReporting_01, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_NULL },
  { 0, NULL, 0, NULL }
};

int
dissect_s1ap_SONtransferResponseContainer(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SONtransferResponseContainer, SONtransferResponseContainer_choice,
                                 NULL);

  return offset;
}


static const value_string s1ap_CellLoadReportingCause_vals[] = {
  {   0, "application-container-syntax-error" },
  {   1, "inconsistent-reporting-cell-identifier" },
  {   2, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_CellLoadReportingCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_HOReportingCause_vals[] = {
  {   0, "application-container-syntax-error" },
  {   1, "inconsistent-reporting-cell-identifier" },
  {   2, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_HOReportingCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_CellActivationCause_vals[] = {
  {   0, "application-container-syntax-error" },
  {   1, "inconsistent-reporting-cell-identifier" },
  {   2, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_CellActivationCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_CellStateIndicationCause_vals[] = {
  {   0, "application-container-syntax-error" },
  {   1, "inconsistent-reporting-cell-identifier" },
  {   2, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_CellStateIndicationCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_FailureEventReportingCause_vals[] = {
  {   0, "application-container-syntax-error" },
  {   1, "inconsistent-reporting-cell-identifier" },
  {   2, "unspecified" },
  { 0, NULL }
};


static int
dissect_s1ap_FailureEventReportingCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_enumerated(tvb, offset, actx, tree, hf_index,
                                     3, NULL, TRUE, 0, NULL);

  return offset;
}


static const value_string s1ap_SONtransferCause_vals[] = {
  {   0, "cellLoadReporting" },
  {   1, "multiCellLoadReporting" },
  {   2, "eventTriggeredCellLoadReporting" },
  {   3, "hOReporting" },
  {   4, "eutranCellActivation" },
  {   5, "energySavingsIndication" },
  {   6, "failureEventReporting" },
  { 0, NULL }
};

static const per_choice_t SONtransferCause_choice[] = {
  {   0, &hf_s1ap_cellLoadReporting_02, ASN1_EXTENSION_ROOT    , dissect_s1ap_CellLoadReportingCause },
  {   1, &hf_s1ap_multiCellLoadReporting_02, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellLoadReportingCause },
  {   2, &hf_s1ap_eventTriggeredCellLoadReporting_02, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellLoadReportingCause },
  {   3, &hf_s1ap_hOReporting_02 , ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_HOReportingCause },
  {   4, &hf_s1ap_eutranCellActivation_02, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellActivationCause },
  {   5, &hf_s1ap_energySavingsIndication_02, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_CellStateIndicationCause },
  {   6, &hf_s1ap_failureEventReporting_02, ASN1_NOT_EXTENSION_ROOT, dissect_s1ap_FailureEventReportingCause },
  { 0, NULL, 0, NULL }
};

static int
dissect_s1ap_SONtransferCause(tvbuff_t *tvb _U_, int offset _U_, asn1_ctx_t *actx _U_, proto_tree *tree _U_, int hf_index _U_) {
  offset = dissect_per_choice(tvb, offset, actx, tree, hf_index,
                                 ett_s1ap_SONtransferCause, SONtransferCause_choice,
                                 NULL);

  return offset;
}



/*--- PDUs ---*/

static int dissect_Additional_GUTI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Additional_GUTI(tvb, offset, &asn1_ctx, tree, hf_s1ap_Additional_GUTI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_AdditionalRRMPriorityIndex_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_AdditionalRRMPriorityIndex(tvb, offset, &asn1_ctx, tree, hf_s1ap_AdditionalRRMPriorityIndex_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_AerialUEsubscriptionInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_AerialUEsubscriptionInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_AerialUEsubscriptionInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_AssistanceDataForPaging_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_AssistanceDataForPaging(tvb, offset, &asn1_ctx, tree, hf_s1ap_AssistanceDataForPaging_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Bearers_SubjectToStatusTransfer_Item_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Bearers_SubjectToStatusTransfer_Item(tvb, offset, &asn1_ctx, tree, hf_s1ap_Bearers_SubjectToStatusTransfer_Item_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Bearers_SubjectToEarlyStatusTransfer_Item_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item(tvb, offset, &asn1_ctx, tree, hf_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_BearerType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_BearerType(tvb, offset, &asn1_ctx, tree, hf_s1ap_BearerType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_BluetoothMeasurementConfiguration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_BluetoothMeasurementConfiguration(tvb, offset, &asn1_ctx, tree, hf_s1ap_BluetoothMeasurementConfiguration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_BroadcastCancelledAreaList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_BroadcastCancelledAreaList(tvb, offset, &asn1_ctx, tree, hf_s1ap_BroadcastCancelledAreaList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_BroadcastCompletedAreaList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_BroadcastCompletedAreaList(tvb, offset, &asn1_ctx, tree, hf_s1ap_BroadcastCompletedAreaList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cause(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CellAccessMode_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CellAccessMode(tvb, offset, &asn1_ctx, tree, hf_s1ap_CellAccessMode_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CellIdentifierAndCELevelForCECapableUEs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CellIdentifierAndCELevelForCECapableUEs(tvb, offset, &asn1_ctx, tree, hf_s1ap_CellIdentifierAndCELevelForCECapableUEs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CE_mode_B_SupportIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CE_mode_B_SupportIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_CE_mode_B_SupportIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000PDU_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000PDU(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000PDU_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000RATType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000RATType(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000RATType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000SectorID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000SectorID(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000SectorID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000HOStatus_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000HOStatus(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000HOStatus_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000HORequiredIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000HORequiredIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000HORequiredIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000OneXSRVCCInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000OneXSRVCCInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000OneXSRVCCInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Cdma2000OneXRAND_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Cdma2000OneXRAND(tvb, offset, &asn1_ctx, tree, hf_s1ap_Cdma2000OneXRAND_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CNDomain_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CNDomain(tvb, offset, &asn1_ctx, tree, hf_s1ap_CNDomain_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CNTypeRestrictions_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CNTypeRestrictions(tvb, offset, &asn1_ctx, tree, hf_s1ap_CNTypeRestrictions_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ConcurrentWarningMessageIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ConcurrentWarningMessageIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_ConcurrentWarningMessageIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ConnectedengNBList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ConnectedengNBList(tvb, offset, &asn1_ctx, tree, hf_s1ap_ConnectedengNBList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ContextatSource_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ContextatSource(tvb, offset, &asn1_ctx, tree, hf_s1ap_ContextatSource_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Correlation_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Correlation_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_Correlation_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSFallbackIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CSFallbackIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_CSFallbackIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_AdditionalCSFallbackIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_AdditionalCSFallbackIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_AdditionalCSFallbackIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSG_Id_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CSG_Id(tvb, offset, &asn1_ctx, tree, hf_s1ap_CSG_Id_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSG_IdList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CSG_IdList(tvb, offset, &asn1_ctx, tree, hf_s1ap_CSG_IdList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSGMembershipStatus_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CSGMembershipStatus(tvb, offset, &asn1_ctx, tree, hf_s1ap_CSGMembershipStatus_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_COUNTValueExtended_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_COUNTValueExtended(tvb, offset, &asn1_ctx, tree, hf_s1ap_COUNTValueExtended_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_COUNTvaluePDCP_SNlength18_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_COUNTvaluePDCP_SNlength18(tvb, offset, &asn1_ctx, tree, hf_s1ap_COUNTvaluePDCP_SNlength18_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Coverage_Level_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Coverage_Level(tvb, offset, &asn1_ctx, tree, hf_s1ap_Coverage_Level_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CriticalityDiagnostics_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CriticalityDiagnostics(tvb, offset, &asn1_ctx, tree, hf_s1ap_CriticalityDiagnostics_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DAPSRequestInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DAPSRequestInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_DAPSRequestInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DAPSResponseInfoList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DAPSResponseInfoList(tvb, offset, &asn1_ctx, tree, hf_s1ap_DAPSResponseInfoList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DAPSResponseInfoItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DAPSResponseInfoItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_DAPSResponseInfoItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DataCodingScheme_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DataCodingScheme(tvb, offset, &asn1_ctx, tree, hf_s1ap_DataCodingScheme_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DataSize_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DataSize(tvb, offset, &asn1_ctx, tree, hf_s1ap_DataSize_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DCN_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DCN_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_DCN_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ServedDCNs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ServedDCNs(tvb, offset, &asn1_ctx, tree, hf_s1ap_ServedDCNs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DL_CP_SecurityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DL_CP_SecurityInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_DL_CP_SecurityInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Direct_Forwarding_Path_Availability_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Direct_Forwarding_Path_Availability(tvb, offset, &asn1_ctx, tree, hf_s1ap_Direct_Forwarding_Path_Availability_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Data_Forwarding_Not_Possible_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Data_Forwarding_Not_Possible(tvb, offset, &asn1_ctx, tree, hf_s1ap_Data_Forwarding_Not_Possible_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DLNASPDUDeliveryAckRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DLNASPDUDeliveryAckRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_DLNASPDUDeliveryAckRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PWSfailedECGIList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PWSfailedECGIList(tvb, offset, &asn1_ctx, tree, hf_s1ap_PWSfailedECGIList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EDT_Session_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EDT_Session(tvb, offset, &asn1_ctx, tree, hf_s1ap_EDT_Session_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EmergencyAreaIDListForRestart_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EmergencyAreaIDListForRestart(tvb, offset, &asn1_ctx, tree, hf_s1ap_EmergencyAreaIDListForRestart_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EmergencyIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EmergencyIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_EmergencyIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENB_EarlyStatusTransfer_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENB_EarlyStatusTransfer_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENB_EarlyStatusTransfer_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_Global_ENB_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Global_ENB_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_Global_ENB_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_GUMMEIList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_GUMMEIList(tvb, offset, &asn1_ctx, tree, hf_s1ap_GUMMEIList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_ENB_StatusTransfer_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENB_StatusTransfer_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_ENB_StatusTransfer_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENB_UE_S1AP_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENB_UE_S1AP_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENB_UE_S1AP_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBname_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBname(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBname_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_EN_DCSONConfigurationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EN_DCSONConfigurationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_EN_DCSONConfigurationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EndIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EndIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_EndIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EnhancedCoverageRestricted_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EnhancedCoverageRestricted(tvb, offset, &asn1_ctx, tree, hf_s1ap_EnhancedCoverageRestricted_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CE_ModeBRestricted_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CE_ModeBRestricted(tvb, offset, &asn1_ctx, tree, hf_s1ap_CE_ModeBRestricted_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABInformationListItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABInformationListItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABInformationListItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABList(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABLevelQoSParameters_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABLevelQoSParameters(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABLevelQoSParameters_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABUsageReportItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABUsageReportItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABUsageReportItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Ethernet_Type_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Ethernet_Type(tvb, offset, &asn1_ctx, tree, hf_s1ap_Ethernet_Type_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_EUTRAN_CGI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EUTRAN_CGI(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_EUTRAN_CGI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_EUTRANRoundTripDelayEstimationInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_EUTRANRoundTripDelayEstimationInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_EUTRANRoundTripDelayEstimationInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ExpectedUEBehaviour_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ExpectedUEBehaviour(tvb, offset, &asn1_ctx, tree, hf_s1ap_ExpectedUEBehaviour_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ExtendedBitRate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ExtendedBitRate(tvb, offset, &asn1_ctx, tree, hf_s1ap_ExtendedBitRate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ExtendedRepetitionPeriod_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ExtendedRepetitionPeriod(tvb, offset, &asn1_ctx, tree, hf_s1ap_ExtendedRepetitionPeriod_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Extended_UEIdentityIndexValue_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Extended_UEIdentityIndexValue(tvb, offset, &asn1_ctx, tree, hf_s1ap_Extended_UEIdentityIndexValue_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_GUMMEI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_GUMMEI(tvb, offset, &asn1_ctx, tree, hf_s1ap_GUMMEI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_GUMMEIType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_GUMMEIType(tvb, offset, &asn1_ctx, tree, hf_s1ap_GUMMEIType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_GWContextReleaseIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_GWContextReleaseIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_GWContextReleaseIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverFlag_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverFlag(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverFlag_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_HandoverRestrictionList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverRestrictionList(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_HandoverRestrictionList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverType(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Masked_IMEISV_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Masked_IMEISV(tvb, offset, &asn1_ctx, tree, hf_s1ap_Masked_IMEISV_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_ImmediateMDT_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ImmediateMDT(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_ImmediateMDT_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_InformationOnRecommendedCellsAndENBsForPaging_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_InformationOnRecommendedCellsAndENBsForPaging(tvb, offset, &asn1_ctx, tree, hf_s1ap_InformationOnRecommendedCellsAndENBsForPaging_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IntersystemMeasurementConfiguration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IntersystemMeasurementConfiguration(tvb, offset, &asn1_ctx, tree, hf_s1ap_IntersystemMeasurementConfiguration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IntersystemSONConfigurationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IntersystemSONConfigurationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_IntersystemSONConfigurationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IMSvoiceEPSfallbackfrom5G_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IMSvoiceEPSfallbackfrom5G(tvb, offset, &asn1_ctx, tree, hf_s1ap_IMSvoiceEPSfallbackfrom5G_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IAB_Authorized_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IAB_Authorized(tvb, offset, &asn1_ctx, tree, hf_s1ap_IAB_Authorized_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IAB_Node_Indication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IAB_Node_Indication(tvb, offset, &asn1_ctx, tree, hf_s1ap_IAB_Node_Indication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_IAB_Supported_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_IAB_Supported(tvb, offset, &asn1_ctx, tree, hf_s1ap_IAB_Supported_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_KillAllWarningMessages_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_KillAllWarningMessages(tvb, offset, &asn1_ctx, tree, hf_s1ap_KillAllWarningMessages_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LAI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LAI(tvb, offset, &asn1_ctx, tree, hf_s1ap_LAI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_LastVisitedEUTRANCellInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LastVisitedEUTRANCellInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_LastVisitedEUTRANCellInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_LastVisitedGERANCellInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LastVisitedGERANCellInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_LastVisitedGERANCellInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LPPa_PDU_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LPPa_PDU(tvb, offset, &asn1_ctx, tree, hf_s1ap_LPPa_PDU_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LHN_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LHN_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_LHN_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LoggedMBSFNMDT_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LoggedMBSFNMDT(tvb, offset, &asn1_ctx, tree, hf_s1ap_LoggedMBSFNMDT_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LTE_M_Indication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LTE_M_Indication(tvb, offset, &asn1_ctx, tree, hf_s1ap_LTE_M_Indication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_M3Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_M3Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_M3Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_M4Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_M4Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_M4Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_M5Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_M5Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_M5Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_M6Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_M6Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_M6Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_M7Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_M7Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_M7Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MDT_Location_Info_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MDT_Location_Info(tvb, offset, &asn1_ctx, tree, hf_s1ap_MDT_Location_Info_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MDT_Configuration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MDT_Configuration(tvb, offset, &asn1_ctx, tree, hf_s1ap_MDT_Configuration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ManagementBasedMDTAllowed_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ManagementBasedMDTAllowed(tvb, offset, &asn1_ctx, tree, hf_s1ap_ManagementBasedMDTAllowed_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MDTPLMNList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MDTPLMNList(tvb, offset, &asn1_ctx, tree, hf_s1ap_MDTPLMNList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PrivacyIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PrivacyIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_PrivacyIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_MDTMode_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MDTMode(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_MDTMode_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MessageIdentifier_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MessageIdentifier(tvb, offset, &asn1_ctx, tree, hf_s1ap_MessageIdentifier_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MobilityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MobilityInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_MobilityInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEname_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEname(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEname_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMERelaySupportIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMERelaySupportIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMERelaySupportIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MME_Group_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MME_Group_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_MME_Group_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MME_UE_S1AP_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MME_UE_S1AP_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_MME_UE_S1AP_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MSClassmark2_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MSClassmark2(tvb, offset, &asn1_ctx, tree, hf_s1ap_MSClassmark2_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MSClassmark3_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MSClassmark3(tvb, offset, &asn1_ctx, tree, hf_s1ap_MSClassmark3_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MutingAvailabilityIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MutingAvailabilityIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_MutingAvailabilityIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MutingPatternInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MutingPatternInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_MutingPatternInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MDT_ConfigurationNR_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MDT_ConfigurationNR(tvb, offset, &asn1_ctx, tree, hf_s1ap_MDT_ConfigurationNR_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NAS_PDU_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NAS_PDU(tvb, offset, &asn1_ctx, tree, hf_s1ap_NAS_PDU_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NASSecurityParametersfromE_UTRAN_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NASSecurityParametersfromE_UTRAN(tvb, offset, &asn1_ctx, tree, hf_s1ap_NASSecurityParametersfromE_UTRAN_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NASSecurityParameterstoE_UTRAN_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NASSecurityParameterstoE_UTRAN(tvb, offset, &asn1_ctx, tree, hf_s1ap_NASSecurityParameterstoE_UTRAN_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NB_IoT_DefaultPagingDRX_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NB_IoT_DefaultPagingDRX(tvb, offset, &asn1_ctx, tree, hf_s1ap_NB_IoT_DefaultPagingDRX_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NB_IoT_PagingDRX_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NB_IoT_PagingDRX(tvb, offset, &asn1_ctx, tree, hf_s1ap_NB_IoT_PagingDRX_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NB_IoT_Paging_eDRXInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NB_IoT_Paging_eDRXInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_NB_IoT_Paging_eDRXInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NB_IoT_RLF_Report_Container_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NB_IoT_RLF_Report_Container(tvb, offset, &asn1_ctx, tree, hf_s1ap_NB_IoT_RLF_Report_Container_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NB_IoT_UEIdentityIndexValue_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NB_IoT_UEIdentityIndexValue(tvb, offset, &asn1_ctx, tree, hf_s1ap_NB_IoT_UEIdentityIndexValue_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NotifySourceeNB_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NotifySourceeNB(tvb, offset, &asn1_ctx, tree, hf_s1ap_NotifySourceeNB_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NRrestrictioninEPSasSecondaryRAT_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NRrestrictioninEPSasSecondaryRAT(tvb, offset, &asn1_ctx, tree, hf_s1ap_NRrestrictioninEPSasSecondaryRAT_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NRrestrictionin5GS_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NRrestrictionin5GS(tvb, offset, &asn1_ctx, tree, hf_s1ap_NRrestrictionin5GS_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NRUESecurityCapabilities_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NRUESecurityCapabilities(tvb, offset, &asn1_ctx, tree, hf_s1ap_NRUESecurityCapabilities_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NumberofBroadcastRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NumberofBroadcastRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_NumberofBroadcastRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NRV2XServicesAuthorized_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NRV2XServicesAuthorized(tvb, offset, &asn1_ctx, tree, hf_s1ap_NRV2XServicesAuthorized_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NRUESidelinkAggregateMaximumBitrate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NRUESidelinkAggregateMaximumBitrate(tvb, offset, &asn1_ctx, tree, hf_s1ap_NRUESidelinkAggregateMaximumBitrate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_OverloadResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_OverloadResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_OverloadResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Packet_LossRate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Packet_LossRate(tvb, offset, &asn1_ctx, tree, hf_s1ap_Packet_LossRate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Paging_eDRXInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Paging_eDRXInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_Paging_eDRXInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PagingDRX_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PagingDRX(tvb, offset, &asn1_ctx, tree, hf_s1ap_PagingDRX_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PagingPriority_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PagingPriority(tvb, offset, &asn1_ctx, tree, hf_s1ap_PagingPriority_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PC5QoSParameters_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PC5QoSParameters(tvb, offset, &asn1_ctx, tree, hf_s1ap_PC5QoSParameters_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PendingDataIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PendingDataIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_PendingDataIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PLMNidentity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PLMNidentity(tvb, offset, &asn1_ctx, tree, hf_s1ap_PLMNidentity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ProSeAuthorized_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ProSeAuthorized(tvb, offset, &asn1_ctx, tree, hf_s1ap_ProSeAuthorized_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ProSeUEtoNetworkRelaying_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ProSeUEtoNetworkRelaying(tvb, offset, &asn1_ctx, tree, hf_s1ap_ProSeUEtoNetworkRelaying_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PS_ServiceNotAvailable_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PS_ServiceNotAvailable(tvb, offset, &asn1_ctx, tree, hf_s1ap_PS_ServiceNotAvailable_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PSCellInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PSCellInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_PSCellInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ReceiveStatusOfULPDCPSDUsExtended_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ReceiveStatusOfULPDCPSDUsExtended(tvb, offset, &asn1_ctx, tree, hf_s1ap_ReceiveStatusOfULPDCPSDUsExtended_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18(tvb, offset, &asn1_ctx, tree, hf_s1ap_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RecommendedCellItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RecommendedCellItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_RecommendedCellItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RecommendedENBItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RecommendedENBItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_RecommendedENBItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RelativeMMECapacity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RelativeMMECapacity(tvb, offset, &asn1_ctx, tree, hf_s1ap_RelativeMMECapacity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RelayNode_Indicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RelayNode_Indicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_RelayNode_Indicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RAT_Type_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RAT_Type(tvb, offset, &asn1_ctx, tree, hf_s1ap_RAT_Type_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RequestType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RequestType(tvb, offset, &asn1_ctx, tree, hf_s1ap_RequestType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RequestTypeAdditionalInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RequestTypeAdditionalInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_RequestTypeAdditionalInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RepetitionPeriod_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RepetitionPeriod(tvb, offset, &asn1_ctx, tree, hf_s1ap_RepetitionPeriod_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RRC_Establishment_Cause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RRC_Establishment_Cause(tvb, offset, &asn1_ctx, tree, hf_s1ap_RRC_Establishment_Cause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ECGIListForRestart_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ECGIListForRestart(tvb, offset, &asn1_ctx, tree, hf_s1ap_ECGIListForRestart_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Routing_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Routing_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_Routing_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecurityKey_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecurityKey(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecurityKey_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecurityContext_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecurityContext(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecurityContext_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecondaryRATDataUsageRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecondaryRATDataUsageRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecondaryRATDataUsageRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecondaryRATDataUsageReportList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecondaryRATDataUsageReportList(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecondaryRATDataUsageReportList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecondaryRATDataUsageReportItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecondaryRATDataUsageReportItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecondaryRATDataUsageReportItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SerialNumber_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SerialNumber(tvb, offset, &asn1_ctx, tree, hf_s1ap_SerialNumber_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ServiceType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ServiceType(tvb, offset, &asn1_ctx, tree, hf_s1ap_ServiceType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SONInformationReport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONInformationReport(tvb, offset, &asn1_ctx, tree, hf_s1ap_SONInformationReport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SONConfigurationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONConfigurationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SONConfigurationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SynchronisationInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SynchronisationInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_SynchronisationInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Source_ToTarget_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Source_ToTarget_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_Source_ToTarget_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SRVCCOperationNotPossible_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SRVCCOperationNotPossible(tvb, offset, &asn1_ctx, tree, hf_s1ap_SRVCCOperationNotPossible_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SRVCCOperationPossible_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SRVCCOperationPossible(tvb, offset, &asn1_ctx, tree, hf_s1ap_SRVCCOperationPossible_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SRVCCHOIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SRVCCHOIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_SRVCCHOIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SourceNodeID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SourceNodeID(tvb, offset, &asn1_ctx, tree, hf_s1ap_SourceNodeID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SourceeNB_ToTargeteNB_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SourceeNB_ToTargeteNB_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SourceeNB_ToTargeteNB_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ServedGUMMEIs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ServedGUMMEIs(tvb, offset, &asn1_ctx, tree, hf_s1ap_ServedGUMMEIs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ServedPLMNs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ServedPLMNs(tvb, offset, &asn1_ctx, tree, hf_s1ap_ServedPLMNs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SubscriberProfileIDforRFP_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SubscriberProfileIDforRFP(tvb, offset, &asn1_ctx, tree, hf_s1ap_SubscriberProfileIDforRFP_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Subscription_Based_UE_DifferentiationInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Subscription_Based_UE_DifferentiationInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_Subscription_Based_UE_DifferentiationInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SupportedTAs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SupportedTAs(tvb, offset, &asn1_ctx, tree, hf_s1ap_SupportedTAs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TimeSynchronisationInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TimeSynchronisationInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_TimeSynchronisationInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S_TMSI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S_TMSI(tvb, offset, &asn1_ctx, tree, hf_s1ap_S_TMSI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TAI_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TAI(tvb, offset, &asn1_ctx, tree, hf_s1ap_TAI_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TargetID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TargetID(tvb, offset, &asn1_ctx, tree, hf_s1ap_TargetID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_TargeteNB_ToSourceeNB_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TargeteNB_ToSourceeNB_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_TargeteNB_ToSourceeNB_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Target_ToSource_TransparentContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Target_ToSource_TransparentContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_Target_ToSource_TransparentContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TimeToWait_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TimeToWait(tvb, offset, &asn1_ctx, tree, hf_s1ap_TimeToWait_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Time_UE_StayedInCell_EnhancedGranularity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Time_UE_StayedInCell_EnhancedGranularity(tvb, offset, &asn1_ctx, tree, hf_s1ap_Time_UE_StayedInCell_EnhancedGranularity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TimeSinceSecondaryNodeRelease_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TimeSinceSecondaryNodeRelease(tvb, offset, &asn1_ctx, tree, hf_s1ap_TimeSinceSecondaryNodeRelease_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TransportInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TransportInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_TransportInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TransportLayerAddress_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TransportLayerAddress(tvb, offset, &asn1_ctx, tree, hf_s1ap_TransportLayerAddress_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TraceActivation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TraceActivation(tvb, offset, &asn1_ctx, tree, hf_s1ap_TraceActivation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_UTRAN_Trace_ID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_UTRAN_Trace_ID(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_UTRAN_Trace_ID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TrafficLoadReductionIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TrafficLoadReductionIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_TrafficLoadReductionIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TunnelInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TunnelInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_TunnelInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TAIListForRestart_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TAIListForRestart(tvb, offset, &asn1_ctx, tree, hf_s1ap_TAIListForRestart_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEAggregateMaximumBitrate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEAggregateMaximumBitrate(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEAggregateMaximumBitrate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEAppLayerMeasConfig_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEAppLayerMeasConfig(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEAppLayerMeasConfig_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UECapabilityInfoRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UECapabilityInfoRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UECapabilityInfoRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_RetentionInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_RetentionInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_RetentionInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_S1AP_IDs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_S1AP_IDs(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_S1AP_IDs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_associatedLogicalS1_ConnectionItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_associatedLogicalS1_ConnectionItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_associatedLogicalS1_ConnectionItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEIdentityIndexValue_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEIdentityIndexValue(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEIdentityIndexValue_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_UE_HistoryInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_HistoryInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_UE_HistoryInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_HistoryInformationFromTheUE_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_HistoryInformationFromTheUE(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_HistoryInformationFromTheUE_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEPagingID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEPagingID(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEPagingID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapability_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapability(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapability_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityForPaging_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityForPaging(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityForPaging_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityID_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityID(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityID_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UESecurityCapabilities_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UESecurityCapabilities(tvb, offset, &asn1_ctx, tree, hf_s1ap_UESecurityCapabilities_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UESidelinkAggregateMaximumBitrate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UESidelinkAggregateMaximumBitrate(tvb, offset, &asn1_ctx, tree, hf_s1ap_UESidelinkAggregateMaximumBitrate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_Usage_Type_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_Usage_Type(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_Usage_Type_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UL_CP_SecurityInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UL_CP_SecurityInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_UL_CP_SecurityInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UnlicensedSpectrumRestriction_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UnlicensedSpectrumRestriction(tvb, offset, &asn1_ctx, tree, hf_s1ap_UnlicensedSpectrumRestriction_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_URI_Address_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_URI_Address(tvb, offset, &asn1_ctx, tree, hf_s1ap_URI_Address_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UserLocationInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UserLocationInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_UserLocationInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEUserPlaneCIoTSupportIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEUserPlaneCIoTSupportIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEUserPlaneCIoTSupportIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_Application_Layer_Measurement_Capability_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_Application_Layer_Measurement_Capability(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_Application_Layer_Measurement_Capability_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_VoiceSupportMatchIndicator_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_VoiceSupportMatchIndicator(tvb, offset, &asn1_ctx, tree, hf_s1ap_VoiceSupportMatchIndicator_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_V2XServicesAuthorized_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_V2XServicesAuthorized(tvb, offset, &asn1_ctx, tree, hf_s1ap_V2XServicesAuthorized_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WarningAreaCoordinates_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WarningAreaCoordinates(tvb, offset, &asn1_ctx, tree, hf_s1ap_WarningAreaCoordinates_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WarningAreaList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WarningAreaList(tvb, offset, &asn1_ctx, tree, hf_s1ap_WarningAreaList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WarningType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WarningType(tvb, offset, &asn1_ctx, tree, hf_s1ap_WarningType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WarningSecurityInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WarningSecurityInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_WarningSecurityInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WarningMessageContents_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WarningMessageContents(tvb, offset, &asn1_ctx, tree, hf_s1ap_WarningMessageContents_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WLANMeasurementConfiguration_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WLANMeasurementConfiguration(tvb, offset, &asn1_ctx, tree, hf_s1ap_WLANMeasurementConfiguration_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WUS_Assistance_Information_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WUS_Assistance_Information(tvb, offset, &asn1_ctx, tree, hf_s1ap_WUS_Assistance_Information_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_X2TNLConfigurationInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_X2TNLConfigurationInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_X2TNLConfigurationInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBX2ExtTLAs_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBX2ExtTLAs(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBX2ExtTLAs_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBIndirectX2TransportLayerAddresses_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBIndirectX2TransportLayerAddresses(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBIndirectX2TransportLayerAddresses_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverRequired_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverRequired(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverRequired_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverCommand_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverCommand(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverCommand_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSubjecttoDataForwardingList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSubjecttoDataForwardingList(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSubjecttoDataForwardingList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABDataForwardingItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABDataForwardingItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABDataForwardingItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverPreparationFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverPreparationFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverPreparationFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupListHOReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupListHOReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupListHOReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupItemHOReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupItemHOReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupItemHOReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverRequestAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverRequestAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverRequestAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABAdmittedList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABAdmittedList(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABAdmittedList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABAdmittedItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABAdmittedItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABAdmittedItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedtoSetupListHOReqAck_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedtoSetupListHOReqAck(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedtoSetupListHOReqAck_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedToSetupItemHOReqAck_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedToSetupItemHOReqAck(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedToSetupItemHOReqAck_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverNotify_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverNotify(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverNotify_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PathSwitchRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PathSwitchRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_PathSwitchRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSwitchedDLList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSwitchedDLList(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSwitchedDLList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSwitchedDLItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSwitchedDLItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSwitchedDLItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PathSwitchRequestAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PathSwitchRequestAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_PathSwitchRequestAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSwitchedULList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSwitchedULList(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSwitchedULList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSwitchedULItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSwitchedULItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSwitchedULItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PathSwitchRequestFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PathSwitchRequestFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_PathSwitchRequestFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverCancel_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverCancel(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverCancel_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverCancelAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverCancelAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverCancelAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_HandoverSuccess_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_HandoverSuccess(tvb, offset, &asn1_ctx, tree, hf_s1ap_HandoverSuccess_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBEarlyStatusTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBEarlyStatusTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBEarlyStatusTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEEarlyStatusTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEEarlyStatusTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEEarlyStatusTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupListBearerSUReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupListBearerSUReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupListBearerSUReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupItemBearerSUReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupItemBearerSUReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupItemBearerSUReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupListBearerSURes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupListBearerSURes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupListBearerSURes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupItemBearerSURes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupItemBearerSURes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupItemBearerSURes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeModifiedListBearerModReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeModifiedListBearerModReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeModifiedListBearerModReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeModifiedItemBearerModReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeModifiedItemBearerModReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeModifiedItemBearerModReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyListBearerModRes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyListBearerModRes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyListBearerModRes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyItemBearerModRes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyItemBearerModRes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyItemBearerModRes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABReleaseCommand_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABReleaseCommand(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABReleaseCommand_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABReleaseResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABReleaseResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABReleaseResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABReleaseListBearerRelComp_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABReleaseListBearerRelComp(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABReleaseListBearerRelComp_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABReleaseItemBearerRelComp_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABReleaseItemBearerRelComp(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABReleaseItemBearerRelComp_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABReleaseIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABReleaseIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABReleaseIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_InitialContextSetupRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_InitialContextSetupRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_InitialContextSetupRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupListCtxtSUReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupListCtxtSUReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupListCtxtSUReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeSetupItemCtxtSUReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeSetupItemCtxtSUReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeSetupItemCtxtSUReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_InitialContextSetupResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_InitialContextSetupResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_InitialContextSetupResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupListCtxtSURes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupListCtxtSURes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupListCtxtSURes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABSetupItemCtxtSURes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABSetupItemCtxtSURes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABSetupItemCtxtSURes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_InitialContextSetupFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_InitialContextSetupFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_InitialContextSetupFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Paging_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Paging(tvb, offset, &asn1_ctx, tree, hf_s1ap_Paging_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TAIList_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TAIList(tvb, offset, &asn1_ctx, tree, hf_s1ap_TAIList_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TAIItem_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TAIItem(tvb, offset, &asn1_ctx, tree, hf_s1ap_TAIItem_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextReleaseRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextReleaseRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextReleaseRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextReleaseCommand_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextReleaseCommand(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextReleaseCommand_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextReleaseComplete_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextReleaseComplete(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextReleaseComplete_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextModificationRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextModificationRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextModificationRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextModificationResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextModificationResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextModificationResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextModificationFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextModificationFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextModificationFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityMatchRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityMatchRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityMatchRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityMatchResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityMatchResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityMatchResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DownlinkNASTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DownlinkNASTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_DownlinkNASTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_InitialUEMessage_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_InitialUEMessage(tvb, offset, &asn1_ctx, tree, hf_s1ap_InitialUEMessage_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UplinkNASTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UplinkNASTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_UplinkNASTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NASNonDeliveryIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NASNonDeliveryIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_NASNonDeliveryIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RerouteNASRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RerouteNASRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_RerouteNASRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S1_Message_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S1_Message(tvb, offset, &asn1_ctx, tree, hf_s1ap_S1_Message_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_NASDeliveryIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_NASDeliveryIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_NASDeliveryIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Reset_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Reset(tvb, offset, &asn1_ctx, tree, hf_s1ap_Reset_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ResetType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ResetType(tvb, offset, &asn1_ctx, tree, hf_s1ap_ResetType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ResetAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ResetAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_ResetAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UE_associatedLogicalS1_ConnectionListResAck_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UE_associatedLogicalS1_ConnectionListResAck(tvb, offset, &asn1_ctx, tree, hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ErrorIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ErrorIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_ErrorIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S1SetupRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S1SetupRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_S1SetupRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S1SetupResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S1SetupResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_S1SetupResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S1SetupFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S1SetupFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_S1SetupFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBConfigurationUpdate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBConfigurationUpdate(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBConfigurationUpdate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBConfigurationUpdateAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBConfigurationUpdateAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBConfigurationUpdateAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBConfigurationUpdateFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBConfigurationUpdateFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBConfigurationUpdateFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEConfigurationUpdate_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEConfigurationUpdate(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEConfigurationUpdate_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEConfigurationUpdateAcknowledge_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEConfigurationUpdateAcknowledge(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEConfigurationUpdateAcknowledge_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEConfigurationUpdateFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEConfigurationUpdateFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEConfigurationUpdateFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DownlinkS1cdma2000tunnelling_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DownlinkS1cdma2000tunnelling(tvb, offset, &asn1_ctx, tree, hf_s1ap_DownlinkS1cdma2000tunnelling_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UplinkS1cdma2000tunnelling_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UplinkS1cdma2000tunnelling(tvb, offset, &asn1_ctx, tree, hf_s1ap_UplinkS1cdma2000tunnelling_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UECapabilityInfoIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UECapabilityInfoIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_UECapabilityInfoIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBStatusTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBStatusTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBStatusTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEStatusTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEStatusTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEStatusTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TraceStart_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TraceStart(tvb, offset, &asn1_ctx, tree, hf_s1ap_TraceStart_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_TraceFailureIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_TraceFailureIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_TraceFailureIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DeactivateTrace_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DeactivateTrace(tvb, offset, &asn1_ctx, tree, hf_s1ap_DeactivateTrace_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CellTrafficTrace_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CellTrafficTrace(tvb, offset, &asn1_ctx, tree, hf_s1ap_CellTrafficTrace_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LocationReportingControl_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LocationReportingControl(tvb, offset, &asn1_ctx, tree, hf_s1ap_LocationReportingControl_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LocationReportingFailureIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LocationReportingFailureIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_LocationReportingFailureIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_LocationReport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_LocationReport(tvb, offset, &asn1_ctx, tree, hf_s1ap_LocationReport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_OverloadStart_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_OverloadStart(tvb, offset, &asn1_ctx, tree, hf_s1ap_OverloadStart_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_OverloadStop_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_OverloadStop(tvb, offset, &asn1_ctx, tree, hf_s1ap_OverloadStop_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WriteReplaceWarningRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WriteReplaceWarningRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_WriteReplaceWarningRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_WriteReplaceWarningResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_WriteReplaceWarningResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_WriteReplaceWarningResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBDirectInformationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBDirectInformationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBDirectInformationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_Inter_SystemInformationTransferType_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_Inter_SystemInformationTransferType(tvb, offset, &asn1_ctx, tree, hf_s1ap_Inter_SystemInformationTransferType_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEDirectInformationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEDirectInformationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEDirectInformationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBConfigurationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBConfigurationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBConfigurationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMEConfigurationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMEConfigurationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMEConfigurationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PrivateMessage_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PrivateMessage(tvb, offset, &asn1_ctx, tree, hf_s1ap_PrivateMessage_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_KillRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_KillRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_KillRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_KillResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_KillResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_KillResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PWSRestartIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PWSRestartIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_PWSRestartIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_PWSFailureIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_PWSFailureIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_PWSFailureIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DownlinkUEAssociatedLPPaTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DownlinkUEAssociatedLPPaTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_DownlinkUEAssociatedLPPaTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UplinkUEAssociatedLPPaTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UplinkUEAssociatedLPPaTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_UplinkUEAssociatedLPPaTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_DownlinkNonUEAssociatedLPPaTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_DownlinkNonUEAssociatedLPPaTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_DownlinkNonUEAssociatedLPPaTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UplinkNonUEAssociatedLPPaTransport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UplinkNonUEAssociatedLPPaTransport(tvb, offset, &asn1_ctx, tree, hf_s1ap_UplinkNonUEAssociatedLPPaTransport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModificationIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModificationIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModificationIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeModifiedListBearerModInd_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeModifiedListBearerModInd(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeModifiedListBearerModInd_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABToBeModifiedItemBearerModInd_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABToBeModifiedItemBearerModInd(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABToBeModifiedItemBearerModInd_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABNotToBeModifiedListBearerModInd_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABNotToBeModifiedListBearerModInd(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABNotToBeModifiedListBearerModInd_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABNotToBeModifiedItemBearerModInd_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABNotToBeModifiedItemBearerModInd(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABNotToBeModifiedItemBearerModInd_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_CSGMembershipInfo_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_CSGMembershipInfo(tvb, offset, &asn1_ctx, tree, hf_s1ap_CSGMembershipInfo_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModificationConfirm_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModificationConfirm(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModificationConfirm_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyListBearerModConf_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyListBearerModConf(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyListBearerModConf_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABModifyItemBearerModConf_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABModifyItemBearerModConf(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABModifyItemBearerModConf_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextModificationIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextModificationIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextModificationIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextModificationConfirm_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextModificationConfirm(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextModificationConfirm_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextSuspendRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextSuspendRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextSuspendRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextSuspendResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextSuspendResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextSuspendResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextResumeRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextResumeRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextResumeRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedToResumeListResumeReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedToResumeListResumeReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedToResumeListResumeReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedToResumeItemResumeReq_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedToResumeItemResumeReq(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedToResumeItemResumeReq_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextResumeResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextResumeResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextResumeResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedToResumeListResumeRes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedToResumeListResumeRes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedToResumeListResumeRes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_E_RABFailedToResumeItemResumeRes_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_E_RABFailedToResumeItemResumeRes(tvb, offset, &asn1_ctx, tree, hf_s1ap_E_RABFailedToResumeItemResumeRes_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEContextResumeFailure_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEContextResumeFailure(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEContextResumeFailure_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ConnectionEstablishmentIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ConnectionEstablishmentIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_ConnectionEstablishmentIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_RetrieveUEInformation_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_RetrieveUEInformation(tvb, offset, &asn1_ctx, tree, hf_s1ap_RetrieveUEInformation_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UEInformationTransfer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UEInformationTransfer(tvb, offset, &asn1_ctx, tree, hf_s1ap_UEInformationTransfer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_ENBCPRelocationIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_ENBCPRelocationIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_ENBCPRelocationIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_MMECPRelocationIndication_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_MMECPRelocationIndication(tvb, offset, &asn1_ctx, tree, hf_s1ap_MMECPRelocationIndication_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_SecondaryRATDataUsageReport_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SecondaryRATDataUsageReport(tvb, offset, &asn1_ctx, tree, hf_s1ap_SecondaryRATDataUsageReport_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityIDMappingRequest_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityIDMappingRequest(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityIDMappingRequest_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_UERadioCapabilityIDMappingResponse_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_UERadioCapabilityIDMappingResponse(tvb, offset, &asn1_ctx, tree, hf_s1ap_UERadioCapabilityIDMappingResponse_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
static int dissect_S1AP_PDU_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_S1AP_PDU(tvb, offset, &asn1_ctx, tree, hf_s1ap_S1AP_PDU_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SONtransferApplicationIdentity_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONtransferApplicationIdentity(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SONtransferApplicationIdentity_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SONtransferRequestContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONtransferRequestContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SONtransferRequestContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SONtransferResponseContainer_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONtransferResponseContainer(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SONtransferResponseContainer_PDU);
  offset += 7; offset >>= 3;
  return offset;
}
int dissect_s1ap_SONtransferCause_PDU(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_, void *data _U_) {
  int offset = 0;
  asn1_ctx_t asn1_ctx;
  asn1_ctx_init(&asn1_ctx, ASN1_ENC_PER, TRUE, pinfo);
  offset = dissect_s1ap_SONtransferCause(tvb, offset, &asn1_ctx, tree, hf_s1ap_s1ap_SONtransferCause_PDU);
  offset += 7; offset >>= 3;
  return offset;
}


/*--- End of included file: packet-s1ap-fn.c ---*/
#line 397 "./asn1/s1ap/packet-s1ap-template.c"

static int dissect_ProtocolIEFieldValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  s1ap_ctx_t s1ap_ctx;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  s1ap_ctx.message_type        = s1ap_data->message_type;
  s1ap_ctx.ProcedureCode       = s1ap_data->procedure_code;
  s1ap_ctx.ProtocolIE_ID       = s1ap_data->protocol_ie_id;
  s1ap_ctx.ProtocolExtensionID = s1ap_data->protocol_extension_id;

  return (dissector_try_uint_new(s1ap_ies_dissector_table, s1ap_data->protocol_ie_id, tvb, pinfo, tree, FALSE, &s1ap_ctx)) ? tvb_captured_length(tvb) : 0;
}
/* Currently not used
static int dissect_ProtocolIEFieldPairFirstValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  return (dissector_try_uint(s1ap_ies_p1_dissector_table, s1ap_data->protocol_ie_id, tvb, pinfo, tree)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_ProtocolIEFieldPairSecondValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  return (dissector_try_uint(s1ap_ies_p2_dissector_table, s1ap_data->protocol_ie_id, tvb, pinfo, tree)) ? tvb_captured_length(tvb) : 0;
}
*/

static int dissect_ProtocolExtensionFieldExtensionValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  s1ap_ctx_t s1ap_ctx;
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  s1ap_ctx.message_type        = s1ap_data->message_type;
  s1ap_ctx.ProcedureCode       = s1ap_data->procedure_code;
  s1ap_ctx.ProtocolIE_ID       = s1ap_data->protocol_ie_id;
  s1ap_ctx.ProtocolExtensionID = s1ap_data->protocol_extension_id;

  return (dissector_try_uint_new(s1ap_extension_dissector_table, s1ap_data->protocol_extension_id, tvb, pinfo, tree, FALSE, &s1ap_ctx)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_InitiatingMessageValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  return (dissector_try_uint_new(s1ap_proc_imsg_dissector_table, s1ap_data->procedure_code, tvb, pinfo, tree, FALSE, data)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_SuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  return (dissector_try_uint_new(s1ap_proc_sout_dissector_table, s1ap_data->procedure_code, tvb, pinfo, tree, FALSE, data)) ? tvb_captured_length(tvb) : 0;
}

static int dissect_UnsuccessfulOutcomeValue(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data)
{
  struct s1ap_private_data *s1ap_data = s1ap_get_private_data(pinfo);

  return (dissector_try_uint_new(s1ap_proc_uout_dissector_table, s1ap_data->procedure_code, tvb, pinfo, tree, FALSE, data)) ? tvb_captured_length(tvb) : 0;
}


static int
dissect_s1ap(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void* data _U_)
{
  proto_item *s1ap_item = NULL;
  proto_tree *s1ap_tree = NULL;
  conversation_t *conversation;
  struct s1ap_private_data* s1ap_data;
  wmem_list_frame_t *prev_layer;

  /* make entry in the Protocol column on summary display */
  col_set_str(pinfo->cinfo, COL_PROTOCOL, "S1AP");
  /* ensure that parent dissector is not S1AP before clearing fence */
  prev_layer = wmem_list_frame_prev(wmem_list_tail(pinfo->layers));
  if (prev_layer && GPOINTER_TO_INT(wmem_list_frame_data(prev_layer)) != proto_s1ap)
    col_clear_fence(pinfo->cinfo, COL_INFO);
  col_clear(pinfo->cinfo, COL_INFO);

  /* create the s1ap protocol tree */
  s1ap_item = proto_tree_add_item(tree, proto_s1ap, tvb, 0, -1, ENC_NA);
  s1ap_tree = proto_item_add_subtree(s1ap_item, ett_s1ap);

  s1ap_data = s1ap_get_private_data(pinfo);
  conversation = find_or_create_conversation(pinfo);
  s1ap_data->s1ap_conv = (struct s1ap_conv_info *)conversation_get_proto_data(conversation, proto_s1ap);
  if (!s1ap_data->s1ap_conv) {
    s1ap_data->s1ap_conv = wmem_new(wmem_file_scope(), struct s1ap_conv_info);
    s1ap_data->s1ap_conv->nbiot_ta = wmem_map_new(wmem_file_scope(), wmem_int64_hash, g_int64_equal);
    s1ap_data->s1ap_conv->nbiot_enb_ue_s1ap_id = wmem_tree_new(wmem_file_scope());
    conversation_add_proto_data(conversation, proto_s1ap, s1ap_data->s1ap_conv);
  }

  dissect_S1AP_PDU_PDU(tvb, pinfo, s1ap_tree, NULL);
  return tvb_captured_length(tvb);
}

/*--- proto_reg_handoff_s1ap ---------------------------------------*/
void
proto_reg_handoff_s1ap(void)
{
  static gboolean Initialized=FALSE;
  static guint SctpPort;

  if (!Initialized) {
    gcsna_handle = find_dissector_add_dependency("gcsna", proto_s1ap);
    nas_eps_handle = find_dissector_add_dependency("nas-eps", proto_s1ap);
    lppa_handle = find_dissector_add_dependency("lppa", proto_s1ap);
    bssgp_handle = find_dissector_add_dependency("bssgp", proto_s1ap);
    lte_rrc_ue_radio_access_cap_info_handle = find_dissector_add_dependency("lte-rrc.ue_radio_access_cap_info", proto_s1ap);
    lte_rrc_ue_radio_access_cap_info_nb_handle = find_dissector_add_dependency("lte-rrc.ue_radio_access_cap_info.nb", proto_s1ap);
    nr_rrc_ue_radio_access_cap_info_handle = find_dissector_add_dependency("nr-rrc.ue_radio_access_cap_info", proto_s1ap);
    lte_rrc_ue_radio_paging_info_handle = find_dissector_add_dependency("lte-rrc.ue_radio_paging_info", proto_s1ap);
    lte_rrc_ue_radio_paging_info_nb_handle = find_dissector_add_dependency("lte-rrc.ue_radio_paging_info.nb", proto_s1ap);
    dissector_add_for_decode_as("sctp.port", s1ap_handle);
    dissector_add_uint("sctp.ppi", S1AP_PAYLOAD_PROTOCOL_ID, s1ap_handle);
    Initialized=TRUE;

/*--- Included file: packet-s1ap-dis-tab.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-dis-tab.c"
  dissector_add_uint("s1ap.ies", id_MME_UE_S1AP_ID, create_dissector_handle(dissect_MME_UE_S1AP_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_HandoverType, create_dissector_handle(dissect_HandoverType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Cause, create_dissector_handle(dissect_Cause_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TargetID, create_dissector_handle(dissect_TargetID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_eNB_UE_S1AP_ID, create_dissector_handle(dissect_ENB_UE_S1AP_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABSubjecttoDataForwardingList, create_dissector_handle(dissect_E_RABSubjecttoDataForwardingList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABtoReleaseListHOCmd, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABDataForwardingItem, create_dissector_handle(dissect_E_RABDataForwardingItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABReleaseItemBearerRelComp, create_dissector_handle(dissect_E_RABReleaseItemBearerRelComp_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupListBearerSUReq, create_dissector_handle(dissect_E_RABToBeSetupListBearerSUReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupItemBearerSUReq, create_dissector_handle(dissect_E_RABToBeSetupItemBearerSUReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABAdmittedList, create_dissector_handle(dissect_E_RABAdmittedList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToSetupListHOReqAck, create_dissector_handle(dissect_E_RABFailedtoSetupListHOReqAck_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABAdmittedItem, create_dissector_handle(dissect_E_RABAdmittedItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedtoSetupItemHOReqAck, create_dissector_handle(dissect_E_RABFailedToSetupItemHOReqAck_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSwitchedDLList, create_dissector_handle(dissect_E_RABToBeSwitchedDLList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSwitchedDLItem, create_dissector_handle(dissect_E_RABToBeSwitchedDLItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupListCtxtSUReq, create_dissector_handle(dissect_E_RABToBeSetupListCtxtSUReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TraceActivation, create_dissector_handle(dissect_TraceActivation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_UTRAN_Trace_ID, create_dissector_handle(dissect_E_UTRAN_Trace_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NAS_PDU, create_dissector_handle(dissect_NAS_PDU_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupItemHOReq, create_dissector_handle(dissect_E_RABToBeSetupItemHOReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABSetupListBearerSURes, create_dissector_handle(dissect_E_RABSetupListBearerSURes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToSetupListBearerSURes, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeModifiedListBearerModReq, create_dissector_handle(dissect_E_RABToBeModifiedListBearerModReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABModifyListBearerModRes, create_dissector_handle(dissect_E_RABModifyListBearerModRes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToModifyList, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeReleasedList, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToReleaseList, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABItem, create_dissector_handle(dissect_E_RABItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeModifiedItemBearerModReq, create_dissector_handle(dissect_E_RABToBeModifiedItemBearerModReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABModifyItemBearerModRes, create_dissector_handle(dissect_E_RABModifyItemBearerModRes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABSetupItemBearerSURes, create_dissector_handle(dissect_E_RABSetupItemBearerSURes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SecurityContext, create_dissector_handle(dissect_SecurityContext_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_HandoverRestrictionList, create_dissector_handle(dissect_s1ap_HandoverRestrictionList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UEPagingID, create_dissector_handle(dissect_UEPagingID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_pagingDRX, create_dissector_handle(dissect_PagingDRX_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TAIList, create_dissector_handle(dissect_TAIList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TAIItem, create_dissector_handle(dissect_TAIItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToSetupListCtxtSURes, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABSetupItemCtxtSURes, create_dissector_handle(dissect_E_RABSetupItemCtxtSURes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABSetupListCtxtSURes, create_dissector_handle(dissect_E_RABSetupListCtxtSURes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupItemCtxtSUReq, create_dissector_handle(dissect_E_RABToBeSetupItemCtxtSUReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSetupListHOReq, create_dissector_handle(dissect_E_RABToBeSetupListHOReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CriticalityDiagnostics, create_dissector_handle(dissect_CriticalityDiagnostics_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Global_ENB_ID, create_dissector_handle(dissect_s1ap_Global_ENB_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_eNBname, create_dissector_handle(dissect_ENBname_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MMEname, create_dissector_handle(dissect_MMEname_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ServedPLMNs, create_dissector_handle(dissect_ServedPLMNs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SupportedTAs, create_dissector_handle(dissect_SupportedTAs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TimeToWait, create_dissector_handle(dissect_TimeToWait_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_uEaggregateMaximumBitrate, create_dissector_handle(dissect_UEAggregateMaximumBitrate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TAI, create_dissector_handle(dissect_TAI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABReleaseListBearerRelComp, create_dissector_handle(dissect_E_RABReleaseListBearerRelComp_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000PDU, create_dissector_handle(dissect_Cdma2000PDU_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000RATType, create_dissector_handle(dissect_Cdma2000RATType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000SectorID, create_dissector_handle(dissect_Cdma2000SectorID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SecurityKey, create_dissector_handle(dissect_SecurityKey_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UERadioCapability, create_dissector_handle(dissect_UERadioCapability_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_GUMMEI_ID, create_dissector_handle(dissect_GUMMEI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABInformationListItem, create_dissector_handle(dissect_E_RABInformationListItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Direct_Forwarding_Path_Availability, create_dissector_handle(dissect_Direct_Forwarding_Path_Availability_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UEIdentityIndexValue, create_dissector_handle(dissect_UEIdentityIndexValue_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000HOStatus, create_dissector_handle(dissect_Cdma2000HOStatus_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000HORequiredIndication, create_dissector_handle(dissect_Cdma2000HORequiredIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RelativeMMECapacity, create_dissector_handle(dissect_RelativeMMECapacity_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SourceMME_UE_S1AP_ID, create_dissector_handle(dissect_MME_UE_S1AP_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Bearers_SubjectToStatusTransfer_Item, create_dissector_handle(dissect_Bearers_SubjectToStatusTransfer_Item_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_eNB_StatusTransfer_TransparentContainer, create_dissector_handle(dissect_s1ap_ENB_StatusTransfer_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_associatedLogicalS1_ConnectionItem, create_dissector_handle(dissect_UE_associatedLogicalS1_ConnectionItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ResetType, create_dissector_handle(dissect_ResetType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_associatedLogicalS1_ConnectionListResAck, create_dissector_handle(dissect_UE_associatedLogicalS1_ConnectionListResAck_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSwitchedULItem, create_dissector_handle(dissect_E_RABToBeSwitchedULItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeSwitchedULList, create_dissector_handle(dissect_E_RABToBeSwitchedULList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_S_TMSI, create_dissector_handle(dissect_S_TMSI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000OneXRAND, create_dissector_handle(dissect_Cdma2000OneXRAND_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RequestType, create_dissector_handle(dissect_RequestType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_S1AP_IDs, create_dissector_handle(dissect_UE_S1AP_IDs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EUTRAN_CGI, create_dissector_handle(dissect_s1ap_EUTRAN_CGI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_OverloadResponse, create_dissector_handle(dissect_OverloadResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_cdma2000OneXSRVCCInfo, create_dissector_handle(dissect_Cdma2000OneXSRVCCInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Source_ToTarget_TransparentContainer, create_dissector_handle(dissect_Source_ToTarget_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ServedGUMMEIs, create_dissector_handle(dissect_ServedGUMMEIs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SubscriberProfileIDforRFP, create_dissector_handle(dissect_SubscriberProfileIDforRFP_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UESecurityCapabilities, create_dissector_handle(dissect_UESecurityCapabilities_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CSFallbackIndicator, create_dissector_handle(dissect_CSFallbackIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CNDomain, create_dissector_handle(dissect_CNDomain_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABReleasedList, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MessageIdentifier, create_dissector_handle(dissect_MessageIdentifier_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SerialNumber, create_dissector_handle(dissect_SerialNumber_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WarningAreaList, create_dissector_handle(dissect_WarningAreaList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RepetitionPeriod, create_dissector_handle(dissect_RepetitionPeriod_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NumberofBroadcastRequest, create_dissector_handle(dissect_NumberofBroadcastRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WarningType, create_dissector_handle(dissect_WarningType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WarningSecurityInfo, create_dissector_handle(dissect_WarningSecurityInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DataCodingScheme, create_dissector_handle(dissect_DataCodingScheme_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WarningMessageContents, create_dissector_handle(dissect_WarningMessageContents_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_BroadcastCompletedAreaList, create_dissector_handle(dissect_BroadcastCompletedAreaList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Inter_SystemInformationTransferTypeEDT, create_dissector_handle(dissect_Inter_SystemInformationTransferType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Inter_SystemInformationTransferTypeMDT, create_dissector_handle(dissect_Inter_SystemInformationTransferType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Target_ToSource_TransparentContainer, create_dissector_handle(dissect_Target_ToSource_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SRVCCOperationPossible, create_dissector_handle(dissect_SRVCCOperationPossible_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SRVCCHOIndication, create_dissector_handle(dissect_SRVCCHOIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CSG_Id, create_dissector_handle(dissect_CSG_Id_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CSG_IdList, create_dissector_handle(dissect_CSG_IdList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SONConfigurationTransferECT, create_dissector_handle(dissect_s1ap_SONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SONConfigurationTransferMCT, create_dissector_handle(dissect_s1ap_SONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TraceCollectionEntityIPAddress, create_dissector_handle(dissect_TransportLayerAddress_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MSClassmark2, create_dissector_handle(dissect_MSClassmark2_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MSClassmark3, create_dissector_handle(dissect_MSClassmark3_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RRC_Establishment_Cause, create_dissector_handle(dissect_RRC_Establishment_Cause_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NASSecurityParametersfromE_UTRAN, create_dissector_handle(dissect_NASSecurityParametersfromE_UTRAN_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NASSecurityParameterstoE_UTRAN, create_dissector_handle(dissect_NASSecurityParameterstoE_UTRAN_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DefaultPagingDRX, create_dissector_handle(dissect_PagingDRX_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Source_ToTarget_TransparentContainer_Secondary, create_dissector_handle(dissect_Source_ToTarget_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Target_ToSource_TransparentContainer_Secondary, create_dissector_handle(dissect_Target_ToSource_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EUTRANRoundTripDelayEstimationInfo, create_dissector_handle(dissect_EUTRANRoundTripDelayEstimationInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_BroadcastCancelledAreaList, create_dissector_handle(dissect_BroadcastCancelledAreaList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ConcurrentWarningMessageIndicator, create_dissector_handle(dissect_ConcurrentWarningMessageIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ExtendedRepetitionPeriod, create_dissector_handle(dissect_ExtendedRepetitionPeriod_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CellAccessMode, create_dissector_handle(dissect_CellAccessMode_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CSGMembershipStatus, create_dissector_handle(dissect_CSGMembershipStatus_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_LPPa_PDU, create_dissector_handle(dissect_LPPa_PDU_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Routing_ID, create_dissector_handle(dissect_Routing_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PS_ServiceNotAvailable, create_dissector_handle(dissect_PS_ServiceNotAvailable_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PagingPriority, create_dissector_handle(dissect_PagingPriority_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_GUMMEIList, create_dissector_handle(dissect_GUMMEIList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_GW_TransportLayerAddress, create_dissector_handle(dissect_TransportLayerAddress_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SourceMME_GUMMEI, create_dissector_handle(dissect_GUMMEI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MME_UE_S1AP_ID_2, create_dissector_handle(dissect_MME_UE_S1AP_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RegisteredLAI, create_dissector_handle(dissect_LAI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RelayNode_Indicator, create_dissector_handle(dissect_RelayNode_Indicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TrafficLoadReductionIndication, create_dissector_handle(dissect_TrafficLoadReductionIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MMERelaySupportIndicator, create_dissector_handle(dissect_MMERelaySupportIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_GWContextReleaseIndication, create_dissector_handle(dissect_GWContextReleaseIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ManagementBasedMDTAllowed, create_dissector_handle(dissect_ManagementBasedMDTAllowed_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PrivacyIndicator, create_dissector_handle(dissect_PrivacyIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_VoiceSupportMatchIndicator, create_dissector_handle(dissect_VoiceSupportMatchIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_GUMMEIType, create_dissector_handle(dissect_GUMMEIType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Tunnel_Information_for_BBF, create_dissector_handle(dissect_TunnelInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ManagementBasedMDTPLMNList, create_dissector_handle(dissect_MDTPLMNList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ECGIListForRestart, create_dissector_handle(dissect_ECGIListForRestart_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SIPTO_L_GW_TransportLayerAddress, create_dissector_handle(dissect_TransportLayerAddress_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_LHN_ID, create_dissector_handle(dissect_LHN_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_AdditionalCSFallbackIndicator, create_dissector_handle(dissect_AdditionalCSFallbackIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TAIListForRestart, create_dissector_handle(dissect_TAIListForRestart_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UserLocationInformation, create_dissector_handle(dissect_UserLocationInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_KillAllWarningMessages, create_dissector_handle(dissect_KillAllWarningMessages_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Masked_IMEISV, create_dissector_handle(dissect_Masked_IMEISV_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ProSeAuthorized, create_dissector_handle(dissect_ProSeAuthorized_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ExpectedUEBehaviour, create_dissector_handle(dissect_ExpectedUEBehaviour_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UERadioCapabilityForPaging, create_dissector_handle(dissect_UERadioCapabilityForPaging_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeModifiedListBearerModInd, create_dissector_handle(dissect_E_RABToBeModifiedListBearerModInd_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeModifiedItemBearerModInd, create_dissector_handle(dissect_E_RABToBeModifiedItemBearerModInd_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABNotToBeModifiedListBearerModInd, create_dissector_handle(dissect_E_RABNotToBeModifiedListBearerModInd_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABNotToBeModifiedItemBearerModInd, create_dissector_handle(dissect_E_RABNotToBeModifiedItemBearerModInd_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABModifyListBearerModConf, create_dissector_handle(dissect_E_RABModifyListBearerModConf_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABModifyItemBearerModConf, create_dissector_handle(dissect_E_RABModifyItemBearerModConf_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToModifyListBearerModConf, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SON_Information_Report, create_dissector_handle(dissect_SONInformationReport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABToBeReleasedListBearerModConf, create_dissector_handle(dissect_E_RABList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_AssistanceDataForPaging, create_dissector_handle(dissect_AssistanceDataForPaging_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CellIdentifierAndCELevelForCECapableUEs, create_dissector_handle(dissect_CellIdentifierAndCELevelForCECapableUEs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_InformationOnRecommendedCellsAndENBsForPaging, create_dissector_handle(dissect_InformationOnRecommendedCellsAndENBsForPaging_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RecommendedCellItem, create_dissector_handle(dissect_RecommendedCellItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RecommendedENBItem, create_dissector_handle(dissect_RecommendedENBItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PWSfailedECGIList, create_dissector_handle(dissect_PWSfailedECGIList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_MME_Group_ID, create_dissector_handle(dissect_MME_Group_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Additional_GUTI, create_dissector_handle(dissect_Additional_GUTI_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_S1_Message, create_dissector_handle(dissect_S1_Message_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CSGMembershipInfo, create_dissector_handle(dissect_CSGMembershipInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Paging_eDRXInformation, create_dissector_handle(dissect_Paging_eDRXInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_RetentionInformation, create_dissector_handle(dissect_UE_RetentionInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_Usage_Type, create_dissector_handle(dissect_UE_Usage_Type_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_extended_UEIdentityIndexValue, create_dissector_handle(dissect_Extended_UEIdentityIndexValue_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NB_IoT_DefaultPagingDRX, create_dissector_handle(dissect_NB_IoT_DefaultPagingDRX_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToResumeListResumeReq, create_dissector_handle(dissect_E_RABFailedToResumeListResumeReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToResumeItemResumeReq, create_dissector_handle(dissect_E_RABFailedToResumeItemResumeReq_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToResumeListResumeRes, create_dissector_handle(dissect_E_RABFailedToResumeListResumeRes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABFailedToResumeItemResumeRes, create_dissector_handle(dissect_E_RABFailedToResumeItemResumeRes_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NB_IoT_Paging_eDRXInformation, create_dissector_handle(dissect_NB_IoT_Paging_eDRXInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UEUserPlaneCIoTSupportIndicator, create_dissector_handle(dissect_UEUserPlaneCIoTSupportIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CE_mode_B_SupportIndicator, create_dissector_handle(dissect_CE_mode_B_SupportIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SRVCCOperationNotPossible, create_dissector_handle(dissect_SRVCCOperationNotPossible_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NB_IoT_UEIdentityIndexValue, create_dissector_handle(dissect_NB_IoT_UEIdentityIndexValue_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_RRC_Resume_Cause, create_dissector_handle(dissect_RRC_Establishment_Cause_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_V2XServicesAuthorized, create_dissector_handle(dissect_V2XServicesAuthorized_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UESidelinkAggregateMaximumBitrate, create_dissector_handle(dissect_UESidelinkAggregateMaximumBitrate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EnhancedCoverageRestricted, create_dissector_handle(dissect_EnhancedCoverageRestricted_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DLNASPDUDeliveryAckRequest, create_dissector_handle(dissect_DLNASPDUDeliveryAckRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DCN_ID, create_dissector_handle(dissect_DCN_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Coverage_Level, create_dissector_handle(dissect_Coverage_Level_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ServedDCNs, create_dissector_handle(dissect_ServedDCNs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DL_CP_SecurityInformation, create_dissector_handle(dissect_DL_CP_SecurityInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_Level_QoS_Parameters, create_dissector_handle(dissect_E_RABLevelQoSParameters_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UL_CP_SecurityInformation, create_dissector_handle(dissect_UL_CP_SecurityInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_E_RABUsageReportItem, create_dissector_handle(dissect_E_RABUsageReportItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SecondaryRATDataUsageReportItem, create_dissector_handle(dissect_SecondaryRATDataUsageReportItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NRUESecurityCapabilities, create_dissector_handle(dissect_NRUESecurityCapabilities_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SecondaryRATDataUsageRequest, create_dissector_handle(dissect_SecondaryRATDataUsageRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_SecondaryRATDataUsageReportList, create_dissector_handle(dissect_SecondaryRATDataUsageReportList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UE_Application_Layer_Measurement_Capability, create_dissector_handle(dissect_UE_Application_Layer_Measurement_Capability_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_HandoverFlag, create_dissector_handle(dissect_HandoverFlag_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EmergencyAreaIDListForRestart, create_dissector_handle(dissect_EmergencyAreaIDListForRestart_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_CE_ModeBRestricted, create_dissector_handle(dissect_CE_ModeBRestricted_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_AerialUEsubscriptionInformation, create_dissector_handle(dissect_AerialUEsubscriptionInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UECapabilityInfoRequest, create_dissector_handle(dissect_UECapabilityInfoRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EndIndication, create_dissector_handle(dissect_EndIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EDT_Session, create_dissector_handle(dissect_EDT_Session_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_LTE_M_Indication, create_dissector_handle(dissect_LTE_M_Indication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Subscription_Based_UE_DifferentiationInfo, create_dissector_handle(dissect_Subscription_Based_UE_DifferentiationInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PendingDataIndication, create_dissector_handle(dissect_PendingDataIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WarningAreaCoordinates, create_dissector_handle(dissect_WarningAreaCoordinates_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PSCellInformation, create_dissector_handle(dissect_PSCellInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ConnectedengNBList, create_dissector_handle(dissect_ConnectedengNBList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ConnectedengNBToAddList, create_dissector_handle(dissect_ConnectedengNBList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_ConnectedengNBToRemoveList, create_dissector_handle(dissect_ConnectedengNBList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EN_DCSONConfigurationTransfer_ECT, create_dissector_handle(dissect_s1ap_EN_DCSONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_EN_DCSONConfigurationTransfer_MCT, create_dissector_handle(dissect_s1ap_EN_DCSONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_TimeSinceSecondaryNodeRelease, create_dissector_handle(dissect_TimeSinceSecondaryNodeRelease_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_AdditionalRRMPriorityIndex, create_dissector_handle(dissect_AdditionalRRMPriorityIndex_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_IAB_Authorized, create_dissector_handle(dissect_IAB_Authorized_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_IAB_Node_Indication, create_dissector_handle(dissect_IAB_Node_Indication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_IAB_Supported, create_dissector_handle(dissect_IAB_Supported_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DataSize, create_dissector_handle(dissect_DataSize_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NRV2XServicesAuthorized, create_dissector_handle(dissect_NRV2XServicesAuthorized_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NRUESidelinkAggregateMaximumBitrate, create_dissector_handle(dissect_NRUESidelinkAggregateMaximumBitrate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_PC5QoSParameters, create_dissector_handle(dissect_PC5QoSParameters_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_IntersystemSONConfigurationTransferMCT, create_dissector_handle(dissect_IntersystemSONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_IntersystemSONConfigurationTransferECT, create_dissector_handle(dissect_IntersystemSONConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UERadioCapabilityID, create_dissector_handle(dissect_UERadioCapabilityID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_UERadioCapability_NR_Format, create_dissector_handle(dissect_UERadioCapability_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_DAPSResponseInfoItem, create_dissector_handle(dissect_DAPSResponseInfoItem_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NotifySourceeNB, create_dissector_handle(dissect_NotifySourceeNB_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_eNB_EarlyStatusTransfer_TransparentContainer, create_dissector_handle(dissect_ENB_EarlyStatusTransfer_TransparentContainer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_Bearers_SubjectToEarlyStatusTransfer_Item, create_dissector_handle(dissect_Bearers_SubjectToEarlyStatusTransfer_Item_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_WUS_Assistance_Information, create_dissector_handle(dissect_WUS_Assistance_Information_PDU, proto_s1ap));
  dissector_add_uint("s1ap.ies", id_NB_IoT_PagingDRX, create_dissector_handle(dissect_NB_IoT_PagingDRX_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Data_Forwarding_Not_Possible, create_dissector_handle(dissect_Data_Forwarding_Not_Possible_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Time_Synchronisation_Info, create_dissector_handle(dissect_TimeSynchronisationInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_x2TNLConfigurationInfo, create_dissector_handle(dissect_X2TNLConfigurationInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_eNBX2ExtendedTransportLayerAddresses, create_dissector_handle(dissect_ENBX2ExtTLAs_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Correlation_ID, create_dissector_handle(dissect_Correlation_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_MDTConfiguration, create_dissector_handle(dissect_MDT_Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Time_UE_StayedInCell_EnhancedGranularity, create_dissector_handle(dissect_Time_UE_StayedInCell_EnhancedGranularity_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_HO_Cause, create_dissector_handle(dissect_Cause_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_M3Configuration, create_dissector_handle(dissect_M3Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_M4Configuration, create_dissector_handle(dissect_M4Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_M5Configuration, create_dissector_handle(dissect_M5Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_MDT_Location_Info, create_dissector_handle(dissect_MDT_Location_Info_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_MobilityInformation, create_dissector_handle(dissect_MobilityInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_SignallingBasedMDTPLMNList, create_dissector_handle(dissect_MDTPLMNList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ULCOUNTValueExtended, create_dissector_handle(dissect_COUNTValueExtended_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_DLCOUNTValueExtended, create_dissector_handle(dissect_COUNTValueExtended_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ReceiveStatusOfULPDCPSDUsExtended, create_dissector_handle(dissect_ReceiveStatusOfULPDCPSDUsExtended_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_SIPTO_Correlation_ID, create_dissector_handle(dissect_Correlation_ID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_TransportInformation, create_dissector_handle(dissect_TransportInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_eNBIndirectX2TransportLayerAddresses, create_dissector_handle(dissect_ENBIndirectX2TransportLayerAddresses_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_LoggedMBSFNMDT, create_dissector_handle(dissect_LoggedMBSFNMDT_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_uE_HistoryInformationFromTheUE, create_dissector_handle(dissect_UE_HistoryInformationFromTheUE_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Muting_Availability_Indication, create_dissector_handle(dissect_MutingAvailabilityIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Muting_Pattern_Information, create_dissector_handle(dissect_MutingPatternInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Synchronisation_Information, create_dissector_handle(dissect_SynchronisationInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ProSeUEtoNetworkRelaying, create_dissector_handle(dissect_ProSeUEtoNetworkRelaying_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ULCOUNTValuePDCP_SNlength18, create_dissector_handle(dissect_COUNTvaluePDCP_SNlength18_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_DLCOUNTValuePDCP_SNlength18, create_dissector_handle(dissect_COUNTvaluePDCP_SNlength18_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18, create_dissector_handle(dissect_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_M6Configuration, create_dissector_handle(dissect_M6Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_M7Configuration, create_dissector_handle(dissect_M7Configuration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_RAT_Type, create_dissector_handle(dissect_RAT_Type_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_BearerType, create_dissector_handle(dissect_BearerType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_e_RAB_MaximumBitrateDL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_e_RAB_MaximumBitrateUL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_e_RAB_GuaranteedBitrateDL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_e_RAB_GuaranteedBitrateUL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_NRrestrictioninEPSasSecondaryRAT, create_dissector_handle(dissect_NRrestrictioninEPSasSecondaryRAT_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_UEAppLayerMeasConfig, create_dissector_handle(dissect_UEAppLayerMeasConfig_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_uEaggregateMaximumBitRateDL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_extended_uEaggregateMaximumBitRateUL, create_dissector_handle(dissect_ExtendedBitRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_UnlicensedSpectrumRestriction, create_dissector_handle(dissect_UnlicensedSpectrumRestriction_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_CNTypeRestrictions, create_dissector_handle(dissect_CNTypeRestrictions_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_DownlinkPacketLossRate, create_dissector_handle(dissect_Packet_LossRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_UplinkPacketLossRate, create_dissector_handle(dissect_Packet_LossRate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_serviceType, create_dissector_handle(dissect_ServiceType_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_BluetoothMeasurementConfiguration, create_dissector_handle(dissect_BluetoothMeasurementConfiguration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_WLANMeasurementConfiguration, create_dissector_handle(dissect_WLANMeasurementConfiguration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_NRrestrictionin5GS, create_dissector_handle(dissect_NRrestrictionin5GS_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_LastNG_RANPLMNIdentity, create_dissector_handle(dissect_PLMNidentity_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_PSCellInformation, create_dissector_handle(dissect_PSCellInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_IMSvoiceEPSfallbackfrom5G, create_dissector_handle(dissect_IMSvoiceEPSfallbackfrom5G_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_TimeSinceSecondaryNodeRelease, create_dissector_handle(dissect_RequestTypeAdditionalInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_ContextatSource, create_dissector_handle(dissect_ContextatSource_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_Ethernet_Type, create_dissector_handle(dissect_Ethernet_Type_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_IntersystemMeasurementConfiguration, create_dissector_handle(dissect_IntersystemMeasurementConfiguration_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_SourceNodeID, create_dissector_handle(dissect_SourceNodeID_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_NB_IoT_RLF_Report_Container, create_dissector_handle(dissect_NB_IoT_RLF_Report_Container_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_MDTConfigurationNR, create_dissector_handle(dissect_MDT_ConfigurationNR_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_DAPSRequestInfo, create_dissector_handle(dissect_DAPSRequestInfo_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_DAPSResponseInfoList, create_dissector_handle(dissect_DAPSResponseInfoList_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_TraceCollectionEntityURI, create_dissector_handle(dissect_URI_Address_PDU, proto_s1ap));
  dissector_add_uint("s1ap.extension", id_EmergencyIndicator, create_dissector_handle(dissect_EmergencyIndicator_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_HandoverPreparation, create_dissector_handle(dissect_HandoverRequired_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_HandoverPreparation, create_dissector_handle(dissect_HandoverCommand_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_HandoverPreparation, create_dissector_handle(dissect_HandoverPreparationFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_HandoverResourceAllocation, create_dissector_handle(dissect_HandoverRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_HandoverResourceAllocation, create_dissector_handle(dissect_HandoverRequestAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_HandoverResourceAllocation, create_dissector_handle(dissect_HandoverFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_HandoverNotification, create_dissector_handle(dissect_HandoverNotify_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_PathSwitchRequest, create_dissector_handle(dissect_PathSwitchRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_PathSwitchRequest, create_dissector_handle(dissect_PathSwitchRequestAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_PathSwitchRequest, create_dissector_handle(dissect_PathSwitchRequestFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_E_RABSetup, create_dissector_handle(dissect_E_RABSetupRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_E_RABSetup, create_dissector_handle(dissect_E_RABSetupResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_E_RABModify, create_dissector_handle(dissect_E_RABModifyRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_E_RABModify, create_dissector_handle(dissect_E_RABModifyResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_E_RABRelease, create_dissector_handle(dissect_E_RABReleaseCommand_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_E_RABRelease, create_dissector_handle(dissect_E_RABReleaseResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_E_RABReleaseIndication, create_dissector_handle(dissect_E_RABReleaseIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_InitialContextSetup, create_dissector_handle(dissect_InitialContextSetupRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_InitialContextSetup, create_dissector_handle(dissect_InitialContextSetupResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_InitialContextSetup, create_dissector_handle(dissect_InitialContextSetupFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextReleaseRequest, create_dissector_handle(dissect_UEContextReleaseRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_Paging, create_dissector_handle(dissect_Paging_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_downlinkNASTransport, create_dissector_handle(dissect_DownlinkNASTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_initialUEMessage, create_dissector_handle(dissect_InitialUEMessage_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_uplinkNASTransport, create_dissector_handle(dissect_UplinkNASTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_NASNonDeliveryIndication, create_dissector_handle(dissect_NASNonDeliveryIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_HandoverCancel, create_dissector_handle(dissect_HandoverCancel_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_HandoverCancel, create_dissector_handle(dissect_HandoverCancelAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_Reset, create_dissector_handle(dissect_Reset_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_Reset, create_dissector_handle(dissect_ResetAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_ErrorIndication, create_dissector_handle(dissect_ErrorIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_S1Setup, create_dissector_handle(dissect_S1SetupRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_S1Setup, create_dissector_handle(dissect_S1SetupResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_S1Setup, create_dissector_handle(dissect_S1SetupFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_DownlinkS1cdma2000tunnelling, create_dissector_handle(dissect_DownlinkS1cdma2000tunnelling_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_ENBConfigurationUpdate, create_dissector_handle(dissect_ENBConfigurationUpdate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_ENBConfigurationUpdate, create_dissector_handle(dissect_ENBConfigurationUpdateAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_ENBConfigurationUpdate, create_dissector_handle(dissect_ENBConfigurationUpdateFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMEConfigurationUpdate, create_dissector_handle(dissect_MMEConfigurationUpdate_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_MMEConfigurationUpdate, create_dissector_handle(dissect_MMEConfigurationUpdateAcknowledge_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_MMEConfigurationUpdate, create_dissector_handle(dissect_MMEConfigurationUpdateFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UplinkS1cdma2000tunnelling, create_dissector_handle(dissect_UplinkS1cdma2000tunnelling_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextModification, create_dissector_handle(dissect_UEContextModificationRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UEContextModification, create_dissector_handle(dissect_UEContextModificationResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_UEContextModification, create_dissector_handle(dissect_UEContextModificationFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UECapabilityInfoIndication, create_dissector_handle(dissect_UECapabilityInfoIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextRelease, create_dissector_handle(dissect_UEContextReleaseCommand_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UEContextRelease, create_dissector_handle(dissect_UEContextReleaseComplete_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_eNBStatusTransfer, create_dissector_handle(dissect_ENBStatusTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMEStatusTransfer, create_dissector_handle(dissect_MMEStatusTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_DeactivateTrace, create_dissector_handle(dissect_DeactivateTrace_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_TraceStart, create_dissector_handle(dissect_TraceStart_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_TraceFailureIndication, create_dissector_handle(dissect_TraceFailureIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_LocationReportingControl, create_dissector_handle(dissect_LocationReportingControl_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_LocationReportingFailureIndication, create_dissector_handle(dissect_LocationReportingFailureIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_LocationReport, create_dissector_handle(dissect_LocationReport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_OverloadStart, create_dissector_handle(dissect_OverloadStart_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_OverloadStop, create_dissector_handle(dissect_OverloadStop_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_WriteReplaceWarning, create_dissector_handle(dissect_WriteReplaceWarningRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_WriteReplaceWarning, create_dissector_handle(dissect_WriteReplaceWarningResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_eNBDirectInformationTransfer, create_dissector_handle(dissect_ENBDirectInformationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMEDirectInformationTransfer, create_dissector_handle(dissect_MMEDirectInformationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_eNBConfigurationTransfer, create_dissector_handle(dissect_ENBConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMEConfigurationTransfer, create_dissector_handle(dissect_MMEConfigurationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_CellTrafficTrace, create_dissector_handle(dissect_CellTrafficTrace_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_PrivateMessage, create_dissector_handle(dissect_PrivateMessage_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_PWSRestartIndication, create_dissector_handle(dissect_PWSRestartIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_Kill, create_dissector_handle(dissect_KillRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_Kill, create_dissector_handle(dissect_KillResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_downlinkUEAssociatedLPPaTransport, create_dissector_handle(dissect_DownlinkUEAssociatedLPPaTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_uplinkUEAssociatedLPPaTransport, create_dissector_handle(dissect_UplinkUEAssociatedLPPaTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_downlinkNonUEAssociatedLPPaTransport, create_dissector_handle(dissect_DownlinkNonUEAssociatedLPPaTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_uplinkNonUEAssociatedLPPaTransport, create_dissector_handle(dissect_UplinkNonUEAssociatedLPPaTransport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UERadioCapabilityMatch, create_dissector_handle(dissect_UERadioCapabilityMatchRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UERadioCapabilityMatch, create_dissector_handle(dissect_UERadioCapabilityMatchResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_E_RABModificationIndication, create_dissector_handle(dissect_E_RABModificationIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_E_RABModificationIndication, create_dissector_handle(dissect_E_RABModificationConfirm_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextModificationIndication, create_dissector_handle(dissect_UEContextModificationIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UEContextModificationIndication, create_dissector_handle(dissect_UEContextModificationConfirm_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_RerouteNASRequest, create_dissector_handle(dissect_RerouteNASRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_PWSFailureIndication, create_dissector_handle(dissect_PWSFailureIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_ConnectionEstablishmentIndication, create_dissector_handle(dissect_ConnectionEstablishmentIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextSuspend, create_dissector_handle(dissect_UEContextSuspendRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UEContextSuspend, create_dissector_handle(dissect_UEContextSuspendResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEContextResume, create_dissector_handle(dissect_UEContextResumeRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UEContextResume, create_dissector_handle(dissect_UEContextResumeResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.uout", id_UEContextResume, create_dissector_handle(dissect_UEContextResumeFailure_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_NASDeliveryIndication, create_dissector_handle(dissect_NASDeliveryIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_RetrieveUEInformation, create_dissector_handle(dissect_RetrieveUEInformation_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UEInformationTransfer, create_dissector_handle(dissect_UEInformationTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_eNBCPRelocationIndication, create_dissector_handle(dissect_ENBCPRelocationIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMECPRelocationIndication, create_dissector_handle(dissect_MMECPRelocationIndication_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_SecondaryRATDataUsageReport, create_dissector_handle(dissect_SecondaryRATDataUsageReport_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_UERadioCapabilityIDMapping, create_dissector_handle(dissect_UERadioCapabilityIDMappingRequest_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.sout", id_UERadioCapabilityIDMapping, create_dissector_handle(dissect_UERadioCapabilityIDMappingResponse_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_HandoverSuccess, create_dissector_handle(dissect_HandoverSuccess_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_eNBEarlyStatusTransfer, create_dissector_handle(dissect_ENBEarlyStatusTransfer_PDU, proto_s1ap));
  dissector_add_uint("s1ap.proc.imsg", id_MMEEarlyStatusTransfer, create_dissector_handle(dissect_MMEEarlyStatusTransfer_PDU, proto_s1ap));


/*--- End of included file: packet-s1ap-dis-tab.c ---*/
#line 517 "./asn1/s1ap/packet-s1ap-template.c"
  } else {
    if (SctpPort != 0) {
      dissector_delete_uint("sctp.port", SctpPort, s1ap_handle);
    }
  }

  SctpPort=gbl_s1apSctpPort;
  if (SctpPort != 0) {
    dissector_add_uint("sctp.port", SctpPort, s1ap_handle);
  }
}

/*--- proto_register_s1ap -------------------------------------------*/
void proto_register_s1ap(void) {

  /* List of fields */

  static hf_register_info hf[] = {
    { &hf_s1ap_transportLayerAddressIPv4,
      { "transportLayerAddress(IPv4)", "s1ap.transportLayerAddressIPv4",
        FT_IPv4, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_transportLayerAddressIPv6,
      { "transportLayerAddress(IPv6)", "s1ap.transportLayerAddressIPv6",
        FT_IPv6, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_UTRAN_Trace_ID_TraceID,
      { "TraceID", "s1ap.E_UTRAN_Trace_ID.TraceID",
        FT_UINT24, BASE_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_UTRAN_Trace_ID_TraceRecordingSessionReference,
      { "TraceRecordingSessionReference", "s1ap.E_UTRAN_Trace_ID.TraceRecordingSessionReference",
        FT_UINT16, BASE_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_S1_MME,
      { "S1-MME", "s1ap.interfacesToTrace.S1_MME",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_interfacesToTrace), 0x80,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_X2,
      { "X2", "s1ap.interfacesToTrace.X2",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_interfacesToTrace), 0x40,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_Uu,
      { "Uu", "s1ap.interfacesToTrace.Uu",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_interfacesToTrace), 0x20,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_F1_C,
      { "F1-C", "s1ap.interfacesToTrace.F1_C",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_interfacesToTrace), 0x10,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_E1,
      { "E1", "s1ap.interfacesToTrace.E1",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_interfacesToTrace), 0x08,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace_Reserved,
      { "Reserved", "s1ap.interfacesToTrace.Reserved",
        FT_UINT8, BASE_HEX, NULL, 0x07,
        NULL, HFILL }},
    { &hf_s1ap_encryptionAlgorithms_EEA1,
      { "128-EEA1", "s1ap.encryptionAlgorithms.EEA1",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x8000,
        NULL, HFILL }},
    { &hf_s1ap_encryptionAlgorithms_EEA2,
      { "128-EEA2", "s1ap.encryptionAlgorithms.EEA2",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x4000,
        NULL, HFILL }},
    { &hf_s1ap_encryptionAlgorithms_EEA3,
      { "128-EEA3", "s1ap.encryptionAlgorithms.EEA3",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x2000,
        NULL, HFILL }},
    { &hf_s1ap_encryptionAlgorithms_Reserved,
      { "Reserved", "s1ap.encryptionAlgorithms.Reserved",
        FT_UINT16, BASE_HEX, NULL, 0x1fff,
        NULL, HFILL }},
    { &hf_s1ap_integrityProtectionAlgorithms_EIA1,
      { "128-EIA1", "s1ap.integrityProtectionAlgorithms.EIA1",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x8000,
        NULL, HFILL }},
    { &hf_s1ap_integrityProtectionAlgorithms_EIA2,
      { "128-EIA2", "s1ap.integrityProtectionAlgorithms.EIA2",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x4000,
        NULL, HFILL }},
    { &hf_s1ap_integrityProtectionAlgorithms_EIA3,
      { "128-EIA3", "s1ap.integrityProtectionAlgorithms.EIA3",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x2000,
        NULL, HFILL }},
    { &hf_s1ap_integrityProtectionAlgorithms_Reserved,
      { "Reserved", "s1ap.integrityProtectionAlgorithms.Reserved",
        FT_UINT16, BASE_HEX, NULL, 0x1fff,
        NULL, HFILL }},
    { &hf_s1ap_SerialNumber_gs,
      { "Geographical Scope", "s1ap.SerialNumber.gs",
        FT_UINT16, BASE_DEC, VALS(s1ap_serialNumber_gs_vals), 0xc000,
        NULL, HFILL }},
    { &hf_s1ap_SerialNumber_msg_code,
      { "Message Code", "s1ap.SerialNumber.msg_code",
        FT_UINT16, BASE_DEC, NULL, 0x3ff0,
        NULL, HFILL }},
    { &hf_s1ap_SerialNumber_upd_nb,
      { "Update Number", "s1ap.SerialNumber.upd_nb",
        FT_UINT16, BASE_DEC, NULL, 0x000f,
        NULL, HFILL }},
    { &hf_s1ap_WarningType_value,
      { "Warning Type Value", "s1ap.WarningType.value",
        FT_UINT16, BASE_DEC, VALS(s1ap_warningType_vals), 0xfe00,
        NULL, HFILL }},
    { &hf_s1ap_WarningType_emergency_user_alert,
      { "Emergency User Alert", "s1ap.WarningType.emergency_user_alert",
        FT_BOOLEAN, 16, TFS(&tfs_yes_no), 0x0100,
        NULL, HFILL }},
    { &hf_s1ap_WarningType_popup,
      { "Popup", "s1ap.WarningType.popup",
        FT_BOOLEAN, 16, TFS(&tfs_yes_no), 0x0080,
        NULL, HFILL }},
    { &hf_s1ap_WarningMessageContents_nb_pages,
      { "Number of Pages", "s1ap.WarningMessageContents.nb_pages",
        FT_UINT8, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningMessageContents_decoded_page,
      { "Decoded Page", "s1ap.WarningMessageContents.decoded_page",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M1,
      { "M1", "s1ap.measurementsToActivate.M1",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x80,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M2,
      { "M2", "s1ap.measurementsToActivate.M2",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x40,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M3,
      { "M3", "s1ap.measurementsToActivate.M3",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x20,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M4,
      { "M4", "s1ap.measurementsToActivate.M4",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x10,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M5,
      { "M5", "s1ap.measurementsToActivate.M5",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x08,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_LoggingM1FromEventTriggered,
      { "LoggingOfM1FromEventTriggeredMeasurementReports", "s1ap.measurementsToActivate.LoggingM1FromEventTriggered",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x04,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M6,
      { "M6", "s1ap.measurementsToActivate.M6",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x02,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate_M7,
      { "M7", "s1ap.measurementsToActivate.M7",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x01,
        NULL, HFILL }},
    { &hf_s1ap_MDT_Location_Info_GNSS,
      { "GNSS", "s1ap.MDT_Location_Info.GNSS",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x80,
        NULL, HFILL }},
    { &hf_s1ap_MDT_Location_Info_E_CID,
      { "E-CID", "s1ap.MDT_Location_Info.E_CID",
        FT_BOOLEAN, 8, TFS(&s1ap_tfs_activate_do_not_activate), 0x40,
        NULL, HFILL }},
    { &hf_s1ap_MDT_Location_Info_Reserved,
      { "Reserved", "s1ap.MDT_Location_Info.Reserved",
        FT_UINT8, BASE_HEX, NULL, 0x3f,
        NULL, HFILL }},
    { &hf_s1ap_NRencryptionAlgorithms_NEA1,
      { "128-NEA1", "s1ap.NRencryptionAlgorithms.NEA1",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x8000,
        NULL, HFILL }},
    { &hf_s1ap_NRencryptionAlgorithms_NEA2,
      { "128-NEA2", "s1ap.NRencryptionAlgorithms.NEA2",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x4000,
        NULL, HFILL }},
    { &hf_s1ap_NRencryptionAlgorithms_NEA3,
      { "128-NEA3", "s1ap.NRencryptionAlgorithms.NEA3",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x2000,
        NULL, HFILL }},
    { &hf_s1ap_NRencryptionAlgorithms_Reserved,
      { "Reserved", "s1ap.NRencryptionAlgorithms.Reserved",
        FT_UINT16, BASE_HEX, NULL, 0x1fff,
        NULL, HFILL }},
    { &hf_s1ap_NRintegrityProtectionAlgorithms_NIA1,
      { "128-NIA1", "s1ap.NRintegrityProtectionAlgorithms.NIA1",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x8000,
        NULL, HFILL }},
    { &hf_s1ap_NRintegrityProtectionAlgorithms_NIA2,
      { "128-NIA2", "s1ap.NRintegrityProtectionAlgorithms.NIA2",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x4000,
        NULL, HFILL }},
    { &hf_s1ap_NRintegrityProtectionAlgorithms_NIA3,
      { "128-NIA3", "s1ap.NRintegrityProtectionAlgorithms.NIA3",
        FT_BOOLEAN, 16, TFS(&tfs_supported_not_supported), 0x2000,
        NULL, HFILL }},
    { &hf_s1ap_NRintegrityProtectionAlgorithms_Reserved,
      { "Reserved", "s1ap.NRintegrityProtectionAlgorithms.Reserved",
        FT_UINT16, BASE_HEX, NULL, 0x1fff,
        NULL, HFILL }},
    { &hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_streaming_service,
      { "QoE Measurement for streaming service", "s1ap.UE_Application_Layer_Measurement_Capability.QoE_Measurement_for_streaming_service",
        FT_BOOLEAN, 8, TFS(&tfs_supported_not_supported), 0x80,
        NULL, HFILL }},
    { &hf_s1ap_UE_Application_Layer_Measurement_Capability_QoE_Measurement_for_MTSI_service,
      { "QoE Measurement for MTSI service", "s1ap.UE_Application_Layer_Measurement_Capability.QoE_Measurement_for_MTSI_service",
        FT_BOOLEAN, 8, TFS(&tfs_supported_not_supported), 0x40,
        NULL, HFILL }},
    { &hf_s1ap_UE_Application_Layer_Measurement_Capability_Reserved,
      { "Reserved", "s1ap.UE_Application_Layer_Measurement_Capability.Reserved",
        FT_UINT8, BASE_HEX, NULL, 0x3f,
        NULL, HFILL }},

/*--- Included file: packet-s1ap-hfarr.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-hfarr.c"
    { &hf_s1ap_Additional_GUTI_PDU,
      { "Additional-GUTI", "s1ap.Additional_GUTI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_AdditionalRRMPriorityIndex_PDU,
      { "AdditionalRRMPriorityIndex", "s1ap.AdditionalRRMPriorityIndex",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_AerialUEsubscriptionInformation_PDU,
      { "AerialUEsubscriptionInformation", "s1ap.AerialUEsubscriptionInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_AerialUEsubscriptionInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_AssistanceDataForPaging_PDU,
      { "AssistanceDataForPaging", "s1ap.AssistanceDataForPaging_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Bearers_SubjectToStatusTransfer_Item_PDU,
      { "Bearers-SubjectToStatusTransfer-Item", "s1ap.Bearers_SubjectToStatusTransfer_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item_PDU,
      { "Bearers-SubjectToEarlyStatusTransfer-Item", "s1ap.Bearers_SubjectToEarlyStatusTransfer_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_BearerType_PDU,
      { "BearerType", "s1ap.BearerType",
        FT_UINT32, BASE_DEC, VALS(s1ap_BearerType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_BluetoothMeasurementConfiguration_PDU,
      { "BluetoothMeasurementConfiguration", "s1ap.BluetoothMeasurementConfiguration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_BroadcastCancelledAreaList_PDU,
      { "BroadcastCancelledAreaList", "s1ap.BroadcastCancelledAreaList",
        FT_UINT32, BASE_DEC, VALS(s1ap_BroadcastCancelledAreaList_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_BroadcastCompletedAreaList_PDU,
      { "BroadcastCompletedAreaList", "s1ap.BroadcastCompletedAreaList",
        FT_UINT32, BASE_DEC, VALS(s1ap_BroadcastCompletedAreaList_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Cause_PDU,
      { "Cause", "s1ap.Cause",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CellAccessMode_PDU,
      { "CellAccessMode", "s1ap.CellAccessMode",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellAccessMode_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CellIdentifierAndCELevelForCECapableUEs_PDU,
      { "CellIdentifierAndCELevelForCECapableUEs", "s1ap.CellIdentifierAndCELevelForCECapableUEs_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CE_mode_B_SupportIndicator_PDU,
      { "CE-mode-B-SupportIndicator", "s1ap.CE_mode_B_SupportIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_CE_mode_B_SupportIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000PDU_PDU,
      { "Cdma2000PDU", "s1ap.Cdma2000PDU",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000RATType_PDU,
      { "Cdma2000RATType", "s1ap.Cdma2000RATType",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cdma2000RATType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000SectorID_PDU,
      { "Cdma2000SectorID", "s1ap.Cdma2000SectorID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000HOStatus_PDU,
      { "Cdma2000HOStatus", "s1ap.Cdma2000HOStatus",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cdma2000HOStatus_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000HORequiredIndication_PDU,
      { "Cdma2000HORequiredIndication", "s1ap.Cdma2000HORequiredIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cdma2000HORequiredIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000OneXSRVCCInfo_PDU,
      { "Cdma2000OneXSRVCCInfo", "s1ap.Cdma2000OneXSRVCCInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Cdma2000OneXRAND_PDU,
      { "Cdma2000OneXRAND", "s1ap.Cdma2000OneXRAND",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CNDomain_PDU,
      { "CNDomain", "s1ap.CNDomain",
        FT_UINT32, BASE_DEC, VALS(s1ap_CNDomain_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CNTypeRestrictions_PDU,
      { "CNTypeRestrictions", "s1ap.CNTypeRestrictions",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ConcurrentWarningMessageIndicator_PDU,
      { "ConcurrentWarningMessageIndicator", "s1ap.ConcurrentWarningMessageIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_ConcurrentWarningMessageIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ConnectedengNBList_PDU,
      { "ConnectedengNBList", "s1ap.ConnectedengNBList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ContextatSource_PDU,
      { "ContextatSource", "s1ap.ContextatSource_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Correlation_ID_PDU,
      { "Correlation-ID", "s1ap.Correlation_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CSFallbackIndicator_PDU,
      { "CSFallbackIndicator", "s1ap.CSFallbackIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_CSFallbackIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_AdditionalCSFallbackIndicator_PDU,
      { "AdditionalCSFallbackIndicator", "s1ap.AdditionalCSFallbackIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_AdditionalCSFallbackIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CSG_Id_PDU,
      { "CSG-Id", "s1ap.CSG_Id",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CSG_IdList_PDU,
      { "CSG-IdList", "s1ap.CSG_IdList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CSGMembershipStatus_PDU,
      { "CSGMembershipStatus", "s1ap.CSGMembershipStatus",
        FT_UINT32, BASE_DEC, VALS(s1ap_CSGMembershipStatus_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_COUNTValueExtended_PDU,
      { "COUNTValueExtended", "s1ap.COUNTValueExtended_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_COUNTvaluePDCP_SNlength18_PDU,
      { "COUNTvaluePDCP-SNlength18", "s1ap.COUNTvaluePDCP_SNlength18_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Coverage_Level_PDU,
      { "Coverage-Level", "s1ap.Coverage_Level",
        FT_UINT32, BASE_DEC, VALS(s1ap_Coverage_Level_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CriticalityDiagnostics_PDU,
      { "CriticalityDiagnostics", "s1ap.CriticalityDiagnostics_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DAPSRequestInfo_PDU,
      { "DAPSRequestInfo", "s1ap.DAPSRequestInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DAPSResponseInfoList_PDU,
      { "DAPSResponseInfoList", "s1ap.DAPSResponseInfoList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DAPSResponseInfoItem_PDU,
      { "DAPSResponseInfoItem", "s1ap.DAPSResponseInfoItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DataCodingScheme_PDU,
      { "DataCodingScheme", "s1ap.DataCodingScheme",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DataSize_PDU,
      { "DataSize", "s1ap.DataSize",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_bit_bits, 0,
        NULL, HFILL }},
    { &hf_s1ap_DCN_ID_PDU,
      { "DCN-ID", "s1ap.DCN_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedDCNs_PDU,
      { "ServedDCNs", "s1ap.ServedDCNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DL_CP_SecurityInformation_PDU,
      { "DL-CP-SecurityInformation", "s1ap.DL_CP_SecurityInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Direct_Forwarding_Path_Availability_PDU,
      { "Direct-Forwarding-Path-Availability", "s1ap.Direct_Forwarding_Path_Availability",
        FT_UINT32, BASE_DEC, VALS(s1ap_Direct_Forwarding_Path_Availability_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Data_Forwarding_Not_Possible_PDU,
      { "Data-Forwarding-Not-Possible", "s1ap.Data_Forwarding_Not_Possible",
        FT_UINT32, BASE_DEC, VALS(s1ap_Data_Forwarding_Not_Possible_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_DLNASPDUDeliveryAckRequest_PDU,
      { "DLNASPDUDeliveryAckRequest", "s1ap.DLNASPDUDeliveryAckRequest",
        FT_UINT32, BASE_DEC, VALS(s1ap_DLNASPDUDeliveryAckRequest_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PWSfailedECGIList_PDU,
      { "PWSfailedECGIList", "s1ap.PWSfailedECGIList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EDT_Session_PDU,
      { "EDT-Session", "s1ap.EDT_Session",
        FT_UINT32, BASE_DEC, VALS(s1ap_EDT_Session_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyAreaIDListForRestart_PDU,
      { "EmergencyAreaIDListForRestart", "s1ap.EmergencyAreaIDListForRestart",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyIndicator_PDU,
      { "EmergencyIndicator", "s1ap.EmergencyIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_EmergencyIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ENB_EarlyStatusTransfer_TransparentContainer_PDU,
      { "ENB-EarlyStatusTransfer-TransparentContainer", "s1ap.ENB_EarlyStatusTransfer_TransparentContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_Global_ENB_ID_PDU,
      { "Global-ENB-ID", "s1ap.Global_ENB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_GUMMEIList_PDU,
      { "GUMMEIList", "s1ap.GUMMEIList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_ENB_StatusTransfer_TransparentContainer_PDU,
      { "ENB-StatusTransfer-TransparentContainer", "s1ap.ENB_StatusTransfer_TransparentContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENB_UE_S1AP_ID_PDU,
      { "ENB-UE-S1AP-ID", "s1ap.ENB_UE_S1AP_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBname_PDU,
      { "ENBname", "s1ap.ENBname",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_EN_DCSONConfigurationTransfer_PDU,
      { "EN-DCSONConfigurationTransfer", "s1ap.EN_DCSONConfigurationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EndIndication_PDU,
      { "EndIndication", "s1ap.EndIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_EndIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_EnhancedCoverageRestricted_PDU,
      { "EnhancedCoverageRestricted", "s1ap.EnhancedCoverageRestricted",
        FT_UINT32, BASE_DEC, VALS(s1ap_EnhancedCoverageRestricted_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CE_ModeBRestricted_PDU,
      { "CE-ModeBRestricted", "s1ap.CE_ModeBRestricted",
        FT_UINT32, BASE_DEC, VALS(s1ap_CE_ModeBRestricted_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABInformationListItem_PDU,
      { "E-RABInformationListItem", "s1ap.E_RABInformationListItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABList_PDU,
      { "E-RABList", "s1ap.E_RABList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABItem_PDU,
      { "E-RABItem", "s1ap.E_RABItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABLevelQoSParameters_PDU,
      { "E-RABLevelQoSParameters", "s1ap.E_RABLevelQoSParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABUsageReportItem_PDU,
      { "E-RABUsageReportItem", "s1ap.E_RABUsageReportItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Ethernet_Type_PDU,
      { "Ethernet-Type", "s1ap.Ethernet_Type",
        FT_UINT32, BASE_DEC, VALS(s1ap_Ethernet_Type_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_EUTRAN_CGI_PDU,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EUTRANRoundTripDelayEstimationInfo_PDU,
      { "EUTRANRoundTripDelayEstimationInfo", "s1ap.EUTRANRoundTripDelayEstimationInfo",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_EUTRANRoundTripDelayEstimationInfo_fmt), 0,
        NULL, HFILL }},
    { &hf_s1ap_ExpectedUEBehaviour_PDU,
      { "ExpectedUEBehaviour", "s1ap.ExpectedUEBehaviour_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ExtendedBitRate_PDU,
      { "ExtendedBitRate", "s1ap.ExtendedBitRate",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        NULL, HFILL }},
    { &hf_s1ap_ExtendedRepetitionPeriod_PDU,
      { "ExtendedRepetitionPeriod", "s1ap.ExtendedRepetitionPeriod",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_Extended_UEIdentityIndexValue_PDU,
      { "Extended-UEIdentityIndexValue", "s1ap.Extended_UEIdentityIndexValue",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_GUMMEI_PDU,
      { "GUMMEI", "s1ap.GUMMEI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_GUMMEIType_PDU,
      { "GUMMEIType", "s1ap.GUMMEIType",
        FT_UINT32, BASE_DEC, VALS(s1ap_GUMMEIType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_GWContextReleaseIndication_PDU,
      { "GWContextReleaseIndication", "s1ap.GWContextReleaseIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_GWContextReleaseIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverFlag_PDU,
      { "HandoverFlag", "s1ap.HandoverFlag",
        FT_UINT32, BASE_DEC, VALS(s1ap_HandoverFlag_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_HandoverRestrictionList_PDU,
      { "HandoverRestrictionList", "s1ap.HandoverRestrictionList_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverType_PDU,
      { "HandoverType", "s1ap.HandoverType",
        FT_UINT32, BASE_DEC, VALS(s1ap_HandoverType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Masked_IMEISV_PDU,
      { "Masked-IMEISV", "s1ap.Masked_IMEISV",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_ImmediateMDT_PDU,
      { "ImmediateMDT", "s1ap.ImmediateMDT_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InformationOnRecommendedCellsAndENBsForPaging_PDU,
      { "InformationOnRecommendedCellsAndENBsForPaging", "s1ap.InformationOnRecommendedCellsAndENBsForPaging_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_IntersystemMeasurementConfiguration_PDU,
      { "IntersystemMeasurementConfiguration", "s1ap.IntersystemMeasurementConfiguration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_IntersystemSONConfigurationTransfer_PDU,
      { "IntersystemSONConfigurationTransfer", "s1ap.IntersystemSONConfigurationTransfer",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_IMSvoiceEPSfallbackfrom5G_PDU,
      { "IMSvoiceEPSfallbackfrom5G", "s1ap.IMSvoiceEPSfallbackfrom5G",
        FT_UINT32, BASE_DEC, VALS(s1ap_IMSvoiceEPSfallbackfrom5G_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_IAB_Authorized_PDU,
      { "IAB-Authorized", "s1ap.IAB_Authorized",
        FT_UINT32, BASE_DEC, VALS(s1ap_IAB_Authorized_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_IAB_Node_Indication_PDU,
      { "IAB-Node-Indication", "s1ap.IAB_Node_Indication",
        FT_UINT32, BASE_DEC, VALS(s1ap_IAB_Node_Indication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_IAB_Supported_PDU,
      { "IAB-Supported", "s1ap.IAB_Supported",
        FT_UINT32, BASE_DEC, VALS(s1ap_IAB_Supported_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_KillAllWarningMessages_PDU,
      { "KillAllWarningMessages", "s1ap.KillAllWarningMessages",
        FT_UINT32, BASE_DEC, VALS(s1ap_KillAllWarningMessages_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_LAI_PDU,
      { "LAI", "s1ap.LAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_LastVisitedEUTRANCellInformation_PDU,
      { "LastVisitedEUTRANCellInformation", "s1ap.LastVisitedEUTRANCellInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_LastVisitedGERANCellInformation_PDU,
      { "LastVisitedGERANCellInformation", "s1ap.LastVisitedGERANCellInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_LastVisitedGERANCellInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_LPPa_PDU_PDU,
      { "LPPa-PDU", "s1ap.LPPa_PDU",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LHN_ID_PDU,
      { "LHN-ID", "s1ap.LHN_ID",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LoggedMBSFNMDT_PDU,
      { "LoggedMBSFNMDT", "s1ap.LoggedMBSFNMDT_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LTE_M_Indication_PDU,
      { "LTE-M-Indication", "s1ap.LTE_M_Indication",
        FT_UINT32, BASE_DEC, VALS(s1ap_LTE_M_Indication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_M3Configuration_PDU,
      { "M3Configuration", "s1ap.M3Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_M4Configuration_PDU,
      { "M4Configuration", "s1ap.M4Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_M5Configuration_PDU,
      { "M5Configuration", "s1ap.M5Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_M6Configuration_PDU,
      { "M6Configuration", "s1ap.M6Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_M7Configuration_PDU,
      { "M7Configuration", "s1ap.M7Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MDT_Location_Info_PDU,
      { "MDT-Location-Info", "s1ap.MDT_Location_Info",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MDT_Configuration_PDU,
      { "MDT-Configuration", "s1ap.MDT_Configuration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ManagementBasedMDTAllowed_PDU,
      { "ManagementBasedMDTAllowed", "s1ap.ManagementBasedMDTAllowed",
        FT_UINT32, BASE_DEC, VALS(s1ap_ManagementBasedMDTAllowed_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MDTPLMNList_PDU,
      { "MDTPLMNList", "s1ap.MDTPLMNList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PrivacyIndicator_PDU,
      { "PrivacyIndicator", "s1ap.PrivacyIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_PrivacyIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_MDTMode_PDU,
      { "MDTMode", "s1ap.MDTMode",
        FT_UINT32, BASE_DEC, VALS(s1ap_MDTMode_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MessageIdentifier_PDU,
      { "MessageIdentifier", "s1ap.MessageIdentifier",
        FT_UINT16, BASE_DEC|BASE_EXT_STRING, &lte_rrc_messageIdentifier_vals_ext, 0,
        NULL, HFILL }},
    { &hf_s1ap_MobilityInformation_PDU,
      { "MobilityInformation", "s1ap.MobilityInformation",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEname_PDU,
      { "MMEname", "s1ap.MMEname",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMERelaySupportIndicator_PDU,
      { "MMERelaySupportIndicator", "s1ap.MMERelaySupportIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_MMERelaySupportIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MME_Group_ID_PDU,
      { "MME-Group-ID", "s1ap.MME_Group_ID",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MME_UE_S1AP_ID_PDU,
      { "MME-UE-S1AP-ID", "s1ap.MME_UE_S1AP_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MSClassmark2_PDU,
      { "MSClassmark2", "s1ap.MSClassmark2",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MSClassmark3_PDU,
      { "MSClassmark3", "s1ap.MSClassmark3",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MutingAvailabilityIndication_PDU,
      { "MutingAvailabilityIndication", "s1ap.MutingAvailabilityIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_MutingAvailabilityIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MutingPatternInformation_PDU,
      { "MutingPatternInformation", "s1ap.MutingPatternInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MDT_ConfigurationNR_PDU,
      { "MDT-ConfigurationNR", "s1ap.MDT_ConfigurationNR",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NAS_PDU_PDU,
      { "NAS-PDU", "s1ap.NAS_PDU",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NASSecurityParametersfromE_UTRAN_PDU,
      { "NASSecurityParametersfromE-UTRAN", "s1ap.NASSecurityParametersfromE_UTRAN",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NASSecurityParameterstoE_UTRAN_PDU,
      { "NASSecurityParameterstoE-UTRAN", "s1ap.NASSecurityParameterstoE_UTRAN",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NB_IoT_DefaultPagingDRX_PDU,
      { "NB-IoT-DefaultPagingDRX", "s1ap.NB_IoT_DefaultPagingDRX",
        FT_UINT32, BASE_DEC, VALS(s1ap_NB_IoT_DefaultPagingDRX_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_NB_IoT_PagingDRX_PDU,
      { "NB-IoT-PagingDRX", "s1ap.NB_IoT_PagingDRX",
        FT_UINT32, BASE_DEC, VALS(s1ap_NB_IoT_PagingDRX_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_NB_IoT_Paging_eDRXInformation_PDU,
      { "NB-IoT-Paging-eDRXInformation", "s1ap.NB_IoT_Paging_eDRXInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NB_IoT_RLF_Report_Container_PDU,
      { "NB-IoT-RLF-Report-Container", "s1ap.NB_IoT_RLF_Report_Container",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NB_IoT_UEIdentityIndexValue_PDU,
      { "NB-IoT-UEIdentityIndexValue", "s1ap.NB_IoT_UEIdentityIndexValue",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NotifySourceeNB_PDU,
      { "NotifySourceeNB", "s1ap.NotifySourceeNB",
        FT_UINT32, BASE_DEC, VALS(s1ap_NotifySourceeNB_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_NRrestrictioninEPSasSecondaryRAT_PDU,
      { "NRrestrictioninEPSasSecondaryRAT", "s1ap.NRrestrictioninEPSasSecondaryRAT",
        FT_UINT32, BASE_DEC, VALS(s1ap_NRrestrictioninEPSasSecondaryRAT_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_NRrestrictionin5GS_PDU,
      { "NRrestrictionin5GS", "s1ap.NRrestrictionin5GS",
        FT_UINT32, BASE_DEC, VALS(s1ap_NRrestrictionin5GS_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_NRUESecurityCapabilities_PDU,
      { "NRUESecurityCapabilities", "s1ap.NRUESecurityCapabilities_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NumberofBroadcastRequest_PDU,
      { "NumberofBroadcastRequest", "s1ap.NumberofBroadcastRequest",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NRV2XServicesAuthorized_PDU,
      { "NRV2XServicesAuthorized", "s1ap.NRV2XServicesAuthorized_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NRUESidelinkAggregateMaximumBitrate_PDU,
      { "NRUESidelinkAggregateMaximumBitrate", "s1ap.NRUESidelinkAggregateMaximumBitrate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_OverloadResponse_PDU,
      { "OverloadResponse", "s1ap.OverloadResponse",
        FT_UINT32, BASE_DEC, VALS(s1ap_OverloadResponse_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Packet_LossRate_PDU,
      { "Packet-LossRate", "s1ap.Packet_LossRate",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_Packet_LossRate_fmt), 0,
        NULL, HFILL }},
    { &hf_s1ap_Paging_eDRXInformation_PDU,
      { "Paging-eDRXInformation", "s1ap.Paging_eDRXInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PagingDRX_PDU,
      { "PagingDRX", "s1ap.PagingDRX",
        FT_UINT32, BASE_DEC, VALS(s1ap_PagingDRX_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PagingPriority_PDU,
      { "PagingPriority", "s1ap.PagingPriority",
        FT_UINT32, BASE_DEC, VALS(s1ap_PagingPriority_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PC5QoSParameters_PDU,
      { "PC5QoSParameters", "s1ap.PC5QoSParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PendingDataIndication_PDU,
      { "PendingDataIndication", "s1ap.PendingDataIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_PendingDataIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PLMNidentity_PDU,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ProSeAuthorized_PDU,
      { "ProSeAuthorized", "s1ap.ProSeAuthorized_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ProSeUEtoNetworkRelaying_PDU,
      { "ProSeUEtoNetworkRelaying", "s1ap.ProSeUEtoNetworkRelaying",
        FT_UINT32, BASE_DEC, VALS(s1ap_ProSeUEtoNetworkRelaying_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PS_ServiceNotAvailable_PDU,
      { "PS-ServiceNotAvailable", "s1ap.PS_ServiceNotAvailable",
        FT_UINT32, BASE_DEC, VALS(s1ap_PS_ServiceNotAvailable_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_PSCellInformation_PDU,
      { "PSCellInformation", "s1ap.PSCellInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ReceiveStatusOfULPDCPSDUsExtended_PDU,
      { "ReceiveStatusOfULPDCPSDUsExtended", "s1ap.ReceiveStatusOfULPDCPSDUsExtended",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ReceiveStatusOfULPDCPSDUsPDCP_SNlength18_PDU,
      { "ReceiveStatusOfULPDCPSDUsPDCP-SNlength18", "s1ap.ReceiveStatusOfULPDCPSDUsPDCP_SNlength18",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RecommendedCellItem_PDU,
      { "RecommendedCellItem", "s1ap.RecommendedCellItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RecommendedENBItem_PDU,
      { "RecommendedENBItem", "s1ap.RecommendedENBItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RelativeMMECapacity_PDU,
      { "RelativeMMECapacity", "s1ap.RelativeMMECapacity",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RelayNode_Indicator_PDU,
      { "RelayNode-Indicator", "s1ap.RelayNode_Indicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_RelayNode_Indicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_RAT_Type_PDU,
      { "RAT-Type", "s1ap.RAT_Type",
        FT_UINT32, BASE_DEC, VALS(s1ap_RAT_Type_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_RequestType_PDU,
      { "RequestType", "s1ap.RequestType_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RequestTypeAdditionalInfo_PDU,
      { "RequestTypeAdditionalInfo", "s1ap.RequestTypeAdditionalInfo",
        FT_UINT32, BASE_DEC, VALS(s1ap_RequestTypeAdditionalInfo_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_RepetitionPeriod_PDU,
      { "RepetitionPeriod", "s1ap.RepetitionPeriod",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_RRC_Establishment_Cause_PDU,
      { "RRC-Establishment-Cause", "s1ap.RRC_Establishment_Cause",
        FT_UINT32, BASE_DEC, VALS(s1ap_RRC_Establishment_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ECGIListForRestart_PDU,
      { "ECGIListForRestart", "s1ap.ECGIListForRestart",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Routing_ID_PDU,
      { "Routing-ID", "s1ap.Routing_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SecurityKey_PDU,
      { "SecurityKey", "s1ap.SecurityKey",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SecurityContext_PDU,
      { "SecurityContext", "s1ap.SecurityContext_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SecondaryRATDataUsageRequest_PDU,
      { "SecondaryRATDataUsageRequest", "s1ap.SecondaryRATDataUsageRequest",
        FT_UINT32, BASE_DEC, VALS(s1ap_SecondaryRATDataUsageRequest_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_SecondaryRATDataUsageReportList_PDU,
      { "SecondaryRATDataUsageReportList", "s1ap.SecondaryRATDataUsageReportList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SecondaryRATDataUsageReportItem_PDU,
      { "SecondaryRATDataUsageReportItem", "s1ap.SecondaryRATDataUsageReportItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SerialNumber_PDU,
      { "SerialNumber", "s1ap.SerialNumber",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServiceType_PDU,
      { "ServiceType", "s1ap.ServiceType",
        FT_UINT32, BASE_DEC, VALS(s1ap_ServiceType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_SONInformationReport_PDU,
      { "SONInformationReport", "s1ap.SONInformationReport",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONInformationReport_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SONConfigurationTransfer_PDU,
      { "SONConfigurationTransfer", "s1ap.SONConfigurationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SynchronisationInformation_PDU,
      { "SynchronisationInformation", "s1ap.SynchronisationInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Source_ToTarget_TransparentContainer_PDU,
      { "Source-ToTarget-TransparentContainer", "s1ap.Source_ToTarget_TransparentContainer",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SRVCCOperationNotPossible_PDU,
      { "SRVCCOperationNotPossible", "s1ap.SRVCCOperationNotPossible",
        FT_UINT32, BASE_DEC, VALS(s1ap_SRVCCOperationNotPossible_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_SRVCCOperationPossible_PDU,
      { "SRVCCOperationPossible", "s1ap.SRVCCOperationPossible",
        FT_UINT32, BASE_DEC, VALS(s1ap_SRVCCOperationPossible_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_SRVCCHOIndication_PDU,
      { "SRVCCHOIndication", "s1ap.SRVCCHOIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_SRVCCHOIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_SourceNodeID_PDU,
      { "SourceNodeID", "s1ap.SourceNodeID",
        FT_UINT32, BASE_DEC, VALS(s1ap_SourceNodeID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SourceeNB_ToTargeteNB_TransparentContainer_PDU,
      { "SourceeNB-ToTargeteNB-TransparentContainer", "s1ap.SourceeNB_ToTargeteNB_TransparentContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedGUMMEIs_PDU,
      { "ServedGUMMEIs", "s1ap.ServedGUMMEIs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedPLMNs_PDU,
      { "ServedPLMNs", "s1ap.ServedPLMNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SubscriberProfileIDforRFP_PDU,
      { "SubscriberProfileIDforRFP", "s1ap.SubscriberProfileIDforRFP",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Subscription_Based_UE_DifferentiationInfo_PDU,
      { "Subscription-Based-UE-DifferentiationInfo", "s1ap.Subscription_Based_UE_DifferentiationInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SupportedTAs_PDU,
      { "SupportedTAs", "s1ap.SupportedTAs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TimeSynchronisationInfo_PDU,
      { "TimeSynchronisationInfo", "s1ap.TimeSynchronisationInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S_TMSI_PDU,
      { "S-TMSI", "s1ap.S_TMSI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAI_PDU,
      { "TAI", "s1ap.TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TargetID_PDU,
      { "TargetID", "s1ap.TargetID",
        FT_UINT32, BASE_DEC, VALS(s1ap_TargetID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_TargeteNB_ToSourceeNB_TransparentContainer_PDU,
      { "TargeteNB-ToSourceeNB-TransparentContainer", "s1ap.TargeteNB_ToSourceeNB_TransparentContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Target_ToSource_TransparentContainer_PDU,
      { "Target-ToSource-TransparentContainer", "s1ap.Target_ToSource_TransparentContainer",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TimeToWait_PDU,
      { "TimeToWait", "s1ap.TimeToWait",
        FT_UINT32, BASE_DEC, VALS(s1ap_TimeToWait_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_Time_UE_StayedInCell_EnhancedGranularity_PDU,
      { "Time-UE-StayedInCell-EnhancedGranularity", "s1ap.Time_UE_StayedInCell_EnhancedGranularity",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_Time_UE_StayedInCell_EnhancedGranularity_fmt), 0,
        NULL, HFILL }},
    { &hf_s1ap_TimeSinceSecondaryNodeRelease_PDU,
      { "TimeSinceSecondaryNodeRelease", "s1ap.TimeSinceSecondaryNodeRelease",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_TransportInformation_PDU,
      { "TransportInformation", "s1ap.TransportInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TransportLayerAddress_PDU,
      { "TransportLayerAddress", "s1ap.TransportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TraceActivation_PDU,
      { "TraceActivation", "s1ap.TraceActivation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_UTRAN_Trace_ID_PDU,
      { "E-UTRAN-Trace-ID", "s1ap.E_UTRAN_Trace_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TrafficLoadReductionIndication_PDU,
      { "TrafficLoadReductionIndication", "s1ap.TrafficLoadReductionIndication",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_percent, 0,
        NULL, HFILL }},
    { &hf_s1ap_TunnelInformation_PDU,
      { "TunnelInformation", "s1ap.TunnelInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIListForRestart_PDU,
      { "TAIListForRestart", "s1ap.TAIListForRestart",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEAggregateMaximumBitrate_PDU,
      { "UEAggregateMaximumBitrate", "s1ap.UEAggregateMaximumBitrate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEAppLayerMeasConfig_PDU,
      { "UEAppLayerMeasConfig", "s1ap.UEAppLayerMeasConfig_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UECapabilityInfoRequest_PDU,
      { "UECapabilityInfoRequest", "s1ap.UECapabilityInfoRequest",
        FT_UINT32, BASE_DEC, VALS(s1ap_UECapabilityInfoRequest_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_RetentionInformation_PDU,
      { "UE-RetentionInformation", "s1ap.UE_RetentionInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_UE_RetentionInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_S1AP_IDs_PDU,
      { "UE-S1AP-IDs", "s1ap.UE_S1AP_IDs",
        FT_UINT32, BASE_DEC, VALS(s1ap_UE_S1AP_IDs_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_associatedLogicalS1_ConnectionItem_PDU,
      { "UE-associatedLogicalS1-ConnectionItem", "s1ap.UE_associatedLogicalS1_ConnectionItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEIdentityIndexValue_PDU,
      { "UEIdentityIndexValue", "s1ap.UEIdentityIndexValue",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_UE_HistoryInformation_PDU,
      { "UE-HistoryInformation", "s1ap.UE_HistoryInformation",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_HistoryInformationFromTheUE_PDU,
      { "UE-HistoryInformationFromTheUE", "s1ap.UE_HistoryInformationFromTheUE",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEPagingID_PDU,
      { "UEPagingID", "s1ap.UEPagingID",
        FT_UINT32, BASE_DEC, VALS(s1ap_UEPagingID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapability_PDU,
      { "UERadioCapability", "s1ap.UERadioCapability",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityForPaging_PDU,
      { "UERadioCapabilityForPaging", "s1ap.UERadioCapabilityForPaging",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityID_PDU,
      { "UERadioCapabilityID", "s1ap.UERadioCapabilityID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UESecurityCapabilities_PDU,
      { "UESecurityCapabilities", "s1ap.UESecurityCapabilities_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UESidelinkAggregateMaximumBitrate_PDU,
      { "UESidelinkAggregateMaximumBitrate", "s1ap.UESidelinkAggregateMaximumBitrate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_Usage_Type_PDU,
      { "UE-Usage-Type", "s1ap.UE_Usage_Type",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UL_CP_SecurityInformation_PDU,
      { "UL-CP-SecurityInformation", "s1ap.UL_CP_SecurityInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UnlicensedSpectrumRestriction_PDU,
      { "UnlicensedSpectrumRestriction", "s1ap.UnlicensedSpectrumRestriction",
        FT_UINT32, BASE_DEC, VALS(s1ap_UnlicensedSpectrumRestriction_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_URI_Address_PDU,
      { "URI-Address", "s1ap.URI_Address",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UserLocationInformation_PDU,
      { "UserLocationInformation", "s1ap.UserLocationInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEUserPlaneCIoTSupportIndicator_PDU,
      { "UEUserPlaneCIoTSupportIndicator", "s1ap.UEUserPlaneCIoTSupportIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_UEUserPlaneCIoTSupportIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_Application_Layer_Measurement_Capability_PDU,
      { "UE-Application-Layer-Measurement-Capability", "s1ap.UE_Application_Layer_Measurement_Capability",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_VoiceSupportMatchIndicator_PDU,
      { "VoiceSupportMatchIndicator", "s1ap.VoiceSupportMatchIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_VoiceSupportMatchIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_V2XServicesAuthorized_PDU,
      { "V2XServicesAuthorized", "s1ap.V2XServicesAuthorized_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningAreaCoordinates_PDU,
      { "WarningAreaCoordinates", "s1ap.WarningAreaCoordinates",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningAreaList_PDU,
      { "WarningAreaList", "s1ap.WarningAreaList",
        FT_UINT32, BASE_DEC, VALS(s1ap_WarningAreaList_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningType_PDU,
      { "WarningType", "s1ap.WarningType",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningSecurityInfo_PDU,
      { "WarningSecurityInfo", "s1ap.WarningSecurityInfo",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WarningMessageContents_PDU,
      { "WarningMessageContents", "s1ap.WarningMessageContents",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WLANMeasurementConfiguration_PDU,
      { "WLANMeasurementConfiguration", "s1ap.WLANMeasurementConfiguration_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WUS_Assistance_Information_PDU,
      { "WUS-Assistance-Information", "s1ap.WUS_Assistance_Information_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_X2TNLConfigurationInfo_PDU,
      { "X2TNLConfigurationInfo", "s1ap.X2TNLConfigurationInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBX2ExtTLAs_PDU,
      { "ENBX2ExtTLAs", "s1ap.ENBX2ExtTLAs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBIndirectX2TransportLayerAddresses_PDU,
      { "ENBIndirectX2TransportLayerAddresses", "s1ap.ENBIndirectX2TransportLayerAddresses",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverRequired_PDU,
      { "HandoverRequired", "s1ap.HandoverRequired_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverCommand_PDU,
      { "HandoverCommand", "s1ap.HandoverCommand_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSubjecttoDataForwardingList_PDU,
      { "E-RABSubjecttoDataForwardingList", "s1ap.E_RABSubjecttoDataForwardingList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABDataForwardingItem_PDU,
      { "E-RABDataForwardingItem", "s1ap.E_RABDataForwardingItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverPreparationFailure_PDU,
      { "HandoverPreparationFailure", "s1ap.HandoverPreparationFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverRequest_PDU,
      { "HandoverRequest", "s1ap.HandoverRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupListHOReq_PDU,
      { "E-RABToBeSetupListHOReq", "s1ap.E_RABToBeSetupListHOReq",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupItemHOReq_PDU,
      { "E-RABToBeSetupItemHOReq", "s1ap.E_RABToBeSetupItemHOReq_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverRequestAcknowledge_PDU,
      { "HandoverRequestAcknowledge", "s1ap.HandoverRequestAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABAdmittedList_PDU,
      { "E-RABAdmittedList", "s1ap.E_RABAdmittedList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABAdmittedItem_PDU,
      { "E-RABAdmittedItem", "s1ap.E_RABAdmittedItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedtoSetupListHOReqAck_PDU,
      { "E-RABFailedtoSetupListHOReqAck", "s1ap.E_RABFailedtoSetupListHOReqAck",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedToSetupItemHOReqAck_PDU,
      { "E-RABFailedToSetupItemHOReqAck", "s1ap.E_RABFailedToSetupItemHOReqAck_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverFailure_PDU,
      { "HandoverFailure", "s1ap.HandoverFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverNotify_PDU,
      { "HandoverNotify", "s1ap.HandoverNotify_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PathSwitchRequest_PDU,
      { "PathSwitchRequest", "s1ap.PathSwitchRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSwitchedDLList_PDU,
      { "E-RABToBeSwitchedDLList", "s1ap.E_RABToBeSwitchedDLList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSwitchedDLItem_PDU,
      { "E-RABToBeSwitchedDLItem", "s1ap.E_RABToBeSwitchedDLItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PathSwitchRequestAcknowledge_PDU,
      { "PathSwitchRequestAcknowledge", "s1ap.PathSwitchRequestAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSwitchedULList_PDU,
      { "E-RABToBeSwitchedULList", "s1ap.E_RABToBeSwitchedULList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSwitchedULItem_PDU,
      { "E-RABToBeSwitchedULItem", "s1ap.E_RABToBeSwitchedULItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PathSwitchRequestFailure_PDU,
      { "PathSwitchRequestFailure", "s1ap.PathSwitchRequestFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverCancel_PDU,
      { "HandoverCancel", "s1ap.HandoverCancel_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverCancelAcknowledge_PDU,
      { "HandoverCancelAcknowledge", "s1ap.HandoverCancelAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_HandoverSuccess_PDU,
      { "HandoverSuccess", "s1ap.HandoverSuccess_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBEarlyStatusTransfer_PDU,
      { "ENBEarlyStatusTransfer", "s1ap.ENBEarlyStatusTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEEarlyStatusTransfer_PDU,
      { "MMEEarlyStatusTransfer", "s1ap.MMEEarlyStatusTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupRequest_PDU,
      { "E-RABSetupRequest", "s1ap.E_RABSetupRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupListBearerSUReq_PDU,
      { "E-RABToBeSetupListBearerSUReq", "s1ap.E_RABToBeSetupListBearerSUReq",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupItemBearerSUReq_PDU,
      { "E-RABToBeSetupItemBearerSUReq", "s1ap.E_RABToBeSetupItemBearerSUReq_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupResponse_PDU,
      { "E-RABSetupResponse", "s1ap.E_RABSetupResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupListBearerSURes_PDU,
      { "E-RABSetupListBearerSURes", "s1ap.E_RABSetupListBearerSURes",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupItemBearerSURes_PDU,
      { "E-RABSetupItemBearerSURes", "s1ap.E_RABSetupItemBearerSURes_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyRequest_PDU,
      { "E-RABModifyRequest", "s1ap.E_RABModifyRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeModifiedListBearerModReq_PDU,
      { "E-RABToBeModifiedListBearerModReq", "s1ap.E_RABToBeModifiedListBearerModReq",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeModifiedItemBearerModReq_PDU,
      { "E-RABToBeModifiedItemBearerModReq", "s1ap.E_RABToBeModifiedItemBearerModReq_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyResponse_PDU,
      { "E-RABModifyResponse", "s1ap.E_RABModifyResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyListBearerModRes_PDU,
      { "E-RABModifyListBearerModRes", "s1ap.E_RABModifyListBearerModRes",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyItemBearerModRes_PDU,
      { "E-RABModifyItemBearerModRes", "s1ap.E_RABModifyItemBearerModRes_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseCommand_PDU,
      { "E-RABReleaseCommand", "s1ap.E_RABReleaseCommand_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseResponse_PDU,
      { "E-RABReleaseResponse", "s1ap.E_RABReleaseResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseListBearerRelComp_PDU,
      { "E-RABReleaseListBearerRelComp", "s1ap.E_RABReleaseListBearerRelComp",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseItemBearerRelComp_PDU,
      { "E-RABReleaseItemBearerRelComp", "s1ap.E_RABReleaseItemBearerRelComp_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseIndication_PDU,
      { "E-RABReleaseIndication", "s1ap.E_RABReleaseIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InitialContextSetupRequest_PDU,
      { "InitialContextSetupRequest", "s1ap.InitialContextSetupRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupListCtxtSUReq_PDU,
      { "E-RABToBeSetupListCtxtSUReq", "s1ap.E_RABToBeSetupListCtxtSUReq",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupItemCtxtSUReq_PDU,
      { "E-RABToBeSetupItemCtxtSUReq", "s1ap.E_RABToBeSetupItemCtxtSUReq_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InitialContextSetupResponse_PDU,
      { "InitialContextSetupResponse", "s1ap.InitialContextSetupResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupListCtxtSURes_PDU,
      { "E-RABSetupListCtxtSURes", "s1ap.E_RABSetupListCtxtSURes",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupItemCtxtSURes_PDU,
      { "E-RABSetupItemCtxtSURes", "s1ap.E_RABSetupItemCtxtSURes_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InitialContextSetupFailure_PDU,
      { "InitialContextSetupFailure", "s1ap.InitialContextSetupFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Paging_PDU,
      { "Paging", "s1ap.Paging_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIList_PDU,
      { "TAIList", "s1ap.TAIList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIItem_PDU,
      { "TAIItem", "s1ap.TAIItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextReleaseRequest_PDU,
      { "UEContextReleaseRequest", "s1ap.UEContextReleaseRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextReleaseCommand_PDU,
      { "UEContextReleaseCommand", "s1ap.UEContextReleaseCommand_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextReleaseComplete_PDU,
      { "UEContextReleaseComplete", "s1ap.UEContextReleaseComplete_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextModificationRequest_PDU,
      { "UEContextModificationRequest", "s1ap.UEContextModificationRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextModificationResponse_PDU,
      { "UEContextModificationResponse", "s1ap.UEContextModificationResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextModificationFailure_PDU,
      { "UEContextModificationFailure", "s1ap.UEContextModificationFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityMatchRequest_PDU,
      { "UERadioCapabilityMatchRequest", "s1ap.UERadioCapabilityMatchRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityMatchResponse_PDU,
      { "UERadioCapabilityMatchResponse", "s1ap.UERadioCapabilityMatchResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DownlinkNASTransport_PDU,
      { "DownlinkNASTransport", "s1ap.DownlinkNASTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InitialUEMessage_PDU,
      { "InitialUEMessage", "s1ap.InitialUEMessage_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UplinkNASTransport_PDU,
      { "UplinkNASTransport", "s1ap.UplinkNASTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NASNonDeliveryIndication_PDU,
      { "NASNonDeliveryIndication", "s1ap.NASNonDeliveryIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RerouteNASRequest_PDU,
      { "RerouteNASRequest", "s1ap.RerouteNASRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S1_Message_PDU,
      { "S1-Message", "s1ap.S1_Message",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NASDeliveryIndication_PDU,
      { "NASDeliveryIndication", "s1ap.NASDeliveryIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Reset_PDU,
      { "Reset", "s1ap.Reset_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ResetType_PDU,
      { "ResetType", "s1ap.ResetType",
        FT_UINT32, BASE_DEC, VALS(s1ap_ResetType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ResetAcknowledge_PDU,
      { "ResetAcknowledge", "s1ap.ResetAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_PDU,
      { "UE-associatedLogicalS1-ConnectionListResAck", "s1ap.UE_associatedLogicalS1_ConnectionListResAck",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ErrorIndication_PDU,
      { "ErrorIndication", "s1ap.ErrorIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S1SetupRequest_PDU,
      { "S1SetupRequest", "s1ap.S1SetupRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S1SetupResponse_PDU,
      { "S1SetupResponse", "s1ap.S1SetupResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S1SetupFailure_PDU,
      { "S1SetupFailure", "s1ap.S1SetupFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBConfigurationUpdate_PDU,
      { "ENBConfigurationUpdate", "s1ap.ENBConfigurationUpdate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBConfigurationUpdateAcknowledge_PDU,
      { "ENBConfigurationUpdateAcknowledge", "s1ap.ENBConfigurationUpdateAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBConfigurationUpdateFailure_PDU,
      { "ENBConfigurationUpdateFailure", "s1ap.ENBConfigurationUpdateFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEConfigurationUpdate_PDU,
      { "MMEConfigurationUpdate", "s1ap.MMEConfigurationUpdate_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEConfigurationUpdateAcknowledge_PDU,
      { "MMEConfigurationUpdateAcknowledge", "s1ap.MMEConfigurationUpdateAcknowledge_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEConfigurationUpdateFailure_PDU,
      { "MMEConfigurationUpdateFailure", "s1ap.MMEConfigurationUpdateFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DownlinkS1cdma2000tunnelling_PDU,
      { "DownlinkS1cdma2000tunnelling", "s1ap.DownlinkS1cdma2000tunnelling_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UplinkS1cdma2000tunnelling_PDU,
      { "UplinkS1cdma2000tunnelling", "s1ap.UplinkS1cdma2000tunnelling_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UECapabilityInfoIndication_PDU,
      { "UECapabilityInfoIndication", "s1ap.UECapabilityInfoIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBStatusTransfer_PDU,
      { "ENBStatusTransfer", "s1ap.ENBStatusTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEStatusTransfer_PDU,
      { "MMEStatusTransfer", "s1ap.MMEStatusTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TraceStart_PDU,
      { "TraceStart", "s1ap.TraceStart_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TraceFailureIndication_PDU,
      { "TraceFailureIndication", "s1ap.TraceFailureIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DeactivateTrace_PDU,
      { "DeactivateTrace", "s1ap.DeactivateTrace_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CellTrafficTrace_PDU,
      { "CellTrafficTrace", "s1ap.CellTrafficTrace_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LocationReportingControl_PDU,
      { "LocationReportingControl", "s1ap.LocationReportingControl_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LocationReportingFailureIndication_PDU,
      { "LocationReportingFailureIndication", "s1ap.LocationReportingFailureIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_LocationReport_PDU,
      { "LocationReport", "s1ap.LocationReport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_OverloadStart_PDU,
      { "OverloadStart", "s1ap.OverloadStart_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_OverloadStop_PDU,
      { "OverloadStop", "s1ap.OverloadStop_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WriteReplaceWarningRequest_PDU,
      { "WriteReplaceWarningRequest", "s1ap.WriteReplaceWarningRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_WriteReplaceWarningResponse_PDU,
      { "WriteReplaceWarningResponse", "s1ap.WriteReplaceWarningResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBDirectInformationTransfer_PDU,
      { "ENBDirectInformationTransfer", "s1ap.ENBDirectInformationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Inter_SystemInformationTransferType_PDU,
      { "Inter-SystemInformationTransferType", "s1ap.Inter_SystemInformationTransferType",
        FT_UINT32, BASE_DEC, VALS(s1ap_Inter_SystemInformationTransferType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEDirectInformationTransfer_PDU,
      { "MMEDirectInformationTransfer", "s1ap.MMEDirectInformationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBConfigurationTransfer_PDU,
      { "ENBConfigurationTransfer", "s1ap.ENBConfigurationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMEConfigurationTransfer_PDU,
      { "MMEConfigurationTransfer", "s1ap.MMEConfigurationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PrivateMessage_PDU,
      { "PrivateMessage", "s1ap.PrivateMessage_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_KillRequest_PDU,
      { "KillRequest", "s1ap.KillRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_KillResponse_PDU,
      { "KillResponse", "s1ap.KillResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PWSRestartIndication_PDU,
      { "PWSRestartIndication", "s1ap.PWSRestartIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PWSFailureIndication_PDU,
      { "PWSFailureIndication", "s1ap.PWSFailureIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DownlinkUEAssociatedLPPaTransport_PDU,
      { "DownlinkUEAssociatedLPPaTransport", "s1ap.DownlinkUEAssociatedLPPaTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UplinkUEAssociatedLPPaTransport_PDU,
      { "UplinkUEAssociatedLPPaTransport", "s1ap.UplinkUEAssociatedLPPaTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_DownlinkNonUEAssociatedLPPaTransport_PDU,
      { "DownlinkNonUEAssociatedLPPaTransport", "s1ap.DownlinkNonUEAssociatedLPPaTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UplinkNonUEAssociatedLPPaTransport_PDU,
      { "UplinkNonUEAssociatedLPPaTransport", "s1ap.UplinkNonUEAssociatedLPPaTransport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModificationIndication_PDU,
      { "E-RABModificationIndication", "s1ap.E_RABModificationIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeModifiedListBearerModInd_PDU,
      { "E-RABToBeModifiedListBearerModInd", "s1ap.E_RABToBeModifiedListBearerModInd",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeModifiedItemBearerModInd_PDU,
      { "E-RABToBeModifiedItemBearerModInd", "s1ap.E_RABToBeModifiedItemBearerModInd_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABNotToBeModifiedListBearerModInd_PDU,
      { "E-RABNotToBeModifiedListBearerModInd", "s1ap.E_RABNotToBeModifiedListBearerModInd",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABNotToBeModifiedItemBearerModInd_PDU,
      { "E-RABNotToBeModifiedItemBearerModInd", "s1ap.E_RABNotToBeModifiedItemBearerModInd_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CSGMembershipInfo_PDU,
      { "CSGMembershipInfo", "s1ap.CSGMembershipInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModificationConfirm_PDU,
      { "E-RABModificationConfirm", "s1ap.E_RABModificationConfirm_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyListBearerModConf_PDU,
      { "E-RABModifyListBearerModConf", "s1ap.E_RABModifyListBearerModConf",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyItemBearerModConf_PDU,
      { "E-RABModifyItemBearerModConf", "s1ap.E_RABModifyItemBearerModConf_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextModificationIndication_PDU,
      { "UEContextModificationIndication", "s1ap.UEContextModificationIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextModificationConfirm_PDU,
      { "UEContextModificationConfirm", "s1ap.UEContextModificationConfirm_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextSuspendRequest_PDU,
      { "UEContextSuspendRequest", "s1ap.UEContextSuspendRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextSuspendResponse_PDU,
      { "UEContextSuspendResponse", "s1ap.UEContextSuspendResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextResumeRequest_PDU,
      { "UEContextResumeRequest", "s1ap.UEContextResumeRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedToResumeListResumeReq_PDU,
      { "E-RABFailedToResumeListResumeReq", "s1ap.E_RABFailedToResumeListResumeReq",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedToResumeItemResumeReq_PDU,
      { "E-RABFailedToResumeItemResumeReq", "s1ap.E_RABFailedToResumeItemResumeReq_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextResumeResponse_PDU,
      { "UEContextResumeResponse", "s1ap.UEContextResumeResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedToResumeListResumeRes_PDU,
      { "E-RABFailedToResumeListResumeRes", "s1ap.E_RABFailedToResumeListResumeRes",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABFailedToResumeItemResumeRes_PDU,
      { "E-RABFailedToResumeItemResumeRes", "s1ap.E_RABFailedToResumeItemResumeRes_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEContextResumeFailure_PDU,
      { "UEContextResumeFailure", "s1ap.UEContextResumeFailure_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ConnectionEstablishmentIndication_PDU,
      { "ConnectionEstablishmentIndication", "s1ap.ConnectionEstablishmentIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RetrieveUEInformation_PDU,
      { "RetrieveUEInformation", "s1ap.RetrieveUEInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UEInformationTransfer_PDU,
      { "UEInformationTransfer", "s1ap.UEInformationTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBCPRelocationIndication_PDU,
      { "ENBCPRelocationIndication", "s1ap.ENBCPRelocationIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MMECPRelocationIndication_PDU,
      { "MMECPRelocationIndication", "s1ap.MMECPRelocationIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_SecondaryRATDataUsageReport_PDU,
      { "SecondaryRATDataUsageReport", "s1ap.SecondaryRATDataUsageReport_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityIDMappingRequest_PDU,
      { "UERadioCapabilityIDMappingRequest", "s1ap.UERadioCapabilityIDMappingRequest_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UERadioCapabilityIDMappingResponse_PDU,
      { "UERadioCapabilityIDMappingResponse", "s1ap.UERadioCapabilityIDMappingResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_S1AP_PDU_PDU,
      { "S1AP-PDU", "s1ap.S1AP_PDU",
        FT_UINT32, BASE_DEC, VALS(s1ap_S1AP_PDU_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SONtransferApplicationIdentity_PDU,
      { "SONtransferApplicationIdentity", "s1ap.SONtransferApplicationIdentity",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONtransferApplicationIdentity_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SONtransferRequestContainer_PDU,
      { "SONtransferRequestContainer", "s1ap.SONtransferRequestContainer",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONtransferRequestContainer_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SONtransferResponseContainer_PDU,
      { "SONtransferResponseContainer", "s1ap.SONtransferResponseContainer",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONtransferResponseContainer_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s1ap_SONtransferCause_PDU,
      { "SONtransferCause", "s1ap.SONtransferCause",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONtransferCause_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_local,
      { "local", "s1ap.local",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_65535", HFILL }},
    { &hf_s1ap_global,
      { "global", "s1ap.global",
        FT_OID, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ProtocolIE_Container_item,
      { "ProtocolIE-Field", "s1ap.ProtocolIE_Field_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_id,
      { "id", "s1ap.id",
        FT_UINT32, BASE_DEC|BASE_EXT_STRING, &s1ap_ProtocolIE_ID_vals_ext, 0,
        "ProtocolIE_ID", HFILL }},
    { &hf_s1ap_criticality,
      { "criticality", "s1ap.criticality",
        FT_UINT32, BASE_DEC, VALS(s1ap_Criticality_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ie_field_value,
      { "value", "s1ap.value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "T_ie_field_value", HFILL }},
    { &hf_s1ap_ProtocolIE_ContainerList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ProtocolExtensionContainer_item,
      { "ProtocolExtensionField", "s1ap.ProtocolExtensionField_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ext_id,
      { "id", "s1ap.id",
        FT_UINT8, BASE_DEC|BASE_EXT_STRING, &s1ap_ProtocolIE_ID_vals_ext, 0,
        "ProtocolExtensionID", HFILL }},
    { &hf_s1ap_extensionValue,
      { "extensionValue", "s1ap.extensionValue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PrivateIE_Container_item,
      { "PrivateIE-Field", "s1ap.PrivateIE_Field_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_private_id,
      { "id", "s1ap.id",
        FT_UINT32, BASE_DEC, VALS(s1ap_PrivateIE_ID_vals), 0,
        "PrivateIE_ID", HFILL }},
    { &hf_s1ap_value,
      { "value", "s1ap.value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_gUMMEI,
      { "gUMMEI", "s1ap.gUMMEI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_m_TMSI,
      { "m-TMSI", "s1ap.m_TMSI",
        FT_UINT32, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_iE_Extensions,
      { "iE-Extensions", "s1ap.iE_Extensions",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ProtocolExtensionContainer", HFILL }},
    { &hf_s1ap_cellBased,
      { "cellBased", "s1ap.cellBased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellBasedMDT", HFILL }},
    { &hf_s1ap_tABased,
      { "tABased", "s1ap.tABased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TABasedMDT", HFILL }},
    { &hf_s1ap_pLMNWide,
      { "pLMNWide", "s1ap.pLMNWide_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAIBased,
      { "tAIBased", "s1ap.tAIBased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TAIBasedMDT", HFILL }},
    { &hf_s1ap_cellBased_01,
      { "cellBased", "s1ap.cellBased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellBasedQMC", HFILL }},
    { &hf_s1ap_tABased_01,
      { "tABased", "s1ap.tABased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TABasedQMC", HFILL }},
    { &hf_s1ap_tAIBased_01,
      { "tAIBased", "s1ap.tAIBased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TAIBasedQMC", HFILL }},
    { &hf_s1ap_pLMNAreaBased,
      { "pLMNAreaBased", "s1ap.pLMNAreaBased_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "PLMNAreaBasedQMC", HFILL }},
    { &hf_s1ap_priorityLevel,
      { "priorityLevel", "s1ap.priorityLevel",
        FT_UINT32, BASE_DEC, VALS(s1ap_PriorityLevel_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pre_emptionCapability,
      { "pre-emptionCapability", "s1ap.pre_emptionCapability",
        FT_UINT32, BASE_DEC, VALS(s1ap_Pre_emptionCapability_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pre_emptionVulnerability,
      { "pre-emptionVulnerability", "s1ap.pre_emptionVulnerability",
        FT_UINT32, BASE_DEC, VALS(s1ap_Pre_emptionVulnerability_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_cellIdentifierAndCELevelForCECapableUEs,
      { "cellIdentifierAndCELevelForCECapableUEs", "s1ap.cellIdentifierAndCELevelForCECapableUEs_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_assistanceDataForRecommendedCells,
      { "assistanceDataForRecommendedCells", "s1ap.assistanceDataForRecommendedCells_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_assistanceDataForCECapableUEs,
      { "assistanceDataForCECapableUEs", "s1ap.assistanceDataForCECapableUEs_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pagingAttemptInformation,
      { "pagingAttemptInformation", "s1ap.pagingAttemptInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_recommendedCellsForPaging,
      { "recommendedCellsForPaging", "s1ap.recommendedCellsForPaging_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Bearers_SubjectToStatusTransferList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RAB_ID,
      { "e-RAB-ID", "s1ap.e_RAB_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uL_COUNTvalue,
      { "uL-COUNTvalue", "s1ap.uL_COUNTvalue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "COUNTvalue", HFILL }},
    { &hf_s1ap_dL_COUNTvalue,
      { "dL-COUNTvalue", "s1ap.dL_COUNTvalue_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "COUNTvalue", HFILL }},
    { &hf_s1ap_receiveStatusofULPDCPSDUs,
      { "receiveStatusofULPDCPSDUs", "s1ap.receiveStatusofULPDCPSDUs",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_Bearers_SubjectToEarlyStatusTransferList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dLCOUNT_PDCP_SNlength,
      { "dLCOUNT-PDCP-SNlength", "s1ap.dLCOUNT_PDCP_SNlength",
        FT_UINT32, BASE_DEC, VALS(s1ap_DLCOUNT_PDCP_SNlength_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_bluetoothMeasConfig,
      { "bluetoothMeasConfig", "s1ap.bluetoothMeasConfig",
        FT_UINT32, BASE_DEC, VALS(s1ap_BluetoothMeasConfig_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_bluetoothMeasConfigNameList,
      { "bluetoothMeasConfigNameList", "s1ap.bluetoothMeasConfigNameList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_bt_rssi,
      { "bt-rssi", "s1ap.bt_rssi",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_bt_rssi_vals), 0,
        "T_bt_rssi", HFILL }},
    { &hf_s1ap_BluetoothMeasConfigNameList_item,
      { "BluetoothName", "s1ap.BluetoothName",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_BPLMNs_item,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellID_Cancelled,
      { "cellID-Cancelled", "s1ap.cellID_Cancelled",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAI_Cancelled,
      { "tAI-Cancelled", "s1ap.tAI_Cancelled",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_emergencyAreaID_Cancelled,
      { "emergencyAreaID-Cancelled", "s1ap.emergencyAreaID_Cancelled",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellID_Broadcast,
      { "cellID-Broadcast", "s1ap.cellID_Broadcast",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAI_Broadcast,
      { "tAI-Broadcast", "s1ap.tAI_Broadcast",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_emergencyAreaID_Broadcast,
      { "emergencyAreaID-Broadcast", "s1ap.emergencyAreaID_Broadcast",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CancelledCellinEAI_item,
      { "CancelledCellinEAI-Item", "s1ap.CancelledCellinEAI_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eCGI,
      { "eCGI", "s1ap.eCGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EUTRAN_CGI", HFILL }},
    { &hf_s1ap_numberOfBroadcasts,
      { "numberOfBroadcasts", "s1ap.numberOfBroadcasts",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CancelledCellinTAI_item,
      { "CancelledCellinTAI-Item", "s1ap.CancelledCellinTAI_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_radioNetwork,
      { "radioNetwork", "s1ap.radioNetwork",
        FT_UINT32, BASE_DEC|BASE_EXT_STRING, &s1ap_CauseRadioNetwork_vals_ext, 0,
        "CauseRadioNetwork", HFILL }},
    { &hf_s1ap_transport,
      { "transport", "s1ap.transport",
        FT_UINT32, BASE_DEC, VALS(s1ap_CauseTransport_vals), 0,
        "CauseTransport", HFILL }},
    { &hf_s1ap_nas,
      { "nas", "s1ap.nas",
        FT_UINT32, BASE_DEC, VALS(s1ap_CauseNas_vals), 0,
        "CauseNas", HFILL }},
    { &hf_s1ap_protocol,
      { "protocol", "s1ap.protocol",
        FT_UINT32, BASE_DEC, VALS(s1ap_CauseProtocol_vals), 0,
        "CauseProtocol", HFILL }},
    { &hf_s1ap_misc,
      { "misc", "s1ap.misc",
        FT_UINT32, BASE_DEC, VALS(s1ap_CauseMisc_vals), 0,
        "CauseMisc", HFILL }},
    { &hf_s1ap_global_Cell_ID,
      { "global-Cell-ID", "s1ap.global_Cell_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EUTRAN_CGI", HFILL }},
    { &hf_s1ap_cELevel,
      { "cELevel", "s1ap.cELevel",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CellID_Broadcast_item,
      { "CellID-Broadcast-Item", "s1ap.CellID_Broadcast_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CellID_Cancelled_item,
      { "CellID-Cancelled-Item", "s1ap.CellID_Cancelled_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellIdListforMDT,
      { "cellIdListforMDT", "s1ap.cellIdListforMDT",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CellIdListforMDT_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellIdListforQMC,
      { "cellIdListforQMC", "s1ap.cellIdListforQMC",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CellIdListforQMC_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cdma2000OneXMEID,
      { "cdma2000OneXMEID", "s1ap.cdma2000OneXMEID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cdma2000OneXMSI,
      { "cdma2000OneXMSI", "s1ap.cdma2000OneXMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cdma2000OneXPilot,
      { "cdma2000OneXPilot", "s1ap.cdma2000OneXPilot",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cell_Size,
      { "cell-Size", "s1ap.cell_Size",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cell_Size_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pLMNidentity,
      { "pLMNidentity", "s1ap.pLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_lAC,
      { "lAC", "s1ap.lAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cI,
      { "cI", "s1ap.cI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_rAC,
      { "rAC", "s1ap.rAC",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CNTypeRestrictions_item,
      { "CNTypeRestrictions-Item", "s1ap.CNTypeRestrictions_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pLMN_Identity,
      { "pLMN-Identity", "s1ap.pLMN_Identity",
        FT_BYTES, BASE_NONE, NULL, 0,
        "PLMNidentity", HFILL }},
    { &hf_s1ap_cNType,
      { "cNType", "s1ap.cNType",
        FT_UINT32, BASE_DEC, VALS(s1ap_CNType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ConnectedengNBList_item,
      { "ConnectedengNBItem", "s1ap.ConnectedengNBItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_en_gNB_ID,
      { "en-gNB-ID", "s1ap.en_gNB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_supportedTAs,
      { "supportedTAs", "s1ap.supportedTAs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sourceNG_RAN_node_ID,
      { "sourceNG-RAN-node-ID", "s1ap.sourceNG_RAN_node_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_Global_RAN_NODE_ID_vals), 0,
        "Global_RAN_NODE_ID", HFILL }},
    { &hf_s1ap_rAN_UE_NGAP_ID,
      { "rAN-UE-NGAP-ID", "s1ap.rAN_UE_NGAP_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CSG_IdList_item,
      { "CSG-IdList-Item", "s1ap.CSG_IdList_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cSG_Id,
      { "cSG-Id", "s1ap.cSG_Id",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pDCP_SN,
      { "pDCP-SN", "s1ap.pDCP_SN",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_hFN,
      { "hFN", "s1ap.hFN",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pDCP_SNExtended,
      { "pDCP-SNExtended", "s1ap.pDCP_SNExtended",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_hFNModified,
      { "hFNModified", "s1ap.hFNModified",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pDCP_SNlength18,
      { "pDCP-SNlength18", "s1ap.pDCP_SNlength18",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_hFNforPDCP_SNlength18,
      { "hFNforPDCP-SNlength18", "s1ap.hFNforPDCP_SNlength18",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_procedureCode,
      { "procedureCode", "s1ap.procedureCode",
        FT_UINT32, BASE_DEC|BASE_EXT_STRING, &s1ap_ProcedureCode_vals_ext, 0,
        NULL, HFILL }},
    { &hf_s1ap_triggeringMessage,
      { "triggeringMessage", "s1ap.triggeringMessage",
        FT_UINT32, BASE_DEC, VALS(s1ap_TriggeringMessage_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_procedureCriticality,
      { "procedureCriticality", "s1ap.procedureCriticality",
        FT_UINT32, BASE_DEC, VALS(s1ap_Criticality_vals), 0,
        "Criticality", HFILL }},
    { &hf_s1ap_iEsCriticalityDiagnostics,
      { "iEsCriticalityDiagnostics", "s1ap.iEsCriticalityDiagnostics",
        FT_UINT32, BASE_DEC, NULL, 0,
        "CriticalityDiagnostics_IE_List", HFILL }},
    { &hf_s1ap_CriticalityDiagnostics_IE_List_item,
      { "CriticalityDiagnostics-IE-Item", "s1ap.CriticalityDiagnostics_IE_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_iECriticality,
      { "iECriticality", "s1ap.iECriticality",
        FT_UINT32, BASE_DEC, VALS(s1ap_Criticality_vals), 0,
        "Criticality", HFILL }},
    { &hf_s1ap_iE_ID,
      { "iE-ID", "s1ap.iE_ID",
        FT_UINT32, BASE_DEC|BASE_EXT_STRING, &s1ap_ProtocolIE_ID_vals_ext, 0,
        "ProtocolIE_ID", HFILL }},
    { &hf_s1ap_typeOfError,
      { "typeOfError", "s1ap.typeOfError",
        FT_UINT32, BASE_DEC, VALS(s1ap_TypeOfError_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_dAPSIndicator,
      { "dAPSIndicator", "s1ap.dAPSIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_dAPSIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_DAPSResponseInfoList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dAPSResponseInfo,
      { "dAPSResponseInfo", "s1ap.dAPSResponseInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dapsresponseindicator,
      { "dapsresponseindicator", "s1ap.dapsresponseindicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_dapsresponseindicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedDCNs_item,
      { "ServedDCNsItem", "s1ap.ServedDCNsItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dCN_ID,
      { "dCN-ID", "s1ap.dCN_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_relativeDCNCapacity,
      { "relativeDCNCapacity", "s1ap.relativeDCNCapacity",
        FT_UINT32, BASE_DEC, NULL, 0,
        "RelativeMMECapacity", HFILL }},
    { &hf_s1ap_dl_NAS_MAC,
      { "dl-NAS-MAC", "s1ap.dl_NAS_MAC",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dLCOUNTValuePDCP_SNlength12,
      { "dLCOUNTValuePDCP-SNlength12", "s1ap.dLCOUNTValuePDCP_SNlength12_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "COUNTvalue", HFILL }},
    { &hf_s1ap_dLCOUNTValuePDCP_SNlength15,
      { "dLCOUNTValuePDCP-SNlength15", "s1ap.dLCOUNTValuePDCP_SNlength15_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "COUNTValueExtended", HFILL }},
    { &hf_s1ap_dLCOUNTValuePDCP_SNlength18,
      { "dLCOUNTValuePDCP-SNlength18", "s1ap.dLCOUNTValuePDCP_SNlength18_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "COUNTvaluePDCP_SNlength18", HFILL }},
    { &hf_s1ap_ECGIList_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PWSfailedECGIList_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyAreaIDList_item,
      { "EmergencyAreaID", "s1ap.EmergencyAreaID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyAreaID_Broadcast_item,
      { "EmergencyAreaID-Broadcast-Item", "s1ap.EmergencyAreaID_Broadcast_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_emergencyAreaID,
      { "emergencyAreaID", "s1ap.emergencyAreaID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_completedCellinEAI,
      { "completedCellinEAI", "s1ap.completedCellinEAI",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyAreaID_Cancelled_item,
      { "EmergencyAreaID-Cancelled-Item", "s1ap.EmergencyAreaID_Cancelled_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cancelledCellinEAI,
      { "cancelledCellinEAI", "s1ap.cancelledCellinEAI",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CompletedCellinEAI_item,
      { "CompletedCellinEAI-Item", "s1ap.CompletedCellinEAI_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ECGI_List_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_EmergencyAreaIDListForRestart_item,
      { "EmergencyAreaID", "s1ap.EmergencyAreaID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_bearers_SubjectToEarlyStatusTransferList,
      { "bearers-SubjectToEarlyStatusTransferList", "s1ap.bearers_SubjectToEarlyStatusTransferList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_macroENB_ID,
      { "macroENB-ID", "s1ap.macroENB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_20", HFILL }},
    { &hf_s1ap_homeENB_ID,
      { "homeENB-ID", "s1ap.homeENB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_28", HFILL }},
    { &hf_s1ap_short_macroENB_ID,
      { "short-macroENB-ID", "s1ap.short_macroENB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_18", HFILL }},
    { &hf_s1ap_long_macroENB_ID,
      { "long-macroENB-ID", "s1ap.long_macroENB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_21", HFILL }},
    { &hf_s1ap_lAI,
      { "lAI", "s1ap.lAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eNB_ID,
      { "eNB-ID", "s1ap.eNB_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_ENB_ID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_GUMMEIList_item,
      { "GUMMEI", "s1ap.GUMMEI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_bearers_SubjectToStatusTransferList,
      { "bearers-SubjectToStatusTransferList", "s1ap.bearers_SubjectToStatusTransferList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBX2TLAs_item,
      { "TransportLayerAddress", "s1ap.TransportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_transfertype,
      { "transfertype", "s1ap.transfertype",
        FT_UINT32, BASE_DEC, VALS(s1ap_EN_DCSONTransferType_vals), 0,
        "EN_DCSONTransferType", HFILL }},
    { &hf_s1ap_sONInformation,
      { "sONInformation", "s1ap.sONInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_x2TNLConfigInfo,
      { "x2TNLConfigInfo", "s1ap.x2TNLConfigInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "X2TNLConfigurationInfo", HFILL }},
    { &hf_s1ap_request,
      { "request", "s1ap.request_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCTransferTypeRequest", HFILL }},
    { &hf_s1ap_reply,
      { "reply", "s1ap.reply_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCTransferTypeReply", HFILL }},
    { &hf_s1ap_sourceeNB,
      { "sourceeNB", "s1ap.sourceeNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCSONeNBIdentification", HFILL }},
    { &hf_s1ap_targetengNB,
      { "targetengNB", "s1ap.targetengNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCSONengNBIdentification", HFILL }},
    { &hf_s1ap_targeteNB,
      { "targeteNB", "s1ap.targeteNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCSONeNBIdentification", HFILL }},
    { &hf_s1ap_associatedTAI,
      { "associatedTAI", "s1ap.associatedTAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TAI", HFILL }},
    { &hf_s1ap_broadcast5GSTAI,
      { "broadcast5GSTAI", "s1ap.broadcast5GSTAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "FiveGSTAI", HFILL }},
    { &hf_s1ap_sourceengNB,
      { "sourceengNB", "s1ap.sourceengNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EN_DCSONengNBIdentification", HFILL }},
    { &hf_s1ap_globaleNBID,
      { "globaleNBID", "s1ap.globaleNBID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "Global_ENB_ID", HFILL }},
    { &hf_s1ap_selectedTAI,
      { "selectedTAI", "s1ap.selectedTAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TAI", HFILL }},
    { &hf_s1ap_globalengNBID,
      { "globalengNBID", "s1ap.globalengNBID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "Global_en_gNB_ID", HFILL }},
    { &hf_s1ap_EPLMNs_item,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABInformationList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dL_Forwarding,
      { "dL-Forwarding", "s1ap.dL_Forwarding",
        FT_UINT32, BASE_DEC, VALS(s1ap_DL_Forwarding_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cause,
      { "cause", "s1ap.cause",
        FT_UINT32, BASE_DEC, VALS(s1ap_Cause_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_qCI,
      { "qCI", "s1ap.qCI",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_allocationRetentionPriority,
      { "allocationRetentionPriority", "s1ap.allocationRetentionPriority_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "AllocationAndRetentionPriority", HFILL }},
    { &hf_s1ap_gbrQosInformation,
      { "gbrQosInformation", "s1ap.gbrQosInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "GBR_QosInformation", HFILL }},
    { &hf_s1ap_E_RABUsageReportList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_startTimestamp,
      { "startTimestamp", "s1ap.startTimestamp",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_endTimestamp,
      { "endTimestamp", "s1ap.endTimestamp",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_usageCountUL,
      { "usageCountUL", "s1ap.usageCountUL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_octet_octets, 0,
        "INTEGER_0_18446744073709551615", HFILL }},
    { &hf_s1ap_usageCountDL,
      { "usageCountDL", "s1ap.usageCountDL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_octet_octets, 0,
        "INTEGER_0_18446744073709551615", HFILL }},
    { &hf_s1ap_cell_ID,
      { "cell-ID", "s1ap.CellIdentity",
        FT_UINT32, BASE_HEX, NULL, 0,
        "CellIdentity", HFILL }},
    { &hf_s1ap_expectedActivity,
      { "expectedActivity", "s1ap.expectedActivity_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "ExpectedUEActivityBehaviour", HFILL }},
    { &hf_s1ap_expectedHOInterval,
      { "expectedHOInterval", "s1ap.expectedHOInterval",
        FT_UINT32, BASE_DEC, VALS(s1ap_ExpectedHOInterval_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_expectedActivityPeriod,
      { "expectedActivityPeriod", "s1ap.expectedActivityPeriod",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_expectedIdlePeriod,
      { "expectedIdlePeriod", "s1ap.expectedIdlePeriod",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_sourceofUEActivityBehaviourInformation,
      { "sourceofUEActivityBehaviourInformation", "s1ap.sourceofUEActivityBehaviourInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_SourceOfUEActivityBehaviourInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_fiveGSTAC,
      { "fiveGSTAC", "s1ap.fiveGSTAC",
        FT_UINT24, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ForbiddenTAs_item,
      { "ForbiddenTAs-Item", "s1ap.ForbiddenTAs_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_forbiddenTACs,
      { "forbiddenTACs", "s1ap.forbiddenTACs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ForbiddenTACs_item,
      { "TAC", "s1ap.TAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ForbiddenLAs_item,
      { "ForbiddenLAs-Item", "s1ap.ForbiddenLAs_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_forbiddenLACs,
      { "forbiddenLACs", "s1ap.forbiddenLACs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ForbiddenLACs_item,
      { "LAC", "s1ap.LAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RAB_MaximumBitrateDL,
      { "e-RAB-MaximumBitrateDL", "s1ap.e_RAB_MaximumBitrateDL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_e_RAB_MaximumBitrateUL,
      { "e-RAB-MaximumBitrateUL", "s1ap.e_RAB_MaximumBitrateUL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_e_RAB_GuaranteedBitrateDL,
      { "e-RAB-GuaranteedBitrateDL", "s1ap.e_RAB_GuaranteedBitrateDL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_e_RAB_GuaranteedBitrateUL,
      { "e-RAB-GuaranteedBitrateUL", "s1ap.e_RAB_GuaranteedBitrateUL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_mME_Group_ID,
      { "mME-Group-ID", "s1ap.mME_Group_ID",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mME_Code,
      { "mME-Code", "s1ap.mME_Code",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_servingPLMN,
      { "servingPLMN", "s1ap.servingPLMN",
        FT_BYTES, BASE_NONE, NULL, 0,
        "PLMNidentity", HFILL }},
    { &hf_s1ap_equivalentPLMNs,
      { "equivalentPLMNs", "s1ap.equivalentPLMNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "EPLMNs", HFILL }},
    { &hf_s1ap_forbiddenTAs,
      { "forbiddenTAs", "s1ap.forbiddenTAs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_forbiddenLAs,
      { "forbiddenLAs", "s1ap.forbiddenLAs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_forbiddenInterRATs,
      { "forbiddenInterRATs", "s1ap.forbiddenInterRATs",
        FT_UINT32, BASE_DEC, VALS(s1ap_ForbiddenInterRATs_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_measurementsToActivate,
      { "measurementsToActivate", "s1ap.measurementsToActivate",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_m1reportingTrigger,
      { "m1reportingTrigger", "s1ap.m1reportingTrigger",
        FT_UINT32, BASE_DEC, VALS(s1ap_M1ReportingTrigger_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m1thresholdeventA2,
      { "m1thresholdeventA2", "s1ap.m1thresholdeventA2_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_m1periodicReporting,
      { "m1periodicReporting", "s1ap.m1periodicReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_recommendENBsForPaging,
      { "recommendENBsForPaging", "s1ap.recommendENBsForPaging_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "RecommendedENBsForPaging", HFILL }},
    { &hf_s1ap_rSRP,
      { "rSRP", "s1ap.rSRP",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_threshold_nr_rsrp_fmt), 0,
        "INTEGER_0_127", HFILL }},
    { &hf_s1ap_rSRQ,
      { "rSRQ", "s1ap.rSRQ",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_threshold_nr_rsrq_fmt), 0,
        "INTEGER_0_127", HFILL }},
    { &hf_s1ap_sINR,
      { "sINR", "s1ap.sINR",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_threshold_nr_sinr_fmt), 0,
        "INTEGER_0_127", HFILL }},
    { &hf_s1ap_interSystemMeasurementParameters,
      { "interSystemMeasurementParameters", "s1ap.interSystemMeasurementParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_measurementDuration,
      { "measurementDuration", "s1ap.measurementDuration",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        "INTEGER_1_100", HFILL }},
    { &hf_s1ap_interSystemMeasurementList,
      { "interSystemMeasurementList", "s1ap.interSystemMeasurementList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_InterSystemMeasurementList_item,
      { "InterSystemMeasurementItem", "s1ap.InterSystemMeasurementItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_freqBandIndicatorNR,
      { "freqBandIndicatorNR", "s1ap.freqBandIndicatorNR",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_1024", HFILL }},
    { &hf_s1ap_sSBfrequencies,
      { "sSBfrequencies", "s1ap.sSBfrequencies",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_maxNARFCN", HFILL }},
    { &hf_s1ap_subcarrierSpacingSSB,
      { "subcarrierSpacingSSB", "s1ap.subcarrierSpacingSSB",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_subcarrierSpacingSSB_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_maxRSIndexCellQual,
      { "maxRSIndexCellQual", "s1ap.maxRSIndexCellQual",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_maxRS_IndexCellQual", HFILL }},
    { &hf_s1ap_sMTC,
      { "sMTC", "s1ap.sMTC",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_threshRS_Index_r15,
      { "threshRS-Index-r15", "s1ap.threshRS_Index_r15",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sSBToMeasure,
      { "sSBToMeasure", "s1ap.sSBToMeasure",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sSRSSIMeasurement,
      { "sSRSSIMeasurement", "s1ap.sSRSSIMeasurement",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_quantityConfigNR_R15,
      { "quantityConfigNR-R15", "s1ap.quantityConfigNR_R15",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_blackCellsToAddModList,
      { "blackCellsToAddModList", "s1ap.blackCellsToAddModList",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_UTRAN_Cell,
      { "e-UTRAN-Cell", "s1ap.e_UTRAN_Cell_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "LastVisitedEUTRANCellInformation", HFILL }},
    { &hf_s1ap_uTRAN_Cell,
      { "uTRAN-Cell", "s1ap.uTRAN_Cell",
        FT_BYTES, BASE_NONE, NULL, 0,
        "LastVisitedUTRANCellInformation", HFILL }},
    { &hf_s1ap_gERAN_Cell,
      { "gERAN-Cell", "s1ap.gERAN_Cell",
        FT_UINT32, BASE_DEC, VALS(s1ap_LastVisitedGERANCellInformation_vals), 0,
        "LastVisitedGERANCellInformation", HFILL }},
    { &hf_s1ap_nG_RAN_Cell,
      { "nG-RAN-Cell", "s1ap.nG_RAN_Cell",
        FT_BYTES, BASE_NONE, NULL, 0,
        "LastVisitedNGRANCellInformation", HFILL }},
    { &hf_s1ap_cellType,
      { "cellType", "s1ap.cellType_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_time_UE_StayedInCell,
      { "time-UE-StayedInCell", "s1ap.time_UE_StayedInCell",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        NULL, HFILL }},
    { &hf_s1ap_undefined,
      { "undefined", "s1ap.undefined_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pattern_period,
      { "pattern-period", "s1ap.pattern_period",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_pattern_period_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pattern_offset,
      { "pattern-offset", "s1ap.pattern_offset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_10239_", HFILL }},
    { &hf_s1ap_loggingInterval,
      { "loggingInterval", "s1ap.loggingInterval",
        FT_UINT32, BASE_DEC, VALS(s1ap_LoggingInterval_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_loggingDuration,
      { "loggingDuration", "s1ap.loggingDuration",
        FT_UINT32, BASE_DEC, VALS(s1ap_LoggingDuration_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_mBSFN_ResultToLog,
      { "mBSFN-ResultToLog", "s1ap.mBSFN_ResultToLog",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_m3period,
      { "m3period", "s1ap.m3period",
        FT_UINT32, BASE_DEC, VALS(s1ap_M3period_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m4period,
      { "m4period", "s1ap.m4period",
        FT_UINT32, BASE_DEC, VALS(s1ap_M4period_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m4_links_to_log,
      { "m4-links-to-log", "s1ap.m4_links_to_log",
        FT_UINT32, BASE_DEC, VALS(s1ap_Links_to_log_vals), 0,
        "Links_to_log", HFILL }},
    { &hf_s1ap_m5period,
      { "m5period", "s1ap.m5period",
        FT_UINT32, BASE_DEC, VALS(s1ap_M5period_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m5_links_to_log,
      { "m5-links-to-log", "s1ap.m5_links_to_log",
        FT_UINT32, BASE_DEC, VALS(s1ap_Links_to_log_vals), 0,
        "Links_to_log", HFILL }},
    { &hf_s1ap_m6report_Interval,
      { "m6report-Interval", "s1ap.m6report_Interval",
        FT_UINT32, BASE_DEC, VALS(s1ap_M6report_Interval_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m6delay_threshold,
      { "m6delay-threshold", "s1ap.m6delay_threshold",
        FT_UINT32, BASE_DEC, VALS(s1ap_M6delay_threshold_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_m6_links_to_log,
      { "m6-links-to-log", "s1ap.m6_links_to_log",
        FT_UINT32, BASE_DEC, VALS(s1ap_Links_to_log_vals), 0,
        "Links_to_log", HFILL }},
    { &hf_s1ap_m7period,
      { "m7period", "s1ap.m7period",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_m7_links_to_log,
      { "m7-links-to-log", "s1ap.m7_links_to_log",
        FT_UINT32, BASE_DEC, VALS(s1ap_Links_to_log_vals), 0,
        "Links_to_log", HFILL }},
    { &hf_s1ap_mdt_Activation,
      { "mdt-Activation", "s1ap.mdt_Activation",
        FT_UINT32, BASE_DEC, VALS(s1ap_MDT_Activation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_areaScopeOfMDT,
      { "areaScopeOfMDT", "s1ap.areaScopeOfMDT",
        FT_UINT32, BASE_DEC, VALS(s1ap_AreaScopeOfMDT_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_mDTMode,
      { "mDTMode", "s1ap.mDTMode",
        FT_UINT32, BASE_DEC, VALS(s1ap_MDTMode_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_MBSFN_ResultToLog_item,
      { "MBSFN-ResultToLogInfo", "s1ap.MBSFN_ResultToLogInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mBSFN_AreaId,
      { "mBSFN-AreaId", "s1ap.mBSFN_AreaId",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_255", HFILL }},
    { &hf_s1ap_carrierFreq,
      { "carrierFreq", "s1ap.carrierFreq",
        FT_UINT32, BASE_DEC, NULL, 0,
        "EARFCN", HFILL }},
    { &hf_s1ap_MDTPLMNList_item,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_immediateMDT,
      { "immediateMDT", "s1ap.immediateMDT_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_loggedMDT,
      { "loggedMDT", "s1ap.loggedMDT_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mDTMode_Extension,
      { "mDTMode-Extension", "s1ap.mDTMode_Extension_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_threshold_RSRP,
      { "threshold-RSRP", "s1ap.threshold_RSRP",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_Threshold_RSRP_fmt), 0,
        NULL, HFILL }},
    { &hf_s1ap_threshold_RSRQ,
      { "threshold-RSRQ", "s1ap.threshold_RSRQ",
        FT_UINT32, BASE_CUSTOM, CF_FUNC(s1ap_Threshold_RSRQ_fmt), 0,
        NULL, HFILL }},
    { &hf_s1ap_global_ENB_ID,
      { "global-ENB-ID", "s1ap.global_ENB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAI,
      { "tAI", "s1ap.tAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_muting_pattern_period,
      { "muting-pattern-period", "s1ap.muting_pattern_period",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_muting_pattern_period_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_muting_pattern_offset,
      { "muting-pattern-offset", "s1ap.muting_pattern_offset",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_10239_", HFILL }},
    { &hf_s1ap_nB_IoT_paging_eDRX_Cycle,
      { "nB-IoT-paging-eDRX-Cycle", "s1ap.nB_IoT_paging_eDRX_Cycle",
        FT_UINT32, BASE_DEC, VALS(s1ap_NB_IoT_Paging_eDRX_Cycle_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_nB_IoT_pagingTimeWindow,
      { "nB-IoT-pagingTimeWindow", "s1ap.nB_IoT_pagingTimeWindow",
        FT_UINT32, BASE_DEC, VALS(s1ap_NB_IoT_PagingTimeWindow_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pLMNIdentity,
      { "pLMNIdentity", "s1ap.pLMNIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nRCellIdentity,
      { "nRCellIdentity", "s1ap.nRCellIdentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nRencryptionAlgorithms,
      { "nRencryptionAlgorithms", "s1ap.nRencryptionAlgorithms",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nRintegrityProtectionAlgorithms,
      { "nRintegrityProtectionAlgorithms", "s1ap.nRintegrityProtectionAlgorithms",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_vehicleUE,
      { "vehicleUE", "s1ap.vehicleUE",
        FT_UINT32, BASE_DEC, VALS(s1ap_VehicleUE_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pedestrianUE,
      { "pedestrianUE", "s1ap.pedestrianUE",
        FT_UINT32, BASE_DEC, VALS(s1ap_PedestrianUE_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_uEaggregateMaximumBitRate,
      { "uEaggregateMaximumBitRate", "s1ap.uEaggregateMaximumBitRate",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_overloadAction,
      { "overloadAction", "s1ap.overloadAction",
        FT_UINT32, BASE_DEC, VALS(s1ap_OverloadAction_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pagingAttemptCount,
      { "pagingAttemptCount", "s1ap.pagingAttemptCount",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_intendedNumberOfPagingAttempts,
      { "intendedNumberOfPagingAttempts", "s1ap.intendedNumberOfPagingAttempts",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nextPagingAreaScope,
      { "nextPagingAreaScope", "s1ap.nextPagingAreaScope",
        FT_UINT32, BASE_DEC, VALS(s1ap_NextPagingAreaScope_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_paging_eDRX_Cycle,
      { "paging-eDRX-Cycle", "s1ap.paging_eDRX_Cycle",
        FT_UINT32, BASE_DEC, VALS(s1ap_Paging_eDRX_Cycle_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pagingTimeWindow,
      { "pagingTimeWindow", "s1ap.pagingTimeWindow",
        FT_UINT32, BASE_DEC, VALS(s1ap_PagingTimeWindow_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_pc5QoSFlowList,
      { "pc5QoSFlowList", "s1ap.pc5QoSFlowList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pc5LinkAggregatedBitRates,
      { "pc5LinkAggregatedBitRates", "s1ap.pc5LinkAggregatedBitRates",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_PC5QoSFlowList_item,
      { "PC5QoSFlowItem", "s1ap.PC5QoSFlowItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pQI,
      { "pQI", "s1ap.pQI",
        FT_UINT32, BASE_DEC, NULL, 0,
        "FiveQI", HFILL }},
    { &hf_s1ap_pc5FlowBitRates,
      { "pc5FlowBitRates", "s1ap.pc5FlowBitRates_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_range,
      { "range", "s1ap.range",
        FT_UINT32, BASE_DEC, VALS(s1ap_Range_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_guaranteedFlowBitRate,
      { "guaranteedFlowBitRate", "s1ap.guaranteedFlowBitRate",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_maximumFlowBitRate,
      { "maximumFlowBitRate", "s1ap.maximumFlowBitRate",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_reportInterval,
      { "reportInterval", "s1ap.reportInterval",
        FT_UINT32, BASE_DEC, VALS(s1ap_ReportIntervalMDT_vals), 0,
        "ReportIntervalMDT", HFILL }},
    { &hf_s1ap_reportAmount,
      { "reportAmount", "s1ap.reportAmount",
        FT_UINT32, BASE_DEC, VALS(s1ap_ReportAmountMDT_vals), 0,
        "ReportAmountMDT", HFILL }},
    { &hf_s1ap_plmnListforQMC,
      { "plmnListforQMC", "s1ap.plmnListforQMC",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_PLMNListforQMC_item,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_proSeDirectDiscovery,
      { "proSeDirectDiscovery", "s1ap.proSeDirectDiscovery",
        FT_UINT32, BASE_DEC, VALS(s1ap_ProSeDirectDiscovery_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_proSeDirectCommunication,
      { "proSeDirectCommunication", "s1ap.proSeDirectCommunication",
        FT_UINT32, BASE_DEC, VALS(s1ap_ProSeDirectCommunication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_nCGI,
      { "nCGI", "s1ap.nCGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "NR_CGI", HFILL }},
    { &hf_s1ap_recommendedCellList,
      { "recommendedCellList", "s1ap.recommendedCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RecommendedCellList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eUTRAN_CGI,
      { "eUTRAN-CGI", "s1ap.eUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_timeStayedInCell,
      { "timeStayedInCell", "s1ap.timeStayedInCell",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_4095", HFILL }},
    { &hf_s1ap_recommendedENBList,
      { "recommendedENBList", "s1ap.recommendedENBList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_RecommendedENBList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mMEPagingTarget,
      { "mMEPagingTarget", "s1ap.mMEPagingTarget",
        FT_UINT32, BASE_DEC, VALS(s1ap_MMEPagingTarget_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_eventType,
      { "eventType", "s1ap.eventType",
        FT_UINT32, BASE_DEC, VALS(s1ap_EventType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_reportArea,
      { "reportArea", "s1ap.reportArea",
        FT_UINT32, BASE_DEC, VALS(s1ap_ReportArea_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_rIMInformation,
      { "rIMInformation", "s1ap.rIMInformation",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_rIMRoutingAddress,
      { "rIMRoutingAddress", "s1ap.rIMRoutingAddress",
        FT_UINT32, BASE_DEC, VALS(s1ap_RIMRoutingAddress_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_gERAN_Cell_ID,
      { "gERAN-Cell-ID", "s1ap.gERAN_Cell_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_targetRNC_ID,
      { "targetRNC-ID", "s1ap.targetRNC_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eHRPD_Sector_ID,
      { "eHRPD-Sector-ID", "s1ap.eHRPD_Sector_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_16", HFILL }},
    { &hf_s1ap_uE_RLF_Report_Container,
      { "uE-RLF-Report-Container", "s1ap.uE_RLF_Report_Container",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uE_RLF_Report_Container_for_extended_bands,
      { "uE-RLF-Report-Container-for-extended-bands", "s1ap.uE_RLF_Report_Container_for_extended_bands",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ECGIListForRestart_item,
      { "EUTRAN-CGI", "s1ap.EUTRAN_CGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nextHopChainingCount,
      { "nextHopChainingCount", "s1ap.nextHopChainingCount",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_7", HFILL }},
    { &hf_s1ap_nextHopParameter,
      { "nextHopParameter", "s1ap.nextHopParameter",
        FT_BYTES, BASE_NONE, NULL, 0,
        "SecurityKey", HFILL }},
    { &hf_s1ap_SecondaryRATDataUsageReportList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_secondaryRATType,
      { "secondaryRATType", "s1ap.secondaryRATType",
        FT_UINT32, BASE_DEC, VALS(s1ap_SecondaryRATType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RABUsageReportList,
      { "e-RABUsageReportList", "s1ap.e_RABUsageReportList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sONInformationRequest,
      { "sONInformationRequest", "s1ap.sONInformationRequest",
        FT_UINT32, BASE_DEC, VALS(s1ap_SONInformationRequest_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_sONInformationReply,
      { "sONInformationReply", "s1ap.sONInformationReply_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sONInformation_Extension,
      { "sONInformation-Extension", "s1ap.sONInformation_Extension_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_x2TNLConfigurationInfo,
      { "x2TNLConfigurationInfo", "s1ap.x2TNLConfigurationInfo_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_rLFReportInformation,
      { "rLFReportInformation", "s1ap.rLFReportInformation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_targeteNB_ID,
      { "targeteNB-ID", "s1ap.targeteNB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sourceeNB_ID,
      { "sourceeNB-ID", "s1ap.sourceeNB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sourceStratumLevel,
      { "sourceStratumLevel", "s1ap.sourceStratumLevel",
        FT_UINT32, BASE_DEC, NULL, 0,
        "StratumLevel", HFILL }},
    { &hf_s1ap_listeningSubframePattern,
      { "listeningSubframePattern", "s1ap.listeningSubframePattern_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_aggressoreCGI_List,
      { "aggressoreCGI-List", "s1ap.aggressoreCGI_List",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ECGI_List", HFILL }},
    { &hf_s1ap_selected_TAI,
      { "selected-TAI", "s1ap.selected_TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TAI", HFILL }},
    { &hf_s1ap_sourceNgRanNode_ID,
      { "sourceNgRanNode-ID", "s1ap.sourceNgRanNode_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_sourceNodeID_Extension,
      { "sourceNodeID-Extension", "s1ap.sourceNodeID_Extension_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_rRC_Container,
      { "rRC-Container", "s1ap.rRC_Container",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RABInformationList,
      { "e-RABInformationList", "s1ap.e_RABInformationList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_targetCell_ID,
      { "targetCell-ID", "s1ap.targetCell_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EUTRAN_CGI", HFILL }},
    { &hf_s1ap_subscriberProfileIDforRFP,
      { "subscriberProfileIDforRFP", "s1ap.subscriberProfileIDforRFP",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uE_HistoryInformation,
      { "uE-HistoryInformation", "s1ap.uE_HistoryInformation",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_global_RAN_NODE_ID,
      { "global-RAN-NODE-ID", "s1ap.global_RAN_NODE_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_Global_RAN_NODE_ID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_selected_TAI_01,
      { "selected-TAI", "s1ap.selected_TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "FiveGSTAI", HFILL }},
    { &hf_s1ap_ServedGUMMEIs_item,
      { "ServedGUMMEIsItem", "s1ap.ServedGUMMEIsItem_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_servedPLMNs,
      { "servedPLMNs", "s1ap.servedPLMNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_servedGroupIDs,
      { "servedGroupIDs", "s1ap.servedGroupIDs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_servedMMECs,
      { "servedMMECs", "s1ap.servedMMECs",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedGroupIDs_item,
      { "MME-Group-ID", "s1ap.MME_Group_ID",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedMMECs_item,
      { "MME-Code", "s1ap.MME_Code",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ServedPLMNs_item,
      { "PLMNidentity", "s1ap.PLMNidentity",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_periodicCommunicationIndicator,
      { "periodicCommunicationIndicator", "s1ap.periodicCommunicationIndicator",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_periodicCommunicationIndicator_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_periodicTime,
      { "periodicTime", "s1ap.periodicTime",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        "INTEGER_1_3600_", HFILL }},
    { &hf_s1ap_scheduledCommunicationTime,
      { "scheduledCommunicationTime", "s1ap.scheduledCommunicationTime_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_stationaryIndication,
      { "stationaryIndication", "s1ap.stationaryIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_stationaryIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_trafficProfile,
      { "trafficProfile", "s1ap.trafficProfile",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_trafficProfile_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_batteryIndication,
      { "batteryIndication", "s1ap.batteryIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_batteryIndication_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_dayofWeek,
      { "dayofWeek", "s1ap.dayofWeek",
        FT_BYTES, BASE_NONE, NULL, 0,
        "BIT_STRING_SIZE_7", HFILL }},
    { &hf_s1ap_timeofDayStart,
      { "timeofDayStart", "s1ap.timeofDayStart",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        "INTEGER_0_86399_", HFILL }},
    { &hf_s1ap_timeofDayEnd,
      { "timeofDayEnd", "s1ap.timeofDayEnd",
        FT_UINT32, BASE_DEC|BASE_UNIT_STRING, &units_seconds, 0,
        "INTEGER_0_86399_", HFILL }},
    { &hf_s1ap_SupportedTAs_item,
      { "SupportedTAs-Item", "s1ap.SupportedTAs_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAC,
      { "tAC", "s1ap.tAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_broadcastPLMNs,
      { "broadcastPLMNs", "s1ap.broadcastPLMNs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "BPLMNs", HFILL }},
    { &hf_s1ap_stratumLevel,
      { "stratumLevel", "s1ap.stratumLevel",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_synchronisationStatus,
      { "synchronisationStatus", "s1ap.synchronisationStatus",
        FT_UINT32, BASE_DEC, VALS(s1ap_SynchronisationStatus_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_mMEC,
      { "mMEC", "s1ap.mMEC",
        FT_UINT8, BASE_DEC_HEX, NULL, 0,
        "MME_Code", HFILL }},
    { &hf_s1ap_tAIListforMDT,
      { "tAIListforMDT", "s1ap.tAIListforMDT",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIListforMDT_item,
      { "TAI", "s1ap.TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIListforWarning_item,
      { "TAI", "s1ap.TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAI_Broadcast_item,
      { "TAI-Broadcast-Item", "s1ap.TAI_Broadcast_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_completedCellinTAI,
      { "completedCellinTAI", "s1ap.completedCellinTAI",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAI_Cancelled_item,
      { "TAI-Cancelled-Item", "s1ap.TAI_Cancelled_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cancelledCellinTAI,
      { "cancelledCellinTAI", "s1ap.cancelledCellinTAI",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAListforMDT,
      { "tAListforMDT", "s1ap.tAListforMDT",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAListforMDT_item,
      { "TAC", "s1ap.TAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAListforQMC,
      { "tAListforQMC", "s1ap.tAListforQMC",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAListforQMC_item,
      { "TAC", "s1ap.TAC",
        FT_UINT16, BASE_DEC_HEX, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tAIListforQMC,
      { "tAIListforQMC", "s1ap.tAIListforQMC",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIListforQMC_item,
      { "TAI", "s1ap.TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CompletedCellinTAI_item,
      { "CompletedCellinTAI-Item", "s1ap.CompletedCellinTAI_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cGI,
      { "cGI", "s1ap.cGI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_targetgNgRanNode_ID,
      { "targetgNgRanNode-ID", "s1ap.targetgNgRanNode_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TargetNgRanNode_ID", HFILL }},
    { &hf_s1ap_rNC_ID,
      { "rNC-ID", "s1ap.rNC_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_extendedRNC_ID,
      { "extendedRNC-ID", "s1ap.extendedRNC_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_gNB,
      { "gNB", "s1ap.gNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ng_eNB,
      { "ng-eNB", "s1ap.ng_eNB_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_global_gNB_ID,
      { "global-gNB-ID", "s1ap.global_gNB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_gNB_ID,
      { "gNB-ID", "s1ap.gNB_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_GNB_Identity_vals), 0,
        "GNB_Identity", HFILL }},
    { &hf_s1ap_gNB_ID_01,
      { "gNB-ID", "s1ap.gNB_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_global_ng_eNB_ID,
      { "global-ng-eNB-ID", "s1ap.global_ng_eNB_ID_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "Global_ENB_ID", HFILL }},
    { &hf_s1ap_measurementThreshold,
      { "measurementThreshold", "s1ap.measurementThreshold",
        FT_UINT32, BASE_DEC, VALS(s1ap_MeasurementThresholdA2_vals), 0,
        "MeasurementThresholdA2", HFILL }},
    { &hf_s1ap_transportLayerAddress,
      { "transportLayerAddress", "s1ap.transportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uL_GTP_TEID,
      { "uL-GTP-TEID", "s1ap.uL_GTP_TEID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "GTP_TEID", HFILL }},
    { &hf_s1ap_e_UTRAN_Trace_ID,
      { "e-UTRAN-Trace-ID", "s1ap.e_UTRAN_Trace_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_interfacesToTrace,
      { "interfacesToTrace", "s1ap.interfacesToTrace",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_traceDepth,
      { "traceDepth", "s1ap.traceDepth",
        FT_UINT32, BASE_DEC, VALS(s1ap_TraceDepth_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_traceCollectionEntityIPAddress,
      { "traceCollectionEntityIPAddress", "s1ap.traceCollectionEntityIPAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        "TransportLayerAddress", HFILL }},
    { &hf_s1ap_uDP_Port_Number,
      { "uDP-Port-Number", "s1ap.uDP_Port_Number",
        FT_UINT16, BASE_DEC, NULL, 0,
        "Port_Number", HFILL }},
    { &hf_s1ap_TAIListForRestart_item,
      { "TAI", "s1ap.TAI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uEaggregateMaximumBitRateDL,
      { "uEaggregateMaximumBitRateDL", "s1ap.uEaggregateMaximumBitRateDL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_uEaggregateMaximumBitRateUL,
      { "uEaggregateMaximumBitRateUL", "s1ap.uEaggregateMaximumBitRateUL",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_containerForAppLayerMeasConfig,
      { "containerForAppLayerMeasConfig", "s1ap.containerForAppLayerMeasConfig",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING_SIZE_1_1000", HFILL }},
    { &hf_s1ap_areaScopeOfQMC,
      { "areaScopeOfQMC", "s1ap.areaScopeOfQMC",
        FT_UINT32, BASE_DEC, VALS(s1ap_AreaScopeOfQMC_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_uE_S1AP_ID_pair,
      { "uE-S1AP-ID-pair", "s1ap.uE_S1AP_ID_pair_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mME_UE_S1AP_ID,
      { "mME-UE-S1AP-ID", "s1ap.MME_UE_S1AP_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eNB_UE_S1AP_ID,
      { "eNB-UE-S1AP-ID", "s1ap.ENB_UE_S1AP_ID",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_HistoryInformation_item,
      { "LastVisitedCell-Item", "s1ap.LastVisitedCell_Item",
        FT_UINT32, BASE_DEC, VALS(s1ap_LastVisitedCell_Item_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_s_TMSI,
      { "s-TMSI", "s1ap.s_TMSI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_iMSI,
      { "iMSI", "s1ap.iMSI",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_encryptionAlgorithms,
      { "encryptionAlgorithms", "s1ap.encryptionAlgorithms",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_integrityProtectionAlgorithms,
      { "integrityProtectionAlgorithms", "s1ap.integrityProtectionAlgorithms",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uESidelinkAggregateMaximumBitRate,
      { "uESidelinkAggregateMaximumBitRate", "s1ap.uESidelinkAggregateMaximumBitRate",
        FT_UINT64, BASE_DEC|BASE_UNIT_STRING, &units_bit_sec, 0,
        "BitRate", HFILL }},
    { &hf_s1ap_ul_NAS_MAC,
      { "ul-NAS-MAC", "s1ap.ul_NAS_MAC",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ul_NAS_Count,
      { "ul-NAS-Count", "s1ap.ul_NAS_Count",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eutran_cgi,
      { "eutran-cgi", "s1ap.eutran_cgi_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_tai,
      { "tai", "s1ap.tai_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellIDList,
      { "cellIDList", "s1ap.cellIDList",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ECGIList", HFILL }},
    { &hf_s1ap_trackingAreaListforWarning,
      { "trackingAreaListforWarning", "s1ap.trackingAreaListforWarning",
        FT_UINT32, BASE_DEC, NULL, 0,
        "TAIListforWarning", HFILL }},
    { &hf_s1ap_emergencyAreaIDList,
      { "emergencyAreaIDList", "s1ap.emergencyAreaIDList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_wlanMeasConfig,
      { "wlanMeasConfig", "s1ap.wlanMeasConfig",
        FT_UINT32, BASE_DEC, VALS(s1ap_WLANMeasConfig_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_wlanMeasConfigNameList,
      { "wlanMeasConfigNameList", "s1ap.wlanMeasConfigNameList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_wlan_rssi,
      { "wlan-rssi", "s1ap.wlan_rssi",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_wlan_rssi_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_wlan_rtt,
      { "wlan-rtt", "s1ap.wlan_rtt",
        FT_UINT32, BASE_DEC, VALS(s1ap_T_wlan_rtt_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_WLANMeasConfigNameList_item,
      { "WLANName", "s1ap.WLANName",
        FT_STRING, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pagingProbabilityInformation,
      { "pagingProbabilityInformation", "s1ap.pagingProbabilityInformation",
        FT_UINT32, BASE_DEC, VALS(s1ap_PagingProbabilityInformation_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_eNBX2TransportLayerAddresses,
      { "eNBX2TransportLayerAddresses", "s1ap.eNBX2TransportLayerAddresses",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ENBX2TLAs", HFILL }},
    { &hf_s1ap_ENBX2ExtTLAs_item,
      { "ENBX2ExtTLA", "s1ap.ENBX2ExtTLA_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_iPsecTLA,
      { "iPsecTLA", "s1ap.iPsecTLA",
        FT_BYTES, BASE_NONE, NULL, 0,
        "TransportLayerAddress", HFILL }},
    { &hf_s1ap_gTPTLAa,
      { "gTPTLAa", "s1ap.gTPTLAa",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ENBX2GTPTLAs", HFILL }},
    { &hf_s1ap_ENBX2GTPTLAs_item,
      { "TransportLayerAddress", "s1ap.TransportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ENBIndirectX2TransportLayerAddresses_item,
      { "TransportLayerAddress", "s1ap.TransportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_protocolIEs,
      { "protocolIEs", "s1ap.protocolIEs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "ProtocolIE_Container", HFILL }},
    { &hf_s1ap_dL_transportLayerAddress,
      { "dL-transportLayerAddress", "s1ap.dL_transportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        "TransportLayerAddress", HFILL }},
    { &hf_s1ap_dL_gTP_TEID,
      { "dL-gTP-TEID", "s1ap.dL_gTP_TEID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "GTP_TEID", HFILL }},
    { &hf_s1ap_uL_TransportLayerAddress,
      { "uL-TransportLayerAddress", "s1ap.uL_TransportLayerAddress",
        FT_BYTES, BASE_NONE, NULL, 0,
        "TransportLayerAddress", HFILL }},
    { &hf_s1ap_gTP_TEID,
      { "gTP-TEID", "s1ap.gTP_TEID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RABlevelQosParameters,
      { "e-RABlevelQosParameters", "s1ap.e_RABlevelQosParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupListBearerSUReq_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RABlevelQoSParameters,
      { "e-RABlevelQoSParameters", "s1ap.e_RABlevelQoSParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_nAS_PDU,
      { "nAS-PDU", "s1ap.nAS_PDU",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupListBearerSURes_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeModifiedListBearerModReq_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_e_RABLevelQoSParameters,
      { "e-RABLevelQoSParameters", "s1ap.e_RABLevelQoSParameters_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyListBearerModRes_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABReleaseListBearerRelComp_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABToBeSetupListCtxtSUReq_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABSetupListCtxtSURes_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_TAIList_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_s1_Interface,
      { "s1-Interface", "s1ap.s1_Interface",
        FT_UINT32, BASE_DEC, VALS(s1ap_ResetAll_vals), 0,
        "ResetAll", HFILL }},
    { &hf_s1ap_partOfS1_Interface,
      { "partOfS1-Interface", "s1ap.partOfS1_Interface",
        FT_UINT32, BASE_DEC, NULL, 0,
        "UE_associatedLogicalS1_ConnectionListRes", HFILL }},
    { &hf_s1ap_UE_associatedLogicalS1_ConnectionListRes_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_UE_associatedLogicalS1_ConnectionListResAck_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_rIMTransfer,
      { "rIMTransfer", "s1ap.rIMTransfer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_privateIEs,
      { "privateIEs", "s1ap.privateIEs",
        FT_UINT32, BASE_DEC, NULL, 0,
        "PrivateIE_Container", HFILL }},
    { &hf_s1ap_dL_GTP_TEID,
      { "dL-GTP-TEID", "s1ap.dL_GTP_TEID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "GTP_TEID", HFILL }},
    { &hf_s1ap_cSGMembershipStatus,
      { "cSGMembershipStatus", "s1ap.cSGMembershipStatus",
        FT_UINT32, BASE_DEC, VALS(s1ap_CSGMembershipStatus_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_cellAccessMode,
      { "cellAccessMode", "s1ap.cellAccessMode",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellAccessMode_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_E_RABModifyListBearerModConf_item,
      { "ProtocolIE-SingleContainer", "s1ap.ProtocolIE_SingleContainer_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_initiatingMessage,
      { "initiatingMessage", "s1ap.initiatingMessage_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_successfulOutcome,
      { "successfulOutcome", "s1ap.successfulOutcome_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_unsuccessfulOutcome,
      { "unsuccessfulOutcome", "s1ap.unsuccessfulOutcome_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_initiatingMessagevalue,
      { "value", "s1ap.value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "InitiatingMessage_value", HFILL }},
    { &hf_s1ap_successfulOutcome_value,
      { "value", "s1ap.value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "SuccessfulOutcome_value", HFILL }},
    { &hf_s1ap_unsuccessfulOutcome_value,
      { "value", "s1ap.value_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "UnsuccessfulOutcome_value", HFILL }},
    { &hf_s1ap_cellLoadReporting,
      { "cellLoadReporting", "s1ap.cellLoadReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_multiCellLoadReporting,
      { "multiCellLoadReporting", "s1ap.multiCellLoadReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "MultiCellLoadReportingRequest", HFILL }},
    { &hf_s1ap_eventTriggeredCellLoadReporting,
      { "eventTriggeredCellLoadReporting", "s1ap.eventTriggeredCellLoadReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EventTriggeredCellLoadReportingRequest", HFILL }},
    { &hf_s1ap_hOReporting,
      { "hOReporting", "s1ap.hOReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "HOReport", HFILL }},
    { &hf_s1ap_eutranCellActivation,
      { "eutranCellActivation", "s1ap.eutranCellActivation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellActivationRequest", HFILL }},
    { &hf_s1ap_energySavingsIndication,
      { "energySavingsIndication", "s1ap.energySavingsIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellStateIndication", HFILL }},
    { &hf_s1ap_failureEventReporting,
      { "failureEventReporting", "s1ap.failureEventReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_FailureEventReport_vals), 0,
        "FailureEventReport", HFILL }},
    { &hf_s1ap_cellLoadReporting_01,
      { "cellLoadReporting", "s1ap.cellLoadReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellLoadReportingResponse_vals), 0,
        "CellLoadReportingResponse", HFILL }},
    { &hf_s1ap_multiCellLoadReporting_01,
      { "multiCellLoadReporting", "s1ap.multiCellLoadReporting",
        FT_UINT32, BASE_DEC, NULL, 0,
        "MultiCellLoadReportingResponse", HFILL }},
    { &hf_s1ap_eventTriggeredCellLoadReporting_01,
      { "eventTriggeredCellLoadReporting", "s1ap.eventTriggeredCellLoadReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EventTriggeredCellLoadReportingResponse", HFILL }},
    { &hf_s1ap_hOReporting_01,
      { "hOReporting", "s1ap.hOReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eutranCellActivation_01,
      { "eutranCellActivation", "s1ap.eutranCellActivation_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "CellActivationResponse", HFILL }},
    { &hf_s1ap_energySavingsIndication_01,
      { "energySavingsIndication", "s1ap.energySavingsIndication_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_failureEventReporting_01,
      { "failureEventReporting", "s1ap.failureEventReporting_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cellLoadReporting_02,
      { "cellLoadReporting", "s1ap.cellLoadReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellLoadReportingCause_vals), 0,
        "CellLoadReportingCause", HFILL }},
    { &hf_s1ap_multiCellLoadReporting_02,
      { "multiCellLoadReporting", "s1ap.multiCellLoadReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellLoadReportingCause_vals), 0,
        "CellLoadReportingCause", HFILL }},
    { &hf_s1ap_eventTriggeredCellLoadReporting_02,
      { "eventTriggeredCellLoadReporting", "s1ap.eventTriggeredCellLoadReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellLoadReportingCause_vals), 0,
        "CellLoadReportingCause", HFILL }},
    { &hf_s1ap_hOReporting_02,
      { "hOReporting", "s1ap.hOReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_HOReportingCause_vals), 0,
        "HOReportingCause", HFILL }},
    { &hf_s1ap_eutranCellActivation_02,
      { "eutranCellActivation", "s1ap.eutranCellActivation",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellActivationCause_vals), 0,
        "CellActivationCause", HFILL }},
    { &hf_s1ap_energySavingsIndication_02,
      { "energySavingsIndication", "s1ap.energySavingsIndication",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellStateIndicationCause_vals), 0,
        "CellStateIndicationCause", HFILL }},
    { &hf_s1ap_failureEventReporting_02,
      { "failureEventReporting", "s1ap.failureEventReporting",
        FT_UINT32, BASE_DEC, VALS(s1ap_FailureEventReportingCause_vals), 0,
        "FailureEventReportingCause", HFILL }},
    { &hf_s1ap_eUTRAN,
      { "eUTRAN", "s1ap.eUTRAN_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EUTRANcellLoadReportingResponse", HFILL }},
    { &hf_s1ap_uTRAN,
      { "uTRAN", "s1ap.uTRAN",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_gERAN,
      { "gERAN", "s1ap.gERAN",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_eHRPD,
      { "eHRPD", "s1ap.eHRPD_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EHRPDSectorLoadReportingResponse", HFILL }},
    { &hf_s1ap_compositeAvailableCapacityGroup,
      { "compositeAvailableCapacityGroup", "s1ap.compositeAvailableCapacityGroup",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cell_ID_01,
      { "cell-ID", "s1ap.cell_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_eUTRANcellLoadReportingResponse,
      { "eUTRANcellLoadReportingResponse", "s1ap.eUTRANcellLoadReportingResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eUTRAN_01,
      { "eUTRAN", "s1ap.eUTRAN",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_eHRPD_01,
      { "eHRPD", "s1ap.eHRPD",
        FT_BYTES, BASE_NONE, NULL, 0,
        "EHRPD_Sector_ID", HFILL }},
    { &hf_s1ap_RequestedCellList_item,
      { "IRAT-Cell-ID", "s1ap.IRAT_Cell_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_IRAT_Cell_ID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_requestedCellList,
      { "requestedCellList", "s1ap.requestedCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_cell_ID_02,
      { "cell-ID", "s1ap.cell_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_IRAT_Cell_ID_vals), 0,
        "IRAT_Cell_ID", HFILL }},
    { &hf_s1ap_ReportingCellList_item,
      { "ReportingCellList-Item", "s1ap.ReportingCellList_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_MultiCellLoadReportingResponse_item,
      { "MultiCellLoadReportingResponse-Item", "s1ap.MultiCellLoadReportingResponse_Item",
        FT_UINT32, BASE_DEC, VALS(s1ap_MultiCellLoadReportingResponse_Item_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_eUTRANResponse,
      { "eUTRANResponse", "s1ap.eUTRANResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_uTRANResponse,
      { "uTRANResponse", "s1ap.uTRANResponse",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_gERANResponse,
      { "gERANResponse", "s1ap.gERANResponse",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_eHRPD_02,
      { "eHRPD", "s1ap.eHRPD_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EHRPDMultiSectorLoadReportingResponseItem", HFILL }},
    { &hf_s1ap_numberOfMeasurementReportingLevels,
      { "numberOfMeasurementReportingLevels", "s1ap.numberOfMeasurementReportingLevels",
        FT_UINT32, BASE_DEC, VALS(s1ap_NumberOfMeasurementReportingLevels_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_cellLoadReportingResponse,
      { "cellLoadReportingResponse", "s1ap.cellLoadReportingResponse",
        FT_UINT32, BASE_DEC, VALS(s1ap_CellLoadReportingResponse_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_overloadFlag,
      { "overloadFlag", "s1ap.overloadFlag",
        FT_UINT32, BASE_DEC, VALS(s1ap_OverloadFlag_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_hoType,
      { "hoType", "s1ap.hoType",
        FT_UINT32, BASE_DEC, VALS(s1ap_HoType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_hoReportType,
      { "hoReportType", "s1ap.hoReportType",
        FT_UINT32, BASE_DEC, VALS(s1ap_HoReportType_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_hosourceID,
      { "hosourceID", "s1ap.hosourceID",
        FT_UINT32, BASE_DEC, VALS(s1ap_IRAT_Cell_ID_vals), 0,
        "IRAT_Cell_ID", HFILL }},
    { &hf_s1ap_hoTargetID,
      { "hoTargetID", "s1ap.hoTargetID",
        FT_UINT32, BASE_DEC, VALS(s1ap_IRAT_Cell_ID_vals), 0,
        "IRAT_Cell_ID", HFILL }},
    { &hf_s1ap_candidateCellList,
      { "candidateCellList", "s1ap.candidateCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_candidatePCIList,
      { "candidatePCIList", "s1ap.candidatePCIList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_CandidateCellList_item,
      { "IRAT-Cell-ID", "s1ap.IRAT_Cell_ID",
        FT_UINT32, BASE_DEC, VALS(s1ap_IRAT_Cell_ID_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_CandidatePCIList_item,
      { "CandidatePCI", "s1ap.CandidatePCI_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_pCI,
      { "pCI", "s1ap.pCI",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_0_503", HFILL }},
    { &hf_s1ap_eARFCN,
      { "eARFCN", "s1ap.eARFCN",
        FT_BYTES, BASE_NONE, NULL, 0,
        "OCTET_STRING", HFILL }},
    { &hf_s1ap_cellsToActivateList,
      { "cellsToActivateList", "s1ap.cellsToActivateList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_minimumActivationTime,
      { "minimumActivationTime", "s1ap.minimumActivationTime",
        FT_UINT32, BASE_DEC, NULL, 0,
        "INTEGER_1_60", HFILL }},
    { &hf_s1ap_CellsToActivateList_item,
      { "CellsToActivateList-Item", "s1ap.CellsToActivateList_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_activatedCellsList,
      { "activatedCellsList", "s1ap.activatedCellsList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_ActivatedCellsList_item,
      { "ActivatedCellsList-Item", "s1ap.ActivatedCellsList_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_notificationCellList,
      { "notificationCellList", "s1ap.notificationCellList",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_NotificationCellList_item,
      { "NotificationCellList-Item", "s1ap.NotificationCellList_Item_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_notifyFlag,
      { "notifyFlag", "s1ap.notifyFlag",
        FT_UINT32, BASE_DEC, VALS(s1ap_NotifyFlag_vals), 0,
        NULL, HFILL }},
    { &hf_s1ap_tooEarlyInterRATHOReportFromEUTRAN,
      { "tooEarlyInterRATHOReportFromEUTRAN", "s1ap.tooEarlyInterRATHOReportFromEUTRAN_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "TooEarlyInterRATHOReportReportFromEUTRAN", HFILL }},
    { &hf_s1ap_uERLFReportContainer,
      { "uERLFReportContainer", "s1ap.uERLFReportContainer",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_mobilityInformation,
      { "mobilityInformation", "s1ap.mobilityInformation",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_dL_EHRPD_CompositeAvailableCapacity,
      { "dL-EHRPD-CompositeAvailableCapacity", "s1ap.dL_EHRPD_CompositeAvailableCapacity_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EHRPDCompositeAvailableCapacity", HFILL }},
    { &hf_s1ap_uL_EHRPD_CompositeAvailableCapacity,
      { "uL-EHRPD-CompositeAvailableCapacity", "s1ap.uL_EHRPD_CompositeAvailableCapacity_element",
        FT_NONE, BASE_NONE, NULL, 0,
        "EHRPDCompositeAvailableCapacity", HFILL }},
    { &hf_s1ap_eHRPDSectorCapacityClassValue,
      { "eHRPDSectorCapacityClassValue", "s1ap.eHRPDSectorCapacityClassValue",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eHRPDCapacityValue,
      { "eHRPDCapacityValue", "s1ap.eHRPDCapacityValue",
        FT_UINT32, BASE_DEC, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eHRPD_Sector_ID_01,
      { "eHRPD-Sector-ID", "s1ap.eHRPD_Sector_ID",
        FT_BYTES, BASE_NONE, NULL, 0,
        NULL, HFILL }},
    { &hf_s1ap_eHRPDSectorLoadReportingResponse,
      { "eHRPDSectorLoadReportingResponse", "s1ap.eHRPDSectorLoadReportingResponse_element",
        FT_NONE, BASE_NONE, NULL, 0,
        NULL, HFILL }},

/*--- End of included file: packet-s1ap-hfarr.c ---*/
#line 728 "./asn1/s1ap/packet-s1ap-template.c"
  };

  /* List of subtrees */
  static gint *ett[] = {
    &ett_s1ap,
    &ett_s1ap_TransportLayerAddress,
    &ett_s1ap_ToTargetTransparentContainer,
    &ett_s1ap_ToSourceTransparentContainer,
    &ett_s1ap_RRCContainer,
    &ett_s1ap_UERadioCapability,
    &ett_s1ap_RIMInformation,
    &ett_s1ap_Cdma2000PDU,
    &ett_s1ap_Cdma2000SectorID,
    &ett_s1ap_UERadioPagingInformation,
    &ett_s1ap_UE_HistoryInformationFromTheUE,
    &ett_s1ap_CELevel,
    &ett_s1ap_UE_RLF_Report_Container,
    &ett_s1ap_UE_RLF_Report_Container_for_extended_bands,
    &ett_s1ap_S1_Message,
    &ett_s1ap_E_UTRAN_Trace_ID,
    &ett_s1ap_InterfacesToTrace,
    &ett_s1ap_EncryptionAlgorithms,
    &ett_s1ap_IntegrityProtectionAlgorithms,
    &ett_s1ap_LastVisitedNGRANCellInformation,
    &ett_s1ap_LastVisitedUTRANCellInformation,
    &ett_s1ap_SerialNumber,
    &ett_s1ap_WarningType,
    &ett_s1ap_DataCodingScheme,
    &ett_s1ap_WarningMessageContents,
    &ett_s1ap_MSClassmark,
    &ett_s1ap_MeasurementsToActivate,
    &ett_s1ap_MDT_Location_Info,
    &ett_s1ap_IMSI,
    &ett_s1ap_NASSecurityParameters,
    &ett_s1ap_NRencryptionAlgorithms,
    &ett_s1ap_NRintegrityProtectionAlgorithms,
    &ett_s1ap_UE_Application_Layer_Measurement_Capability,
    &ett_s1ap_sMTC,
    &ett_s1ap_threshRS_Index_r15,
    &ett_s1ap_sSBToMeasure,
    &ett_s1ap_sSRSSIMeasurement,
    &ett_s1ap_quantityConfigNR_R15,
    &ett_s1ap_blackCellsToAddModList,
    &ett_s1ap_NB_IoT_RLF_Report_Container,
    &ett_s1ap_MDT_ConfigurationNR,
    &ett_s1ap_IntersystemSONConfigurationTransfer,

/*--- Included file: packet-s1ap-ettarr.c ---*/
#line 1 "./asn1/s1ap/packet-s1ap-ettarr.c"
    &ett_s1ap_PrivateIE_ID,
    &ett_s1ap_ProtocolIE_Container,
    &ett_s1ap_ProtocolIE_Field,
    &ett_s1ap_ProtocolIE_ContainerList,
    &ett_s1ap_ProtocolExtensionContainer,
    &ett_s1ap_ProtocolExtensionField,
    &ett_s1ap_PrivateIE_Container,
    &ett_s1ap_PrivateIE_Field,
    &ett_s1ap_Additional_GUTI,
    &ett_s1ap_AreaScopeOfMDT,
    &ett_s1ap_AreaScopeOfQMC,
    &ett_s1ap_AllocationAndRetentionPriority,
    &ett_s1ap_AssistanceDataForCECapableUEs,
    &ett_s1ap_AssistanceDataForPaging,
    &ett_s1ap_AssistanceDataForRecommendedCells,
    &ett_s1ap_Bearers_SubjectToStatusTransferList,
    &ett_s1ap_Bearers_SubjectToStatusTransfer_Item,
    &ett_s1ap_Bearers_SubjectToEarlyStatusTransferList,
    &ett_s1ap_Bearers_SubjectToEarlyStatusTransfer_Item,
    &ett_s1ap_BluetoothMeasurementConfiguration,
    &ett_s1ap_BluetoothMeasConfigNameList,
    &ett_s1ap_BPLMNs,
    &ett_s1ap_BroadcastCancelledAreaList,
    &ett_s1ap_BroadcastCompletedAreaList,
    &ett_s1ap_CancelledCellinEAI,
    &ett_s1ap_CancelledCellinEAI_Item,
    &ett_s1ap_CancelledCellinTAI,
    &ett_s1ap_CancelledCellinTAI_Item,
    &ett_s1ap_Cause,
    &ett_s1ap_CellIdentifierAndCELevelForCECapableUEs,
    &ett_s1ap_CellID_Broadcast,
    &ett_s1ap_CellID_Broadcast_Item,
    &ett_s1ap_CellID_Cancelled,
    &ett_s1ap_CellID_Cancelled_Item,
    &ett_s1ap_CellBasedMDT,
    &ett_s1ap_CellIdListforMDT,
    &ett_s1ap_CellBasedQMC,
    &ett_s1ap_CellIdListforQMC,
    &ett_s1ap_Cdma2000OneXSRVCCInfo,
    &ett_s1ap_CellType,
    &ett_s1ap_CGI,
    &ett_s1ap_CNTypeRestrictions,
    &ett_s1ap_CNTypeRestrictions_Item,
    &ett_s1ap_ConnectedengNBList,
    &ett_s1ap_ConnectedengNBItem,
    &ett_s1ap_ContextatSource,
    &ett_s1ap_CSG_IdList,
    &ett_s1ap_CSG_IdList_Item,
    &ett_s1ap_COUNTvalue,
    &ett_s1ap_COUNTValueExtended,
    &ett_s1ap_COUNTvaluePDCP_SNlength18,
    &ett_s1ap_CriticalityDiagnostics,
    &ett_s1ap_CriticalityDiagnostics_IE_List,
    &ett_s1ap_CriticalityDiagnostics_IE_Item,
    &ett_s1ap_DAPSRequestInfo,
    &ett_s1ap_DAPSResponseInfoList,
    &ett_s1ap_DAPSResponseInfoItem,
    &ett_s1ap_DAPSResponseInfo,
    &ett_s1ap_ServedDCNs,
    &ett_s1ap_ServedDCNsItem,
    &ett_s1ap_DL_CP_SecurityInformation,
    &ett_s1ap_DLCOUNT_PDCP_SNlength,
    &ett_s1ap_ECGIList,
    &ett_s1ap_PWSfailedECGIList,
    &ett_s1ap_EmergencyAreaIDList,
    &ett_s1ap_EmergencyAreaID_Broadcast,
    &ett_s1ap_EmergencyAreaID_Broadcast_Item,
    &ett_s1ap_EmergencyAreaID_Cancelled,
    &ett_s1ap_EmergencyAreaID_Cancelled_Item,
    &ett_s1ap_CompletedCellinEAI,
    &ett_s1ap_CompletedCellinEAI_Item,
    &ett_s1ap_ECGI_List,
    &ett_s1ap_EmergencyAreaIDListForRestart,
    &ett_s1ap_ENB_EarlyStatusTransfer_TransparentContainer,
    &ett_s1ap_ENB_ID,
    &ett_s1ap_GERAN_Cell_ID,
    &ett_s1ap_Global_ENB_ID,
    &ett_s1ap_Global_en_gNB_ID,
    &ett_s1ap_GUMMEIList,
    &ett_s1ap_ENB_StatusTransfer_TransparentContainer,
    &ett_s1ap_ENBX2TLAs,
    &ett_s1ap_EN_DCSONConfigurationTransfer,
    &ett_s1ap_EN_DCSONTransferType,
    &ett_s1ap_EN_DCTransferTypeRequest,
    &ett_s1ap_EN_DCTransferTypeReply,
    &ett_s1ap_EN_DCSONeNBIdentification,
    &ett_s1ap_EN_DCSONengNBIdentification,
    &ett_s1ap_EPLMNs,
    &ett_s1ap_E_RABInformationList,
    &ett_s1ap_E_RABInformationListItem,
    &ett_s1ap_E_RABList,
    &ett_s1ap_E_RABItem,
    &ett_s1ap_E_RABLevelQoSParameters,
    &ett_s1ap_E_RABUsageReportList,
    &ett_s1ap_E_RABUsageReportItem,
    &ett_s1ap_EUTRAN_CGI,
    &ett_s1ap_ExpectedUEBehaviour,
    &ett_s1ap_ExpectedUEActivityBehaviour,
    &ett_s1ap_FiveGSTAI,
    &ett_s1ap_ForbiddenTAs,
    &ett_s1ap_ForbiddenTAs_Item,
    &ett_s1ap_ForbiddenTACs,
    &ett_s1ap_ForbiddenLAs,
    &ett_s1ap_ForbiddenLAs_Item,
    &ett_s1ap_ForbiddenLACs,
    &ett_s1ap_GBR_QosInformation,
    &ett_s1ap_GUMMEI,
    &ett_s1ap_HandoverRestrictionList,
    &ett_s1ap_ImmediateMDT,
    &ett_s1ap_InformationOnRecommendedCellsAndENBsForPaging,
    &ett_s1ap_IntersystemMeasurementConfiguration,
    &ett_s1ap_InterSystemMeasurementParameters,
    &ett_s1ap_InterSystemMeasurementList,
    &ett_s1ap_InterSystemMeasurementItem,
    &ett_s1ap_LAI,
    &ett_s1ap_LastVisitedCell_Item,
    &ett_s1ap_LastVisitedEUTRANCellInformation,
    &ett_s1ap_LastVisitedGERANCellInformation,
    &ett_s1ap_ListeningSubframePattern,
    &ett_s1ap_LoggedMDT,
    &ett_s1ap_LoggedMBSFNMDT,
    &ett_s1ap_M3Configuration,
    &ett_s1ap_M4Configuration,
    &ett_s1ap_M5Configuration,
    &ett_s1ap_M6Configuration,
    &ett_s1ap_M7Configuration,
    &ett_s1ap_MDT_Configuration,
    &ett_s1ap_MBSFN_ResultToLog,
    &ett_s1ap_MBSFN_ResultToLogInfo,
    &ett_s1ap_MDTPLMNList,
    &ett_s1ap_MDTMode,
    &ett_s1ap_MeasurementThresholdA2,
    &ett_s1ap_MMEPagingTarget,
    &ett_s1ap_MutingPatternInformation,
    &ett_s1ap_NB_IoT_Paging_eDRXInformation,
    &ett_s1ap_NR_CGI,
    &ett_s1ap_NRUESecurityCapabilities,
    &ett_s1ap_NRV2XServicesAuthorized,
    &ett_s1ap_NRUESidelinkAggregateMaximumBitrate,
    &ett_s1ap_OverloadResponse,
    &ett_s1ap_PagingAttemptInformation,
    &ett_s1ap_Paging_eDRXInformation,
    &ett_s1ap_PC5QoSParameters,
    &ett_s1ap_PC5QoSFlowList,
    &ett_s1ap_PC5QoSFlowItem,
    &ett_s1ap_PC5FlowBitRates,
    &ett_s1ap_M1PeriodicReporting,
    &ett_s1ap_PLMNAreaBasedQMC,
    &ett_s1ap_PLMNListforQMC,
    &ett_s1ap_ProSeAuthorized,
    &ett_s1ap_PSCellInformation,
    &ett_s1ap_RecommendedCellsForPaging,
    &ett_s1ap_RecommendedCellList,
    &ett_s1ap_RecommendedCellItem,
    &ett_s1ap_RecommendedENBsForPaging,
    &ett_s1ap_RecommendedENBList,
    &ett_s1ap_RecommendedENBItem,
    &ett_s1ap_RequestType,
    &ett_s1ap_RIMTransfer,
    &ett_s1ap_RIMRoutingAddress,
    &ett_s1ap_RLFReportInformation,
    &ett_s1ap_ECGIListForRestart,
    &ett_s1ap_SecurityContext,
    &ett_s1ap_SecondaryRATDataUsageReportList,
    &ett_s1ap_SecondaryRATDataUsageReportItem,
    &ett_s1ap_SONInformation,
    &ett_s1ap_SONInformationReply,
    &ett_s1ap_SONInformationReport,
    &ett_s1ap_SONConfigurationTransfer,
    &ett_s1ap_SynchronisationInformation,
    &ett_s1ap_SourceeNB_ID,
    &ett_s1ap_SourceNodeID,
    &ett_s1ap_SourceeNB_ToTargeteNB_TransparentContainer,
    &ett_s1ap_SourceNgRanNode_ID,
    &ett_s1ap_ServedGUMMEIs,
    &ett_s1ap_ServedGUMMEIsItem,
    &ett_s1ap_ServedGroupIDs,
    &ett_s1ap_ServedMMECs,
    &ett_s1ap_ServedPLMNs,
    &ett_s1ap_Subscription_Based_UE_DifferentiationInfo,
    &ett_s1ap_ScheduledCommunicationTime,
    &ett_s1ap_SupportedTAs,
    &ett_s1ap_SupportedTAs_Item,
    &ett_s1ap_TimeSynchronisationInfo,
    &ett_s1ap_S_TMSI,
    &ett_s1ap_TAIBasedMDT,
    &ett_s1ap_TAIListforMDT,
    &ett_s1ap_TAIListforWarning,
    &ett_s1ap_TAI,
    &ett_s1ap_TAI_Broadcast,
    &ett_s1ap_TAI_Broadcast_Item,
    &ett_s1ap_TAI_Cancelled,
    &ett_s1ap_TAI_Cancelled_Item,
    &ett_s1ap_TABasedMDT,
    &ett_s1ap_TAListforMDT,
    &ett_s1ap_TABasedQMC,
    &ett_s1ap_TAListforQMC,
    &ett_s1ap_TAIBasedQMC,
    &ett_s1ap_TAIListforQMC,
    &ett_s1ap_CompletedCellinTAI,
    &ett_s1ap_CompletedCellinTAI_Item,
    &ett_s1ap_TargetID,
    &ett_s1ap_TargeteNB_ID,
    &ett_s1ap_TargetRNC_ID,
    &ett_s1ap_TargetNgRanNode_ID,
    &ett_s1ap_Global_RAN_NODE_ID,
    &ett_s1ap_GNB,
    &ett_s1ap_Global_GNB_ID,
    &ett_s1ap_GNB_Identity,
    &ett_s1ap_NG_eNB,
    &ett_s1ap_TargeteNB_ToSourceeNB_TransparentContainer,
    &ett_s1ap_M1ThresholdEventA2,
    &ett_s1ap_TransportInformation,
    &ett_s1ap_TraceActivation,
    &ett_s1ap_TunnelInformation,
    &ett_s1ap_TAIListForRestart,
    &ett_s1ap_UEAggregateMaximumBitrate,
    &ett_s1ap_UEAppLayerMeasConfig,
    &ett_s1ap_UE_S1AP_IDs,
    &ett_s1ap_UE_S1AP_ID_pair,
    &ett_s1ap_UE_associatedLogicalS1_ConnectionItem,
    &ett_s1ap_UE_HistoryInformation,
    &ett_s1ap_UEPagingID,
    &ett_s1ap_UESecurityCapabilities,
    &ett_s1ap_UESidelinkAggregateMaximumBitrate,
    &ett_s1ap_UL_CP_SecurityInformation,
    &ett_s1ap_UserLocationInformation,
    &ett_s1ap_V2XServicesAuthorized,
    &ett_s1ap_WarningAreaList,
    &ett_s1ap_WLANMeasurementConfiguration,
    &ett_s1ap_WLANMeasConfigNameList,
    &ett_s1ap_WUS_Assistance_Information,
    &ett_s1ap_X2TNLConfigurationInfo,
    &ett_s1ap_ENBX2ExtTLAs,
    &ett_s1ap_ENBX2ExtTLA,
    &ett_s1ap_ENBX2GTPTLAs,
    &ett_s1ap_ENBIndirectX2TransportLayerAddresses,
    &ett_s1ap_HandoverRequired,
    &ett_s1ap_HandoverCommand,
    &ett_s1ap_E_RABDataForwardingItem,
    &ett_s1ap_HandoverPreparationFailure,
    &ett_s1ap_HandoverRequest,
    &ett_s1ap_E_RABToBeSetupItemHOReq,
    &ett_s1ap_HandoverRequestAcknowledge,
    &ett_s1ap_E_RABAdmittedItem,
    &ett_s1ap_E_RABFailedToSetupItemHOReqAck,
    &ett_s1ap_HandoverFailure,
    &ett_s1ap_HandoverNotify,
    &ett_s1ap_PathSwitchRequest,
    &ett_s1ap_E_RABToBeSwitchedDLItem,
    &ett_s1ap_PathSwitchRequestAcknowledge,
    &ett_s1ap_E_RABToBeSwitchedULItem,
    &ett_s1ap_PathSwitchRequestFailure,
    &ett_s1ap_HandoverCancel,
    &ett_s1ap_HandoverCancelAcknowledge,
    &ett_s1ap_HandoverSuccess,
    &ett_s1ap_ENBEarlyStatusTransfer,
    &ett_s1ap_MMEEarlyStatusTransfer,
    &ett_s1ap_E_RABSetupRequest,
    &ett_s1ap_E_RABToBeSetupListBearerSUReq,
    &ett_s1ap_E_RABToBeSetupItemBearerSUReq,
    &ett_s1ap_E_RABSetupResponse,
    &ett_s1ap_E_RABSetupListBearerSURes,
    &ett_s1ap_E_RABSetupItemBearerSURes,
    &ett_s1ap_E_RABModifyRequest,
    &ett_s1ap_E_RABToBeModifiedListBearerModReq,
    &ett_s1ap_E_RABToBeModifiedItemBearerModReq,
    &ett_s1ap_E_RABModifyResponse,
    &ett_s1ap_E_RABModifyListBearerModRes,
    &ett_s1ap_E_RABModifyItemBearerModRes,
    &ett_s1ap_E_RABReleaseCommand,
    &ett_s1ap_E_RABReleaseResponse,
    &ett_s1ap_E_RABReleaseListBearerRelComp,
    &ett_s1ap_E_RABReleaseItemBearerRelComp,
    &ett_s1ap_E_RABReleaseIndication,
    &ett_s1ap_InitialContextSetupRequest,
    &ett_s1ap_E_RABToBeSetupListCtxtSUReq,
    &ett_s1ap_E_RABToBeSetupItemCtxtSUReq,
    &ett_s1ap_InitialContextSetupResponse,
    &ett_s1ap_E_RABSetupListCtxtSURes,
    &ett_s1ap_E_RABSetupItemCtxtSURes,
    &ett_s1ap_InitialContextSetupFailure,
    &ett_s1ap_Paging,
    &ett_s1ap_TAIList,
    &ett_s1ap_TAIItem,
    &ett_s1ap_UEContextReleaseRequest,
    &ett_s1ap_UEContextReleaseCommand,
    &ett_s1ap_UEContextReleaseComplete,
    &ett_s1ap_UEContextModificationRequest,
    &ett_s1ap_UEContextModificationResponse,
    &ett_s1ap_UEContextModificationFailure,
    &ett_s1ap_UERadioCapabilityMatchRequest,
    &ett_s1ap_UERadioCapabilityMatchResponse,
    &ett_s1ap_DownlinkNASTransport,
    &ett_s1ap_InitialUEMessage,
    &ett_s1ap_UplinkNASTransport,
    &ett_s1ap_NASNonDeliveryIndication,
    &ett_s1ap_RerouteNASRequest,
    &ett_s1ap_NASDeliveryIndication,
    &ett_s1ap_Reset,
    &ett_s1ap_ResetType,
    &ett_s1ap_UE_associatedLogicalS1_ConnectionListRes,
    &ett_s1ap_ResetAcknowledge,
    &ett_s1ap_UE_associatedLogicalS1_ConnectionListResAck,
    &ett_s1ap_ErrorIndication,
    &ett_s1ap_S1SetupRequest,
    &ett_s1ap_S1SetupResponse,
    &ett_s1ap_S1SetupFailure,
    &ett_s1ap_ENBConfigurationUpdate,
    &ett_s1ap_ENBConfigurationUpdateAcknowledge,
    &ett_s1ap_ENBConfigurationUpdateFailure,
    &ett_s1ap_MMEConfigurationUpdate,
    &ett_s1ap_MMEConfigurationUpdateAcknowledge,
    &ett_s1ap_MMEConfigurationUpdateFailure,
    &ett_s1ap_DownlinkS1cdma2000tunnelling,
    &ett_s1ap_UplinkS1cdma2000tunnelling,
    &ett_s1ap_UECapabilityInfoIndication,
    &ett_s1ap_ENBStatusTransfer,
    &ett_s1ap_MMEStatusTransfer,
    &ett_s1ap_TraceStart,
    &ett_s1ap_TraceFailureIndication,
    &ett_s1ap_DeactivateTrace,
    &ett_s1ap_CellTrafficTrace,
    &ett_s1ap_LocationReportingControl,
    &ett_s1ap_LocationReportingFailureIndication,
    &ett_s1ap_LocationReport,
    &ett_s1ap_OverloadStart,
    &ett_s1ap_OverloadStop,
    &ett_s1ap_WriteReplaceWarningRequest,
    &ett_s1ap_WriteReplaceWarningResponse,
    &ett_s1ap_ENBDirectInformationTransfer,
    &ett_s1ap_Inter_SystemInformationTransferType,
    &ett_s1ap_MMEDirectInformationTransfer,
    &ett_s1ap_ENBConfigurationTransfer,
    &ett_s1ap_MMEConfigurationTransfer,
    &ett_s1ap_PrivateMessage,
    &ett_s1ap_KillRequest,
    &ett_s1ap_KillResponse,
    &ett_s1ap_PWSRestartIndication,
    &ett_s1ap_PWSFailureIndication,
    &ett_s1ap_DownlinkUEAssociatedLPPaTransport,
    &ett_s1ap_UplinkUEAssociatedLPPaTransport,
    &ett_s1ap_DownlinkNonUEAssociatedLPPaTransport,
    &ett_s1ap_UplinkNonUEAssociatedLPPaTransport,
    &ett_s1ap_E_RABModificationIndication,
    &ett_s1ap_E_RABToBeModifiedItemBearerModInd,
    &ett_s1ap_E_RABNotToBeModifiedItemBearerModInd,
    &ett_s1ap_CSGMembershipInfo,
    &ett_s1ap_E_RABModificationConfirm,
    &ett_s1ap_E_RABModifyListBearerModConf,
    &ett_s1ap_E_RABModifyItemBearerModConf,
    &ett_s1ap_UEContextModificationIndication,
    &ett_s1ap_UEContextModificationConfirm,
    &ett_s1ap_UEContextSuspendRequest,
    &ett_s1ap_UEContextSuspendResponse,
    &ett_s1ap_UEContextResumeRequest,
    &ett_s1ap_E_RABFailedToResumeItemResumeReq,
    &ett_s1ap_UEContextResumeResponse,
    &ett_s1ap_E_RABFailedToResumeItemResumeRes,
    &ett_s1ap_UEContextResumeFailure,
    &ett_s1ap_ConnectionEstablishmentIndication,
    &ett_s1ap_RetrieveUEInformation,
    &ett_s1ap_UEInformationTransfer,
    &ett_s1ap_ENBCPRelocationIndication,
    &ett_s1ap_MMECPRelocationIndication,
    &ett_s1ap_SecondaryRATDataUsageReport,
    &ett_s1ap_UERadioCapabilityIDMappingRequest,
    &ett_s1ap_UERadioCapabilityIDMappingResponse,
    &ett_s1ap_S1AP_PDU,
    &ett_s1ap_InitiatingMessage,
    &ett_s1ap_SuccessfulOutcome,
    &ett_s1ap_UnsuccessfulOutcome,
    &ett_s1ap_SONtransferRequestContainer,
    &ett_s1ap_SONtransferResponseContainer,
    &ett_s1ap_SONtransferCause,
    &ett_s1ap_CellLoadReportingResponse,
    &ett_s1ap_EUTRANcellLoadReportingResponse,
    &ett_s1ap_EUTRANResponse,
    &ett_s1ap_IRAT_Cell_ID,
    &ett_s1ap_RequestedCellList,
    &ett_s1ap_MultiCellLoadReportingRequest,
    &ett_s1ap_ReportingCellList_Item,
    &ett_s1ap_ReportingCellList,
    &ett_s1ap_MultiCellLoadReportingResponse,
    &ett_s1ap_MultiCellLoadReportingResponse_Item,
    &ett_s1ap_EventTriggeredCellLoadReportingRequest,
    &ett_s1ap_EventTriggeredCellLoadReportingResponse,
    &ett_s1ap_HOReport,
    &ett_s1ap_CandidateCellList,
    &ett_s1ap_CandidatePCIList,
    &ett_s1ap_CandidatePCI,
    &ett_s1ap_CellActivationRequest,
    &ett_s1ap_CellsToActivateList,
    &ett_s1ap_CellsToActivateList_Item,
    &ett_s1ap_CellActivationResponse,
    &ett_s1ap_ActivatedCellsList,
    &ett_s1ap_ActivatedCellsList_Item,
    &ett_s1ap_CellStateIndication,
    &ett_s1ap_NotificationCellList,
    &ett_s1ap_NotificationCellList_Item,
    &ett_s1ap_FailureEventReport,
    &ett_s1ap_TooEarlyInterRATHOReportReportFromEUTRAN,
    &ett_s1ap_EHRPDSectorLoadReportingResponse,
    &ett_s1ap_EHRPDCompositeAvailableCapacity,
    &ett_s1ap_EHRPDMultiSectorLoadReportingResponseItem,

/*--- End of included file: packet-s1ap-ettarr.c ---*/
#line 775 "./asn1/s1ap/packet-s1ap-template.c"
  };

  static ei_register_info ei[] = {
    { &ei_s1ap_number_pages_le15, { "s1ap.number_pages_le15", PI_MALFORMED, PI_ERROR, "Number of pages should be <=15", EXPFILL }}
  };

  module_t *s1ap_module;
  expert_module_t* expert_s1ap;

  /* Register protocol */
  proto_s1ap = proto_register_protocol(PNAME, PSNAME, PFNAME);
  /* Register fields and subtrees */
  proto_register_field_array(proto_s1ap, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));
  expert_s1ap = expert_register_protocol(proto_s1ap);
  expert_register_field_array(expert_s1ap, ei, array_length(ei));

  /* Register dissector */
  s1ap_handle = register_dissector("s1ap", dissect_s1ap, proto_s1ap);

  /* Register dissector tables */
  s1ap_ies_dissector_table = register_dissector_table("s1ap.ies", "S1AP-PROTOCOL-IES", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_ies_p1_dissector_table = register_dissector_table("s1ap.ies.pair.first", "S1AP-PROTOCOL-IES-PAIR FirstValue", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_ies_p2_dissector_table = register_dissector_table("s1ap.ies.pair.second", "S1AP-PROTOCOL-IES-PAIR SecondValue", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_extension_dissector_table = register_dissector_table("s1ap.extension", "S1AP-PROTOCOL-EXTENSION", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_proc_imsg_dissector_table = register_dissector_table("s1ap.proc.imsg", "S1AP-ELEMENTARY-PROCEDURE InitiatingMessage", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_proc_sout_dissector_table = register_dissector_table("s1ap.proc.sout", "S1AP-ELEMENTARY-PROCEDURE SuccessfulOutcome", proto_s1ap, FT_UINT32, BASE_DEC);
  s1ap_proc_uout_dissector_table = register_dissector_table("s1ap.proc.uout", "S1AP-ELEMENTARY-PROCEDURE UnsuccessfulOutcome", proto_s1ap, FT_UINT32, BASE_DEC);

  /* Register configuration options for ports */
  s1ap_module = prefs_register_protocol(proto_s1ap, proto_reg_handoff_s1ap);

  prefs_register_uint_preference(s1ap_module, "sctp.port",
                                 "S1AP SCTP Port",
                                 "Set the SCTP port for S1AP messages",
                                 10,
                                 &gbl_s1apSctpPort);
  prefs_register_bool_preference(s1ap_module, "dissect_container", "Dissect TransparentContainer", "Dissect TransparentContainers that are opaque to S1AP", &g_s1ap_dissect_container);
  prefs_register_enum_preference(s1ap_module, "dissect_lte_container_as", "Dissect LTE TransparentContainer as",
                                 "Select whether LTE TransparentContainer should be dissected as NB-IOT or legacy LTE",
                                 &g_s1ap_dissect_lte_container_as, s1ap_lte_container_vals, FALSE);
}

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 2
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=2 tabstop=8 expandtab:
 * :indentSize=2:tabSize=8:noTabs=true:
 */
