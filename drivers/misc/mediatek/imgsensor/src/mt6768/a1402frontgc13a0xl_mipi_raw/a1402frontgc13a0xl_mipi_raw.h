/*****************************************************************************
 *
 * Filename:
 * ---------
 *     gc13a0mipi_Sensor.h
 *
 * Project:
 * --------
 *     ALPS
 *
 * Description:
 * ------------
 *     CMOS sensor header file
 *
 ****************************************************************************/
 /*hs14 code for SR-AL6528A-01-54 by chengzhi at 2022-9-28 start*/
#ifndef __GC13A0MIPI_SENSOR_H__
#define __GC13A0MIPI_SENSOR_H__


#define MULTI_WRITE             1
#if MULTI_WRITE
#define I2C_BUFFER_LEN  765 /* Max is 255, each 3 bytes */
#else
#define I2C_BUFFER_LEN  3
#endif

/* SENSOR MIRROR FLIP INFO */
#define GC13A0_MIRROR_NORMAL    1
#define GC13A0_MIRROR_H         0
#define GC13A0_MIRROR_V         0
#define GC13A0_MIRROR_HV        0

#if GC13A0_MIRROR_NORMAL
#define GC13A0_MIRROR	        0x00
#elif GC13A0_MIRROR_H
#define GC13A0_MIRROR	        0x01
#elif GC13A0_MIRROR_V
#define GC13A0_MIRROR	        0x02
#elif GC13A0_MIRROR_HV
#define GC13A0_MIRROR	        0x03
#else
#define GC13A0_MIRROR	        0x00
#endif


#define SENSOR_BASE_GAIN           0x400
#define SENSOR_MAX_GAIN            (16 * SENSOR_BASE_GAIN)

enum{
	IMGSENSOR_MODE_INIT,
	IMGSENSOR_MODE_PREVIEW,
	IMGSENSOR_MODE_CAPTURE,
	IMGSENSOR_MODE_VIDEO,
	IMGSENSOR_MODE_HIGH_SPEED_VIDEO,
	IMGSENSOR_MODE_SLIM_VIDEO,
	IMGSENSOR_MODE_CUSTOM1,
	IMGSENSOR_MODE_CUSTOM2,
	IMGSENSOR_MODE_CUSTOM3,
	IMGSENSOR_MODE_CUSTOM4,
	IMGSENSOR_MODE_CUSTOM5,
	IMGSENSOR_MODE_CUSTOM6,
	IMGSENSOR_MODE_CUSTOM7,
	IMGSENSOR_MODE_CUSTOM8,
};

struct imgsensor_mode_struct {
	kal_uint32 pclk;
	kal_uint32 linelength;
	kal_uint32 framelength;
	kal_uint8 startx;
	kal_uint8 starty;
	kal_uint16 grabwindow_width;
	kal_uint16 grabwindow_height;
	kal_uint32 mipi_pixel_rate;
	kal_uint8 mipi_data_lp2hs_settle_dc;
	kal_uint16 max_framerate;
};

/* SENSOR PRIVATE STRUCT FOR VARIABLES */
struct imgsensor_struct {
	kal_uint8 mirror;
	kal_uint8 sensor_mode;
	kal_uint32 shutter;
	kal_uint16 gain;
	kal_uint32 pclk;
	kal_uint32 frame_length;
	kal_uint32 line_length;
	kal_uint32 min_frame_length;
	kal_uint16 dummy_pixel;
	kal_uint16 dummy_line;
	kal_uint16 current_fps;
	kal_bool   autoflicker_en;
	kal_bool   test_pattern;
	enum MSDK_SCENARIO_ID_ENUM current_scenario_id;
	kal_uint8  ihdr_en;
	kal_uint8 i2c_write_id;
};

/* SENSOR PRIVATE STRUCT FOR CONSTANT */
struct imgsensor_info_struct {
	kal_uint32 sensor_id;
	kal_uint32 checksum_value;
	struct imgsensor_mode_struct pre;
	struct imgsensor_mode_struct cap;

	struct imgsensor_mode_struct normal_video;
	struct imgsensor_mode_struct hs_video;
	struct imgsensor_mode_struct slim_video;
	struct imgsensor_mode_struct custom1; //custom1 scenario relative info
	struct imgsensor_mode_struct custom2; //custom2 scenario relative info
	struct imgsensor_mode_struct custom3; //custom3 scenario relative info
	struct imgsensor_mode_struct custom4; //custom4 scenario relative info
	struct imgsensor_mode_struct custom5; //custom5 scenario relative info
	struct imgsensor_mode_struct custom6; //custom6 scenario relative info
	struct imgsensor_mode_struct custom7; //custom7 scenario relative info
	struct imgsensor_mode_struct custom8; //custom8 scenario relative info
	kal_uint8  ae_shut_delay_frame;
	kal_uint8  ae_sensor_gain_delay_frame;
	kal_uint8  ae_ispGain_delay_frame;
	kal_uint8  ihdr_support;
	kal_uint8  ihdr_le_firstline;
	kal_uint8  sensor_mode_num;
	kal_uint8  cap_delay_frame;
	kal_uint8  pre_delay_frame;
	kal_uint8  video_delay_frame;
	kal_uint8  hs_video_delay_frame;
	kal_uint8  slim_video_delay_frame;
	kal_uint8 custom1_delay_frame; //enter custom1 delay frame num
	kal_uint8 custom2_delay_frame; //enter custom2 delay frame num
	kal_uint8 custom3_delay_frame; //enter custom3 delay frame num
	kal_uint8 custom4_delay_frame; //enter custom4 delay frame num
	kal_uint8 custom5_delay_frame; //enter custom5 delay frame num
	kal_uint8 custom6_delay_frame; //enter custom6 delay frame num
	kal_uint8 custom7_delay_frame; //enter custom7 delay frame num
	kal_uint8 custom8_delay_frame; //enter custom8 delay frame num
	kal_uint8  margin;
	kal_uint32 min_shutter;
	kal_uint32 max_frame_length;
	kal_uint8  isp_driving_current;
	kal_uint8  sensor_interface_type;
	kal_uint8  mipi_sensor_type;
	kal_uint8  mipi_settle_delay_mode;
	kal_uint8  sensor_output_dataformat;
	kal_uint8  mclk;
	kal_uint8  mipi_lane_num;
	kal_uint8  i2c_addr_table[5];
	kal_uint32 i2c_speed;
};

extern int iReadRegI2C(u8 *a_pSendData, u16 a_sizeSendData, u8 *a_pRecvData, u16 a_sizeRecvData, u16 i2cId);
extern int iWriteRegI2C(u8 *a_pSendData, u16 a_sizeSendData, u16 i2cId);
extern int iWriteRegI2CTiming(u8 *a_pSendData, u16 a_sizeSendData, u16 i2cId, u16 timing);
extern int iBurstWriteReg_multi(u8 *pData, u32 bytes, u16 i2cId, u16 transfer_length, u16 timing);

#endif
/*hs14 code for SR-AL6528A-01-54 by chengzhi at 2022-9-28 end*/