#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 50

typedef struct data {			//struct links wordarr with its size and the allocated memory
    char **wordarr;
    int size;
    int capacity;
} data_t;

typedef struct freq{			//frequency of each letter
	char c;
	int f; 	//counter-frequency

}freq;


int alloc_data(data_t *dat, int capacity);
void strtok_example(data_t *dat);
void update_File(data_t *dat, char *file);		//
int insert_at_table(char *word, data_t *dat);	//
int find_pos(data_t *dat); 					//
void sort(data_t *dat, int pos ,char *word);		//
char frequency(char **same_size, int size);
//void malloc_string(char **array);
int init_same_size(char **array, data_t *dat, int num_let);
int delete_words(char **same_size,int asciinum, int columns);
int delete_w(char **same_size,int asciinum, int columns);
void game_over(data_t *dat);
void dealloc_data(data_t *dat);


int main(){

	data_t lexicon;
	int flag=0;
	int del_1,del_2;
	int position;
	char letter;
	int answer;
	int num_let; 
	char **same_size;

	FILE *fp;

    int capacity=20;
	int times;
	int size;
    int choice = 3;
    int i=0;
    int pos;
   char platform[100];

    char *input;
    
    fp = fopen("lexicon.txt", "r");				//fp = fopen("dictionary.txt", "r"); 				file
    if (fp == NULL) {									//verify if file is open
        fprintf(stderr, "File not found\n");
        exit(1);
    }

    input=(char*)malloc(sizeof(char)*20);  //to input einai h leksh poy vazei o xrhsths
      

    do{
        printf("\n\n----MENU----\n\n");
        printf("(press 0 for EXIT)\n");
		printf("1. Dictionary Build\n");

        printf("2. Let's play\n");
        scanf("%d", &choice);

        switch (choice){

        	case (0):
        		exit(0);
            case (1):
            	printf("you chose 1\n\n");	// we should put functions in this place


            	int a = alloc_data(&lexicon, capacity);

            	strtok_example(&lexicon);


            	printf("Do you want to insert a new word?\n\n");
					printf("please give word:");
					scanf("%s", input);



            	printf("%s\n", input);
            	

            	size = insert_at_table(input, &lexicon);
            	
                       	
            	pos = find_pos(&lexicon);
            	
            	sort(&lexicon, pos, input);
            	
            	update_File(&lexicon,"lexicon.txt");	// in case the game is lost this function is called
            									 
            	
            	
                        
                break;
            case (2):									////////////////////////////////////////	

            	printf("Give a number of letters\n");
            	scanf("%d", &num_let);

				
            	for(i = 0; i < num_let; i++){				            	
            		platform[i]='-';
            		printf("%c",platform[i]);
				}
				printf("\n");


			//	malloc_string(same_size);
			
					same_size= (char**)malloc(sizeof(char*)*50);
					for(i = 0; i< 20 ; i++){
						if((same_size[i]= (char*)malloc(sizeof(char)*50)) == NULL){
							printf("MEMORY ALLOCATION ERROR");
							//return;
						}
					}//end for
					
				size = init_same_size(same_size, &lexicon, num_let);
						
										
				do{
						
				
                if (size==0){
                	printf("The user won\n\n");
                	break;
				}				
				else if	(size == 1){
					printf("Is %s the word you are thinking about?\n", same_size[0]);
					scanf("%d", &answer);
					
					do{
					
						if(answer==1){		
							flag = 1;   // nikaei o ypologisths
							printf("The pc won\n\n");
						}else if(answer==0){
							printf("The user won\n\n");
							game_over(&lexicon);
						}else{						
							printf("Answer is not 1 or 0\n\n");		
							
						}
					
					}while((answer!=1) || (answer!=0));
					
				}
												
				
				letter = frequency(same_size, size);	//it suggests a letter and returns it
				
				printf("Does this letter exist in the word? Press 1 for Yes and 0 for No\n\n");
            	scanf("%d", answer);            	
				
				if (answer==1){
					printf("How many times does this letter exist?\n\n");
					scanf("%d", times);
														
					for (i=0; i<= times; i++){	
														
						printf("What is the position of character?\n\n");					
						scanf("%d", position);  
						
						platform[position]=letter;																										
					
					}
				
					for (i=0; i<= num_let; i++){
						printf("/n%c",platform[i]);
					}				
				
				
					del_1 = delete_w(same_size,letter,size);			// deletes the words which don't have the suggested letter
			
								
				}
				else{						// deletes the words which have the suggested letter but there isn't in the word
					del_2 = delete_words(same_size,letter,size);
						
							
			}
			
			i++;
			
			}while(i<6);	//meta apo 6 prospatheies xanei
			
			
			if (flag==0){
				printf("The user won. The tries have ended\n");
				game_over(&lexicon);
			}
			
			
			break;  
			
            default:
                printf("Wrong choice.Enter Again\n\n");
                break;      

    } 
	
	}while(choice!=0);	// Number of times the menu will appear. After a correct guess it appears as well.
	dealloc_data(&lexicon);
    return 0;
}


