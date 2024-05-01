#include "Database.h"

int main(int argc, char** argv){
    Database* db = new Database();
    db->start();
    delete db;
}