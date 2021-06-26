#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "starter_code/teamInfo.h"
#include "starter_code/teamInfo_LinkedList.h"


int main()
{
    int i=0, j=0, max_confs=0;						//variables i & j are loop indices while max_confs hold the number of conferences.
    struct _teaminfo *array[50];					//array of type _teaminfo that would hold each team's info after the readTeamInfo function.
    char fname[30];
	printf("Enter the name of the file:");
	scanf("%s",fname);
    int num=readTeamInfo(fname,array);				//variable num holds the number of teams that is returned from the function readTeamInfo.

    for (i=0; i<num; ++i){							//This loop check the maximum number of conferences and assigns it to max_confs.
        if (array[i]->conf>max_confs){
            max_confs=array[i]->conf;
        }
    }

    LinkedListPtr_t confList[max_confs-1];			//creates an array pointer of linked lists.  the size of the array depends on the maximum nuber of conferences (max_confs).

    for(i=0; i<max_confs; ++i){
        confList[i]=createLList();					//this loop creates linked lists within the array of linked lists (confList). i.g. if the number of conferences is 3 then creates 3 lists.
    }

    for(i=0; i<num; ++i){									//this loop populates the linked lists by the number of conference. i.g. if the eastern conference then puts team in the first list, else if the western conference then puts team in the second list.
        if (array[i]->conf==1){
            insertNodeInLList(confList[0],array[i],i+1);
        }
        else if (array[i]->conf==2){
            insertNodeInLList(confList[1],array[i],j+1);
            ++j;
        }
    }

    TeamInfoPtr_t tInfo=(TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));							//creates team info pointer tInfo.

    printf("\nMLS (Eastern Conference):\n");
    for(i=LListLength(confList[0]);i>0;--i){		//This loop prints the team's name if the team is within the eastern conference.
        tInfo=getTeamInfoRecord(confList[0],i);		//confList[0] holds the teams within the eastern conference. this line assigns the team info to tInfo.
        printf("   %s\n",tInfo->name);
    }
    printf("\nMLS (Western Conference):\n");
    for(i=LListLength(confList[1]);i>0;--i){		//This loop prints the team's name if the team is within the western conference
        tInfo=getTeamInfoRecord(confList[1],i);		//confList[1] holds the teams within the western conference. this line assigns the team info to tInfo.
        printf("   %s\n",tInfo->name);
    }

    printf("\nFive teams with the best winning percentage:\n");
    double wins,loss,draws,percentage[num];			//The first three variables hold the wins,losses and draws of each team. percentage is an array that holds the percentage of wins of each team.
    int bestFive[num], q=0;							//bestFive is an array that holds the indices of percentages of the best five teams by wins.
    for(i=0;i<num;++i){								//this loop populates the percentage array with the percentage of wins of each team.
        tInfo=array[i];
        wins=array[i]->wins;
        loss=array[i]->losses;
        draws=array[i]->draws;
        percentage[i]=((wins)/(wins+loss+draws))*100.0;
    }
    double temp[num];								//temp is an array that holds the percentages of wins temporarily.
    for(i=0;i<num;++i){
        temp[i]=percentage[i];
    }

    double maxper;									//this variable holds the maximum percentage.  So it can be used in the loop below.

    for(i=0;i<num;++i){								// this loop checks for the maximum percentage and then puts an index of the maximum percentage within bestFive array.
        maxper=temp[i];
        for(j=0;j<num;++j){
            if(temp[j]>=maxper){
                maxper=temp[j];
                bestFive[q]=j;
            }
        }
        temp[bestFive[q]]=0;
        ++q;
    }
    for(i=0;i<5;++i){								//this loop prints the info of the best 5 teams by wins.
        printf("\n %d:\n",i+1);
        display_team_info(array[bestFive[i]]);
        printf("  Percentage: %.1lf%%\n",percentage[bestFive[i]]);
    }

    printf("\nThe team with most wins:\n");
    i=0;
    int mostWins=array[i]->wins;					//this variable holds the most wins of a team.
    for(i=0;i<num;++i){								//this loop checks for the maximum wins and then assigns j with the index of the team with the maximum wins.
        if(array[i]->wins>mostWins){
            mostWins=array[i]->wins;
            j=i;
        }
    }
    display_team_info(array[j]);					//prints the info the team with the most wins.
    printf("\nThe team with most losses:\n");
    i=0;
    int mostloss=array[i]->losses;					//this variable holds the most losses of a team.
    for(i=0;i<num;++i){								//this loop checks for the most losses and then assigns j to an index of the team with most losses.
        if(array[i]->losses>mostloss){
            mostloss=array[i]->losses;
            j=i;
        }
    }
    display_team_info(array[j]);					//prints the info the team with most losses.


    return 0;
}
