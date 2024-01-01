#include "pch.h"
#include "CImageProcessing.h"

#define max2(a,b) (a>b?a:b)
#define max3(a,b,c) (a>b?max2(a,c):max2(b,c))
#define min2(a,b) (a<b?a:b)
#define min3(a,b,c) (a<b?min2(a,c):min2(b,c))
Mat CImageProcessing::RGB_2_Gray(Mat src)
{
    Mat result;
    // RGBת����GRAY
    cvtColor(src, result, cv::COLOR_BGR2GRAY);
    return result;
}

void CImageProcessing::Show_Histogram(Mat src)
{
	Mat image_gray, hist;   //��������ͼ�񣬻Ҷ�ͼ��, ֱ��ͼ

	cvtColor(src, image_gray, COLOR_BGR2GRAY);  //�ҶȻ�
	//imshow(" image_gray", image_gray);   //��ʾ�Ҷ�ͼ��

	//��ȡͼ��ֱ��ͼ
	int histsize = 256;
	float ranges[] = { 0,256 };
	const float* histRanges = { ranges };
	calcHist(&image_gray, 1, 0, Mat(), hist, 1, &histsize, &histRanges, true, false);

	//����ֱ��ͼ��ʾͼ��
	int hist_h = 300;//ֱ��ͼ��ͼ��ĸ�
	int hist_w = 512; //ֱ��ͼ��ͼ��Ŀ�
	int bin_w = hist_w / histsize;//ֱ��ͼ�ĵȼ�
	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));//����ֱ��ͼ��ʾ��ͼ��

	//���Ʋ���ʾֱ��ͼ
	normalize(hist, hist, 0, hist_h, NORM_MINMAX, -1, Mat());//��һ��ֱ��ͼ
	for (int i = 1; i < histsize; i++)
	{
		line(histImage, Point((i - 1) * bin_w, hist_h - cvRound(hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
	}
	imshow("histImage", histImage);

	waitKey(0);  //��ͣ������ͼ����ʾ���ȴ���������
}

Mat CImageProcessing::EqualizeHist(Mat src)
{
	Mat image_gray, image_enhanced;   //��������ͼ�񣬻Ҷ�ͼ��, ֱ��ͼ

	cvtColor(src, image_gray, COLOR_BGR2GRAY);  //�ҶȻ�
	//imshow(" image_gray", image_gray);   //��ʾ�Ҷ�ͼ��

	equalizeHist(image_gray, image_enhanced);//ֱ��ͼ���⻯
	//imshow(" image_enhanced", image_enhanced);   //��ʾ��ǿͼ��

	return image_enhanced;
}

Mat CImageProcessing::GrayscaleLinearTransform(Mat inputImage, double alpha, double beta)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ���Ա任��new_pixel_value = alpha * original_pixel_value + beta
	// y = kx + b
	cv::Mat transformedImage = cv::Mat::zeros(grayImage.size(), CV_8U);
	for (int y = 0; y < grayImage.rows; ++y) {
		for (int x = 0; x < grayImage.cols; ++x) {
			int originalPixelValue = static_cast<int>(grayImage.at<uchar>(y, x));
			int newPixelValue = cv::saturate_cast<uchar>(alpha * originalPixelValue + beta);
			transformedImage.at<uchar>(y, x) = newPixelValue;
		}
	}

	return transformedImage;
}

Mat CImageProcessing::grayscaleLogTransform(Mat inputImage, double c)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// �����任��new_pixel_value = c * log(1 + original_pixel_value)
	cv::Mat transformedImage = cv::Mat::zeros(grayImage.size(), CV_8U);
	for (int y = 0; y < grayImage.rows; ++y) {
		for (int x = 0; x < grayImage.cols; ++x) {
			int originalPixelValue = static_cast<int>(grayImage.at<uchar>(y, x));
			int newPixelValue = cv::saturate_cast<uchar>(c * std::log(1 + originalPixelValue));
			transformedImage.at<uchar>(y, x) = newPixelValue;
		}
	}

	return transformedImage;
}

