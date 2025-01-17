#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// For the inverse adjacency matrix
typedef struct DATA *P_DATA;
struct DATA {
	int pageID;
	P_DATA link;
};
typedef struct IALIST *P_IALIST;
struct IALIST {
	int numOutlinks;
	P_DATA first;
};

double*		allocateVector(int, double);
P_IALIST	loadInverseAdjacencyList(char*, int);
void		insert(P_DATA*, int);
double*		calculatePageRank(double*, P_IALIST, int, double, int);
void		writeVector(char*, double*, int);
void		printTopK(double*, int, int);
void		freeInverseAdjacencyList(P_IALIST, int);
void		printVector(double*, int);

int main(int argc, char *argv[]) {
	// argv[0] = [program name]
	// argv[1] is the file name that contains the adjacency matrix
	// argv[2] is the number of pages in the given Web graph
	// argv[3] is the value of damping factor (normally set to 0.85)
	// argv[4] is the number of iteration (in this assignment, set to 100)
	// argv[5] is the file name in which you want to record the PageRank scores
	// argv[6] specifies top K

	// Initialize variables from the command-line arguments
	char* inputFile = argv[1];
	int numPages = atoi(argv[2]);
	double d = atof(argv[3]);
	int numIteration = atoi(argv[4]);
	char* outputFile = argv[5];
	int topK = atoi(argv[6]);

	// Allocate and initialize a vector for PageRank
	double* vector = allocateVector(numPages, 1.0/numPages);

	// Load the inverse adjacency lists from [inputFile]
	P_IALIST invAdjLists = loadInverseAdjacencyList(inputFile, numPages);

	// Time variables to evalute the processing time
	time_t beginTime = 0, terTime = 0;

	// Record the CPU clock for beginning the calculation
	beginTime = clock();

	/* ASSIGNMENT FUNCTION NO.3*/
	// Calculate the PageRank scores and store them in the vector
	vector = calculatePageRank(vector, invAdjLists, numPages, d, numIteration);

	// Record the CPU clock for terminating the calculation
	terTime = clock();

	// Print the processing time
	printf("Elapsed time is: %f sec\n", (double)(terTime-beginTime)/(double)CLOCKS_PER_SEC);

	// Output the PageRank scores
	writeVector(outputFile, vector, numPages);

	// Print out the top k ranked pages and the corresponding scores
	printTopK(vector, numPages, topK);

	// Free the allocated vector and inverse adjacency list
	free(vector);
	freeInverseAdjacencyList(invAdjLists, numPages);

	return 0;
}

// Returns the pointer of a double-typed array
// int n: number of elements in the vector
// double initValue: initial value for each element
double* allocateVector(int n, double initValue) {
	// A variable for iteration
	int i;

	// Allocate a vector
	double* vector = (double*)malloc(sizeof(double)*n);

	// Initialize each element in the vector with the default value;
	for (i = 0; i < n; i++) vector[i] = initValue;

	// Return the vector
	return vector;
}

// Returns the pointer of an IALIST array with n elements
// Each element i contains:
//     int numOutlinks: the number of outlinks for the page i
//     P_DATA first: the first pointer of the linked list for inlink pages
// char* inputFile: file name concatenated by its absolute or reletive path
// int n: number of pages in the given Web graph
P_IALIST loadInverseAdjacencyList(char* fileInput, int n) {
	int i, j;
	char line[10000];
	FILE *stream;
	int pageID;
	char* element;

	// Allocate an IALIST-typed array with n elements
	P_IALIST invAdjLists = (P_IALIST)malloc(sizeof(*invAdjLists)*n);

	// Initialize each element in the array
	for (i = 0; i < n; i++) {
		invAdjLists[i].numOutlinks = 0;
		invAdjLists[i].first = NULL;
	}

	// Open file stream
	stream = fopen(fileInput, "r");
	if (stream == NULL) {
		printf("File open error\n");
		exit(1);
	}

	// For each page i, generate a linked list for inlink pages
	i = 0;
	while (!feof(stream)) {
		if (fgets(line, 10000, stream) == NULL) break;
		element = strtok(line, ": ");
		while ((element = strtok(NULL, " "))) {
			pageID = atoi(element);
			if (pageID != -1) {
				insert(&invAdjLists[i].first, pageID);
				invAdjLists[pageID].numOutlinks++;
			}
		}
		i++;
	}
	fclose(stream);

	// For each page i,
	for (i = 0; i < n; i++) {
		// If page i has no outlink pages,
		// then generate 'virtual' links to every page
		if (invAdjLists[i].numOutlinks == 0) {
			invAdjLists[i].numOutlinks = n;
			for (j = 0; j < n; j++) {
				insert(&invAdjLists[j].first, i);
			}
		}
	}

	// Return the inverse adjacency lists
	return invAdjLists;
}

