/*******************************************************************************

   CO_OD.h - Definitions for default values in Object Dictionary

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

#ifndef _CO_OD_H
#define _CO_OD_H

//	#define USER_ISR_HIGH			// Por ahora no usamos ISR High
	#define USER_ISR_LOW			// Vamos a usar ISR High para controlar el puerto serie


/*******************************************************************************
   Setup CANopen
*******************************************************************************/
   #define CO_NO_SYNC            1u  //(0 or 1), is SYNC (producer and consumer) used or not.
   #define CO_NO_EMERGENCY       1u  //(0 or 1), is Emergency message producer used or not.
   #define CO_NO_RPDO            16u  //(0 to 512*), number of receive PDOs.
   #define CO_NO_TPDO            4u  //(0 to 512*), number of transmit PDOs.
   #define CO_NO_SDO_SERVER      1u  //(0 to 128*), number of SDO server channels.
   #define CO_NO_SDO_CLIENT      0u  //(0 to 128*), number of SDO client channels.
   #define CO_NO_CONS_HEARTBEAT  4u  //(0 to 255*), number of consumer heartbeat entries.
   #define CO_NO_USR_CAN_RX      0u  //(0 to ...), number of user CAN RX messages.
   #define CO_NO_USR_CAN_TX      0u  //(0 to ...), number of user CAN TX messages.
   #define CO_MAX_OD_ENTRY_SIZE  250u //(4 to 256), max size of variable in Object Dictionary in bytes.
   #define CO_SDO_TIMEOUT_TIME   100u //[in 100*ms] Timeout in SDO communication.
   #define CO_NO_ERROR_FIELD     8u  //(0 to 254*), size of Pre Defined Error Fields at index 0x1003.
   #define CO_PDO_PARAM_IN_OD       //if defined, PDO parameters will be in Object Dictionary.
   #define CO_PDO_MAPPING_IN_OD     //if defined, PDO mapping will be in Object Dictionary. If not defined, PDO size will be fixed to 8 bytes.
   #define CO_TPDO_INH_EV_TIMER     //if defined, Inhibit and Event timer will be used for TPDO transmission.
   #define CO_VERIFY_OD_WRITE       //if defined, SDO write to Object Dictionary will be verified.
   #define CO_OD_IS_ORDERED         //enable this macro, if entries in CO_OD are ordered (from lowest to highest index, then subindex). For longer Object Dictionaries searching is much faster. If entries are not ordered, disable macro.
   #define CO_SAVE_EEPROM           //if defined, ODE_EEPROM data will be saved.
   #define CO_SAVE_ROM              //if defined, ROM variables will be writeable from outside.

// * For some macros have written only 1 or up to 8 entries in CO_OD.c/CO_OD.h.
//   If you get error message and if you need more than that, write additional entries.


/*******************************************************************************
   Device profile for Generic I/O
*******************************************************************************/
   #define CO_IO_DIGITAL_INPUTS     //4 * 8 digital inputs
   #define CO_IO_DIGITAL_OUTPUTS    //4 * 8 digital outputs
   #define CO_IO_ANALOG_INPUTS      //8 * 16bit analog inputs
//   #define CO_IO_ANALOG_OUTPUTS     //2 * 16bit analog outputs


/*******************************************************************************
   Default values for object dictionary
*******************************************************************************/
   #define ODD_DEVICE_TYPE       0x000F0191L    /*index 0x1000, RO*/ //See standard
   #define ODD_SYNC_COB_ID       0x00000080L    /*index 0x1005*/     //if bit30=1, node produces SYNC
   #define ODD_COMM_CYCLE_PERIOD 0L             /*index 0x1006*/     //in micro seconds
   #define ODD_SYNCHR_WINDOW_LEN 0L             /*index 0x1007*/     //in micro seconds
   #define ODD_MANUF_DEVICE_NAME "MATCAN"  		/*index 0x1008, RO*/
   #define ODD_MANUF_HW_VERSION  "1.00"         /*index 0x1009, RO*/
   #define ODD_MANUF_SW_VERSION  "1.02"         /*index 0x100A, RO*/
   #define ODD_INHIBIT_TIME_EMER 50             /*index 0x1015*/     //time in 100 micro seconds
                                                /*index 0x1016*/     //see below
   #define ODD_PROD_HEARTBEAT    1000           /*index 0x1017*/     //time in ms
   #define ODD_IDENT_VENDOR_ID   0x00000000L    /*index 0x1018, RO*/ //See standard
   #define ODD_IDENT_PROD_CODE   0x00000000L
   #define ODD_IDENT_REVISION_NR 0x00000000L
   #define ODD_IDENT_SERIAL_NR   0x00000000L
   #define ODD_ERROR_BEH_COMM    0x01           /*index 0x1029*/     //If Communication error is present in Operational state: 0x00-switch to pre-operational; 0x01-do nothing; 0x02-switch to stopped.
   #define ODD_NMT_STARTUP       0x00000000L    /*index 0x1F80*/     //only bit2 implemented, if bit2=1, Node will NOT start operational

