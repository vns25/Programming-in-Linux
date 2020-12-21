#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <time.h>

#define OK 1
#define NOK 0
#define NELM 100		/* default 100 elements */
#define N 1048576		/* 2^30 or 1 meg elements  */
//#define N 2097152
//#define N 4194304
//#define N 8388608
//#define N 16777216
//#define N 33554432

void selection_sort();
void merge_sort(); 
void split_merge();
void int_radix_sort();
void float_radix_sort(); 
void float_lst(); 
void print_float_lst();  
void self_check();
void init_lst();
void print_lst();

int n, lst[N], buf[N];
float fl[N]; 

int main(int argc,char **argv) {  
  clock_t t; 
  t=clock(); 

  if (argc>1)
    n = atoi(argv[1]);
  else 
    n = NELM; 

  // INITIALIZING LIST 
  init_lst(lst,n);
  //print_lst(lst, n); 
  // float_lst(fl, n); 
  // print_float_lst(fl, n); 

  printf("\n------------PERFORMING RADIX INT SORT------------\n\n"); 

  // SORT LIST 
  selection_sort(lst,n);
  // merge_sort(lst,buf,n);
  // int_radix_sort(lst,buf,n);
  // float_radix_sort(fl,buf,n);

  // PRINT SORTED LIST
  //print_lst(lst, n); 
  // print_float_lst(fl, n); 

  // ELAPSED TIME 
  t=clock() -t; 
  double time_taken = ((double)t)/CLOCKS_PER_SEC; 
  double time_ms = time_taken * 1000; 
  printf("The sorting algorithm took %f seconds and %f milliseconds \n\n", time_taken, time_ms);

  return 0;
}

void selection_sort(int lst[],int n){
  int min_idx, temp; 
  for(int i = 0; i < n-1; i++) {
      min_idx = i; 
      for(int j = i; j < n; j++) {
          if( lst[min_idx] > lst[j] ) {
              min_idx = j; 
          }
      }
      int temp = lst[min_idx]; 
      lst[min_idx] = lst[i]; 
      lst[i] = temp; 
  }
}

void merge(int lst[], int buf[], int left, int mid, int right){
  int i = left, j=mid+1, k=0; 

  while(i <= mid && j<= right) {
    if(lst[i] <= lst[j]){
      buf[k]= lst[i]; 
      k++; 
      i++; 
    }
    else {
      buf[k] = lst[j]; 
      k++; 
      j++; 
    }
  }
  while( i <= mid) {
    buf[k] = lst[i]; 
    k++; 
    i++; 
  }
  while( j<= right) {
    buf[k] = lst[j]; 
    k++; 
    j++; 
  }
  for(i= left; i<=right; i++) {
    lst[i] = buf[i-left]; 
  }
}

//use recursion
void split_merge(int lst[], int buf[], int left, int right){
   if( left < right) {
       int mid = (right + left) / 2 ;  
       split_merge(lst, buf, left, mid ); 
       split_merge(lst, buf, mid + 1, right ); 
       merge(lst, buf, left, mid, right); 
   }
}

void merge_sort(int lst[], int buf[], int n) {
    split_merge(lst, buf, 0, n-1);
}

//fix the bucket size to 256. run 4 passes where each pass processes 8 bits
void float_radix_sort(int lst[], int buf[], int n) {
  int negCount = 0, *src = lst, *dst = buf, group = 8; 
  int bucket = 1 << group; // 256 
  int mask = bucket-1; // 255
  int cnt[bucket], map[bucket];  
  
  //4 passes processing 8 bits each
  for(int i=0; i<32; i=i+group) {
    //Set cnt[] and map[] to 0s
    for(int j = 0; j<bucket; j++) {
      cnt[j] = map[j] = 0; 
    }
    //count freq and store in cnt[]
    for(int k=0; k<n; k++) {
      cnt[ (src[k] >> i) & mask ]++; 
    }
    //count neg values if last pass 
    if( i == 24 ){
      for(int c=128; c<256; c++){
        negCount += cnt[c]; 
      }
    }
    //cumulative count 
    for(int m=1; m<bucket; m++) {
       map[m] = cnt[m-1] + map[m-1]; 
    } 
    //move to dst 
    for(int p=0; p<n; p++) {
        dst[ map[ (src[p] >> i) & mask]++] = src[p]; 
    }
    //for negative floats 
    if( negCount > 0 ) {
      int num=n-1; 
      for(int i=0; i<negCount; i++){
        src[i]=dst[num-i]; 
      }
      if(negCount != n) {
        int numLeft = n-negCount; 
        for(int i=0; i<numLeft; i++){
          src[ negCount+i ]= dst[i]; 
        }
      }
    }
    //positive floats 
    else {
      for(int q=0; q<n; q++){
        src[q] = dst[q]; 
      }
    }
  }
}

void int_radix_sort(int lst[], int buf[], int n) {
  int negCount = 0, *src = lst, *dst = buf, group = 8; 
  int bucket = 1 << group; // 256 
  int mask = bucket-1; // 255
  int cnt[bucket], map[bucket];  
  
  for(int i=0; i<32; i=i+group) {
    //Set cnt[] and map[] to all 0s
    for(int j = 0; j<bucket; j++) {
      cnt[j] = map[j] = 0; 
    }
    //count freq and store in cnt[]
    for(int k=0; k<n; k++) {
      cnt[ (src[k] >> i) & mask ]++; 
    }
    //count neg values if last pass 
    if( i == 24 ){
      for(int c=128; c<256; c++){
        negCount += cnt[c]; 
      }
    }
    //cumulative count 
    for(int m=1; m<bucket; m++) {
       map[m] = cnt[m-1] + map[m-1]; 
    } 
    //move to dst 
    for(int p=0; p<n; p++) {
        dst[ map[ (src[p] >> i) & mask]++] = src[p]; 
    }
    //fix positions for negative ints 
    if( negCount > 0 ) {
      int num=n-negCount; 
      for(int i=0; i<negCount; i++){
        src[i]=dst[num+i]; 
      }
      if(negCount != n) {
        int numLeft = n-negCount; 
        for(int i=0; i<numLeft; i++){
          src[ negCount+i ]= dst[i]; 
        }
      }
    }
    //positive ints only 
    else {
      for(int q=0; q<n; q++){
        src[q] = dst[q]; 
      }
    }
  }
}

void print_lst(int *l,int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%d\n",l[i]);
  }
  printf("\n");
}

void init_lst(int *l,int n){
  int i;
  //  int seed = time(0) % 100;	/* seconds since 1/1/1970 */
  //  printf ("seed=%d\n", seed);
  srand(1234);			/* SEED */
  for (i=0; i<n; i++) {
    l[i] = rand(); 
    // neg and pos numbers 
    // l[i] = rand()-rand(); 
  }
}

void float_lst(float *l, int n) { 
  float a = 200.0;
  float b = 100.0; 
    for (int i=0;i<n;i++){
         l[i] =  ((float)rand()/(float)(RAND_MAX))* a-b;
    }
}

void print_float_lst(float *f, int n){
  int i;
  for (i=0; i<n; i++) {
    printf("%f\n",f[i]);
  }
  printf("\n");
}

void self_check(int *lst,int n) {
  int i,j,flag=OK,*lstp;

  lstp = lst;
  for (i=0;i<n-1;i++)
     if (lstp[i] > lstp[i+1]) { flag = NOK; break; }

  if (flag == OK) printf("sorted\n");
  else printf("NOT sorted at %d\n",i);
}

/* End of file */