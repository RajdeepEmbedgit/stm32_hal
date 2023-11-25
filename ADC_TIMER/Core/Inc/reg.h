/*
 * reg.h
 *
 *  Created on: Jun 14, 2022
 *      Author: Shyamik Das
 */

#ifndef REG_H_
#define REG_H_

#include "stdint.h"

extern uint16_t FLAG;


/*
 * -------------------FUNCTION PROTOTYPE--------------------------------------------
 *
 * */
void signal_process(int raw_v, int raw_ka);
void set_cell_state(int state);
void reset_all_zone_flags(void);
float ewma (float res);



/*----------------------DEFINES-----------------------------------------------------*/

#define TIM_DELAY 120            //

/*
  *  --------------------CELL_STATE_&_CONTROLLER_MODE(CSCM)--------------------
	CONTROLLER_MODES
	 15   	 14    	 13   	 12	     11	     10	         9                8
	RSVD	RSVD	RSVD	RSVD	RSVD	RSVD	    MANUAL	      AUTOMATIC       MSB


	CELL_STATE
	7   	6   	5	   4	    3   	  2     	1	            0
	RSVD	RSVD	RSVD	RSVD	RSVD	Baking	Out of Circuit	In Operation   LSB
*/

#define CSCM_RESET 										(CSCM = 0)
#define CSCM_IN_OPERATION 								(1U << 0)
#define CSCM_OUT_OF_CIRCUIT								(1U << 1)
#define CSCM_BAKING										(1U << 2)
#define CSCM_AUTOMATIC									(1U << 8)
#define CSCM_MANUAL										(1U << 9)
#define CSCM_RESET_CELL_STATE							(CSCM &=~ 0xFF00)
#define CSCM_RESET_CONTROLLER_MODE						(CSCM &=~ 0x00FF)
//state commands
#define CSCM_IS_IN_OPERATION							(CSCM & CSCM_IN_OPERATION)
#define CSCM_IS_OUT_OF_CIRCUIT							(CSCM & CSCM_OUT_OF_CIRCUIT)
#define CSCM_IS_BAKING									(CSCM & CSCM_BAKING)
#define CSCM_IS_MANUAL                                  (CSCM & CSCM_MANUAL)
#define CSCM_IS_AUTOMATIC								(CSCM & CSCM_AUTOMATIC)
#define CSCM_RESET_CELL_STATE_PARAM						(0xFF00)
#define CSCM_RESET_CONTROLLER_MODE_PARAM				(0x00FF)

//enable commands
//#define CSCM_IN_OPERATION_EN							{CSCM_RESET_CELL_STATE; CSCM |= CSCM_IN_OPERATION;}
#define CSCM_IN_OPERATION_EN							(CSCM = ((CSCM & CSCM_RESET_CELL_STATE_PARAM) | CSCM_IN_OPERATION))
#define CSCM_OUT_OF_CIRCUIT_EN							(CSCM = ((CSCM & CSCM_RESET_CELL_STATE_PARAM) | CSCM_OUT_OF_CIRCUIT))
#define CSCM_BAKING_EN									(CSCM = ((CSCM & CSCM_RESET_CELL_STATE_PARAM) | CSCM_BAKING))
#define CSCM_MANUAL_EN									(CSCM = ((CSCM & CSCM_RESET_CONTROLLER_MODE_PARAM) | CSCM_MANUAL))
#define CSCM_AUTOMATIC_EN								(CSCM = ((CSCM & CSCM_RESET_CONTROLLER_MODE_PARAM) | CSCM_AUTOMATIC))

/*
 *The enable commands automatically disables other possible options, individually for MSB and LSB
 * */


/*

------------------------ABNORMAL_VOLT_AND_CURRENT_STATE(AVCS)--------------------
            7	                        6	                     5	                      4            	3	     2	        1	              0
Abnormal High Line-Current	Abnormal Low Line-Current	Abnormal Low Voltage	Abnormal High Voltage	RSVD	RSVD	Potline Outage	Normal Control

*/
#define AVCS_RESET										(AVCS = 0)
#define AVCS_NORMAL_CONTROL								(1U << 0)
#define AVCS_POTLINE_OUTAGE								(1U << 1)
#define AVCS_ABNORMAL_HIGH_VOLTAGE						(1U << 4)
#define AVCS_ABNORMAL_LOW_VOLTAGE						(1U << 5)
#define AVCS_ABNORMAL_LOW_LINE_CURRENT					(1U << 6)
#define AVCS_ABNORMAL_HIGH_LINE_CURRENT					(1U << 7)

