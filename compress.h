//
// Created by sossnowski on 30/04/2020.
//
#include <iostream>
#ifndef EPSCOMPRESS_COMPRESS_H
#define EPSCOMPRESS_COMPRESS_H

using namespace std;


class Compress {
public:
    Compress();
    ~Compress();
    unique_ptr<char []> compressData(unique_ptr<char[]> buffer, string outputFileName);
};


#endif //EPSCOMPRESS_COMPRESS_H
