/*
 * teamInfo.c - Team info source code file for mls app
 *
 * Originator: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author: Abdullah Almarzouq (an36@pdx.edu)
 *
 * This is the source code file that for functionality specific to the Team Info database that
 * is part of an ECE 361 homework assignment.
 *
 * This file, and its associated header files (including the functions that you
 * need to provide) are meant to be used by your Linked List ADT and main() to deliver
 * the functionality required in the assignment
 *
 * @note:  You need to provide the code for several of these functions
 */

// include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "teamInfo.h"
#include "teamInfo_LinkedList.h"

// constants
#define MAX_TEAMS 100
#define NUM_OF_FIELDS_PER_RECORD 7

/**
 * Creates a new Team Info record
 *
 * @param name      (pointer to a char[]) containing the name of the team
 * @param nickname  (pointer to a char[]) containing the nickname of the team
 * @param league    (int) containing the league the team plays in (MLS, NWSL, USL, Other)
 * @param conf      (int) containing the conference the team plays in (Eastern, Wsstern, NWSL, Other}
 * @param nwins     (int) containing the number of wins during the regular season
 * @param nlosses   (int) containing the number of losses during the regular season
 * @param ndraws    (int) containing the number of draws during the regular season
 *
 * @returns         a pointer to a new TeamInfo record. The caller can check for validity
 * by checking for a "" name
 */
TeamInfoPtr_t createTeamInfoRecord(const char* name, const char* nickname, int league,
					int conf, int nwins, int nlosses, int ndraws)
{
		 //ADD YOUR CODE HERE
			TeamInfoPtr_t tInfo = (TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));    //allocates memory for the pointer that would hold each team info

			if (!tInfo){   							//if memory hasn't been allocated then return error message and exit
				printf("struct is empty");
				exit(1);
			}

			strcpy(tInfo->name, name);							// copy the team's name to the name variable within a structure
			strcpy(tInfo->nickname, nickname);					// copy the nickname into the nickname's variable within a structure
			tInfo->league = league;								// assigns team's league to param league
			tInfo->conf = conf;									// assigns team's conference to param conf
			tInfo->wins = nwins;								// assigns team's wins to param nwins
			tInfo->losses = nlosses;							// assigns team's losses to param nlosses
			tInfo->draws = ndraws;								// assigne team's draws to param ndraws

			return tInfo;    					// returns pointer to a team info after it has been created
}


/**
* Displays the information from a team record on stdout
*
* @param teamInfoPtr    (pointer to the team record) being examined
*
* @returns          nothing
*/
void display_team_info(TeamInfoPtr_t teamInfoPtr)
{
    int confn=teamInfoPtr->conf;                     //variable confn holds the number of conferece to be used by get_conf_str function
    int leagn=teamInfoPtr->league;					 //variable leagn holds the number of league to be used by the get_league_str function
    printf("  Team : %s (%s)\n",teamInfoPtr->name,teamInfoPtr->nickname);						//prints the team's name and nickname
    printf("  League: %s (%s)\n",get_league_str(leagn),get_conf_str(confn));					//prints the team's league and conferece using helper functions
    printf("  Record: %d-%d-%d\n",teamInfoPtr->wins,teamInfoPtr->losses,teamInfoPtr->draws);	//prints record of teams wins-losses-draws
}

/**
*	The function below gets each team's info from the linked list that the team is located in.
*
*   @param L  is the linked list that the team is located in.
* 	@param pos is the position of the team within the list. (where the teams is located within the list).
*	
*	return tInfo which is a teamInfoPtr that points to the info of the located team.
*/
TeamInfoPtr_t getTeamInfoRecord(LinkedListPtr_t L, int pos){
	// ADD YOUR CODE HERE
	LinkedListPtr_t list=(LinkedListPtr_t) malloc(sizeof(LinkedList_t));	//list is a temporary linked list which is assigned to the param L list.
	list=L;
	ListNodePtr_t temp=(ListNodePtr_t) malloc(sizeof(ListNode_t));			// temp is a temporary pointer to a node within the list.
	temp=(*list).head;
	int cnt=(*list).count;						//cnt is a counter variable starts with the element on top of the list.
	for(int i=(*list).count; i>=pos;--i){		// a for loop that traverse the linked list till it finds the wanted node within the list.
        if(cnt==pos){	
			TeamInfoPtr_t tInfo;
			tInfo=(TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));
            tInfo=(*temp).data;					//if the loop finds the desired node then assigns tInfo to the data within the node. (data holds the team info within a node).
			return tInfo;
		}
        else{
            temp=(*temp).next;					//if the node is not the desired one then go to the next node within the list and decrement the counter cnt
            cnt-=1;
        }
	}
	free(temp);									//frees the temporary list node pointer temp
    TeamInfoPtr_t ttt=(TeamInfoPtr_t)malloc(sizeof(TeamInfo_t));
	ttt=NULL;
	return ttt;								//returns tInfo which hold the desired team info
}


