#include<iostream>
#include<string>
#include<tuple>
#include<variant>
std::tuple<std::string, std::variant<int, std::string>> getToken(std::string input){
    std::string token;
    std::string argument;
    int argument_pos = 0;
    bool found_braces = false;
    for(int i = 0; i < input.length(); i++){
        if(input[i]== '(' || input[i] == ' '){
            argument_pos = i + 1;
            found_braces = true;
            break;
        }else{
            token+= input[i];
        }
    }
    if(!found_braces){
        return std::make_tuple("Fail", "Error: No argument found");
    }
    if(argument_pos < input.length()){
        argument += input.substr(argument_pos);
        argument.pop_back(); // Remove trailing newline
    }
    if(argument.empty()) {
        return std::make_tuple(token, std::variant<int, std::string>{});
    }
    if(argument[0] != '"'){
        return std::make_tuple(token, std::variant<int, std::string>{std::stoi(argument)});
    }
    argument.erase(0, 1); // Remove leading quote
    argument.pop_back();  // Remove trailing quote
    return std::make_tuple(token, std::variant<int, std::string>{argument});
}


void count(int x){
    std::cout << "Counting to " << x << std::endl;
    for(int i = 0; i <= x; i++){
        std::cout << i << std::endl;
    }
    std::cout << std::endl;
}

int eval(std::string expression){
    // Placeholder for evaluation logic
    int size = expression.size();
    int nums[2];
    char op;
    int index = 0;
    std::string temp = "";
    for(int i = 0; i < size; i++){
        if(isdigit(expression[i])){
                temp += expression[i];
        }else{
                nums[index] = std::stoi(temp);
                temp = "";
                op = expression[i];
                index++;
            }

        }
        nums[index] = std::stoi(temp); // Last number
        if(op == '+'){
            return nums[0] + nums[1];
        }
        if(op == '-'){
            return nums[0] - nums[1];
        }
        if(op == '*'){
            return nums[0] * nums[1];
        }
        if(op == '/'){
            if(nums[1] == 0){
                std::cout << "Error: Division by zero!" << std::endl;
                return 0;
            }
            return nums[0] / nums[1];
        }
    return 0; // Return 0 if no valid operation is found
}


int main() {
    std::cout << "Welcome to the Shell program!" << std::endl;
    std::string command;
    bool running = true;
    while(running){
        std::cout << "> ";
        std::getline(std::cin, command);
        auto [token,argument] = getToken(command);
        // Terminate the program if the user types "exit"
        if(token == "exit"){running = false;}

        //evaluate the expression if the user types "eval"
        else if(token == "hello"){
            if(token.empty()){
                std::cout << "Hello, World!" << std::endl;
            } else {
                if(std::holds_alternative<std::string>(argument)) {
                    std::cout << "Hello, " << std::get<std::string>(argument) << "!" << std::endl;
                } else if(std::holds_alternative<int>(argument)) {
                    std::cout << "Hello, world!" << std::endl;
                }
            }}
        // Clear the console if the user types "clear"
        else if(token == "clear"){
            std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the console
            std::cout << "Console cleared." << std::endl;}
        
        else if(token == "Fail"){
            // Print the error message from the variant (should always be std::string in this case)
            if(std::holds_alternative<std::string>(argument)) {
                std::cout << std::get<std::string>(argument) << std::endl;
            } else if(std::holds_alternative<int>(argument)) {
                std::cout << std::get<int>(argument) << std::endl;
            } else {
                std::cout << "Unknown error" << std::endl;
            }
            
        }
        // Print the argument if the command is "print"
        else if(token == "print"){
            std::cout << std::get<std::string>(argument) << std::endl;
        }  
        // Count to the number provided in the argument if the command is "count"
        else if(token == "count"){
            std::cout<<"Test"<< std::endl;
            count(std::get<int>(argument));
        }

        else if(token== "fireball"){
            std::cout<< "You cast a fireball at: " << std::get<std::string>(argument) <<std::endl;
        }else if(token == "eval"){
            std::cout << eval(std::get<std::string>(argument)) << std::endl;
        }



        // Print help information if the user types "help"
        else if(token == "help"){
            std::cout<<"Command structure: command(argument)"<<std::endl;
            std::cout << "Available commands:" << std::endl;
            std::cout << "hello [name] - Greet the user or the world" << std::endl;
            std::cout << "count (number) - Count to the specified number" << std::endl;
            std::cout << "print (message) - Print the specified message" << std::endl;
            std::cout << "clear - Clear the console" << std::endl;
            std::cout << "exit - Exit the program" << std::endl;
            std::cout << "eval('expression (such as '2+2'. Does not take multiple operations)') - Evaluate an expression." << std::endl;
            std::cout << "fireball(target) - Cast a fireball at the specified target" << std::endl;
            std::cout << "help - Show this help message" << std::endl;
        }
        


        
        else{std::cout<<"Command not found. use the help() command to see available commands."<<std::endl;}




    }
        
    return 0;
    }
