#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
FILE *in; //for input file
FILE *out; //for output file
int cylinder[25]; //array to hold the cylinders
int head = 33;

void do_FCFS(int arr[], int num); //function to do FCFS
void do_SCAN(int arr[], int num); //function to do SCAN
void do_CSCAN(int arr[], int num); //function to do CSCAN

int main(int argc, char *argv[]){
	in = fopen("input.txt", "r");
	out = fopen("output.txt", "w+");
	char arr[SIZE];
	
	int i = 0;
	while (fgets(arr, SIZE, in)){
		cylinder[i] = atoi(arr); //place the cylinders from the input file into the array
		i++; //increment i
	}
	
	fprintf(out, "\n");
	do_FCFS(cylinder, head); //call FCFS
	fprintf(out, "\n");
	do_SCAN(cylinder, head); //call SCAN
	fprintf(out, "\n");
	do_CSCAN(cylinder, head); //call CSCAN

	return 0;
}

void do_FCFS(int arr[], int num){
	fprintf(out, "FCFS Algorithm\n");
	fprintf(out, "Initial head position = %d\n", num);
	fprintf(out, "Seek Sequence is:\n");
	int start = num;
	int head_move = 0;
	int j;
	for (j = 0; j < 25; j++){
		fprintf(out, "%d\n", arr[j]);
		head_move = head_move + abs(start - arr[j]);
		start = arr[j];
	}
	fprintf(out, "Total head movement for FCFS = %d\n", head_move);
}


void do_SCAN(int arr[], int num){
	fprintf(out, "SCAN Algorithm\n");
	fprintf(out, "Initial head position = %d\n", num);
	fprintf(out, "Seek Sequence is:\n");
	int start = num;
	int head_move = 0;
	int count = 0;
	//int first = arr[0];
	int k;
	int n;
	int s;
	
	//find number of elements less than num
	for (s = 0; s < 25; s++){
		if (arr[s] <= num){
			count++;
		}
	}
	
	//sort array in increasing order
	for(k = 0; k < 25; k++){
		for (n = 0; n < 25; n++){
			if (arr[k] < arr[n]){
				int tmp = arr[k];
				arr[k] = arr[n];
				arr[n] = tmp;
			}
		}
	}
	
	//now make separate array for elements less than the head
	int temp[count];
	int m = 0;
	int j;
	for (j = 0; j < count; j++){
		if (arr[j] <= num){
			temp[m] = arr[j];
			m++;
		}
	}
	
	//now print out elements
	int a;
	for (a = count - 1; a >= 0; a--){
		fprintf(out, "%d\n", temp[a]);
		head_move = head_move + abs(start - temp[a]);
		//printf("Head Move = %d\n", head_move);
		start = temp[a];
	}
	
	head_move += start;
	
	//now print out elements larger than num
	int b;
	int zero = 0; //this is used to check that its at zero
	for (b = count; b < 25; b++){
		fprintf(out, "%d\n", arr[b]); //print out elements
		if (zero == 0){ //if transitioning part
			head_move = head_move + arr[b]; //instead of subtracting the cylinders, add the next cylinder
			start = arr[b]; //the next cylinder now becomes the current cylinder
			zero = 1; //set zero to 1
		}
		else{
			head_move = head_move + abs(start - arr[b]);
			start = arr[b];
		}
	}
	fprintf(out, "Total head movement for SCAN = %d\n", head_move);
}

void do_CSCAN(int arr[], int num){
	fprintf(out, "C_SCAN Algorithm\n");
	fprintf(out, "Initial head position = %d\n", num);
	fprintf(out, "Seek Sequence is:\n");
	int start = num;
	int head_move = 0;
	int count = 0;
	//int first = arr[0];
	int k;
	int n;
	int s;
	
	//find number of elements less than num
	for (s = 0; s < 25; s++){
		if (arr[s] <= num){
			count++;
		}
	}
	
	//sort array in increasing order
	for(k = 0; k < 25; k++){
		for (n = 0; n < 25; n++){
			if (arr[k] < arr[n]){
				int tmp = arr[k];
				arr[k] = arr[n];
				arr[n] = tmp;
			}
		}
	}
	
	//now make separate array for elements less than the head
	int temp[count];
	int m = 0;
	int j;
	for (j = 0; j < count; j++){
		if (arr[j] <= num){
			temp[m] = arr[j];
			m++;
		}
	}
	
	//now print out elements larger than num
	int b;
	
	for (b = count; b < 25; b++){
		fprintf(out, "%d\n", arr[b]); //print out elements
		head_move = head_move + abs(start - arr[b]);
		start = arr[b];
	}
	head_move = head_move + (99 - start);
	head_move += 99; //now at 0
	
	//now print out elements less than num
	int a;
	int zero = 0; //this is used to check that its at zero
	for (a = 0; a < count; a++){
		fprintf(out, "%d\n", temp[a]);
		
		if (zero == 0){ //if transitioning part
			head_move = head_move + temp[a]; //instead of subtracting the cylinders, add the next cylinder
			start = temp[a]; //the next cylinder now becomes the current cylinder
			zero = 1; //set zero to 1
		}
		else{
			head_move = head_move + abs(start - temp[a]);
			start = temp[a];
		}
	}
	
	fprintf(out, "Total head movement for C_SCAN = %d", head_move);
}
