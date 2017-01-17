/*******************************************************************************

   CO_OD.c - Variables and Object Dictionary for CANopenNode

   Copyright (C) 2004  Janez Paternoster, Slovenia

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA


   Author: janez.paternoster@siol.net

********************************************************************************

   For short description of standard Object Dictionary entries see CO_OD.txt

*******************************************************************************/

#define __CPUCONFIG			// Pedimos que aplique la configuracion de cpu

#include "CANopen.h"
#include "user.h"

//CO_MAX_ENTRY_NR is maximum number of PDO and Heartbeat entries
//defined in this file. If more entries are neeed, they can be added
#define CO_MAX_ENTRY_NR 20

//check defines
#if CO_NO_RPDO > CO_MAX_ENTRY_NR
   #error defineCO_NO_RPDO (CO_NO_RPDO) not correct!
#endif
#if CO_NO_TPDO > CO_MAX_ENTRY_NR
   #error defineCO_NO_TPDO (CO_NO_TPDO) not correct!
#endif
#if CO_NO_SDO_SERVER > 1
   #error defineCO_NO_SDO_SERVER (CO_NO_SDO_SERVER) not correct!
#endif
#if CO_NO_SDO_CLIENT > 1
   #error defineCO_NO_SDO_CLIENT (CO_NO_SDO_CLIENT) not correct!
#endif
#if CO_NO_CONS_HEARTBEAT > CO_MAX_ENTRY_NR
   #error defineCO_NO_CONS_HEARTBEAT (CO_NO_CONS_HEARTBEAT) not correct!
#endif
#if CO_NO_ERROR_FIELD != 0 && CO_NO_ERROR_FIELD != 8
   #error defineCO_NO_ERROR_FIELD (CO_NO_ERROR_FIELD) not correct!
#endif

/******************************************************************************/
/*     VARIABLES      *********************************************************/
/******************************************************************************/
#ifdef __18CXX
   #pragma romdata ODE_CO_RomVariables=0x2000 //ROM variables in PIC18fxxx must be above address 0x1000
#endif

/*0x1000*/ ROM UNSIGNED32     ODE_Device_Type = ODD_DEVICE_TYPE;
/*0x1001*/     UNSIGNED8      ODE_Error_Register = 0;
/*0x1002*/     UNSIGNED32     ODE_Manufacturer_Status_Register = 0L;

           #if CO_NO_ERROR_FIELD > 0
/*0x1003*/     UNSIGNED8      ODE_Pre_Defined_Error_Field_NoOfErrors = 0;
               UNSIGNED32     ODE_Pre_Defined_Error_Field[CO_NO_ERROR_FIELD];
           #endif

           #if CO_NO_SYNC > 0
/*0x1005*/ ROM UNSIGNED32     ODE_SYNC_COB_ID = ODD_SYNC_COB_ID;
/*0x1006*/ ROM UNSIGNED32     ODE_Communication_Cycle_Period = ODD_COMM_CYCLE_PERIOD;
/*0x1007*/ ROM UNSIGNED32     ODE_Synchronous_Window_Length = ODD_SYNCHR_WINDOW_LEN;
           #endif

/*0x1008*/ ROM char           ODE_Manufacturer_Device_Name[] = ODD_MANUF_DEVICE_NAME;
/*0x1009*/ ROM char           ODE_Manufacturer_Hardware_Version[] = ODD_MANUF_HW_VERSION;
/*0x100A*/ ROM char           ODE_Manufacturer_Software_Version[] = ODD_MANUF_SW_VERSION;

           #if CO_NO_EMERGENCY > 0
/*0x1014*/ ROM UNSIGNED32     ODE_Emergency_COB_ID = 0x00000080L; //NODE-ID is added when used
/*0x1015*/ ROM UNSIGNED16     ODE_Inhibit_Time_Emergency = ODD_INHIBIT_TIME_EMER;
           #endif

           #if CO_NO_CONS_HEARTBEAT > 0
/*0x1016*/ ROM UNSIGNED8      ODE_Consumer_Heartbeat_Time_NoOfEntries = CO_NO_CONS_HEARTBEAT;
           ROM UNSIGNED32     ODE_Consumer_Heartbeat_Time[CO_NO_CONS_HEARTBEAT] = {
                  ODD_CONS_HEARTBEAT_0,
               #if CO_NO_CONS_HEARTBEAT > 1
                  ODD_CONS_HEARTBEAT_1,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 2
                  ODD_CONS_HEARTBEAT_2,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 3
                  ODD_CONS_HEARTBEAT_3,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 4
                  ODD_CONS_HEARTBEAT_4,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 5
                  ODD_CONS_HEARTBEAT_5,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 6
                  ODD_CONS_HEARTBEAT_6,
               #endif
               #if CO_NO_CONS_HEARTBEAT > 7
                  ODD_CONS_HEARTBEAT_7,
               #endif
               };
           #endif

/*0x1017*/ ROM UNSIGNED16     ODE_Producer_Heartbeat_Time = ODD_PROD_HEARTBEAT;
/*0x1018*/ ROM struct{
               UNSIGNED8      NoOfEntries;
               UNSIGNED32     Vendor_ID;
               UNSIGNED32     Product_Code;
               UNSIGNED32     Revision_Number;
               UNSIGNED32     Serial_Number;
               }              ODE_Identity = {
                                 4,
                                 ODD_IDENT_VENDOR_ID,
                                 ODD_IDENT_PROD_CODE,
                                 ODD_IDENT_REVISION_NR,
                                 ODD_IDENT_SERIAL_NR
                              };

/*0x1029*/ ROM ODEs_Error_Behavior  ODE_Error_Behavior = {
                                 1,
                                 ODD_ERROR_BEH_COMM,
                              };

           #if CO_NO_SDO_SERVER > 0
/*0x1200+*/ROM UNSIGNED8      ODE_Server_SDO_Parameter_NoOfEntries = 2;
           ROM CO_sSDO_Param  ODE_Server_SDO_Parameter[CO_NO_SDO_SERVER] = {
                  {CAN_ID_RSDO, CAN_ID_TSDO, 0}
               };
           #endif

           #if CO_NO_SDO_CLIENT > 0
/*0x1280+*/ROM UNSIGNED8      ODE_Client_SDO_Parameter_NoOfEntries = 3;
               CO_sSDO_Param  ODE_Client_SDO_Parameter[CO_NO_SDO_CLIENT] = {
                  {0x80000000L, 0x80000000L, 0}
               };
           #endif

           #if CO_NO_RPDO > 0
/*0x1400+*/ROM UNSIGNED8      ODE_RPDO_Parameter_NoOfEntries = 2;
           ROM CO_sRPDO_param ODE_RPDO_Parameter[CO_NO_RPDO] = {
                  #if ODD_RPDO_PAR_COB_ID_0 == 0
                     {CAN_ID_RPDO0, ODD_RPDO_PAR_T_TYPE_0},
                  #else
                     {ODD_RPDO_PAR_COB_ID_0, ODD_RPDO_PAR_T_TYPE_0},
                  #endif
               #if CO_NO_RPDO > 1
                  #if ODD_RPDO_PAR_COB_ID_1 == 0
                     {CAN_ID_RPDO1, ODD_RPDO_PAR_T_TYPE_1},
                  #else
                     {ODD_RPDO_PAR_COB_ID_1, ODD_RPDO_PAR_T_TYPE_1},
                  #endif
               #endif
               #if CO_NO_RPDO > 2
                  #if ODD_RPDO_PAR_COB_ID_2 == 0
                     {CAN_ID_RPDO2, ODD_RPDO_PAR_T_TYPE_2},
                  #else
                     {ODD_RPDO_PAR_COB_ID_2, ODD_RPDO_PAR_T_TYPE_2},
                  #endif
               #endif
               #if CO_NO_RPDO > 3
                  #if ODD_RPDO_PAR_COB_ID_3 == 0
                     {CAN_ID_RPDO3, ODD_RPDO_PAR_T_TYPE_3},
                  #else
                     {ODD_RPDO_PAR_COB_ID_3, ODD_RPDO_PAR_T_TYPE_3},
                  #endif
               #endif
               #if CO_NO_RPDO > 4
                  {ODD_RPDO_PAR_COB_ID_4, ODD_RPDO_PAR_T_TYPE_4},
               #endif
               #if CO_NO_RPDO > 5
                  {ODD_RPDO_PAR_COB_ID_5, ODD_RPDO_PAR_T_TYPE_5},
               #endif
               #if CO_NO_RPDO > 6
                  {ODD_RPDO_PAR_COB_ID_6, ODD_RPDO_PAR_T_TYPE_6},
               #endif
               #if CO_NO_RPDO > 7
                  {ODD_RPDO_PAR_COB_ID_7, ODD_RPDO_PAR_T_TYPE_7},
               #endif
               #if CO_NO_RPDO > 8
                  {ODD_RPDO_PAR_COB_ID_8, ODD_RPDO_PAR_T_TYPE_8},
               #endif
               #if CO_NO_RPDO > 9
                  {ODD_RPDO_PAR_COB_ID_9, ODD_RPDO_PAR_T_TYPE_9},
               #endif
               #if CO_NO_RPDO > 10
                  {ODD_RPDO_PAR_COB_ID_10, ODD_RPDO_PAR_T_TYPE_10},
               #endif
               #if CO_NO_RPDO > 11
                  {ODD_RPDO_PAR_COB_ID_11, ODD_RPDO_PAR_T_TYPE_11},
               #endif
               #if CO_NO_RPDO > 12
                  {ODD_RPDO_PAR_COB_ID_12, ODD_RPDO_PAR_T_TYPE_12},
               #endif
               #if CO_NO_RPDO > 13
                  {ODD_RPDO_PAR_COB_ID_13, ODD_RPDO_PAR_T_TYPE_13},
               #endif
               #if CO_NO_RPDO > 14
                  {ODD_RPDO_PAR_COB_ID_14, ODD_RPDO_PAR_T_TYPE_14},
               #endif
               #if CO_NO_RPDO > 15
                  {ODD_RPDO_PAR_COB_ID_15, ODD_RPDO_PAR_T_TYPE_15},
               #endif
               #if CO_NO_RPDO > 16
                  {ODD_RPDO_PAR_COB_ID_16, ODD_RPDO_PAR_T_TYPE_16},
               #endif
               #if CO_NO_RPDO > 17
                  {ODD_RPDO_PAR_COB_ID_17, ODD_RPDO_PAR_T_TYPE_17},
               #endif
               #if CO_NO_RPDO > 18
                  {ODD_RPDO_PAR_COB_ID_18, ODD_RPDO_PAR_T_TYPE_18},
               #endif
               #if CO_NO_RPDO > 19
                  {ODD_RPDO_PAR_COB_ID_19, ODD_RPDO_PAR_T_TYPE_19},
               #endif
               };
           #endif

           #ifdef CO_PDO_MAPPING_IN_OD
           #if CO_NO_RPDO > 0
