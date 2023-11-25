/*
 * pcf8574.h
 *
 *  Created on: Sep 24, 2022
 *      Author: rajdeep
 */

#ifndef INC_PCF8574_H_
#define INC_PCF8574_H_



char int_pow(char base, char exp);
void pcf8574_init(uint8_t exp_num, uint8_t exp_addr);

void pcf8574_setaddr(int exp_num, int addr);

//void pcf8574_write(uint8_t data_write);

void pcf8574_write(int exp_num, int port_num, int port_state, int send_cmd);


#endif /* INC_PCF8574_H_ */
