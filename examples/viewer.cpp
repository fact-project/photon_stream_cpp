// compile using:
// g++ docopt/docopt.cpp viewer.cpp -o phs.viewer -std=gnu++11

#include <stdio.h>
#include <string.h>
#include <array>
#include "../photon_stream.h"
#include "docopt/docopt.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace ps = photon_stream;

static const char USAGE[] =
R"(Show FACT photon-stream event overview. Reads in phs
files from ungzipped file. 

    Usage:
      phs.slices  --input=PATH
      phs.slices  (-h | --help)
      phs.slices  --version

    Options:
      -i --input=PATH     Path to the ungzipped photon-stream file.
      -h --help           Show this screen.
      --version           Show version.
      
)";

float px [] = {28.5,33.25,33.25,38.0,42.75,42.75,47.5,52.25,52.25,-0.0,4.75,4.75,9.5,14.25,14.25,19.0,23.75,23.75,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,133.0,128.25,123.5,118.75,123.5,118.75,114.0,109.25,104.5,104.5,99.75,95.0,90.25,95.0,90.25,85.5,80.75,76.0,85.5,80.75,76.0,76.0,71.25,66.5,61.75,61.75,57.0,128.25,123.5,123.5,118.75,114.0,114.0,109.25,104.5,104.5,152.0,147.25,142.5,137.75,147.25,142.5,137.75,133.0,128.25,99.75,95.0,95.0,90.25,85.5,85.5,80.75,76.0,76.0,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,175.75,175.75,171.0,166.25,161.5,161.5,156.75,152.0,147.25,171.0,166.25,161.5,156.75,156.75,152.0,147.25,142.5,133.0,142.5,137.75,137.75,133.0,128.25,128.25,123.5,118.75,118.75,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,185.25,185.25,180.5,175.75,180.5,175.75,171.0,166.25,161.5,156.75,152.0,152.0,147.25,142.5,142.5,137.75,133.0,133.0,128.25,123.5,123.5,118.75,114.0,114.0,109.25,104.5,104.5,99.75,95.0,95.0,90.25,85.5,85.5,80.75,76.0,76.0,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,171.0,166.25,166.25,161.5,156.75,156.75,152.0,147.25,147.25,142.5,137.75,137.75,133.0,128.25,128.25,123.5,118.75,118.75,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,156.75,152.0,152.0,147.25,142.5,142.5,137.75,133.0,133.0,185.25,180.5,180.5,175.75,171.0,171.0,166.25,161.5,161.5,128.25,123.5,123.5,118.75,114.0,114.0,109.25,104.5,104.5,99.75,95.0,95.0,90.25,85.5,85.5,80.75,76.0,76.0,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,185.25,185.25,180.5,175.75,180.5,175.75,171.0,166.25,161.5,171.0,166.25,166.25,161.5,156.75,156.75,152.0,147.25,147.25,142.5,137.75,137.75,133.0,128.25,128.25,123.5,118.75,118.75,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,175.75,175.75,171.0,166.25,161.5,161.5,156.75,152.0,147.25,156.75,152.0,152.0,147.25,142.5,142.5,137.75,133.0,133.0,128.25,123.5,123.5,118.75,114.0,114.0,109.25,104.5,104.5,99.75,95.0,95.0,90.25,85.5,85.5,80.75,76.0,76.0,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,171.0,166.25,161.5,156.75,156.75,152.0,147.25,142.5,133.0,142.5,137.75,137.75,133.0,128.25,128.25,123.5,118.75,118.75,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,152.0,147.25,142.5,137.75,147.25,142.5,137.75,133.0,128.25,128.25,123.5,123.5,118.75,114.0,114.0,109.25,104.5,104.5,99.75,95.0,95.0,90.25,85.5,85.5,80.75,76.0,76.0,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,133.0,128.25,123.5,118.75,123.5,118.75,114.0,109.25,104.5,114.0,109.25,109.25,104.5,99.75,99.75,95.0,90.25,90.25,104.5,99.75,95.0,90.25,95.0,90.25,85.5,80.75,76.0,85.5,80.75,80.75,76.0,71.25,71.25,66.5,61.75,61.75,57.0,52.25,52.25,47.5,42.75,42.75,38.0,33.25,33.25,28.5,23.75,23.75,19.0,14.25,14.25,9.5,4.75,4.75,42.75,38.0,38.0,33.25,28.5,28.5,23.75,19.0,19.0,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,85.5,80.75,76.0,76.0,71.25,66.5,61.75,61.75,57.0,71.25,66.5,66.5,61.75,57.0,57.0,52.25,47.5,47.5,28.5,33.25,33.25,38.0,42.75,42.75,47.5,52.25,52.25,-0.0,4.75,4.75,9.5,14.25,14.25,19.0,23.75,23.75,-57.0,-52.25,-52.25,-47.5,-42.75,-42.75,-38.0,-33.25,-33.25,-28.5,-23.75,-23.75,-19.0,-14.25,-14.25,-9.5,-4.75,-4.75,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-104.5,-114.0,-118.75,-123.5,-114.0,-118.75,-123.5,-128.25,-128.25,-71.25,-76.0,-80.75,-85.5,-90.25,-95.0,-99.75,-104.5,-109.25,-61.75,-66.5,-71.25,-76.0,-76.0,-80.75,-85.5,-90.25,-95.0,-99.75,-104.5,-104.5,-109.25,-114.0,-114.0,-118.75,-123.5,-123.5,-128.25,-133.0,-133.0,-137.75,-133.0,-137.75,-142.5,-142.5,-147.25,-71.25,-76.0,-76.0,-80.75,-85.5,-85.5,-90.25,-95.0,-95.0,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,-147.25,-152.0,-156.75,-161.5,-166.25,-166.25,-171.0,-171.0,-175.75,-142.5,-147.25,-142.5,-156.75,-152.0,-152.0,-156.75,-147.25,-161.5,-114.0,-118.75,-118.75,-123.5,-128.25,-128.25,-133.0,-137.75,-137.75,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,-156.75,-161.5,-161.5,-166.25,-171.0,-175.75,-175.75,-180.5,-185.25,-128.25,-133.0,-133.0,-137.75,-142.5,-142.5,-147.25,-152.0,-152.0,-99.75,-104.5,-104.5,-109.25,-114.0,-114.0,-118.75,-123.5,-123.5,-71.25,-76.0,-76.0,-80.75,-85.5,-85.5,-90.25,-95.0,-95.0,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,-142.5,-147.25,-147.25,-152.0,-156.75,-156.75,-161.5,-166.25,-166.25,-114.0,-118.75,-118.75,-123.5,-128.25,-128.25,-133.0,-137.75,-137.75,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-156.75,-161.5,-161.5,-166.25,-171.0,-171.0,-175.75,-180.5,-185.25,-171.0,-171.0,-175.75,-180.5,-175.75,-180.5,-180.5,-185.25,-185.25,-128.25,-133.0,-133.0,-137.75,-142.5,-142.5,-147.25,-152.0,-152.0,-99.75,-104.5,-104.5,-109.25,-114.0,-114.0,-118.75,-123.5,-123.5,-71.25,-76.0,-76.0,-80.75,-85.5,-85.5,-90.25,-95.0,-95.0,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,-156.75,-161.5,-161.5,-166.25,-171.0,-175.75,-175.75,-180.5,-185.25,-142.5,-147.25,-147.25,-152.0,-156.75,-156.75,-161.5,-166.25,-166.25,-114.0,-118.75,-118.75,-123.5,-128.25,-128.25,-133.0,-137.75,-137.75,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-147.25,-152.0,-156.75,-161.5,-166.25,-166.25,-171.0,-171.0,-175.75,-128.25,-133.0,-133.0,-137.75,-142.5,-142.5,-147.25,-152.0,-152.0,-99.75,-104.5,-104.5,-109.25,-114.0,-114.0,-118.75,-123.5,-123.5,-71.25,-76.0,-76.0,-80.75,-85.5,-85.5,-90.25,-95.0,-95.0,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,-142.5,-142.5,-147.25,-156.75,-147.25,-152.0,-152.0,-156.75,-161.5,-114.0,-118.75,-118.75,-123.5,-128.25,-128.25,-133.0,-137.75,-137.75,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-128.25,-133.0,-133.0,-137.75,-133.0,-137.75,-142.5,-142.5,-147.25,-99.75,-104.5,-104.5,-109.25,-114.0,-114.0,-118.75,-123.5,-123.5,-71.25,-76.0,-76.0,-80.75,-85.5,-85.5,-90.25,-95.0,-95.0,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-104.5,-114.0,-118.75,-123.5,-114.0,-118.75,-123.5,-128.25,-128.25,-85.5,-90.25,-90.25,-95.0,-99.75,-99.75,-104.5,-109.25,-109.25,-71.25,-76.0,-80.75,-85.5,-90.25,-95.0,-99.75,-104.5,-109.25,-57.0,-61.75,-61.75,-66.5,-71.25,-71.25,-76.0,-80.75,-80.75,-28.5,-33.25,-33.25,-38.0,-42.75,-42.75,-47.5,-52.25,-52.25,-0.0,-4.75,-4.75,-9.5,-14.25,-14.25,-19.0,-23.75,-23.75,-14.25,-19.0,-19.0,-23.75,-28.5,-28.5,-33.25,-38.0,-38.0,14.25,9.5,9.5,4.75,-0.0,-0.0,-4.75,-9.5,-9.5,-61.75,-66.5,-71.25,-76.0,-76.0,-80.75,-85.5,-90.25,-95.0,-42.75,-47.5,-47.5,-52.25,-57.0,-57.0,-61.75,-66.5,-66.5,-57.0,-52.25,-52.25,-47.5,-42.75,-42.75,-38.0,-33.25,-33.25,-28.5,-23.75,-23.75,-19.0,-14.25,-14.25,-9.5,-4.75,-4.75};
float py [] = {172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,131.67,123.805,115.14,139.84,131.67,139.84,148.105,139.84,156.275,148.105,156.275,164.54,139.84,148.105,139.84,148.105,139.84,156.275,164.54,156.275,172.805,164.54,172.805,164.54,180.975,172.805,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,106.97,98.705,106.97,98.705,115.14,123.805,115.14,106.97,115.14,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,49.4,65.835,57.57,65.835,57.57,74.005,65.835,74.005,65.835,74.005,82.27,90.535,82.27,98.705,90.535,82.27,90.535,90.535,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,16.435,32.87,24.7,16.435,41.135,32.87,41.135,49.4,41.135,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-32.87,-16.435,-24.7,-16.435,-41.135,-32.87,-41.135,-49.4,-41.135,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-65.835,-49.4,-57.57,-65.835,-74.005,-57.57,-65.835,-74.005,-65.835,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-90.535,-82.27,-98.705,-90.535,-82.27,-90.535,-90.535,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-106.97,-98.705,-106.97,-98.705,-115.14,-123.805,-115.14,-106.97,-115.14,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-123.805,-131.67,-123.805,-115.14,-139.84,-131.67,-139.84,-148.105,-139.84,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-156.275,-148.105,-156.275,-164.54,-139.84,-148.105,-139.84,-148.105,-139.84,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-156.275,-164.54,-172.805,-156.275,-164.54,-172.805,-180.975,-164.54,-172.805,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-172.805,-164.54,-180.975,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-148.105,-156.275,-139.84,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-139.84,-139.84,-131.67,-139.84,-123.805,-115.14,-123.805,-131.67,-115.14,-148.105,-139.84,-148.105,-139.84,-148.105,-139.84,-148.105,-156.275,-148.105,-164.54,-172.805,-164.54,-172.805,-156.275,-164.54,-156.275,-164.54,-156.275,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-123.805,-115.14,-123.805,-106.97,-115.14,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-123.805,-131.67,-115.14,-65.835,-74.005,-65.835,-74.005,-82.27,-65.835,-74.005,-57.57,-65.835,-90.535,-82.27,-74.005,-82.27,-90.535,-106.97,-98.705,-98.705,-90.535,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-74.005,-82.27,-65.835,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-98.705,-106.97,-90.535,-49.4,-57.57,-41.135,-49.4,-41.135,-49.4,-32.87,-41.135,-32.87,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-49.4,-57.57,-41.135,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,-24.7,-32.87,-16.435,0.0,-8.265,8.265,0.0,8.265,24.7,16.435,24.7,16.435,-24.7,-8.265,-16.435,-24.7,0.0,-8.265,8.265,-16.435,0.0,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,0.0,-8.265,8.265,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,32.87,49.4,41.135,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,24.7,16.435,32.87,65.835,74.005,65.835,74.005,65.835,82.27,57.57,74.005,65.835,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,49.4,41.135,57.57,49.4,41.135,57.57,49.4,41.135,57.57,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,90.535,82.27,82.27,98.705,90.535,106.97,98.705,90.535,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,74.005,65.835,82.27,98.705,90.535,106.97,98.705,123.805,115.14,106.97,123.805,115.14,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,98.705,90.535,106.97,139.84,139.84,131.67,139.84,123.805,115.14,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,148.105,139.84,148.105,139.84,148.105,139.84,148.105,156.275,148.105,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,123.805,115.14,131.67,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,164.54,172.805,164.54,172.805,156.275,164.54,156.275,164.54,156.275,148.105,139.84,156.275,148.105,139.84,156.275,148.105,139.84,156.275,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54,172.805,180.975,164.54};

