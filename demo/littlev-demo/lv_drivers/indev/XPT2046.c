/**
 * @file XPT2046.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "XPT2046.h"
#if USE_XPT2046

#include <stddef.h>
#include LV_DRV_INDEV_INCLUDE
#include LV_DRV_DELAY_INCLUDE

/*********************
 *      DEFINES
 *********************/
#define CMD_X_READ  0b10010000
#define CMD_Y_READ  0b11010000

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void xpt2046_corr(int16_t * x, int16_t * y);
static void xpt2046_avg(int16_t * x, int16_t * y);

/**********************
 *  STATIC VARIABLES
 **********************/
int16_t avg_buf_x[XPT2046_AVG];
int16_t avg_buf_y[XPT2046_AVG];
uint8_t avg_last;
unsigned long int *regAddress;

/**********************
 *      MACROS
 **********************/

// #define XPT7603_READ_X  (0x88)
// #define XPT7603_READ_Y  (0x98)
#define XPT7603_READ_X  (0xc8)
#define XPT7603_READ_Y  (0xd8)
#define XPT7603_READ_Z1  (0xb8)
#define XPT7603_READ_Z2  (0xa8)

#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>
 
#define I2C_DEV_PATH   "/dev/i2c-0"
#define EXIT_FAILURE   -1
 
uint16_t om_i2c_read(int addr) {
    int 	status, size;
// 	char 	pathname[255];
	int     numBytes = 2;
	int     devAddr = 0x48;
	int     fd;
    uint8_t buffer[2];
    uint16_t ret = 0;

	//// define the path to open
	//status = sprintf(pathname, I2C_DEV_PATH);
    fd = open(I2C_DEV_PATH, O_RDWR);
    
    //// set the device address
    // set to 7-bit addr
	if ( ioctl(fd, I2C_TENBIT, 0) < 0 ) {
		return EXIT_FAILURE;
	}

	//// write the  address
	if ( ioctl(fd, I2C_SLAVE, devAddr) < 0 ) {
		return EXIT_FAILURE;
	}
	
	//// set addr
	// clear the buffer
	memset( buffer, 0, numBytes );
	// push the address and data values into the buffer
	buffer[0]	= (addr & 0xff);
	size 		= 1;

	// write to the i2c device
	status = write(fd, buffer, size);
	
	// read from the i2c device
	size 	= numBytes;
	status 	= read(fd, &buffer, size);
	
	ret = (buffer[0] & 0xff) << 8;
	ret += buffer[1] & 0xff;
	
	// release the device file handle
	if ( close(fd) < 0 ) {
		return EXIT_FAILURE;
	}
	
	return ret;
 }
 
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define GPIO_REG_BLOCK_ADDR			0x10000000
#define GPIO_REG_DATA0_OFFSET		392
#define GPIO_IRQ_NUMBER    14
 
int om_read_gpio(int gpioNumber) {
    int  m_mfd;
    int regAddrOffset = GPIO_REG_DATA0_OFFSET;
    unsigned long int 	value = 0x0;
    int gpioVal;
    
    if (regAddress == NULL){
        if ((m_mfd = open("/dev/mem", O_RDWR)) < 0)
    	{
    		return EXIT_FAILURE;	// maybe return -1
    	}
    	regAddress = (unsigned long int*)mmap	(	NULL, 
    												1024, 
    												PROT_READ|PROT_WRITE, 
    												MAP_FILE|MAP_SHARED, 
    												m_mfd, 
    												GPIO_REG_BLOCK_ADDR
    											);
        close(m_mfd);
    }
    
	// read the value 
	value = *(regAddress + regAddrOffset);
// 	printf("GPIO_DATA_0 = 0x%08x\n", value);
	
	gpioVal = ((value >> gpioNumber) & 0x1);
// 	printf("gpioVal = %d\n", gpioVal);
	
	return gpioVal;
 }

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/**
 * Initialize the XPT2046
 */
void xpt2046_init(void)
{
    printf("initializing xpt touch\n");
    om_i2c_read(0xd8);
}

/**
 * Get the current position and state of the touchpad
 * @param data store the read data here
 * @return false: because no ore data to be read
 */
