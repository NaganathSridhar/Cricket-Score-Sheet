/*
 * main.c
 *
 *  Created on: 06-May-2023
 *      Author: Naganath
 */

//CRICKET SCORE SHEET FOR A T20 MATCH

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A C-Structure to store Batsman info
struct bat
{
	char bat_name[50];
	float bat_runs;
	float bat_balls;
	int bat_4;
	int bat_6;
	float bat_sr;
	struct bat *next;
};

// A C-Structure to store Bowler info
struct bowl
{
	char bowl_name[50];
	float overs;
	int maidens;
	int bowl_runs;
	int bowl_wkts;
	float bowl_econ;
	struct bowl *next;
};

// Function Prototype
/*
 *  Function Name: insertlast_bat()
 *  Function Definition: Used to store the data of Batsman entered in the Batsman Array. (For 1 Batsman)
 */
void insertlast_bat(struct bat** head,int i)
{
    struct bat* newnode = (struct bat*) malloc(sizeof(struct bat));

    struct bat *last = *head;

    char bat_name[50];
    float bat_runs;
    float bat_balls;
    int bat_4;
    int bat_6;

    printf("Batter %d:\n",i+1);
    printf("Name: ");
    getchar();
    gets(bat_name);
    printf("Runs scored: ");
    scanf("%f",&bat_runs);
    printf("Balls faced: ");
    scanf("%f",&bat_balls);
    printf("Number of 4s scored: ");
    scanf("%d",&bat_4);
    printf("Number of 6s scored: ");
    scanf("%d",&bat_6);
    printf("\n");

    if((bat_4*4)+(bat_6*6)>bat_runs)
    {
    	printf("Invalid data...Please enter the details again\n");
    	insertlast_bat(head,i);
    	return;
    }
    else if((bat_4+bat_6)>bat_balls)
    {
    	printf("Invalid data...Please enter the details again\n");
		insertlast_bat(head,i);
		return;
    }
    else if(bat_runs>0 && bat_balls==0)
    {
    	printf("Invalid data...Please enter the details again\n");
		insertlast_bat(head,i);
		return;
    }

    strcpy(newnode->bat_name,bat_name);

    newnode->bat_runs=bat_runs;

    newnode->bat_balls=bat_balls;

    newnode->bat_4=bat_4;

    newnode->bat_6=bat_6;

    // Calculating Strike Rate of the batsman
    newnode->bat_sr=(newnode->bat_runs*100/newnode->bat_balls);

    newnode->next = NULL;

    if (*head == NULL)
    {
       *head = newnode;
       return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newnode;
    return;
}

// Function Prototype
/*
 *  Function Name: insertlast_bowl()
 *  Function Definition: Used to store the data of Bowler entered in the Bowler Array. (For 1 Bowler)
 */
void insertlast_bowl(struct bowl** head, int i)
{
    struct bowl* newnode = (struct bowl*) malloc(sizeof(struct bowl));

    struct bowl *last = *head;

    char bowl_name[50];
    float overs;
    int maidens;
    int bowl_runs;
    int bowl_wkts;

    printf("Bowler %d:\n",i+1);
    printf("Name: ");
    getchar();
    gets(bowl_name);
    printf("Overs bowled: ");
    scanf("%f",&overs);
    printf("Maidens bowled: ");
    scanf("%d",&maidens);
    printf("Runs given: ");
    scanf("%d",&bowl_runs);
    printf("Wickets taken: ");
    scanf("%d",&bowl_wkts);
    printf("\n");

    if(maidens>overs)
    {
    	printf("Invalid data...Please enter the details again\n");
		insertlast_bowl(head,i);
		return;
    }
    else if(maidens==overs && bowl_runs>0)
    {
    	printf("Invalid data...Please enter the details again\n");
		insertlast_bowl(head,i);
		return;
    }
    else if(overs>4)
    {
		printf("Invalid data...Please enter the details again\n");
		insertlast_bowl(head,i);
		return;
    }

    strcpy(newnode->bowl_name,bowl_name);

    newnode->overs=overs;

    newnode->maidens=maidens;

    newnode->bowl_runs=bowl_runs;

    newnode->bowl_wkts=bowl_wkts;

    // Finding the economy of the bowler
	newnode->bowl_econ=newnode->bowl_runs/((int)newnode->overs+((newnode->overs-(int)newnode->overs)*16.667/10));

    newnode->next = NULL;

    if (*head == NULL)
    {
       *head = newnode;
       return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newnode;
    return;
}

// Function Prototype
/*
 *  Function Name: wkts()
 *  Function Definition: Used to return the total number of wickets fallen.
 */
int wkts(struct bowl **head,int bat_n)
{
	int wkts=0;

	struct bowl *temp;

	temp=(*head);
	while(temp!=NULL)
	{
		wkts+=(temp->bowl_wkts); // Adding Bowler Wickets
		temp=temp->next;
	}

	int run_out=0;

	printf("Number of runouts: "); // Adding the run-outs
	scanf("%d",&run_out);

	wkts+=run_out;

	if(wkts>bat_n)
	{
		printf("Invalid data (Number of Wickets fallen is greater than the total number of batters");
		exit(0);
	}
	else
	{
		return wkts;
	}
}

// Function Prototype
/*
 *  Function Name: total_score()
 *  Function Definition: Used to return the total runs scored by the batters in the innings.
 */
int total_score(struct bat **head)
{
	int runs=0;

	struct bat *temp;

	temp=(*head);

	while(temp!=NULL)
	{
		runs+=(temp->bat_runs);
		temp=temp->next;
	}

	return runs;
}

// Function Prototype
/*
 *  Function Name: print_bat()
 *  Function Definition: To display the Batting team's score card.
 */
void print_bat(struct bat **head)
{
	struct bat *temp;

	temp=(*head);

	printf("\n\nBatting Scorecard\n\n");

	printf("Batter		Runs	Balls	4s	6s	SR\n\n");

	while(temp!=NULL)
	{
		printf("%s		%d	%d	%d	%d	%.2lf\n",temp->bat_name,(int)temp->bat_runs,(int)temp->bat_balls,temp->bat_4,temp->bat_6,temp->bat_sr);
		temp=temp->next;
	}

	getchar();
	getchar();
}

// Function Prototype
/*
 *  Function Name: print_bowl()
 *  Function Definition: To display the Bowling score card.
 */
void print_bowl(struct bowl **head)
{
	struct bowl *temp;

	temp=(*head);

	printf("\n\nBowling Scorecard\n\n");

    printf("Bowler		Overs	Maidens	Runs	Wickets	Economy\n\n");

    while(temp!=NULL)
    {
    	printf("%s		%.1f	%d	%d	%d	%.2f\n",temp->bowl_name,temp->overs,(int)temp->maidens,temp->bowl_runs,temp->bowl_wkts,temp->bowl_econ);
    	temp=temp->next;
    }

    getchar();
    getchar();
}

// Function Prototype
/*
 *  Function Name: bat_search()
 *  Function Definition: To display the details of a particular batter.
 */
void bat_search(struct bat **head,char name[])
{
	struct bat *temp;

	temp=(*head);

	while(temp!=NULL)
	{
		if(strcmp(temp->bat_name,name)==0)
		{
			printf("Batter		Runs	Balls	4s	6s	SR\n");
			printf("%s		%d	%d	%d	%d	%.2lf\n",temp->bat_name,(int)temp->bat_runs,(int)temp->bat_balls,temp->bat_4,temp->bat_6,temp->bat_sr);
			break;
		}
		else
		{
			temp=temp->next;
		}
	}
}

// Function Prototype
/*
 *  Function Name: bowl_search()
 *  Function Definition: To display the details of a particular bowler.
 */
void bowl_search(struct bowl **head,char name[])
{
	struct bowl *temp;

	temp=(*head);

	while(temp!=NULL)
	{
		if(strcmp(temp->bowl_name,name)==0)
		{
			printf("Bowler		Overs	Maidens Runs	Wickets	Economy\n");
			printf("%s		%d	%d	%d	%d	%.2lf\n",temp->bowl_name,(int)temp->overs,(int)temp->maidens,temp->bowl_runs,temp->bowl_wkts,temp->bowl_econ);			break;
			break;
		}
		else
		{
			temp=temp->next;
		}
	}
}

// Function Prototype
/*
 *  Function Name: no_of_balls_bowled_VS_faced()
 *  Function Definition: To check whether the number of balls faced is greater than or equal to the number of balls bowled.
 */
int no_of_balls_bowled_VS_faced(struct bat** head1,struct bowl** head2)
{
	struct bat *temp1;
	temp1=*head1;
	struct bowl *temp2;
	temp2=*head2;

	int no_of_balls_bowled=0;
	int no_of_balls_faced=0;

	while(temp1!=NULL)
	{
		no_of_balls_faced+=temp1->bat_balls;
		temp1=temp1->next;
	}

	while(temp2!=NULL)
	{
		no_of_balls_bowled+=(((int)(temp2->overs*6))+((int)(temp2->overs-(int)temp2->overs)*10));
		temp2=temp2->next;
	}

	if(no_of_balls_faced<no_of_balls_bowled)
	{
		printf("Invalid data entered");
		getchar();
		exit(0);
	}
	else
	{
		return 0;
	}
}

// Function Prototype
/*
 *  Function Name: overs()
 *  Function Definition: To determine the total number of overs bowled.
 */
float overs(struct bowl** head)
{
	struct bowl *temp;
	temp=*head;
	float ov=0,ov1=0;

	while(temp!=NULL)
	{
		ov+=(int)temp->overs;
		ov1+=(temp->overs-(int)temp->overs);
		temp=temp->next;
	}

	ov+=(int)ov1/1+(ov1-(int)ov1);

	return ov;
}

int main()
{
	struct bat *head1=NULL;
	struct bowl *head2=NULL;

	printf("\t\t\t*****CRICKET SCORE SHEET*****\n\n");

	int bat_n,bowl_n,ch=0;

	while(1)
	{
		printf("\n1. To Enter Batter and Bowler Details\n2. To Display the batter and bowler details\n3. To print particular batter's and bowler's details\n4. Exit");
		printf("\n\nEnter your choice: ");
	    scanf("%d",&ch);
	    switch(ch)
	    {
	    	case 1:
	        {
	            printf("\nEnter the total number of batters: ");
	            scanf("%d",&bat_n);

	            if(bat_n>11 || bat_n<2)
	            {
	            	printf("Invalid input for the total number of batters...Please enter the correct total number of batters: ");
	            	scanf("%d",&bat_n);
	            }

	            printf("\nEnter the total number of bowlers: ");
	            scanf("%d",&bowl_n);

	            if(bat_n>11)
	            {
					printf("Invalid input for the total number of bowlers...Please enter the correct total number of bowlers");
					scanf("%d",&bowl_n);
				}

	        	for(int i=0;i<bat_n;i++)
	        	{
	        	    insertlast_bat(&head1,i);
	        	}

	        	for(int i=0;i<bowl_n;i++)
	        	{
	        	    insertlast_bowl(&head2,i);
	        	}
	        	break;
	         }

	    	case 2:
	        {
	        	int x=no_of_balls_bowled_VS_faced(&head1, &head2);
	        	if(x==0)
				{
	        		int wkts_1=wkts(&head2,bat_n);
					int runs=total_score(&head1);
					int ext=0;
					printf("Enter the extras: "); // Adding the extras
					scanf("%d",&ext);
					runs+=ext;
					print_bat(&head1);
					printf(" TOTAL SCORE : %d/%d (%.1f). ",runs,wkts_1,overs(&head2));
					printf("\n\nEXTRAS: %d\n",ext);
					print_bowl(&head2);
					break;
	        	}
	        }

	    	case 3:
	        {
	            char name_bat[50];
	            char name_bowl[50];
	            printf("Enter the batter's name to be searched: ");
	            getchar();
	            scanf("%s",name_bat);
	            printf("\n");
	            bat_search(&head1,name_bat);
	            printf("Enter the bowler's name to be searched: ");
	          	getchar();
	          	scanf("%s",name_bowl);
	          	printf("\n");
	            bowl_search(&head2,name_bowl);
	            break;
	        }

	    	case 4:
	        {
	            exit(0);
	            break;
	        }

	    	default:
	        {
	            printf("Invalid choice");
	            getchar();
	            getchar();
	        }
	    }
    }
    return 0;
}