/**
 * readTeamInfo() - reads the team info from a file
 * and creates an array of pointers to team Info records
 *
 * @param fname     (pointer to char[]) file name of  team info file to read
 * @param teams[]   (array of team info records) array to put pointers to team records into
 *
 * @returns         the number of team records stored
 *
 * @note You may have to include part (or all) of the absolute path in the file name.  It depends
 * on what directory(s) you are building and running your application from
 */
int readTeamInfo(char* fname, TeamInfoPtr_t  teams[])
{
    FILE *fp;           // pointer to team info file
    char buf[100];      // input buffer

    // holding variables for fields in the team info record
    char tir_name[MAX_TEAM_NAME];
    char tir_nickname[MAX_TEAM_NICKNAME];
    int tir_league;
    int tir_conf;
    int tir_wins;
    int tir_losses;
    int tir_draws;

    int nfields = 0;		// number of fields read from file
    int nrecs = 0;          // number of records
    TeamInfoPtr_t tir;		// pointer to team info record

    // open the team info file for reading
    if ((fp = fopen(fname, "r")) == NULL) {
        fprintf(stderr, "readTeamInfo: Could  not open team info file: %s (%s)...exiting\n",
			fname, strerror(errno));
        exit(1);
    }

	tir = (TeamInfoPtr_t) malloc(sizeof(TeamInfo_t));
	if (!tir) {
		fprintf(stderr, "readTeamInfo: Could not create Team Info record...exiting\n");
		exit(1);
	}

	// ready to read team info records
    printf("readTeamInfo: Reading team info file...\n");

    // get record from team info file
    while (!feof(fp)) {
		fgets(buf, sizeof(buf), fp);
		buf[strlen(buf) - 1] = '\0';    // trim the string
		if ((buf[0] == '/') && (buf[1] == '/'))  {
			// this is a comment, display and skip it
			printf("%s\n", buf);
		}  // display and skip comments
		else {  // try to process a team info record
			if (strlen(buf) > 0) {  // is it a blank line?
				// use scanf() to parse the team info line in the file
				nfields = sscanf(buf, "%30s %5s %d %d %d-%d-%d",
					tir_name, tir_nickname, &tir_league, &tir_conf,
					&tir_wins, &tir_losses, &tir_draws);

				if (nfields != NUM_OF_FIELDS_PER_RECORD) {  // is the team info line valid?
					// error parsing the line
					fprintf(stderr,
					"readTeamInfo: Error parsing team info record: #fields read = %d\tline=%s\n",
					nfields, buf);
					fprintf(stderr,
  					  "name= %s\tnickname= %s\tleague= %d\tconference= %d\twins-losses-ties= %d-%d-%d\n",
					tir_name, tir_nickname, tir_league, tir_conf, tir_wins, tir_losses, tir_draws);
				}  // invalid team info line - wrong number of fields
				else {  // add the record to the array of teams
					// replace underscores ('_') with space in the team name
					for(int i = 0; i < strlen(tir_name); i++) {
						if (tir_name[i] == '_') {
							tir_name[i] = ' ';
						}
					}

					// create a new team info record and add it to the array
					tir = createTeamInfoRecord(tir_name, tir_nickname, tir_league, tir_conf, tir_wins,
						tir_losses, tir_draws);
					teams[nrecs] = tir;
					printf("readTeamInfo: Added record %d\n", nrecs);
					nrecs++;
				} // right number of fields - add team info record to array
			} // not an empty line
		} // try to process a team info record
    } // read all of the line of the file
    fclose(fp);
    return nrecs;
}



// Helper functions

/**
 * get_conf_str() - returns a string containing the conference the team plays.
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param conf    (int) conference
 *
 * @returns         a pointer to a char array holding the conference the team plays in
 */
static char* get_conf_str(int conf)
{
    static char conf_ptr[MAX_CONF_TXT];	// string containing name of conference.
									// static so it hangs around after function returns
    switch (conf)
    {
        case CONF_OTHER:     strcpy(conf_ptr, "OTHER");     break;
        case CONF_EASTERN:   strcpy(conf_ptr, "EASTERN");   break;
        case CONF_WESTERN:   strcpy(conf_ptr, "WESTERN");   break;
        case CONF_NWSL:      strcpy(conf_ptr, "NWSL");      break;

        default:             strcpy(conf_ptr, "?????");     break;
    }
    return conf_ptr;
}


/**
 * get_league_str() - returns a string containing the league the team plays in.
 * Assumes that sufficient space has been allocated for the return string
 *
 * @param league   (int) league the team plays in
 *
 * @returns         a pointer to a char array holding the league the team plays in
 */
static char* get_league_str(int league)
{
	static char league_ptr[MAX_LEAGUE_TXT];	// string containing name of league.
											// static so it hangs around after function returns
    switch (league)
    {
        case LEAGUE_OTHER:   strcpy(league_ptr, "OTHER");   break;
        case LEAGUE_MLS:     strcpy(league_ptr, "MLS");     break;
        case LEAGUE_USL:     strcpy(league_ptr, "USL");     break;
        case LEAGUE_NWSL:    strcpy(league_ptr, "NWSL");    break;

        default:             strcpy(league_ptr, "?????");   break;
    }
    return league_ptr;
}
