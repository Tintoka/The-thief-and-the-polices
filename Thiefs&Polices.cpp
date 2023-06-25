#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include <time.h>
#include<math.h>
#include<unistd.h>
char positions[100][100];
int NumOfST, PolicPos[3][1000] ,PolicMove, DozdMove;
// print of positions
void Pose_Print(int m, int n){
	static int t=0;
    for(int i = 0;i <m ; i++){
        for(int j = 0; j< n; j++) {
            printf("%c ", positions[i][j]);
        }
        printf("\n");
    }
	printf("\ntime: %d\n", t++);
}
//Did
void DID(int m,int n, int DozdPos[2], int Did[]){
    for(int i = 0; i < NumOfST; i++)
        Did[i] = 0;
    for(int i= DozdPos[0] -2; i < DozdPos[0] + 3; i++){
        for(int j = DozdPos[1] -2;j < DozdPos[1] + 3; j++){
            if(positions[i][j] != 'T' && positions[i][j] != (char) 177 && !(i < 0 || j < 0 || i > m-1 || j > n-1))
               Did[(int)(positions[i][j]) -48]= 1;
        }
    }
}
//polices
bool police_next_move(int m, int n, int i, int DozdPos[2], int Did[])
{
    int x, y;
    PolicMove++;
    positions[PolicPos[0][i]][PolicPos[1][i]] = (char) 177;
   	if(Did[PolicPos[2][i]] == 1) {
       //printf("Hello from a Not Blind Polic\n");
        if (PolicPos[1][i] > DozdPos[1] && PolicPos[1][i]-1>0)
            y = -1;
        else if (PolicPos[1][i] < DozdPos[1] && PolicPos[1][i]+1<=n-1)
            y = 1;
        else
            y = 0;
        if (PolicPos[0][i] > DozdPos[0] && PolicPos[0][i]-1>0)
            x = -1;
        else if (PolicPos[0][i] < DozdPos[0] && PolicPos[0][i]+1<=m-1)
            x = 1;
        else
            x = 0;
        if (PolicPos[1][i]==DozdPos[1] && (positions[PolicPos[0][i]+x][PolicPos[1][i]]=='T' || positions[PolicPos[0][i]+x][PolicPos[1][i]]== (char)177)) {
			if (positions[PolicPos[0][i]+x][PolicPos[1][i]] == 'T')
	        {
				positions[PolicPos[0][i]+x][PolicPos[1][i]]= (char) 254;
	        	return true;
			}
			positions[PolicPos[0][i]+x][PolicPos[1][i]]= positions[PolicPos[0][i]][PolicPos[1][i]]; 
			positions[PolicPos[0][i]][PolicPos[1][i]]= (char)177;
			PolicPos[0][i]+= x;	
		}
		else if (PolicPos[0][i]==DozdPos[0] && (positions[PolicPos[0][i]][PolicPos[1][i]+y]=='T' || positions[PolicPos[0][i]][PolicPos[1][i]+y]== (char)(char)177)) {
			if (positions[PolicPos[0][i]][PolicPos[1][i]+y] == 'T')
	        {
				positions[PolicPos[0][i]][PolicPos[1][i]+y]= (char) 254;
	        	return true;
			}
			positions[PolicPos[0][i]][PolicPos[1][i]+y]= positions[PolicPos[0][i]][PolicPos[1][i]];
			positions[PolicPos[0][i]][PolicPos[1][i]]= (char)177; 
			PolicPos[1][i]+= y;	
		}
		else {
			if (positions[PolicPos[0][i]+x][PolicPos[1][i]+y]=='T' || positions[PolicPos[0][i]+x][PolicPos[1][i]+y]== (char)(char)177) {
				if (positions[PolicPos[0][i]+x][PolicPos[1][i]+y] == 'T'){
					positions[PolicPos[0][i]+x][PolicPos[1][i]+y]= (char) 254;
		        	return true;
				}
				positions[PolicPos[0][i]+x][PolicPos[1][i]+y]= positions[PolicPos[0][i]][PolicPos[1][i]]; 
				positions[PolicPos[0][i]][PolicPos[1][i]]= (char)177; 
				PolicPos[0][i] += x, PolicPos[1][i] += y;	
			}
			else if (positions[PolicPos[0][i]+x][PolicPos[1][i]]=='T' || positions[PolicPos[0][i]+x][PolicPos[1][i]]==(char)177) {
				if (positions[PolicPos[0][i]+x][PolicPos[1][i]] == 'T'){
					positions[PolicPos[0][i]+x][PolicPos[1][i]]= (char) 254;
		        	return true;
				}
				positions[PolicPos[0][i]+x][PolicPos[1][i]]= positions[PolicPos[0][i]][PolicPos[1][i]];
				positions[PolicPos[0][i]][PolicPos[1][i]]= (char)177;
				PolicPos[0][i] += x;
			}
			else if (positions[PolicPos[0][i]][PolicPos[1][i]+y]=='T' || positions[PolicPos[0][i]][PolicPos[1][i]+y]==(char)177) {
				if (positions[PolicPos[0][i]][PolicPos[1][i]+y] == 'T'){
					positions[PolicPos[0][i]][PolicPos[1][i]+y]= (char) 254;
		        	return true;
				}
				positions[PolicPos[0][i]][PolicPos[1][i]+y]= positions[PolicPos[0][i]][PolicPos[1][i]];
				positions[PolicPos[0][i]][PolicPos[1][i]]= (char)177;
				PolicPos[1][i] += y;
			}
		} 
        positions[PolicPos[0][i]][PolicPos[1][i]] = (char) (PolicPos[2][i] + 48);
        return false;
    }
    else{
        do{
            x = rand() % 3 - 1;
            y = rand() % 3 - 1;
            //printf("Hello from Blind Polic :3\n");
		}while(((positions[PolicPos[0][i]][PolicPos[1][i]] != (char)177 && (positions[PolicPos[0][i]][PolicPos[1][i]] != 'T')) || PolicPos[0][i] + x > m-1 || PolicPos[0][i] + x < 0 || PolicPos[1][i] + y > n-1 || PolicPos[1][i] + y < 0));
		PolicPos[0][i] += x;
        PolicPos[1][i] += y;
        if (positions[PolicPos[0][i]][PolicPos[1][i]] == 'T')
        {
			positions[PolicPos[0][i]][PolicPos[1][i]]= (char) 254;
        	return true;
		}
        positions[PolicPos[0][i]][PolicPos[1][i]] = (char) (PolicPos[2][i] + 48);
	}
	return false;
}
//dozd
bool Dozd_next_move(int m, int n, int DozdPos[]) {
    int x, y;
	DozdMove++;    
    do{
		x = ( rand() % 3 ) - 1;
		y = (rand() % 3)  -1;
		//printf("Hello From Dozd\n");
    }while (DozdPos[0] + x > m-1 || DozdPos[1] + y > n-1 || DozdPos[0] + x < 0 || DozdPos[1] + y < 0);
    positions[DozdPos[0]][DozdPos[1]] = (char)177; //turn the last pose of dozd to normal
    DozdPos[0] += x;
    DozdPos[1] += y;
    if(positions[DozdPos[0]][DozdPos[1]] != (char) 177 && positions[DozdPos[0]][DozdPos[1]] != 'T'){
        positions[DozdPos[0]][DozdPos[1]] = (char) 254;
        return true;
    }
    positions[DozdPos[0]][DozdPos[1]] = 'T';
    return false;
}

