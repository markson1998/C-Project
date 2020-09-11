
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUESTION 20000
#define MAX_ANSWER 200


int countLines(char filename[]){

    FILE *fp;
    int count = 0;  // Line counter (result)
    char c;  // To store a character read from file

    fp = fopen(filename, "r");

    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s, ", filename);
        return 0;
    }

    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    }

    // Close the file
    fclose(fp);
    printf("The file %s has %d Questions\n", filename, count+1);

    return count;


}


void storeResult(char *filename, int totalCorrect, int n, int dl){


   FILE *fptr;

   fptr = fopen("result.txt","a");

   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }

   fprintf(fptr,"Quiz Name: %s\n",filename);
   fprintf(fptr,"Correct Answers: %d\n",totalCorrect);
   fprintf(fptr,"Total Questions: %d\n",n);
   fprintf(fptr,"Difficulty Level: %d\n",dl);

   fprintf(fptr,"\n\n",dl);


   fclose(fptr);

}

int main(int argc, char* argv[]) {

    //Checking for arguments
    if(argc <= 2){

        printf("\nMethod To Use: programName filetoRead.txt difficulty(integer)\n");
        return 0;

    }

    printf("\n-------------------- Quiz --------------------\n\n");
    // Name of Quiz to Read Questions
    char *filename = argv[1];
    // Difficulty level
    int dl = atoi(argv[2]);
    // Getting No of Questions in Quiz
    int n = countLines(filename)+1;

    //Arrays storing questions and answers respectively
    char QuestionsArray[n][MAX_QUESTION];
    char AnswersArray[n][MAX_ANSWER];

    // reading questions and answers and storing in respective arrays
    FILE *filePointer;
    char ch;
    int isQuestion = 0;
    int i = 0;
    //2
    filePointer = fopen(filename, "r");
    //3
    if (filePointer == NULL)
    {
        printf("File is not available \n");
        return 0;
    }
    else
    {
        //4
        while ((ch = fgetc(filePointer)) != EOF)
        {
            while(ch != '?' && isQuestion == 0){
                //printf("%c", ch);
                strncat(QuestionsArray[i], &ch, 1);
                break;
            }

            if(ch == '?'){
                strncat(QuestionsArray[i], &ch, 1);
                //printf("%c", ch);
                isQuestion = 1;
                //printf("%d", isQuestion);
                continue;
            }

            if(ch == ' '){
                continue;
            }

            while(ch != '\n' && isQuestion == 1){
                strncat(AnswersArray[i], &ch, 1);
                break;
            }

            if(ch == '\n'){
                //printf("\n");
                isQuestion = 0;
                i++;
            }
        }
    }






// An array to keep record of already asked questions
    int isAsked[n];
// Variables to use during process of printing clues
    int index;
    char answer[200];
    int totalAsked = 0;
    int totalCorrect = 0;
    int wrongAnswers[n];
    int pos1 = 0;
    int pos2 = 0;

// Filling isAsked with zeros
    for(int i = 0; i < n; i++){

        isAsked[i] = 0;
        wrongAnswers[i] = 0;

    }

// Major logic of showing questions and getting answers
    for(int i = 0; i < n; i++){


        //for random selection
        while(1){
            //srand(time(0));
            index = rand() % n;
            if(isAsked[index] == 0){
                isAsked[index] = 1;
                break;
            }
        }


        printf("Question %d) %s \n", i, QuestionsArray[index]);

        //For clue 5
        int isPrinted[strlen(AnswersArray[index])];
        // Filling isPrinted Array;
        for(int i = 0; i < strlen(AnswersArray[index]); i++){

        isPrinted[i] = 0;

        }
        // For clue 6
        int clue = 0;

        // Clues Printing
        switch (dl)
       {
           case 1:
                clue1:
                printf("Clue: ?\n");
                break;
           case 2:
                clue2:
                printf("Clue: ");
                for(int j = 0; j < strlen(AnswersArray[index]); j++){
                    printf("_ ");
                }
                printf("\n");
                break;
           case 3:
                clue3:
                printf("Clue: ");
                printf("%c ", AnswersArray[index][0]);
                for(int j = 1; j < strlen(AnswersArray[index])-1; j++){
                    printf("_ ");
                }
                printf("%c", AnswersArray[index][strlen(AnswersArray[index])-1]);
                printf("\n");
                break;
           case 4:
                clue4:
                while(pos1 == pos2){
                    //srand(time(0));
                    pos1 = rand() % strlen(AnswersArray[index]);
                    pos2 = rand() % strlen(AnswersArray[index]);
                    //printf("%d %d", pos1,pos2);
                }

                printf("Clue: ");
                for(int j = 0; j < strlen(AnswersArray[index]); j++){
                    if(j == pos1 || j == pos2){
                        printf("%c ", AnswersArray[index][j]);
                    }else{
                        printf("_ ");
                    }
                }
                printf("\n");
                pos1 = 0;
                pos2 = 0;
                break;
           case 5:
               clue5:
                printf("Clue: ");
                for(int j = 0; j < strlen(AnswersArray[index]); j++){

                    while(1){
                        //srand(time(0));
                        pos1 = rand() % strlen(AnswersArray[index]);
                        if(isPrinted[pos1] == 0){
                            break;
                        }
                    }
                    printf("%c", AnswersArray[index][pos1]);
                    isPrinted[pos1] = 1;
                }
                printf("\n");
                break;
           case 6:
                printf("Enter the type of clue you want (1-5): ");
                scanf("%d", &clue);
                switch (clue)
                {
                    case 1: goto clue1;
                    case 2: goto clue2;
                    case 3: goto clue3;
                    case 4: goto clue4;
                    case 5: goto clue5;
                }
                break;

           default: printf("Invalid clue choice! \n");
                    break;
       }

        // Getting Answer
        printf("Write your Answer: ");
        scanf("%s", answer);
        printf("Answer: %s", answer);
        printf("\n");

        // Comparing Answers and storing wrong answers and calculating score
        if(strcmp(strlwr(answer), strlwr(AnswersArray[index])) == 0){
            printf("your answer is correct!\n");
            totalCorrect++;
        }else{

            wrongAnswers[index] = 1;

        }

        totalAsked++;
        //printing score
        printf("Score: %d / %d\n", totalCorrect, totalAsked);

    }
    // choice for printing right answers of wrong answers
    char choice = '0';
    // printing right answers of wrong answered questions
    printf("Do you want to see the correct answers of questions that you did wrong?(y/n) ");
    scanf("%s", &choice);
    if(choice == 'y'){
        for(int i = 0; i < n; i++){
            printf("\n");
            if(wrongAnswers[i] == 1){
                printf("Question: %s\n", QuestionsArray[i]);
                printf("Correct Answer: %s\n", AnswersArray[i]);
            }
        }
        // Ending and storing result into result.txt
        printf("\nThanks for playing :)\n\n");
        storeResult(filename,totalCorrect,n,dl);
    }else{
        // Ending and storing result into result.txt
        printf("\nThanks for playing :)\n\n");
        storeResult(filename,totalCorrect,n,dl);
    }



   return 0;
}