uint8_t intensity_to_color_code(float i) {
    // ”<Esc>[48;5;ColorNumber
    if(i > 1.0)
        i = 1.0;
    if(i < 0.0)
        i = 0.0;
    float close = i*23.0;
    float contr = close + 232.0;
    uint8_t out = uint8_t(floor(contr));
    return out;
}

std::array<int, 9> nx =   { 1, 0,-1, 1, 0,-1, 1, 0,-1};
std::array<int, 9> ny =   { 1, 1, 1, 0, 0, 0,-1,-1,-1};
std::array<float, 9> we = {.3,.5,.3,.5, 1,.5,.3,.5,.3};

const uint64_t NUMBER_OF_TIME_INTEGRAL_SLICES = 19;
# define cmdl_image std::array<std::array<float, 80>, 80>
# define cmdl_image_seq std::array<cmdl_image, NUMBER_OF_TIME_INTEGRAL_SLICES>
# define phs_integral std::array<uint64_t, ps::NUMBER_OF_PIXELS>
# define phs_lol std::array<std::vector<uint8_t>, ps::NUMBER_OF_PIXELS>


cmdl_image normalized_cmdl_image(cmdl_image in, float max) {
    cmdl_image out;
    for(int x=0; x<in.size(); x++) {
        for(int y=0; y<in.at(x).size(); y++) {
            out.at(x).at(y) = in.at(x).at(y) / max;
        }
    }
    return out;
}


