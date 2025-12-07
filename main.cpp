#include <cstdint>
#include <opencv2/opencv.hpp> 
#include <fstream>
#include <iostream>
#include <sys/types.h>
using namespace std;

int main() {

  // cv::Mat image =cv::imread("/home/ujjwal/Downloads/images/shep.jpeg");
  //   if(image.empty()){
  //   cerr << "error couldnt open the image"<<endl;
  //
  // }

  string base64_output;
const char* base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
  const string filename="/home/ujjwal/Downloads/images/shep.jpeg";
 ifstream file_vec(filename,ios::in | ios::binary);
  if(file_vec.is_open()){
    file_vec.seekg(0, ios::end);
    streampos file_size = file_vec.tellg();
    file_vec.seekg(0, ios::beg);
    vector<unsigned char> image_data(file_size);
    file_vec.read((char*)image_data.data(), file_size);
    cout<<"file size"<< file_size<<endl;
    cout << "Image data read..."<<filename<<endl;
// for (unsigned char byte : image_data) {
//     cout << hex << setw(2) << setfill('0') << (int)byte << " ";
// }
//
for (size_t i = 0; i < image_data.size(); i += 3) {
    bool has_b2 = (i + 1 < image_data.size());
    bool has_b3 = (i + 2 < image_data.size());
    unsigned char b1 = image_data[i];
    unsigned char b2 = has_b2 ? image_data[i + 1] : 0;
    unsigned char b3 = has_b3 ? image_data[i + 2] : 0;

    uint32_t block = (b1 << 16) | (b2 << 8) | b3;
     uint8_t c1= (block>>18)& 0x3F;
     uint8_t c2= (block>>12)& 0x3F;
     uint8_t c3= (block>>6)& 0x3F;
     uint8_t c4= block& 0x3F;
      // cout << (int)c1 << " " << (int)c2 << " " << (int)c3 << " " << (int)c4 << endl;

  base64_output += base64_chars[c1];
    base64_output += base64_chars[c2];
   if (has_b2)
        base64_output += base64_chars[c3];
    else
        base64_output += '=';

    if (has_b3)
        base64_output += base64_chars[c4];
    else
        base64_output += '=';
}
    file_vec.close();
  }else {
  cout<<"failed to open the file"<<filename<<endl;
  }
  ofstream outputfile;

    outputfile.open("output.txt");
  outputfile << base64_output<<endl;
  outputfile.close();
  // cout<<base64_output<<endl;


  // cv::imshow("image",image);
  // for (int i=0 ;i<image.rows; ++i) {
  //   for(int j=0;j<image.cols;++j){
  //     u_char pixel_values=image.at<u_char>(i,j);
  //   }
  //
  // }
  // cv::Mat binary_image;
  //   double threshold_value = 100; 
  //   double max_value = 255;      
  //   cv::threshold(image, binary_image, threshold_value, max_value, cv::THRESH_BINARY);
  // cv::imshow("binary_image",binary_image);
  // cv::waitKey(0);
  // cv::destroyAllWindows();
}