/*0x1600+*/ROM UNSIGNED8      ODE_RPDO_Mapping_NoOfEntries = 8;
           ROM UNSIGNED32     ODE_RPDO_Mapping[CO_NO_RPDO][8] = {
                  {ODD_RPDO_MAP_0_1, ODD_RPDO_MAP_0_2, ODD_RPDO_MAP_0_3, ODD_RPDO_MAP_0_4, ODD_RPDO_MAP_0_5, ODD_RPDO_MAP_0_6, ODD_RPDO_MAP_0_7, ODD_RPDO_MAP_0_8},
               #if CO_NO_RPDO > 1
                  {ODD_RPDO_MAP_1_1, ODD_RPDO_MAP_1_2, ODD_RPDO_MAP_1_3, ODD_RPDO_MAP_1_4, ODD_RPDO_MAP_1_5, ODD_RPDO_MAP_1_6, ODD_RPDO_MAP_1_7, ODD_RPDO_MAP_1_8},
               #endif
               #if CO_NO_RPDO > 2
                  {ODD_RPDO_MAP_2_1, ODD_RPDO_MAP_2_2, ODD_RPDO_MAP_2_3, ODD_RPDO_MAP_2_4, ODD_RPDO_MAP_2_5, ODD_RPDO_MAP_2_6, ODD_RPDO_MAP_2_7, ODD_RPDO_MAP_2_8},
               #endif
               #if CO_NO_RPDO > 3
                  {ODD_RPDO_MAP_3_1, ODD_RPDO_MAP_3_2, ODD_RPDO_MAP_3_3, ODD_RPDO_MAP_3_4, ODD_RPDO_MAP_3_5, ODD_RPDO_MAP_3_6, ODD_RPDO_MAP_3_7, ODD_RPDO_MAP_3_8},
               #endif
               #if CO_NO_RPDO > 4
                  {ODD_RPDO_MAP_4_1, ODD_RPDO_MAP_4_2, ODD_RPDO_MAP_4_3, ODD_RPDO_MAP_4_4, ODD_RPDO_MAP_4_5, ODD_RPDO_MAP_4_6, ODD_RPDO_MAP_4_7, ODD_RPDO_MAP_4_8},
               #endif
               #if CO_NO_RPDO > 5
                  {ODD_RPDO_MAP_5_1, ODD_RPDO_MAP_5_2, ODD_RPDO_MAP_5_3, ODD_RPDO_MAP_5_4, ODD_RPDO_MAP_5_5, ODD_RPDO_MAP_5_6, ODD_RPDO_MAP_5_7, ODD_RPDO_MAP_5_8},
               #endif
               #if CO_NO_RPDO > 6
                  {ODD_RPDO_MAP_6_1, ODD_RPDO_MAP_6_2, ODD_RPDO_MAP_6_3, ODD_RPDO_MAP_6_4, ODD_RPDO_MAP_6_5, ODD_RPDO_MAP_6_6, ODD_RPDO_MAP_6_7, ODD_RPDO_MAP_6_8},
               #endif
               #if CO_NO_RPDO > 7
                  {ODD_RPDO_MAP_7_1, ODD_RPDO_MAP_7_2, ODD_RPDO_MAP_7_3, ODD_RPDO_MAP_7_4, ODD_RPDO_MAP_7_5, ODD_RPDO_MAP_7_6, ODD_RPDO_MAP_7_7, ODD_RPDO_MAP_7_8},
               #endif
               #if CO_NO_RPDO > 8
                  {ODD_RPDO_MAP_8_1, ODD_RPDO_MAP_8_2, ODD_RPDO_MAP_8_3, ODD_RPDO_MAP_8_4, ODD_RPDO_MAP_8_5, ODD_RPDO_MAP_8_6, ODD_RPDO_MAP_8_7, ODD_RPDO_MAP_8_8},
               #endif
               #if CO_NO_RPDO > 9
                  {ODD_RPDO_MAP_9_1, ODD_RPDO_MAP_9_2, ODD_RPDO_MAP_9_3, ODD_RPDO_MAP_9_4, ODD_RPDO_MAP_9_5, ODD_RPDO_MAP_9_6, ODD_RPDO_MAP_9_7, ODD_RPDO_MAP_9_8},
               #endif
               #if CO_NO_RPDO > 10
                  {ODD_RPDO_MAP_10_1, ODD_RPDO_MAP_10_2, ODD_RPDO_MAP_10_3, ODD_RPDO_MAP_10_4, ODD_RPDO_MAP_10_5, ODD_RPDO_MAP_10_6, ODD_RPDO_MAP_10_7, ODD_RPDO_MAP_10_8},
               #endif
               #if CO_NO_RPDO > 11
                  {ODD_RPDO_MAP_11_1, ODD_RPDO_MAP_11_2, ODD_RPDO_MAP_11_3, ODD_RPDO_MAP_11_4, ODD_RPDO_MAP_11_5, ODD_RPDO_MAP_11_6, ODD_RPDO_MAP_11_7, ODD_RPDO_MAP_11_8},
               #endif
               #if CO_NO_RPDO > 12
                  {ODD_RPDO_MAP_12_1, ODD_RPDO_MAP_12_2, ODD_RPDO_MAP_12_3, ODD_RPDO_MAP_12_4, ODD_RPDO_MAP_12_5, ODD_RPDO_MAP_12_6, ODD_RPDO_MAP_12_7, ODD_RPDO_MAP_12_8},
               #endif
               #if CO_NO_RPDO > 13
                  {ODD_RPDO_MAP_13_1, ODD_RPDO_MAP_13_2, ODD_RPDO_MAP_13_3, ODD_RPDO_MAP_13_4, ODD_RPDO_MAP_13_5, ODD_RPDO_MAP_13_6, ODD_RPDO_MAP_13_7, ODD_RPDO_MAP_13_8},
               #endif
               #if CO_NO_RPDO > 14
                  {ODD_RPDO_MAP_14_1, ODD_RPDO_MAP_14_2, ODD_RPDO_MAP_14_3, ODD_RPDO_MAP_14_4, ODD_RPDO_MAP_14_5, ODD_RPDO_MAP_14_6, ODD_RPDO_MAP_14_7, ODD_RPDO_MAP_14_8},
               #endif
               #if CO_NO_RPDO > 15
                  {ODD_RPDO_MAP_15_1, ODD_RPDO_MAP_15_2, ODD_RPDO_MAP_15_3, ODD_RPDO_MAP_15_4, ODD_RPDO_MAP_15_5, ODD_RPDO_MAP_15_6, ODD_RPDO_MAP_15_7, ODD_RPDO_MAP_15_8},
               #endif
               #if CO_NO_RPDO > 16
                  {ODD_RPDO_MAP_16_1, ODD_RPDO_MAP_16_2, ODD_RPDO_MAP_16_3, ODD_RPDO_MAP_16_4, ODD_RPDO_MAP_16_5, ODD_RPDO_MAP_16_6, ODD_RPDO_MAP_16_7, ODD_RPDO_MAP_16_8},
               #endif
               #if CO_NO_RPDO > 17
                  {ODD_RPDO_MAP_17_1, ODD_RPDO_MAP_17_2, ODD_RPDO_MAP_17_3, ODD_RPDO_MAP_17_4, ODD_RPDO_MAP_17_5, ODD_RPDO_MAP_17_6, ODD_RPDO_MAP_17_7, ODD_RPDO_MAP_17_8},
               #endif
               #if CO_NO_RPDO > 18
                  {ODD_RPDO_MAP_18_1, ODD_RPDO_MAP_18_2, ODD_RPDO_MAP_18_3, ODD_RPDO_MAP_18_4, ODD_RPDO_MAP_18_5, ODD_RPDO_MAP_18_6, ODD_RPDO_MAP_18_7, ODD_RPDO_MAP_18_8},
               #endif
               #if CO_NO_RPDO > 19
                  {ODD_RPDO_MAP_19_1, ODD_RPDO_MAP_19_2, ODD_RPDO_MAP_19_3, ODD_RPDO_MAP_19_4, ODD_RPDO_MAP_19_5, ODD_RPDO_MAP_19_6, ODD_RPDO_MAP_19_7, ODD_RPDO_MAP_19_8},
               #endif
               };
           #endif
           #endif

           #if CO_NO_TPDO > 0
/*0x1800+*/ROM UNSIGNED8      ODE_TPDO_Parameter_NoOfEntries =
           #ifdef CO_TPDO_INH_EV_TIMER
                     5;
           #else
                     2;
           #endif
           ROM CO_sTPDO_param ODE_TPDO_Parameter[CO_NO_TPDO] = {
                  #if ODD_TPDO_PAR_COB_ID_0 == 0
                     {CAN_ID_TPDO0, ODD_TPDO_PAR_T_TYPE_0, ODD_TPDO_PAR_I_TIME_0, ODD_TPDO_PAR_E_TIME_0},
                  #else
                     {ODD_TPDO_PAR_COB_ID_0, ODD_TPDO_PAR_T_TYPE_0, ODD_TPDO_PAR_I_TIME_0, ODD_TPDO_PAR_E_TIME_0},
                  #endif
               #if CO_NO_TPDO > 1
                  #if ODD_TPDO_PAR_COB_ID_1 == 0
                     {CAN_ID_TPDO1, ODD_TPDO_PAR_T_TYPE_1, ODD_TPDO_PAR_I_TIME_1, ODD_TPDO_PAR_E_TIME_1},
                  #else
                     {ODD_TPDO_PAR_COB_ID_1, ODD_TPDO_PAR_T_TYPE_1, ODD_TPDO_PAR_I_TIME_1, ODD_TPDO_PAR_E_TIME_1},
                  #endif
               #endif
               #if CO_NO_TPDO > 2
                  #if ODD_TPDO_PAR_COB_ID_2 == 0
                     {CAN_ID_TPDO2, ODD_TPDO_PAR_T_TYPE_2, ODD_TPDO_PAR_I_TIME_2, ODD_TPDO_PAR_E_TIME_2},
                  #else
                     {ODD_TPDO_PAR_COB_ID_2, ODD_TPDO_PAR_T_TYPE_2, ODD_TPDO_PAR_I_TIME_2, ODD_TPDO_PAR_E_TIME_2},
                  #endif
               #endif
               #if CO_NO_TPDO > 3
                  #if ODD_TPDO_PAR_COB_ID_3 == 0
                     {CAN_ID_TPDO3, ODD_TPDO_PAR_T_TYPE_3, ODD_TPDO_PAR_I_TIME_3, ODD_TPDO_PAR_E_TIME_3},
                  #else
                     {ODD_TPDO_PAR_COB_ID_3, ODD_TPDO_PAR_T_TYPE_3, ODD_TPDO_PAR_I_TIME_3, ODD_TPDO_PAR_E_TIME_3},
                  #endif
               #endif
               #if CO_NO_TPDO > 4
                  {ODD_TPDO_PAR_COB_ID_4, ODD_TPDO_PAR_T_TYPE_4, ODD_TPDO_PAR_I_TIME_4, ODD_TPDO_PAR_E_TIME_4},
               #endif
               #if CO_NO_TPDO > 5
                  {ODD_TPDO_PAR_COB_ID_5, ODD_TPDO_PAR_T_TYPE_5, ODD_TPDO_PAR_I_TIME_5, ODD_TPDO_PAR_E_TIME_5},
               #endif
               #if CO_NO_TPDO > 6
                  {ODD_TPDO_PAR_COB_ID_6, ODD_TPDO_PAR_T_TYPE_6, ODD_TPDO_PAR_I_TIME_6, ODD_TPDO_PAR_E_TIME_6},
               #endif
               #if CO_NO_TPDO > 7
                  {ODD_TPDO_PAR_COB_ID_7, ODD_TPDO_PAR_T_TYPE_7, ODD_TPDO_PAR_I_TIME_7, ODD_TPDO_PAR_E_TIME_7},
               #endif
               };
           #endif

           #ifdef CO_PDO_MAPPING_IN_OD
           #if CO_NO_TPDO > 0
