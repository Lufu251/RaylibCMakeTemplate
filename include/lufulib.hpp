#pragma once

#include <vector>

namespace lfl {
    template<typename T>
    struct Array2D{
    private:
        int mX, mY;
        std::vector<T> mData;

    public:
        Array2D(){}
        Array2D(size_t& x, size_t& y):mX(x), mY(y), mData(x*y){}
        
        void reserve(size_t& x, size_t& y){
            mData.reserve(x * y);
            mX = x;
            mY = y;
        }

        void resize(size_t& x, size_t& y){
            mData.resize(x * y);
            mX = x;
            mY = y;
        }

        int getX(){
            return mX;
        }

        int getY(){
            return mY;
        }

        T& operator()(size_t x, size_t y){
            return mData[mX * y + x];
        }

        const T& operator()(size_t x, size_t y) const {
            return mData[mX * y + x];
        }
    };

}