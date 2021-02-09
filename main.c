#include "main.h"
node *top;

void initialize()
{
    top = NULL;
}

void push(int value)
{
    node *tmp;
    tmp = malloc(sizeof(node));
    tmp -> data = value;
    tmp -> next = top;
    top = tmp;
    display(top);
}

int pop()
{
    node *tmp;
    int n;
    tmp = top;
    n = tmp->data;
    top = top->next;
    free(tmp);
    return n;
}

int Top()
{
    return top->data;
}

int isempty()
{
    return top==NULL;
}

void display(node *head)
{
    if(head == NULL)
    {
        printf("NULL\n");
    }
    else
    {
        printf("%d\n", head -> data);
        display(head->next);
    }
}

void machine(struct string* cmd,int numLines){
    int i = 0;
    int lim = 0;
    int input = 0;
    int push1 = 0;
    int push2 = 0;
    char garbage[MAX];
    char hex[2];
    int *ptr;
    int mPtr;
    initialize();

    while(i < numLines){
        printf("This is the string: %s\n", cmd[i].line);

      if(strncmp(cmd[i].line, "IN",2)==0 ) {
          printf("Please Enter an Integer: ");
          scanf("%d", &input);
          push(input);
          i++;
      }

      else if (strncmp(cmd[i].line, "OUT",3)==0){
          input = pop();
          printf("Popped %d off of the stack\n", input);
          i++;
      }

      else if(strncmp(cmd[i].line, "LIT", 3) == 0 ){
          sscanf(cmd[i].line, "%s" "%d",garbage, &input);
          push(input);
          i++;

      }

      else if(strncmp(cmd[i].line,"DROP",4)==0){
          input = pop();
          i++;
      }

      else if(strncmp(cmd[i].line, "DUP", 3) == 0){
          int lim = 0;
          sscanf(cmd[i].line, "%s" "%d",garbage, &lim);
          ptr = malloc(sizeof(int)*lim);
          for(int j=lim; j >0; --j){
              ptr[j-1]=pop();
          }

          for(int k=0; k< lim; ++k){
              push(ptr[k]);
          }
          for(int l=0; l< lim; ++l){
              push(ptr[l]);
          }
          i++;
          free (ptr);
          ptr =NULL;
      }

      else if(strncmp(cmd[i].line, "SWAP",4)==0){
          push1 = pop();
          push2 = pop();
          push(push1);
          push(push2);
          i++;
      }

      else if(strncmp(cmd[i].line, "ADD",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1 + push2;
          push(input);
          i++;
      }

      else if(strncmp(cmd[i].line, "SUB",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1-push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "MUL",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1 * push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "DIV",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1/push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "MOD",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1%push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "AND",3)==0){
          push1 = pop();
          push2 = pop();
          input = push1&push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "OR",2)==0){
          push1 = pop();
          push2 = pop();
          input = push1|push2;
          push(input);
          i++;
      }
      else if(strncmp(cmd[i].line, "IFEQ",4)==0){
          sscanf(cmd[i].line, "%s" "%d",garbage, &lim);
          printf("This is limit %d\n", lim);
          push1 = pop();
          push2 = pop();
          if(push1==push2) {
              i = lim-1;
          }
          else i++;
      }
      else if(strncmp(cmd[i].line, "IFLT",4)==0){
          sscanf(cmd[i].line, "%s" "%d",garbage, &lim);
          push1 = pop();
          push2 = pop();
          if(push1<push2) {
              i = lim-1;
          }
          else i++;
          push(push2);
          push(push1);
      }
      else if(strncmp(cmd[i].line, "JUMP",4)==0){
          sscanf(cmd[i].line, "%s" "%d",garbage, &lim);
          printf("This is the lim in jump: %d\n", lim);
          i =lim-1;
      }
      /*else if(strncmp(cmd[i].line, "STOR",4)==0){
          sscanf(cmd[i].line, "%s""%s",garbage,hex);
          mPtr = (int)strtol(hex,NULL,16);
          *ptr = mPtr;
          ptr = pop();


      }
      else if(strncmp(cmd[i].line, "LOAD",4)==0){
          sscanf(cmd[i].line, "%s""%s",garbage,hex);
          mPtr = (int)strtol(hex,NULL,16);
          *ptr = mPtr;
          push(ptr);
      }*/

    }



}

int main() {
    FILE *fp;
    char size[255];
    int lim = 0;
    // Give it the full text file path
    fp = fopen("/home/nate/CLionProjects/C/instructions.txt","r");
    if(fp == NULL) {
        printf("Error Opening File\n");
        return -1;
    }
    fgets(size, sizeof(size),fp);
    lim = atoi(size);
    struct string *msg = malloc(lim * sizeof(struct string));
    for(int i = 0; i<lim; i++){
        fgets(msg[i].line , MAX, fp);
    }
    free(fp);
    fp = NULL;
    machine(msg,lim);
    free(msg);
    msg= NULL;
    return 0;
}
