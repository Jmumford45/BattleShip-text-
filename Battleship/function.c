//function.c
#include"header.h"
void welcome_screen(void)
{
   printf("\n\t\t\tBATTLESHIP!!!\n");
   printf("\n\t\t\tRules of Battleship: \n\n");
   printf("Players place their 'fleet' of 5 ships on their 'ocean', hidden from the\n");
   printf("opponent's view. Taking turns, players call out their 'shots' attempting to\n");
   printf("get 'hits' on the opponent's ships in order to sink them. Strategy and some\n");
   printf("luck must be combined to be the first to locate and sink all 5 opponent's\n");
   printf("ships to win the game. The object of the game is to be the first player to\n");
   printf("sink all five of his opponent's ships. Each player SECRETLY places his fleet\n");
   printf("of 5 ships on his ocean grid. Ships may be placed in any horizontal or vertical\n");
   printf("position - but NOT diagonally. You MAY NOT change the position of any ship.\n");
   printf("To do so would be cheating!\n\n");
   printf("This is a one player game where you are player1, and the computer is player2.\n\n");
   printf("Types of Ships: \tSize:\n\n");
   printf("Aircraft Carrier \t5 \nBattleship \t\t4 \nCruiser \t\t3 \nSubmarine \t\t3 \nDestroyer \t\t2\n\n");
   printf("Symbols: \n c - Aircraft Carrier\n b - Battleship\n r - Cruiser\n s - Submarine\n d - Destroyer\n");
   printf("\n ~ - Water\n * - Hit\n m - Miss\n");
}
/* Description:   This function uses a two-dimensional array   *
*           to intitialize the game board, place ships on the*
*           board, and update the board after each shot.   *
*/
char initialize_game_board(int x1, int y1, int x2, int y2, char board[10][10], int print, int player,
                           int xtarget, int ytarget, int *hits, char visible[10][10], char type)
{
   int x = 0, y = 0;
   if(print != 0)
   {
       printf("\n\t    0 1 2 3 4 5 6 7 8 9\n");
       printf("\t +---------------------+\n\t");
   }
   for(x = 0; x < 10; x++)
   {
       if((x < 9)&&(print != 0))
       {
           printf("%d | ", x);
       }
       if((x == 9)&&(print != 0))
       {
           printf("%d | ", x);
       }
       for(y = 0; y < 10; y++)
       {
           if((board[x][y] != 'c')&&(board[x][y] != 'b')&&(board[x][y] != 'r')&&(board[x][y] != 's')&&(board[x][y] != 'd')
               &&(board[x][y] != '*')&&(board[x][y] != 'm'))
           {
               board[x][y] = '~';
               if((((x == x1)&&(y == y1))||((x == x2)&&(y == y2)))&&(print != -1))
               {
                   board[x][y] = type;
               }
               if((((x < x1)&&(x > x2)&&(y == y1))||((x > x1)&&(x < x2)&&(y == y1)))&&(print != -1))
               {
                   board[x][y] = type;
               }
               if((((y < y1)&&(y > y2)&&(x == x1))||((y > y1)&&(y < y2)&&(x == x1)))&&(print != -1))
               {
                   board[x][y] = type;
               }
           }
           if(board[x][y] == '~')
           {
               visible[x][y] = '~';
           }
           if((board[x][y] >= 'b')&&(board[x][y] <= 's')&&(board[x][y] != 'm'))
           {
               visible[x][y] = '~';
           }
           if(board[x][y] == 'm')
           {
               visible[x][y] = 'm';
           }
           if(board[x][y] == '*')
           {
               visible[x][y] = '*';
           }
           if((x == xtarget)&&(y == ytarget))
           {
               if((board[x][y] >= 'b')&&(board[x][y] <= 's'))
               {
                   visible[x][y] = '*';
                   board[x][y] = '*';
                   *hits = *hits + 1;
               }
               if(board[x][y] == '~')
               {
                   visible[x][y] = 'm';
                   board[x][y] = 'm';
               }
           }
           //player = 1;   //Uncomment this to see the enemy's ships!!!
           if((print != 0)&&(player == 1))
           {
               printf("%c ", board[x][y]);
           }
           if((print != 0)&&(player == 2))
           {
               printf("%c ", visible[x][y]);
           }
           if((y == 9)&&(print != 0))
           {
               printf("| %d\n\t", x);
           }
       }
   }
   if(print != 0)
   {
       printf(" +---------------------+\n");
       printf("\t    0 1 2 3 4 5 6 7 8 9\n\n");
   }
   return board;
}
/**Description:   This function decides and returns which       *
*           player goes first.                               */
int select_who_starts_first(void)
{
   int select = 0, player = 0;
   select = rand() % 2;
   if(select == 0)
   {
       printf("Player1 (Human) goes first. . .\n\n");
       player = 1;
   }
   if(select == 1)
   {
       printf("Player2 (CPU) goes first. . .\n\n");
       player = 2;
   }
   return player;
}
/**Description:   This function prompts the user to decide   *
*           whether to place their ships randomly or manually*/
int deploy_ships(void)
{
   int deploy = 0;
   printf("How would you like to deploy your ships?\n1) Manually\n2) Randomly\n\n");
   scanf("%d", &deploy);
   return deploy;
}
/* manually_place_ships_on_board()               *
* Description:   This function prompts the user to enter the *
*           endpoint coordinates for each ship.               */
void manually_place_ships_on_board(int *x1, int *y1, int *x2, int *y2, int size, char board[10][10])
{
   int check = 0, x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, x = 0, y = 0;
   do{
   do{
   check = 0; x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0, *x1 = 0, *y1 = 0, *x2 = 0, *y2 = 0;
   printf("Enter the endpoint coordinates for your Ship, size: %d: \n", size);
   scanf("%d %d %d %d", y1, x1, y2, x2);
   if((*x1 != *x2)&&(*y1 != *y2))
   {
       printf("The ship cannot be diagonal!\n");
   }
   if(*y1 == *y2)
   {
       check = abs(*x1 - *x2) + 1;
   }
   if(*x1 == *x2)
   {
       check = abs(*y1 - *y2) + 1;
   }
   if(check != size)
   {
       printf("The ship does not fit those coordinates!\n");
   }
   }while(((*x1 < 0)||(*x1 > 9))||((*y1 < 0)&&(*y1 > 9))||((*x2 < 0)||(*x2 > 9))||((*y2 < 0)&&(*y2 > 9))||
           ((*x1 != *x2)&&(*y1 != *y2))||(check != size));
   if(*y1 == *y2)
   {
       if(*x1 > *x2)
       {
           if(size > 2)
           {
               x_1 = *x2 + 1;
               y_1 = *y1;
           }
           if(size > 3)
           {
               x_2 = *x2 + 2;
               y_2 = *y1;
           }
           if(size > 4)
           {
               x_3 = *x2 + 3;
               y_3 = *y1;
           }
       }
       if(*x1 < *x2)
       {
           if(size > 2)
           {
               x_1 = *x1 + 1;
               y_1 = *y1;
           }
           if(size > 3)
           {
               x_2 = *x1 + 2;
               y_2 = *y1;
           }
           if(size > 4)
           {
               x_3 = *x1 + 3;
               y_3 = *y1;
           }
       }
   }
   if(*x1 == *x2)
   {
       if(*y1 < *y2)
       {
           if(size > 2)
           {
               x_1 = *x1;
               y_1 = *y1 + 1;
           }
           if(size > 3)
           {
               x_2 = *x1;
               y_2 = *y1 + 2;
           }
           if(size > 4)
           {
               x_3 = *x1;
               y_3 = *y1 + 3;
           }
       }
       if(*y1 > *y2)
       {
           if(size > 2)
           {
               x_1 = *x1;
               y_1 = *y2 + 1;
           }
           if(size > 3)
           {
               x_2 = *x1;
               y_2 = *y2 + 2;
           }
           if(size > 4)
           {
               x_3 = *x1;
               y_3 = *y2 + 3;
           }
       }
   }
   if((((board[*x1][*y1] > 'a')&&(board[*x1][*y1] < 'z'))||((board[*x2][*y2] > 'a')&&(board[*x2][*y2] < 'z'))||(((board[x_1][y_1] > 'a')&&(board[x_1][y_1] < 'z'))&&(size > 2))||
       (((board[x_2][y_2] > 'a')&&(board[x_2][y_2] < 'z'))&&(size > 3))||(((board[x_3][y_3] > 'a')&&(board[x_3][y_3] < 'z')&&(size > 4)))))
   {
       printf("Your ships cannot overlap!\n");
   }
   }while((((board[*x1][*y1] > 'a')&&(board[*x1][*y1] < 'z'))||((board[*x2][*y2] > 'a')&&(board[*x2][*y2] < 'z'))||(((board[x_1][y_1] > 'a')&&(board[x_1][y_1] < 'z'))&&(size > 2))||
       (((board[x_2][y_2] > 'a')&&(board[x_2][y_2] < 'z'))&&(size > 3))||(((board[x_3][y_3] > 'a')&&(board[x_3][y_3] < 'z')&&(size > 4)))));
}
/* Description:   This function randomly generates the       *
*           endpoint coordinates (x1, y1, x2, y2) for each   *
*           ship.                                           */
void randomly_place_ships_on_board(int *x1, int *y1, int *x2, int *y2, int size, char board[10][10])
{
   int way = 0, x_1 = 0, y_1 = 0, x_2 = 0, y_2 = 0, x_3 = 0, y_3 = 0;
   do{
   *x1 = rand() % 10;
   *y1 = rand() % 10;
   way = rand() % 2;
   if(way == 0)
   {
       *x2 = *x1 - size + 1;
       *y2 = *y1;
       if(size > 2)
       {
           x_1 = *x2 + 1;
           y_1 = *y1;
       }
       if(size > 3)
       {
           x_2 = *x2 + 2;
           y_2 = *y1;
       }
       if(size > 4)
       {
           x_3 = *x2 + 3;
           y_3 = *y1;
       }
   }
   if(way == 1)
   {
       *y2 = *y1 - size + 1;
       *x2 = *x1;
       if(size > 2)
       {
           x_1 = *x1;
           y_1 = *y2 + 1;
       }
       if(size > 3)
       {
           x_2 = *x1;
           y_2 = *y2 + 2;
       }
       if(size > 4)
       {
           x_3 = *x1;
           y_3 = *y2 + 3;
       }
   }
   }while((*x2 < 1)||(*y2 < 1)||(*x2 > 9)||(*y2 > 9)||((board[*x1][*y1] > 'a')&&(board[*x1][*y1] < 'z'))||
       ((board[*x2][*y2] > 'a')&&(board[*x2][*y2] < 'z'))||((board[x_1][y_1] > 'a')&&(board[x_1][y_1] < 'z'))||
       ((board[x_2][y_2] > 'a')&&(board[x_2][y_2] < 'z'))||((board[x_3][y_3] > 'a')&&(board[x_3][y_3] < 'z')));
}
/*Description:   This function prompts the user to enter the   *
*           target coordinates (xtarget, ytarget)           */
void shoot_manual(int *xtarget, int *ytarget, char board[10][10])
{
   do{
   do{
   printf("Enter target coordinates: \n");
   scanf("%d %d", ytarget, xtarget);
   if((*xtarget > 9)||(*xtarget < 0)||(*ytarget > 9)||(*ytarget < 0))
   {
       printf("Your target coordinates must be from 0-9!\n");
   }
   }while((*xtarget > 9)||(*xtarget < 0)||(*ytarget > 9)||(*ytarget < 0));
   if((board[*xtarget][*ytarget] == '*')||(board[*xtarget][*ytarget] == 'm'))
   {
       printf("You have already shot there! \n");
   }
   }while((board[*xtarget][*ytarget] == '*')||(board[*xtarget][*ytarget] == 'm'));
}
void shoot_random(int *xtarget, int *ytarget, char board[10][10])
{
   do{
   *xtarget = rand() % 10;
   *ytarget = rand() % 10;
   }while((board[*xtarget][*ytarget] == '*')||(board[*xtarget][*ytarget] == 'm'));
}
int check_ship(char board[10][10], int *sunkc, int *sunkb, int *sunkr, int *sunks, int *sunkd)
{
   int x = 0, y = 0, c = 0, b = 0, r = 0, s = 0, d = 0;
   for(x = 0; x < 10; x++)
   {
       for(y = 0; y < 10; y++)
       {
           if((board[x][y] == 'c')&&(*sunkc == 0))
           {
               c++;
           }
           if((board[x][y] == 'b')&&(*sunkb == 0))
           {
               b++;
           }
           if((board[x][y] == 'r')&&(*sunkr == 0))
           {
               r++;
           }
           if((board[x][y] == 's')&&(*sunks == 0))
           {
               s++;
           }
           if((board[x][y] == 'd')&&(*sunkd == 0))
           {
               d++;
           }
       }
   }
   if((c == 0)&&(*sunkc != -1))
   {
       printf("You sunk my Aircraft Carrier!\n");
       *sunkc = 1;
   }
   if((b == 0)&&(*sunkb != -1))
   {
       printf("You sunk my Battleship!\n");
       *sunkb = 1;
   }
   if((r == 0)&&(*sunkr != -1))
   {
       printf("You sunk my Cruiser!\n");
       *sunkr = 1;
   }
   if((s == 0)&&(*sunks != -1))
   {
       printf("You sunk my Submarine!\n");
       *sunks = 1;
   }
   if((d == 0)&&(*sunkd != -1))
   {
       printf("You sunk my Destroyer!\n");
       *sunkd = 1;
   }
}
/*Description:   This function prints to file, the info       *
*           associated with each player's shot:   Target Coords*
*           hit or miss, if a ship was sunk                   */
void output_move(FILE *outfile, int xtarget, int ytarget, int player, int hit, int *sunkc, int *sunkb, int *sunkr, int *sunks, int *sunkd)
{
   if((xtarget != -1)&&(ytarget != -1))
   {
       fprintf(outfile, "Player%d: (%d,%d)\t", player, xtarget, ytarget);
   }
   if(hit == 1)
   {
       fprintf(outfile, "Hit!\n");
   }
   if(hit == 0)
   {
       fprintf(outfile, "Miss...\n");
   }
   if(*sunkc == 1)
   {
       fprintf(outfile, "Sunk Aircraft Carrier!\n");
       *sunkc = -1;
   }
   if(*sunkb == 1)
   {
       fprintf(outfile, "Sunk Battleship!\n");
       *sunkb = -1;
   }
   if(*sunkr == 1)
   {
       fprintf(outfile, "Sunk Cruiser!\n");
       *sunkr = -1;
   }
   if(*sunks == 1)
   {
       fprintf(outfile, "Sunk Submarine!\n");
       *sunks = -1;
   }
   if(*sunkd == 1)
   {
       fprintf(outfile, "Sunk Destroyer!\n");
       *sunkd = -1;
   }
   fprintf(outfile, "\n");
}
/**Description:   This function prints to file, the game stats *
*           for each player.(Hits, Misses, Shots, Accuracy)   */
void output_stats(FILE *outfile, stats player)
{
   if(player.win == 1)
   {
       fprintf(outfile, "\nPlayer%d Wins!!\n", player.player_num);
   }
   if(player.win == 0)
   {
       fprintf(outfile, "\nPlayer%d Losses... \n", player.player_num);
   }
   fprintf(outfile, "\n***Player%d Stats***\nHits: %d\nMisses: %d\nTotal Shots: %d\nAccuracy: %.2lf%%\n\n",
           player.player_num, player.hits, player.misses, player.shots, player.accuracy);
}