/*0x1A00+*/ROM UNSIGNED8      ODE_TPDO_Mapping_NoOfEntries = 8;
           ROM UNSIGNED32     ODE_TPDO_Mapping[CO_NO_TPDO][8] = {
                  {ODD_TPDO_MAP_0_1, ODD_TPDO_MAP_0_2, ODD_TPDO_MAP_0_3, ODD_TPDO_MAP_0_4, ODD_TPDO_MAP_0_5, ODD_TPDO_MAP_0_6, ODD_TPDO_MAP_0_7, ODD_TPDO_MAP_0_8},
               #if CO_NO_TPDO > 1
                  {ODD_TPDO_MAP_1_1, ODD_TPDO_MAP_1_2, ODD_TPDO_MAP_1_3, ODD_TPDO_MAP_1_4, ODD_TPDO_MAP_1_5, ODD_TPDO_MAP_1_6, ODD_TPDO_MAP_1_7, ODD_TPDO_MAP_1_8},
               #endif
               #if CO_NO_TPDO > 2
                  {ODD_TPDO_MAP_2_1, ODD_TPDO_MAP_2_2, ODD_TPDO_MAP_2_3, ODD_TPDO_MAP_2_4, ODD_TPDO_MAP_2_5, ODD_TPDO_MAP_2_6, ODD_TPDO_MAP_2_7, ODD_TPDO_MAP_2_8},
               #endif
               #if CO_NO_TPDO > 3
                  {ODD_TPDO_MAP_3_1, ODD_TPDO_MAP_3_2, ODD_TPDO_MAP_3_3, ODD_TPDO_MAP_3_4, ODD_TPDO_MAP_3_5, ODD_TPDO_MAP_3_6, ODD_TPDO_MAP_3_7, ODD_TPDO_MAP_3_8},
               #endif
               #if CO_NO_TPDO > 4
                  {ODD_TPDO_MAP_4_1, ODD_TPDO_MAP_4_2, ODD_TPDO_MAP_4_3, ODD_TPDO_MAP_4_4, ODD_TPDO_MAP_4_5, ODD_TPDO_MAP_4_6, ODD_TPDO_MAP_4_7, ODD_TPDO_MAP_4_8},
               #endif
               #if CO_NO_TPDO > 5
                  {ODD_TPDO_MAP_5_1, ODD_TPDO_MAP_5_2, ODD_TPDO_MAP_5_3, ODD_TPDO_MAP_5_4, ODD_TPDO_MAP_5_5, ODD_TPDO_MAP_5_6, ODD_TPDO_MAP_5_7, ODD_TPDO_MAP_5_8},
               #endif
               #if CO_NO_TPDO > 6
                  {ODD_TPDO_MAP_6_1, ODD_TPDO_MAP_6_2, ODD_TPDO_MAP_6_3, ODD_TPDO_MAP_6_4, ODD_TPDO_MAP_6_5, ODD_TPDO_MAP_6_6, ODD_TPDO_MAP_6_7, ODD_TPDO_MAP_6_8},
               #endif
               #if CO_NO_TPDO > 7
                  {ODD_TPDO_MAP_7_1, ODD_TPDO_MAP_7_2, ODD_TPDO_MAP_7_3, ODD_TPDO_MAP_7_4, ODD_TPDO_MAP_7_5, ODD_TPDO_MAP_7_6, ODD_TPDO_MAP_7_7, ODD_TPDO_MAP_7_8},
               #endif
               };
           #endif
           #endif

/*0x1F80*/ ROM UNSIGNED32     ODE_NMT_Startup = ODD_NMT_STARTUP;


/***** Manufacturer specific variables ****************************************/
/*0x2100*/ extern unsigned char CO_ErrorStatusBits[ERROR_NO_OF_BYTES];
///*0x2101*/ ROM UNSIGNED8      ODE_CANnodeID = ODD_CANnodeID;
                //this entry can be replaced with DIP switches on printed board
///*0x2102*/ ROM UNSIGNED8      ODE_CANbitRate = ODD_CANbitRate;
                //this entry can be replaced with DIP switches on printed board
           #if CO_NO_SYNC > 0
/*0x2103*/ extern volatile unsigned int CO_SYNCcounter;
                //variable is incremented after SYNC message
/*0x2104*/ extern volatile unsigned int CO_SYNCtime;
                //variable is incremented every 1ms, after SYNC message it is set to 0
           #endif















































/***** Manufacturer specific EEPROM DATA **************************************/
//Data in following structure are read from EEPROM at microcontroller intialisation
//and is written automatically to EEPROM when changed. Structure is defined in CO_OD.h
               sODE_EEPROM    ODE_EEPROM;
               unsigned char* CO_EEPROM_pointer = (unsigned char*) &ODE_EEPROM;
           ROM unsigned int   CO_EEPROM_size = sizeof(ODE_EEPROM);





		   ROM UNSIGNED8 ODE_DEVICEPARAM_NUMBER_ENTRIES=11;
		   ROM UNSIGNED8 ODE_PLCPARAM_NUMBER_ENTRIES=2;
		   ROM UNSIGNED8 ODE_MODBUSPARAM_NUMBER_ENTRIES=2;
		   ROM UNSIGNED8 ODE_LCDPARAM_NUMBER_ENTRIES=6;
		   ROM UNSIGNED8 ODE_SERIALPARAM_NUMBER_ENTRIES=1;
		   ROM UNSIGNED8 ODE_PLC_MAPMEM_NUMBER_ENTRIES=1;
		   ROM UNSIGNED8 ODE_RFID_NUMBER_ENTRIES=34;
		   ROM UNSIGNED8 ODE_CLOCK_NUMBER_ENTRIES=6;





/*0x2107 IO Port Parameters*/
/* 	 sub 1 */	ROM UNSIGNED8	  	adc_Number=0;			// Number of Analog Inputs
/* 	 sub 2 */	ROM UNSIGNED8	  	tris_PortX1=0;			// port X1 - 1 input 0 output
/* 	 sub 3 */	ROM UNSIGNED8	  	tris_PortX2=0;			// port X2 - 1 input 0 output
/* 	 sub 4 */	ROM UNSIGNED16	  	tris_PortX3=0;			// port X3 - 1 input 0 output
/* 	 sub 5 */   ROM UNSIGNED8 	  	tempS_Enabled=1;		// LM35 Temp Sensor enabled
/*   DEFAULT VALUES AT START UP */
/* 	 sub 6 */	ROM UNSIGNED8	  	default_PortX1=0;		// default value port X1 
/* 	 sub 7 */	ROM UNSIGNED8	  	default_PortX2=0;		// default value port X2 
/* 	 sub 8 */	ROM UNSIGNED16	  	default_PortX3=0;		// default value port X3 
/*   sub 9 */	/* In eeprom */
/*   SAVE VALUES AND RESTORE AT REBOOT */
/*	 sub A */	ROM UNSIGNED8	  	save_PortX1=0;			// save value port X1 
/*	 sub B*/	ROM UNSIGNED8	  	save_PortX2=0;			// save value port X2 
/* 	 sub C */	ROM UNSIGNED8	  	save_PortX3=0;			// save value port X3 
/*   PORT TYPE - 1 analog -0 digital */
/*	 sub D */	ROM UNSIGNED8	  	type_PortX1=0;			// type port X1 
/*	 sub E */	ROM UNSIGNED8	  	type_PortX2=0;			// type port X2 
/* 	 sub F */	ROM UNSIGNED16	  	type_PortX3=0;			// type port X3 
/*	 sub 10 */  ROM UNSIGNED8		saveTPDOFlags=0;		// Save TPDO to EPROM flags (bit0: TPDO0, bit1: TPDO2, ...)

/*0x2108 PLC Parameters */     	
/* 	 sub 1 */	ROM UNSIGNED8	  	plc_Enabled=0;			// plc Process Enabled
/* 	 sub 2 */	ROM UNSIGNED8     	plc_Program1[248];		// 248 bytes de programa
/* 	 sub 2 */	ROM UNSIGNED8     	plc_Program2[248];		// 248 bytes de programa

/*0x2109 Modbus Parameters */     	
/* 	 sub 1 */	ROM UNSIGNED8	  	mb_Type=2;				// 0 Disabled 1 Master 2 Slave
/* 	 sub 2 */	ROM UNSIGNED8     	mb_NodeId=1;			// Modbus node id

/*0x2111 Serial Parameters */
/*   sub 1 */	ROM UNSIGNED8		serial_baudrate=3;		// 9600, 19200, 38400, 57600, 115200

