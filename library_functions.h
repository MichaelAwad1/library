#ifndef LIBRARY_FUNCTIONS_H_INCLUDED
#define LIBRARY_FUNCTIONS_H_INCLUDED

void Borrowing(book a,member b);
void read_borrowed();
void print_borrowed();
void Returned(borrowed a);
void popular_books();
int dateCompare(date a,date b);
void print_overdue(borrowed a);
void overdue();
void add_new_book();
void read_members(char const * filename);
void add_new_member();
void print_books(book booksarray[], int n);
int sub_search(char* needle, char* haystack);
void search_books_by_name(char * key);book search_by_ISBN();
void search_books_by_cat(char * key);
void search_books_by_author(char * key);
void save_changes();
void add_new_copy();
void removeMember();
void removeBook();
void main_menu();
int check_id(char *id);
int check_isbn(char *a);


int mobile_validation(char *a){
    int i;
    for(i=0;i<strlen(a);i++){
        if(isdigit(a[i])==0 || a[0]!='0' || a[1]!='1' || strlen(a)!=11){
         printf("Invalid mobile, please enter valid mobile which is 11 numbers starting with 01 : ");
            return 0;

          //  not valid
       }
    }
        return 1;
}

int str_validation(char *a){
    int i;
    for(i=0;i<strlen(a);i++){
        if((isalpha(a[i])==0) && (a[i]!=' ') ){
           printf("Invalid String, please enter valid one: ");
            return 0;

          //  not valid
       }
    }
        return 1;
}

int number_validation(char *a){
    int i;
    for(i=0;i<strlen(a);i++){
        if(isdigit(a[i])==0){
         printf("Invalid number, please enter valid one: ");
            return 0;

          //  not valid
       }
    }
        return 1;
}

int positive(int n){
    if(n<0){
        printf("Please Enter positive number :");
        return 0;
    }
    return 1;
}

int date_validation(int a, int b, int c){
    if((a<1 || a> 31) || (b<1 || b>12) || (c<1 ||c>2018)){
        printf("Invalid Date please enter: day between 1-31,month between 1-12, year between 1-2018 : ");
        return 0;  //  not valid
    }
    return 1;
}

int check_isbn(char *a){
    int i;
    for(i=0;i<books;i++)
    {
        if(strcmp(a,books_array[i].ISBN)==0)
            return 1;
    }
    return 0;
}

int check_id(char * id){
    int i;
    for(i=0;i<mem;i++)
    {
        if(strcmp(id,members_array[i].ID)==0)
            return 1;

    }
    return 0;
}

void Borrowing(book a,member b){
        borrowed br;
        int i,idcount=0,index=0;
        for(i=0;i<100;i++)
        {
            if(borrowed_array[i].ID==b.ID && borrowed_array[i].returned_on.day==0)
                idcount++;
        }
        for(i=0;i<100;i++)
        {
            if(strcmp(books_array[i].ISBN,a.ISBN)==0)
            {
                index=i;
                if(books_array[index].current_no<1)
                        {
            printf("Book is currently not available.\n");
            main_menu();
                        }
                else
                {
                    books_array[index].current_no--;
                }
            }
        }
       if(idcount>2)
                        {
            printf("Member has reached maximum number of borrowed books.\n");
                   books_array[index].current_no++;
                                main_menu();
                          }
        else {
        strcpy(br.ISBN,a.ISBN);
        br.ID=b.ID;
        time_t t= time(NULL);
        struct tm tm= *localtime(&t);
        br.borrowed_on.day=tm.tm_mday;
        br.borrowed_on.month=tm.tm_mon+1;
        br.borrowed_on.year=tm.tm_year+1900;
        printf("Enter due date:");
        scanf("%d%d%d",&br.due.day,&br.due.month,&br.due.year);
        while(date_validation(br.due.day,br.due.month,br.due.year)==0){
        scanf("%d%d%d",&br.due.day,&br.due.month,&br.due.year);
                            }
        br.returned_on.day=0;
        br.returned_on.month=0;
        br.returned_on.year=0;
        borrowed_array[borrows]= br;
        borrows++;
        }

}