int alloc_data(data_t *dat, int capacity){
    int i;

    dat->capacity = capacity;
    dat->size = 0;
    if (!(dat->wordarr = (char**)malloc(sizeof(char*) * dat->capacity))){

		printf("---===ERROR===---\n Not enough memory\n");
		return 1;
	}//end if
    for (i=0; i<dat->capacity; i++) {
        dat->wordarr[i] = (char*)malloc(sizeof(char) * WIDTH);
    }
}//end alloc_data



void update_File(data_t *dat, char *file){

    int i=0;
	FILE *fp;
	//it asks it from the user and puts it in the buffer with dynamic allocation 


    fp = fopen(file, "w");
    

    if (fp != NULL){
    	while(i<dat->size){		
	    	fputs(" ",fp);
	        fputs(dat->wordarr[i], fp);		       
	        i++;
    	}
    	
    	 fclose(fp);
    	
    }
    
    
    //diavazei tis lekseis apo to file
    fp = fopen(file,"r");
	int c;
   while(1) {
      c = fgetc(fp);
      if( feof(fp) ) {
         break ;
      }
      //printf("%c", c);
   }
   fclose(fp);

}


void strtok_example(data_t *dat){
    int i;
//    data_t dat;
    FILE *fp;
    char buffer[10000];
    char *tok;

//    alloc_data(&dat, 5);

    fp = fopen("lexicon.txt", "r");
    if (fp == NULL) {									//verify if file is open
        fprintf(stderr, "File not found\n");
        exit(1);
    }

    fgets(buffer, 10000, fp);							//reads string from file

    tok = strtok(buffer, " .,!");
    while (tok != NULL) {
        if (dat->size >= dat->capacity) {
            dat->capacity *= 2;							//check if inside limits
            dat->wordarr = (char**)realloc(dat->wordarr, sizeof(char*) * dat->capacity);	//if not realloc
            for (i=dat->capacity/2; i<dat->capacity; i++) {
                dat->wordarr[i] = (char*)malloc(sizeof(char) * WIDTH);
            }
            printf("realloc\n");
        }//end if
        strcpy(dat->wordarr[(dat->size)++], tok);			//add each word into array
        tok = strtok(NULL, " .,!");
    }

    fclose(fp);

    for (i=0; i<dat->size; i++) {						//type array
        printf("[%s]\n", dat->wordarr[i]);
    }

 //   dealloc_data(&dat);
}//end strtoc_example


int insert_at_table(char *word, data_t *dat){

    int i;

    for (i=0; i<dat->size; i++) {
        printf("%s\n", dat->wordarr[i]);
    }

   	printf("Inside insert at table");
	strcpy(dat->wordarr[dat->size], word);
	printf("\nword =%s size=%d\n" , dat->wordarr[dat->size], dat->size);
    dat->size++;
    
    return dat->size;


}//end insert_at_table



int find_pos(data_t *dat){

	char *des_word,												//new word
 		*prev,													//temp previous word
 		*next;													//temp next word
	int next_len, 											//length of next
	length,													//temps length
	temp_len,												// temp of prev
	comp_prev,												//result when compare prev with des_word
	comp_next;												//result when compare next with des_word
	int i = 0;
	int pos = 0;

	des_word = dat -> wordarr[(dat->size)-1];
	length = strlen(des_word);

	while (i<(dat->size)-1){

		temp_len=strlen(dat->wordarr[i]);

		if(length < temp_len)
		{
			// new word length < old word length
			pos = i;
			break;
		}
		else if(length > temp_len)
		{
			// new word length > old word length
			i++;
			if(i+1 == dat->size)
			{
				pos = i;
				break;
			}
		}
		else if(length == temp_len)
		{
			// new word length == old word length
			int res = strcmp(des_word, dat->wordarr[i]);
			if(res == -1)
			{
				// new word < old word
				pos = i;
				break;
			}
			else if(res == 1)
			{
				// new word > new word
				i++;
				if(i+1 == dat->size)
				{
					pos = i;
					break;
				}
			}
			else if(res == 0)
			{
				// new word = old word
				pos = -1;
				break;
			}
		}
		
    }

    printf("pos = %d\n", pos);
	return pos;
}//end find_pos


