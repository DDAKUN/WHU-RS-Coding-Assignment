#include <opencv2/opencv.hpp>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
using namespace cv;

void grayLinearTransformation(string name) {
	Mat image = imread(name, 0);
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	int newmax, newmin;
	cout << "请输入新的灰度范围" << endl;
	cin >> newmin >> newmax;//获取新的灰度范围
	float alpha = 0;
	Mat dst(image.size(), image.type());//创建一个新矩阵
	
		for (int row = 0; row < rows; row++) {//遍历像素
			for (int col = 0; col < cols; col++) {
				double minVal = 0.0;
				double maxVal = 0.0;
				minMaxLoc(image, &minVal, &maxVal);//获取原图像灰度范围
				int v = image.at<uchar>(row, col);
				alpha = (newmax - newmin) / (maxVal - minVal);
				dst.at<uchar>(row, col) = saturate_cast<uchar>(alpha * (v - minVal) + newmin);//运用灰度变换公式,并防止越界
			}
		}
	imshow("origin", image);
	imshow("output", dst);
	waitKey(0);
	imwrite("out.png", dst);
	
}

vector<uchar> getNeighbor(Mat& image,int i,int j,int dim,int channal) {//获取邻域
	vector<uchar> neighbor;
	if (dim == 1) {//灰度图的情况
		neighbor.push_back(image.at<uchar>(i, j+1));
		neighbor.push_back(image.at<uchar>(i-1, j+1));
		neighbor.push_back(image.at<uchar>(i-1, j));
		neighbor.push_back(image.at<uchar>(i-1, j-1));
		neighbor.push_back(image.at<uchar>(i, j-1) );
		neighbor.push_back(image.at<uchar>(i+1, j-1));
		neighbor.push_back(image.at<uchar>(i+1, j));
		neighbor.push_back(image.at<uchar>(i+1, j+1));
		neighbor.push_back(image.at<uchar>(i, j));
	};
	if (dim == 3) {// 彩色图像的情况
		neighbor.push_back(image.at<Vec3b>(i, j + 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i - 1, j + 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i - 1, j)[channal]);
		neighbor.push_back(image.at<Vec3b>(i - 1, j - 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i, j - 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i + 1, j - 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i + 1, j)[channal]);
		neighbor.push_back(image.at<Vec3b>(i + 1, j + 1)[channal]);
		neighbor.push_back(image.at<Vec3b>(i, j)[channal]);
	}
	return neighbor;
}


void medianFlitering(string name, int dims) {
	Mat image;
	if (dims == 1) {//读取图像
		image = imread(name, 0);
	}
	if (dims == 3) {
		image = imread(name, 1);
	}
	Mat dst(image.size(), image.type());//建立新矩阵
	vector<uchar> newvec;
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	for (int i = 0;i < rows;i++) {//遍历像素
		for (int j = 0; j < cols; j++) {
			if ((i - 1) > 0 && (i + 1) < rows && (j - 1) > 0 && (j + 1) < cols) {//判断是否在边缘
				if (dims == 3) {
					for (int m = 0;m < 3;m++) {//三个通道分别处理
						newvec = getNeighbor(image, i, j, dims, m);
						sort(newvec.begin(), newvec.end());//对窗口内进行排序
						dst.at<Vec3b>(i, j)[m] = newvec[5];
					}
				}
				if (dims == 1) {
					newvec = getNeighbor(image, i, j, dims, 0);
					sort(newvec.begin(), newvec.end());//对窗口内进行排序
					dst.at<uchar>(i, j) = newvec[5];
				}
			}
			else {
				if (dims == 3) {
					dst.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);//边缘的处理
				}
				if (dims == 1) {
					dst.at<uchar>(i, j) = dst.at<uchar>(i, j);
				}
			}
		}
	}
	imshow("origin", image);
	imshow("output", dst);
	waitKey(0);
	imwrite("out.png", dst);
	
}

