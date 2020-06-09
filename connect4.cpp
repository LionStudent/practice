#include <iostream>

class BoardData{
    public:
    std::string grid[8][8];
    
    BoardData(){
        for (int r=0; r<8; r++){
            for (int c=0; c<8; c++){
                grid[r][c] = "XX";
            }
        }
    }
};

class BoardCmds{
    public:
    int isExit(std::string cmd){
        int retval = 0;
        if (cmd.compare("exit") == 0){
            retval = 1;
        }
        return retval;
    }
    int isCommand(std::string cmd){
        std::string color = this->getColor(cmd);
        int column = this->getColumn(cmd);

        int retval = 0;
        if (this->isExit(cmd) || color.compare("") != 0 && (column >= 1 && column <= 8)){
            retval = 1;
        }
        return retval;
    }
    std::string getColor(std::string cmd){
        std::string retval = "";
        std::string firstChar = cmd.substr(0, 1);
        if (firstChar.compare("r") == 0 || firstChar.compare("R") == 0){
            retval = "R";
        }else if (firstChar.compare("b") == 0 || firstChar.compare("B") == 0){
            retval = "B";
        }
        return retval;
    }
    int getColumn(std::string cmd){
        int retval = -1;
        try{
            retval = std::stoi(cmd.substr(1,1));
        }catch (const std::invalid_argument& ia){
            // pass
        }
        return retval;
    }
};


class BoardWidget{
    public:
    BoardData& board;
    
    BoardWidget(BoardData& board): board(board){}
    
    void show(){
        BoardCmds cmds;

        for (int r=0; r<8; r++){
            std::cout << "0" << r+1 << " "; // prefix
            for (int c=0; c<8; c++){
                std::string show = board.grid[r][c];
                if (cmds.isCommand(show)){
                  std::string color = cmds.getColor(show);
                  show = color + color;
                }
                std::cout << show << " ";
            }
            std::cout << std::endl;
        }
                        
        std::cout << "   01 02 03 04 05 06 07 08" << std::endl;
    }
    
    int drop(std::string color, int column){
        BoardCmds cmds;
        int bottom = 7;
        int r;
        for (r=0; r<8; r++){
            if (!cmds.isCommand(board.grid[bottom-r][column-1])){
                board.grid[bottom-r][column-1] = color + std::to_string(column);
                //board.grid[bottom-r][column-1] = color + color;
                break;
            }
        }
        return bottom-r+1;
    }
    
    int sum(std::string color, int row, int column, int rise, int run){
        //std::cout << "sum("<< color << ", " <<  row << ", " << column << ", " <<  rise << ", " << run << ")" << std::endl;
        BoardCmds cmds;
        int stopRise = 0;
        int stopRun = 0;
        int retval = 0;
        int r=row; 
        int c=column;
        while(1){
            r=r+rise;
            if (r>8 || r<1){
                break;
            }
            c=c+run;
            if (c>8 || c<1){
                break;
            }            

            std::string test = this->board.grid[r-1][c-1];
            if (cmds.getColor(test).compare(color) == 0){
                retval++;
            }else{
                break;
            }
        }
        return retval;
    }
    
    int sumSlant1(std::string color, int row, int column){
        int rt = this->sum(color, row, column, 1, 1);
        int lt = this->sum(color, row, column, -1, -1);
        int ctr = 1;
        return lt+rt+ctr;
    }
    
    int sumSlant2(std::string color, int row, int column){
        int rt = this->sum(color, row, column, 1, -1);
        int lt = this->sum(color, row, column, -1, 1);
        int ctr = 1;
        return lt+rt+ctr;
    }
    
    int sumVert(std::string color, int row, int column){
        int rt = this->sum(color, row, column, 1, 0);
        int lt = this->sum(color, row, column, -1, 0);
        int ctr = 1;
        return lt+rt+ctr;
    }
    
    int sumHorz(std::string color, int row, int column){
        int rt = this->sum(color, row, column, 0, -1);
        int lt = this->sum(color, row, column, 0, 1);
        int ctr = 1;
        return lt+rt+ctr;
    }
    
    int isConnect4(std::string color, int row, int column){
        if (this->sumSlant1(color, row, column) >= 4) return 1;
        if (this->sumSlant2(color, row, column) >= 4) return 1;
        if (this->sumVert(color, row, column) >= 4) return 1;
        if (this->sumHorz(color, row, column) >= 4) return 1;
        return 0;
    }
};


int main(){
    BoardData data;
    BoardWidget widget(data);
    BoardCmds cmds;
    
    int gameOn = 1;
    
    // show initial board            
    widget.show();

    while(gameOn){
        
        std::string usrInput;
        std::cout << "Command: ";
        std::cin >> usrInput;
        if(cmds.isCommand(usrInput)){
            if (cmds.isExit(usrInput)){
                gameOn = 0;
            }else{
                std::string color = cmds.getColor(usrInput);
                int column = cmds.getColumn(usrInput);
                int row = widget.drop(color, column);
                widget.show();
                if (widget.isConnect4(color, row, column)){
                    std::cout << "CONNECT FOUR!" << std::endl;
                }
            }            
        }else{
            std::cout << "Valid commands: 'exit', 'r<1-8>', 'b<1-8>'" << std::endl;
        }
    }
    return 0;
}