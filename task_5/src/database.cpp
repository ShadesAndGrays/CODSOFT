#include <cstdlib>
#include <database.hpp>
#include <iostream>
#include <mariadb/conncpp/Connection.hpp>
#include <mariadb/conncpp/Driver.hpp>
#include <mariadb/conncpp/DriverManager.hpp>
#include <mariadb/conncpp/Exception.hpp>
#include <memory>
#include <vector>


std::shared_ptr<DatabaseManger> DatabaseManger::dbManager = nullptr;


std::shared_ptr<DatabaseManger> DatabaseManger::getInstance(){
    if (dbManager == nullptr){
        dbManager.reset(new DatabaseManger); 
        std::cout << "manager has been created" << std::endl;
       dbManager->conn.reset(sql::mariadb::get_driver_instance()->connect("127.0.0.1",getenv("DB_USER"),getenv("DB_PASSWORD")));
       dbManager->conn->setSchema("bookDB");
    }
    return dbManager;
}

void DatabaseManger::cleanUp(){
    conn->close();
}

std::shared_ptr<sql::Connection> DatabaseManger::getConnection(){
    if(!conn)
        std::cerr << "Connection was not established" << std::endl;
    else
        return conn;
    return nullptr;
}

std::vector<schema::Book> DatabaseManger::getBooks(){
    auto x = getConnection()->prepareStatement("SELECT * FROM bookInfo");
    std::unique_ptr<sql::ResultSet> rs ( x->executeQuery());
    std::vector<schema::Book> books;
    while(rs->next()){
        schema::Book book;
        book.author = rs->getString("author");
        book.title = rs->getString("title");
        book.isbn = rs->getString("isbn");
        book.noOfCopies = rs->getInt("noOfCopies");
        books.push_back(book);
    }
    return books;
}
void DatabaseManger::addBook(schema::Book bk){
    auto x = getConnection()->prepareStatement("INSERT INTO bookInfo VALUES(?,?,?,?)");
    x->setString(1, bk.title);
    x->setString(2, bk.author);
    x->setString(3, bk.isbn);
    x->setInt(4, bk.noOfCopies);

    try {
     int rs =  x->executeUpdate();
    }catch(sql::SQLSyntaxErrorException e){
        std::cerr << "An error occured: " << e.what() << std::endl;
    }
}


std::vector<schema::Book> DatabaseManger::getBooks(std::string column, std::string cmp, bool exact){
    std::string query = "SELECT * FROM bookInfo where " + column + (exact ? " = " : " LIKE ") + "?";
    std::cout << query << std::endl;
    auto x = getConnection()->prepareStatement(query);
    x->setString(1, cmp);
    std::unique_ptr<sql::ResultSet> rs ( x->executeQuery());
    std::vector<schema::Book> books;
    while(rs->next()){
        schema::Book book;
        book.author = rs->getString("author");
        book.title = rs->getString("title");
        book.isbn = rs->getString("isbn");
        book.noOfCopies = rs->getInt("noOfCopies");
        books.push_back(book);
    }
    return books;

}

void DatabaseManger::borrowBook(std::vector<std::string> isbnOfBooks){

    for i 
    auto x = getConnection()->prepareStatement("INSERT INTO bookInfo VALUES(?,?,?,?)");
    x->setString(1, bk.title);
    x->setString(2, bk.author);
    x->setString(3, bk.isbn);
    x->setInt(4, bk.noOfCopies);

    try {
     int rs =  x->executeUpdate();
    }catch(sql::SQLSyntaxErrorException e){
        std::cerr << "An error occured: " << e.what() << std::endl;
    }
    // create book id 
    // add books to borrow log
    // display success message

}
void schema::printBooks(std::vector<schema::Book> books){
    for (auto book: books){
        std::cout << "\t Title: " << book.title;
        std::cout << "\t\t Author: " << book.author;
        std::cout << "\t ISBN: " << book.isbn;
        std::cout << "\t No. of Copies: " << book.noOfCopies<<std::endl;
    }
    std::cout << std::endl;
}