/*0x2113 RFID Parameters */
/*   sub 1 */	ROM UNSIGNED8		rfid_readerOn=0;		// Lector apagado
/*   sub 2 */	ROM UNSIGNED8		rfid_IDCount=1;			// Numero de IDs
/*   sub 3+ */	ROM UNSIGNED32		rfid_IDList[32]={		// Lista de IDs
										0xEA92E872,			// 1
										0x0,				// 2
										0x0,				// 3
										0x0,				// 4
										0x0,				// 5
										0x0,				// 6
										0x0,				// 7
										0x0,				// 8
										0x0,				// 9
										0x0,				// 10
										0x0,				// 11
										0x0,				// 12
										0x0,				// 13
										0x0,				// 14
										0x0,				// 15
										0x0,				// 16
										0x0,				// 17
										0x0,				// 18
										0x0,				// 19
										0x0,				// 20
										0x0,				// 21
										0x0,				// 22
										0x0,				// 23
										0x0,				// 24
										0x0,				// 25
										0x0,				// 26
										0x0,				// 27
										0x0,				// 28
										0x0,				// 29
										0x0,				// 30
										0x0,				// 31
									};

			UNSIGNED16			temp_TimerCount;

			UNSIGNED16			clk_yy;			// year
			UNSIGNED8			clk_MM;			// month
			UNSIGNED8			clk_dd;			// day
			UNSIGNED8			clk_hh;			// hour
			UNSIGNED8			clk_mm;			// minutes
			UNSIGNED8			clk_ss;			// seconds
			UNSIGNED16			clk_mlsec;		// Milliseconds
			UNSIGNED8			clk_Updated;	// Clock Updated

			UNSIGNED16			bl_Version;

			ROM UNSIGNED8      ODE_Read_Digital_Input_NoOfEntries = 8;
			ROM UNSIGNED8      ODE_Write_Digital_Output_NoOfEntries = 4;
			ROM UNSIGNED8      ODE_Read_Analog_Input_NoOfEntries = 8;
			ROM UNSIGNED8      ODE_Write_Analog_Output_NoOfEntries = 2;


