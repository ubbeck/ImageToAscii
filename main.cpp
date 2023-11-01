#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <iostream>

const float SCALE_FACTOR = 0.2;
const int CHAR_WIDTH = 10;
const int CHAR_HEIGHT = 18;

struct tUser{
    std::string inputFileName;
    std::string outputFileName;
    cv::Mat inputImage;
    cv::Mat outputImage;
};

bool loadUser(int argc, char* argv[], tUser &user);
void imgToAscii(tUser &user);

int main(int argc, char* argv[]){

    if(argc != 3){
        std::cout << "Incorrect number of arguments\n";
        return 1;
    }

    tUser user;

    if(!loadUser(argc, argv, user)){
        std::cout << "Could not read image: " << user.inputFileName << "\n";
        return 1; 
    }

    imgToAscii(user);

    cv::imwrite(user.outputFileName, user.outputImage);

    std::cout << "ASCII art saved to " << user.outputFileName << "\n";

    return 0;
}

bool loadUser(int argc, char* argv[], tUser &user){
    user.inputFileName = argv[1];
    user.outputFileName = std::string(argv[2]) + ".png";
    user.inputImage = cv::imread(user.inputFileName, cv::IMREAD_COLOR);

    return !(user.inputImage.empty());
}

void imgToAscii(tUser &user){
    cv::resize(user.inputImage, user.inputImage, cv::Size(static_cast<int>(SCALE_FACTOR * user.inputImage.cols), static_cast<int>(SCALE_FACTOR * user.inputImage.rows * (static_cast<float>(CHAR_WIDTH) / CHAR_HEIGHT))));
    user.outputImage = cv::Mat(CHAR_HEIGHT * user.inputImage.rows, CHAR_WIDTH * user.inputImage.cols, user.inputImage.type());

    for (int i = 0; i < user.inputImage.rows; i++) {
        for (int j = 0; j < user.inputImage.cols; j++) {
            cv::Vec3b pixel = user.inputImage.at<cv::Vec3b>(i, j);

            int h = (pixel[0] + pixel[1] + pixel[2]) / 3;
            uchar asciiChar = h * 1.0 / 256 * 16;
            std::string asciiText(1, " .,:;i1tfLCG08$@"[asciiChar]);

            user.outputImage(cv::Rect(j * CHAR_WIDTH, i * CHAR_HEIGHT, CHAR_WIDTH, CHAR_HEIGHT)) = cv::Scalar(25, 25, 25);
            cv::putText(user.outputImage, asciiText, cv::Point(j * CHAR_WIDTH, i * CHAR_HEIGHT + CHAR_HEIGHT), cv::FONT_HERSHEY_SIMPLEX, 0.6, cv::Scalar(pixel[0], pixel[1], pixel[2]), 1);
        }
    }
}