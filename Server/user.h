//
//  user.h
//  
//
//  Created by Andres Monroy on 4/16/13.
//
//

#ifndef ____user__
#define ____user__

#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

namespace serverss{
    class user{
    private:
        
        boost::asio::ip::tcp::socket* user_socket;
        
    public:
        user(boost::asio::ip::tcp::socket*);
    };
}

#endif /* defined(____user__) */