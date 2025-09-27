// sieves

void print_sieves(int max) {
    int is_prime[max + 1];  // Allocate memory on the stack

    // Initialize the array with all values set to 1 (considered as prime initially)
    for (int i = 0; i <= max; i++) {
        is_prime[i] = 1;
    }

    // 0 and 1 are not prime numbers
    is_prime[0] = is_prime[1] = 0;

    // Apply Sieve of Eratosthenes
    for (int i = 2; i * i <= max; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max; j += i) {
                is_prime[j] = 0;  // Mark multiples of i as non-prime
            }
        }
    }

    // Print the prime numbers using the provided print_number function
    for (int i = 2; i <= max; i++) {
        if (is_prime[i]) {
            print_number(i);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        print_sieves(atoi(argv[1]));
    } else {
        fprintf(stderr, "Please state an integer number.\n");
        return 1;  // Return an error status
    }

    return 0;
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        int n = atoi(argv[1]);
        if (n >= 2) {
            print_sieves(n);
        } else {
            printf("Please provide a positive integer greater than or equal to 2.\n");
        }
    } else {
        printf("Please state an integer number.\n");
    }

    return 0;
}

// sieves-heap

void print_sieves(int max) {
    int *is_prime = (int *)malloc((max + 1) * sizeof(int));  // Allocate memory on the heap

    if (is_prime == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Initialize the array with all values set to 1 (considered as prime initially)
    for (int i = 0; i <= max; i++) {
        is_prime[i] = 1;
    }

    // 0 and 1 are not prime numbers
    is_prime[0] = is_prime[1] = 0;

    // Apply Sieve of Eratosthenes
    for (int i = 2; i * i <= max; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j <= max; j += i) {
                is_prime[j] = 0;  // Mark multiples of i as non-prime
            }
        }
    }

    // Print the prime numbers using the provided print_number function
    for (int i = 2; i <= max; i++) {
        if (is_prime[i]) {
            print_number(i);
        }
    }

    // Release allocated memory
    free(is_prime);
}

void print_sieves(int n) {
    // Initialize the array on the heap
    int a = n - 1;
    char *numbers = malloc(sizeof(char) * a);

    // Check if memory allocation was successful
    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Populate the array with 1's (True values)
    for (int i = 0; i < a; i++) {
        numbers[i] = 1;
    }

    // The algorithm starts here!
    // Check the factors up to the square of the input, since that is
    // the last number that can be squared to produce the input.
    for (int i = 0; i <= (int)sqrt(n); i++) {
        if (numbers[i] == 1) { // Adjust index to start from 2
            for (int j = (i + 2) * (i + 2); j <= n; j += (i + 2)) { // For every multiple of that number 
                numbers[j - 2] = 0; // Mark it as non-prime (adjusting index to start from 2)
            }
        }
    }

    // Printing out the true values from the array, starting from the "2"
    for (int i = 0; i < a; i++) {
        if (numbers[i] == 1) {
            print_number(i + 2); // Adjust index to print the actual value
        }
    }

    // Free the dynamically allocated memory
    free(numbers);
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        int n = atoi(argv[1]);
        if (n >= 2) {
            print_sieves(n);
        } else {
            fprintf(stderr, "Please provide a positive integer greater than or equal to 2.\n");
            exit(EXIT_FAILURE);
        }
    } else {
        fprintf(stderr, "Please state an integer number.\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}


// pointers

int list1[20];  
int list2[20];  
int count = 0;

void copycodes(char* src, int* dest) {
    char* src_ptr = src;
    int* dest_ptr = dest;

    while (*src_ptr != '\0') {
        *dest_ptr = (int)(*src_ptr);
        src_ptr++;
        dest_ptr++;
        count++;
    }
}

void work() {
    char* text1_ptr = text1;
    char* text2_ptr = text2;
    int* list1_ptr = list1;
    int* list2_ptr = list2;

    // Calling the copycodes function for text1
    copycodes(text1_ptr, list1_ptr);

    // Calling the copycodes function for text2
    copycodes(text2_ptr, list2_ptr);
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
