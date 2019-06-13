int order[100];
float fitness[15]; //this value must be the same as the row of listOfOrder
float bestFitness;
int listOfOrder[15][100];// the row value is the number of variated paths, the colum is the value of ncity
int listOfOrderIndex = 0;
double bestDistance = 999999;
struct point {
    int x;
    int y;
};
struct point points[4];

double distance(struct point a, struct point b ){
    return sqrt( pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

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
  //printf("\nPath Distance of %d is %.2lf and the fitness is %f",orderIndex,pathDistance,fitness_tmp);
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

void initPoints(){
  points[0].x = 100; points[0].y = 100;
  points[1].x = 900; points[1].y = 100;
  points[2].x = 900; points[2].y = 900;
  points[3].x = 100; points[3].y = 900;
}
