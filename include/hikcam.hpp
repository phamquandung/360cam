#ifndef HIKCAM_HPP
#define HIKCAM_HPP

#include <string>
#include <vector>
#include <thread>
#include <opencv2/opencv.hpp>

#include "MvCameraControl.h"

#define MAX_CAMERA_NUM     2

class HikCam
{
public:
	long int id;
	HikCam();
	HikCam(int num);
	bool init();
	~HikCam();
	bool getImage(unsigned char **imgs, const bool bconvert=false);
	bool getImage(std::vector<cv::Mat> &imgs);
	void getSingleImage(unsigned char *img, bool &success, const bool bconvert=false, const int flag = 0);
	void getSingleImage(cv::Mat &img, bool &success, const int flag = 0);
	int getCamCount();
	MV_FRAME_OUT_INFO_EX getImgInfo(int flag=0);
	bool PrintDeviceInfo(MV_CC_DEVICE_INFO *pstMVDevInfo);

private:
	int nRet;
	int bstart;
	int camera_count = MAX_CAMERA_NUM;
	void* mhandle[MAX_CAMERA_NUM] = {nullptr};
    unsigned char* mImg[MAX_CAMERA_NUM];
    unsigned int mDataSize[MAX_CAMERA_NUM];
    MV_FRAME_OUT_INFO_EX mImageInfo[MAX_CAMERA_NUM];
    std::string mSN[MAX_CAMERA_NUM];
    void readImage(void* handle, unsigned char* img, unsigned int dataSize, 
    					MV_FRAME_OUT_INFO_EX& imgInfo, bool &success);
	void readConvertImage(void* handle, unsigned char* img, unsigned int dataSize, 
							MV_FRAME_OUT_INFO_EX& imgInfo, bool &success);
	void readMat(void* handle, cv::Mat &img, unsigned int dataSize, 
							MV_FRAME_OUT_INFO_EX& imgInfo, bool &success);
};

#endif //HIKCAM_HPP