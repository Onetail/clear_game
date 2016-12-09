/*
*	start prority : game of start running
*/
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define Max 26
int row = 12,col = 3;	// control x & y Max value
int speed = 1000;	// add | relieve game's speed	start is 1000 msec
int Round = 0, game_value = 0;	// record round	& game's value
int clear_check= 0;	// boolean true or false
char English_az[Max];
char user_input;
char xy_coordinate[12][3];	// record now num of coordinate
char Priority[15];
int times = 0;	// to know priority times
DWORD WINAPI ThreadFunc();
void array_clear()	// clear Priority & xy_coordinate array
{
	memset(xy_coordinate,' ',sizeof(xy_coordinate));
	memset(Priority,'\0',sizeof(Priority));
}
int game_over_check()
{
	int i ;
	for(i = 0;i < 3; i++)
	{
		if(xy_coordinate[0][i] == Priority[0] && xy_coordinate[0][i] != user_input) return 1;	
	}
	return 0;
}
void game_running_ui(int rowl,char word)
{
	int j,z;
	if(Round !=0)
	{
		for(j =0; j <row-1;j++)
			for(z = 0 ; z < col; z++)
			{
				xy_coordinate[j][z] = xy_coordinate[j+1][z];	
			}
		for(z = 0;z<col;z++)
			xy_coordinate[row-1][z] = '\0';
	}
	system("cls");
	printf("row1\t row2\t row3\n");
	fflush(stdout);
	xy_coordinate[row-1][rowl] = word;
	for(j = row-1 ; j >=0;j--)
	{
		for(z = 0 ; z< col; z++)
		{
			printf("|%c\t",xy_coordinate[j][z]);
		}
		printf("\n");
	}
	printf("speed = %d msec\tValue = %d g\n",speed,game_value);
//	printf("\n\n\tTimes = %d\n\tPriority = %d",times,sizeof(Priority));
//	printf("\nPriority[0] = %c\nRound = %d",Priority[0],Round);
//	printf("\nPriority[1] = %c\n",Priority[1]);
	printf("\t\t\t\t\t+ speed + 500 msec\n\t\t\t\t\t- speed -  500 msec\n\t\t\t\t\t5 clear |  0 to exit");
	fflush(stdout);
	printf("\nInput: ");
	fflush(stdout);
	Round ++;
}
char Random_number()	// 26 English to random
{
	srand(time(NULL));
	int random_number = (rand()%52) +1 ;
	return English_az[random_number];
}
void English_all()	// (start)	new for English array a~z
{
	int i;
	for(i = 1; i <= 26 ; i++)
		English_az[i] = 96 + i;	// 65 A~Z 97 a~z
	for(i = 27;i<=52; i++)
		English_az[i] = 65 + i - 27;
}
void main_while_running()
{
	while(1)
	{	
		int a = 0;
		scanf(" %c",&user_input);	
		if(user_input == '0')break;	// input 0 can exit game
		else if(user_input == '5')	// input 5 can clear the ui gameframe
			array_clear();
		else if(user_input == '+')
		{
			if(speed >= 5000);
			else speed = speed + 500;
		}
		else if(user_input == '-')
		{
			if(speed <= 500);
			else speed  = speed - 500;
		}
		else if(user_input == Priority[0])
		{
			int i,z,s;
			for(i = 0; i < row;i++)
			{
				for(z = 0 ;z <col;z++)
				{
					if(xy_coordinate[i][z] == Priority[0])
					{
						xy_coordinate[i][z] = '\0';
						clear_check = 1;
						game_value += 20;
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
			for(s = 0; s < strlen(Priority)-1; s++)
				Priority[s] = Priority[s+1];
		}else printf("\nerror");
	}
}
int main()
{
	system("cls");
	English_all();	// set English_az array
	printf("Enter any and game will start: ");
	getchar();
	HANDLE thread = CreateThread(NULL,0 ,ThreadFunc,NULL,0,NULL);	
	main_while_running();
	printf("end");
}
/*
*	ui frame for game
*	1. 1 sec to run
*	2. only kill the downest number
*	3. input 0 to exit
*/
DWORD WINAPI ThreadFunc()
{
	int randint;
	while(1)	 
	{
		if(game_over_check() == 1)
		{
			printf("\n\nYou are die~~");
			printf("\nInput(0 to exit) : ");
			fflush(stdout); 
			break;
		}
		Sleep(speed);
		if(user_input == '0')break;
		randint = (rand()%3);
		Priority[times] = Random_number();
		game_running_ui(randint,Priority[times]);
		times++;
	}
	_In_ DWORD dwExitCode;
}
