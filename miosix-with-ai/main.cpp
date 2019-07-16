/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/

#include "miosix.h"
#include "LSM6DSLSensor.h"
#include <cstdio>
#include <stdio.h>
#include "Middlewares/ST/AI/AI/include/estimator.h"
#include "Middlewares/ST/AI/AI/data/estimator_data.h"

#define AI_NETWORK_CONFIG  \
  AI_BUFFER_OBJ_INIT( \
    AI_BUFFER_FORMAT_U8, \
    1, 1, 0, 1, \
    AI_ESTIMATOR_DATA_CONFIG )
	
#define __FPU_PRESENT 1U
	
using namespace std;
using namespace miosix;

void aiLogErr(const ai_error err, const char *fct);
int aiInit(void);
int aiRun(const ai_float *in_data, ai_float *out_data, const ai_u16 batch_size);




/* Global handle to reference the instantiated NN */
static ai_handle network = AI_HANDLE_NULL;

/* Global buffer to handle the activations data buffer - R/W data */
static ai_u8 activations[AI_ESTIMATOR_DATA_ACTIVATIONS_SIZE];

static ai_buffer ai_input[AI_ESTIMATOR_IN_NUM] = { AI_ESTIMATOR_IN_1 };
static ai_buffer ai_output[AI_ESTIMATOR_OUT_NUM] = { AI_ESTIMATOR_OUT_1 };


void aiLogErr(const ai_error err, const char *fct)
{
	if (fct)
		printf("E: AI error (%s) - type=%d code=%d\r\n", fct, err.type, err.code);
	else
		printf("E: AI error - type=%d code=%d\r\n", err.type, err.code);
}

int aiInit(void) 
{
	ai_error err;
	const ai_buffer ai_network = {AI_BUFFER_FORMAT_U8, 1, 1, 0, 1, AI_ESTIMATOR_DATA_CONFIG};

	err = ai_estimator_create(&network, &ai_network);
	if (err.type != AI_ERROR_NONE) 
	{
		/* manage the error */
		printf("E: AI error - type=%d code=%d\r\n", err.type, err.code);
	}
	
	/* initialize network */
	
	const ai_network_params params = {
		AI_ESTIMATOR_DATA_WEIGHTS(ai_estimator_data_weights_get()),
		AI_ESTIMATOR_DATA_ACTIVATIONS(activations) };
	
	if (!ai_estimator_init(network, &params)) 
	{
		err = ai_estimator_get_error(network);
		/* manage the error */
		aiLogErr(err, "ai_network_init");
	}
}

int aiRun(const ai_float *in_data, ai_float *out_data, const ai_u16 batch_size)
{
	ai_i32 nbatch;
	ai_error err;

	/* initialize input/output buffer handlers */
	ai_input[0].n_batches = batch_size;
	ai_input[0].data = AI_HANDLE_PTR(in_data);
	ai_output[0].n_batches = batch_size;
	ai_output[0].data = AI_HANDLE_PTR(out_data);
	nbatch = ai_estimator_run(network, &ai_input[0], &ai_output[0]);
	if (nbatch != batch_size) 
	{
		err = ai_estimator_get_error(network);
		/* manage the error */
		aiLogErr(err, "ai_estimator_run");
	}
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  
	LSM6DSLSensor *acc_gyro;
	
	int32_t axes[3];
	uint8_t id;
	int i = 0;
	
	int32_t acc_x[201];
	
	
	
	acc_gyro = new LSM6DSLSensor(LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH);
	acc_gyro->init(NULL);
	acc_gyro->enable_x();
	acc_gyro->enable_g();
	int b=0;
	aiInit();

	printf("%d\n",acc_gyro->read_id(&id));
	printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);
  
  /* Infinite loop */
  while (1)
  {
	printf("\r\n")
	acc_gyro->get_x_axes(axes);
	acc_x[i] = axes[0];
	
	//printf("LSM6DSL [acc/mg]:      %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
		
	//acc_gyro->get_g_axes(axes);
	//printf("LSM6DSL [gyro/mdps]:   %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);

	Thread::sleep(10);
	i+=1;
	if(i=200)
	{
		i=0;
		/* for (i=0;i<=200;i++)
		{
			printf("%6ld",acc_x[i]);
		} */
	}
	

  }

}


