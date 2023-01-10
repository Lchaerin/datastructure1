#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/* 
    [Task 1] Choose the TIGHT bound of the following arraySum function
    
    *arraySum*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        Output
        - int: Sum of given array A
	int arraySum(int n, int* A) {
	    int currSum = 0;
	    for (int i = 0; i < n; i++)
	        currSum += A[i];
	    return currSum;
	}


    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
    int answer = 2;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following primeSearch function

    *primeSearch*
        Input
        - int n: input number for ending range
        Output
        - int numPrimes: The total number of prime numbers less than n
	int primeSearch(int n) {
	    int numPrimes = 0;
	    int ctr = 0;
	    for (int i = 0; i < n; i++) {
	        for(int j = 2; j <= sqrt(i); j++) {
	            if(i % j == 0) {
			ctr++;
			break;
	            }
	        }
		if(ctr == 0 && i > 1)
	            numPrimes++;
	        ctr=0;
	    }
	    return numPrimes;
	}


    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n^(1/2) )
        4: O( n*n^(1/2) )
*/
void task_2(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the list.
        An user can insert or delete an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,index): insert “# of elements in the current list” at the
   index in the list. index indicates zero-based index.
        - (‘delete’,index): delete an element at the index in the list. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/

void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer="";
  struct NODE{
    int data;
    NODE* link;
  };
  NODE *dummy_node=new NODE();
  dummy_node->data=0;//list의 길이 저장
  dummy_node->link=NULL;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int index = instr_seq->instructions[i].value;//
    if (command.compare("insert") == 0) {
      if(index>dummy_node->data){
        answer="error";
        break;
        }
      else{
        
        if(dummy_node->data==0){//list가 비어있을 때
          NODE *temp=new NODE();
          dummy_node->link=temp;
          temp->data=dummy_node->data;
          temp->link=NULL;
          dummy_node->data++;
        }
        else{//list의 element가 1개 이상일 때
          if(index==0){
            NODE *temp=new NODE();
          temp->link=dummy_node->link;
          dummy_node->link=temp;
          temp->data=dummy_node->data;
          dummy_node->data++;
          }
          else{
          int num=0;
          NODE *temp=new NODE();
          NODE *temp2=new NODE();
          NODE *pre=new NODE();
          for (temp = dummy_node->link; num < index; num++)
            {
              pre=temp;
              temp=temp->link;
            }
              temp2->link = pre->link;
	          	pre->link = temp2;
              temp2->data=dummy_node->data;
              dummy_node->data++;
              }
        }
      }

      
    }
    else if (command.compare("delete") == 0) {
      if(index>=dummy_node->data){
        answer="error";
        break;
      }
      else{
        if(dummy_node->data==1){//list element가 1개일 때
          dummy_node->link=NULL;
          dummy_node->data=0;
        }
        else {
          if(index==0){
            dummy_node->link=dummy_node->link->link;
            dummy_node->data--;
          }
          else{
          int num=0;
          NODE *pre=new NODE();
          pre=dummy_node->link;
            while(num<index-1){
              pre=pre->link;
              num++;
            }
            if(pre->link->link=NULL){
              pre->link=NULL;
              dummy_node->data--;
            }
            else{
              pre->link=pre->link->link;
              dummy_node->data--;
            }
        }}
      }
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  
  if(answer!="error"){
  NODE *temp=new NODE();
  for(temp=dummy_node->link;temp->link!=NULL;temp=temp->link){
    if(answer==""){
      answer=to_string(temp->data);
    }
    else{
      answer=answer+" "+to_string(temp->data);
    }
  }
  answer=answer+" "+to_string(temp->data);}

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   stack is empty, and the “top” operation is called, then print “-1”, If “pop”
   operation from the empty stack then print “error”

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is
   always positive)
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack
*/

