/*  main.c  -  Lets the user search for desired team info within a hash table or specifically the file "teaminfo2.txt"
 *
 *  Author: Abdullah Almarzouq (an36@pdx.edu)
 *
 *  The program below in main.c lets the user to find the desired team info within several hash tables by asking
 *  the user to enter the name of the league and the nickname of the team, then the program will print the record of the
 *  desired team and will ask the user to enter the league and name of another team.  The user can quit by simply
 *  clicking Enter (entering a newline).
 *
 *  The program creates several hash tables, depending on the number of league, and stores those hash tables within
 *  an array called (hts).  Then, when the user enters a league's name, the program will call a function called hash_index
 *  which returns an index to the desired hash table that holds the teams of the desired league.  If the entered league's name
 *  is not found then the program will ask again.
 *  After that the program will ask the user to enter the team's nickname then the program will search the desired hash table for
 *  that nickname, if the nickname is not found then the program ask the user again.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "starter_code/teamInfo.h"
#include "starter_code/hash_table.h"
int main()
{
    int i=0, maxLeagues=0;              // int i is a loop index and int maxLeagues will hold the maximum number of leagues
    char key[MAX_TEAM_NICKNAME];        // char key[] will hold the nickname of the desired team (entered by user)
    char league[MAX_LEAGUE_TXT];        // char league[] will hold the name of the desired league (entered by user)

    TeamInfoPtr_t teams[MAX_TEAMS];     //this array will hold each team's info and it is going to be used by the function readTeamInfo()
    TeamInfoPtr_t tir;                  //this team info pointer will hold the desired team's info after it has been found from the hash table

    int tnum = readTeamInfo("data/teaminfo2.txt",teams);     //tnum hold the number of records found in teaminfo2.txt, also the function readTeamInfo will put all those record in teams[] array

    for(i=0; i<tnum; ++i){                   // this loop will search through the teams[] array to find the maximum number of leagues
        if(teams[i]->league>maxLeagues){
            maxLeagues=teams[i]->league;     // holds the maximum number of leagues
        }
    }
    ht_hash_table *hts[maxLeagues];         // hash tables array which hold a number of hash tables that is equal to the maximum number of leagues

    for(i=0; i<maxLeagues; ++i){            //this loop will create new hash tables within the array hts depending on the number of league
        hts[i]=ht_new();
    }

    for(i=0; i<tnum; ++i){                  //this loop populates the each hash table with the teams info depending on the team's league
        if (teams[i]->league==1){                           //if the league of the team is 1 then insert the team's info in this hash table
            ht_insert(hts[0],teams[i]->nickname,teams[i]);
        }
        else if (teams[i]->league==2){                      //if the league of the team is 2 then insert the team's info in this hash table
            ht_insert(hts[1],teams[i]->nickname,teams[i]);
        }
        if (teams[i]->league==3){                           //if the league of the team is 3 then insert the team's info in this hash table
            ht_insert(hts[2],teams[i]->nickname,teams[i]);
        }
    }

    while(1){                                       // this while loop is used so that the program keeps on asking the user for a new team's league and nickname to be searched

        int index=-1, found=-1;                     // int index is used to specify which hash table, within an array, to be searched
                                                    // int found is used so that the program knows that the nickname of the team is found in a hash table

        printf("\nEnter the name of the league (CAPS ONLY): ");     //asks the user for the name of the league
        fgets (league, sizeof (league), stdin);
        league[strlen(league)-1]='\0';

        if(strcmp(league,"\0")==0){                 // if the user enter only a newline (clicked enter) then exit the program
            exit(-1);
        }

        index = hash_index(league);                 //the function hash_index(league) returns the index of the desired hash table within an array, i.g. if league is MLS then index is 0 (hts[0]) first hash table

        while(index==-1){                           //this while loop asks the user to enter the league's name again.  index in initialized with -1, if the user didn't entered a recognizable league then the index doesn't change.
            printf("\nError: There is no league with that name\nPlease enter the name of the league again: ");
            fgets (league, sizeof (league), stdin);
            league[strlen(league)-1]='\0';
            if(strcmp(league,"\0")==0){             // this statement quits the program if the user entered a newline.
                exit(-1);
            }
            index = hash_index(league);             //returns an index of the desired hash table. i.g. if league is NWSL then index is 1 (hts[1]) second hash table
        }

        printf("\nPlease enter the nickname of the team (CAPS ONLY): ");    //asks the user to enter the desired team's nickname
        fgets (key, sizeof (key), stdin);
        key[strlen(key)-1]='\0';

        if((strcmp(key,"\0")==0)){              //this statement quit the program if the user entered a newline.
            exit(-1);
        }

        while(found==-1){                   //this while loop searches for the nickname in the desired hash table, if not found then ask the user again. The variable found=-1 doesn't change unless the desired team's nickname is found in a hash table.
            printf("\n");
            if((tir=(TeamInfoPtr_t) ht_search(hts[index],key))==NULL){      //searches for the team's nickname in the desired hash table
                printf("\nThere is no team with that nickname in this league\nPlease enter the team's nickname again: ");
                fgets (key, sizeof (key), stdin);
                key[strlen(key)-1]='\0';

                if(strcmp(key,"\0")==0){        //quits the program if the user entered a newline
                    exit(-1);
                }
            }
            else{
                printf("\n");
                displayTeamInfo(tir);           //if the desired team is found within the hash table, then display the team's info
                found=0;                        // sets variable 'found' to 0 so that it quit this last while loop and the program can ask the user to enter the league name again to find info of another team
            }
        }
    }

    return 0;
}
