#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1[20];  // in ASM it's 80 bytes of storage and int has 4 bytes size
int list2[20];  // therefore 80/4 = 20
int count = 0;  // global count defined in the memory

void copycodes(char* text, int* list, int* count) {
  while (*text != 0) {     // Loop until the end of the string ('\0') is encountered.  beq $t0, $0, done
      // (lb $t0, 0($a0)) & (sw $t0, 0($a1))
      *list = *text;          // Copy the ASCII value of the current character to the integer array
                        // copies to the element of the destination array
      // (addi	$a0,$a0,1) & (addi	$a1,$a1,4)
      text++;              // Move to the next character in the source string
      list++;              // Move to the next element in the destination array
      
      // addi	$t1,$t1,1  increase the count
      (*count)++;       // Increment the count of characters copied
    }
}

void work() {
    // Calling the copycodes function for text1. jal	copycode ($a0, $a1, $a2)
    copycodes(text1, list1, &count);

    // Calling the copycodes function for text2. jal	copycode ($a0, $a1, $a2)
    copycodes(text2, list2, &count);
}


void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