/***** Device profile for Generic I/O *****************************************/
/*
           #ifdef CO_IO_DIGITAL_INPUTS
//0x6000 
			ROM UNSIGNED8      ODE_Read_Digital_Input_NoOfEntries = 8;
               tData4bytes    ODE_Read_Digital_Input;
           #endif

           #ifdef CO_IO_DIGITAL_OUTPUTS
//0x6200
			ROM UNSIGNED8      ODE_Write_Digital_Output_NoOfEntries = 8;
               tData4bytes    ODE_Write_Digital_Output;
           #endif

           #ifdef CO_IO_ANALOG_INPUTS
//0x6401   
			ROM UNSIGNED8      ODE_Read_Analog_Input_NoOfEntries = 8;
               INTEGER16      ODE_Read_Analog_Input[8];
           #endif

           #ifdef CO_IO_ANALOG_OUTPUTS
//0x6411 
			ROM UNSIGNED8      ODE_Write_Analog_Output_NoOfEntries = 2;
               INTEGER16      ODE_Write_Analog_Output[2];
           #endif
/

#ifdef __18CXX
   #pragma romdata //return to the default section
#endif


/******************************************************************************/
/*     VERIFY FUNCTION      ***************************************************/
/******************************************************************************/
//SDO server verifies new values, before they are written to Object Dictionary
//Typical Error codes:
//       0x06090030L   Value range of parameter exceeded
//       0x06090031L   Value of parameter written too high
//       0x06090032L   Value of parameter written too low
#ifdef CO_VERIFY_OD_WRITE
unsigned long CO_OD_VerifyWrite(ROM CO_objectDictionaryEntry* pODE, void* data){
   unsigned int index;
   
   index = pODE->index;

   if(index > 0x1200u && index <= 0x12FFu) index &= 0xFF80;//All SDO
   if(index > 0x1400u && index <= 0x1BFFu) index &= 0xFE00;//All PDO

   switch(index){
      unsigned char i;
	
	case 0x2114:
		clk_Updated = 1;
		break;

   #if CO_NO_ERROR_FIELD > 0
   case 0x1003://Pre Defined Error Field
               if(*((unsigned char*)data) > ODE_Pre_Defined_Error_Field_NoOfErrors)
                  return 0x06090031L;  //Value of parameter written too high
               break;
   #endif

   #if CO_NO_SYNC > 0
   case 0x1005://SYNC COB ID
               if(*((unsigned long*)data) & 0xBFFFF800L)
                  return 0x08000020L;  //Data can not be transferred or stored to the application
               if((ODE_SYNC_COB_ID & 0x40000000L) &&
                  (*((unsigned int*)data) != (ODE_SYNC_COB_ID&0x7FF)))
                  return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               break;

   case 0x1006:   //Communication Cycle Period
               if(*((unsigned int*)data) != 0u && *((unsigned int*)data) < 3000u)
                  return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
   #endif

   #if CO_NO_CONS_HEARTBEAT > 0
   case 0x1016://Consumer Heartbeat Time
               if(*((unsigned long*)data) & 0xFF800000L)
                  return 0x08000020L;  //Data can not be transferred or stored to the application
               for(i = 0; i<CO_NO_CONS_HEARTBEAT; i++){
                  if((*((unsigned long*)data)>>16) == (ODE_Consumer_Heartbeat_Time[i]>>16) &&   //same NodeID
                     (pODE->subindex-1) != i && //different subindex
                     *((unsigned int*)(data)) != 0u &&    //time nonzero
                     (ODE_Consumer_Heartbeat_Time[i]&0xFFFF) != 0u) //time nonzero
                     return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               }
               break;
   #endif

   #if CO_NO_SDO_SERVER > 0
   case 0x1200://Server SDO Parameter
               if(pODE->subindex == 1u || pODE->subindex == 2u){
                  //unsigned long COB_ID;
                  //if(pODE->subindex == 1) COB_ID = ODE_Server_SDO_Parameter[pODE->index&0x7F].COB_ID_Client_to_Server;
                  //else                    COB_ID = ODE_Server_SDO_Parameter[pODE->index&0x7F].COB_ID_Server_to_Client;
                  if((*((unsigned long*)data) & 0x7FFFF800L))
                     return 0x08000020L;  //Data can not be transferred or stored to the application
                  //if(*((unsigned int*)(data)) != (COB_ID&0xFFFF) &&   //Different COB ID
                  //   !(COB_ID&0x80000000L))   //bit 31 is 0 (SDO in use)
                  //   return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               }
               break;
   #endif

   #if CO_NO_SDO_CLIENT > 0
   case 0x1280://Client SDO Parameter
               if(pODE->subindex == 1 || pODE->subindex == 2){
                  //unsigned long COB_ID;
                  //if(pODE->subindex == 1) COB_ID = ODE_Client_SDO_Parameter[pODE->index&0x7F].COB_ID_Client_to_Server;
                  //else                    COB_ID = ODE_Client_SDO_Parameter[pODE->index&0x7F].COB_ID_Server_to_Client;
                  if((*((unsigned long*)data) & 0x7FFFF800L))
                     return 0x08000020L;  //Data can not be transferred or stored to the application                  //if(*((unsigned int*)(data)) != (COB_ID&0xFFFF) &&   //Different COB ID
                  //   !(COB_ID&0x80000000L))   //bit 31 is 0 (SDO in use)
                  //   return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               }
               break;
   #endif

   #if CO_NO_RPDO > 0
   case 0x1400://Receive PDO Parameter
               if(pODE->subindex == 1u){
                  //unsigned long COB_ID = ODE_RPDO_Parameter[pODE->index&0x1FF].COB_ID;
                  if((*((unsigned long*)data) & 0x3FFFF800L) || !(*((unsigned long*)data) & 0x40000000L))
                     return 0x08000020L;  //Data can not be transferred or stored to the application
                  //if(*((unsigned int*)(data)) != (COB_ID&0xFFFF) &&   //Different COB ID
                  //   !(COB_ID&0x80000000L))   //bit 31 is 0 (PDO in use)
                  //   return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               }
               break;
   #endif

   #if CO_NO_TPDO > 0
   case 0x1800://Transmit PDO Parameter
               if(pODE->subindex == 1u){
                  //unsigned long COB_ID = ODE_TPDO_Parameter[pODE->index&0x1FF].COB_ID;
                  if((*((unsigned long*)data) & 0x3FFFF800L) || !(*((unsigned long*)data) & 0x40000000L))
                     return 0x08000020L;  //Data can not be transferred or stored to the application
                  //if(*((unsigned int*)(data)) != (COB_ID&0xFFFF) &&   //Different COB ID
                  //   !(COB_ID&0x80000000L))   //bit 31 is 0 (PDO in use)
                  //   return 0x08000022L;  //Data can not be transferred or stored to the application because of the present device state
               }
               break;
   #endif

   case 0x1F80://NMT Startup
               if(*((unsigned long*)data) & 0xFFFFFFFBL)
                  return 0x08000020L;  //Data can not be transferred or stored to the application
               break;

   case 0x2101://CAN Node ID
               if(*((unsigned char*)data) < 1u)
                  return 0x06090032L;  //Value of parameter written too low
               else if(*((unsigned char*)data) > 127u)
                  return 0x06090031L;  //Value of parameter written too high
               break;

   case 0x2102://CAN Bit RAte
               if(*((unsigned char*)data) > 7u)
                  return 0x06090031L;  //Value of parameter written too high
               break;

   }//end switch
   return 0L;
}
#endif

/******************************************************************************/
/*     OBJECT DICTIONARY                                                      */
/* Entries in CO_OD[] must be ordered. If not, disable macro CO_OD_IS_ORDERED */
/******************************************************************************/
//macro for add entry to object dictionary
#define OD_ENTRY(Index, Subindex, Attribute, Variable) \
     {Index, Subindex, Attribute, sizeof(Variable), (ROM void*)&Variable}

ROM CO_objectDictionaryEntry CO_OD[] = {
   OD_ENTRY(0x1000, 0x00, ATTR_RO|ATTR_ROM, ODE_Device_Type),
   OD_ENTRY(0x1001, 0x00, ATTR_RO, ODE_Error_Register),
   OD_ENTRY(0x1002, 0x00, ATTR_RO, ODE_Manufacturer_Status_Register),

   #if CO_NO_ERROR_FIELD > 0
      OD_ENTRY(0x1003, 0x00, ATTR_RW, ODE_Pre_Defined_Error_Field_NoOfErrors),
      OD_ENTRY(0x1003, 0x01, ATTR_RO, ODE_Pre_Defined_Error_Field[0]),
      OD_ENTRY(0x1003, 0x02, ATTR_RO, ODE_Pre_Defined_Error_Field[1]),
      OD_ENTRY(0x1003, 0x03, ATTR_RO, ODE_Pre_Defined_Error_Field[2]),
      OD_ENTRY(0x1003, 0x04, ATTR_RO, ODE_Pre_Defined_Error_Field[3]),
      OD_ENTRY(0x1003, 0x05, ATTR_RO, ODE_Pre_Defined_Error_Field[4]),
      OD_ENTRY(0x1003, 0x06, ATTR_RO, ODE_Pre_Defined_Error_Field[5]),
      OD_ENTRY(0x1003, 0x07, ATTR_RO, ODE_Pre_Defined_Error_Field[6]),
      OD_ENTRY(0x1003, 0x08, ATTR_RO, ODE_Pre_Defined_Error_Field[7]),
   #endif

   #if CO_NO_SYNC > 0
      OD_ENTRY(0x1005, 0x00, ATTR_RW|ATTR_ROM, ODE_SYNC_COB_ID),
      OD_ENTRY(0x1006, 0x00, ATTR_RW|ATTR_ROM, ODE_Communication_Cycle_Period),
      OD_ENTRY(0x1007, 0x00, ATTR_RW|ATTR_ROM, ODE_Synchronous_Window_Length),
   #endif

   OD_ENTRY(0x1008, 0x00, ATTR_RO|ATTR_ROM, ODE_Manufacturer_Device_Name),
   OD_ENTRY(0x1009, 0x00, ATTR_RO|ATTR_ROM, ODE_Manufacturer_Hardware_Version),
   OD_ENTRY(0x100A, 0x00, ATTR_RO|ATTR_ROM, ODE_Manufacturer_Software_Version),

   #if CO_NO_EMERGENCY > 0
      OD_ENTRY(0x1014, 0x00, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_Emergency_COB_ID),
      OD_ENTRY(0x1015, 0x00, ATTR_RW|ATTR_ROM, ODE_Inhibit_Time_Emergency),
   #endif

   #if CO_NO_CONS_HEARTBEAT > 0
      OD_ENTRY(0x1016, 0x00, ATTR_RO|ATTR_ROM, ODE_Consumer_Heartbeat_Time_NoOfEntries),
      OD_ENTRY(0x1016, 0x01, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[0]),
      #if CO_NO_CONS_HEARTBEAT > 1
         OD_ENTRY(0x1016, 0x02, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[1]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 2
         OD_ENTRY(0x1016, 0x03, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[2]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 3
         OD_ENTRY(0x1016, 0x04, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[3]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 4
         OD_ENTRY(0x1016, 0x05, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[4]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 5
         OD_ENTRY(0x1016, 0x06, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[5]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 6
         OD_ENTRY(0x1016, 0x07, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[6]),
      #endif
      #if CO_NO_CONS_HEARTBEAT > 7
         OD_ENTRY(0x1016, 0x08, ATTR_RW|ATTR_ROM, ODE_Consumer_Heartbeat_Time[7]),
      #endif
   #endif

   OD_ENTRY(0x1017, 0x00, ATTR_RW|ATTR_ROM, ODE_Producer_Heartbeat_Time),
   OD_ENTRY(0x1018, 0x00, ATTR_RO|ATTR_ROM, ODE_Identity.NoOfEntries),
   OD_ENTRY(0x1018, 0x01, ATTR_RO|ATTR_ROM, ODE_Identity.Vendor_ID),
   OD_ENTRY(0x1018, 0x02, ATTR_RO|ATTR_ROM, ODE_Identity.Product_Code),
   OD_ENTRY(0x1018, 0x03, ATTR_RO|ATTR_ROM, ODE_Identity.Revision_Number),
   OD_ENTRY(0x1018, 0x04, ATTR_RO|ATTR_ROM, ODE_Identity.Serial_Number),
   OD_ENTRY(0x1029, 0x00, ATTR_RO|ATTR_ROM, ODE_Error_Behavior.NoOfEntries),
   OD_ENTRY(0x1029, 0x01, ATTR_RW|ATTR_ROM, ODE_Error_Behavior.Communication_Error),

   #if CO_NO_SDO_SERVER > 0
      OD_ENTRY(0x1200, 0x00, ATTR_RO|ATTR_ROM, ODE_Server_SDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1200, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_Server_SDO_Parameter[0].COB_ID_Client_to_Server),
      OD_ENTRY(0x1200, 0x02, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_Server_SDO_Parameter[0].COB_ID_Server_to_Client),
   #endif

   #if CO_NO_SDO_CLIENT > 0
      OD_ENTRY(0x1280, 0x00, ATTR_RO|ATTR_ROM, ODE_Client_SDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1280, 0x01, ATTR_RW, ODE_Client_SDO_Parameter[0].COB_ID_Client_to_Server),
      OD_ENTRY(0x1280, 0x02, ATTR_RW, ODE_Client_SDO_Parameter[0].COB_ID_Server_to_Client),
      OD_ENTRY(0x1280, 0x03, ATTR_RW, ODE_Client_SDO_Parameter[0].NODE_ID_of_SDO_Client_or_Server),
   #endif

   #ifdef CO_PDO_PARAM_IN_OD
   #if CO_NO_RPDO > 0
      OD_ENTRY(0x1400, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      #if ODD_RPDO_PAR_COB_ID_0 == 0
         OD_ENTRY(0x1400, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_RPDO_Parameter[0].COB_ID),
      #else
         OD_ENTRY(0x1400, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[0].COB_ID),
      #endif
      OD_ENTRY(0x1400, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[0].Transmission_type),
   #endif
   #if CO_NO_RPDO > 1
      OD_ENTRY(0x1401, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      #if ODD_RPDO_PAR_COB_ID_1 == 0
         OD_ENTRY(0x1401, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_RPDO_Parameter[1].COB_ID),
      #else
         OD_ENTRY(0x1401, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[1].COB_ID),
      #endif
      OD_ENTRY(0x1401, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[1].Transmission_type),
   #endif
   #if CO_NO_RPDO > 2
      OD_ENTRY(0x1402, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      #if ODD_RPDO_PAR_COB_ID_2 == 0
         OD_ENTRY(0x1402, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_RPDO_Parameter[2].COB_ID),
      #else
         OD_ENTRY(0x1402, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[2].COB_ID),
      #endif
      OD_ENTRY(0x1402, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[2].Transmission_type),
   #endif
   #if CO_NO_RPDO > 3
      OD_ENTRY(0x1403, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      #if ODD_RPDO_PAR_COB_ID_3 == 0
         OD_ENTRY(0x1403, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_RPDO_Parameter[3].COB_ID),
      #else
         OD_ENTRY(0x1403, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[3].COB_ID),
      #endif
      OD_ENTRY(0x1403, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[3].Transmission_type),
   #endif
   #if CO_NO_RPDO > 4
      OD_ENTRY(0x1404, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1404, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[4].COB_ID),
      OD_ENTRY(0x1404, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[4].Transmission_type),
   #endif
   #if CO_NO_RPDO > 5
      OD_ENTRY(0x1405, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1405, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[5].COB_ID),
      OD_ENTRY(0x1405, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[5].Transmission_type),
   #endif
   #if CO_NO_RPDO > 6
      OD_ENTRY(0x1406, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1406, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[6].COB_ID),
      OD_ENTRY(0x1406, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[6].Transmission_type),
   #endif
   #if CO_NO_RPDO > 7
      OD_ENTRY(0x1407, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1407, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[7].COB_ID),
      OD_ENTRY(0x1407, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[7].Transmission_type),
   #endif
   #if CO_NO_RPDO > 8
      OD_ENTRY(0x1408, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1408, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[8].COB_ID),
      OD_ENTRY(0x1408, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[8].Transmission_type),
   #endif
   #if CO_NO_RPDO > 9
      OD_ENTRY(0x1409, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1409, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[9].COB_ID),
      OD_ENTRY(0x1409, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[9].Transmission_type),
   #endif
   #if CO_NO_RPDO > 10
      OD_ENTRY(0x140A, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140A, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[10].COB_ID),
      OD_ENTRY(0x140A, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[10].Transmission_type),
   #endif
   #if CO_NO_RPDO > 11
      OD_ENTRY(0x140B, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140B, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[11].COB_ID),
      OD_ENTRY(0x140B, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[11].Transmission_type),
   #endif
   #if CO_NO_RPDO > 12
      OD_ENTRY(0x140C, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140C, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[12].COB_ID),
      OD_ENTRY(0x140C, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[12].Transmission_type),
   #endif
   #if CO_NO_RPDO > 13
      OD_ENTRY(0x140D, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140D, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[13].COB_ID),
      OD_ENTRY(0x140D, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[13].Transmission_type),
   #endif
   #if CO_NO_RPDO > 14
      OD_ENTRY(0x140E, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140E, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[14].COB_ID),
      OD_ENTRY(0x140E, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[14].Transmission_type),
   #endif
   #if CO_NO_RPDO > 15
      OD_ENTRY(0x140F, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x140F, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[15].COB_ID),
      OD_ENTRY(0x140F, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[15].Transmission_type),
   #endif
   #if CO_NO_RPDO > 16
      OD_ENTRY(0x1410, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1410, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[16].COB_ID),
      OD_ENTRY(0x1410, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[16].Transmission_type),
   #endif
   #if CO_NO_RPDO > 17
      OD_ENTRY(0x1411, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1411, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[17].COB_ID),
      OD_ENTRY(0x1411, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[17].Transmission_type),
   #endif
   #if CO_NO_RPDO > 18
      OD_ENTRY(0x1412, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1412, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[18].COB_ID),
      OD_ENTRY(0x1412, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[18].Transmission_type),
   #endif
   #if CO_NO_RPDO > 19
      OD_ENTRY(0x1413, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1413, 0x01, ATTR_RW|ATTR_ROM, ODE_RPDO_Parameter[19].COB_ID),
      OD_ENTRY(0x1413, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Parameter[19].Transmission_type),
   #endif
   #endif

   #ifdef CO_PDO_MAPPING_IN_OD
   #if CO_NO_RPDO > 0
      OD_ENTRY(0x1600, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1600, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][0]),
      OD_ENTRY(0x1600, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][1]),
      OD_ENTRY(0x1600, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][2]),
      OD_ENTRY(0x1600, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][3]),
      OD_ENTRY(0x1600, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][4]),
      OD_ENTRY(0x1600, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][5]),
      OD_ENTRY(0x1600, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][6]),
      OD_ENTRY(0x1600, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[0][7]),
   #endif
   #if CO_NO_RPDO > 1
      OD_ENTRY(0x1601, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1601, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][0]),
      OD_ENTRY(0x1601, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][1]),
      OD_ENTRY(0x1601, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][2]),
      OD_ENTRY(0x1601, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][3]),
      OD_ENTRY(0x1601, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][4]),
      OD_ENTRY(0x1601, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][5]),
      OD_ENTRY(0x1601, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][6]),
      OD_ENTRY(0x1601, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[1][7]),
   #endif
   #if CO_NO_RPDO > 2
      OD_ENTRY(0x1602, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1602, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][0]),
      OD_ENTRY(0x1602, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][1]),
      OD_ENTRY(0x1602, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][2]),
      OD_ENTRY(0x1602, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][3]),
      OD_ENTRY(0x1602, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][4]),
      OD_ENTRY(0x1602, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][5]),
      OD_ENTRY(0x1602, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][6]),
      OD_ENTRY(0x1602, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[2][7]),
   #endif
   #if CO_NO_RPDO > 3
      OD_ENTRY(0x1603, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1603, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][0]),
      OD_ENTRY(0x1603, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][1]),
      OD_ENTRY(0x1603, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][2]),
      OD_ENTRY(0x1603, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][3]),
      OD_ENTRY(0x1603, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][4]),
      OD_ENTRY(0x1603, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][5]),
      OD_ENTRY(0x1603, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][6]),
      OD_ENTRY(0x1603, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[3][7]),
   #endif
   #if CO_NO_RPDO > 4
      OD_ENTRY(0x1604, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1604, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][0]),
      OD_ENTRY(0x1604, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][1]),
      OD_ENTRY(0x1604, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][2]),
      OD_ENTRY(0x1604, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][3]),
      OD_ENTRY(0x1604, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][4]),
      OD_ENTRY(0x1604, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][5]),
      OD_ENTRY(0x1604, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][6]),
      OD_ENTRY(0x1604, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[4][7]),
   #endif
   #if CO_NO_RPDO > 5
      OD_ENTRY(0x1605, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1605, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][0]),
      OD_ENTRY(0x1605, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][1]),
      OD_ENTRY(0x1605, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][2]),
      OD_ENTRY(0x1605, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][3]),
      OD_ENTRY(0x1605, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][4]),
      OD_ENTRY(0x1605, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][5]),
      OD_ENTRY(0x1605, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][6]),
      OD_ENTRY(0x1605, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[5][7]),
   #endif
   #if CO_NO_RPDO > 6
      OD_ENTRY(0x1606, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1606, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][0]),
      OD_ENTRY(0x1606, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][1]),
      OD_ENTRY(0x1606, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][2]),
      OD_ENTRY(0x1606, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][3]),
      OD_ENTRY(0x1606, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][4]),
      OD_ENTRY(0x1606, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][5]),
      OD_ENTRY(0x1606, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][6]),
      OD_ENTRY(0x1606, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[6][7]),
   #endif
   #if CO_NO_RPDO > 7
      OD_ENTRY(0x1607, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1607, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][0]),
      OD_ENTRY(0x1607, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][1]),
      OD_ENTRY(0x1607, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][2]),
      OD_ENTRY(0x1607, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][3]),
      OD_ENTRY(0x1607, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][4]),
      OD_ENTRY(0x1607, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][5]),
      OD_ENTRY(0x1607, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][6]),
      OD_ENTRY(0x1607, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[7][7]),
   #endif
   #if CO_NO_RPDO > 8
      OD_ENTRY(0x1608, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1608, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][0]),
      OD_ENTRY(0x1608, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][1]),
      OD_ENTRY(0x1608, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][2]),
      OD_ENTRY(0x1608, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][3]),
      OD_ENTRY(0x1608, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][4]),
      OD_ENTRY(0x1608, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][5]),
      OD_ENTRY(0x1608, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][6]),
      OD_ENTRY(0x1608, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[8][7]),
   #endif
   #if CO_NO_RPDO > 9
      OD_ENTRY(0x1609, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1609, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][0]),
      OD_ENTRY(0x1609, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][1]),
      OD_ENTRY(0x1609, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][2]),
      OD_ENTRY(0x1609, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][3]),
      OD_ENTRY(0x1609, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][4]),
      OD_ENTRY(0x1609, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][5]),
      OD_ENTRY(0x1609, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][6]),
      OD_ENTRY(0x1609, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[9][7]),
   #endif
   #if CO_NO_RPDO > 10
      OD_ENTRY(0x160A, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160A, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][0]),
      OD_ENTRY(0x160A, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][1]),
      OD_ENTRY(0x160A, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][2]),
      OD_ENTRY(0x160A, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][3]),
      OD_ENTRY(0x160A, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][4]),
      OD_ENTRY(0x160A, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][5]),
      OD_ENTRY(0x160A, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][6]),
      OD_ENTRY(0x160A, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[10][7]),
   #endif
   #if CO_NO_RPDO > 11
      OD_ENTRY(0x160B, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160B, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][0]),
      OD_ENTRY(0x160B, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][1]),
      OD_ENTRY(0x160B, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][2]),
      OD_ENTRY(0x160B, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][3]),
      OD_ENTRY(0x160B, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][4]),
      OD_ENTRY(0x160B, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][5]),
      OD_ENTRY(0x160B, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][6]),
      OD_ENTRY(0x160B, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[11][7]),
   #endif
   #if CO_NO_RPDO > 12
      OD_ENTRY(0x160C, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160C, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][0]),
      OD_ENTRY(0x160C, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][1]),
      OD_ENTRY(0x160C, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][2]),
      OD_ENTRY(0x160C, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][3]),
      OD_ENTRY(0x160C, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][4]),
      OD_ENTRY(0x160C, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][5]),
      OD_ENTRY(0x160C, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][6]),
      OD_ENTRY(0x160C, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[12][7]),
   #endif
   #if CO_NO_RPDO > 13
      OD_ENTRY(0x160D, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160D, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][0]),
      OD_ENTRY(0x160D, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][1]),
      OD_ENTRY(0x160D, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][2]),
      OD_ENTRY(0x160D, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][3]),
      OD_ENTRY(0x160D, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][4]),
      OD_ENTRY(0x160D, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][5]),
      OD_ENTRY(0x160D, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][6]),
      OD_ENTRY(0x160D, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[13][7]),
   #endif
   #if CO_NO_RPDO > 14
      OD_ENTRY(0x160E, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160E, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][0]),
      OD_ENTRY(0x160E, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][1]),
      OD_ENTRY(0x160E, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][2]),
      OD_ENTRY(0x160E, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][3]),
      OD_ENTRY(0x160E, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][4]),
      OD_ENTRY(0x160E, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][5]),
      OD_ENTRY(0x160E, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][6]),
      OD_ENTRY(0x160E, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[14][7]),
   #endif
   #if CO_NO_RPDO > 15
      OD_ENTRY(0x160F, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x160F, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][0]),
      OD_ENTRY(0x160F, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][1]),
      OD_ENTRY(0x160F, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][2]),
      OD_ENTRY(0x160F, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][3]),
      OD_ENTRY(0x160F, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][4]),
      OD_ENTRY(0x160F, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][5]),
      OD_ENTRY(0x160F, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][6]),
      OD_ENTRY(0x160F, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[15][7]),
   #endif
   #if CO_NO_RPDO > 16
      OD_ENTRY(0x1610, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1610, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][0]),
      OD_ENTRY(0x1610, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][1]),
      OD_ENTRY(0x1610, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][2]),
      OD_ENTRY(0x1610, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][3]),
      OD_ENTRY(0x1610, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][4]),
      OD_ENTRY(0x1610, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][5]),
      OD_ENTRY(0x1610, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][6]),
      OD_ENTRY(0x1610, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[16][7]),
   #endif
   #if CO_NO_RPDO > 17
      OD_ENTRY(0x1611, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1611, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][0]),
      OD_ENTRY(0x1611, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][1]),
      OD_ENTRY(0x1611, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][2]),
      OD_ENTRY(0x1611, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][3]),
      OD_ENTRY(0x1611, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][4]),
      OD_ENTRY(0x1611, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][5]),
      OD_ENTRY(0x1611, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][6]),
      OD_ENTRY(0x1611, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[17][7]),
   #endif
   #if CO_NO_RPDO > 18
      OD_ENTRY(0x1612, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1612, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][0]),
      OD_ENTRY(0x1612, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][1]),
      OD_ENTRY(0x1612, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][2]),
      OD_ENTRY(0x1612, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][3]),
      OD_ENTRY(0x1612, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][4]),
      OD_ENTRY(0x1612, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][5]),
      OD_ENTRY(0x1612, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][6]),
      OD_ENTRY(0x1612, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[18][7]),
   #endif
   #if CO_NO_RPDO > 16
      OD_ENTRY(0x1613, 0x00, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1613, 0x01, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][0]),
      OD_ENTRY(0x1613, 0x02, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][1]),
      OD_ENTRY(0x1613, 0x03, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][2]),
      OD_ENTRY(0x1613, 0x04, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][3]),
      OD_ENTRY(0x1613, 0x05, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][4]),
      OD_ENTRY(0x1613, 0x06, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][5]),
      OD_ENTRY(0x1613, 0x07, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][6]),
      OD_ENTRY(0x1613, 0x08, ATTR_RO|ATTR_ROM, ODE_RPDO_Mapping[19][7]),
   #endif
   #endif

   #ifdef CO_PDO_PARAM_IN_OD
   #if CO_NO_TPDO > 0
      OD_ENTRY(0x1800, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      #if ODD_TPDO_PAR_COB_ID_0 == 0
         OD_ENTRY(0x1800, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_TPDO_Parameter[0].COB_ID),
      #else
         OD_ENTRY(0x1800, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[0].COB_ID),
      #endif
      OD_ENTRY(0x1800, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[0].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1800, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[0].Inhibit_Time),
         OD_ENTRY(0x1800, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[0].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 1
      OD_ENTRY(0x1801, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      #if ODD_TPDO_PAR_COB_ID_1 == 0
         OD_ENTRY(0x1801, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_TPDO_Parameter[1].COB_ID),
      #else
         OD_ENTRY(0x1801, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[1].COB_ID),
      #endif
      OD_ENTRY(0x1801, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[1].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1801, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[1].Inhibit_Time),
         OD_ENTRY(0x1801, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[1].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 2
      OD_ENTRY(0x1802, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      #if ODD_TPDO_PAR_COB_ID_2 == 0
         OD_ENTRY(0x1802, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_TPDO_Parameter[2].COB_ID),
      #else
         OD_ENTRY(0x1802, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[2].COB_ID),
      #endif
      OD_ENTRY(0x1802, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[2].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1802, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[2].Inhibit_Time),
         OD_ENTRY(0x1802, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[2].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 3
      OD_ENTRY(0x1803, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      #if ODD_TPDO_PAR_COB_ID_3 == 0
         OD_ENTRY(0x1803, 0x01, ATTR_RO|ATTR_ROM|ATTR_ADD_ID, ODE_TPDO_Parameter[3].COB_ID),
      #else
         OD_ENTRY(0x1803, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[3].COB_ID),
      #endif
      OD_ENTRY(0x1803, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[3].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1803, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[3].Inhibit_Time),
         OD_ENTRY(0x1803, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[3].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 4
      OD_ENTRY(0x1804, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1804, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[4].COB_ID),
      OD_ENTRY(0x1804, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[4].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1804, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[4].Inhibit_Time),
         OD_ENTRY(0x1804, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[4].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 5
      OD_ENTRY(0x1805, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1805, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[5].COB_ID),
      OD_ENTRY(0x1805, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[5].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1805, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[5].Inhibit_Time),
         OD_ENTRY(0x1805, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[5].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 6
      OD_ENTRY(0x1806, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1806, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[6].COB_ID),
      OD_ENTRY(0x1806, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[6].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1806, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[6].Inhibit_Time),
         OD_ENTRY(0x1806, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[6].Event_Timer),
      #endif
   #endif
   #if CO_NO_TPDO > 7
      OD_ENTRY(0x1807, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Parameter_NoOfEntries),
      OD_ENTRY(0x1807, 0x01, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[7].COB_ID),
      OD_ENTRY(0x1807, 0x02, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[7].Transmission_type),
      #ifdef CO_TPDO_INH_EV_TIMER
         OD_ENTRY(0x1807, 0x03, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[7].Inhibit_Time),
         OD_ENTRY(0x1807, 0x05, ATTR_RW|ATTR_ROM, ODE_TPDO_Parameter[7].Event_Timer),
      #endif
   #endif
   #endif

   #ifdef CO_PDO_MAPPING_IN_OD
   #if CO_NO_TPDO > 0
      OD_ENTRY(0x1A00, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A00, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][0]),
      OD_ENTRY(0x1A00, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][1]),
      OD_ENTRY(0x1A00, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][2]),
      OD_ENTRY(0x1A00, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][3]),
      OD_ENTRY(0x1A00, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][4]),
      OD_ENTRY(0x1A00, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][5]),
      OD_ENTRY(0x1A00, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][6]),
      OD_ENTRY(0x1A00, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[0][7]),
   #endif
   #if CO_NO_TPDO > 1
      OD_ENTRY(0x1A01, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A01, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][0]),
      OD_ENTRY(0x1A01, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][1]),
      OD_ENTRY(0x1A01, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][2]),
      OD_ENTRY(0x1A01, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][3]),
      OD_ENTRY(0x1A01, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][4]),
      OD_ENTRY(0x1A01, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][5]),
      OD_ENTRY(0x1A01, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][6]),
      OD_ENTRY(0x1A01, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[1][7]),
   #endif
   #if CO_NO_TPDO > 2
      OD_ENTRY(0x1A02, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A02, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][0]),
      OD_ENTRY(0x1A02, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][1]),
      OD_ENTRY(0x1A02, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][2]),
      OD_ENTRY(0x1A02, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][3]),
      OD_ENTRY(0x1A02, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][4]),
      OD_ENTRY(0x1A02, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][5]),
      OD_ENTRY(0x1A02, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][6]),
      OD_ENTRY(0x1A02, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[2][7]),
   #endif
   #if CO_NO_TPDO > 3
      OD_ENTRY(0x1A03, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A03, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][0]),
      OD_ENTRY(0x1A03, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][1]),
      OD_ENTRY(0x1A03, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][2]),
      OD_ENTRY(0x1A03, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][3]),
      OD_ENTRY(0x1A03, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][4]),
      OD_ENTRY(0x1A03, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][5]),
      OD_ENTRY(0x1A03, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][6]),
      OD_ENTRY(0x1A03, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[3][7]),
   #endif
   #if CO_NO_TPDO > 4
      OD_ENTRY(0x1A04, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A04, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][0]),
      OD_ENTRY(0x1A04, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][1]),
      OD_ENTRY(0x1A04, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][2]),
      OD_ENTRY(0x1A04, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][3]),
      OD_ENTRY(0x1A04, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][4]),
      OD_ENTRY(0x1A04, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][5]),
      OD_ENTRY(0x1A04, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][6]),
      OD_ENTRY(0x1A04, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[4][7]),
   #endif
   #if CO_NO_TPDO > 5
      OD_ENTRY(0x1A05, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A05, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][0]),
      OD_ENTRY(0x1A05, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][1]),
      OD_ENTRY(0x1A05, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][2]),
      OD_ENTRY(0x1A05, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][3]),
      OD_ENTRY(0x1A05, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][4]),
      OD_ENTRY(0x1A05, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][5]),
      OD_ENTRY(0x1A05, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][6]),
      OD_ENTRY(0x1A05, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[5][7]),
   #endif
   #if CO_NO_TPDO > 6
      OD_ENTRY(0x1A06, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A06, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][0]),
      OD_ENTRY(0x1A06, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][1]),
      OD_ENTRY(0x1A06, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][2]),
      OD_ENTRY(0x1A06, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][3]),
      OD_ENTRY(0x1A06, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][4]),
      OD_ENTRY(0x1A06, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][5]),
      OD_ENTRY(0x1A06, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][6]),
      OD_ENTRY(0x1A06, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[6][7]),
   #endif
   #if CO_NO_TPDO > 7
      OD_ENTRY(0x1A07, 0x00, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping_NoOfEntries),
      OD_ENTRY(0x1A07, 0x01, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][0]),
      OD_ENTRY(0x1A07, 0x02, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][1]),
      OD_ENTRY(0x1A07, 0x03, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][2]),
      OD_ENTRY(0x1A07, 0x04, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][3]),
      OD_ENTRY(0x1A07, 0x05, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][4]),
      OD_ENTRY(0x1A07, 0x06, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][5]),
      OD_ENTRY(0x1A07, 0x07, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][6]),
      OD_ENTRY(0x1A07, 0x08, ATTR_RO|ATTR_ROM, ODE_TPDO_Mapping[7][7]),
   #endif
   #endif

   OD_ENTRY(0x1F80, 0x00, ATTR_RW|ATTR_ROM, ODE_NMT_Startup),

