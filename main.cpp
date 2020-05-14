//  prog5_1024.cpp
//     Text version of the game 1024, a variant of 2048 available online at:
//        http://gabrielecirulli.github.io/2048/
//     Object of game is to combine number tiles with the same value, accumulating
//     points as the game progresses, to try and create the tile with the value 1024.
//     Each move consists of sliding pieces to the left, up, right or down.
//  Running program looks like:

/*
     Patel, Jaykumar
     UIC CS 141, Spring 2019
     Welcome to 1024.
     This program is based off of Gabriele Cirulli's game online at
     bit.ly/great2048
*/

#include <iostream>     // For cin, cout, endl
#include <iomanip>      // used for setting output field size using setw
#include <cstdlib>      // For rand()
#include <cmath>        // For mathematical functions such as abs and pow.
using namespace std;    // So we don't need std:: in front of every cin, cout, and endl

const int MaxBoardSize = 12;          // Max number of squares per side
const int MaxTileStartValue = 1024;   // Max tile value to start out on a 4x4 board


//--------------------------------------------------------------------
// Display Instructions
void displayInstructions()
{
    cout << "Welcome to 1024. \n"
         << "  \n"
         << "For each move enter a direction as a letter key, as follows: \n"
		 << "    W    \n"
		 << "  A S D  \n"
		 << "where A=left,W=up, D=right and S=down. \n"
		 << "  \n"
		 << "After a move, when two identical valued tiles come together they    \n"
		 << "join to become a new single tile with the value of the sum of the   \n"
		 << "two originals. This value gets added to the score.  On each move    \n"
		 << "one new randomly chosen value of 2 or 4 is placed in a random open  \n"
		 << "square.  User input of x exits the game.                            \n"
		 << "  \n";
}//end displayInstructions()


//--------------------------------------------------------------------
// Place a randomly selected 2 or 4 into a random open square on
// the board.
void placeRandomPiece( int board[], int squaresPerSide)
{
    // Randomly choose a piece to be placed (2 or 4)
    int pieceToPlace = 2;
    if( rand()%2 == 1) {
        pieceToPlace = 4;
    }

    // Find an unoccupied square that currently has a 0
    int index;
    do {
        index = rand() % (squaresPerSide * squaresPerSide);
    }while( board[ index] != 0);

    // board at position index is blank, so place piece there
    board[ index] = pieceToPlace;

}//end placeRandomPiece()



void displayAsciiBoard( int board[], int squaresPerSide, int score){

//     board[ squaresPerSide * squaresPerSide];

    cout << "Score: " << score << endl;

    for(int i = 0; i < (squaresPerSide * squaresPerSide); i++){

        if (i % squaresPerSide == 0){

            cout << endl << endl;
            cout << "   ";
        }

        if( board[ i] == 0 ){
            cout << setw(6) << ".";

        }
        else{
             cout << setw(6) << board[ i];
        }

    }// ends for loop.

    cout << endl;

} // ends displayAsciiBoard function.



void moveLeft(int board[], int squaresPerSide){
    int temp;

    for(int i =0; i < squaresPerSide*squaresPerSide; i++){

        if( (i % squaresPerSide != 0) && (board[i] != 0) ){
            temp = i;

           while( ( board[temp -1] == 0) && (temp % squaresPerSide != 0) ){
               board[temp -1 ] = board[temp];
               board[temp] = 0;
               temp--;

           }// ends while loop.
        }// ends if statement.
    } // ends for loop.

} // ends moveLeft.



void moveRight( int board[], int squaresPerSide){
    int temp;

    for(int i =( squaresPerSide * squaresPerSide -1); i >= 0; i--){

        if( ((i +1)% squaresPerSide != 0) && (board[i] != 0)){
            temp = i;

            while( ( board[temp +1] == 0) && ( (temp+1) % squaresPerSide != 0) ){
               board[temp +1 ] = board[temp];
               board[temp] = 0;

               temp++;

            } // ends while loop.
        } // ends if statement.
    } // ends for loop.

} //ends moveRight



