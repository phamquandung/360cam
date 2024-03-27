#include <vector>
#include <string>
#include <chrono>
#include <opencv2/opencv.hpp>

#include "hikcam.hpp"

// std::string getTimeStr(){
//     std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
//     std::string s(30, '\0');
//     std::strftime(&s[0], s.size(), "%Y_%m_%d_%H-%M-%S_", std::localtime(&now));
//     std::cout<<s<<std::endl;
//     return s.substr(0,20);;
// }
std::string getTimeStr(){
	uint64_t timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
	std::cout << "timestamp: " << timestamp << std::endl;
	int timestamp_second = int(timestamp / 1000);
	int timestamp_float = int(timestamp % 1000); 
	std::cout << "timestamp double: " << timestamp_second << std::endl;
	std::cout << "timestamp float: " << timestamp_float << std::endl;
	// std::string s = std::to_string(timestamp_second) + '.' + std::to_string(timestamp_float);
	std::string s = std::to_string(timestamp);
	std::cout << "timestamp string: " << s << std::endl;
	return s;
}
int main(int argc, char const *argv[])
{
    std::string imgPath = "";
    if (argc > 1)
    {
        imgPath = argv[1];
    }
    HikCam mycam;
    if (argc > 2)
    {
        mycam = HikCam(std::stoi(argv[2]));
    }
    if(!mycam.init())
    	return -1;
	std::vector<cv::Mat> vImgs;
	char nameBuff [50];
    int imgID = 0;
    	std::chrono::steady_clock clock;
	while(1)
	{
		if (!mycam.getImage(vImgs))
			return 0;

		for (int i = 0; i < mycam.getCamCount(); ++i)
		{
			cv::Mat img;
			cv::resize(vImgs[i].t(), img, cv::Size(), 0.2, 0.2);
			cv::imshow("img"+std::to_string(i), img);
		}

		MV_FRAME_OUT_INFO_EX imgInfo = mycam.getImgInfo();
		

    	int k = cv::waitKey(100);
    	if (k == 'q')
    	{
    		break;
    	}
    	// else if (k == 'c' || k == 'C')
		if (true)
    	{
    		/* save */
    		sprintf (nameBuff, "_%06d.png", imgID++);
    		std::string savename = getTimeStr();
    		for (int i = 0; i < mycam.getCamCount(); ++i)
			{
				cv::imwrite(imgPath+savename+"_img"+std::to_string(i)+".png", vImgs[i].t());
			}
            printf("GetOneFrame[%d], Width[%d], Height[%d]\n", imgInfo.nFrameNum,
                imgInfo.nWidth, imgInfo.nHeight);
    	}
	}
	return 0;
}