int main() {
    int m, n, DozdPos[2], PolicHQ = 0;
    bool  flag_arrest = false;
    srand(time(0));
    printf("Enter m and n\n");
    scanf("%d %d", &m, &n);
    //char positions[m][n]; //Toka no
    printf("Enter the number of stations : \n");
    scanf("%d", &NumOfST);
    int PolicNum[NumOfST];
    int Did[NumOfST];
    for (int i = 0; i < NumOfST; i++) {
        printf("Number Of Police for station %d:\n",i);
        scanf("%d", &PolicNum[i]);
        PolicHQ += PolicNum[i];
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            positions[i][j] = (char) 177;
        }
    }
    int Polic_ID_Num=0; // counter = Polic_ID_Num
    for (int i = 0; i < NumOfST; i++) {
        for (int j = 0; j < PolicNum[i]; j++) {
            PolicPos[2][Polic_ID_Num] = i ;
            do {
                PolicPos[0][Polic_ID_Num] = rand() % m;
                PolicPos[1][Polic_ID_Num] = rand() % n;
            } while (positions[PolicPos[0][Polic_ID_Num]][PolicPos[1][Polic_ID_Num]] != (char) 177); //checks if two Police are not in the same place
            positions[PolicPos[0][Polic_ID_Num]][PolicPos[1][Polic_ID_Num]]= (char) (i + 48);
            Polic_ID_Num++;
        }
    }
    do {
        DozdPos[0] = rand() % m;
        DozdPos[1] = rand() % n;
    } while (positions[DozdPos[0]][DozdPos[1]] != (char) 177); //checks if Dozd is not in the same place with a Police
    positions[DozdPos[0]][DozdPos[1]] = 'T';
    system("cls");
    do{
        //printf("KJShkdja");
        Pose_Print(m, n);
        printf("\n");
	    for (int i=0; i<3; i++)
	    {
	    	for (int j=0; j<PolicHQ; j++)
	    		printf("%d ", PolicPos[i][j]);
	    	printf("\n");
	    }
        sleep(1);
        system("cls");
        //printf("i'M HERE??!!");
		flag_arrest = (Dozd_next_move(m, n, DozdPos));
        //printf("i'M HERE?!");
		if(flag_arrest){  //** Toka no
		    Pose_Print(m,n);
		    goto end;
		}    //Toka no
        for (int i = 0; i < PolicHQ; i++) {
            //printf("i'M HERE\n");
            DID(m, n, DozdPos, Did);
            flag_arrest = police_next_move(m, n, i, DozdPos, Did);
            if (flag_arrest) {
                Pose_Print(m, n);
                goto end;
            }
        }
	}while (!flag_arrest);
	end: ;
    printf("\n");
    printf("Busted!\n");
    printf("Police Moves: %d\n", PolicMove);
    printf("Dozd Moves: %d\n", DozdMove);
    return 0;
}