//state commands
#define AVCS_IS_NORMAL_CONTROL							(AVCS & AVCS_NORMAL_CONTROL)
#define AVCS_IS_POTLINE_OUTAGE							(AVCS & AVCS_POTLINE_OUTAGE)
#define AVCS_IS_ABNORMAL_HIGH_VOLTAGE					(AVCS & AVCS_ABNORMAL_HIGH_VOLTAGE)
#define AVCS_IS_ABNORMAL_LOW_VOLTAGE					(AVCS & AVCS_ABNORMAL_LOW_VOLTAGE)
#define AVCS_IS_ABNORMAL_LOW_LINE_CURRENT				(AVCS & AVCS_ABNORMAL_LOW_LINE_CURRENT)
#define AVCS_IS_ABNORMAL_HIGH_LINE_CURRENT				(AVCS & AVCS_ABNORMAL_HIGH_LINE_CURRENT)

//enable commands
#define AVCS_NORMAL_CONTROL_EN							(AVCS |= (AVCS_NORMAL_CONTROL))
#define AVCS_POTLINE_OUTAGE_EN							(AVCS |= (AVCS_POTLINE_OUTAGE))
#define AVCS_ABNORMAL_HIGH_VOLTAGE_EN					(AVCS |= (AVCS_ABNORMAL_HIGH_VOLTAGE))
#define AVCS_ABNORMAL_LOW_VOLTAGE_EN					(AVCS |= (AVCS_ABNORMAL_LOW_VOLTAGE))
#define AVCS_ABNORMAL_LOW_LINE_CURRENT_EN				(AVCS |= (AVCS_ABNORMAL_LOW_LINE_CURRENT))
#define AVCS_ABNORMAL_HIGH_LINE_CURRENT_EN				(AVCS |= (AVCS_ABNORMAL_HIGH_LINE_CURRENT))

//disable commands
#define AVCS_NORMAL_CONTROL_RESET						(AVCS &=~ (AVCS_NORMAL_CONTROL))
#define AVCS_POTLINE_PUTAGE_RESET						(AVCS &=~ (AVCS_POTLINE_OUTAGE))
#define AVCS_ABNORMAL_HIGH_VOLTAGE_RESET				(AVCS &=~ (AVCS_ABNORMAL_HIGH_VOLTAGE))
#define AVCS_ABNORMAL_LOW_VOLTAGE_RESET					(AVCS &=~ (AVCS_ABNORMAL_LOW_VOLTAGE))
#define AVCS_ABNORMAL_LOW_LINE_CURRENT_RESET			(AVCS &=~ (AVCS_ABNORMAL_LOW_LINE_CURRENT))
#define AVCS_ABNORMAL_HIGH_LINE_CURRENT_RESET			(AVCS &=~ (AVCS_ABNORMAL_HIGH_LINE_CURRENT))


/*
 *
 *------------------------------FEED_CONTROL(FEED)-----------------------------------------
15	     14	     13	     12	     11	     10	     9	    8
RSVD	RSVD	RSVD	RSVD	RSVD	RSVD	RSVD	RSVD
Feed State
7	     6	     5	     4	     3	     2	           1	            0
RSVD	RSVD	RSVD	RSVD	RSVD	RSVD	"Balanced Feed(BF)"	Normal Feed (NF)
 *
 * */

#define FEED_NORMAL										(1U << 0)
#define FEED_BALANCED								 	(1U << 1)
#define FEED_RESET										(FEED = 0)
#define FEED_RESET_PARAM								(0xFF00)
//#define CSCM_RESET_CONTROLLER_MODE_PARAM				(0x00FF)

//state commands
#define FEED_IS_NORMAL									(FEED & FEED_NORMAL)
#define FEED_IS_BALANCED								(FEED & FEED_BALANCED)

//enable commands   {CSCM = ((CSCM & CSCM_RESET_CELL_STATE_PARAM) | CSCM_IN_OPERATION)}
#define FEED_NORMAL_SET									(FEED = ((FEED & FEED_RESET_PARAM) | FEED_NORMAL))
#define FEED_BALANCED_SET								(FEED = ((FEED & FEED_RESET_PARAM) | FEED_BALANCED))