void filter(string name, int dims) {
	Mat image;
	if (dims == 1) {//读取图像
		image = imread(name, 0);
	}
	if (dims == 3) {
		image = imread(name, 1);
	}
	cout << "请选择滤波模式\n1.高通滤波\n2.低通滤波" << endl;
	int mode = 0;
	cin >> mode;
	Mat dst(image.size(), image.type());//建立新矩阵
	double High[9] = { -1,0,-1,0,-1,0,-1,0,5 };//定义高通滤波数组
	double Low[9] = { 1,1,1,1,1,1,1,1,1 };
	vector<uchar> newvec;
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	int sum = 0;
	if(mode == 1){
		for (int i = 0;i < rows;i++) {//遍历像素
			for (int j = 0; j < cols; j++) {
				if ((i - 1) > 0 && (i + 1) < rows && (j - 1) > 0 && (j + 1) < cols) {//判断是否在边缘
					if (dims == 3) {
						for (int m = 0;m < 3;m++) {//三个通道分别处理
							newvec = getNeighbor(image, i, j, dims, m);//获取邻域
							for (int s = 0;s < 9;s++) {
								sum = sum + (newvec[s] * High[s]);//运用算子进行计算
							}
							dst.at<Vec3b>(i, j)[m] = sum;
							sum = 0;
						}
					}
					if (dims == 1) {
						newvec = getNeighbor(image, i, j, dims, 0);
						for (int s = 0;s < 9;s++) {
							sum = sum + (newvec[s] * High[s]);
						}
						dst.at<uchar>(i, j) = sum;
						sum = 0;
					}
				}
				else {
					if (dims == 3) {
						dst.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);//边缘的处理
					}
					if (dims == 1) {
						dst.at<uchar>(i, j) = dst.at<uchar>(i, j);
					}
				}
			}
		}
	}
	if (mode == 2) {
		for (int i = 0;i < rows;i++) {//遍历像素
			for (int j = 0; j < cols; j++) {
				if ((i - 1) > 0 && (i + 1) < rows && (j - 1) > 0 && (j + 1) < cols) {//判断是否在边缘
					if (dims == 3) {
						for (int m = 0;m < 3;m++) {//三个通道分别处理
							newvec = getNeighbor(image, i, j, dims, m);//获取邻域
							for (int s = 0;s < 9;s++) {
								sum = sum + (newvec[s] * Low[s]);//运用算子进行计算
							}
							dst.at<Vec3b>(i, j)[m] = sum/9;
							sum = 0;
						}
					}
					if (dims == 1) {
						newvec = getNeighbor(image, i, j, dims, 0);
						for (int s = 0;s < 9;s++) {
								sum = sum + (newvec[s] * Low[s]);//运用算子进行计算
						}
							dst.at<uchar>(i, j) = sum/9;
							sum = 0;
					}
				}
				else {
					if (dims == 3) {
						dst.at<Vec3b>(i, j) = image.at<Vec3b>(i, j);//边缘的处理
					}
					if (dims == 1) {
						dst.at<uchar>(i, j) = dst.at<uchar>(i, j);
					}
				}
			}
		}
	}
	imshow("origin", image);
	imshow("output", dst);
	waitKey(0);
	imwrite("out.png", dst);
	
}

