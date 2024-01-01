#pragma once
class CImageProcessing
{
public:
	//�Ҷ�ͼ����
	Mat RGB_2_Gray(Mat src);	//RGBת�Ҷ�
	void Show_Histogram(Mat src);	//��ʾ�Ҷ�ֱ��ͼ
	Mat EqualizeHist(Mat src);	//ֱ��ͼ���⻯
	Mat GrayscaleLinearTransform(Mat inputImage, double alpha, double beta);	//�Ҷ����Ա任
	Mat grayscaleLogTransform(Mat inputImage, double c);	//�Ҷȶ����任
	Mat grayscaleGammaTransform(Mat inputImage, double gamma);	//�Ҷ�٤��任

	//��̬ѧ����
	Mat ImageErosion(Mat inputImage, int erosionSize);	//��ʴ
	Mat ImageDilation(Mat inputImage, int dilationSize);	//����
	Mat ImageBrightness(Mat inputImage, int brightvalue);	//����
	Mat ImageSaturation(Mat inputImage, int saturation);	//���Ͷ�
	Mat ImageSharpen(Mat inputImage, int percent, int type);	//��
	Mat ColorTemperature(Mat inputImage, int percent);		//ɫ�µ���

	//ͼ��ָ�
	Mat imageThresholdSegmentation(Mat inputImage, int threshold);	//�̶���ֵ�ָ�
	Mat adaptiveThresholdSegmentation(Mat inputImage, int blockSize, int subtractValue);	//����Ӧ��ֵ�ָ�
	Mat regionGrowingSegmentation(Mat inputImage, int seedX, int seedY, int threshold);	//���������ָ�
	Mat sobelEdgeDetection(Mat inputImage, int kernelSize);	//Sobel��Ե���
	Mat cannyEdgeDetection(Mat inputImage, double threshold1, double threshold2);	//Canny��Ե���

	//ͼ���˲�
	Mat meanFilter(Mat inputImage, int kernelSize);	//��ֵ�˲�
	Mat medianFilter(Mat inputImage, int kernelSize);	//��ֵ�˲�
	Mat gaussianFilter(Mat inputImage, int kernelSize, double sigma);//��˹�˲�

	//�������
	Mat detectFaces(Mat inputImage);
};

