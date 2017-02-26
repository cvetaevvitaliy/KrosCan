/*
 * cansat.c
 *
 *  Created on: 07.02.2017
 *      Author: grzegorz
 */

#include <cansat.h>

FATFS sdCardFS;

FIL radio_log;

TaskHandle_t tsk_radio_rx;
TaskHandle_t tsk_radio_tx;

SemaphoreHandle_t PayloadReady_sem;
SemaphoreHandle_t PacketSent_sem;
SemaphoreHandle_t ModeReady_sem;
SemaphoreHandle_t Radio_mutex;

QueueHandle_t Radio_echo;

void vApplicationStackOverflowHook( TaskHandle_t xTask,
                                    signed char *pcTaskName )
{
	trace_printf("StackFail: %s\n", pcTaskName);
	for(;;);
}

void CreateSynchronizationObjects()
{
	//create synchronization objects
	vSemaphoreCreateBinary(PayloadReady_sem);
	vSemaphoreCreateBinary(PacketSent_sem);
	vSemaphoreCreateBinary(ModeReady_sem);
	Radio_mutex = xSemaphoreCreateMutex();

	Radio_echo = xQueueCreate(512, sizeof(char));

}

void CanSatMain()
{
	//initialize the file system
	/*while (f_mount(&sdCardFS, "0:/", 0) != FR_OK)
	{
		trace_printf("Failed to init SD-Card");
	}

	while (f_open(&radio_log, "radio.log", FA_WRITE | FA_OPEN_APPEND) != FR_OK)
	{
		trace_printf("Failed to open radio log");
	}*/

	rfm69_init(hspi1, 1);
	rfm69_setPowerDBm(-2);
	rfm69_setFrequency(433500000);
	rfm69_setMode(RFM69_MODE_RX);
	//rfm69_sleep();


	trace_printf("Radio initialized");

	//start tasks
	xTaskCreate(HandleRadioRX, "radiorx", 128, NULL, tskIDLE_PRIORITY+1, &tsk_radio_rx);
	xTaskCreate(HandleRadioTX, "radiotx", 128, NULL, tskIDLE_PRIORITY+1, &tsk_radio_tx);

	//start FreeRTOS
	vTaskStartScheduler();


	/*
	//Benchmark of writing 1kB of data
	uint32_t time0 = HAL_GetTick();
	uint32_t wbytes;

	char buff[512*20];
	memset(buff, 'C', 512*20); //10 kb buffer

	if(f_open(&file, "bnch3", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
	{
		f_expand(&file, 100*1024, 1);
		for(int i = 0; i<30; i++)
		{
			/* Get physical location of the file data
			    BYTE drv = file.obj.fs->drv;
			    DWORD sect = file.obj.fs->database + file.obj.fs->csize * (file.obj.sclust - 2);

			    /* Write 2048 sectors from top of the file at a time
			    disk_write(drv, buff, sect, 20);
		}

		f_close(&file);

		uint32_t time1 = HAL_GetTick();

		//save test result
		if(f_open(&resfile, "res.txt", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
		{
			f_printf(&resfile, "Writing 300kB of data took %d ms", time1-time0);
			f_close(&resfile);
		}

		trace_printf("Writing 300kB of data took %d ms", time1-time0);
	}
	else
	{
		trace_printf("U fckd up m8");
	}

	for(;;){}*/

	//HAL_GPIO_WritePin(MOTOR_DISABLE_GPIO_Port, MOTOR_DISABLE_Pin, GPIO_PIN_SET);
	//HAL_GPIO_WritePin(MOTOR_DIR_GPIO_Port, MOTOR_DIR_Pin, GPIO_PIN_SET);

	/*for(;;)
	{

	}*/

	/*if (f_mount(&sdCard, "0:/", 0) != FR_OK) {
		trace_printf("Nie mozemy zamontowac karty SD :(\n");
		trace_printf("%s", "0:/");
	}
	if (f_open(&file, "ansAt.txt", FA_CREATE_ALWAYS | FA_WRITE) != FR_OK) {
		trace_printf("Nie udalo sie utworzyc przykladowego pliku\n");
	}

	uint32_t messages = 0;
	uint32_t message_len = 0;
	uint32_t wbytes;
	while (1) {
		messages++;
		message_len = sprintf((char*)buffor, "ASDASDZapisalismy dotychczas %d wiadomosci\n", messages);
		if(f_write(&file, buffor, message_len, (void*)&wbytes) != FR_OK)
		{
			trace_printf("Nie udalo sie zapisac %d wiadomosci\n", messages);
		}
		f_sync(&file);
		trace_printf("%s", buf1);
		HAL_Delay(1000);
		if(messages==10)
			f_close(&file);

	}*/


	/*xTaskHandle lol;
	xTaskHandle lol2;

	xTaskCreate(lols, "Lol", 128, NULL, tskIDLE_PRIORITY+1, &lol);
	xTaskCreate(lols2, "Lol2", 128, NULL, tskIDLE_PRIORITY+1, &lol2);

	vTaskStartScheduler();*/
}

