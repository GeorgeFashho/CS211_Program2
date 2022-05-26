/*  gfash2-proj2.c

	Written [5/22/2022] by [George Fashho] for CS 211, Summer 2022

	The program maintains a collection of points in 3D
    space, and certain properties of the collection as a whole. Then you will use this information to test
    whether a given separate point intersects with the collection of points or not.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define X 0
#define Y 1
#define Z 2
#define SIZE 15

int debug = 0 ; //set to 0 by default (FALSE)

typedef struct POINT_3D {
    int ID;
    double coordinates[3],luminosity;
}Point3D;   //struct containing information for every point

typedef struct POINT_SET{
    Point3D *points ;
    int numAllocated,numPoints;
    double luminosity,lower[3],upper[3];
}PointSet;  //struct with information of all points as well as information needed to allocate memory
           // and lower, upper limits of coordinates

//---------------------------------------------------------------------------
//Function used to dynamically allocate memory to array, as well as add the users input
//into the struct of points if luminosity is a non-negative number
int addPointToSet( PointSet *set, Point3D point );


//---------------------------------------------------------------------------
//Function that checks for intersection of points if ALL [X, Y, Z] coordinates
//inputted by user are within the upper and lower range of the box they are in.
int intersection( PointSet set, Point3D point );


//---------------------------------------------------------------------------
int main( int argc, char const *argv[ ] ) {

    PointSet pointSet ; //declaring new struct
    pointSet.points = (Point3D *) malloc(sizeof(Point3D)*SIZE); //allocating memory to struct array point3D


    for( int i = 0; i < argc; i++ ) { //debugging information!!

        /* access the ith ARGument Value */
        printf( "argv[ %d ] = \"%s\" ", i, argv[ i ] ); //printing arguments entered by user

        if( '-' == argv[ i ][ 0 ] ) {
            printf("debug mode on!");
            debug = 1;  //debug mode on since -d called
        }
 }

    double userInput[4]; //array to hold user inputs
    pointSet.numPoints = 0;
    int index = pointSet.numPoints; //setting first user input to 0 to count all user inputted info

    pointSet.numAllocated = SIZE; //original spaces allocated for memory
    Point3D temp; // making a temp struct type from Point3D to hold user data

    scanf("%lf %lf %lf %lf",&userInput[0],&userInput[1],&userInput[2],&userInput[3]
    );

    pointSet.lower[X] = userInput[0];
    pointSet.upper[X] = userInput[0];
    pointSet.lower[Y] = userInput[1];   //initiating lower and upper bounds!
    pointSet.upper[Y] = userInput[1];
    pointSet.lower[Z] = userInput[2];
    pointSet.upper[Z] = userInput[2];

    while(userInput[3] >=0.0){

        scanf("%lf %lf %lf %lf",&userInput[0],&userInput[1],&userInput[2],&userInput[3]
        ); //taking in user inputs

        temp.coordinates[X] = userInput[0];
        temp.coordinates[Y] = userInput[1];
        temp.coordinates[Z] = userInput[2];
        temp.luminosity = userInput[3];
        temp.ID = pointSet.numPoints;

        if(debug == 1 ){
            printf("%d\n",temp.ID);
        } //debugging info to find what user input causes an issue!!

        if(temp.luminosity >= 0.00 ) {
            addPointToSet(&pointSet, temp); //adding point to set in luminosity is a non-negative number
        }
        else{
            break;
        }

        if(userInput[0]<pointSet.lower[X]){
            pointSet.lower[X] = userInput[X];
        }else if(temp.coordinates[Y]<pointSet.lower[Y]) {
            pointSet.lower[Y] = temp.coordinates[Y];
        } else if(temp.coordinates[Z]<pointSet.lower[Z]){
            pointSet.lower[Z] = temp.coordinates[Z];
        }else if(temp.coordinates[X]>pointSet.upper[X]){    //finding the lower and upper bounds for [ X, Y , Z]
            pointSet.upper[X] = temp.coordinates[X];
        }else if(temp.coordinates[Y]>pointSet.upper[Y]){
            pointSet.upper[Y] = temp.coordinates[Y];
        }else if(temp.coordinates[Z]>pointSet.upper[Z]){
            pointSet.upper[Z] = temp.coordinates[Z];
        }

        pointSet.numPoints = pointSet.numPoints + 1  ;
}

    double totalSum = 0 ;

    for(int i = 0 ; i< pointSet.numPoints ; i++){
    totalSum += pointSet.points[i].luminosity;  //finding total sum of luminosity
}
    double avg =0 ;
    avg =totalSum/(double)pointSet.numPoints;   //calculating average luminosity

    pointSet.luminosity = avg;

    printf("Number of points in set 1: %.0f\nLower X, Y, Z Bounds (Respectively): [%.2f,  %.2f,  %.2f]\n"
           "Upper X, Y, Z Bounds (Respectively): [%.2f,  %.2f,  %.2f]\n Average Luminosity: %.2f",(double)pointSet.numPoints+1,pointSet.lower[X],
           pointSet.lower[Y],pointSet.lower[Z],pointSet.upper[X],pointSet.upper[Y],pointSet.upper[Z],avg);


    Point3D temp2; //temp Point3D struct to hold user input

    scanf("%lf %lf %lf %lf",&userInput[0],&userInput[1],&userInput[2],&userInput[3]
    );

    while(userInput[3] >=0.0){ //continue taking in user input till luminosity < 0.

        int bool = 0 ; //setting bool to 0 by default
        scanf("%lf %lf %lf %lf",&userInput[0],&userInput[1],&userInput[2],&userInput[3]
        );

        temp2.coordinates[X] = userInput[0];
        temp2.coordinates[Y] = userInput[1];
        temp2.coordinates[Z] = userInput[2];
        temp2.luminosity = userInput[3];
        temp2.ID = pointSet.numPoints;

        if(temp2.luminosity >= 0.00 ) {
             bool = intersection(pointSet,temp2); //finding if the values intersect or not
        }
        else{
            break;
        }
        //echoing information for second set of points inputted
        printf("Coordinates inputted [X, Y, Z]: %.2f, %.2f, %.2f\n",temp2.coordinates[X],temp2.coordinates[Y],temp2.coordinates[Z]);
        if(bool == 1 ){
            printf("*The coordinates inputted intersect with the set*\n");
        }
        else{
            printf("*The coordinates inputted do not intersect with the set*\n");
        }
    }
    free((Point3D*)pointSet.points); //freeing memory !!
    return 0;

}