void print_cmdl_image(cmdl_image img, float max) {

    img = normalized_cmdl_image(img, max);

    std::array<std::array<uint8_t, 80>, 80> color_code_img;
    for(int x=0; x<img.size(); x++) {
        for(int y=0; y<img.at(x).size(); y++) {
            color_code_img.at(x).at(y) = intensity_to_color_code(
                img.at(x).at(y)
            );
        }
    }

    std::stringstream out;
    for(int x=0; x<color_code_img.size(); x++) {
        for(int y=0; y<color_code_img.at(x).size(); y++) {
            uint8_t color_code = color_code_img.at(x).at(y);
            std::string color = std::to_string(color_code);
            out << "\033[48;5;" << color << "m  \033[0m";
        }
        out << "\n";
    }

    std::cout << out.str();
}


void print_colorbar(float min, float max) {
    std::stringstream out;
    std::array<uint8_t, 65> bar;
    for(int i=0; i<bar.size(); i++) {
        float u = float(i)/bar.size();
        bar.at(i) = intensity_to_color_code(u);
    }
    out << min << " [";
    for(int i=0; i<bar.size(); i++) {
        uint8_t color_code = bar.at(i);
        std::string color = std::to_string(color_code);
        out << "\033[48;5;" << color << "m  \033[0m";
    }
    out << "] " << max << " photons\n";
    std::cout << out.str();
}