/***** Manufacturer specific **************************************************/
   OD_ENTRY(0x2100, 0x00, ATTR_RO, CO_ErrorStatusBits),

   OD_ENTRY(0x2101, 0x00, ATTR_RW, ODE_EEPROM.ODE_CANnodeID),
   OD_ENTRY(0x2102, 0x00, ATTR_RW, ODE_EEPROM.ODE_CANbitRate),

   #if CO_NO_SYNC > 0
      OD_ENTRY(0x2103, 0x00, ATTR_RW, CO_SYNCcounter),
      OD_ENTRY(0x2104, 0x00, ATTR_RO, CO_SYNCtime),
   #endif

   OD_ENTRY(0x2106, 0x00, ATTR_RO, ODE_EEPROM.PowerOnCounter),

   // Device Configuration

   OD_ENTRY(0x2107, 0x00, ATTR_RO|ATTR_ROM, ODE_DEVICEPARAM_NUMBER_ENTRIES),
   OD_ENTRY(0x2107, 0x01, ATTR_RW|ATTR_ROM, adc_Number),
   OD_ENTRY(0x2107, 0x02, ATTR_RW|ATTR_ROM, tris_PortX1),
   OD_ENTRY(0x2107, 0x03, ATTR_RW|ATTR_ROM, tris_PortX2),
   OD_ENTRY(0x2107, 0x04, ATTR_RW|ATTR_ROM, tris_PortX3),
   OD_ENTRY(0x2107, 0x05, ATTR_RW|ATTR_ROM, tempS_Enabled),
   OD_ENTRY(0x2107, 0x06, ATTR_RW|ATTR_ROM, default_PortX1),
   OD_ENTRY(0x2107, 0x07, ATTR_RW|ATTR_ROM, default_PortX2),
   OD_ENTRY(0x2107, 0x08, ATTR_RW|ATTR_ROM, default_PortX3),
   
