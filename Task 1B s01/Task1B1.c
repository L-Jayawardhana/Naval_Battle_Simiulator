#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

struct battle_ship {
    char Type_notation[2] ; char Type_name[25] ; 
    char Gun_name[25] ; float Max_Fire_Range ; 
    int Shell_Velocity ;
} ;

struct escort {
    char Type_notation[3] ; char Type_name[28] ; 
    char Gun_name[28] ; float Impact_power ;
    float Angle_range ; float Max_Fire_Range ; 
    float Min_angle ; int Min_velocity ; 
    int Max_velocity ;int X_coordinate ; 
    int Y_coordinate; float Distance ;
} ;

void Battleship();
void Escortships(struct escort Escships[]);
void RandomEscortships(struct escort Random_Eschips[] ,struct escort Escships[] ,int N , int Size,int Bx ,int By);
int Gen_Random(int g , int h);
float Distance(int BxC , int RxC , int ByC , int RyC);
char* FindName(struct battle_ship Batships[] , char B_choice[]);
int FindVelocity(struct battle_ship Batships[] , char B_choice[]);
int FindMaxFireRange(struct battle_ship Batships[] , char B_choice[]);
float Find_Max_Min_Distance(int Velo , int angle);
void Instructions();

int main (){
    // ask the user for choice
    int choice ;
    do {
    printf("\n");
    printf("\x1b[1m"); // Start bold font
    printf("\x1b[35m"); // change the title color
    printf("%40s" , "Advanced Naval Battle Simulator\n");
    printf("%41s" , "---------------------------------\n");
    printf("\x1b[0m"); // Reset formatting

    //main menu 
    printf("\x1b[1m");
    printf("Main Menu\n");
    printf("\x1b[0m");
    printf(" 1 - Start Simulation\n");
    printf(" 2 - View Instructions\n");
    printf(" 3 - Simulation Statistics\n");
    printf(" 4 - Exit\n");

    // ask the user for choice
    int choice ;
    //creating do-while loop for avoid invalid user input
    do {
        printf("Enter your choice : ");
            printf("\x1b[1m"); // formatting for user choice
            printf("\x1b[32m");  
        scanf("%d", &choice);
            printf("\x1b[0m");
        if (choice > 4 || choice <= 0){
            printf("\n");
            printf("Invalid choice, Plz choose 1 - 4\n");
        }
    } while (choice > 4 || choice <= 0) ;

    
            FILE *Task_1_B_S1;
    switch (choice){
        case 1: {
            Task_1_B_S1 = fopen("Task 1 B S1.txt", "w"); // Open for writing
            if (Task_1_B_S1 == NULL) {
                printf("Error opening file ..! \n");
                return 1;
            }
            fprintf(Task_1_B_S1, "%35s","Through out the Task 1 B S1\n");
            fprintf(Task_1_B_S1, "%36s","--------------------------\n");
            fprintf(Task_1_B_S1, "\n");

            printf("\n");
                printf("\x1b[1m");
                printf("\x1b[32m");
            printf("%16s" , "Start Simulation\n");
                printf("\x1b[0m");
                            
            srand(time(NULL)); //seed value

            //ask for the battlefield size
            int Size ;
            printf("Enter the length(km) of one side of the battlefield.(battlefield is a square) : ");
            scanf("%d", &Size);
                printf("\x1b[1m"); 
            printf("Size of the battlefield is %d * %d square kilometer.\n", Size ,Size);
                printf("\x1b[0m");

            //print the length of canvas to text file
            fprintf(Task_1_B_S1, "length(km) of one side of the battlefield.(battlefield is a square) : %d * %d square kilometer.\n",Size ,Size);
            fprintf(Task_1_B_S1, "\n");

            printf("\n");

            //Battle ship properties
                    printf("\x1b[1m"); printf("\x1b[34m");
                printf("%30s\n" , "Battleship properties");
                    printf("\x1b[0m");

                //store the battleships details in to a array
                struct battle_ship Batships[4] = {
                    {"U" , "USS lowa (BB-61)" , "50-caliber Mark 7 gun" , 32} ,
                    {"M" , "Ms King George V" , "(356 mm) Mark VII gun" , 33.7} ,
                    {"R" , "Richelieu" , "(15 inch) Mle 1935 gun" , 39} ,
                    {"S" , "Sovetsky Soyuz-class" , "(16 inch) B-37 gun" , 32}
                } ;
                
                //generate the random values for velocity and stored the to the Batship array.
                for (int i = 0 ; i < 4 ; i++){
                    Batships[i].Shell_Velocity = Gen_Random(200 , 751) ;
                }
                Battleship(Batships); //display the type of battelship, guns and shell velocities as a table
                
                //print the battships data to the text
                fprintf(Task_1_B_S1,"%30s\n" , "Types of Battleships and their species"); fprintf(Task_1_B_S1, "\n");
          //print the type of battelship, guns and shell velocities as a table to the text file
                fprintf(Task_1_B_S1, "%-10s %-26s %-26s %-16s %-15s\n" , "Notation" , "Battleship Name" , "Gun name" ,"Max fire range" , "Shell velocity");
                fprintf(Task_1_B_S1, "--------------------------------------------------------------------------------------------------------\n");

                //using for loop to getting inputs from the array and print them 
                for (int i = 0 ; i < 4 ; i++){
                    fprintf(Task_1_B_S1, "%-10s %-26s %-26s %-5.2f %-11s %-4d %-4s\n",Batships[i].Type_notation,
                    Batships[i].Type_name,Batships[i].Gun_name,Batships[i].Max_Fire_Range , "km" , Batships[i].Shell_Velocity ,"m/s" );
                } 
                fprintf(Task_1_B_S1, "\n");

            printf("\n");
                //asking the type of battleship
                char B_choice[2];
                printf("Enter the Notation for choosed Battleship: ");
                
                //using do-while loop for ignoring invalid inputs
                do {
                    printf("\x1b[1m"); printf("\x1b[32m");
                    scanf(" %1s", B_choice);
                    printf("\x1b[0m");
                    B_choice[0] = toupper(B_choice[0]);
                    if (B_choice[0] != 'U' && B_choice[0] != 'M' && B_choice[0] != 'R' && B_choice[0] != 'S') {
                        printf("Invalid notation, Please Re-Enter: ");
                    } 
                } while (B_choice[0] != 'U' && B_choice[0] != 'M' && B_choice[0] != 'R' && B_choice[0] != 'S');
            
                //print the choosed battleship
                char* FindName1 = FindName(Batships , B_choice); //called function name, FindName
                char Batname[20] ;
                        
                //copy the  string to the Batname
                strcpy(Batname, FindName1);
                int FindVelocity1 = FindVelocity(Batships , B_choice);
                    printf("\x1b[1m");
                printf("you choosed %s as your battleship and its velocity is %d m/s.\n" , Batname , FindVelocity1);
                    printf("\x1b[0m");
            printf("\n");

               //Asking for battleship coordinates
                int Bx , By ;
                printf("Enter the starting coordinates for your battleship. Each X and Y values should be equal or less than %d.\n" , Size);
                    
                    //using do-while loop for avoid invalid x , y values
                    do{
                        printf("Value for X : ") ;
                        scanf("%d" , &Bx);
                        printf("Value for Y : ") ;
                        scanf("%d" , &By);
                            if (Bx > Size || By > Size || Bx < 0 || By < 0){
                                printf("\n");
                                printf("invalid coordinate values. re enter.\n");
                            }
                    } while (Bx > Size || By > Size || Bx < 0 || By < 0);
                    printf("\x1b[1m");
                printf("Your -%s-starting coordinates are (%d , %d)\n" , Batname ,Bx ,By);
                    printf("\x1b[0m");

                     //print b ship and it s velocity to text
                fprintf(Task_1_B_S1,"Choosed %s as your battleship and its velocity is %d m/s.\n" , Batname , FindVelocity1);
                fprintf(Task_1_B_S1,"Your -%s-starting coordinates are (%d , %d)\n" , Batname ,Bx ,By);
                fprintf(Task_1_B_S1, "\n");

            printf("\n");
            
                //Escort ships properties
                        printf("\x1b[1m"); printf("\x1b[34m");
                    printf("%30s\n" , "Escort ships properties");
                        printf("\x1b[0m");
                
                    //store the escort ships details in to a array
                    struct escort Escships[5] = {
                        {"Ea" , "1936A-class Destroyer" , "SK C/34 naval gun" , 0.08 , 20 , 22.8} ,
                        {"Eb" , "Gabbiano-class Destroyer" , "L/47 dual-purpose gun" , 0.06 , 30 , 16.4} ,
                        {"Ec" , "Matsu-class Destroyer" , "Type 89 dual-purpose gun" , 0.07 , 25 , 14.6} ,
                        {"Ed" , "F-class Escort Ships" , "SK C/32 naval gun" , 0.05 , 50 , 17.4} ,
                        {"Ee" , "Japanese Kaibokan" , "(4.7 inch) naval guns", 0.04 ,70 , 14.7}
                    } ;

                    for (int i = 0 ; i < 5 ; i++){
                        if (i == 0){
                            Escships[i].Min_angle = Gen_Random(90-Escships[i].Angle_range , 1);
                            Escships[i].Max_velocity = 1.2 * FindVelocity1 ;
                            Escships[i].Min_velocity = Gen_Random(150 , (FindVelocity1 - 350));
                            continue;
                        }
                        Escships[i].Min_angle = Gen_Random(90-Escships[i].Angle_range , 1) ;
                        Escships[i].Max_velocity = Gen_Random(200 , (FindVelocity1 - 200)); //max v generate between Vb(max) to Vb(max)-200
                        Escships[i].Min_velocity = Gen_Random(150 , (FindVelocity1 - 350)) ; // Min v generate between Vb(max)-200 to Vb(max)-350 
                    }

                    //show the types of escort ships 
                    Escortships(Escships); 

                    //show the escort ship types in text file
                    fprintf(Task_1_B_S1,"%46s" ,"Types of Escort ships and their species\n");
                    fprintf(Task_1_B_S1,"%-10s %-28s %-27s %-15s %-16s %-15s %-12s %-15s %-15s\n","Notation","Type name","Gun name","Impact power","Max fire range","Angle range","Min Angle","Min Velocity","Max Velocity");
                    fprintf(Task_1_B_S1,"-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
                    
                    //using for loop to getting inputs from the array and print them
                    for (int i = 0 ; i < 5 ; i++){
                        fprintf(Task_1_B_S1,"%-10s %-28s %-27s %-15.2f %-6.2f %-9s %-15.f %-13.f %-4d %-10s %-4d %-10s\n",
                                Escships[i].Type_notation, Escships[i].Type_name, Escships[i].Gun_name, Escships[i].Impact_power, Escships[i].Max_Fire_Range ,
                                "km",Escships[i].Angle_range, Escships[i].Min_angle, Escships[i].Min_velocity,"m/s", Escships[i].Max_velocity ,
                                "m/s" );
                    }
                    fprintf(Task_1_B_S1,"\n"); 

                printf("\n"); 
                    int N ;
                    //asking for how many escort ships in the battlee field
                    printf("How many escort ships do you want for the battlefield? : ");
                        printf("\x1b[1m"); printf("\x1b[32m");                
                    scanf("%d" , &N);
                        printf("\x1b[0m");
                    printf("Your %d escort ships are randomly generating. Escort ships for the batterfiled are following :\n" , N);
                    
                    //creating new structer for random escorts details
                    struct escort Random_Eschips[N] ;

                    fprintf(Task_1_B_S1,"Escort ships for the battlefield is %d" ,N);//text
                    fprintf(Task_1_B_S1,"\n"); 

            printf("\n");           
                    // dispaly randomly generated escort ships and their distance to the battleship  .
                        printf("\x1b[1m"); printf("\x1b[36m");
                    printf("%30s\n" , "Escort ships for the battle, their location and distance to the initial location of battleship.");
                        printf("\x1b[0m"); 

                    RandomEscortships(Random_Eschips , Escships , N , Size, Bx , By); //call the function to display details

                    // dispaly randomly generated escort ships and their distance to the battleship in to the text file.
                    fprintf(Task_1_B_S1,"%30s\n" , "Escort ships for the battle, their location and distance to the initial location of battleship.\n");
                    for(int i = 0 ; i < N ; i++){
                        fprintf(Task_1_B_S1,"%3d - %-25s location = (%3d , %-3d)    distance = %.2f km \n" , i+1 , Random_Eschips[i].Type_name,Random_Eschips[i].X_coordinate ,
                        Random_Eschips[i].Y_coordinate,Random_Eschips[i].Distance);
                    }
                    
            fprintf(Task_1_B_S1,"\n");
            printf("\n");

                //get the current time
                    time_t currentTime;
                    struct tm *localTime;

                    time(&currentTime);
                    localTime = localtime(&currentTime);

                bool battleshipHit = false;
                
                int *sunk_array = NULL; // Initialize array pointer to NULL
                int Arraysize = 0;

                //repitition for k iterations
                for (int k = 0 ; k < 100 ; k++){
                                       
                    printf("\n");
                    printf("\x1b[1m"); printf("\x1b[33m");
                    printf("Battle details when %s in (%d , %d) position.\n" , Batname , Bx ,By);
                        printf("\x1b[0m");

                    //print position to the text
                    fprintf(Task_1_B_S1,"Battle details when %s in (%d , %d) position.\n" , Batname , Bx ,By);

                    float max , min ;
                    // display , escort ships status after the battle .
                        printf("\x1b[1m"); printf("\x1b[36m");
                    printf("%30s\n" , "Escort ships details");
                        printf("\x1b[0m");
                    
                    fprintf(Task_1_B_S1, "%30s\n" , "Escort ships details");

                    // Iterating through all escort ships
                    for (int i = 0 ; i < N ; i++){
                        // If sunk_array is not NULL and the current ship was sunk in previous iterations, skip printing its status
                        
                            if (sunk_array != NULL) {
                                int Sunk = 0; 
                                for (int j = 0; j < Arraysize; j++) {
                                    if (i == sunk_array[j]) {
                                        Sunk = 1; 
                                    }
                                }
                                if (Sunk) {
                                    continue; // move to the next iteration
                                }
                            }
                        //check the max fire range of battleship is less than or more than the distance between escort ships.
                        if (Distance(Bx , Random_Eschips[i].X_coordinate , By , Random_Eschips[i].Y_coordinate) <= FindMaxFireRange(Batships , B_choice)){ 

                            //if max fire range is more than distance then display that escort ship hit by battleship.
                            printf("%-25s %-5s %-8s %02d:%02d:%02d    by the %s\n",Random_Eschips[i].Type_name ,"was"," hit on",localTime->tm_hour, localTime->tm_min, localTime->tm_sec, Batname);
                            
                            fprintf(Task_1_B_S1,"%-25s %-5s %-8s %02d:%02d:%02d    by the %s\n",Random_Eschips[i].Type_name ,"was"," hit on",localTime->tm_hour, localTime->tm_min, localTime->tm_sec, Batname);//to text file

                            Arraysize++; // Increase the size of array
                            sunk_array = realloc(sunk_array, Arraysize * sizeof(int)); // Reallocate memory to increase the size of the array
                            sunk_array[Arraysize - 1] = i; // Add the new element to the end of the array
                        } else {
                            //if max fire range is less than distance then display that escort ship not hit by battleship.
                            printf("%-25s %-5s %-20s by the %s\n",Random_Eschips[i].Type_name ,"was","not hit", Batname);

                            fprintf(Task_1_B_S1,"%-25s %-5s %-20s by the %s\n",Random_Eschips[i].Type_name ,"was","not hit", Batname);
                        }
                    }
                                    
                    //open a for loop for going through the all randomly generated escort ships for once
                    //because escort ships only fire once
                    //if battle ship not hit by the escorts in initial position battleship is safe
                    if (k == 0){
                    //display , battleship status after the battle
                        printf("\x1b[1m"); printf("\x1b[36m");
                    printf("%30s\n" , "Battleship details");
                        printf("\x1b[0m");

                        //display , battleship status after the battle to the text file
                        fprintf(Task_1_B_S1,"%30s\n" , "Battleship details");

                        for(int i = 0 ; i < N ; i++){
                                                
                            //defining two variables min , max 
                            float max = 0;
                            float min = INFINITY ;

                            //open another for loop for get the max fire range and min fire range for each escort ship
                            // range of the j is min angle - max angle of each escort ship gun
                            //max angle is getting by add the angle range to the min angle of each ship.
                            for (int j = Random_Eschips[i].Min_angle ; j <= (Random_Eschips[i].Min_angle + Random_Eschips[i].Angle_range) ; j++){
                                
                                //getting the max fire range by using max velocity of the shell and angle
                                //to get the fire range, called function named Find_Max_Min_Distance()
                                
                                if (Find_Max_Min_Distance(Random_Eschips[i].Max_velocity , j) > max ) {
                                    max = Find_Max_Min_Distance(Random_Eschips[i].Max_velocity , j);
                                } 
                                //getting the min fire range by using min velocity of the shell and angle
                                if (Find_Max_Min_Distance(Random_Eschips[i].Min_velocity , j) < min){
                                    min = Find_Max_Min_Distance(Random_Eschips[i].Min_velocity , j) ;
                                }
                            }
                            //check max distance of shell can go is less or more than max fire range
                            //max fire ranges are acoording to true data 
                            if (max > Random_Eschips[i].Max_Fire_Range){
                                max = Random_Eschips[i].Max_Fire_Range ;
                            }
                            //if min fire range is more than max fire range we assume min = max fire range - 8(km) ; 
                            if (min > Random_Eschips[i].Max_Fire_Range){
                                min = Random_Eschips[i].Max_Fire_Range - 8 ;
                            }

                            //compare the max fire range of each escort ship and distane between escort and battle ship
                            //if distance for the batlleship is between min and max fire range of escort ship, display battleship was hit by that escort ship
                            if (Distance(Bx , Random_Eschips[i].X_coordinate , By , Random_Eschips[i].Y_coordinate) <= max && 
                                Distance(Bx , Random_Eschips[i].X_coordinate , By , Random_Eschips[i].Y_coordinate) >= min){
                                
                                printf("%-25s %-5s %-8s %02d:%02d:%02d   by the %s\n",Batname ,"was"," hit on",localTime->tm_hour, localTime->tm_min, localTime->tm_sec, Random_Eschips[i].Type_name);           
                                printf("\n");

                                //to the text
                                fprintf(Task_1_B_S1,"%-25s %-5s %-8s %02d:%02d:%02d   by the %s\n",Batname ,"was"," hit on",localTime->tm_hour, localTime->tm_min, localTime->tm_sec, Random_Eschips[i].Type_name);           
                                fprintf(Task_1_B_S1,"\n");
                                
                                battleshipHit = true; //change the value
                                break ;          
                            } 
                            //if distance for the batlleship is not between min and max fire range of escort ship,display battleship was not hit by that escort ship
                            else {
                                if(i == N-1){
                                    printf("Battleship was not harmed .");
                                    printf("\n");
                                    fprintf(Task_1_B_S1,"Battleship was not harmed .");//to the text
                                }
                            }
                        }
                    }
                        printf("\n");
                        fprintf(Task_1_B_S1,"\n");  

                        if (Arraysize == N || battleshipHit){
                            if (Arraysize == N){
                                printf("\x1b[1m");printf("All escort ships was destroyed .\n"); printf("\x1b[0m");
                                fprintf(Task_1_B_S1,"All escort ships was destroyed .\n");
                            } 
                            if (battleshipHit){
                                printf("\x1b[1m"); printf("Battleship was destroyed .\n");printf("\x1b[0m");
                                fprintf(Task_1_B_S1,"Battleship was destroyed .\n");
                            } else {
                                printf("\x1b[1m"); printf("Battleship was not destroyed .\n");printf("\x1b[0m");
                                fprintf(Task_1_B_S1,"Battleship was not destroyed .\n");
                            }
                            printf("\x1b[1m"); printf("Battle is over");printf("\x1b[0m");
                            fprintf(Task_1_B_S1,"Battle is over");
                            break;    
                        }

                    //create new random cordinates by adding or substract values
                        Bx = Bx + Gen_Random(3,0) ; 
                        By = By + Gen_Random(3,0) ;

                    //keep that coordinate values in the canavs
                    while (By > Size && Bx > Size || Bx < 0 && By < 0) {
                        if (By > Size && Bx > Size){
                            Bx = Bx - Gen_Random(3,0) ; 
                            By = By - Gen_Random(3,0) ;
                        } else if(Bx < 0 && By < 0){
                            Bx = Bx + Gen_Random(3,0) ; 
                            By = By + Gen_Random(3,0) ;
                        }
                    } 
                    //in this case assume that Bship going tot he next location after 1 - 3  min
                    int time_diff = Gen_Random(3,1);
                    localTime->tm_min += time_diff ;
                    mktime(localTime); // Adjust time in case minutes overflow
                }

                free(sunk_array);
    printf("\n");
    fprintf(Task_1_B_S1,"\n");
    fclose(Task_1_B_S1); //close
    printf("Data written to Task 1 B S1.txt successfully.\n");           
        }   break;
    case 2:
                printf("Viewing Instructions...\n");
                Instructions();
                break;
        case 3:
                printf("Viewing Simulation Statistics...\n");
                FILE *file;
                char line[1000]; // Assuming each line has at most 100 characters

                // Open the file
                file = fopen("Task 1 B S1.txt", "r");
                
                // Check if the file is opened successfully
                if (file == NULL) {
                    printf("Error opening the file.\n");
                    return 1;
                }

                // Read and print each line of the file
                while (fgets(line, sizeof(line), file) != NULL) {
                    printf("%s", line);
                }

                // Close the file
                fclose(file);
                break;
        case 4:
                printf("Exiting...\n");
                // Add code to exit the program
                break;
    
    }
    if (choice == 4){
        break;
    }
    }  while (choice != 4); 

return 0;
}

//this function is called for dispaly the battleship table
void Battleship(struct battle_ship Batships[]){
    printf("\x1b[1m");printf("\x1b[36m");
    printf("%46s" ,"Choose your battleship among the following\n");
    printf("\x1b[0m");
    printf("%-10s %-26s %-26s %-16s %-15s\n" , "Notation" , "Battleship Name" , "Gun name" ,"Max fire range" , "Shell velocity");
    printf("--------------------------------------------------------------------------------------------------------\n");

    //using for loop to getting inputs from the array and print them 
    for (int i = 0 ; i < 4 ; i++){
        printf("%-10s %-26s %-26s %-5.2f %-11s %-4d %-4s\n",Batships[i].Type_notation,Batships[i].Type_name,
        Batships[i].Gun_name,Batships[i].Max_Fire_Range , "km" , Batships[i].Shell_Velocity ,"m/s" );
    } 
}

//this function is called for dispaly the escort ship table
void Escortships(struct escort Escships[]){
    printf("\x1b[1m");printf("\x1b[36m");
    printf("%46s" ,"Types of Escort ships and their species\n");
    printf("\x1b[0m");
    printf("%-10s %-28s %-27s %-15s %-16s %-15s %-12s %-15s %-15s\n","Notation","Type name","Gun name","Impact power","Max fire range","Angle range","Min Angle","Min Velocity","Max Velocity");
    printf("-------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    
    //using for loop to getting inputs from the array and print them
    for (int i = 0 ; i < 5 ; i++){
        printf("%-10s %-28s %-27s %-15.2f %-6.2f %-9s %-15.f %-13.f %-4d %-10s %-4d %-10s\n",
                Escships[i].Type_notation, Escships[i].Type_name, Escships[i].Gun_name, Escships[i].Impact_power, Escships[i].Max_Fire_Range ,
                "km",Escships[i].Angle_range, Escships[i].Min_angle, Escships[i].Min_velocity,"m/s", Escships[i].Max_velocity ,
                "m/s" );
    }
}

//copy and assign some values to the Random_Eschips[] array
//this array is using for store details of randomly generated escort shpis.
void RandomEscortships(struct escort Random_Eschips[] ,struct escort Escships[] ,int N , int Size , int Bx ,int By){
    for(int i = 0 ; i < N ; i++){
        int random_index = rand() % 5 ;
        strcpy(Random_Eschips[i].Type_name, Escships[random_index].Type_name);
        Random_Eschips[i].Impact_power = Escships[random_index].Impact_power ;
        Random_Eschips[i].Angle_range  = Escships[random_index].Angle_range ;
        Random_Eschips[i].Min_angle    = Escships[random_index].Min_angle ;
        Random_Eschips[i].Min_velocity = Escships[random_index].Min_velocity ;
        Random_Eschips[i].Max_velocity = Escships[random_index].Max_velocity ;
        Random_Eschips[i].X_coordinate = Gen_Random(Size + 1 , 0) ;
        Random_Eschips[i].Y_coordinate  = Gen_Random(Size + 1 , 0) ;
        Random_Eschips[i].Max_Fire_Range = Escships[random_index].Max_Fire_Range ;
        //distance between battle ship and each escort ship
        //distance also stored in to the Random_Eschips[] array
        Random_Eschips[i].Distance     = Distance(Bx , Random_Eschips[i].X_coordinate , By , Random_Eschips[i].Y_coordinate) ;
        printf("%3d - %-25s location = (%3d , %-3d)    distance = %.2f km \n" , i+1 , Random_Eschips[i].Type_name,Random_Eschips[i].X_coordinate ,
                        Random_Eschips[i].Y_coordinate,Random_Eschips[i].Distance);
    }
}
// function to find distance between two coordinates
float Distance(int BxC , int RxC , int ByC , int RyC){
    int s = sqrt(pow(abs(BxC - RxC) , 2) + pow(abs(ByC - RyC) , 2));
    return s ; 
}

//this function is using for generate the random number
//values for g and h should be give when function is called
int Gen_Random(int g , int h){
    int random = (rand() % g) + h ;
    return random ;
}

//this function using for know the battleship name when its notaion are given
char* FindName(struct battle_ship Batships[] , char B_choice[]){
    for (int i = 0 ; i < 4 ; i++){
        if (strcmp(B_choice , Batships[i].Type_notation) == 0){
            return Batships[i].Type_name ;
        }
    }
}

//this function using for know the battleship shell velocity when its notaion are given
int FindVelocity(struct battle_ship Batships[] , char B_choice[]){
    for (int i = 0 ; i < 4 ; i++){

        //compare the user input notation and Type_notaion in Batships array
        //if the are equal return that battleship shell velocity.
        if (strcmp(B_choice , Batships[i].Type_notation) == 0){
            return Batships[i].Shell_Velocity ;
        }
    }
}
//this function using for know the battleship max fire range when its notaion are given
int FindMaxFireRange(struct battle_ship Batships[] , char B_choice[]){
    for (int i = 0 ; i < 4 ; i++){

        //compare the user input notation and Type_notaion in Batships array
        //if the are equal return that battleship shell velocity.
        if (strcmp(B_choice , Batships[i].Type_notation) == 0){
            return Batships[i].Max_Fire_Range ;
        }
    }
}

//this function using for find the distance by using mathematical calculation. 
//this gives the distance as the return when we know the velocity and angle.
//this calculation gives max or min fire range in KM
float Find_Max_Min_Distance(int Velo , int angle){
    float pi = 3.14159 ;
    float S =  ((pow(Velo , 2) * sin(2*((angle*pi)/180))) / 9.98) / 1000 ; //g = 9.98 m/s 
    return S ;
}


void Instructions() {
     printf("\n");
    printf("Instructions:\n");
    printf("1. Start Simulation: Choose this option to begin the naval battle simulation.\n");
    printf("2. View Instructions: View the instructions on how to use the program effectively.\n");
    printf("3. Simulation Statistics: View the statistics generated during the simulation.\n");
    printf("4. Exit: Exit the program.\n");
    printf("\n");
    printf("How to use the simulation:\n");
    printf("- Choose option 1 to start the simulation and follow the prompts to set up the simulation parameters.\n");
    printf("- During the simulation, you will see the details of battleships and escort ships, their coordinates, and distances.\n");
    printf("- The simulation will run for a specified number of iterations, during which battleships and escort ships will engage in combat.\n");
    printf("- Escort ships will attempt to destroy the battleship, while the battleship will attempt to survive by avoiding hits.\n");
    printf("- After each iteration, you will receive updates on the status of battleships and escort ships.\n");
    printf("- The simulation will end when either all escort ships are destroyed or the battleship is destroyed.\n");
    printf("- View simulation statistics using option 3 to see the outcome of the simulation and any relevant data.\n");
    printf("- You can exit the program at any time by choosing option 4.\n");
    printf("\n");
}