cmdl_image phs_integral_to_cmdl_image(phs_integral integral) {
    cmdl_image bg;
    for(int x=0; x<bg.size(); x++)
        for(int y=0; y<bg.at(x).size(); y++)
            bg.at(x).at(y) = 0;

    for(int chid=0; chid<integral.size(); chid++) {
        float x = px[chid]/5.0 + 2*19.0;
        float y = py[chid]/5.0 + 2*19.0;

        int cx = int(round(x));
        int cy = int(round(y));

        for(uint64_t n=0; n<nx.size(); n++) {
            int ax = cx + nx.at(n);
            int ay = cy + ny.at(n);

            if(ax>=0 && ax<80 && ay>=0 && ay<80) {
                bg.at(ax).at(ay) += we.at(n)*float(integral.at(chid));
            }
        }
    }
    return bg;
}


phs_integral phs_integral_start_stop(phs_lol& phs, uint8_t start, uint8_t stop) {
    phs_integral integral;
    for(uint64_t chid=0; chid<integral.size(); chid++)
        integral.at(chid) = 0;

    for(uint64_t chid=0; chid<phs.size(); chid++) {
        for(uint64_t ph=0; ph<phs.at(chid).size(); ph++) {
            uint8_t t = phs.at(chid).at(ph);
            if(t >= start && t < stop)
                integral.at(chid) += 1;
        }
    }
    return integral;
}


