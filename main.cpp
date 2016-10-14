/** Preprocessors and Global Variables*/

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include <iostream>
#include "tidier.h"
#include <cstddef>
#include<time.h>
#include<limits.h>
int xmax=INT_MIN,ymax=INT_MIN,xmin=INT_MAX,ymin=INT_MAX; 
#define nd struct node
using namespace std;
FILE *fp = fopen("pixels.txt","w");
#include "primitives.h"
#include "trees.h"
#include "input_tree.h"
#include "plotter.h"
#define new (nd*)malloc(sizeof(nd)




/** Subroutine to traverse the resultant tree.
Draws all the nodes and respective edges*/
void draw(struct node *node){
 if(node!=NULL){
   if(node->x > xmax) xmax = node->x;
   if(node->x < xmin) xmin = node->x;
   if(node->y > ymax) ymax = node->y;
   if(node->y < ymin) ymin = node->y;
   if(node->Llink!=NULL){
     primitives::drawLine(point(node->x,node->y),point(node->Llink->x,node->Llink->y));
   }
   if(node->Rlink!=NULL){
     primitives::drawLine(point(node->x,node->y),point(node->Rlink->x,node->Rlink->y));
   }
   draw(node->Llink);
   draw(node->Rlink);
   primitives::drawCircle(point(node->x,node->y),15);
 }
}

/** Main Function To Run The Code*/
int main(int argc,char** argv){
    time_t t;
     	srand((unsigned) time(&t));

    struct node *root = (struct node *)malloc(sizeof(struct node));
    root =NULL;
    printf("ENTER VALUES FOR N\n");
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        root = RandomTree::insert(root,rand()%10000);
    }
    printf("Enter Your Choice\n1. Tidy\n2. Tidier\n");
    int choice;
    scanf("%d",&choice);
    if(choice==1){
	Tidy::SetHeight(root,0);
	Tidy::SetParent(root);
	Tidy::tidyTree(root);
	Tidy::SetXY(root);
    }
    else if(choice==2){
	struct extreme LEFTMOST,RIGHTMOST;
	Tidier::setup(root,0,LEFTMOST,RIGHTMOST);
	Tidier::petrify(root,0);
    }
    else printf("\nWrong Choice");
    draw(root);
    fclose(fp);
    fp = fopen("pixels.txt","r");
    glutInit(&argc, argv);
    Plot::init();
    glutDisplayFunc(Plot::plotpixel);
    glutMainLoop();
    return 0;
}
