#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct point {
    int x;
    int y;
};

double distance(struct point a, struct point b);
int getPointsLength(FILE *fp);


int main(){
    FILE *fp;
    char ch;
    struct point points[100];
    int pointsLength;

    fp = fopen("../assets/trace.txt", "r");

    pointsLength = getPointsLength(fp);

    // if (fp == NULL)
    // {
    //     perror("Error while opening the file.\n");
    //     exit(EXIT_FAILURE);
    // }

    // while((ch = fgetc(fp)) != EOF){
    //     printf("%c", ch);
    // }

    // fclose(fp);

    printf("%d",pointsLength);
    return 0;
}

int getPointsLength(FILE *fp){
    char pointsLengthTemp [4];// The amount of points is limited to 100, so we only need 3 digits and one for EOF -> [1] [0] [0] [\0]
    int i = 0;
    char ch;
    ch = fgetc(fp);

    while((ch != '\n') && (ch != EOF)){
        if(i<3){
            pointsLengthTemp[i] = ch;
        }
        i++;
        ch = fgetc(fp);
    }
    pointsLengthTemp[i] = '\0';
    fclose(fp);
    return atoi(pointsLengthTemp);
}

double distance(struct point a, struct point b ){

    return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}