//   OD_ENTRY(0x2107, 0x09, ATTR_RW, ODE_EEPROM.activate_bootloader),

   OD_ENTRY(0x2107, 0x0A, ATTR_RW|ATTR_ROM, save_PortX1),
   OD_ENTRY(0x2107, 0x0B, ATTR_RW|ATTR_ROM, save_PortX2),
   OD_ENTRY(0x2107, 0x0C, ATTR_RW|ATTR_ROM, save_PortX3),
   OD_ENTRY(0x2107, 0x0D, ATTR_RW|ATTR_ROM, type_PortX1),
   OD_ENTRY(0x2107, 0x0E, ATTR_RW|ATTR_ROM, type_PortX2),
   OD_ENTRY(0x2107, 0x0F, ATTR_RW|ATTR_ROM, type_PortX3),
   OD_ENTRY(0x2107, 0x10, ATTR_RW|ATTR_ROM, saveTPDOFlags),
   
   // 0x2108 PLC Specific
   
   OD_ENTRY(0x2108, 0x00, ATTR_RO|ATTR_ROM, ODE_PLCPARAM_NUMBER_ENTRIES),
   OD_ENTRY(0x2108, 0x01, ATTR_RW,ODE_EEPROM.plc_Enabled),
   OD_ENTRY(0x2108, 0x02, ATTR_RW|ATTR_ROM, plc_Program1),
   OD_ENTRY(0x2108, 0x03, ATTR_RW|ATTR_ROM, plc_Program2),

   // 0x2109 Modbus Specific

   OD_ENTRY(0x2109, 0x00, ATTR_RO|ATTR_ROM, ODE_MODBUSPARAM_NUMBER_ENTRIES),
   OD_ENTRY(0x2109, 0x01, ATTR_RW|ATTR_ROM, mb_Type),
   OD_ENTRY(0x2109, 0x02, ATTR_RW|ATTR_ROM, mb_NodeId),
   
   /// 0x2110 LED TouchScreen Specific
   
   OD_ENTRY(0x2110, 0x00, ATTR_RO|ATTR_ROM, ODE_LCDPARAM_NUMBER_ENTRIES),
   OD_ENTRY(0x2110, 0x01, ATTR_RW, plc_MM_BYTE(0,0xE8) ),				// WGR N
   OD_ENTRY(0x2110, 0x02, ATTR_RW, plc_MM_BYTE(0,0xE9) ),				// WGR N
   OD_ENTRY(0x2110, 0x03, ATTR_RW, plc_MM_BYTE(0,0xEA) ),				// WGR N+1
   OD_ENTRY(0x2110, 0x04, ATTR_RW, plc_MM_BYTE(0,0xEB) ),				// WGR N+1
   OD_ENTRY(0x2110, 0x05, ATTR_RW, plc_MM_BYTE(0,0xEC) ),				// WGR N+2
   OD_ENTRY(0x2110, 0x06, ATTR_RW, plc_MM_BYTE(0,0xED) ),				// WGR N+2
   OD_ENTRY(0x2110, 0x07, ATTR_RW, plc_MM_WORD(0,0xEE) ),				// GDT N
   OD_ENTRY(0x2110, 0x08, ATTR_RW, plc_MM_WORD(0,0xF0) ),				// GDT N+1
   OD_ENTRY(0x2110, 0x09, ATTR_RW, plc_MM_WORD(0,0xF2) ),				// GDT N+2
   
   /// 0x2111 Serial Parameters
   OD_ENTRY(0x2111, 0x00, ATTR_RO|ATTR_ROM, ODE_SERIALPARAM_NUMBER_ENTRIES),
   OD_ENTRY(0x2111, 0x01, ATTR_RW|ATTR_ROM, serial_baudrate),
   
   /// 0x2112 Mapping Memory
   OD_ENTRY(0x2112, 0x00, ATTR_RO|ATTR_ROM, ODE_PLC_MAPMEM_NUMBER_ENTRIES),
   OD_ENTRY(0x2112, 0x01, ATTR_RO, 			plc_mappingMem),

   /// 0x2113 RFID Reader
   OD_ENTRY(0x2113, 0x00, ATTR_RO|ATTR_ROM, ODE_RFID_NUMBER_ENTRIES),
   OD_ENTRY(0x2113, 0x01, ATTR_RW|ATTR_ROM,	rfid_readerOn),
   OD_ENTRY(0x2113, 0x02, ATTR_RW|ATTR_ROM,	rfid_IDCount),
   OD_ENTRY(0x2113, 0x03, ATTR_RW|ATTR_ROM,	rfid_IDList[0]),
   OD_ENTRY(0x2113, 0x04, ATTR_RW|ATTR_ROM,	rfid_IDList[1]),
   OD_ENTRY(0x2113, 0x05, ATTR_RW|ATTR_ROM,	rfid_IDList[2]),
   OD_ENTRY(0x2113, 0x06, ATTR_RW|ATTR_ROM,	rfid_IDList[3]),
   OD_ENTRY(0x2113, 0x07, ATTR_RW|ATTR_ROM,	rfid_IDList[4]),
   OD_ENTRY(0x2113, 0x08, ATTR_RW|ATTR_ROM,	rfid_IDList[5]),
   OD_ENTRY(0x2113, 0x09, ATTR_RW|ATTR_ROM,	rfid_IDList[6]),
   OD_ENTRY(0x2113, 0x0A, ATTR_RW|ATTR_ROM,	rfid_IDList[7]),
   OD_ENTRY(0x2113, 0x0B, ATTR_RW|ATTR_ROM,	rfid_IDList[8]),
   OD_ENTRY(0x2113, 0x0C, ATTR_RW|ATTR_ROM,	rfid_IDList[9]),
   OD_ENTRY(0x2113, 0x0D, ATTR_RW|ATTR_ROM,	rfid_IDList[10]),
   OD_ENTRY(0x2113, 0x0E, ATTR_RW|ATTR_ROM,	rfid_IDList[11]),
   OD_ENTRY(0x2113, 0x0F, ATTR_RW|ATTR_ROM,	rfid_IDList[12]),
   OD_ENTRY(0x2113, 0x10, ATTR_RW|ATTR_ROM,	rfid_IDList[13]),
   OD_ENTRY(0x2113, 0x11, ATTR_RW|ATTR_ROM,	rfid_IDList[14]),
   OD_ENTRY(0x2113, 0x12, ATTR_RW|ATTR_ROM,	rfid_IDList[15]),
   OD_ENTRY(0x2113, 0x13, ATTR_RW|ATTR_ROM,	rfid_IDList[16]),
   OD_ENTRY(0x2113, 0x14, ATTR_RW|ATTR_ROM,	rfid_IDList[17]),
   OD_ENTRY(0x2113, 0x15, ATTR_RW|ATTR_ROM,	rfid_IDList[18]),
   OD_ENTRY(0x2113, 0x16, ATTR_RW|ATTR_ROM,	rfid_IDList[19]),
   OD_ENTRY(0x2113, 0x17, ATTR_RW|ATTR_ROM,	rfid_IDList[20]),
   OD_ENTRY(0x2113, 0x18, ATTR_RW|ATTR_ROM,	rfid_IDList[21]),
   OD_ENTRY(0x2113, 0x19, ATTR_RW|ATTR_ROM,	rfid_IDList[22]),
   OD_ENTRY(0x2113, 0x1A, ATTR_RW|ATTR_ROM,	rfid_IDList[23]),
   OD_ENTRY(0x2113, 0x1B, ATTR_RW|ATTR_ROM,	rfid_IDList[24]),
   OD_ENTRY(0x2113, 0x1C, ATTR_RW|ATTR_ROM,	rfid_IDList[25]),
   OD_ENTRY(0x2113, 0x1D, ATTR_RW|ATTR_ROM,	rfid_IDList[26]),
   OD_ENTRY(0x2113, 0x1E, ATTR_RW|ATTR_ROM,	rfid_IDList[27]),
   OD_ENTRY(0x2113, 0x1F, ATTR_RW|ATTR_ROM,	rfid_IDList[28]),
   OD_ENTRY(0x2113, 0x20, ATTR_RW|ATTR_ROM,	rfid_IDList[29]),
   OD_ENTRY(0x2113, 0x21, ATTR_RW|ATTR_ROM,	rfid_IDList[30]),
   OD_ENTRY(0x2113, 0x22, ATTR_RW|ATTR_ROM,	rfid_IDList[31]),

   /// 0x2114 Clock
   OD_ENTRY(0x2114, 0x00, ATTR_RO|ATTR_ROM, ODE_CLOCK_NUMBER_ENTRIES),
   OD_ENTRY(0x2114, 0x01, ATTR_RW,	clk_dd),
   OD_ENTRY(0x2114, 0x02, ATTR_RW,	clk_MM),
   OD_ENTRY(0x2114, 0x03, ATTR_RW,	clk_yy),
   OD_ENTRY(0x2114, 0x04, ATTR_RW,	clk_hh),
   OD_ENTRY(0x2114, 0x05, ATTR_RW,	clk_mm),
   OD_ENTRY(0x2114, 0x06, ATTR_RW,	clk_ss),

   /// 0x2115 Bootloader Version
   OD_ENTRY(0x2115, 0x00, ATTR_RO|ATTR_ROM, ODE_PLC_MAPMEM_NUMBER_ENTRIES),
   OD_ENTRY(0x2115, 0x01, ATTR_RO, 			bl_Version),