// Help fuction to insert a data in the linked list
// called by the loadInverseAdjacencyList fuction
// This function is slighed modified from the insert function in page 153 of the text book
// P_DATA *first: pointer of the first data in the linked list
// int pageID: page id (index in the array)
void insert(P_DATA *first, int pageID) {
	P_DATA temp = (P_DATA)malloc(sizeof(struct DATA));
	temp->pageID = pageID;

	if (*first) {
		temp->link = *first;
		*first = temp;
	} else {
		temp->link = NULL;
		*first = temp;
	}
}

// Returns a vector that contains the PageRank scores for each page i
// double* vector: vec(R)
// P_IALIST invAdjLists: inverse adjacency lists
// int n: number of pages (number of elements in the [invAdjLists])
// double d: damping factor (normally set to 0.85)
// int numIteration: number of iteration
double* calculatePageRank(double* vector, P_IALIST invAdjLists, int n, double d, \
	int numIteration) {
	// ASSIGNMENT FUNCTION NO.3
	// PLEASE RE-IMPLEMENT THE BODY
	//Data Structure
	double rank;
	double tempVector [n];
	P_DATA node;

	//Algorithms
	//for numIterations
	int m;
	for (m = 0; m < numIteration; m++)
		{
		//for every vertex
		int i;
		for (i = 0; i < n; i++)
			{
			//printf("\n\nfor %d\n", i);

			//Calculate page rank
			//initialize rank = 0.0
			rank = 0.0;
			//for every inlink
			node = invAdjLists[i].first;
			while (node != NULL)
				{
				//printf("	inlink: %d\n", node->pageID);
				//rank += inlink's weight /inlink's outlinks
				rank += vector[node->pageID] / invAdjLists[node->pageID].numOutlinks;
				node = node->link;
				}
			//multiply by d and etc
			rank = d * rank + (1.0 - d) * (1.0 / n);
			//assign rank to tempVector
			tempVector[i] = rank;
			} //for every vertex

		//Assign tempVector to vertex node
		for (i = 0; i< n; i++)
			{
				vector[i] = tempVector[i];
			}
		}//for numIterations

	return vector;
}

// Writes the [vector] in [outputFile]
// char* outputFile: file name concatenated by its absolute or reletive path
// double* vector: vector to be printed
// int n: number of element in the vector
void writeVector(char* outputFile, double* vector, int n) {
	char strElement[32];
	FILE *stream;
	int i;

	// Open file stream withe [outputFile] to write the vector
	stream = fopen(outputFile, "wb");
	if (stream == NULL) {
		printf("Output stream is NULL. Program terminates.\n");
		exit(1);
	}

	// For each element in the vector
	for (i = 0; i < n; i++) {
		// Generate a string that represents the element
		sprintf(strElement, "%f\n", vector[i]);

		// Write the string
		if (fputs(strElement, stream) == EOF) {
			printf("fputc() returns NULL. Program terminates.\n");
			exit(1);
		}
	}

	// Close the file stream
	fclose(stream);
}

// Prints the top k ranked pages and the corresponding scores
// double* vector: vector that contains the PageRank scores
// int topK: top k
void printTopK(double* vector, int n, int topK) {
	// Define a structure for sorting
	typedef struct _ID_SCORE {
		int pageID;
		double score;
	} ID_SCORE;

	int i, j;
	ID_SCORE* rank;
	int index;
	ID_SCORE temp;

	// If topK is not positive or is greater than n,
	// then do nothing
	if ((topK <= 0) || (n < topK)) return;

	// Allocate an array of ID_SCORE
	rank = (ID_SCORE*)malloc(sizeof(ID_SCORE)*n);

	// Initilize the array
	for (i = 0; i < n; i++) {
		rank[i].pageID = i;
		rank[i].score = vector[i];
	}

	// Selection Sort
	for (i = 0; i < n; i++) {
		index = i;

		for (j = i; j < n; j++) {
			if (rank[index].score < rank[j].score) index = j;
		}

		temp = rank[i];
		rank[i] = rank[index];
		rank[index] = temp;
	}

	// Print the top k ranked pages and the corresponding scores
	printf("Top-%d [pageID: score]\n", topK);
	for (i = 0; i < topK; i++) {
		printf("%4d: %f\n", rank[i].pageID, rank[i].score);
	}

	// Free the allocated rank vector
	free(rank);
}

// Free allocated memory in the inverse adjacency lists
// P_IALIST invAdjLists: IALIST-typed array
// int n: number of elements in the [invAdjLists]
void freeInverseAdjacencyList(P_IALIST invAdjLists, int n) {
	int i;
	P_DATA pData;
	P_DATA temp;

	// For each element i,
	for (i = 0; i < n; i++) {
		// Free allocated data in the linked list
		pData = invAdjLists[i].first;
		while (pData) {
			temp = pData->link;
			free(pData);
			pData = temp;
		}
	}

	// Free the IALIST-typed array
	free(invAdjLists);
}

void printVector(double* vector, int n) {
	int i;
	for (i = 0; i < n; i++) printf("%f\n", vector[i]);
}
