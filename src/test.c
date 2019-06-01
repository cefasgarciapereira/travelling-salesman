#include<stdio.h>

int main(){
    int v[3];
    v[0] = 8;
    v[1] = 3;
    v[2] = 7;
    int concat=0;
    int i;
    
    for(i=0;i<3;i++){
        concat = (concat*10) + v[i];
    }
    printf("%d",concat);
}