Mat CImageProcessing::grayscaleGammaTransform(Mat inputImage, double gamma)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ٤��任��new_pixel_value = 255 * (original_pixel_value / 255) ^ gamma
	cv::Mat transformedImage = cv::Mat::zeros(grayImage.size(), CV_8U);
	for (int y = 0; y < grayImage.rows; ++y) {
		for (int x = 0; x < grayImage.cols; ++x) {
			int originalPixelValue = static_cast<int>(grayImage.at<uchar>(y, x));
			int newPixelValue = cv::saturate_cast<uchar>(255 * std::pow(originalPixelValue / 255.0, gamma));
			transformedImage.at<uchar>(y, x) = newPixelValue;
		}
	}

	return transformedImage;
}

Mat CImageProcessing::ImageErosion(Mat inputImage, int erosionSize)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ���帯ʴ�ˣ��ṹԪ�أ�
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * erosionSize + 1, 2 * erosionSize + 1),
		cv::Point(erosionSize, erosionSize));

	// ���и�ʴ����
	cv::Mat erodedImage;
	cv::erode(grayImage, erodedImage, element);

	return erodedImage;
}

Mat CImageProcessing::ImageDilation(Mat inputImage, int dilationSize)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// �������ͺˣ��ṹԪ�أ�
	cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2 * dilationSize + 1, 2 * dilationSize + 1),
		cv::Point(dilationSize, dilationSize));

	// �������Ͳ���
	cv::Mat dilatedImage;
	cv::dilate(grayImage, dilatedImage, element);

	return dilatedImage;
}

Mat CImageProcessing::ImageBrightness(Mat inputImage, int brightvalue)
{
	cv::Mat brightImage;
	brightImage = cv::Mat::zeros(inputImage.size(), inputImage.type());
	int height = inputImage.rows;
	int width = inputImage.cols;
	//cv::Mat temp;
	//inputImage.convertTo(temp, CV_32F);
	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			if (inputImage.channels() == 3) {
				float b = inputImage.at<cv::Vec3b>(row, col)[0];
				float g = inputImage.at<cv::Vec3b>(row, col)[1];
				float r = inputImage.at<cv::Vec3b>(row, col)[2];
				brightImage.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(b + brightvalue);
				brightImage.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(g + brightvalue);
				brightImage.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(r + brightvalue);
			}
			else if (inputImage.channels() == 1) {
				float v = inputImage.at<uchar>(row, col);
				brightImage.at<uchar>(row, col) = saturate_cast<uchar>(v + brightvalue);
			}
		}
	}
	return brightImage;
}

Mat CImageProcessing::ImageSaturation(Mat inputImage, int saturation)
{
	float Increment = saturation * 1.0f / 100;
	cv::Mat result = inputImage.clone();
	int row = inputImage.rows;
	int col = inputImage.cols;
	for (int i = 0; i < row; ++i) {
		uchar* t = result.ptr<uchar>(i);
		uchar* s = inputImage.ptr<uchar>(i);
		for (int j = 0; j < col; ++j) {
			uchar b = s[3 * j];
			uchar g = s[3 * j + 1];
			uchar r = s[3 * j + 2];
			float max = max3(r, g, b);
			float min = min3(r, g, b);
			float delta, value;
			float L, S, alpha;
			delta = (max - min) / 255;
			if (delta == 0)
				continue;
			value = (max + min) / 255;
			L = value / 2;
			if (L < 0.5)
				S = delta / value;
			else
				S = delta / (2 - value);
			if (Increment >= 0) {
				if ((Increment + S) >= 1)
					alpha = S;
				else
					alpha = 1 - Increment;
				alpha = 1 / alpha - 1;
				t[3 * j + 2] = static_cast<uchar>(r + (r - L * 255) * alpha);
				t[3 * j + 1] = static_cast<uchar>(g + (g - L * 255) * alpha);
				t[3 * j] = static_cast<uchar>(b + (b - L * 255) * alpha);
			}
			else {
				alpha = Increment;
				t[3 * j + 2] = static_cast<uchar>(L * 255 + (r - L * 255) * (1 + alpha));
				t[3 * j + 1] = static_cast<uchar>(L * 255 + (g - L * 255) * (1 + alpha));
				t[3 * j] = static_cast<uchar>(L * 255 + (b - L * 255) * (1 + alpha));
			}
		}
	}
	return result;
}