/* 0x1016 Heartbeat consumer **************************************************/
   //00NNTTTT: N=NodeID, T=time in ms
   #define ODD_CONS_HEARTBEAT_0  0x007F1388L	// Esperamos HB de 127 cada 5 segundos minimo
   #define ODD_CONS_HEARTBEAT_1  0x00000000L
   #define ODD_CONS_HEARTBEAT_2  0x00000000L
   #define ODD_CONS_HEARTBEAT_3  0x00000000L
   #define ODD_CONS_HEARTBEAT_4  0x00000000L
   #define ODD_CONS_HEARTBEAT_5  0x00000000L
   #define ODD_CONS_HEARTBEAT_6  0x00000000L
   #define ODD_CONS_HEARTBEAT_7  0x00000000L

/* 0x1400 Receive PDO parameters **********************************************/
   //COB-ID: if(bit31==1) PDO is not used; bit30=1; bits(10..0)=COB-ID;
   #define ODD_RPDO_PAR_COB_ID_0 0  //if 0, predefined value will be used (0x200+NODE-ID - read-only)
   #define ODD_RPDO_PAR_T_TYPE_0 255
   #define ODD_RPDO_PAR_COB_ID_1 0  //if 0, predefined value will be used (0x300+NODE-ID - read-only)
   #define ODD_RPDO_PAR_T_TYPE_1 255
   #define ODD_RPDO_PAR_COB_ID_2 0  //if 0, predefined value will be used (0x400+NODE-ID - read-only)
   #define ODD_RPDO_PAR_T_TYPE_2 255
   #define ODD_RPDO_PAR_COB_ID_3 0  //if 0, predefined value will be used (0x500+NODE-ID - read-only)
   #define ODD_RPDO_PAR_T_TYPE_3 255
//   #define ODD_RPDO_PAR_COB_ID_4 0xC0000000L
   #define ODD_RPDO_PAR_COB_ID_4 0x00000181L
   #define ODD_RPDO_PAR_T_TYPE_4 255
   #define ODD_RPDO_PAR_COB_ID_5 0x00000281L
   #define ODD_RPDO_PAR_T_TYPE_5 255
   #define ODD_RPDO_PAR_COB_ID_6 0x00000381L
   #define ODD_RPDO_PAR_T_TYPE_6 255
   #define ODD_RPDO_PAR_COB_ID_7 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_7 255
   #define ODD_RPDO_PAR_COB_ID_8 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_8 255
   #define ODD_RPDO_PAR_COB_ID_9 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_9 255
   #define ODD_RPDO_PAR_COB_ID_10 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_10 255
   #define ODD_RPDO_PAR_COB_ID_11 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_11 255
   #define ODD_RPDO_PAR_COB_ID_12 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_12 255
   #define ODD_RPDO_PAR_COB_ID_13 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_13 255
   #define ODD_RPDO_PAR_COB_ID_14 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_14 255
   #define ODD_RPDO_PAR_COB_ID_15 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_15 255
   #define ODD_RPDO_PAR_COB_ID_16 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_16 255
   #define ODD_RPDO_PAR_COB_ID_17 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_17 255
   #define ODD_RPDO_PAR_COB_ID_18 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_18 255
   #define ODD_RPDO_PAR_COB_ID_19 0x00000481L
   #define ODD_RPDO_PAR_T_TYPE_19 255