void pseudoColorEnhancement(string name) {
	Mat image;
	image = imread(name, 0);
	int v = 0;
	Mat dst1(image.size(), CV_8UC3);
	Mat dst2(image.size(), CV_8UC3);//建立新矩阵
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	for (int i = 0;i < rows;i++) {//遍历像素
		for (int j = 0; j < cols; j++) {
			v = image.at<unsigned char>(i, j);
			dst1.at<Vec3b>(i, j)[0] = abs(255 - v); //blue
			dst1.at<Vec3b>(i, j)[1] = abs(127 - v); //green
			dst1.at<Vec3b>(i, j)[2] = abs(0 - v); //red
		}
	}
	for (int i = 0;i < rows;i++) {//遍历像素
		for (int j = 0; j < cols; j++) {
			v = image.at<uchar>(i, j);
			if (v <= 51)
			{
				dst2.at<Vec3b>(i, j)[0] = 255;
				dst2.at<Vec3b>(i, j)[1] = v * 5;
				dst2.at<Vec3b>(i, j)[2] = 0;
			}
			else if (v <= 102)
			{
				v -= 51;
				dst2.at<Vec3b>(i, j)[0] = 255 - v * 5;
				dst2.at<Vec3b>(i, j)[1] = 255;
				dst2.at<Vec3b>(i, j)[2] = 0;
			}
			else if (v <= 153)
			{
				v -= 102;
				dst2.at<Vec3b>(i, j)[0] = 0;
				dst2.at<Vec3b>(i, j)[1] = 255;
				dst2.at<Vec3b>(i, j)[2] = v * 5;
			}
			else if (v <= 204)
			{
				v -= 153;
				dst2.at<Vec3b>(i, j)[0] = 0;
				dst2.at<Vec3b>(i, j)[1] = 255 - uchar(128.0 * v / 51.0 + 0.5);
				dst2.at<Vec3b>(i, j)[2] = 255;
			}
			else
			{
				v -= 204;
				dst2.at<Vec3b>(i, j)[0] = 0;
				dst2.at<Vec3b>(i, j)[1] = 127 - uchar(127.0 * v / 51.0 + 0.5);
				dst2.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
	imshow("origin", image);
	imshow("output1", dst1);
	imshow("output2", dst2);
	waitKey(0);
	imwrite("out1.png", dst1);
	imwrite("out2.png", dst2);
}

int maxFrequency(Mat& image) {//寻找频率最大的灰度值
	int fre[256]={};
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	for (int i = 0;i < rows;i++) {//遍历像素
		for (int j = 0; j < cols; j++) {
			int v = image.at<uchar>(i, j);
			fre[v]++;//统计各灰度频率
		}
	}
	int max = 0;
	int maxGrayscale = 0;
	for (int i = 0;i < 256;i++) {
		if (fre[i] > max) {
			max = fre[i];
			maxGrayscale = i;
		}
	}//得出最大频率最大的灰度值
	return maxGrayscale;
}


void equalizeCallback(string name)
{
	Mat image = imread(name);
	Mat dst;
	Mat ycrcb;
	//用cvtColor函数将BGR图像转化为YCrCb
	cvtColor(image, ycrcb, COLOR_BGR2YCrCb);
	vector<Mat> channels;
	split(ycrcb, channels);
	//函数只有两参数：输入参数和输出参数
	equalizeHist(channels[0], channels[0]);
	//合成生成的通道并将其转换为BGR格式
	merge(channels, ycrcb);
	cvtColor(ycrcb, dst, COLOR_YCrCb2BGR);
	imshow("origin", image);
	imshow("output", dst);
	waitKey(0);
	imwrite("out.png", dst);
}

void geometricTransformation(string name, int dims) {
	Mat image;
	if (dims == 1) {//读取图像
		image = imread(name, 0);
	}
	if (dims == 3) {
		image = imread(name, 1);
	}
	cout << "请选择滤波模式\n1.平移\n2.缩放\n3.旋转" << endl;
	int mode = 0;
	cin >> mode;
	int rows = image.rows; 
	int cols = image.cols;
	if (mode == 1) {
		Mat dst(image.size(), image.type());
		int xOffset = 100;
		int yOffset = 200;
		for (int i = 0; i < rows; i++)//遍历式平移
		{
			for (int j = 0; j < cols; j++)
			{
				int x = j + xOffset;
				int y = i + yOffset;
				if (x >= 0 && y >= 0 && x < cols && y < rows)//溢出保护
				{
					if (dims == 1) {
						dst.at<uchar>(y, x) = image.at<uchar>(i, j);
					}
					if (dims == 3) {
						dst.at<Vec3b>(y, x) = image.at<Vec3b>(i, j);
					}
					
				}
			}
		}
		imshow("origin", image);
		imshow("output", dst);
		waitKey(0);
		imwrite("out.png", dst);
	}
	if (mode == 2) {
		double mul_num = 0.8;//大于1是放大，小于1是缩小
		int row_num = (int)floor(rows * mul_num), col_num = (int)floor(cols * mul_num);
		Mat dst(row_num, col_num, image.type());
		for (int i = 0; i < row_num; i++){
			for (int j = 0; j < col_num; j++){
				int x = (int)1.0 / mul_num * i, y = (int)1.0 / mul_num * j;
				if (dims == 1) {
					dst.at<uchar>(i, j) = image.at<uchar>(x, y);
				}
				if (dims == 3) {
					dst.at<Vec3b>(i, j) = image.at<Vec3b>(x, y);
				}
			}
		}
		imshow("origin", image);
	    imshow("output", dst);
	    waitKey(0);
	    imwrite("out.png", dst);
	}
	if (mode == 3){

		double angle = 135.0 * 3.1415926 / 180.0;//把角度化成弧度
		int dis = ceil(sqrt(pow(rows, 2) + pow(cols, 2)));//新图像的长宽应该是原图像的对角线长度
		Mat dst(dis, dis, image.type());

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				//计算应该平移的距离
				float cenX = dst.rows / 2 - ((rows / 2) * cos(angle) - (cols / 2) * sin(angle));
				float cenY = dst.cols / 2 - ((rows / 2) * sin(angle) + (cols / 2) * cos(angle));
				//按照仿射矩阵计算后进行平移
				int x = i * cos(angle) - j * sin(angle) + cenX;
				int	y = i * sin(angle) + j * cos(angle) + cenY;
				if (dims == 1) {
					dst.at<uchar>(x, y) = image.at<uchar>(i, j);
				}
				if (dims == 3) {
					dst.at<Vec3b>(x, y) = image.at<Vec3b>(i, j);
				}
			}
		}
		imshow("origin", image);
		imshow("output", dst);
		waitKey(0);
		imwrite("out.png", dst);

	}

	
}


void binaryzation(string name) {
	Mat image;
	image = imread(name, 0);
	Mat dst(image.size(), CV_8UC1);
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	cout << "请输入二值化模式\n1.状态法\n2.判断分析法" << endl;
	int mode = 0;
	cin >> mode;
	if (mode == 1) {//状态法
		int threshold = maxFrequency(image);//获取阈值
		for (int i = 0;i < rows;i++) {//遍历像素
			for (int j = 0; j < cols; j++) {
				int v = image.at<uchar>(i, j);
				if (v >= threshold) {
					dst.at<uchar>(i, j) = 255;
				}
				else {
					dst.at<uchar>(i, j) = 0;
				}
			}
		}
	}
	if (mode == 2) {//判断分析法
		double sum1 = 0, sum2 = 0, sumgray1 = 0, sumgray2 = 0;
		double variance1 = 0, variance2 = 0, avg1 = 0, avg2 = 0;
		double varw = 0, varb = 0, max = 0;
		int v = 0, threshold = 0;
		for (int gray = 0;gray < 256;gray++) {
			for (int i = 0;i < rows;i++) {//遍历像素
				for (int j = 0; j < cols; j++) {
					if (image.at<uchar>(i, j) <= gray) {
						sum1++;
						v = image.at<uchar>(i, j);
						sumgray1 += v;
					}
					else {
						sum2++;
						v = image.at<uchar>(i, j);
						sumgray2 += v;
					}
				}//计算各组的像元数和灰度总值
			}
			if (sum1 == 0) {
				avg1 = 0;
				avg2 = sumgray2 / sum2;
			}
			else if (sum2 == 0) {
				avg2 = 0;
				avg1 = sumgray1 / sum1;
			}
			else {
				avg1 = sumgray1 / sum1;
				avg2 = sumgray2 / sum2;
			}//计算各组灰度均值
			for (int i = 0;i < rows;i++) {//遍历像素
				for (int j = 0; j < cols; j++) {
					if (image.at<uchar>(i, j) <= gray) {
						v = image.at<uchar>(i, j);
						variance1 = variance1 + (v - avg1) * (v - avg1);
					}
					else {
						v = image.at<uchar>(i, j);
						variance2 = variance2 + (v - avg2) * (v - avg2);
					}
				}
			}//计算各组灰度方差
			variance1 = variance1 / sum1;variance2 = variance2 / sum2;
			varw = sum1 * variance1 + sum2 * variance2;
			varb = sum1 * sum2 * (avg1 - avg2) * (avg1 - avg2);//计算组内方差和组间方差
			if ((varb / varw) > max) {
				max = (varb / varw);
				threshold = gray;
			}
			sum1 = 0, sum2 = 0, sumgray1 = 0, sumgray2 = 0;
			variance1 = 0, variance2 = 0, avg1 = 0, avg2 = 0;
			varw = 0, varb = 0;

		}
		for (int i = 0;i < rows;i++) {//遍历像素
			for (int j = 0; j < cols; j++) {
				int v = image.at<uchar>(i, j);
				if (v >= threshold) {
					dst.at<uchar>(i, j) = 255;
				}
				else {
					dst.at<uchar>(i, j) = 0;
				}
			}
		}
	}
	imshow("origin", image);
	imshow("output", dst);
	waitKey(0);
	imwrite("out.png", dst);

}

Mat gaussianbrf(Mat &image, float r,int mode)
{
	Mat gaussianBlur(image.size(), CV_32FC1); //CV_32FC1
	float d0 = 2 * r * r;//高斯函数参数，越小，频率高斯滤波器越窄，滤除高频成分越多，图像就越平滑
	if (mode == 1) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//分子,计算pow必须为float型
				gaussianBlur.at<float>(i, j) = expf(-d / d0);//expf为以e为底求幂（必须为float型）
			}
		}
		imshow("高斯低通滤波器", gaussianBlur);
		imwrite("filtout.tif", gaussianBlur);
	}
	if (mode == 2) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//分子,计算pow必须为float型
				gaussianBlur.at<float>(i, j) = 1 - expf(-d / d0);//expf为以e为底求幂（必须为float型）
			}
		}
		imshow("高斯高通滤波器", gaussianBlur);
		imwrite("filtout.tif", gaussianBlur);
	}
	return gaussianBlur;
}

