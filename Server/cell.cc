//
//  cell.cc
//  
//
//  Created by Andres Monroy on 4/16/13.
//
//

#include "cell.h"
namespace serverss {
    cell::cell(std::string cell_name, std::string contents)
    {
        this->cell_name = cell_name;
        this->contents = contents;
    }
    
    cell::cell(){
        
    }
    
    std::string cell::to_string()
    {
        return "";
    }
    
    void cell::parse_contents(std::string data)
    {
    
    }
}
