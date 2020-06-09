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
        for (int r=0; r<8; r++){
            for (int c=0; c<8; c++){
                std::cout << board.grid[r][c] << " ";
            }
            std::cout << std::endl;
        }
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
        std::cout << "sum("<< color << ", " <<  row << ", " << column << ", " <<  rise << ", " << run << ")" << std::endl;

        BoardCmds cmds;
        int stopRise = 0;
        int stopRun = 0;
        int retval = 0;
        int r=row; 
        int c=column;
        while(1){
            std::cout << "log: " <<  r << " " << c << " " <<  this->board.grid[r-1][c-1] << std::endl;
            r=r+rise;
            if (r>8 || r<1){
                break;
            }
            c=c+run;
            if (c>8 || c<1){
                break;
            }            

            std::string test = this->board.grid[r-1][c-1];
            std::cout << "log: " <<  r << " " << c << " " << test << std::endl;
            std::cout << "log: " <<  cmds.getColor(test) << " == " << color << std::endl;
            if (cmds.getColor(test).compare(color) == 0){
                retval++;
            }else{
                break;
            }
        }
        return retval;
    }
};


int main(){
    /*
    std::string x;
    std::cin >> x ;
    std::cout << "Echo: " << x << std::endl;
    */
    
    BoardData data;
    BoardWidget widget(data);
    BoardCmds cmds;
    
    int gameOn = 1;
    while(gameOn){
        widget.show();
        
        std::string usrInput;
        std::cin >> usrInput;
        if(cmds.isCommand(usrInput)){
            if (cmds.isExit(usrInput)){
                gameOn = 0;
            }else{
                std::string color = cmds.getColor(usrInput);
                int column = cmds.getColumn(usrInput);
                //std::cout << color << column << std::endl;
                int row = widget.drop(color, column);
                int rt = widget.sum(color, row, column, 0, 1);
                int lt = widget.sum(color, row, column, 0, -1);
                std::cout << "isConnect4: " <<  rt << " + " << lt << std::endl;

            }            
        }else{
            std::cout << "Valid commands: 'exit', 'r<1-8>', 'b<1-8>'" << std::endl;
        }
    }

    
    return 0;
}