#include <stdlib.h>
#include "timeKeeper.h"
#include <time.h>
using namespace std;


int main(){
    TimeClass t1;
    t1.initTimeValues();
    t1.setTime("60", "0", "0", "0");
    while(1){
        t1.autoIncreaseTime();
        int *p = t1.getTime();
        t1.setTime("11", "cur", "cur" , "cur");
    }
}