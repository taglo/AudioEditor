#include "Sample.h"

Sample& Sample::clip(double maxValue ,double minValue ){
    
    
    for (int i = fxIStart; i < fxIEnd; i++) {
        if(data[i]>maxValue){
            data[i]=maxValue;
        }else if(data[i]<minValue){
            data[i]=minValue;
        }
    }

    return *this;    
}