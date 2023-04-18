#include <stdio.h>
#define HEIGHT 5
#define WIDTH 5
typedef struct{
    int board[WIDTH+2][HEIGHT+2];
    int turn;
} PHASE;

typedef struct{
    int x;
    int y;
} MOVE;

void init_board(PHASE *p){
    int i, j;
    int array[5][5]={
        {-1, -1, -1, -1, -1}, 
        {-1, 0, 0, 0, -1},
        {-1, 0, 0, 0, -1},
        {-1, 0, 0, 0, -1}, 
        {-1, -1, -1, -1, -1} 
    };
    for(i=0;i<=HEIGHT+1;i++){
        for(j=0;j<=WIDTH+1;j++){
            p->board[i][j]=array[i][j];
        }
    }
    p->turn=1;
}

void print_board(PHASE p){
    int i, j;
    for(i=0;i<=HEIGHT+1;i++){
        for(j=0;j<=WIDTH+1;j++){
            switch(p.board[i][j]){
                case -1:
                printf(" □ ");
                break;
                case 0:
                printf("   ");
                break;
                case 1:
                printf(" ● ");
                break;
                case 2:
                printf(" ○ ");
                break;
            }
        }
        printf("\n");
    }
    printf("\n");
}

void change_phase(PHASE *p, MOVE m){
    if(p->turn==1){
        p->board[m.x][m.y]=1;
        p->turn=2;
        return ;
    }
    if(p->turn==2){
        p->board[m.x][m.y]=2;
        p->turn=1;
        return ;
    }
}

int check_end(PHASE p){
    int i, j;
    for(i=0;i<=HEIGHT+1;i++){
                for(j=0;j<=WIDTH+1;j++){
                    if(p.board[i][j]==1){
                        if(p.board[i][j+1]==1 && p.board[i][j+2]==1)
                        return 1;
                        if(p.board[i+1][j]==1 && p.board[i+2][j]==1)
                        return 1;
                        if(p.board[i+1][j+1]==1 && p.board[i+2][j+2]==1)
                        return 1;
                        if(p.board[i-1][j-1]==1 && p.board[i-2][j-2]==1)
                        return 1;
                    }
                }
    }
    for(i=0;i<=HEIGHT+1;i++){
                for(j=0;j<=WIDTH+1;j++){
                    if(p.board[i][j]==2){
                        if(p.board[i][j+1]==2 && p.board[i][j+2]==2)
                        return 2;
                        if(p.board[i+1][j]==2 && p.board[i+2][j]==2)
                        return 2;
                        if(p.board[i+1][j+1]==2 && p.board[i+2][j+2]==2)
                        return 2;
                        if(p.board[i-1][j-1]==2 && p.board[i-2][j-2]==2)
                        return 2;
                    }
                }
    }  
    
    return 0;
}



void find_move(PHASE p, MOVE moves[HEIGHT*WIDTH+1]){
    int i, j, count=0;
    for(i=0;i<=HEIGHT+1;i++){
        for(j=0;j<=WIDTH+1;j++){
            if(p.board[i][j]==0){
                moves[count].x=i;
                moves[count].y=j;
                count++;
            }
        }
    }
    moves[count].x=-1;
    moves[count].y=-1;
}


