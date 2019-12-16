#include <stdlib.h>
#include "timeKeeper.h"

using namespace std;


int main(){
    TimeClass t1;
    t1.initTimeValues();
    bool called = false;

    
    while(1){
        t1.autoIncreaseTime();
        if(t1.getTime(1) == 20){
            //cout << t1.getTime(1) << endl;
        }
    }
}