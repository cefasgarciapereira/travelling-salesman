#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include<time.h>
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
int order[100];
float fitness[15]; //this value must be the same as the row of listOfOrder
float bestFitness;
int listOfOrder[15][100];// the row value is the number of variated paths, the colum is the value of ncity
int listOfOrderIndex = 0;
double bestDistance = 999999;


void pickOne(int populationSize){
  int i, orderIndex;
  float tmp_fitness;
  bestFitness = fitness[0];
  for(i=0;i<populationSize;i++){
    if(fitness[i] > bestFitness){
      bestFitness = fitness[i];
      orderIndex = i;
    }
  }
  //system("clear"); //change to cls in windows
  printf("\nPickOne: Order %d with weight %.2lf and fitness %f\n",orderIndex,bestDistance,bestFitness);
}

void calculateFitness(int ncities, int orderIndex){//orderIndex is which route you want the fitness
  int col;
  double pathDistance = 0;
  float fitness_tmp;
  for(col=0;col<ncities-1;col++){
    pathDistance = pathDistance + distance(points[listOfOrder[orderIndex][col]],points[listOfOrder[orderIndex][col+1]]);
  }
  pathDistance = pathDistance + distance(points[listOfOrder[orderIndex][ncities-1]],points[listOfOrder[orderIndex][0]]);
  if(pathDistance < bestDistance){
    bestDistance = pathDistance; //store the best distance
  }
  fitness_tmp = (1 / (pathDistance + 1));
  printf("\nPath Distance of %d is %.2lf and the fitness is %f",orderIndex,pathDistance,fitness_tmp);
  fitness[orderIndex] = (1 / pathDistance);
  mutate(orderIndex,ncities);
}

void mutate(int orderIndex, int ncities){
  int indexA, indexB;
  indexA = rand() % (ncities - 1) + 1;
  indexB = rand() % (ncities - 1) + 1;  
  gaSwap(listOfOrder[orderIndex],indexA, indexB);
}

void initOrder(){
  int i,j;
  for(i=0;i<100;i++){
    order[i] = i;
  }
}

void shuffle(int times, int ncities){ // makes a new route starting from 1 and changin only one element
  int i,indexA, indexB;
  for(i=0;i<times;i++){
    indexA = rand() % (ncities - 1) + 1;
    indexB = rand() % (ncities - 1) + 1;
    gaSwap(order,indexA,indexB);
    pushOrder(ncities);
  }
  printListOfOrder(times,ncities);
}

void gaSwap(int v[],int a, int b){
  int temp;
  temp = v[a];
  v[a] = v[b];
  v[b] = temp;
}

void printOrder(int ncities){
  int i;
  printf("\n");
  for(i=0;i<ncities;i++){
    printf("%d ",order[i]);
  }
}

void pushOrder(int ncities){
  int col;
  for(col=0;col<ncities;col++){
    listOfOrder[listOfOrderIndex][col] = order[col];
  }
  calculateFitness(ncities,listOfOrderIndex);
  listOfOrderIndex++;
}

void printListOfOrder(int shuffle_times, int ncities){// shuffle_times = if you shuffle 10 times, then you'll have 10 variations of path
  int row, col;
  for(row = 0; row<shuffle_times;row++){
    printf("\n [%d]: ",row);
    for(col=0;col<ncities;col++){
      printf(" %d ->",listOfOrder[row][col]);
    }
  }
}

int main(){
  int pointsLength;
  int i;
  int populationSize = 15;//number of diferent path variation MAX of 15
  pointsLength = getPointsLength();
  getPoints();
  //printPoints(pointsLength);
  //allDistances(pointsLength);
  printf("\n\n");
  srand (time(NULL));
  initOrder();
  shuffle(populationSize,pointsLength);
  pickOne(populationSize);
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
