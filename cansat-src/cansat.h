/*
 * cansat.h
 *
 *  Created on: 07.02.2017
 *      Author: grzegorz
 */

#ifndef CANSAT_H_
#define CANSAT_H_

#include <main.h>
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>
#include <diag/Trace.h>
#include "FATFS/src/ff.h"
#include <stm32f1xx_hal.h>

#include "tasks/radio/radio.h"
#include "tasks/bmp180/bmp180.h"
#include "tasks/imu/imu.h"

//externs
extern SPI_HandleTypeDef hspi1;
extern I2C_HandleTypeDef hi2c1;
extern I2C_HandleTypeDef hi2c2;

//functions
void CanSatMain();
void CreateSynchronizationObjects();

#endif /* CANSAT_H_ */
