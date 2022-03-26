# PFE_Classification

## Table of Contents

1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)
4. [Usage](#usage)
5. [Collaboration](#collaboration)

## General Info

This project is part of our Master 2 Computer Science final year project at the university of Bordeaux. It is a generic classification application allowing to perform pre-processing on a loaded database, to do data augmentation, to launch classification model training (pre-written by the user in python) and to launch a classification on an image by loading a pre-trained model.

## Technologies

[OpenCV](https://gist.github.com/umardx/dfce1dc74d925629a9eb8ad409740b47) : Version 3.2.0
Debian GNU/Linux 10 (buster)
[QT](https://www.qt.io/download) : Version 5.0
## Installation

Retrieve the file :
$ git clone git@github.com:Florian33850/PFE_Classification.git

CMake is used to manage the compilation of the project.
Create a build directory :

$ mkdir build
$ cd build

$ cmake ..
$ make

Launch the application :

$ ./application_viewer

## Usage

First tab : 
- Possibility to load one or more images with File > ImageSelection or a database as a folder with File > LymeDatabase
- Addition of pre-processing which is carried out on the original images.
- Save all images with active pre-processing.

Second tab:
- Possibility to load images as before (if not already done in the previous tab).
- Addition of one or more data increases. Each data augmentation preview is done separately from each other.
- Saving the images is only done on the first data augmentation currently.

Third tab:
- Possibility to choose a classification method between deep learning and random
- Then you have to choose a python file (written by the user, where he will have specified the place where the arguments to be passed to the application will be called): 
       - DeepLearning: arg[1] = width of images, arg[2] = height of images, arg[3] = training set, arg[4] = testing set, arg[5] = number of epochs
       - RandomForest : arg[1] = width of images, arg[2] = height of images, arg[3] = training set, arg[4] = number of trees
Arguments can be passed in the python code with the import sys and the method sys.argv[n°] prefixed with the desired type (int, str, ...).
- Once the training is started, a message is displayed to warn that the training is in progress and another message warns when it is finished.
- The standard output of the python file is displayed on the application

Fourth tab :
Same method as for the previous tab except that a prediction file must be passed as a parameter which will have been written in python upstream by the user. Possibility of passing a pre-trained model (arg[1]), an image to be classified (arg[2]) and a label file (arg[3]) as parameters to the python file.

## Collaboration

Hugo Lecomte, Hugo Trarieux, Florian Dayre, Elodie Gaudry