Mat CImageProcessing::ImageSharpen(Mat inputImage, int percent, int type)
{
	cv::Mat sharpenImage;
	cv::Mat s = inputImage.clone();
	cv::Mat kernel;
	switch (type) {
		case 0:
			kernel = (Mat_<int>(3, 3) <<
				0, -1, 0,
				-1, 4, -1,
				0, -1, 0
				);
			break;
		case 1:
			kernel = (Mat_<int>(3, 3) <<
				-1, -1, -1,
				-1, 8, -1,
				-1, -1, -1
				);
			break;
		default:
			kernel = (Mat_<int>(3, 3) <<
				0, -1, 0,
				-1, 4, -1,
				0, -1, 0
				);
			break;
	}
	filter2D(s, s, s.depth(), kernel);
	sharpenImage = inputImage + s * 0.01 * percent;
	return sharpenImage;
}

Mat CImageProcessing::ColorTemperature(Mat inputImage, int percent)
{
	cv::Mat result = inputImage.clone();
	int row = inputImage.rows;
	int col = inputImage.cols;
	int level = percent / 2;
	for (int i = 0; i < row; ++i) {
		uchar* a = inputImage.ptr<uchar>(i);
		uchar* r = result.ptr<uchar>(i);
		for (int j = 0; j < col; ++j) {
			int R, G, B;
			R = a[j * 3 + 2];
			R = R + level;
			if (R > 255)
				r[j * 3 + 2] = 255;
			else if (R < 0)
				r[j * 3 + 2] = 0;
			else
				r[j * 3 + 2] = R;
			G = a[j * 3 + 1];
			G = G + level;
			if (G > 255)
				r[j * 3 + 1] = 255;
			else if (G < 0)
				r[j * 3 + 1] = 0;
			else
				r[j * 3 + 1] = G;
			B = a[j * 3];
			B = B + level;
			if (B > 255)
				r[j * 3] = 255;
			else if (B < 0)
				r[j * 3] = 0;
			else
				r[j * 3] = B;
		}
	}
	return result;
}


Mat CImageProcessing::imageThresholdSegmentation(Mat inputImage, int threshold)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ���й̶���ֵ�ָ�
	cv::Mat segmentedImage;
	cv::threshold(grayImage, segmentedImage, threshold, 255, cv::THRESH_BINARY);

	return segmentedImage;
}

Mat CImageProcessing::adaptiveThresholdSegmentation(Mat inputImage, int blockSize, int subtractValue)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ��������Ӧ��ֵ�ָ�
	cv::Mat segmentedAdaptive;
	cv::adaptiveThreshold(grayImage, segmentedAdaptive, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
		cv::THRESH_BINARY, blockSize, subtractValue);

	return segmentedAdaptive;
}

Mat CImageProcessing::regionGrowingSegmentation(Mat inputImage, int seedX, int seedY, int threshold)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ��ʼ���ָ�ͼ��
	Mat segmentedImage = cv::Mat::zeros(grayImage.size(), CV_8U);

	// ��ȡ���ӵ�ĳ�ʼ�Ҷ�ֵ
	int seedValue = static_cast<int>(grayImage.at<uchar>(seedY, seedX));

	// �����������ڱ�����������������
	std::queue<std::pair<int, int>> pixelQueue;
	pixelQueue.push(std::make_pair(seedX, seedY));

	// ��ʼ��������
	while (!pixelQueue.empty()) {
		int x = pixelQueue.front().first;
		int y = pixelQueue.front().second;
		pixelQueue.pop();

		// ��鵱ǰ�����Ƿ��ѱ������
		if (segmentedImage.at<uchar>(y, x) == 0) {
			// ���㵱ǰ���������ӵ�ĻҶȲ�
			int pixelValue = static_cast<int>(grayImage.at<uchar>(y, x));
			int diff = std::abs(seedValue - pixelValue);

			// ����ҶȲ�С����ֵ�������ָ�����
			if (diff <= threshold) {
				segmentedImage.at<uchar>(y, x) = 255;

				// ����ǰ���ص�����������
				for (int dy = -1; dy <= 1; ++dy) {
					for (int dx = -1; dx <= 1; ++dx) {
						int newX = x + dx;
						int newY = y + dy;
						if (newX >= 0 && newX < grayImage.cols && newY >= 0 && newY < grayImage.rows) {
							pixelQueue.push(std::make_pair(newX, newY));
						}
					}
				}
			}
		}
	}

	return segmentedImage;
}