/***** Device profile for Generic I/O *****************************************/
   #ifdef CO_IO_DIGITAL_INPUTS
      OD_ENTRY(0x6000, 0x00, ATTR_RO|ATTR_ROM, ODE_Read_Digital_Input_NoOfEntries),
      OD_ENTRY(0x6000, 0x01, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,0)),
      OD_ENTRY(0x6000, 0x02, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,1)),
      OD_ENTRY(0x6000, 0x03, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,2)),
      OD_ENTRY(0x6000, 0x04, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,3)),
      OD_ENTRY(0x6000, 0x05, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,4)),
      OD_ENTRY(0x6000, 0x06, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,5)),
      OD_ENTRY(0x6000, 0x07, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,6)),
      OD_ENTRY(0x6000, 0x08, ATTR_RO, plc_MM_BYTE(MAP_TPDO0,7)),
   #endif

   #ifdef CO_IO_DIGITAL_OUTPUTS
      OD_ENTRY(0x6200, 0x00, ATTR_RO|ATTR_ROM, ODE_Write_Digital_Output_NoOfEntries),
      OD_ENTRY(0x6200, 0x01, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,0)),
      OD_ENTRY(0x6200, 0x02, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,1)),
      OD_ENTRY(0x6200, 0x03, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,2)),
      OD_ENTRY(0x6200, 0x04, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,3)),
      OD_ENTRY(0x6200, 0x05, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,4)),
      OD_ENTRY(0x6200, 0x06, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,5)),
      OD_ENTRY(0x6200, 0x07, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,6)),
      OD_ENTRY(0x6200, 0x08, ATTR_RWW, plc_MM_BYTE(MAP_RPDO0,7)),
   #endif

   #ifdef CO_IO_ANALOG_INPUTS
      OD_ENTRY(0x6401, 0x00, ATTR_RO|ATTR_ROM, ODE_Read_Analog_Input_NoOfEntries),
      OD_ENTRY(0x6401, 0x01, ATTR_RO, plc_MM_WORD(MAP_TPDO1,0)),
      OD_ENTRY(0x6401, 0x02, ATTR_RO, plc_MM_WORD(MAP_TPDO1,2)),
      OD_ENTRY(0x6401, 0x03, ATTR_RO, plc_MM_WORD(MAP_TPDO1,4)),
      OD_ENTRY(0x6401, 0x04, ATTR_RO, plc_MM_WORD(MAP_TPDO1,6)),

      OD_ENTRY(0x6401, 0x05, ATTR_RO, plc_MM_WORD(MAP_TPDO2,0)),
      OD_ENTRY(0x6401, 0x06, ATTR_RO, plc_MM_WORD(MAP_TPDO2,2)),
      OD_ENTRY(0x6401, 0x07, ATTR_RO, plc_MM_WORD(MAP_TPDO2,4)),
      OD_ENTRY(0x6401, 0x08, ATTR_RO, plc_MM_WORD(MAP_TPDO2,6)),
   #endif

   #ifdef CO_IO_ANALOG_OUTPUTS
      OD_ENTRY(0x6411, 0x00, ATTR_RO|ATTR_ROM, ODE_Write_Analog_Output_NoOfEntries),
      OD_ENTRY(0x6411, 0x01, ATTR_RWW, ODE_Write_Analog_Output[0]),
      OD_ENTRY(0x6411, 0x02, ATTR_RWW, ODE_Write_Analog_Output[1]),
   #endif

};

/***** Number of Elements in Object Dictionary ********************************/
ROM unsigned int CO_OD_NoOfElements = sizeof(CO_OD) / sizeof(CO_OD[0]);
