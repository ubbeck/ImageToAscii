# Image to ASCII converter
Convert images into ASCII art using command-line.  

## Dependencies
[OpenCV](https://opencv.org/) (>= 4.5)

## Build

With **MinGW** compiler version 12.2.0  
Modify the OpenCV path
```bash
g++ -o main main.cpp -IC:\OpenCV\opencv\build\include -LC:\OpenCV\opencv\build\lib -llibopencv_core450 -llibopencv_highgui450 -llibopencv_imgcodecs450 -llibopencv_imgproc450
```

## Usage and examples
Just add the image path and output file name when you run the program in the command console
```bash
main.exe img/blade_runner.jpg blade_runner_ascii
```

| RAW | ASCII |
| :---: | :---: |
| <img src="img\blade_runner.jpg" width="150"> | <img src="img\blade_runner_ascii.png" width="750"> |
| <img src="img\porsche.jpg" width="150"> | <img src="img\porscheAscii.png" width="750"> |
| <img src="img\hands.jpg" width="150"> | <img src="img\handsAscii.png" width="350"> |
| <img src="img\street.jpg" width="150"> | <img src="img\streetAscii.png" width="350"> |

Increases `SCALE_FACTOR` to generate larger and more detailed images. Check img examples.

## Goals
* Add command line arguments to modify scale, colour, brightness, etc.
* Video support