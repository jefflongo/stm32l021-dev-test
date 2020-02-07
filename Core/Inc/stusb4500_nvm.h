/*
 * File:     stusb4500_nvm.h
 * Author:   jefflongo
 * Comments: Programs the STUSB4500 non-volatile memory
 */

#ifndef STUSB4500_NVM_H
#define STUSB4500_NVM_H

#include <stdbool.h>
#include <stdint.h>

bool nvm_flash(void);
bool nvm_read(uint8_t* sectors_out);
bool nvm_verify(void);

#endif // STUSB4500_NVM_H