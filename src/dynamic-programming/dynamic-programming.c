#include<stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
double a[100][100];
int visited[10],n,cost=0; // from the algorithm
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

void get()
{
	int i,j;
	printf("\n\nThe cost list is:\n\n");
	for( i=0;i < n;i++)
	{
		printf("\n\n");
		for(j=0;j < n;j++)
			printf("\t%d",a[i][j]);
	}
}

void mincost(int city)
{
	int i,ncity;
	visited[city]=1;	
	printf("%d -> ",city);
	ncity=least(city);
	if(ncity==999)
	{
		ncity=0;
		printf("%d",ncity);
		cost+=a[city][ncity];
		return;
	}
	mincost(ncity);
}

int least(int c)
{
	int i,nc=999;
	int min=999,kmin;
	for(i=0;i < n;i++)
	{
		if((a[c][i]!=0)&&(visited[i]==0))
			if(a[c][i] < min)
			{
				min=a[i][0]+a[c][i];
				kmin=a[c][i];
				nc=i;
			}
	}
	if(min!=999)
		cost+=kmin;
	return nc;
}

void put()
{
	printf("\n\nMinimum cost:");
	printf("%d",cost);
}

int main(){
    int pointsLength;
    int i;
    pointsLength = getPointsLength();
    n = pointsLength;
    getPoints();
    //printPoints(pointsLength);
    //allDistances(pointsLength);
    populateA(pointsLength);
	mincost(0);
    printf("\nThe Best Path Ever is %d\n",cost);
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

void populateA(int number_of_points){
    int i,j;
    for(i = 0;i<number_of_points;i++){
        for(j=0;j<number_of_points;j++){
            if(i != j){
                a[i][j] = distance(points[i],points[j]);
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