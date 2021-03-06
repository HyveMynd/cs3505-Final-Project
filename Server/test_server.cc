//
//  test_server.cc
//  
//
//  Created by Andres Monroy on 4/21/13.
//
//

#include <iostream>
#include <string>
#include "server.h"
#include "enums.h"

using namespace std;
using namespace serverss;


void write(string message)
{
    cout << "TEST LOG: " << message << endl;;
}

void write_result(ss_result& result)
{
    write("RESULTS ARE:\n\n"+result.to_string());
}

void write_fail()
{
    write("\n\n--==TEST FAIL==--\n\n");
    throw 1;
}

void test_fail(ss_result& result)
{
    if(result.status == FAIL)
    	write_result(result);
    else
        write_fail();
}

void test_ok(ss_result& result)
{
    if(result.status == OK)
    	write_result(result);
    else
        write_fail();
}

void test_wait(ss_result& result)
{
    if(result.status == WAIT)
    	write_result(result);
    else
        write_fail();
}

void test_create(server& myServer)
{
    ss_result result = myServer.do_create("testCreate", "test");
    test_ok(result);
}

void test_create_fail(server& myServer)
{
    ss_result result = myServer.do_create("testCreate", "test");
    test_fail(result);
}

void test_join(server& myServer)
{
    boost::asio::ip::tcp::socket* new_socket = NULL;
    user* new_user = new user(new_socket);
//    new_user->uid = 0;
    ss_result result = myServer.do_join("testCreate", "test", new_user);
    test_ok(result);
}

void test_join_again(server& myServer)
{
    boost::asio::ip::tcp::socket* new_socket = NULL;
    user new_user(new_socket);
    new_user.uid = 0;
    ss_result result = myServer.do_join("testCreate", "test", &new_user);
    test_fail(result);
}

void test_join_fail(server& myServer)
{
    boost::asio::ip::tcp::socket* new_socket = NULL;
    user new_user(new_socket);
    new_user.uid = 0;
    ss_result result = myServer.do_join("test_Create", "test", &new_user);
    test_fail(result);
}

void test_change_new(server& myServer)
{
    cell new_cell("A1", "123");
    ss_result result = myServer.do_change("testCreate", 0, new_cell);
    test_ok(result);
}

void test_change_exist(server& myServer)
{
    cell new_cell("A1", "321");
    ss_result result = myServer.do_change("testCreate", 1, new_cell);
    test_ok(result);
}

void test_change_no_ss(server& myServer)
{
    cell new_cell("A1", "321");
    ss_result result = myServer.do_change("test_Create", 1, new_cell);
    test_fail(result);
}

void test_change_version(server& myServer)
{
    cell new_cell("A1", "321");
    ss_result result = myServer.do_change("testCreate", 0, new_cell);
    test_wait(result);
}

void test_save(server& myServer)
{
    ss_result result = myServer.do_save("testCreate");
    test_ok(result);
}

void test_save_fail(server& myServer)
{
    ss_result result = myServer.do_save("test_Create");
    test_fail(result);
}

void test_undo(server& myServer)
{
    ss_result result = myServer.do_undo("testCreate", 2);
    test_ok(result);
}

void test_undo_fail(server& myServer)
{
    ss_result result = myServer.do_undo("test_Create", 2);
    test_fail(result);
}

void test_undo_version(server& myServer)
{
    ss_result result = myServer.do_undo("testCreate", 1);
    test_wait(result);
}

void test_undo_end(server& myServer)
{
    ss_result result = myServer.do_undo("testCreate", 0);
    
    if(result.status == END)
    	write_result(result);
    else
        write_fail();
}

void test_leave(server& myServer)
{
    boost::asio::ip::tcp::socket* new_socket = NULL;
    user new_user(new_socket);
    new_user.uid = 0;
    myServer.do_leave("testCreate", &new_user);
}

void test_leave_user(server& myServer)
{
    boost::asio::ip::tcp::socket* new_socket = NULL;
    user new_user(new_socket);
    new_user.uid = 4;
    myServer.do_leave("testCreate", &new_user);
}

int main (int argc, char* argv)
{
    write ("\n\n-----=====TESTING START=====---------\n\n");
    server myServer;
    
    /*----CREATE TESTS----*/
    write("TESTING do_create");
    test_create(myServer);
    
    write("TESTING do_create fails");
    test_create_fail(myServer);
    
    /*----JOIN TESTS----*/
    write("TESTING do_join");
    test_join(myServer);

    write("TESTING do_join fails");
    test_join_fail(myServer);
    
    write("TESTING do_join again");
    test_join_again(myServer);
    
    /*----UNDO TESTS----*/
    write("TESITNG do_undo no changes to undo");
    test_undo_end(myServer);
    
    /*----CHANGE TESTS----*/
	write("TESTING do_change new");
    test_change_new(myServer);
    
    write("TESTING do_change existing");
    test_change_exist(myServer);
    
    write("TESITNG do_change fail no SS");
    test_change_no_ss(myServer);
    
    write("TESITNG do_change fail wrong version");
    test_change_version(myServer);
    
    /*----UNDO TESTS----*/
    write("TESITNG do_undo");
    test_undo(myServer);
    
    write("TESITNG do_undo_fail cant find SS");
    test_undo_fail(myServer);
    
    write("TESITNG do_undo_fail wrong version");
    test_undo_version(myServer);

    
    /*----SAVE TESTS----*/
    write("TESITNG do_save");
    test_save(myServer);

    write("TESITNG do_save fail");
    test_save_fail(myServer);
    
    /*----LEAVE TESTS----*/
    write("TESITNG do_leave fail no user");
    test_leave_user(myServer);

    write("TESITNG do_leave");
    test_leave(myServer);
    
    write("TESITNG do_leave again. SS should not be found");
    test_leave(myServer);

    
    cout << "TESTING DONE!" << endl;
    return 0;
}