/* 0x1600 Receive PDO mapping *************************************************/
   //0xIIIISSDD IIII = index from OD, SS = subindex, DD = data length in bits
   //DD must be byte aligned, max value 0x40 (8 bytes)
   #define ODD_RPDO_MAP_0_1      0x62000108L
   #define ODD_RPDO_MAP_0_2      0x62000208L
   #define ODD_RPDO_MAP_0_3      0x62000308L
   #define ODD_RPDO_MAP_0_4      0x62000408L
   #define ODD_RPDO_MAP_0_5      0x62000508L
   #define ODD_RPDO_MAP_0_6      0x62000608L
   #define ODD_RPDO_MAP_0_7      0x62000708L
   #define ODD_RPDO_MAP_0_8      0x62000808L

   #define ODD_RPDO_MAP_1_1      0x64110108L
   #define ODD_RPDO_MAP_1_2      0x64110208L
   #define ODD_RPDO_MAP_1_3      0x64110308L
   #define ODD_RPDO_MAP_1_4      0x64110408L
   #define ODD_RPDO_MAP_1_5      0x64110508L
   #define ODD_RPDO_MAP_1_6      0x64110608L
   #define ODD_RPDO_MAP_1_7      0x64110708L
   #define ODD_RPDO_MAP_1_8      0x64110808L

   #define ODD_RPDO_MAP_2_1      0x00000040L
   #define ODD_RPDO_MAP_2_2      0x00000000L
   #define ODD_RPDO_MAP_2_3      0x00000000L
   #define ODD_RPDO_MAP_2_4      0x00000000L
   #define ODD_RPDO_MAP_2_5      0x00000000L
   #define ODD_RPDO_MAP_2_6      0x00000000L
   #define ODD_RPDO_MAP_2_7      0x00000000L
   #define ODD_RPDO_MAP_2_8      0x00000000L

   #define ODD_RPDO_MAP_3_1      0x00000040L
   #define ODD_RPDO_MAP_3_2      0x00000000L
   #define ODD_RPDO_MAP_3_3      0x00000000L
   #define ODD_RPDO_MAP_3_4      0x00000000L
   #define ODD_RPDO_MAP_3_5      0x00000000L
   #define ODD_RPDO_MAP_3_6      0x00000000L
   #define ODD_RPDO_MAP_3_7      0x00000000L
   #define ODD_RPDO_MAP_3_8      0x00000000L

   #define ODD_RPDO_MAP_4_1      0xFFFF0108L
   #define ODD_RPDO_MAP_4_2      0xFFFF0108L
   #define ODD_RPDO_MAP_4_3      0xFFFF0108L
   #define ODD_RPDO_MAP_4_4      0xFFFF0108L
   #define ODD_RPDO_MAP_4_5      0xFFFF0108L
   #define ODD_RPDO_MAP_4_6      0xFFFF0108L
   #define ODD_RPDO_MAP_4_7      0xFFFF0108L
   #define ODD_RPDO_MAP_4_8      0xFFFF0108L

   #define ODD_RPDO_MAP_5_1      0xFFFF0108L
   #define ODD_RPDO_MAP_5_2      0xFFFF0108L
   #define ODD_RPDO_MAP_5_3      0xFFFF0108L
   #define ODD_RPDO_MAP_5_4      0xFFFF0108L
   #define ODD_RPDO_MAP_5_5      0xFFFF0108L
   #define ODD_RPDO_MAP_5_6      0xFFFF0108L
   #define ODD_RPDO_MAP_5_7      0xFFFF0108L
   #define ODD_RPDO_MAP_5_8      0xFFFF0108L

   #define ODD_RPDO_MAP_6_1      0xFFFF0108L
   #define ODD_RPDO_MAP_6_2      0xFFFF0108L
   #define ODD_RPDO_MAP_6_3      0xFFFF0108L
   #define ODD_RPDO_MAP_6_4      0xFFFF0108L
   #define ODD_RPDO_MAP_6_5      0xFFFF0108L
   #define ODD_RPDO_MAP_6_6      0xFFFF0108L
   #define ODD_RPDO_MAP_6_7      0xFFFF0108L
   #define ODD_RPDO_MAP_6_8      0xFFFF0108L

   #define ODD_RPDO_MAP_7_1      0xFFFF0108L
   #define ODD_RPDO_MAP_7_2      0xFFFF0108L
   #define ODD_RPDO_MAP_7_3      0xFFFF0108L
   #define ODD_RPDO_MAP_7_4      0xFFFF0108L
   #define ODD_RPDO_MAP_7_5      0xFFFF0108L
   #define ODD_RPDO_MAP_7_6      0xFFFF0108L
   #define ODD_RPDO_MAP_7_7      0xFFFF0108L
   #define ODD_RPDO_MAP_7_8      0xFFFF0108L

   #define ODD_RPDO_MAP_8_1      0xFFFF0108L
   #define ODD_RPDO_MAP_8_2      0xFFFF0108L
   #define ODD_RPDO_MAP_8_3      0xFFFF0108L
   #define ODD_RPDO_MAP_8_4      0xFFFF0108L
   #define ODD_RPDO_MAP_8_5      0xFFFF0108L
   #define ODD_RPDO_MAP_8_6      0xFFFF0108L
   #define ODD_RPDO_MAP_8_7      0xFFFF0108L
   #define ODD_RPDO_MAP_8_8      0xFFFF0108L

   #define ODD_RPDO_MAP_9_1      0xFFFF0108L
   #define ODD_RPDO_MAP_9_2      0xFFFF0108L
   #define ODD_RPDO_MAP_9_3      0xFFFF0108L
   #define ODD_RPDO_MAP_9_4      0xFFFF0108L
   #define ODD_RPDO_MAP_9_5      0xFFFF0108L
   #define ODD_RPDO_MAP_9_6      0xFFFF0108L
   #define ODD_RPDO_MAP_9_7      0xFFFF0108L
   #define ODD_RPDO_MAP_9_8      0xFFFF0108L

   #define ODD_RPDO_MAP_10_1      0xFFFF0108L
   #define ODD_RPDO_MAP_10_2      0xFFFF0108L
   #define ODD_RPDO_MAP_10_3      0xFFFF0108L
   #define ODD_RPDO_MAP_10_4      0xFFFF0108L
   #define ODD_RPDO_MAP_10_5      0xFFFF0108L
   #define ODD_RPDO_MAP_10_6      0xFFFF0108L
   #define ODD_RPDO_MAP_10_7      0xFFFF0108L
   #define ODD_RPDO_MAP_10_8      0xFFFF0108L

   #define ODD_RPDO_MAP_11_1      0xFFFF0108L
   #define ODD_RPDO_MAP_11_2      0xFFFF0108L
   #define ODD_RPDO_MAP_11_3      0xFFFF0108L
   #define ODD_RPDO_MAP_11_4      0xFFFF0108L
   #define ODD_RPDO_MAP_11_5      0xFFFF0108L
   #define ODD_RPDO_MAP_11_6      0xFFFF0108L
   #define ODD_RPDO_MAP_11_7      0xFFFF0108L
   #define ODD_RPDO_MAP_11_8      0xFFFF0108L

   #define ODD_RPDO_MAP_12_1      0xFFFF0108L
   #define ODD_RPDO_MAP_12_2      0xFFFF0108L
   #define ODD_RPDO_MAP_12_3      0xFFFF0108L
   #define ODD_RPDO_MAP_12_4      0xFFFF0108L
   #define ODD_RPDO_MAP_12_5      0xFFFF0108L
   #define ODD_RPDO_MAP_12_6      0xFFFF0108L
   #define ODD_RPDO_MAP_12_7      0xFFFF0108L
   #define ODD_RPDO_MAP_12_8      0xFFFF0108L

   #define ODD_RPDO_MAP_13_1      0xFFFF0108L
   #define ODD_RPDO_MAP_13_2      0xFFFF0108L
   #define ODD_RPDO_MAP_13_3      0xFFFF0108L
   #define ODD_RPDO_MAP_13_4      0xFFFF0108L
   #define ODD_RPDO_MAP_13_5      0xFFFF0108L
   #define ODD_RPDO_MAP_13_6      0xFFFF0108L
   #define ODD_RPDO_MAP_13_7      0xFFFF0108L
   #define ODD_RPDO_MAP_13_8      0xFFFF0108L

   #define ODD_RPDO_MAP_14_1      0xFFFF0108L
   #define ODD_RPDO_MAP_14_2      0xFFFF0108L
   #define ODD_RPDO_MAP_14_3      0xFFFF0108L
   #define ODD_RPDO_MAP_14_4      0xFFFF0108L
   #define ODD_RPDO_MAP_14_5      0xFFFF0108L
   #define ODD_RPDO_MAP_14_6      0xFFFF0108L
   #define ODD_RPDO_MAP_14_7      0xFFFF0108L
   #define ODD_RPDO_MAP_14_8      0xFFFF0108L

   #define ODD_RPDO_MAP_15_1      0xFFFF0108L
   #define ODD_RPDO_MAP_15_2      0xFFFF0108L
   #define ODD_RPDO_MAP_15_3      0xFFFF0108L
   #define ODD_RPDO_MAP_15_4      0xFFFF0108L
   #define ODD_RPDO_MAP_15_5      0xFFFF0108L
   #define ODD_RPDO_MAP_15_6      0xFFFF0108L
   #define ODD_RPDO_MAP_15_7      0xFFFF0108L
   #define ODD_RPDO_MAP_15_8      0xFFFF0108L

   #define ODD_RPDO_MAP_16_1      0xFFFF0108L
   #define ODD_RPDO_MAP_16_2      0xFFFF0108L
   #define ODD_RPDO_MAP_16_3      0xFFFF0108L
   #define ODD_RPDO_MAP_16_4      0xFFFF0108L
   #define ODD_RPDO_MAP_16_5      0xFFFF0108L
   #define ODD_RPDO_MAP_16_6      0xFFFF0108L
   #define ODD_RPDO_MAP_16_7      0xFFFF0108L
   #define ODD_RPDO_MAP_16_8      0xFFFF0108L

   #define ODD_RPDO_MAP_17_1      0xFFFF0108L
   #define ODD_RPDO_MAP_17_2      0xFFFF0108L
   #define ODD_RPDO_MAP_17_3      0xFFFF0108L
   #define ODD_RPDO_MAP_17_4      0xFFFF0108L
   #define ODD_RPDO_MAP_17_5      0xFFFF0108L
   #define ODD_RPDO_MAP_17_6      0xFFFF0108L
   #define ODD_RPDO_MAP_17_7      0xFFFF0108L
   #define ODD_RPDO_MAP_17_8      0xFFFF0108L

   #define ODD_RPDO_MAP_18_1      0xFFFF0108L
   #define ODD_RPDO_MAP_18_2      0xFFFF0108L
   #define ODD_RPDO_MAP_18_3      0xFFFF0108L
   #define ODD_RPDO_MAP_18_4      0xFFFF0108L
   #define ODD_RPDO_MAP_18_5      0xFFFF0108L
   #define ODD_RPDO_MAP_18_6      0xFFFF0108L
   #define ODD_RPDO_MAP_18_7      0xFFFF0108L
   #define ODD_RPDO_MAP_18_8      0xFFFF0108L

   #define ODD_RPDO_MAP_19_1      0xFFFF0108L
   #define ODD_RPDO_MAP_19_2      0xFFFF0108L
   #define ODD_RPDO_MAP_19_3      0xFFFF0108L
   #define ODD_RPDO_MAP_19_4      0xFFFF0108L
   #define ODD_RPDO_MAP_19_5      0xFFFF0108L
   #define ODD_RPDO_MAP_19_6      0xFFFF0108L
   #define ODD_RPDO_MAP_19_7      0xFFFF0108L
   #define ODD_RPDO_MAP_19_8      0xFFFF0108L