Mat butterworthbrf(Mat& image, float r, int mode)
{
	Mat butterworthBlur(image.size(), CV_32FC1); 
	float d0 = r * r;
	if (mode == 1) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				butterworthBlur.at<float>(i, j) = 1 / (1 + pow(d / d0, 2));
			}
		}
		imshow("butterworth低通滤波器", butterworthBlur);
		imwrite("filtout.tif", butterworthBlur);
	}
	if (mode == 2) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				butterworthBlur.at<float>(i, j) = 1 / (1 + pow(d0 / d, 2));
			}
		}
		imshow("butterworth高通滤波器", butterworthBlur);
		imwrite("filtout.tif", butterworthBlur);
	}
	return butterworthBlur;
}


Mat expbrf(Mat& image, float r, int mode)
{
	Mat expBlur(image.size(), CV_32FC1);
	float d0 = r * r;
	if (mode == 1) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				expBlur.at<float>(i, j) = expf(-pow(d / d0, 2));
			}
		}
		imshow("expBlur低通滤波器", expBlur);
		imwrite("filtout.tif", expBlur);
	}
	if (mode == 2) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				expBlur.at<float>(i, j) = expf(-pow(d0 / d, 2));
			}
		}
		imshow("expBlur高通滤波器", expBlur);
		imwrite("filtout.tif", expBlur);
	}
	return expBlur;
}

