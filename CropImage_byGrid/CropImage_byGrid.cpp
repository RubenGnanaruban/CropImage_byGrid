/*
* Authour: Vimalatharmaiyah Gnanaruban
* September 2022
*/

#include <string>
#include <iostream>
#include<opencv2/opencv.hpp>
//#include <fstream>
//#include <cstdlib>
#include <filesystem>
#include <opencv2/core/utility.hpp>
#include <vector>

namespace fs = std::filesystem;
using namespace std;
using namespace cv;

string getFileName(const string& s) {
    char sep = '/';
#ifdef _WIN32
    sep = '\\';
#endif
    size_t i = s.rfind(sep, s.length());
    if (i != string::npos)
    {
        string filename = s.substr(i + 1, s.length() - i);
        size_t lastindex = filename.find_last_of(".");
        string rawname = filename.substr(0, lastindex);
        return(rawname);
    }
    return("");
}

int main()
{
    int imgheight, imgwidth, M, N;
    int N_x = 4;
    int N_y = 4;

    //fs::create_directories("saved_patches");
    //String dirname = "images_to_crop"; //".\\images_to_crop";
    String dirname = "C:\\Users\\Histo\\Documents\\ProstateTissue_for_CycleGAN\\191\\191";
    //String dirname = "C:\\Users\\Histolix3\\source\\repos\\CropImage_byGrid\\CropImage_byGrid\\images_to_crop"; //".\\images_to_crop";
    string dir_raw = dirname;
    /*size_t ii = dir_raw.rfind('\\', dir_raw.length());
    string dir_patch = dir_raw.substr(0, ii);
    dir_patch += "\\saved_patches";*/
    string dir_patch = dir_raw + "_saved_patches";
    fs::create_directories(dir_patch);
    //fs::create_directories("saved_patche");

    vector<cv::String> fn;
    glob(dirname, fn, false);
    Mat img = imread(fn[0]);
    imgheight = img.rows;
    imgwidth = img.cols;
    M = imgheight / N_y;
    N = imgwidth / N_x;
    size_t count = fn.size(); //number of jpg files in images_to_crop folder
    for (size_t i = 0; i < count; i++) {
        Mat img = imread(fn[i]);
        int x1 = 0;
        int y1 = 0;
        for (int i_y = 0; i_y < N_y; i_y++){
            int y = i_y * M;
            for (int i_x = 0; i_x < N_x; i_x++){
                int x = i_x * N;
                string a = to_string(i_x);
                string b = to_string(i_y);
                // special case where the original image is eqully divisible:
                Mat tiles = img(Range(y, y + M), Range(x, x + N));
                //save each patches into file directory
                imwrite(dir_patch + "\\" + getFileName(fn[i]) + "_Y" + b + "_X" + a + ".jpg", tiles);
                //imwrite("saved_patches/" + getFileName(fn[i]) + "_Y" + b + "_X" + a + ".jpg", tiles);
                auto xs = fn[i];
            }
        }
    }

    /*N_x = 4;
    N_y = 4;
    M = imgheight / N_y;
    N = imgwidth / N_x;
    string path = ".\\images_to_crop";
    for (const auto& entry : fs::directory_iterator(path)) {
        //std::cout << entry.path() << std::endl;
        Mat img = imread(entry.path());
        Mat image_copy = img.clone();
        int imgheight = img.rows;
        int imgwidth = img.cols;
    }*/
    /*
    int x1 = 0;
    int y1 = 0;
    for (int i_y = 0; i_y < N_y; i_y++)
    {
        int y = i_y * M; 
        for (int i_x = 0; i_x < N_x; i_x++)
        {
            int x = i_x * N;
            if ((imgheight - y) < M || (imgwidth - x) < N)
            {
                break;
            }
            y1 = y + M;
            x1 = x + N;
            string a = to_string(i_x);
            string b = to_string(i_y);
            // special case where the original image is eqully divisible:
            Mat tiles = image_copy(Range(y, y + M), Range(x, x + N));
            //save each patches into file directory
            imwrite("saved_patches/tileY" + b + "_X" + a + ".jpg", tiles);
            
            if (x1 > imgwidth && y1 > imgheight)
            {
                x = imgwidth - 1;
                y = imgheight - 1;
                x1 = imgwidth - 1;
                y1 = imgheight - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, imgheight), Range(x, imgwidth));
                //save each patches into file directory
                imwrite("saved_patches/tileY" + b + "_X" + a + ".jpg", tiles);
                //rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else if (y1 > imgheight)
            {
                y = imgheight - 1;
                y1 = imgheight - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, imgheight), Range(x, x + N));
                //save each patches into file directory
                imwrite("saved_patches/tileY" + b + "_X" + a + ".jpg", tiles);
                //rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else if (x1 > imgwidth)
            {
                x = imgwidth - 1;
                x1 = imgwidth - 1;

                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, y + M), Range(x, imgwidth));
                //save each patches into file directory
                imwrite("saved_patches/tileY" + b + "_X" + a + ".jpg", tiles);
                //rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
            else
            {
                // crop the patches of size MxN
                Mat tiles = image_copy(Range(y, y + M), Range(x, x + N));
                //save each patches into file directory
                imwrite("saved_patches/tileY" + b + "_X" + a + ".jpg", tiles);
                //rectangle(img, Point(x, y), Point(x1, y1), Scalar(0, 255, 0), 1);
            }
        }
    }*/
}