//The SETable commands automatically disables other possible options, individually for LSB (FEED)

/*
 * ------------------------------------Flag(FLAG)-----------------------------------------
 * 15	   14	   13	   12	   11	      	10	  	  			9	        8
RSVD	  RSVD	  RSVD	  EWMA	  T_ABNL_LOW_A	T_ABNL_HIGH_A	  T_ABNL_LOW_V  T_ABML_HIGH_V

Feed State
7	     6	     5	     4	          3	            2	        1	        0
RSVD	RSVD   POTOUT  ABNL_LOW_A	ABNL_HIGH_A	  ABNL_LOW_V  ABML_HIGH_V  NORMAL
 *
 * */
#define FLAG_NORMAL										(1U << 0)
#define FLAG_ABNORMAL_HIGH_VOLT							(1U << 1)
#define FLAG_ABNORMAL_LOW_VOLT							(1U << 2)
#define FLAG_ABNORMAL_HIGH_CURRENT						(1U << 3)
#define FLAG_ABNORMAL_LOW_CURRENT						(1U << 4)
#define FLAG_POTOUT										(1U << 5)
#define FLAG_TIM_ABNORMAL_HIGH_VOLT						(1U << 8)
#define FLAG_TIM_ABNORMAL_LOW_VOLT						(1U << 9)
#define FLAG_TIM_ABNORMAL_HIGH_CURRENT					(1U << 10)
#define FLAG_TIM_ABNORMAL_LOW_CURRENT					(1U << 11)
#define FLAG_EWMA										(1U << 12)




#define FLAG_RESET_MSB_PARAM							(0x00FF)
#define FLAG_RESET_LSB_PARAM							(0xFF00)


#define FLAG_NORMAL_SET									(FLAG |= (FLAG_NORMAL))
#define FLAG_NORMAL_RESET								(FLAG &= (FLAG_NORMAL))
#define FLAG_ABNORMAL_HIGH_VOLT_SET						(FLAG |= (FLAG_ABNORMAL_HIGH_VOLT))
#define FLAG_ABNORMAL_HIGH_VOLT_RESET					(FLAG &= (FLAG_ABNORMAL_HIGH_VOLT))
#define FLAG_ABNORMAL_LOW_VOLT_SET						(FLAG |= (FLAG_ABNORMAL_LOW_VOLT))
#define FLAG_ABNORMAL_LOW_VOLT_RESET					(FLAG &= (FLAG_ABNORMAL_LOW_VOLTT))
#define FLAG_ABNORMAL_HIGH_CURRENT_SET					(FLAG |= (FLAG_ABNORMAL_HIGH_CURRENT))
#define FLAG_ABNORMAL_HIGH_CURRENT_RESET				(FLAG &= (FLAG_ABNORMAL_HIGH_CURRENT))
#define FLAG_ABNORMAL_LOW_CURRENT_SET					(FLAG |= (FLAG_ABNORMAL_LOW_CURRENT))
#define FLAG_ABNORMAL_LOW_CURRENT_RESET					(FLAG &= (FLAG_ABNORMAL_LOW_CURRENT))
#define FLAG_ABNORMAL_POTOUT_SET					    (FLAG |= (FLAG_POTOUT))
#define FLAG_ABNORMAL_POTOUT_RESET						(FLAG &= (FLAG_POTOUT))

#define FLAG_CLEAR_ALL									(FLAG = (FLAG & 0xFF00))
// set flag
#define FLAG_TIM_ABNORMAL_HIGH_VOLT_SET					(FLAG |= FLAG_TIM_ABNORMAL_HIGH_VOLT)
#define FLAG_TIM_ABNORMAL_LOW_VOLT_SET					(FLAG |= FLAG_TIM_ABNORMAL_LOW_VOLT	)
#define FLAG_TIM_ABNORMAL_HIGH_CURRENT_SET				(FLAG |= FLAG_TIM_ABNORMAL_HIGH_CURRENT)
#define FLAG_TIM_ABNORMAL_LOW_CURRENT_SET				(FLAG |= FLAG_TIM_ABNORMAL_LOW_CURRENT	)
#define FLAG_EWMA_SET                                   (FLAG |= FLAG_EWMA)

