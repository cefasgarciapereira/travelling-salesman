#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

struct point {
    int x;
    int y;
};

double distance(struct point a, struct point b);
double allDistances(int number_of_points);
char toggleXY(char xy);
int getPointsLength();
int charToInt(char c);
void printPoints(int n);
struct point points[100];
double bestDistanceEver = 999999.99;
int bestPathEver[100];

/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */

void permute(int vector[], int start, int end){
 int i;
 int c;
 double totalDistance = 0;

 if(start == end){
   for(c=0;c<end+1;c++){
     //printf("%d ",vector[c]); //this print shows us all the path permutations
   }
   for(c=0;c<end;c++){
     //printf("dist(%d %d)",vector[c], vector[c+1]); // this print show us the par of points, like: (1 2)
     //printf(" = %.2lf ",distance(points[vector[c]], points[vector[c+1]])); //this print shows us the distance of the two points above (the edges)
     totalDistance = totalDistance + distance(points[vector[c]], points[vector[c+1]]); //the total distance of the path
   }
   //printf("\nTotal Distance = %.2lf",totalDistance);
   if(totalDistance < bestDistanceEver){ //if this is the shortest path, save it!
     bestDistanceEver = totalDistance;
     for(i=0;i<end+1;i++){
       bestPathEver[i] = vector[i]; // also save the path itself
     }
   }
   totalDistance = 0;
 }else{
   for(i=start; i <= end; i++){
     swap(vector,start,i);
     permute(vector,start+1,end);
     swap(vector,start,i);
   }
 }
}

void swap(int vector[], int i, int j)
{
    int temp;
    temp = vector[i];
    vector[i] = vector[j];
    vector[j] = temp;
}

int main(){
    int pointsLength;
    int i;
    int pointsIndexes[100];
    double total_time;
    clock_t start, end;

    for(i=0;i<100;i++){
      pointsIndexes[i]=i; // not an elegant way, but it sets the index value to an array. So we can print the proper path.
    }
    pointsLength = getPointsLength();
    getPoints();
    start = clock();
    srand(time(NULL));
    //time count starts
    permute(pointsIndexes,0,pointsLength-1);
    end = clock();
    //calulate total time
    total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printResult(pointsLength);
    printf("\nTime taken to solve it: %.2f miliseconds\n", total_time*1000);
    return 0;
}

void getPoints(){
    FILE *fp;
    fp = fopen("../../assets/trace.txt", "r");
    char ch;
    char XorY = 'x';
    int i = 0;
    int number = 0;
    int j=0;

    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    do{
        ch = fgetc(fp); //skip first line of the file
    }while(ch != '\n');

    while((ch = fgetc(fp)) != EOF){

     if(ch == ' '){
         if(XorY == 'x'){
             points[i].x = number;
         }

         if(XorY == 'y'){
             points[i].y = number;
         }

         XorY = toggleXY(XorY);
         number = 0;
     }

     if(ch == '\n' || ch == EOF){
           if(XorY == 'x'){
             points[i].x = number;
         }

         if(XorY == 'y'){
             points[i].y = number;
         }
         XorY = toggleXY(XorY);
         number = 0;
         i++;
     }

     if(ch=='0' || ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='8' || ch=='9'){
         number = (number*10) + charToInt(ch);
     }
    }
    if(XorY == 'x'){
        points[i].x = number;
    }

    if(XorY == 'y'){
        points[i].y = number;
    }
    fclose(fp);
}

int getPointsLength(){
    FILE *fp;
    char pointsLengthTemp [4];// The amount of points is limited to 100, so we only need 3 digits and one for EOF -> [1] [0] [0] [\0]
    int i = 0;
    char ch;
    fp = fopen("../../assets/trace.txt", "r");
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

double allDistances(int number_of_points){
    int i,j;
    for(i = 0;i<number_of_points;i++){
        for(j=0;j<number_of_points;j++){
            if(i != j){
                printf("\nDistance p%d x p%d: %.2lf",i,j,distance(points[i],points[j]));
            }
        }
    }
}

double distance(struct point a, struct point b ){
    return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

int charToInt(char c){
    int i;

    switch(c){
        case'0':
            i = 0;
        break;

        case'1':
            i = 1;
        break;

        case'2':
            i = 2;
        break;

        case'3':
            i = 3;
        break;

        case'4':
            i = 4;
        break;

        case'5':
            i = 5;
        break;

        case'6':
            i = 6;
        break;

        case'7':
            i = 7;
        break;

        case'8':
            i = 8;
        break;

        case'9':
            i = 9;
        break;

        default:
        break;
    }

    return i;
}

char toggleXY(char xy){
    char resp;
    if(xy == 'x'){
        resp = 'y';
    }else{
        resp = 'x';
    }

    return resp;
}

void printPoints(int n){
    int i;
    for(i=0;i<n;i++){
        printf("Point %d: (%d , %d)\n",i,points[i].x,points[i].y);
    }
}

void printResult(int n){
  int i;
  printf("\n");
  for(i=0;i<n-1;i++){
    printf("%d -> ",bestPathEver[i]);
  }
  printf("%d",bestPathEver[i++]);
  printf("\nBest Distance Ever: %.2lf",bestDistanceEver);
  printf("\n");
}