Mat CImageProcessing::sobelEdgeDetection(Mat inputImage, int kernelSize)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ����Sobel��Ե���
	cv::Mat gradientX, gradientY;
	cv::Sobel(grayImage, gradientX, CV_16S, 1, 0, kernelSize);
	cv::Sobel(grayImage, gradientY, CV_16S, 0, 1, kernelSize);

	// �����ݶȷ�ֵ
	cv::Mat absGradientX, absGradientY;
	cv::convertScaleAbs(gradientX, absGradientX);
	cv::convertScaleAbs(gradientY, absGradientY);

	// �ϲ�X��Y�ݶȷ�ֵ
	cv::Mat gradientImage;
	cv::addWeighted(absGradientX, 0.5, absGradientY, 0.5, 0, gradientImage);

	return gradientImage;
}

Mat CImageProcessing::cannyEdgeDetection(Mat inputImage, double threshold1, double threshold2)
{
	// ��RGBͼ��ת��Ϊ�Ҷ�ͼ��
	cv::Mat grayImage;
	cv::cvtColor(inputImage, grayImage, cv::COLOR_BGR2GRAY);

	// ����Canny��Ե���
	cv::Mat edgeImage;
	cv::Canny(grayImage, edgeImage, threshold1, threshold2);

	return edgeImage;
}

Mat CImageProcessing::meanFilter(Mat inputImage, int kernelSize)
{
	cv::Mat filteredImage;
	// ʹ�þ�ֵ�˲�
	cv::blur(inputImage, filteredImage, cv::Size(kernelSize, kernelSize));
	return filteredImage;
}

Mat CImageProcessing::medianFilter(Mat inputImage, int kernelSize)
{
	cv::Mat filteredImage;
	// ʹ����ֵ�˲�
	cv::medianBlur(inputImage, filteredImage, kernelSize);
	return filteredImage;
}

Mat CImageProcessing::gaussianFilter(Mat inputImage, int kernelSize, double sigma)
{
	cv::Mat filteredImage;
	// ʹ�ø�˹�˲�
	cv::GaussianBlur(inputImage, filteredImage, cv::Size(kernelSize, kernelSize), sigma);
	return filteredImage;
}

Mat CImageProcessing::detectFaces(Mat inputImage)
{
	/*********************************** 1.�������������  ******************************/
	// ��������������
	CascadeClassifier cascade;
	// ����ѵ���õ� �����������.xml��
	//ע��·�����⣬��ǰĿ¼����һ��Ŀ¼�е�xml�ļ�����
	const string path = "C:\\Users\\ssx\\Desktop\\ImageSystem\\xml\\haarcascade_frontalface_alt.xml";
	if (!cascade.load(path))
	{
		AfxMessageBox(TEXT("cascade load failed!"));
	}

	//��ʱ
	double t = 0;
	t = (double)getTickCount();
	/*********************************** 2.������� ******************************/
	vector<Rect> faces(0);
	cascade.detectMultiScale(inputImage, faces, 1.1, 2, 0, Size(30, 30));

	//cout << "detect face number is :" << faces.size() << endl;

	CString str;
	str.Format(TEXT("detect face number is : %d"), faces.size());
	AfxMessageBox(str);

	/********************************  3.��ʾ�������ο� ******************************/

	if (faces.size() > 0)
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			rectangle(inputImage, faces[i], Scalar(150, 0, 0), 3, 8, 0);
		}
	}
	else AfxMessageBox(TEXT("δ��⵽����"));

	//t = (double)getTickCount() - t;  //getTickCount():  Returns the number of ticks per second.
	//cout << "���������ʱ��" << t * 1000 / getTickFrequency() << "ms (���������ģ�͵�ʱ�䣩" << endl;

	//namedWindow("face_detect");
	//imshow("face_detect", inputImage);
	//waitKey(0);

	//destroyWindow("display");
	//destroyWindow("face_detect");

	return inputImage;
}