/* 0x1800 Transmit PDO parameters *********************************************/
   //COB-ID: if(bit31==1) PDO is not used; bit30=1; bits(10..0)=COB-ID;
   //T_TYPE: 1-240...transmission after every (T_TYPE)-th SYNC object;
   //        254...manufacturer specific
   //        255...Device Profile specific, default transmission is Change of State
   //I_TIME: 0...65535 Inhibit time in 100�s is minimum time between PDO transmission
   //E_TIME: 0...65535 Event timer in ms - PDO is periodically transmitted (0 == disabled)

   #define ODD_TPDO_PAR_COB_ID_0 0  //if 0, predefined value will be used (0x180+NODE-ID - read-only)
   #define ODD_TPDO_PAR_T_TYPE_0 255
   #define ODD_TPDO_PAR_I_TIME_0 1000	// Inhibit en 2000micros = 100ms
   #define ODD_TPDO_PAR_E_TIME_0 5000	// Updates cada 5 segundos

   #define ODD_TPDO_PAR_COB_ID_1 0  //if 0, predefined value will be used (0x280+NODE-ID - read-only)
   #define ODD_TPDO_PAR_T_TYPE_1 255
   #define ODD_TPDO_PAR_I_TIME_1 2000   // Inhibit de 200 milisegundos
   #define ODD_TPDO_PAR_E_TIME_1 5100	// Updates cada 5.1 segundos, para que no simultaneidad con tpdo0

   #define ODD_TPDO_PAR_COB_ID_2 0  //if 0, predefined value will be used (0x380+NODE-ID - read-only)
   #define ODD_TPDO_PAR_T_TYPE_2 255
   #define ODD_TPDO_PAR_I_TIME_2 5000	// Valores no muy importantes - temp
   #define ODD_TPDO_PAR_E_TIME_2 5200
   
   #define ODD_TPDO_PAR_COB_ID_3 0  //if 0, predefined value will be used (0x480+NODE-ID - read-only)
   #define ODD_TPDO_PAR_T_TYPE_3 255
   #define ODD_TPDO_PAR_I_TIME_3 1000
   #define ODD_TPDO_PAR_E_TIME_3 0
   #define ODD_TPDO_PAR_COB_ID_4 0xC0000000L
   #define ODD_TPDO_PAR_T_TYPE_4 254
   #define ODD_TPDO_PAR_I_TIME_4 1000
   #define ODD_TPDO_PAR_E_TIME_4 0
   #define ODD_TPDO_PAR_COB_ID_5 0xC0000000L
   #define ODD_TPDO_PAR_T_TYPE_5 254
   #define ODD_TPDO_PAR_I_TIME_5 1000
   #define ODD_TPDO_PAR_E_TIME_5 0
   #define ODD_TPDO_PAR_COB_ID_6 0xC0000000L
   #define ODD_TPDO_PAR_T_TYPE_6 254
   #define ODD_TPDO_PAR_I_TIME_6 1000
   #define ODD_TPDO_PAR_E_TIME_6 0
   #define ODD_TPDO_PAR_COB_ID_7 0xC0000000L
   #define ODD_TPDO_PAR_T_TYPE_7 254
   #define ODD_TPDO_PAR_I_TIME_7 1000
   #define ODD_TPDO_PAR_E_TIME_7 0

