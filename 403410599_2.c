/*
*	start prority : game of start running
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#define Max 26
int speed = 1;	// add | relieve game's speed	start is 1000 msec
int Round = 0;	// record round
int clear_check= 0;	// boolean true or false
char English_az[Max];
char user_input;
char xy_coordinate[10][3];	// record now num of coordinate
char Priority[15];
int times = 0;	// to know priority times
void *run();
void array_clear()	// clear Priority & xy_coordinate array
{
	memset(xy_coordinate,' ',sizeof(xy_coordinate));
	memset(Priority,'\0',sizeof(Priority));
}
int game_over_check()
{
	for(int i = 0;i < 3; i++)
	{
		if(xy_coordinate[0][i] == Priority[0] && xy_coordinate[0][i] != user_input) return 1;	
	}
	return 0;
}
void game_running_ui(int row,char word)
{
	int j,z;
	if(Round !=0)
	{
		for(j =0; j <9;j++)
			for(z = 0 ; z < 3; z++)
			{
				xy_coordinate[j][z] = xy_coordinate[j+1][z];	
			}
		for(z = 0;z<3;z++)
			xy_coordinate[9][z] = '\0';
	}
	printf("\033c");
	printf("\nrow1\t row2\t row3\n\n");
	fflush(stdout);
	xy_coordinate[9][row] = word;
	for(j = 9 ; j >=0;j--)
	{
		for(z = 0 ; z<3; z++)
		{
			printf("|%c\t",xy_coordinate[j][z]);
		}
		printf("\n");
	}
	printf("speed = %d\n",speed);
//	printf("\n\n\tTimes = %d\n\tPriority = %d",times,sizeof(Priority));
//	printf("\nPriority[0] = %c\nRound = %d",Priority[0],Round);
//	printf("\nPriority[1] = %c\n",Priority[1]);
	fflush(stdout);
	printf("\n\nInput: ");
	fflush(stdout);
	Round ++;
}
char Random_number()	// 26 English to random
{
	srand(time(NULL));
	int random_number = (rand()%26) +1 ;
	return English_az[random_number];
}
void English_all()	// (start)	new for English array a~z
{
	for(int i = 1; i <= 26 ; i++)
		English_az[i] = 96 + i;	// 65 A~Z 97 a~z
}
int main()
{
	printf("\033c");
	English_all();	// set English_az array
	pthread_t ti;
	pthread_attr_t attr;
	pthread_attr_init(&attr);	//	init thread
	pthread_create(&ti,&attr,run,English_az);	
	while(1)
	{	
		int a = 0;
		scanf(" %c",&user_input);	
		if(user_input == '0')break;	// input 0 can exit game
		else if(user_input == '5')	// input 5 can clear the ui gameframe
			array_clear();
		else if(user_input == '+')
		{
			if(speed > 5);
			else speed = speed + 1;
		}
		else if(user_input == '-')
		{
			if(speed <= 1);
			else speed  = speed - 1;
		}
		else if(user_input == Priority[0])
		{
			for(int i = 0; i < 10;i++)
			{
				for(int z = 0 ;z <3;z++)
				{
					if(xy_coordinate[i][z] == Priority[0])
					{
						xy_coordinate[i][z] = '\0';
						clear_check = 1;
						break;
					}
				}
				if(clear_check ==  1)	// check the one clear for xy_coordinate
				{
					clear_check = 0;
					break;
				}
			}
			times --;
			for(int s = 0; s < strlen(Priority)-1; s++)
			{
				Priority[s] = Priority[s+1];
			}
		}else printf("\nerror");
	}
	printf("end");
}
/*
*	ui frame for game
*	1. 1 sec to run
*	2. only kill the downest number
*	3. input 0 to exit
*/
void *run()	
{
	int randint;
	while(1)	 
	{
		if(game_over_check() == 1)
		{
			printf("\n\nYou are die~~\n");
			printf("\nInput(0 to exit) : ");
			fflush(stdout); 
			break;
		}
		sleep(speed);
		if(user_input == '0')break;
		randint = (rand()%3);
		Priority[times] = Random_number();
		game_running_ui(randint,Priority[times]);
		times++;
	}
	pthread_exit(0);
}
