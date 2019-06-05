#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define INT_MAX 999999

int n=4;
int dist[100][100];
int VISITED_ALL;
int dp[16][4];

struct point {
    int x;
    int y;
};

double distance(struct point a, struct point b);
double allDistances(int number_of_points, int print);
char toggleXY(char xy);
int getPointsLength();
int charToInt(char c);
void printPoints(int n);
struct point points[100];
double costMatrix[100][100];

int  tsp(int mask,int pos){

	if(mask==VISITED_ALL){
		return dist[pos][0];
	}
	if(dp[mask][pos]!=-1){
	   return dp[mask][pos];
	}

	//Now from current node, we will try to go to every other node and take the min ans
	int ans = INT_MAX;

	//Visit all the unvisited cities and take the best route
	for(int city=0;city<n;city++){

		if((mask&(1<<city))==0){

			int newAns = dist[pos][city] + tsp( mask|(1<<city), city);
			ans = min(ans, newAns);
		}
	}

	return dp[mask][pos] = ans;
}

int min(int a, int b){
  if(a<b){
    return a;
  }else{
    return b;
  }
}

int main(){
    int pointsLength;
    int i;
    pointsLength = getPointsLength();
    getPoints();
    printPoints(pointsLength);
    allDistances(pointsLength,1);
    double total_time;
    clock_t start, end;
    printf("\n\n");
    /* init the dp array */
    VISITED_ALL = (1<<pointsLength)-1;
    for(int i=0;i<(1<<pointsLength);i++){
        for(int j=0;j<pointsLength;j++){
            dp[i][j] = -1;
        }
    }
    /* init the cost array */
    for(int i=0;i<(1<<pointsLength);i++){
        for(int j=0;j<pointsLength;j++){
            dist[i][j] = costMatrix[i][j];
        }
    }
    start = clock();
    srand(time(NULL));
    //time count starts
    printf("Best Distance Ever: %d\n",tsp(1,0));
    end = clock();
    //calulate total time
    total_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken to solve it: %.2lf miliseconds\n", total_time*1000);
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

double allDistances(int number_of_points, int print){//if print is 1, print the result
    int i,j;
    if(print == 1){
      printf("\n");
    }
    for(i = 0;i<number_of_points;i++){
        for(j=0;j<number_of_points;j++){
            costMatrix[i][j] = distance(points[i],points[j]);
            if(print == 1){
                printf("%.lf ",i,j, costMatrix[i][j]);
            }
        }
        printf("\n");
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
