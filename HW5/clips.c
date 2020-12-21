#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 256
#define MAX_FIELDS 5 /* 5 fields: views,user,upload_time,duration,title */

struct clip *build_a_lst();
struct clip *append();
int find_length();
void print_lst();
void split_line();

struct clip {
  int views;
  char *user;
  char *upload_time;
  char *duration;
  char *title;
  struct clip *next;
} *head;

int main(int argc, char **argv) {

  if(argc > 1) {
    int n;
    head = build_a_lst(*(argv+1));
    n = find_length(head);
    printf("%d clips\n",n);
    print_lst(head);		/* prints the table */
  }

  else 
    printf("Error: enter a csv file "); 

  return 0;
}

struct clip *build_a_lst(char *fn) {
  FILE *fp;
  struct clip *hp;
  char *fields[MAX_FIELDS];
  char line[LINE_LENGTH];
  hp=NULL;

  fp = fopen(fn, "r"); 

  while( fgets(line, LINE_LENGTH, fp) != NULL) 
  {
      split_line(fields, line); 
      hp = append(hp,fields); 
  }
  fclose(fp); 

  // return the head pointer holding the list
  return hp;
}

/* fields will have five values stored upon return */
void split_line(char **fields, char *line) {
  int i=0;
  char *token, *delim;
  delim = ",\n";
  token = strtok(line, delim);

  while ( token != NULL ) {
      fields[i] = token;  
      token = strtok(NULL, delim); 
      i++;
  }

}

/* set five values into a clip, insert a clip at the of the list */
struct clip *append(struct clip *hp,char **five) {
  struct clip *cp = NULL; 
  struct clip *tp = NULL; 

  int titleL = strlen( five[0] ) + 1; 
  int userL =  strlen( five[1] ) + 1; 
  int uploadL =  strlen( five[2] ) + 1; 
  int durL =  strlen( five[3] ) + 1; 

  tp = malloc( sizeof(struct clip) ); 
  tp->next = NULL; 

  tp->title = malloc( titleL );
  tp->user = malloc( userL );
  tp->upload_time = malloc( uploadL );
  tp->duration = malloc( durL );
  tp->views = atoi ( five[4] ); 

  strcpy( tp->title, five[0] ); 
  strcpy( tp->user, five[1] ); 
  strcpy( tp->upload_time, five[2] ); 
  strcpy( tp->duration, five[3] ); 

  if( hp == NULL ) 
    hp = tp; 
  else {
    cp = hp; 
    while( cp->next != NULL ) {
      cp = cp->next; 
    }
    cp->next = tp; 
  }
  return hp;
}

void print_lst(struct clip *cp) {
     while( cp != NULL ) {
       printf("%s, %s, %s, %s, %d \n",cp->title, cp->user, cp->upload_time, cp->duration, cp->views);
       cp = cp->next; 
     }
}

int find_length(struct clip *hp) {
  int len = 0; 
  struct clip *cp; 
  cp = hp; 

  while( cp != NULL ) {
    len++; 
    cp = cp->next; 
  }
  return len; 
}

/* End of file */