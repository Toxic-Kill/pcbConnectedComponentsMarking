#include <iostream>
#include<opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("D:\\Files\\PCB.jpg", 0);//读取图片
	cv::Mat resMat;
	cv::Mat binMat;
	cv::Mat opeMat;
	cv::Mat labMat;
	cv::Mat staMat;
	cv::Mat cenMat;
	threshold(srcMat, binMat, 100, 255, THRESH_BINARY_INV);//图像二值化
	cv::Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(15, 15));//定义结构元素
	morphologyEx(binMat, opeMat, MORPH_OPEN, kernel);//进行开运算
	opeMat.copyTo(resMat);//深复制开运算结果
	int num = cv::connectedComponentsWithStats(opeMat, labMat, staMat, cenMat);//连通域标记
	for (int i = 1; i < num; i++)//画出连通域
	{
		cv::Rect bndbox;
		bndbox.x = staMat.at<int>(i, 0);
		bndbox.y = staMat.at<int>(i, 1);
		bndbox.width = staMat.at<int>(i, 2);
		bndbox.height = staMat.at<int>(i, 3);
		cv::rectangle(resMat, bndbox, CV_RGB(255, 255, 255), 1, 8, 0);
	}
	std::cout << "The number is:" << num - 1 << endl;//自动计件
	cv::imshow("frame", srcMat);//显示原图像
	cv::imshow("binMat", opeMat);//显示二值化图像
	cv::imshow("results", resMat);//显示连通域标记后图像
	waitKey(0);
}