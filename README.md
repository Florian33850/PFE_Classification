# PFE_Classification

## Table of Contents

1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Collaboration](#collaboration)

## General Info

This project is part of our Master 2 Computer Science final year project at the university of Bordeaux. It is a generic classification application allowing to perform pre-processing on a loaded database, data augmentation, launch classification model training and classify an image with a loaded pre-trained model.

## Technologies

[OpenCV](https://gist.github.com/umardx/dfce1dc74d925629a9eb8ad409740b47) : Version 3.2.0
Debian GNU/Linux 10 (buster)
[QT](https://www.qt.io/download) : Version 5.0

## Installation

Retrieve the repository :
$ git clone git@github.com:Florian33850/PFE_Classification.git

CMake is used to build the project.
Create a build directory :
```
$ mkdir build
$ cd build
```
```
$ cmake ..
$ make
```
To obtain the project's code coverage execute the following command:

```
$ make && make gcov && make lcov && firefox lcoverage/index.html
```

Launch the application :
```
$ ./application_viewer
```
## Usage

First tab : 
- Possibility to load one or more images with File > ImageSelection or a database as a folder with File > LymeDatabase
- Addition of pre-processing which is carried out on the original images.
- Save all images with active pre-processing.

Second tab:
- Possibility to load images as before (if not already done in the previous tab).
- Addition of one or more data increases. Each data augmentation preview is done separately from each other.
- Currently saving the images is only done on the last data augmentation previewed.

Third tab:
- Possibility to choose a classification method between deep learning and random forest.
- Then you have to choose a python file (where it should be specified, according to the the following convention how the arguments needed in the application are passed): 
       - DeepLearning: arg[1] = width of images, arg[2] = height of images, arg[3] = training set, arg[4] = testing set, arg[5] = number of epochs
       - RandomForest : arg[1] = width of images, arg[2] = height of images, arg[3] = training set, arg[4] = number of trees
Arguments can be passed in the python code with the import sys and the method sys.argv[n°] prefixed with the desired type (int, str, ...).
- Once the training start, a message is displayed to inform that a training is in progress and another message is displayed when it finished.
- The standard output of the python file is displayed in the application.

Fourth tab :
- Same method as for the previous tab, except that a prediction file must be passed as a parameter and should be already writtent in Python by the user.
- Possibility of passing a pre-trained model (arg[1]), an image to be classified (arg[2]) and a label file (arg[3]) as parameters to the python file.

## Collaboration

Florian Dayre, Elodie Gaudry, Hugo Lecomte, Hugo Trarieux.
