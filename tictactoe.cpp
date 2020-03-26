#include <iostream>
#include <cstdlib>
using namespace std;

void board();
void clearScreen();
int checkWin();
void twoPlayer();
int oneMoveToWin(char ch);
void playerVsPc();

char cell[10] = { '0','1','2','3','4','5','6','7','8','9' };
char sel[3] = { '0', 'X', 'O' };

void clearScreen(){
    if(system("cls")) system("clear");
    else system("cls");
}

void board(){
    clearScreen();
    cout << "\n\n";
    cout << "         |         |" << endl;
    cout << "    " << cell[1] << "    |    " << cell[2] <<  "    |    " << cell[3] << endl;
    cout << "_________|_________|_________" << endl;
    cout << "         |         |" << endl;
    cout << "    " << cell[4] << "    |    " << cell[5] <<  "    |    " << cell[6] << endl;
    cout << "_________|_________|_________" << endl;
    cout << "         |         |" << endl;
    cout << "    " << cell[7] << "    |    " << cell[8] <<  "    |    " << cell[9] << endl;
    cout << "         |         |" << endl;
}
/*
 * -1 = we found a winner
 *  1 = game in progress
 *  0 = game is draw
 */
int checkWin(){
    bool progress = false;
    // row 
    for(int i = 1; i <= 9; i += 3){
        if(cell[i] == cell[i+1] && cell[i] == cell[i+2])
            return -1;
    }
    //column
    for(int i = 1; i <= 3; i++){
        if(cell[i] == cell[i+3] && cell[i] == cell[i+6])
            return -1;
    }
    if((cell[1] == cell[5] && cell[1] == cell[9]) || (cell[3] == cell[5] && cell[3] == cell[7]))
        return -1;
    else{
        for(int i = 1; i <= 9; i++)
            if(cell[i] == i + '0'){
                progress = true;
                break;
            }
    }
    return progress;
}
void twoPlayer(){
    int player = 2,choose;
    do{
        board();
        player = player == 1 ? 2 : 1;
        cout << "\nplayer " << player << " \'" << sel[player] << "\' : " ;
        cin >> choose;
        
        if(choose > 9 ||  choose < 1 || cell[choose] != choose + '0'){
            cout << "Invalid move " << endl;
            player = player == 2 ? 1 : 2;
            cin.ignore();
            cin.get();
            continue;
        }
        else{
            cell[choose] = sel[player];
        }
    }while(checkWin() == 1);

    clearScreen();
    board();
    int winner = checkWin();
    if(winner) cout << "\nplayer " << player << " is the Winner !" << endl;
    else cout << "\nDraw !!! " << endl;
}
void playerVsPc(){
    clearScreen();
    int player = 2, pc = 1, turn = 1;
    do{
        board();
        cout << "\n     Pc : You can't beat me :v" << endl;
        turn = turn == pc ? player : pc;
        if(turn == player){
            while(true){
                cout << "\nplayer " << player << " \'" << sel[player] << "\' : "; 
                int choose; cin >> choose;
                if(choose > 9 ||  choose < 1 || cell[choose] != choose + '0'){
                    cout << "Invalid move " << endl;
                    cin.ignore();
                    cin.get();
                    continue;
                }
                cell[choose] = sel[player];
                break;
            }
        }
        else{
            if(oneMoveToWin(sel[pc])) {
                int c = oneMoveToWin(sel[pc]);
                cell[c] = sel[pc];
            }
            else if(oneMoveToWin(sel[player])){
                int c = oneMoveToWin(sel[player]);
                cell[c] = sel[pc];
            }
            else{
                // if center in not occupied
                if(cell[5] == 5 + '0') {
                    cell[5] = sel[pc];
                }
                else{
                    for(int i = 1; i <= 9; i++)
                        if(cell[i] == i+'0'){
                            cell[i] = sel[pc];
                            break;
                        }
                }
            }
        }
    }while(checkWin() == 1);

    clearScreen();
    board();
    if(checkWin() == -1) {
        if(turn == player) cout << "\nPlayer is the winner !" << endl;
        else cout << "\nPc is the winner ! told you can't beat me :P " << endl;
    }
    else cout << "\nDraw !" << endl;
}
int oneMoveToWin(char ch){
    // for row 
    for(int i = 1; i <= 7; i+=3){
        if(cell[i] == cell[i+1] && cell[i+2] == i+2+'0' && cell[i] == ch)
            return i+2;
        if(cell[i] == cell[i+2] && cell[i+1] == i+1+'0' && cell[i] == ch)
            return i+1;
        if(cell[i+2] == cell[i+1] && cell[i] == i+'0' && cell[i+1] == ch)
            return i;
    }
    // for column
    for(int i = 1; i <= 3; i++){
        if(cell[i] == cell[i+3] && cell[i+6] == i+6+'0' && cell[i] == ch)
            return i+6;
        if(cell[i] == cell[i+6] && cell[i+3] == i+3+'0' && cell[i] == ch)
            return i+3;
        if(cell[i+3] == cell[i+6] && cell[i] == i+'0' && cell[i+3] == ch)
            return i;
    }
    // for diagonal
    if(cell[1] == cell[5] && cell[9] == 9+'0' && cell[1] == ch)
        return 9;
    if(cell[1] == cell[9] && cell[5] == 5+'0' && cell[1] == ch)
        return 5;
    if(cell[5] == cell[9] && cell[1] == 1+'0' && cell[5] == ch)
        return 1;
    // another corner
    if(cell[3] == cell[5] && cell[7] == 7+'0' && cell[3] == ch)
        return 7;
    if(cell[3] == cell[7] && cell[5] == 5+'0' && cell[3] == ch)
        return 5;
    if(cell[5] == cell[7] && cell[3] == 3+'0' && cell[5] == ch)
        return 3;
    return 0;
}
int main(){
    int mode;
    cout << "Select Mode : \n1. 2 Player\n2. Player vs Pc" << endl;
    cin >> mode;
    if(mode == 1) twoPlayer();
    else if(mode == 2) playerVsPc();
    else{
        cout << "Invalid mode !" << endl;
        cin.ignore();
        cin.get();
    }
}
