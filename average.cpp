#include <iostream>
#include <vector>
#include <cmath>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

Mat& Average(Mat& I, int th);


int main( int argc, char* argv[]) {

  // if (argc < 5) {
      
  //   cout << "Not enough parameters" << endl;
  //   return -1;

  // }

  Mat I, O;

  I = imread("output.tif", IMREAD_GRAYSCALE);
  int th = stoi(argv[1]);




  if (!I.data) {
    cout << "The image" << argv[1] << " could not be loaded." << endl;
    return -1;
  }


  O = Average(I, th);

  imwrite("averageout.tif", O);

 
  return 0;
}


Mat& Average(Mat& I, int th) {

  // accept only char type matrices
  CV_Assert(I.depth() == CV_8U);

  int channels = I.channels();

  int nRows = I.rows;
  int nCols = I.cols;

  int cost = 0;


  long i,j;
  // uchar* p;
  long n,m;

  cout << nRows << "\n";
  int searchRadius = 10;

  for( i = 0; i < nRows; ++i) {
    for ( j = 0; j < nCols; ++j) {
      

      int byte = (int)I.at<uchar>(i,j);

      if(byte == 255) {

        int count = 0;

        for( n = -searchRadius; n < searchRadius; n++) {
          for( m = -searchRadius; m < searchRadius; m++) {

            if(i+n > 0 && i+n < nRows && j+m > 0 && j+m < nCols-1000) {
              
              byte = (int)I.at<uchar>(i+n,j+m);            
              if(byte == 255) count++;
            }
          }
        }

        if(count < th) {
          I.at<uchar>(i,j) = 0;
        }

      }

      
    }
  }
  
  return I;
}