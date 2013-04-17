//
//  spreadsheet.h
//  
//
//  Created by Andres Monroy on 4/16/13.
//
//

#ifndef ____spreadsheet__
#define ____spreadsheet__

#include <iostream>
#include <string>
#include <list>
#include <stack>
#include "ss_result.h"
#include "cell.h"
#include "user.h"

namespace serverss {

    class spreadsheet{
  
    
    public:
        
        // Constructors
        spreadsheet(std::string, std::string);
        
        // Spreadsheet functions
        ss_result join(user);
        ss_result change(cell, int);
        ss_result update(cell, int);
        ss_result save();
        ss_result leave(user);
        ss_result undo(int);
    
        // Accessors
        void get_user(std::string);
        void get_all_users();
        int get_version_number();
        std::string get_password();
    
    private:
    
        std::list<std::string> users;
        std::stack<std::string> undo_stack;
        std::string password;
        std::string name;
        int version;
        
        void log();
    
    };

}

#endif /* defined(____spreadsheet__) */
