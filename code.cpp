#include "code.h"
#include <iostream>
#include <vector>
using namespace std;
using Image = vector<vector<int>>;

void printImage(const Image& img){
    if(img.size()==0||img[0].size()==0){
        cout << "The provided image is invalid";
        return;
    }
    for(auto i=0;i<img.size();i++){
        for(auto j=0;j<(int)img[i].size();j++){
            cout << img[i][j];
            if(j != img[i].size()-1){
                cout << "\t";
            }
        }
        cout << endl;
    }
}

Image applyKernel(const Image& img){
    int H = (int)img.size();
    int W = 0;
    if (H > 0){
        W = (int)img[0].size();
    }
    Image out(H,vector<int>(W,0));
    if (H == 0||W==0) return out;
    int k[3][3] = {{-1,-1,-1},{-1,8,-1},{-1,-1,-1}};
    for(auto i=1;i<H-1;i++){
        for(auto j=1; j<=W-2;j++){
            int sum = 0;
            for(auto di = -1;di<=1;di++){
                for(auto dj = -1;dj<=1;dj++){
                    sum += img[i+di][j+dj]*k[di+1][dj+1];
                }
            }
            out[i][j] = sum;
        }
    }
    return out;
}

void minMaxNormalization(Image& img){
    if(img.size()==0||img[0].size()==0) return;
    int H = (int)img.size();
    int W = (int)img[0].size();
    int mn = img[0][0];
    int mx = img[0][0];
    for(int i=0; i<H; i++){
        for(int j=0; j<img[0].size();j++){
            mn=min(mn,img[i][j]);
            mx=max(mx,img[i][j]);
        }
    }
    if(mn == mx){
        for(int i= 0; i < H; i++)
            for (int j = 0; j < W; j++)
                img[i][j] = 0;
        return;
    }
    for(auto i=0;i<H;i++){
        for(auto j=0;j<W;j++){
            double scaled = (double)(img[i][j]-mn)/(double)(mx-mn)*255;
            img[i][j] = (int)scaled;
        }
    }
}

