#include "../headers/project.h"

/* Calculate mean */

uint32_t mean(cv::Mat image){
	/* Compute mean*/
	uint32_t unnormalized_mean = 0;
	for(int r = 0; r < image.rows; r++) {
		for(int c = 0; c < image.cols; c++){
			unnormalized_mean += image.at<uint8_t>(r,c);
		}
	}
	uint32_t mean = unnormalized_mean / (image.rows*image.cols);
	std::cout << "Unormalized mean: " << unnormalized_mean << std:: endl;
	std::cout << "mean: " << mean << std:: endl;
	return mean;
}
/* Split images into sub images  */
std::vector < cv::Mat > split(cv::Mat image,int n) {
	int num_blocks = 0;
	std::cout<<"The length of the image is "  << image.rows << std::endl;
	std::cout<<"The width of the image is " << image.cols << std::endl;
	cv::Size smallSize(image.rows/n,image.cols/n);
	std::vector<cv::Mat> smallImages;
	std::cout<<"The length of a block is " << image.rows/n << std::endl;
	std::cout<<"The width of a block is " << image.cols/n << std::endl;
	for (uint32_t r = 0; r < smallSize.height*n; r += smallSize.height){
		for (uint32_t c = 0; c < smallSize.width*n; c += smallSize.width){
			cv::Rect rect = cv:: Rect(r,c,smallSize.height, smallSize.width);
			std::cout<<"r is "<< r << std::endl;
			std::cout<<"c is "<< c << std::endl;
			std::cout<<"Creating block "<< ++num_blocks << std::endl;
			smallImages.push_back(cv::Mat(image, rect));
			cv::namedWindow("Display window", cv::WINDOW_AUTOSIZE);
    		cv::imshow( "Display window", cv::Mat(image,rect));
    		cv::waitKey(0);
		}
	}
	return smallImages;  
}
/* Median Filter */
cv::Mat filter(cv::Mat img) {
	/* 3x3 kernel */
	uint8_t kernel[][3]  = { 1,  1,  1, 
                             1,  0,  1, 
                             1,  1,  1 ,};
    uint32_t arr[8];
    uint32_t arr_corner[3];
    uint32_t arr_semiBounded[5];
    int choice[3] = {0,0,0};
    /* Bounds - do not exceed bounds */
    int r_start = 0;
    int r_end = img.rows - 1;
    int c_start = 0;
    int c_end = img.cols- 1;
    std::cout << "Begining to apply filter" << std::endl;
    for(uint32_t r = 0; r < img.rows;r++) {
    	for(uint32_t c = 0; c < img.cols; c++) {
    	uint32_t window = 0;
    	/* If we are at the top left corner */
    	if(r == 0 && c == 0) {
    			std::cout << "We are at a corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    			img.at<uint8_t>(r+1,c)*kernel[2][1] +\
    			img.at<uint8_t>(r,c+1)*kernel[1][2] +\
    			img.at<uint8_t>(r+1,c+1)*kernel[2][2];
    			/* Set arr values */
    			arr_corner[0] = img.at<uint8_t>(r+1,c);
    			arr_corner[1] = img.at<uint8_t>(r,c+1);
    			arr_corner[2] = img.at<uint8_t>(r+1,c+1);
    			choice[0] = 1;
    	}
    	/* If we are at the bottom left corner */
    	else if(r == r_end && c == 0) {
    			std::cout << "We are at a corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    				img.at<uint8_t>(r-1,c)*kernel[0][1] +\
    				img.at<uint8_t>(r-1,c+1)*kernel[0][2] +\
    				img.at<uint8_t>(r,c+1)*kernel[1][2];
    				/* Set arr values */
    				arr_corner[0] = img.at<uint8_t>(r-1,c);
    				arr_corner[1] = img.at<uint8_t>(r-1,c+1);
    				arr_corner[2] = img.at<uint8_t>(r,c+1);
    				choice[0] = 1;
    	}
    	/* If we are at the top right corner */
    	else if(r == 0 && c == c_end){
    			std::cout << "We are at a corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    					img.at<uint8_t>(r,c-1)*kernel[1][0] +\
    					img.at<uint8_t>(r+1,c-1)*kernel[2][0] +\
    					img.at<uint8_t>(r+1,c)*kernel[2][1];
    					/* Set arr values */
    					arr_corner[0] = img.at<uint8_t>(r,c-1);
    					arr_corner[1] = img.at<uint8_t>(r+1,c-1);
    					arr_corner[2] = img.at<uint8_t>(r+1,c);
    					choice[0] = 1;
    	}
    	/* If we are at the bottom right corner */
    	else if(r == r_end && c == c_end){
    			std::cout << "We are at a corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    					img.at<uint8_t>(r-1,c-1)*kernel[0][0] +\
    					img.at<uint8_t>(r,c-1)*kernel[1][0] +\
    					img.at<uint8_t>(r-1,c)*kernel[0][1];
    					/* Set arr values */
    					arr_corner[0] = img.at<uint8_t>(r-1,c-1);
    					arr_corner[1] = img.at<uint8_t>(r,c-1);
    					arr_corner[2] = img.at<uint8_t>(r-1,c);
    					choice[0] = 1;
    	}
    	/* If r = 0 but we are not at a corner */
    	else if (r == 0 && (c !=  0 && c != c_end)) {
    			std::cout << "We are at the boundary but not the corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    				img.at<uint8_t>(r,c-1)*kernel[1][0] +\ 
    				img.at<uint8_t>(r+1,c-1)*kernel[2][0] +\
    				img.at<uint8_t>(r+1,c)*kernel[2][1] +\
    				img.at<uint8_t>(r,c+1)*kernel[1][2] +\
    				img.at<uint8_t>(r+1,c+1)*kernel[2][2];
    				/* Set arr values */
    				arr_semiBounded[0] = img.at<uint8_t>(r,c-1);
    				arr_semiBounded[1] = img.at<uint8_t>(r+1,c-1);
    				arr_semiBounded[2] = img.at<uint8_t>(r+1,c);
    				arr_semiBounded[3] = img.at<uint8_t>(r,c+1);
    				arr_semiBounded[4] = img.at<uint8_t>(r+1,c+1);
    				choice[1] = 1;  
    	}
    	/* if r = r_end but we are not at a corner */
    	else if(r == r_end && (c != 0 && c != c_end)) {
    			std::cout << "We are at the boundary but not the corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    					img.at<uint8_t>(r-1,c-1)*kernel[0][0] +\
    					img.at<uint8_t>(r,c-1)*kernel[1][0] +\
    					img.at<uint8_t>(r-1,c)*kernel[0][0] +\
    					img.at<uint8_t>(r-1,c+1)*kernel[0][2] +\
    					img.at<uint8_t>(r,c+1)*kernel[1][2];
    					/* Set arr values */
    					arr_semiBounded[0] = img.at<uint8_t>(r-1,c-1);
    					arr_semiBounded[1] = img.at<uint8_t>(r,c-1);
    					arr_semiBounded[2] = img.at<uint8_t>(r-1,c);
    					arr_semiBounded[3] = img.at<uint8_t>(r-1,c+1);
    					arr_semiBounded[4] = img.at<uint8_t>(r,c+1);
    					choice[1] = 1;
    	}
    	/* if c = 0 but we are not at a corner */
    	else if(c == 0 && (r != 0 && r != r_end)) {
    			std::cout << "We are at the boundary but not the corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    			 img.at<uint8_t>(r-1,c)*kernel[0][1] +\
    			 img.at<uint8_t>(r+1,c)*kernel[2][1] +\
    			 img.at<uint8_t>(r-1,c+1)*kernel[0][2] +\
    			 img.at<uint8_t>(r,c+1)*kernel[1][2] +\
    			 img.at<uint8_t>(r+1,c+1)*kernel[2][2];
    			 /* Set arr values */
    			 arr_semiBounded[0] = img.at<uint8_t>(r-1,c);
    			 arr_semiBounded[1] = img.at<uint8_t>(r+1,c);
    			 arr_semiBounded[2] = img.at<uint8_t>(r-1,c+1);
    			 arr_semiBounded[3] = img.at<uint8_t>(r,c+1);
    			 arr_semiBounded[4] = img.at<uint8_t>(r+1,c+1);
    			 choice[1] = 1;
    	}
    	/* if c == c_end but we are not at a corner */
    	else if(c == c_end && (r != 0 && r != r_end)) {
    			std::cout << "We are at the boundary but not the corner" << std::endl;
    			std::cout << r << "," << c << std::endl;
    			window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    			img.at<uint8_t>(r-1,c-1)*kernel[0][0] +\
    			img.at<uint8_t>(r,c-1)*kernel[1][0] +\
    			img.at<uint8_t>(r+1,c-1)*kernel[2][0] +\
    			img.at<uint8_t>(r-1,c)*kernel[0][1] +\
    			img.at<uint8_t>(r+1,c)*kernel[2][1];
    			/* Set arr values */
    			arr_semiBounded[0] = img.at<uint8_t>(r-1,c-1);
    			arr_semiBounded[1] = img.at<uint8_t>(r,c-1);
    			arr_semiBounded[2] = img.at<uint8_t>(r+1,c-1);
    			arr_semiBounded[3] = img.at<uint8_t>(r-1,c);
    			arr_semiBounded[4] = img.at<uint8_t>(r+1,c);
    			choice[1] = 1;
    	}
    	else {
    	window = img.at<uint8_t>(r,c)*kernel[1][1] +\
    					 img.at<uint8_t>(r-1,c-1)*kernel[0][0] +\
    					 img.at<uint8_t>(r,c-1)*kernel[1][0] +\
    					 img.at<uint8_t>(r+1,c-1)*kernel[2][0] +\
    					 img.at<uint8_t>(r-1,c)*kernel[0][1] +\
    					 img.at<uint8_t>(r+1,c)*kernel[2][1] +\
    					 img.at<uint8_t>(r-1,c+1)*kernel[0][2] +\
    					 img.at<uint8_t>(r,c+1)*kernel[1][2] +\
    					 img.at<uint8_t>(r+1,c+1)*kernel[2][2];
    		
    		/* Set arr values */
    		arr[0] = img.at<uint8_t>(r-1,c-1);
    		arr[1] = img.at<uint8_t>(r,c-1);
    		arr[2] = img.at<uint8_t>(r+1,c-1);
    		arr[3] = img.at<uint8_t>(r-1,c); 
    		arr[4] = img.at<uint8_t>(r+1,c);
    		arr[5] = img.at<uint8_t>(r-1,c+1); 
    		arr[6] = img.at<uint8_t>(r,c+1);
    		arr[7] = img.at<uint8_t>(r+1,c+1);
    		choice[2] = 1;
    	}
    	if(choice[0]) { 
    		std::sort(arr_corner,arr_corner + 3);
    		if(img.at<uint8_t>(r,c) > window) {
    			int median = arr_corner[1];
    			img.at<uint8_t>(r,c) = median;
    		}
    	}
    	else if(choice[1]) {
    		std::sort(arr_semiBounded,arr_semiBounded + 5);
    		if(img.at<uint8_t>(r,c) > window) {
    			int median = arr_semiBounded[2];
    			img.at<uint8_t>(r,c) = median;
    		}
    	}
    	else {
    		std::sort(arr,arr + 8);
    		if(img.at<uint8_t>(r,c) > window) {
    			int median = (arr[4] + arr[3])/2;
    			img.at<uint8_t>(r,c) = median;
    		}	
    	}
    }
}
    return img;
}