void read_borrowed(){
      FILE *f;
      borrows=0;
      f=fopen("borrowed.txt","r");
      if(f==NULL){
          printf("Can't open file");
      }
      else{
          while(!feof(f)){

            fscanf(f,"%[^,]",&borrowed_array[borrows].ISBN);
            fscanf(f,",");
            fscanf(f,"%d",&borrowed_array[borrows].ID);
            fscanf(f,",");
            fscanf(f,"%d",&borrowed_array[borrows].borrowed_on.day);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].borrowed_on.month);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].borrowed_on.year);
            fscanf(f,",");
            fscanf(f,"%d",&borrowed_array[borrows].due.day);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].due.month);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].due.year);
            fscanf(f,",");
            fscanf(f,"%d",&borrowed_array[borrows].returned_on.day);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].returned_on.month);
            fscanf(f,"/");
            fscanf(f,"%d",&borrowed_array[borrows].returned_on.year);
            fscanf(f,"\n");
              borrows++;

          }
          printf("Finished reading the borrows\n");
      fclose(f);
    }
}

void print_borrowed(){
      int i=0;
      while(i<borrows){
          printf("Borrow #%d : ISBN:%s, ID:%d, Borrowed on:%d/%d/%d, Due Date:%d/%d/%d, Returned on:%d/%d/%d\n",i,borrowed_array[i].ISBN,
                                                       borrowed_array[i].ID,
                                                       borrowed_array[i].borrowed_on.day,
                                                       borrowed_array[i].borrowed_on.month,
                                                       borrowed_array[i].borrowed_on.year,
                                                       borrowed_array[i].due.day,
                                                       borrowed_array[i].due.month,
                                                       borrowed_array[i].due.year,
                                                       borrowed_array[i].returned_on.day,
                                                       borrowed_array[i].returned_on.month,
                                                       borrowed_array[i].returned_on.year);
          i++;
        }
        printf("Finished printing the file\n" );
  }

void Returned(borrowed a){

    time_t t= time(NULL);
    struct tm *t2= localtime(&t);
    int i;
    for(i=0;i<100;i++)
    {
            if( strcmp(borrowed_array[i].ISBN,a.ISBN)==0 && borrowed_array[i].ID==a.ID)
            {
                books_array[i].current_no++;
                borrowed_array[i].returned_on.day=t2->tm_mday;
                borrowed_array[i].returned_on.month=t2->tm_mon+1;
                borrowed_array[i].returned_on.year=t2->tm_year+1900;
            }
    }
  }

