/*
 * spi.h
 *
 *  Created on: Oct 15, 2017
 *      Author: t400
 */

#ifndef INC_SPI_H_
#define INC_SPI_H_
#include "main.h"

#define DD_MOSI		DDB5
#define DD_SCK		DDB7
#define SPI_CLK     PB7
#define SPI_MOSI    PB5
#define SPI_MISO    PB6
#define SPI_SS      PB4

void spi_init(uint8_t CSN);
uint8_t spi_transfer(uint8_t data);

#endif /* INC_SPI_H_ */
