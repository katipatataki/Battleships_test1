#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    //P[1-4][...]= id ploiwn. P[...][1-4]= 1=X location, 2=Y location, 3=Rotation, 4=Health
    //Ephdei den exoume mathei 3sdiastatous pinakes gia ayto ekana A[20][10] anti gia A[10][10][2]
    //s = show enemy ships. patiste 0 0 otan sas zhtaei X kai Y location gia na to anoijete. bohthaei sto debuging
    //a= rotation, n= number of ships, p= ploia, G= age, st= Stage of Game, A[][]= board, pl= player, P[][]= ploia ID
    //g= value, N[]= Name, tm= Temp

    int a,n,p,i,j,G,Y,X,st,A[20][10],P[4][4],pl=0,s=-1;
    char g,N[100],tm;
    srand((unsigned)time(NULL));

    // misw ton kanona: Η λύση της εργασίας να γίνεται μόνο με χρήση εντολών που έχουν διδαχθεί στο μάθημα
    do {
        p=0; st=0; n=3; pl=0;


        printf("welcome to Battleships\n\nStarting board is 10*10\n");                   // arxizei task 1 edw

        for (i=0;i<10;i=i+1) {
            for (j=0;j<10;j=j+1) {
                A[i][j]=0;
                A[i+10][j]=0;
                printf(".");
                }
            printf("|\n");
        }

        printf("Write Your Name: ");

        scanf("%s",N);
        getchar();

        do {
            printf("Write Age: ");
            scanf("%d",&G);
            getchar();
            if (G>=120 || G<0) {
                printf("Wrong Age \nPlease enter a right age\n");
                G=-1;
            }
        } while (G>=120 || G<0);

        printf("your name is %s and your age %d\nGame started\nTime to place your ships\n", N, G);

        for (i=0;i<4;i=i+1) {
            P[i][3]=1;
        }


        n=3;                                                                //arxizei task 2 kai 3
        do {                                                                //st0= topothetish ploiwn, st1= Ai topothetish ploiwn, st2= paixnidi
            a=0;                                                            //Ship selection
            if (st==0) {
                printf("select ship: 1=2x and 2=4x\n");
                if (n==1||n==3) {
                    printf("<Ship 1 can be place>\n");
                } else {
                    printf("<>\n");
                }
                if (n==2||n==3) {
                    printf("<Ship 2 can be place>\n");
                } else {
                    printf("<>\n");
                }

                do {
                    scanf("%d",&p);
                    getchar();
                    if (p==1 || p==2) {
                        if (n==3 || p==n) {
                            printf("you want to place ship number %d\n",p);
                            n=n-p;
                        } else {
                            printf("You have placed that ship\nWrong value, place ship again\n");
                            p=0;
                        }
                    } else printf("Wrong value, place ship again\n");

                }while (p!=1 && p!=2);

            }





            do {
                if (st==0 || (st==2 && pl==0)) {
                    if (st==0) {
                        printf("Pick location:\nFirst put the X value and then the Y\nThe 00 location is in the down left of the board (just like chess)\nAdd values from 1-10: ");
                    } else {
                        printf("Player plays\nPick location to shoot\nWrite the X and Y locations\nAdd values from 1-10: ");
                    }

                    scanf("%d",&X);                                       //pick location
                    getchar();
                    scanf("%d",&Y);
                    getchar();

                    if (X==0 && Y==0) {
                        printf("<You Toggled show enemy ships>\n");
                        s=s*-1; //show enemy ships
                    }

                } else if (st==1 || (st==2 && pl==1)) {                             //AI pick location
                    X=(rand() % (10))+ 1;
                    Y=(rand() % (10))+ 1;
                    if (st==1) {
                        printf("Player plays\n");
                    } else {
                        printf("Computer plays\n");
                    }
                }
                printf("Location:(%d, %d)\n",X,Y);

                if (!(X<1 || X>10||Y<1 || Y>10)) {


                    if (st!=2) {                                                    //both player and AI calculates and picks rotation
                        if (p*2+X<=11) {
                            printf("Can go right\n");
                            a=a+1;
                        }
                        if (p * 2 + Y <= 11) {
                            printf("Can go up\n");
                            a=a+2;
                        }

                        if (a == 3) {
                            if (st==0) {
                                do {
                                    printf("What direction do you want. H or V\n");

                                    scanf("%c", &tm);
                                    getchar();

                                    if (tm == 'H' || tm == 'h') {
                                        a = 1;
                                    } else if (tm == 'V' || tm == 'v') {
                                        a = 2;
                                    } else {
                                        printf("Wrong direction symbol. try again\n");
                                    }
                                } while (a == 3);
                            } else if (st==1) {
                                a=(rand() % (2))+ 1;
                            }

                        }
                        tm='1';



                        if (st==1 && X==P[p-1][0] && Y==P[p-1][1] && a==P[p-1][2]) {
                            tm='0';
                            a=0;
                            //elenxei ama ta ploia tou antipalou einai sthn idia thesh me ayta toy pexth
                        }



                        if (a==2) {                                           //collision checks
                            for (i=0;i<p*2;i=i+1) {
                                if (A[Y+i-1+(st*10)][X-1]!=0 && tm=='1') {
                                    tm='0';
                                    a=0;
                                    if (st==0) {
                                        printf("Position taken\nPlace a ship again\n");
                                    }
                                }
                            }
                            if (tm=='1') {
                                for (i=0;i<p*2;i=i+1) {
                                    A[Y+i-1+(st*10)][X-1]=p;
                                }
                            }
                        } else if (a==1) {
                            for (i=0;i<p*2;i=i+1) {
                                if (A[Y-1+(st*10)][X+i-1]!=0 && tm=='1'){
                                    tm='0';
                                    a=0;
                                    if (st==0) {
                                        printf("Position taken\nPlace a ship again\n");
                                    }
                                }
                            }
                            if (tm=='1') {
                                for (i=0;i<p*2;i=i+1) {
                                    A[Y-1+(st*10)][X+i-1]=p;
                                }
                            }
                        }
                    } else if (A[Y-1+(-pl+1)*10][X-1]>=3) {
                        printf("The location has already be marked\n\n");
                        a=0;
                    } else {
                        a=3;
                    }

                    if (a==0 && st!=2) {
                        printf("out of bound\nNot enough space from either side\n\n");
                    }
                } else {
                    printf("out of bound\n\n");
                }

            } while (X<1 || X>10||Y<1 || Y>10 || a==0);




            if (st==2) {                                                        //Storing ship ids on the A board
                A[Y-1+(-pl+1)*10][X-1]=A[Y-1+(-pl+1)*10][X-1]+3;
                if (A[Y-1+(-pl+1)*10][X-1]<4) {
                    if (pl==1) {
                        pl=0;
                    } else if (pl==0) {
                        pl=1;
                    }
                } else if (A[Y-1+(-pl+1)*10][X-1]==4) {
                    P[2-(pl*2)][3] = P[2-(pl*2)][3]-1;
                    if (P[2-(pl*2)][3]==0) {
                        if (pl==1) {
                            printf("||player's ship 1 has been eliminated||\n");
                        } else {
                            printf("||enemy's ship 1 has been eliminated||\n");
                        }

                    }
                } else if (A[Y-1+(-pl+1)*10][X-1]==5) {
                    P[3-(pl*2)][3] = P[3-(pl*2)][3]-1;
                    if (P[3-(pl*2)][3]==0) {
                        if (pl==1) {
                            printf("||player's ship 2 has been eliminated||\n");
                        } else {
                            printf("||enemy's ship 2 has been eliminated||\n");
                        }
                    }
                }

            } else if (st==1 || st==0) {                                        // storing ship id and other stuff
                P[p-1+(st*2)][0]=X;
                P[p-1+(st*2)][1]=Y;
                P[p-1+(st*2)][2]=a;
                P[p-1+(st*2)][3]=p*2;

                if (st==1) {
                    if (p==2) {
                        p=1;
                        n=1;
                    } else if (p==1) {
                        p=0;
                        n=0;
                        st=2;
                        pl=0;
                        printf("AI has placed Its ships\n");
                    }
                }
            }



            for (i=0; i<10;i=i+1) {                             //start rendering
                                                                // To rendering sigoura mporei na faei optimisations
                if (st==1 || st==2) {
                    for (j=0;j<10;j=j+1) {
                        if (A[19-i][j]==0 ) {
                            printf(".");
                        } else if (A[19-i][j]==1) {
                            if (s==-1) {
                                printf(".");
                            } else {
                                printf("*");
                            }
                        }
                        if (A[19-i][j]==2) {
                            if (s==-1) {
                                printf(".");
                            } else {
                                printf("o");
                            }
                        }else if (A[19-i][j]==3) {
                            printf("X");
                        }else if (A[19-i][j]==4) {
                            printf("@");
                        }else if (A[19-i][j]==5) {
                            printf("@");
                        }
                    }
                    printf(" || ");
                }
                for (j=0;j<10;j=j+1) {
                    if (A[9-i][j]==0) {
                        printf(".");
                    } else if (A[9-i][j]==1) {
                        printf("*");
                    } else if (A[9-i][j]==2) {
                        printf("o");
                    } else if (A[9-i][j]==3) {
                        printf("X");
                    } else if (A[9-i][j]==4) {
                        printf("@");
                    } else if (A[9-i][j]==5) {
                        printf("@");
                    }
                }
                printf(" |\n");
            }
            printf(" \n");

            if (st==0 && n==0) {                                            //task 2 accepting positions
                printf("Are those the final positions?\nType Y if you want to accept those locations or N if you want to change\n");

                scanf("%c",&tm);
                getchar();

                if (tm=='N' || tm=='n') {
                    n=3;
                    for (i=0;i<10;i=i+1) {
                        for (j=0;j<10;j=j+1) {
                            A[i][j]=0;
                            printf(".");
                        }
                        printf("|\n");
                    }

                } else if (tm=='Y' || tm=='y' || tm=='1') {
                    st=1;
                    p=2;
                    n=3;
                    printf("\nPositions have been accepeted\nGame Starting\n\n");
                }
            }

        } while ((X !=11 && Y !=11) && (((P[2][3]!=0 || P[3][3]!=0) && (P[0][3]!=0 || P[1][3]!=0)) && st!=3));


        printf("Game Over\n");                                              //Game ending
        if (P[2][3]==0 && P[3][3]==0) {
            printf("Player won\n");
        } else {
            printf("Computer won\n");
        }
        printf("\nDo you want to play again?\n Type y for Yes or n for No\n");

        scanf("%c",&g);
        getchar();
    } while (g!='n' && g!='N');                                             //again?



    return 0;

    //Time spent on Project: 16h 54m 44s