/* 0x1A00 Transmit PDO mapping ************************************************/
   //0xIIIISSDD IIII = index from OD, SS = subindex, DD = data length in bits
   //DD must be byte aligned, max value 0x40 (8 bytes)
   #define ODD_TPDO_MAP_0_1      0x60000108L
   #define ODD_TPDO_MAP_0_2      0x60000208L
   #define ODD_TPDO_MAP_0_3      0x60000308L
   #define ODD_TPDO_MAP_0_4      0x60000408L
   #define ODD_TPDO_MAP_0_5      0x60000508L
   #define ODD_TPDO_MAP_0_6      0x60000608L
   #define ODD_TPDO_MAP_0_7      0x60000708L
   #define ODD_TPDO_MAP_0_8      0x60000808L

   #define ODD_TPDO_MAP_1_1      0x64010110L
   #define ODD_TPDO_MAP_1_2      0x64010210L
   #define ODD_TPDO_MAP_1_3      0x64010310L
   #define ODD_TPDO_MAP_1_4      0x64010410L
   #define ODD_TPDO_MAP_1_5      0x00000000L
   #define ODD_TPDO_MAP_1_6      0x00000000L
   #define ODD_TPDO_MAP_1_7      0x00000000L
   #define ODD_TPDO_MAP_1_8      0x00000000L

   #define ODD_TPDO_MAP_2_1      0x64010510L
   #define ODD_TPDO_MAP_2_2      0x64010610L
   #define ODD_TPDO_MAP_2_3      0x64010710L
   #define ODD_TPDO_MAP_2_4      0x64010810L
   #define ODD_TPDO_MAP_2_5      0x00000000L
   #define ODD_TPDO_MAP_2_6      0x00000000L
   #define ODD_TPDO_MAP_2_7      0x00000000L
   #define ODD_TPDO_MAP_2_8      0x00000000L

   #define ODD_TPDO_MAP_3_1      0x00000040L
   #define ODD_TPDO_MAP_3_2      0x00000000L
   #define ODD_TPDO_MAP_3_3      0x00000000L
   #define ODD_TPDO_MAP_3_4      0x00000000L
   #define ODD_TPDO_MAP_3_5      0x00000000L
   #define ODD_TPDO_MAP_3_6      0x00000000L
   #define ODD_TPDO_MAP_3_7      0x00000000L
   #define ODD_TPDO_MAP_3_8      0x00000000L

   #define ODD_TPDO_MAP_4_1      0x00000040L
   #define ODD_TPDO_MAP_4_2      0x00000000L
   #define ODD_TPDO_MAP_4_3      0x00000000L
   #define ODD_TPDO_MAP_4_4      0x00000000L
   #define ODD_TPDO_MAP_4_5      0x00000000L
   #define ODD_TPDO_MAP_4_6      0x00000000L
   #define ODD_TPDO_MAP_4_7      0x00000000L
   #define ODD_TPDO_MAP_4_8      0x00000000L

   #define ODD_TPDO_MAP_5_1      0x00000040L
   #define ODD_TPDO_MAP_5_2      0x00000000L
   #define ODD_TPDO_MAP_5_3      0x00000000L
   #define ODD_TPDO_MAP_5_4      0x00000000L
   #define ODD_TPDO_MAP_5_5      0x00000000L
   #define ODD_TPDO_MAP_5_6      0x00000000L
   #define ODD_TPDO_MAP_5_7      0x00000000L
   #define ODD_TPDO_MAP_5_8      0x00000000L

   #define ODD_TPDO_MAP_6_1      0x00000040L
   #define ODD_TPDO_MAP_6_2      0x00000000L
   #define ODD_TPDO_MAP_6_3      0x00000000L
   #define ODD_TPDO_MAP_6_4      0x00000000L
   #define ODD_TPDO_MAP_6_5      0x00000000L
   #define ODD_TPDO_MAP_6_6      0x00000000L
   #define ODD_TPDO_MAP_6_7      0x00000000L
   #define ODD_TPDO_MAP_6_8      0x00000000L

   #define ODD_TPDO_MAP_7_1      0x00000040L
   #define ODD_TPDO_MAP_7_2      0x00000000L
   #define ODD_TPDO_MAP_7_3      0x00000000L
   #define ODD_TPDO_MAP_7_4      0x00000000L
   #define ODD_TPDO_MAP_7_5      0x00000000L
   #define ODD_TPDO_MAP_7_6      0x00000000L
   #define ODD_TPDO_MAP_7_7      0x00000000L
   #define ODD_TPDO_MAP_7_8      0x00000000L


