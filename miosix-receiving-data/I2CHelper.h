#ifndef I2CHELPER_H
#define I2CHELPER_H

#include <miosix.h>
#include <util/software_i2c.h>

using namespace miosix;


class I2CHelper
{
	
	
	public:
	
		I2CHelper() {} 	// Create our I2CHelper with an sda and scl predefined for our card
	   
	    
		bool write(uint8_t* pBuffer, uint8_t deviceAddr, uint8_t registerAddr, uint16_t numByteToWrite)
		    {
                    i2c::init();
		    	int i=0;
		    	for(i=0;i<numByteToWrite;i++)
		    	{
		    		i2c::sendStart();
		    		if (i2c::send((unsigned char)deviceAddr))
		    		{
		    			if (i2c::send((unsigned char)(registerAddr+i)))
		    			{
		    				if(!i2c::send((unsigned char)*(pBuffer+i)))
		    				{
		    					return false;
		    				}
		    			}
		    			else
		    			{
		    				return false;
		    			}
		    		}
		    		else
		    		{
		    			return false;
		    		}
		    	}
		    	
		    	i2c::sendStop();
		   	delayUs(10);
		    	
		    	return true;
		    }
		    
		   bool read(uint8_t* pBuffer, uint8_t deviceAddr, uint8_t registerAddr,  uint16_t numByteToRead)
		    {
                       i2c::init();
		    	int i=0;
		    	for (i=0;i<numByteToRead;i++)
		    	{
		    		i2c::sendStart();
		    		if (i2c::send((unsigned char)deviceAddr))
		    		{
		    			if (i2c::send((unsigned char)(registerAddr+i)))
					{
		    				i2c::sendRepeatedStart();
						unsigned char sl_addr=(unsigned char)(deviceAddr+1);
						if(i2c::send((unsigned char)sl_addr))
						{
							*(pBuffer+i)=i2c::recvWithNack();
							i2c::sendStop();
							delayUs(10);
						}
					}
		    			else
		    				return false;
		    		}
		    		else
		    			return false;	 
		    	}
		    
		    	return true;
		    }

	    
	    

	private:

	    	typedef Gpio<GPIOB_BASE,8> scl; // D14
		typedef Gpio<GPIOB_BASE,9> sda; // D15
		typedef Gpio<GPIOB_BASE,5> INT1_pin; // D4
		typedef Gpio<GPIOB_BASE,4> INT2_pin; // D5
		typedef SoftwareI2C<sda,scl> i2c; // i2c used by miosix
};



#endif