//---------------------------------------------------------------------------
int addPointToSet(PointSet *set, Point3D point ){

   int index = set->numPoints;

   if(debug ==1 ){  //debug info to find error in user input or memory issue
       printf("\nMemory Check:");
       printf("%lf",(double)sizeof(set->points[index]));
       printf("%lf",(double)sizeof(point));
   }

   /*dynamically allocating more memory to array, when needed*/

   if(index==set->numAllocated) {
       Point3D *temp;   //temp array to save points in
       temp = set->points;

       set->points = (Point3D *) malloc((index*sizeof (Point3D))*2);

       for (int i = 0; i < index; i++) {     //copying values from array at old memory address
           set->points[i] = temp[i] ;  //and filling half of the array at the new memory address
       }

       free(temp);  //freeing space in memory
       temp = NULL;        //setting temp to NULL for safety
       set->numAllocated = (set->numAllocated) *2;
       if(debug == 1){
           printf("More Memory Added");

       }
   }

   set->points[index] = point; //adding point3D to array of points in struct

   if(debug == 1){
       printf("done\n"); // error checking
   }
}//end addPointToSet()


//---------------------------------------------------------------------------
int intersection( PointSet set, Point3D point ){

    //returning 1 if points intersect and returning 0 otherwise.
    if(point.coordinates[X]>=set.lower[X] && point.coordinates[X] <= set.upper[X]){
        if(point.coordinates[Y]>=set.lower[Y] && point.coordinates[Y] <= set.upper[Y]){
            if(point.coordinates[Z]>=set.lower[Z] && point.coordinates[Z] <= set.upper[Z]) {
                return 1;
            }else{
                return 0;
            }
        }else{
            return 0;
        }
    }else{
        return 0;
    }
    return 0;
} //end intersection()