/*******************************************************************************
   Default values for user Object Dictionary Entries
*******************************************************************************/
/*0x2101*/
   #define ODD_CANnodeID    MAT_NODE_ID //(1 to 127), default node ID
/*0x2102*/
   #define ODD_CANbitRate   MAT_CAN_BAUDRATE    //(0 to 7), default CAN bit rate
                                 // 0 = 10 kbps    1 = 20 kbps
                                 // 2 = 50 kbps    3 = 125 kbps
                                 // 4 = 250 kbps   5 = 500 kbps
                                 // 6 = 800 kbps   7 = 1000 kbps


/*******************************************************************************
   CANopen basic Data Types
*******************************************************************************/
   #define UNSIGNED8  unsigned char
   #define UNSIGNED16 unsigned int
   #define UNSIGNED32 unsigned long
   #define INTEGER8   char
   #define INTEGER16  int
   #define INTEGER32  long


/*******************************************************************************
   CANopen Variables from Object Dictionary
*******************************************************************************/
/*0x1001*/ extern       UNSIGNED8      ODE_Error_Register;
/*0x1002*/ extern       UNSIGNED32     ODE_Manufacturer_Status_Register;

           #if CO_NO_ERROR_FIELD > 0
/*0x1003*/ extern       UNSIGNED8      ODE_Pre_Defined_Error_Field_NoOfErrors;
           extern       UNSIGNED32     ODE_Pre_Defined_Error_Field[];
           #endif

           #if CO_NO_SYNC > 0
/*0x1005*/ extern ROM   UNSIGNED32     ODE_SYNC_COB_ID;
/*0x1006*/ extern ROM   UNSIGNED32     ODE_Communication_Cycle_Period;
/*0x1007*/ extern ROM   UNSIGNED32     ODE_Synchronous_Window_Length;
           #endif

           #if CO_NO_EMERGENCY > 0
