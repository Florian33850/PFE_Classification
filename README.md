# PFE_Classification


## Table of Contents

1. [General Info](#general-info)
2. [Technologies](#technologies)
3. [Installation](#installation)
4. [Collaboration](#collaboration)

## General Info

... photos du projet ...

(The software allows to detect diseases from databases. non, pas encore en tout cas).

## Technologies

[OpenCV](https://gist.github.com/umardx/dfce1dc74d925629a9eb8ad409740b47) : Version 3.2.0
Debian GNU/Linux 10 (buster)
[Libtorch](https://pytorch.org/cppdocs/installing.html)
 
## Installation

Retrieve the file :
$ git clone git@github.com:Florian33850/PFE_Classification.git

CMake is used to manage the compilation of the project.
Create a build directory :

$ mkdir build
$ cd build

Include libtorch while generating the makefile :

$ cmake -DCMAKE_PREFIX_PATH=/libtorch_path/ ../PFE_CLASSIFICATION/
$ make

## Collaboration

Hugo Lecomte, Hugo Trarieux, Florian Dayre, Elodie Gaudry