cv::Mat merge(std::vector<cv::Mat> vec,cv::Mat image) {
	/* Perform matrix merge */
	int image_num = 0;
	cv::Mat m = vec[image_num];
    if((image.cols == 206) && (image.rows == 213)) {
    cv::Mat imgPanel(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
    for(int c = 0; c < image.cols - 2; c += m.cols) {
        for(int r = 0; r < image.rows - 5; r += m.rows -1) {
            vec[image_num++].copyTo(imgPanel(cv:: Rect(c,r,m.cols, m.rows)));
            std::cout << "Image is 213 x 206" << std::endl;
            std::cout << "Merging image " << image_num << std::endl;
            std::cout << image.rows << std::endl;
            std::cout << image.cols << std::endl;
            std::cout << r << std::endl;
            std::cout << c << std::endl;
            imshow("imgPanel", imgPanel);
            cv::waitKey(0);
        }
    }
    return imgPanel;
    }
    else if ((image.cols == 208) && (image.rows == 194)) {
	cv::Mat imgPanel(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
	for(int c = 0; c < image.cols ; c += m.cols) {
		for(int r = 0; r < image.rows - 2 ; r += m.rows) {
            vec[image_num++].copyTo(imgPanel(cv:: Rect(c,r,m.cols, m.rows)));
            std::cout << "Image is 194 x 208" << std::endl;
			std::cout << "Merging image " << image_num << std::endl;
			std::cout << image.rows << std::endl;
            std::cout << image.cols << std::endl;
            std::cout << r << std::endl;
            std::cout << c << std::endl;
            imshow("imgPanel", imgPanel);	
            cv::waitKey(0);
        
		}
	}
	return imgPanel;
    }
    else{
     cv::Mat imgPanel(image.rows, image.cols, CV_8UC1, cv::Scalar(0));
     for(int c = 0; c < image.cols - 2; c += m.cols) {
        for(int r = 0; r < image.rows -3; r += m.rows) {
            vec[image_num++].copyTo(imgPanel(cv:: Rect(c,r,m.cols, m.rows)));
            std::cout << "Matrix is 299 x 362" << std::endl;
            std::cout << "Merging image " << image_num << std::endl;
            std::cout << image.rows << std::endl;
            std::cout << image.cols << std::endl;
            std::cout << r << std::endl;
            std::cout << c << std::endl;
            imshow("imgPanel", imgPanel);
            cv::waitKey(0);
        }
    }
    return imgPanel;   
    }
   
}

Mat myEntropy(Mat seq, int histSize)
{ 

  float range[] = { 0, 256 } ;
  const float* histRange = { range };

  bool uniform = true; bool accumulate = false;

  Mat hist;

  /// Compute the histograms:
  calcHist( &seq, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate );

  return hist;
}

float entropy(Mat seq, Size size, int index)
{
  int cnt = 0;
  float entr = 0;
  float total_size = size.height * size.width; //total size of all symbols in an image

  for(int i=0;i<index;i++)
  {
    float sym_occur = seq.at<float>(0, i); //the number of times a sybmol has occured
    if(sym_occur>0) //log of zero goes to infinity
      {
        cnt++;
        entr += (sym_occur/total_size)*(log2(total_size/sym_occur));
      }
  }
  return entr;

}





    
                               