/*0x1014*/ extern ROM   UNSIGNED32     ODE_Emergency_COB_ID;
/*0x1015*/ extern ROM   UNSIGNED16     ODE_Inhibit_Time_Emergency;
           #endif

           #if CO_NO_CONS_HEARTBEAT > 0
/*0x1016*/ extern ROM   UNSIGNED32     ODE_Consumer_Heartbeat_Time[];
           #endif

/*0x1017*/ extern ROM   UNSIGNED16     ODE_Producer_Heartbeat_Time;

           typedef struct{
              UNSIGNED8    NoOfEntries;
              UNSIGNED8    Communication_Error;
           }               ODEs_Error_Behavior;
/*0x1029*/ extern ROM   ODEs_Error_Behavior  ODE_Error_Behavior;

           #if CO_NO_SDO_SERVER > 0 || CO_NO_SDO_CLIENT > 0
           typedef struct{
              UNSIGNED32   COB_ID_Client_to_Server;
              UNSIGNED32   COB_ID_Server_to_Client;
              UNSIGNED8    NODE_ID_of_SDO_Client_or_Server;
           }               CO_sSDO_Param;
           #endif

           #if CO_NO_SDO_SERVER > 0
/*0x1200*/ extern ROM   CO_sSDO_Param  ODE_Server_SDO_Parameter[];
           #endif

           #if CO_NO_SDO_CLIENT > 0
/*0x1280*/ extern       CO_sSDO_Param  ODE_Client_SDO_Parameter[];
           #endif

           #if CO_NO_RPDO > 0
           typedef struct{
              UNSIGNED32   COB_ID;
              UNSIGNED8    Transmission_type;
           }               CO_sRPDO_param;
/*0x1400*/ extern ROM   CO_sRPDO_param ODE_RPDO_Parameter[];
           #ifdef CO_PDO_MAPPING_IN_OD
/*0x1600*/ extern ROM   UNSIGNED32     ODE_RPDO_Mapping[][8];
           #endif
           #endif

           #if CO_NO_TPDO > 0
           typedef struct{
              UNSIGNED32   COB_ID;
              UNSIGNED8    Transmission_type;
              UNSIGNED16   Inhibit_Time;
              //UNSIGNED8    Compatibility_Entry; - not needed
              UNSIGNED16   Event_Timer;
           }               CO_sTPDO_param;
/*0x1800*/ extern ROM   CO_sTPDO_param ODE_TPDO_Parameter[];
           #ifdef CO_PDO_MAPPING_IN_OD
/*0x1A00*/ extern ROM   UNSIGNED32     ODE_TPDO_Mapping[][8];
           #endif
           #endif

/*0x1F80*/ extern ROM   UNSIGNED32     ODE_NMT_Startup;
















/***** Manufacturer specific EEPROM DATA **************************************/
           typedef struct{
	            UNSIGNED8	   	plc_Enabled;

// Guardamos los ultimos valores de las salidas analogicas
/*not mapped*/	UNSIGNED8		last_PWMX2_1;
/*not mapped*/	UNSIGNED8		last_PWMX2_2;
/*not mapped*/	UNSIGNED8		last_PWMX2_3;
/*not mapped*/	UNSIGNED8		last_PWMX2_4;
/*not mapped*/	UNSIGNED8		last_PWMX2_5;
/*not mapped*/	UNSIGNED8		last_PWMX2_6;

/*not mapped*/	UNSIGNED8		last_PWMX1_1;
/*not mapped*/	UNSIGNED8		last_PWMX1_2;
/*not mapped*/	UNSIGNED8		last_PWMX1_3;
/*not mapped*/	UNSIGNED8		last_PWMX1_4;
/*not mapped*/	UNSIGNED8		last_PWMX1_5;
/*not mapped*/	UNSIGNED8		last_PWMX1_6;
/*not mapped*/	UNSIGNED8		last_PWMX1_7;

// Guardamos el ultimo estado de los puertos
/*not mapped*/	UNSIGNED16	   	last_PortX3;
/*not mapped*/	UNSIGNED8	   	last_PortX2;
/*not mapped*/	UNSIGNED8	   	last_PortX1;

/*0x2101*/		UNSIGNED8	   	ODE_CANnodeID;
/*0x2102*/ 		UNSIGNED8      	ODE_CANbitRate;
/*0x2106*/     	UNSIGNED32     	PowerOnCounter;   	// Incremented every time, when chip is powered.

/*not mapped*/  UNSIGNED32		last_TPDO0Low;
/*not mapped*/  UNSIGNED32		last_TPDO0High;
/*not mapped*/  UNSIGNED32		last_TPDO1Low;
/*not mapped*/  UNSIGNED32		last_TPDO1High;
/*not mapped*/  UNSIGNED32		last_TPDO2Low;
/*not mapped*/  UNSIGNED32		last_TPDO2High;
/*not mapped*/  UNSIGNED32		last_TPDO3Low;
/*not mapped*/  UNSIGNED32		last_TPDO3High;
           } sODE_EEPROM;
           extern sODE_EEPROM ODE_EEPROM;