// reset flag
#define FLAG_TIM_ABNORMAL_HIGH_VOLT_RESET				(FLAG &=~ FLAG_TIM_ABNORMAL_HIGH_VOLT)
#define FLAG_TIM_ABNORMAL_LOW_VOLT_RESET				(FLAG &=~ FLAG_TIM_ABNORMAL_LOW_VOLT	)
#define FLAG_TIM_ABNORMAL_HIGH_CURRENT_RESET			(FLAG &=~ FLAG_TIM_ABNORMAL_HIGH_CURRENT	)
#define FLAG_TIM_ABNORMAL_LOW_CURRENT_RESET				(FLAG &=~ FLAG_TIM_ABNORMAL_LOW_CURRENT	)
#define FLAG_EWMA_RESET									(FLAG &=~ FLAG_EWMA)
//state
#define FLAG_IS_NORMAL									(FLAG & FLAG_NORMAL)
#define FLAG_IS_ABNORMAL_HIGH_VOLT						(FLAG & FLAG_ABNORMAL_HIGH_VOLT)
#define FLAG_IS_ABNORMAL_LOW_VOLT						(FLAG & FLAG_ABNORMAL_LOW_VOLT)
#define FLAG_IS_ABNORMAL_HIGH_CURRENT					(FLAG & FLAG_ABNORMAL_HIGH_CURRENT)
#define FLAG_IS_ABNORMAL_LOW_CURRENT					(FLAG & FLAG_ABNORMAL_LOW_CURRENT)
#define FLAG_IS_POTOUT									(FLAG & FLAG_POTOUT)
#define FLAG_IS_TIM_ABNORMAL_HIGH_VOLT					(FLAG & FLAG_TIM_ABNORMAL_HIGH_VOLT)
#define FLAG_IS_TIM_ABNORMAL_LOW_VOLT					(FLAG & FLAG_TIM_ABNORMAL_LOW_VOLT	)
#define FLAG_IS_TIM_ABNORMAL_HIGH_CURRENT				(FLAG & FLAG_TIM_ABNORMAL_HIGH_CURRENT)
#define FLAG_IS_TIM_ABNORMAL_LOW_CURRENT				(FLAG & FLAG_TIM_ABNORMAL_LOW_CURRENT)
#define FLAG_IS_EWMA									(FLAG & FLAG_EWMA)
/*
 * --------------------------RESISTANCE CONTROL(RCCTRL)--------------------------------------------------
 *
 * */

/*
RESISTANCE CONTROL
15	      14	 13	     12	     11      	10	                              9	                                         8
RSVD	RSVD	RSVD	RSVD	RSVD	Resistance Control Timeout	 Cell Resistance Control Failed Alarm	 Resistance Control Failed Alarm
RESISTANCE CONTROL
7	           6	        5	       4 	       3	      2          	1	                                    0
ZONE3 LOW	ZONE2 LOW	ZONE1 LOW	ZONE3 UP	ZONE2 UP	ZONE1 UP	Resistance Control Treatment Active  	Resistance Control State Active
*/

#define RCCTRL_RES_CTRL_STATE_ACTIVE					(1U << 0)
#define RCCTRL_RES_CTRL_TREATMENT_ACTIVE				(1U << 1)
#define RCCTRL_ZONE_1_UP								(1U << 2)
#define RCCTRL_ZONE_2_UP								(1U << 3)
#define RCCTRL_ZONE_3_UP								(1U << 4)
#define RCCTRL_ZONE_1_LOW								(1U << 5)
#define RCCTRL_ZONE_2_LOW								(1U << 6)
#define RCCTRL_ZONE_3_LOW								(1U << 7)
#define RCCTRL_RES_CTRL_FAILED_ALARM					(1U << 8)
#define RCCTRL_CELL_RES_CTRL_FAILED_ALARM				(1U << 9)
#define RCCTRL_RES_CTRL_TIMEOUT							(1U << 10)

//enable commands