void popular_books(){
    int i,j;
    int counter;
    for(i=0;i<100;i++)
    {
        counter=0;
        popular_array[i].b_book=books_array[i];
        for(j=0;j<100;j++)
        {

            if(strcmp(borrowed_array[j].ISBN,books_array[i].ISBN)==0)
            counter++;
        }
    popular_array[i].times_borrowed=counter;

    }
    popular temp=popular_array[0];
    for(j=0;j<books-1;j++){
        for(i=0;i<books-1;i++)
    {

        if(popular_array[i].times_borrowed<popular_array[i+1].times_borrowed)
        {
            temp=popular_array[i];
            popular_array[i]=popular_array[i+1];
            popular_array[i+1]=temp;
        }
    }
    }
    printf("POPULAR BOOKS:\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    for(i=0;i<5;i++)
    {
        printf("%s\n",popular_array[i].b_book.title);
    }

  }

int dateCompare(date a,date b){
    if(a.year>b.year)
        return 1;
    else if(a.year==b.year)
    {
        if(a.month>b.month)
            return 1;
        else if(a.month==b.month)
        {
            if(a.day>b.day)
                return 1;
            else return 0;
        }
        else return 0;
    }
    else return 0;
}

void print_overdue(borrowed a){

          printf("ISBN:%s, ID:%s, Borrowed on:%d/%d/%d, Due Date:%d/%d/%d, Returned on:%d/%d/%d\n",a.ISBN,
                                                       a.ID,
                                                       a.borrowed_on.day,
                                                       a.borrowed_on.month,
                                                       a.borrowed_on.year,
                                                       a.due.day,
                                                       a.due.month,
                                                       a.due.year,
                                                       a.returned_on.day,
                                                       a.returned_on.month,
                                                       a.returned_on.year);

        printf("\n");

  }

void overdue(){
    int i,j;
    time_t t= time(NULL);
    struct tm tm= *localtime(&t);
    printf("OVERDUE BOOKS\n");
    printf("~~~~~~~~~~~~~~~~~~\n");
    date todays_date;
    todays_date.day= tm.tm_mday;
    todays_date.month= tm.tm_mon+1;
    todays_date.year= tm.tm_year+1900;
    for(i=0;i<borrows;i++)
    {
        if(borrowed_array[i].returned_on.day==0)
        {
            if(dateCompare(todays_date,borrowed_array[i].due)>0)
                print_overdue(borrowed_array[i]);
        }
    }


  }

int sub_search(char* needle, char* haystack){
  if(strstr(haystack,needle) != NULL)
    return 1;
  else return 0;
}

void search_books_by_name(char * key){
  int i;
  int found = 0;
  book arr[100];
  char target[50];
  char k[50];
  book b;
  int l =0;
  for(i=0; i<books; i++){
     b = books_array[i];
    int j;
    for(j=0;j<strlen(key); j++){
      char x = key[j];
      x = toupper(x);
      k[j] = x;
    }
    char t[50];
    strcpy(t, b.title);
    for(j=0; j<strlen(t); j++){
      char x = t[j];
      x = toupper(x);
      target[j] = x;
    }
found = sub_search(k, target);
    if(found == 1){
      arr[l] = b;
      l++;

  }

  }
     if(l!=0){
         print_books(arr,l);
     }
     else
        printf("No books\n");
}

void search_books_by_cat(char * key){
  int i;
  int found;
  book arr[100];
  char target[50];
  char k[50];
  book b;
  int l =0;
  for(i=0; i<books; i++){
     b = books_array[i];
    int j;
    for(j=0;j<strlen(key); j++){
      char x = key[j];
      x = toupper(x);
      k[j] = x;
    }
    char t[50];
    strcpy(t, b.category);
    for(j=0; j<strlen(t); j++){
      char x = t[j];
      x = toupper(x);
      target[j] = x;
    }
found = sub_search(k, target);
    if(found == 1){
      arr[l] = b;
      l++;

  }

  }
     if(l!=0){
         print_books(arr,l);
     }
     else
        printf("No books\n");
}

void search_books_by_author(char * key){
 int i;
  int found;
  book arr[100];
  char target[50];
  char k[50];
  book b;
  int l =0;
  for(i=0; i<books; i++){
     b = books_array[i];
    int j;
    for(j=0;j<strlen(key); j++){
      char x = key[j];
      x = toupper(x);
      k[j] = x;
    }
    char t[50];
    strcpy(t, b.author);
    for(j=0; j<strlen(t); j++){
      char x = t[j];
      x = toupper(x);
      target[j] = x;
    }
found = sub_search(k, target);
    if(found == 1){
      arr[l] = b;
      l++;
      }

  }
     if(l!=0){
         print_books(arr,l);
     }
     else  {
        printf("No books\n");
     }

}

void add_new_book() {
   book b;
   printf("Enter book's title : ");
   gets(b.title);
   gets(b.title);
   printf("Enter book's author : ");
   gets(b.author);
   while(str_validation(b.author)==0){
   gets(b.author);
   }
   printf("Enter book's publisher : ");
   gets(b.publisher);
   while(str_validation(b.publisher)==0){
   gets(b.publisher);
   }
   printf("Enter book's ISBN : ");
   gets(b.ISBN);
   printf("Enter book's DOP : ");
   scanf("%d%d%d",&b.pub.day,&b.pub.month,&b.pub.year);
   while(date_validation(b.pub.day,b.pub.month,b.pub.year)==0){
     scanf("%d%d%d",&b.pub.day,&b.pub.month,&b.pub.year);
   }
   printf("Enter book's  original number of copies : ");
   scanf("%d",&b.no_of_copies);
   while(positive(b.no_of_copies)==0){
       scanf("%d",&b.no_of_copies);
   }
   printf("Enter book's current number of copies : ");
   scanf("%d",&b.current_no);
   while(positive(b.current_no)==0){
       scanf("%d",&b.current_no);
   }
   printf("Enter book's category : ");
   gets(b.category);
   gets(b.category);
   while(str_validation(b.category)==0){
   gets(b.category);
   }
   books_array[books] = b;
   books++;
   }

void add_new_member(){
    member m;
    int i,z=0;
        printf("Please enter user's last name ");
        gets(m.last_name);
        gets(m.last_name);
        while(str_validation(m.last_name)==0){
             gets(m.last_name);
        }
        printf("Please enter user's first name ");
        gets(m.first_name);
        while(str_validation(m.first_name)==0){
             gets(m.first_name);
        }
        printf("Please enter user's ID ");
        scanf("%d",m.ID);
        while(number_validation(m.ID)==0){
                    scanf("%d",m.ID);
        }
        while(check_id(m.ID)==1 ){
        printf("ID already exists, please enter unique ID:");
        scanf("%d",m.ID); }
        printf("Enter users' buliding ");
        gets(m.s.building);
        while(number_validation(m.s.building)==0){
                    gets(m.s.building);
        }
        printf("Enter user's street ");
        gets(m.s.street);
        printf("Enter user's city ");
        gets(m.s.city);
        while(str_validation(m.s.city)==0){
             gets(m.s.city);
        }
        printf("Enter user's mobile " );
        gets(m.mobile);
        while(mobile_validation(m.mobile)==0){
                    gets(m.mobile);

        }
        printf("Enter user's age " );
        gets(m.age);
        while(number_validation(m.age)==0){
             gets(m.age);
        }
        printf("Enter user's mail ");
        gets(m.mail);
       members_array[mem] = m;
       mem++;
    }

void read_members(char const * filename){
    FILE *f;
    mem=0;
    f=fopen(filename,"r");
    if(f==NULL){
        printf("Can't open file");
        return;
    }
    else{
        while(fscanf(f,"%[^,], %[^,], %d, %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]",members_array[mem].last_name,
                                                                                members_array[mem].first_name,
                                                                                &members_array[mem].ID,
                                                                                members_array[mem].s.building,
                                                                                members_array[mem].s.street,
                                                                                members_array[mem].s.city,
                                                                                members_array[mem].mobile,
                                                                                &members_array[mem].age,
                                                                                members_array[mem].mail) == 9)
        {
            mem++;
        }
        printf("Finished reading the members\n");


    fclose(f);
    }
  }

void print_members(){
      int i=0;
      while(i<mem){
printf("Member # %d\n",i);
printf("Last name: %s, First name: %s, ID: %d, Buliding: %s, Street: %s, City: %s, Mobile: %s, Age: %s, Mail: %s\n",
                                                       members_array[i].last_name,
                                                       members_array[i].first_name,
                                                       members_array[i].ID,
                                                       members_array[i].s.building,
                                                       members_array[i].s.street,
                                                       members_array[i].s.city,
                                                       members_array[i].mobile,
                                                       members_array[i].age,
                                                       members_array[i].mail);
          i++;
        }
        printf("\nFinished printing the file\n" );
  }

void read_books(char const* filename){
      FILE *f;
      books=0;
      f=fopen(filename,"r");
      if(f==NULL){
          printf("Can't open file");
          return ;
      }
      else{
          while(fscanf(f,"%[^,], %[^,], %[^,], %[^,], %d/%d/%d, %d, %d, %[^\n]",books_array[books].title,
                                                                                books_array[books].author,
                                                                                books_array[books].publisher,
                                                                                books_array[books].ISBN,
                                                                                &books_array[books].pub.day,
                                                                                &books_array[books].pub.month,
                                                                                &books_array[books].pub.year,
                                                                                &books_array[books].no_of_copies,
                                                                                &books_array[books].current_no,
                                                                                books_array[books].category) == 10){
              books++;

          }
                  printf("Finished reading the books\n");
      fclose(f);
    }
}

void print_books(book booksarray[], int n){
  int i=0;
      while(i<n){
          printf("Book #%d: %s, %s, %s, %s, %d/%d/%d, %d, %d, %s\n",i,
                                                        booksarray[i].title,
                                                        booksarray[i].author,
                                                        booksarray[i].publisher,
                                                        booksarray[i].ISBN,
                                                        booksarray[i].pub.day,
                                                        booksarray[i].pub.month,
                                                        booksarray[i].pub.year,
                                                        booksarray[i].no_of_copies,
                                                        booksarray[i].current_no,
                                                        booksarray[i].category);
      i++;
  }
          printf("Finished printing the file\n" );
}

book search_by_ISBN(){
    char isbn[50];
    int i;
    printf("Please enter book's ISBN: \n");
    gets(isbn);
    gets(isbn);
    for(i=0;i<books;i++){
        if(strcmp(books_array[i].ISBN,isbn)==0){
            return books_array[i];
             }


    }

}

void save_changes(){
    FILE *f1,*f2,*f3;
    int i;
    f1=fopen("users.txt","w");
    if(f1==NULL){
        printf("CANNOT OPEN THE FILE\n");

    }
    else{
        for(i=0;i<mem;i++){
            fprintf(f1,"%s, %s, %d, %s, %s, %s, %s, %s, %s\n",members_array[i].last_name,
                                                       members_array[i].first_name,
                                                       members_array[i].ID,
                                                       members_array[i].s.building,
                                                       members_array[i].s.street,
                                                       members_array[i].s.city,
                                                       members_array[i].mobile,
                                                       members_array[i].age,
                                                       members_array[i].mail);

        }
    }

   fclose(f1);
   f2=fopen("books.txt","w");
    if(f2==NULL){
        printf("CANNOT OPEN THE FILE\n");

    }
    else{
        for(i=0;i<books;i++){
             fprintf(f2,"%s, %s, %s, %s, %d/%d/%d, %d, %d, %s\n",books_array[i].title,
                                                        books_array[i].author,
                                                        books_array[i].publisher,
                                                        books_array[i].ISBN,
                                                        books_array[i].pub.day,
                                                        books_array[i].pub.month,
                                                        books_array[i].pub.year,
                                                        books_array[i].no_of_copies,
                                                        books_array[i].current_no,
                                                        books_array[i].category);

        }
           fclose(f2);
    }


    f3=fopen("borrowed.txt","w");
    if(f3==NULL){
        printf("CANNOT OPEN THE FILE\n");

    }
    else{
        for(i=0;i<borrows;i++){
             fprintf(f3,"%s, %d, %d/%d/%d, %d/%d/%d, %d/%d/%d\n",borrowed_array[i].ISBN,
                                                       borrowed_array[i].ID,
                                                       borrowed_array[i].borrowed_on.day,
                                                       borrowed_array[i].borrowed_on.month,
                                                       borrowed_array[i].borrowed_on.year,
                                                       borrowed_array[i].due.day,
                                                       borrowed_array[i].due.month,
                                                       borrowed_array[i].due.year,
                                                       borrowed_array[i].returned_on.day,
                                                       borrowed_array[i].returned_on.month,
                                                       borrowed_array[i].returned_on.year);

        }
        fclose(f3);
      }
  }

void add_new_copy(){
    char isbn[50];
    int i,n;
    book temp;
    printf("Please enter book's ISBN :\n");
    gets(isbn);
    gets(isbn);
    for(i=0;i<books;i++){
        if(strcmp(books_array[i].ISBN,isbn)==0){
            printf("Enter number of copies :\n");
            scanf("%d",&n);
            while(positive(n)==0){
                scanf("%d",&n);
            }
            books_array[i].current_no+= n;
            return;
        }
    }


}

void removeMember(){
    int m,i,check=1;
    print_members();
    printf("Choose which member to remove:\n");
    scanf("%d",&m);
    if(m<0 || m>mem-1){
        printf("Invalid Entry please choose from 0 to %d\n",mem-1);
        removeMember();
    }
    for(i=0;i<100;i++)
    {
        if(members_array[m].ID==borrowed_array[i].ID && borrowed_array[i].returned_on.day ==0)
            check=0;

        }

    if(check==1){
    for(i=m;i<mem-1;i++)
    {
        members_array[i]=members_array[i+1];
    }
    mem--;
    printf("Member #%d removed successfully!\n",m);
    }
    else printf("Cannot remove member, return borrowed books first.\n");
}

void removeBook(){
    int m,i;
    print_books(books_array, books);
    printf("Choose which book to remove:\n");
    scanf("%d",&m);
    if(m<0 || m>books-1){
        printf("Invalid Entry please choose from 0 to %d\n",books-1);
        removeBook();
    }
    else{
    for(i=m;i<books-1;i++)
    {
        books_array[i]=books_array[i+1];
    }
    books--;
    printf("Book #%d removed successfully!\n",m);
}
}

void main_menu(){
    int a,y;
    char x;
    int cont = 1;
    while(cont){
      printf("\t\t\t LIBRARY MANAGMENT SYSTEM\n");
      printf("\t\t\t       MAIN MENU\n");
           printf("\t\t\t 0-LOAD FILE\n");
           printf("\t\t\t 1-BOOK MANAGEMENT\n");
           printf("\t\t\t 2-MEMBER TRANSACTIONS\n");
           printf("\t\t\t 3-BORROW MANAGEMENT\n");
           printf("\t\t\t 4-ADMINISTRATIVE ACTIONS\n");
           printf("\t\t\t 5-View all members\n");
           printf("\t\t\t 6-View all books\n");
           printf("\t\t\t 7-View all borrows\n");
           printf("\t\t\t 8-SAVE CHANGES\n");
           printf("\t\t\t 9-QUIT PROGRAM\n");
           scanf("%d",&a);
           while(a<0 || a>9){
             printf("Error unvalid option\n Enter a choice between 0 and 6\n");
             main_menu();
           }
           if(a==0){
             printf("LOADING FILES \n");
             read_members("users.txt");
             read_books("books.txt");
             read_borrowed();
           }

           else if(a==1){

             printf("\t\t\t A-INSERT A BOOK\n");
             printf("\t\t\t B-SEARCH FOR A BOOK\n");
             printf("\t\t\t C-ADD A NEW COPY\n");
             printf("\t\t\t D-DELETE A BOOK\n");
             printf("for main menu press s\n");
             scanf("%c",&x);
             scanf("%c",&x);

             while(x != 'A' && x!= 'a' && x!= 'b' && x!='B' && x!='c' && x!= 'C' && x!= 'd' && x!='D' && x!='s' && x!='S'){
               printf("Error invalid option please choose again\n");
               printf("\t\t\t A-INSERT A BOOK\n");
               printf("\t\t\t B-SEARCH FOR A BOOK\n");
               printf("\t\t\t C-ADD A NEW COPY\n");
               printf("\t\t\t D-DELETE A BOOK\n");
               printf("for main menu press s\n");
               scanf("%c",&x);
               scanf("%c",&x);
             }

             if(x=='a' || x=='A'){
                 add_new_book();
                 save =0;
             }
             else if(x=='b' || x=='B'){
                 printf("\t\t\t1-Search by title\n");
                 printf("\t\t\t2-Search by author\n");
                 printf("\t\t\t3-Search by ISBN\n");
                 printf("\t\t\t4-Search by category\n");
                 scanf("%d",&y);
                 if(y<1||y>4){
                     printf("invalid option Please enter number between 1 and 4\n");
                     printf("\t\t\t1-Search by title\n");
                 printf("\t\t\t2-Search by author\n");
                 printf("\t\t\t3-Search by ISBN\n");
                 printf("\t\t\t4-Search by category\n");
                 scanf("%d",&y);
                 }
                 if(y==1){

                     char key1[50];
                     printf("Enter book's name or part of it\n");
                     gets(key1);
                     gets(key1);
                     printf("Books found: \n");
                     search_books_by_name(key1);
                 }
                 else if(y==2){

                     char key2[50];
                     printf("Enter author's name or part of it\n");
                     gets(key2);
                     gets(key2);
                     printf("Books found: \n");
                     search_books_by_author(key2);
                 }
                 else if (y==3){

                     book x;
                        x=search_by_ISBN();
                       if(strcmp(x.ISBN,"")==0){
                         printf("Not found\n");
                      }
                  else
                      printf("%s, %s, %s, %s, %d/%d/%d, %d, %d, %s\n",x.title,
                                                        x.author,
                                                        x.publisher,
                                                        x.ISBN,
                                                        x.pub.day,
                                                        x.pub.month,
                                                        x.pub.year,
                                                        x.no_of_copies,
                                                        x.current_no,
                                                        x.category);
                 }
                 else if (y==4){

                     char key3[50] ;
                     printf("Enter book's Category or part of it\n");
                     gets(key3);
                     gets(key3);
                   printf("Books found: \n");
                 search_books_by_cat(key3);

             }
      }
             else if(x=='c' || x=='C'){
                 add_new_copy();
             printf("adding copies: DONE");
             save =0;
             }
             else if(x=='d' || x=='D'){
                 removeBook();
             save = 0;
             }
             else if(x=='s'|| x=='S'){
                 main_menu();
             }
             }

           else if(a==2){
               printf("\t\t\t A-ADD A NEW USER\n");
               printf("\t\t\t B-REMOVE A MEMBER\n");
               printf("for main menu press s\n");

               scanf("%c",&x);
               scanf("%c",&x);
               while(x != 'A' && x!= 'a' && x!= 'b' && x!='B'  && x!='s' && x!='S'){
                 printf("Error invalid option please choose again\n");
                 printf("\t\t\t A-ADD A NEW USER\n");
                 printf("\t\t\t B-REMOVE A MEMBER\n");
                 printf("for main menu press s\n");

                 scanf("%c",&x);
                 scanf("%c",&x);
               }


               if(x=='a'|| x=='A'){
                   add_new_member();
                   main_menu();
               save=0;

               }
               else if(x=='b'|| x=='B'){
                   removeMember();
                          save =0;

               }

               else if(x=='s' || x=='S'){
                   main_menu();
               }
             }

          else if(a==3){
            printf("\t\t\t A-Borrow a book\n");
            printf("\t\t\t B-Return a book\n");
            printf("for main menu press s\n");

            scanf("%c",&x);
            scanf("%c",&x);
            while(x != 'A' && x!= 'a' && x!= 'b' && x!='B'  && x!='s' && x!='S'){
              printf("Error invalid option please choose again\n");
              printf("\t\t\t A-Borrow a book\n");
              printf("\t\t\t B-Return a book\n");
              printf("for main menu press s\n");

              scanf("%c",&x);
              scanf("%c",&x);
            }


            if(x=='a'|| x=='A'){
                printf("\t\t\t1-Search by title\n");
                 printf("\t\t\t2-Search by author\n");
                 printf("\t\t\t3-Search by ISBN\n");
                 printf("\t\t\t4-Search by category\n");
                 scanf("%d",&y);
                 if(y<1||y>4){
                     printf("invalid option Please enter number between 1 and 4\n");
                     printf("\t\t\t1-Search by title\n");
                 printf("\t\t\t2-Search by author\n");
                 printf("\t\t\t3-Search by ISBN\n");
                 printf("\t\t\t4-Search by category\n");
                 scanf("%d",&y);
                 }
                 if(y==1){
                     char key1[50];
                     printf("Enter book's name or part of it\n");
                     gets(key1);
                     gets(key1);
                     printf("Books found: \n");
                     search_books_by_name(key1);
                 }
                 else if(y==2){
                     char key2[50];
                     printf("Enter author's name or part of it\n");
                     gets(key2);
                     gets(key2);
                     printf("Books found: \n");
                     search_books_by_author(key2);
                 }
                 else if (y==3){
                     book x;
                        x=search_by_ISBN();
                       if(strcmp(x.ISBN,"")==0){
                         printf("Not found\n");
                      }
                  else
                      printf("%s, %s, %s, %s, %d/%d/%d, %d, %d, %s\n",x.title,
                                                        x.author,
                                                        x.publisher,
                                                        x.ISBN,
                                                        x.pub.day,
                                                        x.pub.month,
                                                        x.pub.year,
                                                        x.no_of_copies,
                                                        x.current_no,
                                                        x.category);
                 }
                 else if (y==4){
                     char key3[50] ;
                     printf("Enter book's Category or part of it\n");
                     gets(key3);
                     gets(key3);
                    printf("Books found: \n");
            search_books_by_cat(key3);

             }

                    int m,b;
                printf("\n\n");
                printf("All Books: \n");
                print_books(books_array,books);
                printf("Choose book to borrow from all books:\n");
                scanf("%d",&b);
                printf("\n\n");
                print_members();
                printf("Choose member number:\n");
                scanf("%d",&m);
                Borrowing(books_array[b],members_array[m]);

            printf("borrow book done\n");
            save =0;
            }

            else if(x=='b'|| x=='B'){
                    int b;
                         print_borrowed();
                         printf("Which entry do you wish to return?\n");
                         scanf("%d",&b);
                         Returned(borrowed_array[b]);
                         save = 0;

              }

            else if(x=='s' || x=='S'){
                main_menu();
             }


      }
           else if(a==4){
             printf("\t\t\t A-LIST OF OVERDUE BOOKS\n");
             printf("\t\t\t B-LIST OF MOST POPULAR BOOKS\n");
             printf("for main menu press s\n");
             scanf("%c",&x);
             scanf("%c",&x);
             while(x != 'A' && x!= 'a' && x!= 'b' && x!='B'  && x!='s' && x!='S'){
               printf("\t\t\t A-LIST OF OVERDUE BOOKS\n");
               printf("\t\t\t B-LIST OF MOST POPULAR BOOKS\n");
               printf("for main menu press s\n");
               scanf("%c",&x);
               scanf("%c",&x);
             }
             if(x=='a'){
                 overdue();
             }
             else if(x=='b'){
                 popular_books();
             }
             else if(x=='s'){
                 main_menu();
             }
           }

           else if(a == 5){
             print_members();
             main_menu();
           }

           else if(a == 6){
             print_books(books_array, books);
             main_menu();
           }

           else if (a == 7){
             print_borrowed();
             main_menu();
           }

           else if(a == 8){
             save_changes();
               printf("saving chages....\n DONE");
             save = 1;
             main_menu();

           }

           else if(a == 9){
             if(save == 0){
               printf("Are you sure you want to exit without saving??\n 1- yes   2- save and quit\n");
               int c;
               scanf("%d",&c);
               while(c>2 || c< 1){
                 printf("Are you sure you want to exit without saving??\n 1- yes   2- save and quit\n");
                 scanf("%d",&c);
               }
               if(c == 1){
                 exit(1);

               }
               else if(c==2){
                   save_changes();
                 printf("save done\n");
                 exit(1);
               }
             }
             else if(save==1){
                 exit(1);
             }
           }
    }

}

#endif // LIBRARY_FUNCTIONS_H_INCLUDED
