#pragma once
class CImageProcessing
{
public:
	//灰度图像处理
	Mat RGB_2_Gray(Mat src);	//RGB转灰度
	void Show_Histogram(Mat src);	//显示灰度直方图
	Mat EqualizeHist(Mat src);	//直方图均衡化
	Mat GrayscaleLinearTransform(Mat inputImage, double alpha, double beta);	//灰度线性变换
	Mat grayscaleLogTransform(Mat inputImage, double c);	//灰度对数变换
	Mat grayscaleGammaTransform(Mat inputImage, double gamma);	//灰度伽马变换

	//形态学处理
	Mat ImageErosion(Mat inputImage, int erosionSize);	//腐蚀
	Mat ImageDilation(Mat inputImage, int dilationSize);	//膨胀
	Mat ImageBrightness(Mat inputImage, int brightvalue);	//亮度
	Mat ImageSaturation(Mat inputImage, int saturation);	//饱和度
	Mat ImageSharpen(Mat inputImage, int percent, int type);	//锐化
	Mat ColorTemperature(Mat inputImage, int percent);		//色温调节

	//图像分割
	Mat imageThresholdSegmentation(Mat inputImage, int threshold);	//固定阈值分割
	Mat adaptiveThresholdSegmentation(Mat inputImage, int blockSize, int subtractValue);	//自适应阈值分割
	Mat regionGrowingSegmentation(Mat inputImage, int seedX, int seedY, int threshold);	//区域生长分割
	Mat sobelEdgeDetection(Mat inputImage, int kernelSize);	//Sobel边缘检测
	Mat cannyEdgeDetection(Mat inputImage, double threshold1, double threshold2);	//Canny边缘检测

	//图像滤波
	Mat meanFilter(Mat inputImage, int kernelSize);	//均值滤波
	Mat medianFilter(Mat inputImage, int kernelSize);	//中值滤波
	Mat gaussianFilter(Mat inputImage, int kernelSize, double sigma);//高斯滤波

	//人脸检测
	Mat detectFaces(Mat inputImage);
};