#define RCCTRL_RES_CTRL_STATE_ACTIVE_SET				(RCCTRL |= RCCTRL_RES_CTRL_STATE_ACTIVE)
#define RCCTRL_RES_CTRL_TREATMENT_ACTIVE_SET			(RCCTRL |= RCCTRL_RES_CTRL_TREATMENT_ACTIVE)
#define RCCTRL_ZONE_1_UP_SET							(RCCTRL |= RCCTRL_ZONE_1_UP)
#define RCCTRL_ZONE_2_UP_SET				            (RCCTRL |= RCCTRL_ZONE_2_UP)
#define RCCTRL_ZONE_3_UP_SET							(RCCTRL |= RCCTRL_ZONE_3_UP)
#define RCCTRL_ZONE_1_LOW_SET							(RCCTRL |= RCCTRL_ZONE_1_LOW)
#define RCCTRL_ZONE_2_LOW_SET							(RCCTRL |= RCCTRL_ZONE_2_LOW)
#define RCCTRL_ZONE_3_LOW_SET							(RCCTRL |= RCCTRL_ZONE_3_LOW)
#define RCCTRL_RES_CTRL_FAILED_ALARM_SET				(RCCTRL |= RCCTRL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_CELL_RES_CTRL_FAILED_ALARM_SET			(RCCTRL |= RCCTRL_CELL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_RES_CTRL_TIMEOUT_SET						(RCCTRL |= RCCTRL_RES_CTRL_TIMEOUT)

//disable commands

#define RCCTRL_RES_CTRL_STATE_ACTIVE_RESET				(RCCTRL &= RCCTRL_RES_CTRL_STATE_ACTIVE)
#define RCCTRL_RES_CTRL_TREATMENT_ACTIVE_RESET			(RCCTRL &= RCCTRL_RES_CTRL_TREATMENT_ACTIVE)
#define RCCTRL_ZONE_1_UP_RESET							(RCCTRL &= RCCTRL_ZONE_1_UP)
#define RCCTRL_ZONE_2_UP_RESET				            (RCCTRL &= RCCTRL_ZONE_2_UP)
#define RCCTRL_ZONE_3_UP_RESET							(RCCTRL &= RCCTRL_ZONE_3_UP)
#define RCCTRL_ZONE_1_LOW_RESET							(RCCTRL &= RCCTRL_ZONE_1_LOW)
#define RCCTRL_ZONE_2_LOW_RESET							(RCCTRL &= RCCTRL_ZONE_2_LOW)
#define RCCTRL_ZONE_3_LOW_RESET							(RCCTRL &= RCCTRL_ZONE_3_LOW)
#define RCCTRL_RES_CTRL_FAILED_ALARM_RESET				(RCCTRL &= RCCTRL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_CELL_RES_CTRL_FAILED_ALARM_RESET			(RCCTRL &= RCCTRL_CELL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_RES_CTRL_TIMEOUT_RESET					(RCCTRL &= RCCTRL_RES_CTRL_TIMEOUT)
// #define RCCTRL_ALL_ZONE_RESET                           (RCCTRL &= RCCTRL_ZONE_1_)

//state commands
#define RCCTRL_IS_RES_CTRL_STATE_ACTIVE					(RCCTRL & RCCTRL_RES_CTRL_STATE_ACTIVE)
#define RCCTRL_IS_RES_CTRL_TREATMENT_ACTIVE				(RCCTRL & RCCTRL_RES_CTRL_TREATMENT_ACTIVE)
#define RCCTRL_IS_ZONE_1_UP								(RCCTRL & RCCTRL_ZONE_1_UP)
#define RCCTRL_IS_ZONE_2_UP       		        	    (RCCTRL & RCCTRL_ZONE_2_UP)
#define RCCTRL_IS_ZONE_3_UP								(RCCTRL & RCCTRL_ZONE_3_UP)
#define RCCTRL_IS_ZONE_1_LOW							(RCCTRL & RCCTRL_ZONE_1_LOW)
#define RCCTRL_IS_ZONE_2_LOW							(RCCTRL & RCCTRL_ZONE_2_LOW)
#define RCCTRL_IS_ZONE_3_LOW							(RCCTRL & RCCTRL_ZONE_3_LOW)
#define RCCTRL_IS_RES_CTRL_FAILED_ALARM				    (RCCTRL & RCCTRL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_IS_CELL_RES_CTRL_FAILED_ALARM			(RCCTRL & RCCTRL_CELL_RES_CTRL_FAILED_ALARM)
#define RCCTRL_IS_RES_CTRL_TIMEOUT						(RCCTRL & RCCTRL_RES_CTRL_TIMEOUT)




#endif /* REG_H_ */