void moveUp( int board[], int squaresPerSide){
    int temp;

    for( int i = squaresPerSide; i < ( squaresPerSide * squaresPerSide); i++){

		if (board[i] != 0){ //moves applies to those pieces that are not currently zero.
            temp = i;

            while( board[ temp- squaresPerSide] == 0  &&  temp >= squaresPerSide ){

                board[ temp - squaresPerSide] = board[ temp]; // moves the piece that has the number upwards.
                board[ temp] = 0;     //changes the value of the piece that had a number to 0 .
                temp -= squaresPerSide;

            } //ends while loop.
        } // ends if statement
    }// ends for loop.

}// ends the moveUp function.

void moveDown( int board[], int squaresPerSide){
    int temp;

    for(int i = ( squaresPerSide*squaresPerSide - squaresPerSide -1); i >= 0 ; i-- ){

        if( board[i] != 0) {
            temp = i;

             while( ( board[ temp+squaresPerSide] == 0)  && temp < ( squaresPerSide*squaresPerSide - squaresPerSide ))
             {
                  board[temp + squaresPerSide] = board[ temp];
                  board[ temp] =0;
                  temp += squaresPerSide;

              } // ends while.
        } // ends if statement.
     } // ends for loop.

} // ends the moveDown function.




// Function for copying the elements by iterating from the board array to the previousBoard array.
void copyBoard(int board[], int previousBoard[],int squaresPerSide)
{
    previousBoard[ squaresPerSide*squaresPerSide]; //declaring the size.

    for(int i=0; i< squaresPerSide*squaresPerSide; i++){ // loop copying the contents one by one.
        previousBoard[ i]=board[ i];
    }

}// ends copyBoard.



void setBoardFunction(int board[], int previousBoard[], int &squaresPerSide, int &maxTileValue){

    for(int row = 0; row <squaresPerSide; row++){
        for(int col =0; col<squaresPerSide; col++){
             board[ row * squaresPerSide + col] = 0;
        }
    }

    maxTileValue = MaxTileStartValue;        // Reset the value, in case we resize the board to be smaller.

    for( int i=4; i<squaresPerSide; i++) {
        maxTileValue = maxTileValue * 2;   // double for each additional board dimension > 4
    }

    cout << "Game ends when you reach " << maxTileValue << "." << endl;

    placeRandomPiece( board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);

} // ends setBoardFunction.



