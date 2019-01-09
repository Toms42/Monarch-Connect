

# Monarch-Connect
A generic client for managing control and telemetry streams for embedded devices, such as mobile robots or IOT devices.

## Building
### Continuous Integration:
*Note: these builds run the test suite as well. Failing might indicate the build timed out, so check that*
* Ubuntu xenial (clang and gcc): [![Build Status](https://travis-ci.org/Toms42/Monarch-Connect.svg?branch=master)](https://travis-ci.org/Toms42/Monarch-Connect)
* Windows (mingw and msvc): TODO
* MacOS: TODO
### How to build: (Installer coming with first release!)
* Install Qt 5 for your os, as well as the opengl support. Installing Qt Creator will take care of all of this, or you can install individual packages as necessary. (reference the .travis.yml file to see what this project needs)
* Setup a compiler compatible with C++14. This project has been tested on Clang and GCC for MacOS and Linux (see travis) and MSVC and MinGW on Windows.
* Run qmake on the parent project. This project is configured using qmake to use c++14, which relies on the qmake packaged with qt 5.4 or later. (Note: This means that common qt 5.2 packages will not work out of the box, such as those used by default on Ubuntu 14 (trusty). You can fix by adding the cxx flags manually for your compiler, or updating your qmake version.
* Run make
* Run test suite in the test subdir to verify successful setup.
## Features:
* Modular, node-based creation of telemetry/control flows
* Saving/Loading of projects with multiple flows
* Hierarchical flows*
* Abstracted "Streams," "Events," and "Payloads" for different data use-cases.
* "Payload" system allowing payloads with multiple related fields
* User-defined "tags" which define payload types
* In-flow data visualization*
* Easy-access statistics for connections*
* Nodes for COM ports, TCP/UDP sockets, xbox controllers, etc*
* Convenience nodes for easy-setup arduino-integration*
* Easily-extended with new nodes
*\* indicates planned feature for first release* 
## Screenshots:
Current internal test build:
![enter image description here](https://i.imgur.com/b0FfJD1.png)

## Using
* [Qt](https://www.qt.io/): Cross-platform c++ gui framework.
* [Nodeeditor](https://github.com/paceholder/nodeeditor): A Qt Graph-node editor platform. Used to render the flows and handle user input and some data propagation. Using Chigraph's model-view fork.
## Progress
See the "projects" page for current status.
First release is aimed for the around late January 2019.
