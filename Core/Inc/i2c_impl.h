#ifndef I2C_IMPL_H
#define I2C_IMPL_H

#include <stdint.h>

int _i2c_master_init_impl(void);
int _i2c_master_write_impl(const uint8_t device, const uint8_t reg, const void* buf, uint16_t len);
int _i2c_master_read_impl(const uint8_t device, const uint8_t reg, void* buf, uint16_t len);

#endif // I2C_IMPL_H