int order[100];

void populate(){
  int i,j;
  for(i=0;i<100;i++){
    order[i] = i;
  }
}

void shuffle(int times, int ncities){
  int i,j,k,na,nb;
  srand ( time(NULL) );
  for(i=0;i<ncities;i++){
    na = rand() % ncities;
    nb = rand() % ncities;
    gaSwap(order,na,nb);
    printOrder(ncities);
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
