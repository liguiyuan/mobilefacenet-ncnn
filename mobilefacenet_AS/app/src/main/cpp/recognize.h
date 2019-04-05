//
// Created by liguiyuan on 19-4-5.
//
#pragma once
#ifndef MOBILEFACENET_AS_RECOGNIZE_H
#define MOBILEFACENET_AS_RECOGNIZE_H
#include <string>
#include "net.h"
#include <algorithm>

namespace Face {
    class Recognize {
    public:
        Recognize(const std::string &model_path);
        ~Recognize();
        void start(ncnn::Mat& ncnn_img, std::vector<float>&feature128);
        void SetThreadNum(int threadNum);
    private:
        void RecogNet(ncnn::Mat& img_);
        ncnn::Net Recognet;
        //ncnn::Mat ncnn_img;
        std::vector<float> feature_out;
        int threadnum = 1;
    };

    double calculSimilar(std::vector<float>& v1, std::vector<float>& v2);
}
#endif //MOBILEFACENET_AS_RECOGNIZE_H