void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer="";
  struct NODE{
    int data;
    struct NODE* next;
  };
  struct STACK{
    int count;
    NODE* top;

  };

  STACK *stack=new STACK();
	// 초기화
	stack->count = 0;
	stack->top = NULL;

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int index = instr_seq->instructions[i].value;
    if (command.compare("push") == 0) {
      
        NODE *temp=new NODE();
        temp->data=index;
        temp->next = stack->top;
        stack->top = temp;
        stack->count++;
      

    } else if (command.compare("pop") == 0) {
      if(stack->count==0){
        answer="error";
        break;
      }
      else{
        NODE *temp=new NODE();
        temp=stack->top;
        stack->top=temp->next;
        stack->count--;
        delete temp;
      }

    } else if (command.compare("top") == 0) {
      if(answer==""){
        if(stack->count==0){
          answer=to_string(-1);
        }else{
        answer=to_string(stack->top->data);
        }
      }
      else{
        if(stack->count==0){
          answer=answer+" "+to_string(-1);
        }else{
      answer=answer+" "+to_string(stack->top->data);}
      }

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Queue

    Description:
        Implement a function which shows the value of a queue after the sequence
   of arbitrary queue operation. If the queue after the operations is empty,
   print “empty”. If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the queue from the head to the tail, in a string separated
   with spacebar
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/

void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer="";
  struct NODE{
    int data;
    struct NODE* next;
  };
  struct QUEUE{
    NODE* front;
    NODE* rear;
  };
  QUEUE *queue=new QUEUE();
	// 초기화
	queue->front = NULL;
	queue->rear = NULL;
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;

    if (command.compare("enqueue") == 0) {
      NODE *node=new NODE();
      if(queue->front!=NULL){
        queue->rear->next=node;
        node->next=NULL;
        node->data=value;
        queue->rear=node;
        //cerr << "enque: " << queue->rear->data << endl;
      }
      else{
        queue->front=node;
        queue->rear=node;
        node->next=NULL;
        node->data=value;
        //cerr << "enque: " << queue->rear->data << endl;
      }

    } else if (command.compare("dequeue") == 0) {
      if(queue->front==NULL){
      answer="error";
        break;
      }
      else if(queue->front==queue->rear){
        queue->front=NULL;
        queue->rear=NULL;
      }
      else{
        queue->front=queue->front->next;
      }

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  if(answer!="error"){
  NODE *node=new NODE();
  node=queue->front;
    if(queue->front==NULL){
      answer="empty";
      }
  else{
    answer=to_string(node->data);
  while(node->next!=NULL){
    node=node->next;
      answer=answer+" "+to_string(node->data);
  }

  }
  delete node;}
  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Circular Queue

    Description:
        - a.	Implement a function which shows the value in the circular queue
   from the head to tale. If “enqueue” operates on full or “dequeue” operates
   on an empty queue, no change would happen.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue
        -(‘dequeue’,NULL): dequeue integer into the current queue

    Output:
        - Values in the queue from the head to the tail, in a size of 4.
   string separated with the spacebar, empy memory shows NULL -	No
   pointer movement if dequeue on empty, enqueue on full queue

*/

void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer="";
  int queue_size = 4;
  struct NODE{
    int data=0;
    bool full=false;
    struct NODE* next;
  };
  struct QUEUE{
    NODE* front;
    NODE* rear;
    int element;
  };

  QUEUE *queue=new QUEUE();
  NODE *basic=new NODE[queue_size];
  
	queue->front = basic;
	queue->rear = basic;
  queue->element=0;
  for(int i=0;i<queue_size-1;i++){
    basic->next=(basic+1);
    basic=basic->next;
  }
  basic->next=queue->front;

	// 초기화
  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    int value = instr_seq->instructions[i].value;
    if (command.compare("enqueue") == 0) {
      if((queue->rear->next!=queue->front)||(queue->element<4)){
        if(queue->element==0){
          queue->front->data=value;
          queue->front->full=true;
        queue->element++;
        }
        else{
        queue->rear=queue->rear->next;
        queue->rear->data=value;
        queue->rear->full=true;
        queue->element++;
        }
        }
    }
    else if (command.compare("dequeue") == 0) {
      if(queue->element!=0){
      queue->front->data=0;
      queue->front->full=false;
      queue->front=queue->front->next;
      queue->element--;
      }
    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }
  NODE *temp=new NODE();
  temp=queue->front;
  for(int j=0;j<queue_size;j++){
    if(temp->full){
      if(temp==queue->front){
        answer=to_string(temp->data);
      }
      else{
        answer=answer+" "+to_string(temp->data);
      }
      
      temp=temp->next;
    }
    else{
      break;
    }
  }
  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);

    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}

