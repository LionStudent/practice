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
    
    void drop(std::string color, int column){
        BoardCmds cmds;
        int bottom = 7;
        for (int r=0; r<8; r++){
            if (!cmds.isCommand(board.grid[bottom-r][column-1])){
                board.grid[bottom-r][column-1] = color + std::to_string(column);
                //board.grid[bottom-r][column-1] = color + color;
                break;
            }
        }
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
                widget.drop(color, column);
            }            
        }else{
            std::cout << "Valid commands: 'exit', 'r<1-8>', 'b<1-8>'" << std::endl;
        }
    }

    
    return 0;
}