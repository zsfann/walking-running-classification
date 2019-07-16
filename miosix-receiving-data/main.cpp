#include "miosix.h"
#include "LSM6DSLSensor.h"
#include <cstdio>
#include <stdio.h>
#include <functional>
#include <stdint.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

using namespace std;
using namespace miosix;

typedef Gpio<GPIOC_BASE,7>  led;

int main()
{
	/*for(;;)
	{
		Thread::sleep(100);
		ledOn();
		Thread::sleep(100);
		ledOff();
	}*/
	printf("ok");
	
	LSM6DSLSensor *acc_gyro;
        int32_t axes[3];
        uint8_t id;
	acc_gyro = new LSM6DSLSensor(LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH);
	//acc_gyro->init(NULL);
	acc_gyro->enable_x();
  	acc_gyro->enable_g();

  	printf("%d\n",acc_gyro->read_id(&id));
  	printf("LSM6DSL accelerometer & gyroscope = 0x%X\r\n", id);
	
	//led::mode(Mode::OUTPUT);
	
    	for(;;)
    	{
        	printf("ok");
			
			printf("\r\n");
        	acc_gyro->get_x_axes(axes);
    		printf("LSM6DSL [acc/mg]:      %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
                
    		acc_gyro->get_g_axes(axes);
    		printf("LSM6DSL [gyro/mdps]:   %6ld, %6ld, %6ld\r\n", axes[0], axes[1], axes[2]);
		

    		Thread::sleep(1000);
    	}
}