int check_win(PHASE p, MOVE m){
    PHASE c;
    c.turn=p.turn;
    for(int i=0;i<=HEIGHT+1;i++){
        for(int j=0;j<=WIDTH+1;j++){
            c.board[i][j]=p.board[i][j];
        }
    }
    change_phase(&c, m);//p0
    if(check_end(c)==1){
        return 1;
    }
    if(check_end(c)==2){
        return 2;
    }//p0で終了するかどうかチェック
    
    
    PHASE n;
    n.turn=c.turn;
    for(int i=0;i<=HEIGHT+1;i++){
        for(int j=0;j<=WIDTH+1;j++){
            n.board[i][j]=c.board[i][j];
        }
    }
    MOVE moves[HEIGHT*WIDTH+1];
    find_move(n, moves);
    int count=0;
    int i;
    if(n.turn==1){
        for(i=0;moves[i].x!=-1;i++){
            n.turn=c.turn;
    for(int i=0;i<=HEIGHT+1;i++){
        for(int j=0;j<=WIDTH+1;j++){
            n.board[i][j]=c.board[i][j];
        }
    }
        
            if(check_win(n, moves[i])==1){
                return 1;
            } else if(check_win(n, moves[i])==2){
                count++;
            }else{
            }
        }
        if(count==i){
            return 2;
        }
        return 0; 
    } 
    
    if(n.turn==2){
        for(i=0;moves[i].x!=-1;i++){
            n.turn=c.turn;
    for(int i=0;i<=HEIGHT+1;i++){
        for(int j=0;j<=WIDTH+1;j++){
            n.board[i][j]=c.board[i][j];
        }
    }
            if(check_win(n, moves[i])==2){
                return 2;
            } else if(check_win(n, moves[i])==1){
                count++;
            }else{
                
            }
        }
        if(count==i){
            return 1;
        }
    }
    return 0;
}


int main(void){
    PHASE p;
    MOVE m;
    int i, j;
    MOVE moves[HEIGHT*WIDTH+1];
    init_board(&p);
    print_board(p);
    printf("先手=1か後手=2を選択して入力してください\n");
    int ban;
    scanf("%d", &ban);
    if(ban==1){
        scanf("%d", &m.x);
        scanf("%d", &m.y);
        change_phase(&p, m);
        print_board(p);
        for(i=1;i<=4;i++){
            find_move(p, moves);
            for(j=0;moves[j].x!=-1;j++){
                if(check_win(p, moves[j])==2){
                    change_phase(&p, moves[j]);
                    print_board(p);
                    break;
                    }
            }
            if(p.turn==2){
                change_phase(&p, moves[0]);
                print_board(p);
            }
            if(check_end(p)==1){
                printf("先手●の勝ちです\n");
                break;
            }
            if(check_end(p)==2){
                printf("後手○の勝ちです\n");
                break;
            }
            scanf("%d", &m.x);
            scanf("%d", &m.y);
            change_phase(&p, m);
            print_board(p);
            if(check_end(p)==1){
                printf("先手●の勝ちです\n");
                break;
            }
            if(check_end(p)==2){
                printf("後手○の勝ちです\n");
                break;
            }
            if(check_end(p)==0 && i==4){
                printf("引き分け\n");
            }
        }
    } 
    
    
    
    
    
    
    
    if(ban==2){
        m.x=2;
        m.y=2;
        change_phase(&p, m);
        print_board(p);
        for(i=1;i<=3;i++){
            scanf("%d", &m.x);
            scanf("%d", &m.y);
            change_phase(&p, m);
            print_board(p);
            if(check_end(p)==1){
                printf("先手●の勝ちです\n");
                break;
            }
            if(check_end(p)==2){
                printf("後手○の勝ちです\n");
                break;
            }
            
            find_move(p, moves);
            /*for(int k=0;k<=9;k++){
            printf("%d ", moves[k].x);
            printf("%d  ", moves[k].y);
        }*/
        printf("\n");
            for(j=0;moves[j].x!=-1;j++){
                if(check_win(p, moves[j])==1){
                    change_phase(&p, moves[j]);
                    print_board(p);
                    break;
                    }
            }
            if(p.turn==1){
                change_phase(&p, moves[0]);
                print_board(p);
            }
            if(check_end(p)==1){
                printf("先手●の勝ちです\n");
                break;
            }
            if(check_end(p)==2){
                printf("後手○の勝ちです\n");
                break;
            }
        }
        if(check_end(p)==0 && i==5){
                printf("引き分け\n");
            }
    }     
}