float max_intensity_in_cmdl_image(cmdl_image img) {
    float max = 0.0;
    for(int x=0; x<img.size(); x++) {
        for(int y=0; y<img.at(x).size(); y++) {
            if(img.at(x).at(y) > max)
                max = img.at(x).at(y);
        }
    }
    return max;
}


struct ArgMax {
    float max;
    uint64_t arg;
};  


ArgMax argmax_intensity_in_cmdl_image_seq(cmdl_image_seq img_seq) {
    ArgMax argmax;
    argmax.max = 0;
    for(uint64_t i=0; i<img_seq.size(); i++) {
        float maxi = max_intensity_in_cmdl_image(img_seq.at(i));
        if(maxi > argmax.max) {
            argmax.max = maxi;
            argmax.arg = i;
        }            
    }
    return argmax;
}


struct Slices{
    ArgMax arg_max;
    cmdl_image_seq img_seq;
};


Slices make_slices_from_phs_lol(phs_lol lol) {
    Slices slices;
    for(uint64_t i=0; i<slices.img_seq.size(); i++) {
        uint8_t start = i*5 + ps::NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI;
        uint8_t stop = start + 10 + ps::NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI;
        phs_integral phs_i = phs_integral_start_stop(lol, start, stop);
        slices.img_seq.at(i) = phs_integral_to_cmdl_image(phs_i);
    }
    slices.arg_max = argmax_intensity_in_cmdl_image_seq(slices.img_seq);
    return slices;
}


void print_event_info_line(ps::ObservationEvent &event) {
    printf(
        "Night %5d  Run %3d  Event %6d  Trigger %6d\nAzimuth %3.2fdeg  Zenith distance %3.2fdeg\nUnixTime %10.6fs  photons %6d  Saturated %s\n",  
        event.id.night,
        event.id.run,
        event.id.event,
        event.info.trigger_type,
        event.pointing.az,
        event.pointing.zd,
        float(event.info.unix_time_s) + 1e-6*float(event.info.unix_time_us),
        event.photon_stream.number_of_photons(),
        event.photon_stream.is_saturated() ? "true" : "false"
    );
};


void print_time_slice_bar(int slice) {
    int start_slice = slice*5;
    int end_slice = slice*5+10;
    int END = NUMBER_OF_TIME_INTEGRAL_SLICES*5 + 5;
    std::cout << "Time              <";
    std::cout << std::string(start_slice, '.');
    std::cout << "[        ]";
    std::cout << std::string(END - end_slice, '.');
    std::cout << "> ";
    std::cout << 0.5*float(start_slice + ps::NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI) << "ns to ";
    std::cout << 0.5*float(end_slice + ps::NUMBER_OF_TIME_SLICES_OFFSET_AFTER_BEGIN_OF_ROI) << "ns\n";
}


std::vector<ps::ObservationEvent> read_in_event_list(std::string path) {
    std::vector<ps::ObservationEvent> events;
    std::ifstream fin(path.c_str(), std::ios::binary);
    while(true) {
        ps::ObservationEvent event = ps::read_ObservationEvent_from_file(fin);
        if(!event.descriptor.is_valid())
            break;
        events.push_back(event);
    }
    fin.close();
    return events;
}

const char ESCAPE_KEY = 27;

