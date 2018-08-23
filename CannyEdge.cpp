#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

Mat src1, src, src_gray, src_rgb, dst1;
Mat dst, detected_edges;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
const string window_name("Edge Map");
const string window_name_real("Main Image");

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );
  //blur( src_gray, detected_edges);
  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  //dst = Scalar::all(0);
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  imshow( window_name, dst );
 }


/** @function main */
int main( int argc, char** argv )
{
  /// Load an image
  src = imread( argv[1] );

  if( !src.data )
  { return -1; }
  
  /// Create a matrix of the same type and size as src (for dst)
  //cvtColor(src1, dst, CV_BGR2GRAY);
  dst.create( src.size(), src.type() );
  cvtColor( src, src_gray, CV_BGR2GRAY );
  /// Convert the image to grayscale
  //cvtColor( src, src_gray, CV_BGR2GRAY );
  //cvtColor( src1, dst1, CV_BGR2GRAY );
  //cvtColor( src, src_rgb, CV_BGR2RGB );
  Mat image;
  src_rgb = imread(argv[1], CV_LOAD_IMAGE_COLOR); 
  namedWindow( window_name_real, CV_WINDOW_AUTOSIZE);
  imshow( window_name_real, src_rgb );
  /// Create a window
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;
  }
