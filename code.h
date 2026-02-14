#pragma once
#include <vector>

using Image = std::vector<std::vector<int>>;

void printImage(const Image& img);

Image applyKernel(const Image& img);

void minMaxNormalization(Image& img);
