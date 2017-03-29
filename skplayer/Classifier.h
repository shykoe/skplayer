#pragma once
#define GLOG_NO_ABBREVIATED_SEVERITIES
#include <caffe/common.hpp>  
#include <caffe/layer.hpp>  
#include <caffe/layer_factory.hpp>  
#include <caffe/layers/input_layer.hpp>  
#include <caffe/layers/inner_product_layer.hpp>  
#include <caffe/layers/dropout_layer.hpp>  
#include <caffe/layers/conv_layer.hpp>  
#include <caffe/layers/relu_layer.hpp>  

#include <caffe/layers/pooling_layer.hpp>  
#include <caffe/layers/lrn_layer.hpp>  
#include <caffe/layers/softmax_layer.hpp>   
#include <caffe/caffe.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>
#include <iosfwd>
#include <memory>
#include <string>
#include <utility>
#include <vector>
namespace caffe
{

	extern INSTANTIATE_CLASS(InputLayer);
	extern INSTANTIATE_CLASS(InnerProductLayer);
	extern INSTANTIATE_CLASS(DropoutLayer);
	extern INSTANTIATE_CLASS(ConvolutionLayer);
	//REGISTER_LAYER_CLASS(Convolution);
	extern INSTANTIATE_CLASS(ReLULayer);
	//REGISTER_LAYER_CLASS(ReLU);
	extern INSTANTIATE_CLASS(PoolingLayer);
	//REGISTER_LAYER_CLASS(Pooling);
	extern INSTANTIATE_CLASS(LRNLayer);
	//REGISTER_LAYER_CLASS(LRN);
	extern INSTANTIATE_CLASS(SoftmaxLayer);
	//REGISTER_LAYER_CLASS(Softmax);

	class Classifier {
	public:
		Classifier(const string& model_file,
			const string& trained_file,
			const string& mean_file);

		std::vector<float> Classify(const cv::Mat& img, int N = 5);

	private:
		void SetMean(const string& mean_file);

		std::vector<float> Predict(const cv::Mat& img);

		void WrapInputLayer(std::vector<cv::Mat>* input_channels);

		void Preprocess(const cv::Mat& img,
			std::vector<cv::Mat>* input_channels);

	private:
		shared_ptr<Net<float> > net_;
		cv::Size input_geometry_;
		int num_channels_;
		cv::Mat mean_;
		std::vector<string> labels_;
	};
}