bool xpt2046_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static int16_t last_x = 0;
    static int16_t last_y = 0;
    uint8_t buf;

    int16_t x = 0;
    int16_t y = 0;

    // uint8_t irq = LV_DRV_INDEV_IRQ_READ;
    uint8_t irq = (uint8_t)om_read_gpio(GPIO_IRQ_NUMBER);
    // printf("touch irq = %d\n", irq);

    if(irq == 0) {
        // LV_DRV_INDEV_SPI_CS(0);

        // LV_DRV_INDEV_SPI_XCHG_BYTE(CMD_X_READ);         /*Start x read*/

        // buf = LV_DRV_INDEV_SPI_XCHG_BYTE(0);           /*Read x MSB*/
        // x = buf << 8;
        // buf = LV_DRV_INDEV_SPI_XCHG_BYTE(CMD_Y_READ);  /*Until x LSB converted y command can be sent*/
        // x += buf;

        // buf =  LV_DRV_INDEV_SPI_XCHG_BYTE(0);   /*Read y MSB*/
        // y = buf << 8;

        // buf =  LV_DRV_INDEV_SPI_XCHG_BYTE(0);   /*Read y LSB*/
        // y += buf;
        
        x = (int16_t)(om_i2c_read(XPT7603_READ_X) >> 4);
        
        y = (int16_t)(om_i2c_read(XPT7603_READ_Y) >> 4);
        // printf("read\tx = 0x%04x", x);
        // printf("\ty = 0x%04x\n", y);

        /*Normalize Data*/
        // x = x >> 4;
        // y = y >> 4;
        // printf("val\tx = %d", x);
        // printf("\ty = %d\n", y);
        xpt2046_corr(&x, &y);
        xpt2046_avg(&x, &y);

        last_x = x;
        last_y = y;
		data->state = LV_INDEV_STATE_PR;
		
// 		printf("coord\tx = %d", x);
//         printf("\ty = %d\n", y);

        // LV_DRV_INDEV_SPI_CS(1);
    } else {
        x = last_x;
        y = last_y;
        avg_last = 0;
		data->state = LV_INDEV_STATE_REL;
    }

    data->point.x = x;
    data->point.y = y;

    return false;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/
static void xpt2046_corr(int16_t * x, int16_t * y)
{
#if XPT2046_XY_SWAP != 0
    int16_t swap_tmp;
    swap_tmp = *x;
    *x = *y;
    *y = swap_tmp;
#endif

    if((*x) > XPT2046_X_MIN)(*x) -= XPT2046_X_MIN;
    else(*x) = 0;

    if((*y) > XPT2046_Y_MIN)(*y) -= XPT2046_Y_MIN;
    else(*y) = 0;

    (*x) = (uint32_t)((uint32_t)(*x) * XPT2046_HOR_RES) /
           (XPT2046_X_MAX - XPT2046_X_MIN);

    (*y) = (uint32_t)((uint32_t)(*y) * XPT2046_VER_RES) /
           (XPT2046_Y_MAX - XPT2046_Y_MIN);

#if XPT2046_X_INV != 0
    (*x) =  XPT2046_HOR_RES - (*x);
#endif

#if XPT2046_Y_INV != 0
    (*y) =  XPT2046_VER_RES - (*y);
#endif


}


static void xpt2046_avg(int16_t * x, int16_t * y)
{
    /*Shift out the oldest data*/
    uint8_t i;
    for(i = XPT2046_AVG - 1; i > 0 ; i--) {
        avg_buf_x[i] = avg_buf_x[i - 1];
        avg_buf_y[i] = avg_buf_y[i - 1];
    }

    /*Insert the new point*/
    avg_buf_x[0] = *x;
    avg_buf_y[0] = *y;
    if(avg_last < XPT2046_AVG) avg_last++;

    /*Sum the x and y coordinates*/
    int32_t x_sum = 0;
    int32_t y_sum = 0;
    for(i = 0; i < avg_last ; i++) {
        x_sum += avg_buf_x[i];
        y_sum += avg_buf_y[i];
    }

    /*Normalize the sums*/
    (*x) = (int32_t)x_sum / avg_last;
    (*y) = (int32_t)y_sum / avg_last;
}

#endif