Mat idealbrf(Mat& image, float r, int mode)
{
	Mat idealBlur(image.size(), CV_32FC1);
	float d0 = r * r;
	if (mode == 1) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				if (d <= d0) {
					idealBlur.at<float>(i, j) = 1;
				}
				if (d > d0) {
					idealBlur.at<float>(i, j) = 0;
				}
			}
		}
		imshow("idealBlur低通滤波器", idealBlur);
		imwrite("filtout.tif", idealBlur);
	}
	if (mode == 2) {
		for (int i = 0;i < image.rows; i++)
		{
			for (int j = 0; j < image.cols; j++)
			{
				float d = pow(float(i - image.rows / 2), 2) + pow(float(j - image.cols / 2), 2);//计算pow必须为float型
				if (d <= d0) {
					idealBlur.at<float>(i, j) = 0;
				}
				if (d > d0) {
					idealBlur.at<float>(i, j) = 1;
				}
			}
		}
		imshow("idealBlur高通滤波器", idealBlur);
		imwrite("filtout.tif", idealBlur);
	}
	return idealBlur;
}


int getOptimalDFTSizeW(int a) {//获取图像进行傅里叶变换的最佳大小，D=2^p+2^q+5^n>a,D的最小值就是最佳大小
	int n = 0, min = 100000;
	for (int i = 0;i < 14;i++) {
		for (int j = 0;j < 14;j++) {
			for (int m = 0;m < 14;m++) {
				n = pow(2, i) + pow(3, j) + pow(5, m);
				if (n > a) {
					if (n < min) {
						min = n;
					}
				}
			}
		}
	}
	return min;
}


