#include "../headers/project.h"

int main( int argc, char* argv[] ) {
	std::vector <cv::Mat> vec;
	int hist = 256;
	cv::Mat im_o = cv::imread(argv[1] , CV_LOAD_IMAGE_GRAYSCALE);
	printf("Beginning Loop.\n");
	for(int j = 0; j < 16;) {
		std::ostringstream s_num;
        s_num << "./Denoised_Images/Denoised_Im_" << ++j << ".pgm"; 
		printf("Creating Image %d.\n",j);
	    cv::Mat image = cv::imread(s_num.str(),CV_LOAD_IMAGE_GRAYSCALE);
	    printf("Number of rows is %d\n",image.rows);
	    printf("Number of cols is %d\n",image.cols);
	    if(!image.empty()) {
	    	cv::imshow("Denoised Image",image);
	    	cv::waitKey(0);
	    }
	   // std::cout << "Computing entropy " << entropy(myEntropy(image,hist),(image).size(),hist) << std::endl;
		vec.push_back(image);
		printf("Size of vec is %d.\n",vec.size());
	}
	printf("Completed Loop.\n");
	cv::Mat im = merge(vec,im_o);
	std::cout << "Computing entropy " << entropy(myEntropy(im,hist),im.size(),hist) << std::endl;
	printf("Completed Merge.\n");
	printf("Number of rows is %d\n",im.rows);
	printf("Number of cols is %d\n",im.cols);
	cv::imshow("Full Denoised Image",im);
	cv::waitKey(0);
	cv::imwrite("./BM3D_Image/out.pgm",im);

	return 0;
}