int event_idx = 0;
int slice_idx = 0;
std::vector<ps::ObservationEvent> events;

void next_event_if_possible() {
    if(event_idx + 1 < events.size())
        event_idx++;
};

void prev_event_if_possible() {
    if(event_idx - 1 >= 0)
        event_idx--;
};

void next_slice_if_possible() {
    if(slice_idx + 1 < NUMBER_OF_TIME_INTEGRAL_SLICES)
        slice_idx++;
};

void prev_slice_if_possible() {
    if(slice_idx - 1 >= 0)
        slice_idx--;
};

void go_to_event_id(int event_id) {
    for(int i=0; i<events.size(); i++) {
        if(events.at(i).id.event == event_id)
            event_idx = i;
    }
}

void print_help() {
    std::cout << std::string(120, '\n');
    std::stringstream o;
    o << "  FACT - Photon-Stream Event Viewer  \n";
    o << "-------------------------------------\n";
    o << "\n";
    o << "    Press [return] key after each input\n";
    o << "\n";
    o << "    [h]    Print this help\n";
    o << "\n";
    o << "    [d]    Next event\n";
    o << "    [a]    Previous event\n";
    o << "\n";   
    o << "    [g]    Go to event ID if existing\n";
    o << "\n";
    o << "    [w]    Next time slice integral\n";
    o << "    [s]    Previous time slice integral\n";
    o << "           (Time slices are 5ns integrals here)\n";
    o << "\n";
    o << "    [ESC]  Quit\n";
    o << "\n";
    o << "\n";    
    o << "Requieres\n";
    o << "---------\n";
    o << "    Your terminal must support:\n";
    o << "    American National Standards Institute (ANSI) escape sequences\n";
    o << "\n";
    o << "To blame: Sebastian A. Mueller, ETH Zurich 2017, sebmuell@phys.ethz.ch\n";
    std::cout << o.str();
}


int main(int argc, char* argv[]) {

    std::map<std::string, docopt::value> args = docopt::docopt(
        USAGE,
        { argv + 1, argv + argc },
        true,        // show help if requested
        "mct 0.0"
    );  // version string

    std::string path = args.find("--input")->second.asString();
    events = read_in_event_list(path);

    if(events.size() == 0)
        return 0;

    ps::ObservationEvent current_event = events.at(0);
    Slices current_slices = make_slices_from_phs_lol(
        ps::list_of_lists_representation(current_event.photon_stream.raw)
    );
    slice_idx = current_slices.arg_max.arg;

    bool go_on = true;
    bool update_event = true;
    bool update_slice = false;

    print_help();
    while(go_on) {
        std::string user_input;
        std::getline(std::cin, user_input);
        
        update_event = true;
        update_slice = false;
        if(user_input.length() > 0) {
            char first_key = user_input.at(0);
            if(first_key == ESCAPE_KEY) {
                go_on = false;
                update_event = false;
            }else if(first_key == 'd') {
                next_event_if_possible();
            }else if(first_key == 'a') {
                prev_event_if_possible();
            }else if(first_key == 'w') {
                next_slice_if_possible();
                update_event = false;
                update_slice = true;
            }else if(first_key == 's') {
                prev_slice_if_possible();
                update_event = false;
                update_slice = true;
            }else if(first_key == 'g') {
                std::string event_id_str = user_input.substr(1);
                go_to_event_id(atoi(event_id_str.c_str()));
            }else if(first_key == 'h') {
                print_help();
                update_event = false;
            }else{
                update_event = false;
            }

        }else{
            update_event = false;
        }

        if(update_event) {
            current_event = events.at(event_idx);
            current_slices = make_slices_from_phs_lol(
                ps::list_of_lists_representation(current_event.photon_stream.raw)
            );
            slice_idx = current_slices.arg_max.arg;
        }

        if(update_event || update_slice) {
            std::cout << std::string(120, '\n');
            cmdl_image img = current_slices.img_seq.at(slice_idx);
            print_cmdl_image(img, current_slices.arg_max.max);
            print_colorbar(0.0, current_slices.arg_max.max);
            std::cout << "\n";
            print_time_slice_bar(slice_idx);
            std::cout << "\n";
            print_event_info_line(current_event);
        }   
    }

    return 0;
};