//---------------------------------------------------------------------------------------
int main()
{
    int score = 0;
    int squaresPerSide = 4;        // User will enter this value.  Set default to 4
    int board[ MaxBoardSize * MaxBoardSize];          // space for largest possible board
    int previousBoard[ MaxBoardSize * MaxBoardSize];  // space for copy of board, used to see
                                                      //    if a move changed the board.
    int maxTileValue = MaxTileStartValue;  // 1024 for 4x4 board, 2048 for 5x5, 4096 for 6x6, etc.
    char userInput = ' ';                  // handles user input
    int move = 1;                          // user move counter
    int maxSize;

    displayInstructions();

    int givenSize = 4; // minimum and already given size.
    int otherSize; // userInput variable for user chosen size of board.
    int variable;
    int var;
    int num;
    int finalScore; // varible of final score.
    int fullVar = 0; // variable used in checking if the game should exit.


    cout << "Game ends when you reach "<< (squaresPerSide * 256)<< "."<<endl << endl;


/*
     //  board[ 12 X 12 ]
     int board[ MaxBoardSize * MaxBoardSize] = {
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0,0,0,0,0,0,0
    };

*/

    // giving size to the board array and then adding the elements(all '0' in this case) to it using a for loop.
    board[ squaresPerSide * squaresPerSide];
    for(int i= 0; i < squaresPerSide * squaresPerSide; i++){
        board[i]=0;
    }

    placeRandomPiece( board, squaresPerSide);
    placeRandomPiece( board, squaresPerSide);


    // Infinite loop to run program until user selects exit, board is fullVar, or max tile value is reached
    while( true)
    {
        // Display the text-based board
        displayAsciiBoard( board, squaresPerSide, score);

        // Make a copy of the board.  After we then attempt a move, the copy will be used to
        copyBoard( board, previousBoard, squaresPerSide);

        cout << move << ". Your move: " << endl;

        // if maximum score has reached, then the game ends.
        if( fullVar == squaresPerSide * squaresPerSide){

            cout << endl << "No more available moves.  Game is over."<< endl;
            displayAsciiBoard( board, squaresPerSide, score);

            break;
        }


        // Prompt for and handle user input
        cin >> userInput;
        userInput = tolower(userInput); //to handle uppercase and lowercase input equally.

        switch (userInput) {
            case 'x':
                    cout << "Thanks for playing. Exiting program... \n\n";
                    exit( 0);
                    break;

            case 'a':
                    moveLeft(board, squaresPerSide);
                    for (int i =0; i < squaresPerSide*squaresPerSide; i++){
                        if(board[i] != 0){
                            if( (i+1) % squaresPerSide != 0 && board[ i] == board[ i+1]){
                                board[i] += board[ i+1];
                                board[ i+1] = 0;
                                score += board[i];

                            } // ends if statement.
                        } // ends if.
                     } //ends for loop.

                    moveLeft(board, squaresPerSide);
                    break;

            case 'd':
                    moveRight(board, squaresPerSide);
                    for(int i =(squaresPerSide*squaresPerSide -1); i >= 0; i--){
                        if( board[i] != 0) {
                            if( (i % squaresPerSide != 0) && (board[ i] == board[ i-1]) ){
                                board[ i] += board[ i-1];
                                board[i -1] = 0;
                                score += board[i];

                            }// ends the if statement
                        } // ends if.
                    } // ends for loop.

                    moveRight(board, squaresPerSide);
                    break;

            case 'w':
                    moveUp(board, squaresPerSide);
                    for( int i= 0; i < ( squaresPerSide * squaresPerSide); i++){
                        if( board[i] != 0){
                            if(board[i] == board[i + squaresPerSide] ){
                                board[i] += board[i + squaresPerSide];
                                board[i + squaresPerSide] = 0;
                                score += board[i];

                            } // ends if statement.
                        } // ends if.
                    } // ends for loop.

                    moveUp(board, squaresPerSide);
                    break;

            case 's':
                    moveDown(board, squaresPerSide);
                    for(int i = ( squaresPerSide * squaresPerSide -1); i >=0 ; i-- ){
                        if(board[ i] != 0){
                            if(board[i] == board[i - squaresPerSide] ){
                                board[ i] += board[ i- squaresPerSide];
                                board[ i- squaresPerSide] = 0;
                                score += board[i];

                            } // ends the first if statement.
                        } // ends the second if statement.
                    }// ends the for loop.

                    moveDown(board, squaresPerSide);
                    break;

            case 'p':
            		cin >> variable >> num;
                    if(variable < squaresPerSide*squaresPerSide){
                        board[variable] = num;
                        var = 1;
                    }
//                     continue;
                    break;

            case 'r':
                cout << endl <<"Resetting board"<< endl << "Enter the size board you want, between 4 and 12: ";
                cin >> squaresPerSide; // custom size chosen by the user.

                //setting the board with the custom size (according to user input).
                setBoardFunction(board, previousBoard, squaresPerSide, maxTileValue);

                var = 1;
                score = 0;
                move = 1;
                break;

            default:
                    cout << "Invalid input, please retry.";
                    continue;
                    break;

            } // ends switch-case.



        int x =0;
        for(int i = 0;i < squaresPerSide * squaresPerSide ;i++){

            if( board[ i] == previousBoard[ i]){
                x = x + 1;
            }
        } // ends for loop.

        if( x != ( squaresPerSide * squaresPerSide) && var==0){
            placeRandomPiece( board, squaresPerSide);
            move++;
        }

        var =0;
        fullVar = 0;

        if( finalScore == 1){
            cout << endl << "Congratulations!  You made it to 1024 !!!" << endl;
            displayAsciiBoard( board, squaresPerSide, score);
            break;
        }

         for( int i =0; i < ( squaresPerSide * squaresPerSide) ; i++){
            if( board[ i] != 0){
              fullVar += 1;
            }

            if(board[ i] >= pow(2,(10 + abs (givenSize - squaresPerSide))) ) {
                finalScore = 1;
            }
        } // ends for loop.

    }//ends while( true)

    return 0;
}//end main()
