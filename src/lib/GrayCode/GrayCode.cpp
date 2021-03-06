#include "GrayCode.hpp"
namespace SLS{
GrayCode::GrayCode(size_t projW, size_t projH):
    width_(projW), height_(projH),currImg(0)
{
    // Calculate number of bits for each dimension
    numColBits = (size_t)std::ceil(std::log2((float) width_));
    numRowBits = (size_t)std::ceil(std::log2((float) height_));
    grayCodes_.resize(numColBits*2+numRowBits*2+2);
}
const std::vector<cv::Mat>& GrayCode::generateGrayCode()
{
    // Init rest of the mat
    for (auto &mat: grayCodes_)
        mat = cv::Mat(height_, width_, CV_8UC1, cv::Scalar(0));
    // Set first frame to white
    grayCodes_[0] = cv::Mat(height_, width_, CV_8UC1, cv::Scalar(255));
    uchar flag = 0;

    // Generate patterns to encode x pixels.
    // For each column
	for (size_t j=0; j<width_; j++)	
	{
		int rem=0, num=j, prevRem=j%2;

        // For each bit in the column
		for (size_t k=0; k<numColBits; k++)	
		{
			num=num/2;
			rem=num%2;
			if ((rem==0 && prevRem==1) || (rem==1 && prevRem==0)) { 
				flag=1;
			}
			else {
				flag= 0;
			}
			for (size_t i=0;i<height_;i++)	
			{
                uchar pixel_color = flag*255;
                grayCodes_[2*numColBits-2*k].at<uchar>(i, j) = pixel_color;
                pixel_color = pixel_color==0?255:0;
                grayCodes_[2*numColBits-2*k+1].at<uchar>(i,j) = pixel_color;

			}
			prevRem=rem;
		} 
		
	}
    
    // Generate patterns to encode y pixels
    // For each row
	for (size_t i=0;i<height_;i++)	
	{
		int rem=0, num=i, prevRem=i%2;
        // For each bit in the row
		for (size_t k=0; k<numRowBits; k++)	
		{

			num=num/2;
			rem=num%2;
			if ((rem==0 && prevRem==1) || (rem==1 && prevRem==0)) { 
				flag=1;
			}
			else {
				flag= 0;
			}

			for (size_t j=0; j<width_; j++)	
			{
                uchar pixel_color = flag*255;
                grayCodes_[2*numRowBits-2*k+2*numColBits].at<uchar>(i,j) = pixel_color;
                pixel_color = pixel_color==0?255:0;
                grayCodes_[2*numRowBits-2*k+2*numColBits+1].at<uchar>(i,j) = pixel_color;
			}

			prevRem=rem;
		} 
	}
    return grayCodes_;
}
} // namespace SLS
