// Tower of Hanoi Animation

#include <stdio.h>
#include <graphics.h>
#include <string.h>
#define MAX 10				// maximum number of disks supported (10)
#define MID 190				// x-coordinate for pole A (leftmost pole)
#define LEN 380				// length of the base for all poles
#define Y0 600				// lower y-coordinate
#define Y1 180				// upper y-coordinate
#define HEIGHT 40			// height of a disk

int COLORS[10] = {2, 5, 7, 8, 9, 10, 11, 12, 13, 14};		// supported color for disks
int pass = 0;							// number of passes

// pole structure
struct pole {
	char label;
	int stack[MAX];			// disks on the pole
	int top;			// (number of disks on the pole) - 1
	int x0;				// (left x-coordinate of the pole base)
} A, B, C;

// move a disk to a pole
void push(struct pole *x, int data) {
    x->top++;
    x->stack[x->top] = data;
}

// remove a disk from a pole
int pop(struct pole *x) {
    int data;
    data = x->stack[x->top];
    x->top--;
    return data;
}

// initialize the poles and disks for drawing
void initpoles(int n) {
	int i;
    A.label = 'A';
    B.label = 'B';
    C.label = 'C';
    A.x0 = 100;
    B.x0 = 550;
    C.x0 = 1000;
    A.top = B.top = C.top = -1;
    for (i = n; i >= 1; i--) {
        push(&A, i);
    }
}

// move disk from one pole to other
void movedisk(struct pole *x1, struct pole *x2) {
    int data;
    data = pop(x1);
    push(x2, data);
}

// draw the disks present on a pole
void drawdisks(struct pole x) {
	int i, m;
	int dky1 = Y0; 
	int dky2 = Y0-HEIGHT;
	int dkx1;
	int dkx2;
	setcolor(RED);
	for (i=0; i<=x.top; i++) {
		setfillstyle(SOLID_FILL, COLORS[x.stack[i]-1]);
		m = 45+15*(x.stack[i]-1);
		dkx1 = x.x0+MID-m;
		dkx2 = x.x0+MID+m;
		rectangle(dkx1, dky1, dkx2, dky2);
		floodfill(dkx1+1, dky1-1, RED);
		dky1 -= HEIGHT;
		dky2 -= HEIGHT;
	}
}

// draw a pole along with the disks on it
void drawpole(struct pole x) {
	setcolor(WHITE);
	line(x.x0, Y0, x.x0+LEN, Y0);
	line(x.x0+MID, Y0, x.x0+MID, Y1);
	settextstyle(8, 0, 5);
	char pn[10] = "POLE X";
	pn[5] = x.label;
	outtextxy(x.x0+120, Y0+10, pn);
	drawdisks(x); 							
}

// show the move number, the source pole of top disk and its destination pole as text on screen
void showmove(struct pole x1, struct pole x2) {
    setcolor(WHITE);
    settextstyle(10, 0, 6);
    char move1[30] = "MOVE ";
    char move2[5];
    sprintf(move2, "%d", ++pass);
    char move3[20] = ": POLE X --> POLE X";
    move3[7] = x1.label;
    move3[18] = x2.label;
    strcat(move1, move2);
    strcat(move1, move3);
    outtextxy(360, Y1-170, (char*)"TOWER OF HANOI ANIMATION");
    outtextxy(350, Y1-100, move1);
}

// draw all the poles and the disks
void showpoles() {
	drawpole(A);
	drawpole(B);
	drawpole(C);
}

// main tower of hanoi function
void tohDraw(int n, struct pole *a, struct pole *b, struct pole *c) {
    if (n == 1) {
    	movedisk(a, c);
    	cleardevice();
    	showmove(*a, *c);
    	printf("\nMOVE %d: POLE %c --> POLE %c", pass, a->label, c->label);
    	showpoles();
    	delay(1500);
    } 
	else {
        tohDraw(n - 1, a, c, b);
        tohDraw(1, a, b, c);
        tohDraw(n - 1, b, a, c);
    }
}

// code to generate the animation
void animator() {
	int win, ndisks;
	char disks1[20];
	char disks2[20] = " DISKS";
	while (1) {
		printf("\nHow many disks you wish to animate for?: ");
    		scanf("%d", &ndisks);
    		if ((ndisks<=0) || (ndisks>10))
    			printf("Invalid input!...");
    		else break;
	}
    sprintf(disks1, "%d", ndisks);
    strcat(disks1, disks2);
    initpoles(ndisks);
    printf("\nSTARTING ANIMATION....\n");
    printf("\nTower of Hanoi moves for %d disks....\n", ndisks);
    win = initwindow(getmaxwidth(), getmaxheight(), (char*)"Tower of Hanoi Animation");
    showpoles();
    setcolor(WHITE);
    settextstyle(10, 0, 6);
    outtextxy(360, Y1-170, (char*)"TOWER OF HANOI ANIMATION");
    outtextxy(620, Y1-100, disks1);
    outtextxy(550, Y0+100, (char*)"INITIAL STATE");
    getch();
    tohDraw(ndisks, &A, &B, &C);
    setcolor(WHITE);
    settextstyle(10, 0, 6);
    outtextxy(560, Y0+100, (char*)"FINAL STATE");
    getch();
    closegraph(win);
    printf("\n\nANIMATED SUCCESSFULLY!");
}

// code to call the animator function in a loop
void menu() {
	int exit = 1;
	printf(">>======>> TOWER OF HANOI ANIMATOR V1.0 <<======<<\n\n");
	printf("NOTE: THIS PROGRAM CAN ANIMATE FOR UPTO 10 DISKS.\n");
	while (1) {
		animator();
		printf("\n\n>>=========================================================<<");
		printf("\n\nDo you wish to generate another animation?\n");
		printf("Enter 0 to QUIT\n");
		printf("Enter anything else to continue with another animation\n\n");
		printf("Enter your choice: ");
		scanf("%d", &exit);
		if (exit==0) {
			printf("\n\nQuitting program...");
			printf("\n**********************************************************\n\n");
			printf("Thank you for using TOWER OF HANOI ANIMATOR V1.0!\n");
			break;
		}
		printf("\n\nGenerating another Tower of Hanoi animation....");
		printf("\n**********************************************************\n\n");
		pass = 0;
	}
}

// driver code
int main(){
	menu();
	return 0;
}