void sort(data_t *dat,int pos, char *word){
	int i;
	int assist;
	char *temp_word;
	temp_word = (char*)malloc(sizeof(char)*20);

	if (pos == -1){
		dat->size--;
		return ;
	}//end if
	printf("in sort function\n");
	printf("%d\n", dat->size);

//	dat->size++;
	assist=dat->size;
	
	if(dat->size == dat->capacity)
	{
		// array is full
		printf("in function - sort: Maximum capacity reached.\n");
		// make array bigger
		char **newData;
		newData = realloc(dat->wordarr, sizeof(char*)*dat->capacity*2);
		if(!newData)
		{
			printf("in function - sort: Realloc failed.\n");
			return;
		}
		dat->wordarr = newData;
		dat->capacity = 2*dat->capacity;
		// init new array values
		for(i = dat->size; i < dat->capacity; i++)
		{
			dat->wordarr[i] = (char *) malloc(20*sizeof(char));
			
		}		
	}

	for(i = dat->size;i > pos;i--)
    {
        strcpy(dat->wordarr[i] , dat->wordarr[i-1]);
        	}
	
    strcpy(dat->wordarr[pos], word);
    

}//end sort


char frequency(char **same_size, int size){  

	freq *letters_freq;														//create a freq struct

		letters_freq=(freq*)malloc(sizeof(freq)*26);							//memory allocation

	int i;
	int asc=97;
	int rows,
		columns;
	
	
	for(i=0;i<26;i++){														//loop for every letter of alphabet
	
		 columns=0;
		 rows = 0;
		
		
		letters_freq[i].c=asc;													//characters should start with letter a
		letters_freq[i].f=0;
			
		
			while(rows<size){													//for every word
				int j = (strlen(same_size[rows]-1));
				
				while(columns<j){												//search every char
					printf("table char =%c char to be found %c\n",same_size[rows][columns], asc );
					if(same_size[rows][columns]==asc){
						printf("%c\n",same_size[rows][columns] );
						letters_freq[i].f++;									//if match f++
						printf("freq = %d letter = %c" , letters_freq[i].f, asc);
					}//end if
				columns++;
		
				}//end inner while
			rows++;
			}//end while
	
		
	asc++;
	}//end for
	printf("\n this is the letter: %c and this is the frequency: %d \n",letters_freq[i].c,letters_freq[i].f);
	printf("\n I suggest the letter %c\n",letters_freq[i].c);	
		
	return letters_freq[i].c;

}




int init_same_size(char **array, data_t *dat, int num_let){

	int i = 0;
	int j;
	int k = 0;
	int prev_length;
	int flag = 0;
	int counter;
	char *string,
	*temp;
	string = (char *) malloc(sizeof(char) * 25);
	printf("dat_size = %d", dat->size);
	while (i < dat->size){	
		strcpy(string,(dat->wordarr[i]));

		prev_length = strlen(dat->wordarr[i]);
		if (prev_length == num_let){
			flag = 1;
			printf("Inside if\n");
			printf("%s\n", string);
			printf("%d\n", prev_length);
			strcpy(array[k], string);
			counter++;
			printf("w=%s counter = %d arr=%s\n " , string, counter,  array[k]);
		}//end if
		i++;
		k++;
	}//end while
	if(flag == 0){
		printf("There is no matching word! \n Game Over");
		return 0;
	}//end if

	for(j = 0; j< i; j++){
		printf("%s", &array[i]);
	}//end for
	return counter;

}//end init_same_size


int delete_words(char **same_size,int asciinum, int columns){	//If the letter is rejected, delete function is called
	int i,j,s;
	char *temp;
	int size = s;

	for(i=0;i<size;i++){	//it controls the line which will have a specific length
		for(j=0;j<columns;j++){
			if (same_size[i][j]==asciinum){	//reading character by character
	
				temp=same_size[size-1];					// moves the word to the end of the file
				same_size[size-1]=same_size[i];
				same_size[i]=temp;
				s--;
	
			}
		}

	}

return s;

}


int delete_w(char **same_size,int asciinum, int columns){	//delete function is called if we accept the letter
	int i,j, s;
	char *temp;
	int size = s;

	for(i=0;i<size;i++){	//checks the line 
		for(j=0;j<columns;j++){
			if (same_size[i][j]!=asciinum){	//reading character by character
	
				temp=same_size[size-1];					// moves the word to the end of the file
				same_size[size-1]=same_size[i];
				same_size[i]=temp;
				s--;
	
			}
		}

	}

return s;

}


void game_over(data_t *dat){

	int s;
	int pos;
	char *word;
	int right_pos;
	
	word = (char*)malloc(sizeof(char));
	
	printf("----------Game Over----------\n");
	printf("The user won\n");
	printf("Insert the word \n");									//Ask for the right word
	scanf("%s", word);
	
	s = insert_at_table(word, dat);
	
	pos = find_pos(dat); 
						
 	sort(dat, pos , word);
	update_File(dat, "lexicon.txt");
	
}

void dealloc_data(data_t *dat)
{
    int i;

    for (i=0; i<dat->capacity; i++) {
        free(dat->wordarr[i]);
    }
    free(dat->wordarr);    
}