void magnitudeW(Mat& image1, Mat& image2, Mat& dst) {//求图像幅值，即为两图像该点值的平方和开根号，便于显示
	for (int i = 0;i < image1.rows;i++) {
		for (int j = 0;j < image1.cols;j++) {
			dst.at<float>(i, j) = sqrt(image1.at<float>(i, j) * image1.at<float>(i, j) + image2.at<float>(i, j) * image2.at<float>(i, j));
		}
	}
}

void normalizeW(Mat& image, Mat& dst, float max, float min) {//归一化处理，采用线性方法
	double minVal = 0.0;
	double maxVal = 0.0;
	minMaxLoc(image, &minVal, &maxVal);
	for (int i = 0;i < image.rows;i++) {
		for (int j = 0;j < image.cols;j++) {
			dst.at<float>(i, j) = ((image.at<float>(i, j) - minVal)*(max-min))/(maxVal-minVal)+min;
		}
	}
}

void freqFilt(string name)
{
	Mat image = imread(name, 0);
	
	int w = getOptimalDFTSizeW(image.cols);
	int h = getOptimalDFTSizeW(image.rows); //获取进行dtf的最优尺寸
	Mat padded(h,w,image.type());//建立一个新矩阵
	for (int i = 0;i < padded.rows;i++) {//边界填充,便于傅里叶计算
		for (int j = 0;j < padded.cols;j++) {
			if (i < image.rows && j < image.cols) {
				padded.at<uchar>(i, j) = image.at<uchar>(i, j);
			}
			else {
				padded.at<uchar>(i, j) = 0;
			}
		}
	}
	padded.convertTo(padded, CV_32FC1); //将图像转换为float型
	
	int mode = 0, r = 0;
	cout << "请输入模式\n1.低通滤波\n2.高通滤波" << endl;
	cin >> mode;
	cout << "请选择滤波器\n1.理想滤波器\n2.butterworth滤波器\n3.指数滤波器\n4.高斯滤波器" << endl;
	cin >> r;
	Mat blur;
	if (r == 1) {
		blur = idealbrf(padded, 45, mode);
	}
	if (r == 2) {
		blur = butterworthbrf(padded, 45, mode);
	}
	if (r == 3) {
		blur = expbrf(padded, 45, mode);
	}
	if (r == 4) {
		blur = gaussianbrf(padded, 45, mode);
	}
	

	//DFT操作
	Mat plane[] = { padded, Mat::zeros(padded.size() , CV_32FC1) }; //创建通道，存储dft后的实部与虚部（CV_32F，必须为单通道数）
	Mat complexIm;
	merge(plane, 2, complexIm);//合并通道 （把两个矩阵合并为一个2通道的Mat类容器）
	dft(complexIm, complexIm);//进行傅立叶变换，结果保存在自身  

	//中心化，便于显示
	split(complexIm, plane);//分离通道（数组分离）
	int cx = plane[0].cols / 2;int cy = plane[0].rows / 2;
	Mat part1_r(plane[0], Rect(0, 0, cx, cy));  //移动图像 (零频移到中心)
	Mat part2_r(plane[0], Rect(cx, 0, cx, cy));
	Mat part3_r(plane[0], Rect(0, cy, cx, cy));
	Mat part4_r(plane[0], Rect(cx, cy, cx, cy));

	Mat temp;
	part1_r.copyTo(temp);  //左上与右下交换位置(实部)
	part4_r.copyTo(part1_r);
	temp.copyTo(part4_r);

	part2_r.copyTo(temp);  //右上与左下交换位置(实部)
	part3_r.copyTo(part2_r);
	temp.copyTo(part3_r);

	Mat part1_i(plane[1], Rect(0, 0, cx, cy));  //元素坐标(cx,cy)
	Mat part2_i(plane[1], Rect(cx, 0, cx, cy));
	Mat part3_i(plane[1], Rect(0, cy, cx, cy));
	Mat part4_i(plane[1], Rect(cx, cy, cx, cy));

	part1_i.copyTo(temp);  //左上与右下交换位置(虚部)
	part4_i.copyTo(part1_i);
	temp.copyTo(part4_i);

	part2_i.copyTo(temp);  //右上与左下交换位置(虚部)
	part3_i.copyTo(part2_i);
	temp.copyTo(part3_i);


	//为了方便更改滤波器，这里的滤波实际上可以看成滤波器函数与频率域矩阵的乘积
	Mat blur_r, blur_i, BLUR;
	multiply(plane[0], blur, blur_r); //滤波（实部与滤波器模板对应元素相乘）
	multiply(plane[1], blur, blur_i);//滤波（虚部与滤波器模板对应元素相乘）
	Mat plane1[] = { blur_r, blur_i };
	merge(plane1, 2, BLUR);//实部与虚部合并

	//得到原图频谱图
	magnitudeW(plane[0], plane[1], plane[0]);//获取幅度图像，0通道为实部通道，1为虚部，因为二维傅立叶变换结果是复数
	plane[0] += Scalar::all(1);  //傅立叶变o换后的图片不好分析，进行对数处理，结果比较好看 
	log(plane[0], plane[0]);    // float型的灰度空间为[0，1])
	normalizeW(plane[0], plane[0], 1, 0);  //归一化便于显示
	imshow("origin", image);
	imshow("原图像频谱图", plane[0]);
	imwrite("outfreq.tif", plane[0]);
	waitKey(0);

	//IDFT操作，获得原图
	idft(BLUR, BLUR);	//idft结果也为复数
	split(BLUR, plane);//分离通道，主要获取通道
	magnitudeW(plane[0], plane[1], plane[0]);  //求幅值(模)
	normalizeW(plane[0], plane[0], 1, 0);  //归一化（线性）便于显示
	imshow("output", plane[0]);
	imwrite("out.tif", plane[0]);
	waitKey(0);
	
}

