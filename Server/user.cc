//
//  user.cc
//  
//
//  Created by Andres Monroy on 4/16/13.
//
//

#include "user.h"

namespace serverss {
    
    user::user(socket* user_socket)
    {
        this->user_socket = user_socket;
    }
    
}