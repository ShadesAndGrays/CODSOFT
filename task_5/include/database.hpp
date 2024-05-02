#pragma once

#include <mariadb/conncpp.hpp>
#include <mariadb/conncpp/Connection.hpp>
#include <memory>
#include <vector>

namespace schema{
    struct Book{
        std::string title;
        std::string author;
        std::string isbn;
        int noOfCopies;
    };
    void printBooks(std::vector<schema::Book> books);
}

class DatabaseManger{


        DatabaseManger() = default;
    private:
        std::shared_ptr<sql::Connection> conn;
        static std::shared_ptr<DatabaseManger> dbManager;

    public:
        static std::shared_ptr<DatabaseManger> getInstance();
        std::shared_ptr<sql::Connection> getConnection();
        std::vector<schema::Book> getBooks();
        std::vector<schema::Book> getBooks(std::string column, std::string cmp, bool exact = false);
        void addBook(schema::Book bk);
        void cleanUp();


};

// requires ENVIRONMENT VARIABLES
