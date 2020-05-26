#include "../headers/project.h"

int main( int argc, char* argv[] ) {

  cv::Mat image;
  cv::Scalar mean;
  cv::Scalar standard_deviation;
  int hist = 256;
  image = cv::imread(argv[1] , CV_LOAD_IMAGE_GRAYSCALE);
  std::cout << "Computing entropy " << entropy(myEntropy(image,hist),(image).size(),hist) << std::endl;
  if(! image.data ) {
      std::cout <<  "Could not open or find the image" << std::endl ;
      return -1;
    }
  /* Prior information - for the full image */ 
  meanStdDev(image,mean,standard_deviation);
  std::cout << "mean is: " << mean[0] << std::endl;
  std::cout << "standard_deviation is: " << standard_deviation[0] << std::endl;
  std::cout << "Collecting image blocks -" << std::endl;
  std::vector < cv::Mat > vec = split(image,4);
  /* Determing means and standard deviations for the subimages */
  std::vector <cv::Scalar> mean_vec;
  std::vector <cv::Scalar> std_vec;
  int num = 0;
  std::vector <cv::Mat> adjusted_vec;
  int image_partition = 0;
  for(std::vector<cv::Mat>::iterator it = vec.begin(); it != vec.end(); it++) {
       std::cout << "Computing mean and standard standard_deviation over " \
                << ++num << " element" << std::endl;
        cv::Scalar mean_temp;
        cv::Scalar standard_deviation_temp;
        meanStdDev(*it,mean_temp,standard_deviation_temp);
        std::cout << "Computed mean is" \
                << mean_temp << std::endl;
        std::cout << "Computed standard deviation is" \
                << standard_deviation_temp << std::endl;
        if(standard_deviation_temp.val[0] > 30) {
          std::cout << "Standard deviation is greater than 30" \
                    << std::endl;
          cv::Mat filtered_img = filter(*it);
        //  std::cout << "Computing entropy " << entropy(myEntropy(*it,hist),(*it).size(),hist) << std::endl;
          adjusted_vec.push_back(filtered_img);
          std::ostringstream s_num;
          s_num << "/home/ekram/4422/EECS4422/sources/Images/IMG_" << ++image_partition << ".pgm";
          cv::imwrite(s_num.str(),filtered_img);
        } 
        else
        {
          adjusted_vec.push_back(*it);
       //   std::cout << "Computing entropy " << entropy(myEntropy(*it,hist),(*it).size(),hist) << std::endl;
          std::ostringstream s_num;
          s_num << "/home/ekram/4422/EECS4422/sources/Images/IMG_" << ++image_partition << ".pgm";
          cv::imwrite(s_num.str(),*it);
        }
        mean_vec.push_back(mean_temp);
        std_vec.push_back(standard_deviation_temp);
  }
  cv::Mat im = merge(adjusted_vec,image);

  return 0;
}