void detection(Mat &image) {
	int rows = image.rows;//获取行数
	int cols = image.cols;//获取列数
	int v = 0, s = 0, mark = 0, pointx = 0, pointy = 0, m = 0, n = 0, q = 0,pointx1 = 0, pointy1 = 0,pointx2 = 0, pointy2 = 0;
	for (int j = 1;j < cols-1;j++) {
		for (int i = 1;i < rows-1;i++) {
			v = image.at<uchar>(i, j);
			s = image.at<uchar>(i, j - 1);
			m = image.at<uchar>(i + 1, j);
			n = image.at<uchar>(i - 1, j);
			q = image.at<uchar>(i, j + 1);
			if (v == 0 && s == 255 && mark == 0) {
				pointx = i;pointy = j;
				cout << "长方形顶点坐标为" << "\n(" << pointx << "," << pointy << ")" << endl;
				mark++;
			}
			if (m == 255 && v == 0 && mark == 1) {
				pointx = i;pointy = j;
				cout << "(" << pointx << "," << pointy << ")" << endl;
				mark++;
			}
			if (q == 255 && v == 0 && mark == 2) {
				pointx = i;pointy = j;
				cout << "(" << pointx << "," << pointy << ")" << endl;
				mark++;
			}
			if (m == 255 && v == 0 && mark == 3) {
				pointx = i;pointy = j;
				cout << "(" << pointx << "," << pointy << ")" << endl;
				mark++;
			}
		}
	}
	int max = 0, r = 0;
	mark = 0;
	pointx = 0;pointx1 = 0;
	for (int j = 434;j < 870;j++) {
		for (int i = 1;i < rows - 1;i++) {
			v = image.at<uchar>(i, j);
			s = image.at<uchar>(i, j - 1);
			m = image.at<uchar>(i + 1, j);
			n = image.at<uchar>(i - 1, j);
			q = image.at<uchar>(i, j + 1);
			if (n == 255 && v == 0 ) {
				pointx1 = i;pointy1 = j;
			}

			if (m == 255 && v == 0 ) {
				pointx = i;pointy = j;
			}
		}
		r = pointx - pointx1;
		if (r > max) {
			pointx2 = (pointx + pointx1) / 2;
			pointy2 = j;
			max = r;
		}
		pointx = 0; pointx1 = 0;
	}
	cout << "圆的中心坐标为" << "\n(" << pointx2 << "," << pointy2 << ")" << endl;
	cout << "半径为" << max / 2 << endl;
	mark = 0;
	int min = 1000;
	max = 0;
	for (int j = 800;j < cols - 1;j++) {
		for (int i = 1;i < rows - 1;i++) {
			v = image.at<uchar>(i, j);
			s = image.at<uchar>(i, j - 1);
			m = image.at<uchar>(i + 1, j);
			n = image.at<uchar>(i - 1, j);
			q = image.at<uchar>(i, j + 1);
			if (v == 0 && s == 255&&mark==0) {
				pointx = i;pointy = j;
				cout << "三角形顶点坐标为" << "\n(" << pointx << "," << pointy << ")" << endl;
				mark++;
			}
			if (n == 255 && v == 0) {
				if (i < min) {
					min = i;
					pointy2 = j;
				}
			}
			if (q == 255 && v == 0) {
				if (j > max) {
					max = j;
					pointx1 = i;
				}
			}
		}
	}
    cout << "(" << min << "," << pointy2 << ")" << endl;
	cout << "(" << pointx1 << "," << max << ")" << endl;

}


int main(int argc, char** argv)
{
	/*cout << "请输入图像名称" << endl;
	string name;
	cin >> name;
	cout << "请输入通道数" << endl;
	int dims = 0;
	cin >> dims;
	int type = 0;
	Mat image1 = imread("666.bmp", 0);
	while (1) {
		cout << "请选择处理方式\n1.灰度线性变换\n2.高通低通滤波\n3.中值滤波\n4.图像二值化\n5.伪彩色增强\n6.色彩平衡\n7.几何变换\n8.频率域变换\n9.图形检测" << endl;
		cin >> type;
		switch (type) {
		case 1:
			grayLinearTransformation(name);
			break;
		case 2:
			filter(name, dims);
			break;
		case 3:
			medianFlitering(name, dims);
			break;
		case 4:
			binaryzation(name);
			break;
		case 5:
			pseudoColorEnhancement(name);
			break;
		case 6:
			equalizeCallback(name);
			break;
		case 7:
			geometricTransformation(name, dims);
			break;
		case 8:
			freqFilt(name);
			break;
		case 9:
			detection(image1);
			break;
		default:
			cout << "请重新输入" << endl;
			break;
		}
		waitKey(0);
	}*/
	freqFilt("222.jpg");
	
	return 0;
}