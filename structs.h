#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct date{
    int day,month,year;
}date;

typedef struct book{
    char title[50];
    char author[50];
    char publisher[50];
    char ISBN[50];
    date pub;
    int no_of_copies;
    int current_no;
    char category[50];
}book;

typedef struct address{
    char building[20];
    char street[20];
    char city[20];
}address;

typedef struct member{
    char last_name[20];
    char first_name[20];
    int ID;
    address s;
    char mobile[15];
    char age[3];
    char mail[50];
}member;

typedef struct {
    char ISBN[50];
    int ID;
    date borrowed_on;
    date due;
    date returned_on;
}borrowed;

typedef struct {
    book b_book;
    int times_borrowed;
}popular;

book books_array[100];
member members_array[100];
borrowed borrowed_array[100];
popular popular_array[100];
int mem = 0;
int save;
int books = 0;
int bookindex = 0;
int borrows=0;


#endif // STRUCTS_H_INCLUDED