/***** Manufacturer specific variables ****************************************/
///*0x2100  							CO_ErrorStatusBits 
///*0x2101 	extern ROM   UNSIGNED8      ODE_CANnodeID;
///*0x2102 	extern ROM   UNSIGNED8      ODE_CANbitRate;
///*0x2103								CO_SYNCcounter
///*0x2104								CO_SYNCTime
///*0x2106								PowerOn Counter


/*0x2107 Device Configuration */
/* 	 sub 1 */	extern ROM UNSIGNED8	  	adc_Number;				// Number of Analog Inputs

/* 	 sub 2 */	extern ROM UNSIGNED8	  	tris_PortX1;			// port X1 - 1 input 0 output
/* 	 sub 3 */	extern ROM UNSIGNED8	  	tris_PortX2;			// port X2 - 1 input 0 output
/* 	 sub 4 */	extern ROM UNSIGNED16	tris_PortX3;			// port X3 - 1 input 0 output
/* 	 sub 5 */   extern ROM UNSIGNED8 	tempS_Enabled;			// LM35 Temp Sensor enabled

/* 	 sub 6 */	extern ROM UNSIGNED8	  	default_PortX1;			// default value port X1
/* 	 sub 7 */	extern ROM UNSIGNED8	  	default_PortX2;			// default value port X2
/* 	 sub 8 */	extern ROM UNSIGNED16	default_PortX3;			// default value port X3

/*   sub 9   */

/*	 sub 10 */	extern ROM UNSIGNED8			save_PortX1;			// save value port X1 
/*	 sub 11 */	extern ROM UNSIGNED8	  		save_PortX2;			// save value port X2 
/* 	 sub 12 */	extern ROM UNSIGNED8	save_PortX3;			// save value port X3 

/* 	 sub 13 */	extern ROM UNSIGNED8	  	type_PortX1;			// port X1 - 1 analog 0 digital
/* 	 sub 14 */	extern ROM UNSIGNED8	  	type_PortX2;			// port X2 - 1 analog 0 digital
/* 	 sub 15 */	extern ROM UNSIGNED16	type_PortX3;			// port X3 - 1 analog 0 digital
/*	 sub 16 */  extern ROM UNSIGNED8		saveTPDOFlags;			// Save TPDO to EPROM flags (bit0: TPDO0, bit1: TPDO2, ...)


/*0x2108 PLC Parameters */     	
///* sub 1 */	extern ROM UNSIGNED8	  		plc_Enabled;				// plc Process Enabled
/* 	 sub 2 */	extern ROM UNSIGNED8    plc_Program1[248];			// 248 bytes de programa
/* 	 sub 3 */	extern ROM UNSIGNED8    plc_Program2[248];			// 248 bytes de programa

/*0x2109 Modbus Parameters */     	
/* 	 sub 1 */	extern ROM UNSIGNED8	  	mb_Type;					// 0 Disabled 1 Master 2 Slave
/* 	 sub 2 */	extern ROM UNSIGNED8    mb_NodeId;				// Modbus node id

/// 0x2110 LED TouchScreen Specific
//   sub 1 	   	plc_MM_BYTE(0,0xE8)				// WGR N
//   sub 2 	   	plc_MM_BYTE(0,0xE9)				// WGR N
//   sub 3 	   	plc_MM_BYTE(0,0xEA)				// WGR N+1
//   sub 4 	   	plc_MM_BYTE(0,0xEB)				// WGR N+1
//   sub 5 	   	plc_MM_BYTE(0,0xEC)				// WGR N+2
//   sub 6 	   	plc_MM_BYTE(0,0xED)				// WGR N+2
//   sub 7 	   	plc_MM_WORD(0,0xEE)				// GDT N
//   sub 8 	   	plc_MM_WORD(0,0xF0)				// GDT N+1
//   sub 9 	   	plc_MM_WORD(0,0xF2)				// GDT N+2

/*0x2111 Serial Parameters */
/*   sub 1 */	extern ROM UNSIGNED8	serial_baudrate;				//

/*0x2112 PLC Mapping Memory */
//   sub1  								plc_MappingMem

/*0x2113 RFID Reader Parameters */
/*   sub 1 */	extern ROM UNSIGNED8		rfid_readerOn;				// Lector apagado
/*   sub 2 */	extern ROM UNSIGNED8		rfid_IDCount;				// Numero de IDs
/*   sub 3+ */	extern ROM UNSIGNED32		rfid_IDList[32];			// Lista de IDs

			extern UNSIGNED16			temp_TimerCount;

			extern UNSIGNED16			clk_yy;			// year
			extern UNSIGNED8			clk_MM;			// month
			extern UNSIGNED8			clk_dd;			// day
			extern UNSIGNED8			clk_hh;			// hour
			extern UNSIGNED8			clk_mm;			// minutes
			extern UNSIGNED8			clk_ss;			// seconds
			extern UNSIGNED16			clk_mlsec;		// Milliseconds
			extern UNSIGNED8			clk_Updated;	// Clock Updated

			extern UNSIGNED16			bl_Version;		// blVersion








#endif
