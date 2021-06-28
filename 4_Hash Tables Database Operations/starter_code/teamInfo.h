/*
 * teamInfo.h - Team info header file for mls app
 *
 * Originator: Roy Kravitz (roy.kravitz@pdx.edu)
 * Author:  Abdullah Almarzouq (an36@pdx.edu)
 *
 * This is the header file for constants, variables, and function prototypes
 * for functionality specific to the Team Info database.
 *
 * This file, and its associated source code file are meant to be used by your Linked List ADT and main() to deliver
 * the functionality required in the assignment
 */

#ifndef _TEAM_INFO_H_
#define _TEAM_INFO_H_

// Constants and Macros
#define MAX_TEAM_NAME		30	// maximum length of team name string
#define MAX_TEAM_NICKNAME	5	// maximum length of a team nickname string
#define MAX_LEAGUE_TXT		10	// maximum length of text for the league the team plays in
#define MAX_CONF_TXT		10	// maximum length of text for the conference the team plays in
#define MAX_TEAMS 100			// maximum number of teams within a file

// enums and typedefs
typedef enum {LEAGUE_OTHER = 0, LEAGUE_MLS = 1,LEAGUE_NWSL = 2, LEAGUE_USL = 3} LEAGUE_t;
typedef enum {CONF_OTHER = 0, CONF_EASTERN = 1, CONF_WESTERN = 2, CONF_NWSL = 3}CONF_t;

// define the struct that contains the team info
typedef struct _teaminfo
{
	char name[MAX_TEAM_NAME];
	char nickname[MAX_TEAM_NICKNAME];
	int league;
	int conf;
	int wins;
	int losses;
	int draws;
} TeamInfo_t, *TeamInfoPtr_t;

// function prototypes

/* TODO: YOU NEED TO WRITE THIS FUNCTION */
TeamInfoPtr_t createTeamInfoRecord(const char* name, const char* nickname, int league,
					int conf, int nwins, int nlosses, int ndraws);

/* TODO: THIS FUNCTION IS PROVIDED BUT YOU MAY WANT TO MODIFY IT */
int readTeamInfo(char* fname, TeamInfoPtr_t teams[]);

/* TODO: YOU NEED TO WRITE THIS FUNCTION */
void displayTeamInfo(TeamInfoPtr_t teamInfoPtr);

static char* get_conf_str(int conf);

static char* get_league_str(int league);

#endif
