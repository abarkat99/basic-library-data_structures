#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct book
{
    char name[30];
    char a_name[35];
    int isbn;
    int amount;
    int borrowed;
    struct book *left, *right;
}book;
typedef struct student
{
    char name[35];
    char uname[15];
    char pass[15];
    char contact[11];
    int rollno;
    struct borrows *bor;
    struct student *left, *right;
}student;
typedef struct libuser
{
    char name[35];
    char uname[15];
    char pass[15];
}libuser;
libuser librar;
struct borrows
{
    student *s;
    book *b;
    struct date
    {
        int day;
        int month;
        int year;
    }issue,due;
    struct borrows *next;
};
int libexist=0;
FILE *fp;
void Linterface(book **broot, student **sroot, struct borrows **bor_head);
void Sinterface(book **broot, student **sroot);
void insertbook(book **broot);
void insertstudent(student **sroot);
void deletebook(book **broot);
void deletestudent(student **sroot);
void display_book(book *b);
void display_student(student *s);
void display_allbooks(book *broot);
void editbook(book *broot);
void issue_book(book *broot, student *sroot,struct borrows **bor_head);
void reclaim_book(struct borrows **bor_head);
void display_borrows(struct borrows *bor_head);
book* search_book(int isbn, book *broot);
student* search_student(int rollno, student *sroot);
void display_allstudents(student *sroot);
void editstudent(student *sroot);
void book_table(book *broot);
void init(student **sroot, book **broot,struct borrows **bor_head);
void close(student *sroot,book *broot, struct borrows *bor_head);
void write_student(student *sroot);
void write_book(book *broot);
void write_borrows(struct borrows *bor_head);
student* read_student();
book* read_book();
struct borrows* read_borrows(student *sroot, book *broot);
student* student_login(student *sroot,char uname[],char pass[]);

int main()
{
    int c=0;
    book *broot=NULL;
    student *sroot=NULL;
    struct borrows *bor_head=NULL;
    init(&sroot,&broot,&bor_head);
    do
    {
        if(c!=0)
        {
            printf("Press Enter to continue..");
            getchar();
            system("cls");
        }
        printf("Menu:-\n1. Login as Librarian\n2. Login as Student\n3. Exit\n");
        printf("Please enter your choice: ");
        scanf("%d",&c);
        getchar();  //To deal with input buffer
        switch (c)
        {
        case 1:
            Linterface(&broot,&sroot,&bor_head);
            break;
        case 2:
            Sinterface(&broot,&sroot);
        case 3:
            break;
        default:
            printf("Invalid choice try again\n");
        }
    }while(c!=3);
    close(sroot,broot,bor_head);
    return 0;
}

void Linterface(book **broot, student **sroot,struct borrows **bor_head)
{
    char uname[15],pass[15];
    int c=0;
    int rollno;
    int isbn;
    book *sbook;
    student *sstudent;
    system("cls");
    if(libexist==0)
    {
        printf("No Librarian found, please create an account\n");
        printf("Enter your name: ");
        scanf("%[^\n]",librar.name);
        printf("Enter your user name: ");
        scanf("%s",librar.uname);
        printf("Enter your password: ");
        scanf("%s",librar.pass);
        libexist=1;
        system("cls");
    }
    printf("Login as Librarian:-\nEnter your user name: ");
    scanf("%s",uname);
    printf("Enter your password: ");
    scanf("%s",pass);
    if(strcmp(uname,librar.uname)!=0||strcmp(pass,librar.pass)!=0)
    {
        printf("Invalid user name or password\n");
        return;
    }
    system("cls");
    printf("Welcome %s\n",librar.name);
    do
    {
        if(c!=0)
        {
            printf("Press Enter to continue..");
            getchar();
            system("cls");
        }
        printf("Main Menu\n");
        printf("1. Add a book\n2. Delete a book\n3. Search for a book\n4. Display all books\n");
        printf("5. Edit a books details\n6. Issue a book\n7. Reclaim a book\n");
        printf("8. Browse all issues\n9. Add a student\n10. Delete a student\n11. Search for a student\n");
        printf("12. Display all students\n13. Edit a students details\n14. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d",&c);
        getchar(); //Input buffer
        system("cls");
        switch (c)
        {
            case 1:
                insertbook(broot);
                break;
            case 2:
                deletebook(broot);
                break;
            case 3:
                if(*broot==NULL)
                {
                    printf("No books found\n");
                    break;
                }
                printf("-------------------------------------------------\n");
                printf("|  ISBN No.    |  Book Name                     |\n");
                printf("-------------------------------------------------\n");
                book_table(*broot);
                printf("ISBN of Required Book: ");
                scanf("%d",&isbn);
                getchar(); //Input Buffer
                sbook=search_book(isbn, *broot);
                if(sbook==NULL)
                    printf("Book Not found\n");
                else
                    display_book(sbook);
                break;
            case 4:
                if(*broot!=NULL)
                {
                    printf("Books are:-\n\n");
                    display_allbooks(*broot);
                }
                else
                    printf("No books to display\n");
                break;
            case 5:
                if(*broot!=NULL)
                    editbook(*broot);
                else
                    printf("No books found\n");
                break;
            case 6:
                if(*broot==NULL)
                {
                    printf("No books found\n");
                    break;
                }
                issue_book(*broot,*sroot,bor_head);
                break;
            case 7:
                reclaim_book(bor_head);
                break;
            case 8:
                display_borrows(*bor_head);
                break;
            case 9:
                insertstudent(sroot);
                break;
            case 10:
                deletestudent(sroot);
                break;
            case 11:
                printf("Roll Number of Required Student: ");
                scanf("%d",&rollno);
                getchar(); //Input Buffer
                sstudent=search_student(rollno,*sroot);
                if(sstudent==NULL)
                    printf("Student not found\n");
                else
                    display_student(sstudent);
                break;
            case 12:
                if(*sroot!=NULL)
                {
                    printf("Students are:-\n\n");
                    display_allstudents(*sroot);
                }
                else
                    printf("No students to display\n");
                break;
            case 13:
                editstudent(*sroot);
                break;
            case 14:
                break;
            default:
                printf("Invalid choice, try again\n");
        }
    }while(c!=14);
}

void Sinterface(book **broot, student **sroot)
{
    int c=0;
    int isbn;
    student *s1;
    book *sbook;
    char uname[15],pass[15];
    system("cls");
    printf("Login as Student\nEnter your Username: ");
    scanf("%s",uname);
    printf("Enter your Password: ");
    scanf("%s",pass);
    s1=student_login(*sroot,uname,pass);
    if(s1==NULL)
    {
        printf("Invalid Username or Password\n");
        return;
    }
    system("cls");
    printf("Welcome %s\n",s1->name);
    do
    {
        if(c!=0)
        {
            printf("Press Enter to continue..");
            getchar();
            system("cls");
        }
        printf("Main Menu\n");
        printf("1. Display Profile\n2. Change Password\n3. Search for a book\n");
        printf("4. Browse Books\n5. Log Out\n");
        printf("Enter your choice: ");
        scanf("%d",&c);
        getchar(); //Input Buffer
        system("cls");
        switch (c)
        {
        case 1:
            display_student(s1);
            break;
        case 2:
            printf("Enter new Password: ");
            scanf("%s",s1->pass);
            printf("Password changed\nLogin again to continue\n");
            return;
            break;
        case 3:
            if(*broot==NULL)
                {
                    printf("No books found\n");
                    break;
                }
            printf("-------------------------------------------------\n");
            printf("|  ISBN No.    |  Book Name                     |\n");
            printf("-------------------------------------------------\n");
            book_table(*broot);
            printf("ISBN of Required Book: ");
            scanf("%d",&isbn);
            getchar(); //Input Buffer
            sbook=search_book(isbn, *broot);
            if(sbook==NULL)
                printf("Book not found\n");
            else
                display_book(sbook);
            break;
        case 4:
            if(*broot!=NULL)
            {
                printf("Books are:-\n\n");
                display_allbooks(*broot);
            }
            else
                printf("No books to display\n");
            break;
        case 5:
            break;
        default:
            printf("Invalid Choice, try again\n");
            break;
        }
    }while(c!=5);
}

void insertbook(book **broot)
{
    book *ptr,*prev,*p;
    ptr=(book *)malloc(sizeof(book));
    printf("Enter details to insert book\n");
    printf("Book Name: ");
    scanf("%[^\n]",ptr->name);
    getchar(); //INput Buffer
    printf("Author Name: ");
    scanf("%[^\n]",ptr->a_name);
    printf("ISBN: ");
    scanf("%d",&(ptr->isbn));
    getchar(); //Input Buffer
    printf("Availability: ");
    scanf("%d",&(ptr->amount));
    getchar(); //Input Buffer
    ptr->borrowed=0;
    ptr->left=ptr->right=NULL;
    p=*broot;
    prev=NULL;
    while(p!=NULL)
    {
        prev=p;
        if((ptr->isbn)<(p->isbn))
            p=p->left;
        else
            p=p->right;
    }
    if(prev==NULL)
        *broot=ptr;
    else
    {
        if((ptr->isbn)<(prev->isbn))
            prev->left=ptr;
        else
            prev->right=ptr;
    }
}

void insertstudent(student **sroot)
{
    student *ptr,*prev,*p;
    ptr=(student *)malloc(sizeof(student));
    printf("Enter details to insert student\n");
    printf("Student Name: ");
    scanf("%[^\n]",ptr->name);
    printf("User Name: ");
    scanf("%s",ptr->uname);
    printf("Password: ");
    scanf("%s",ptr->pass);
    printf("Contact Number: ");
    scanf("%s",ptr->contact);
    printf("Roll No: ");
    scanf("%d",&(ptr->rollno));
    getchar(); //Input Buffer
    ptr->left=ptr->right=NULL;
    ptr->bor=NULL;
    p=*sroot;
    prev=NULL;
    while(p!=NULL)
    {
        prev=p;
        if((ptr->rollno)<(p->rollno))
            p=p->left;
        else
            p=p->right;
    }
    if(prev==NULL)
        *sroot=ptr;
    else
    {
        if((ptr->rollno)<(prev->rollno))
            prev->left=ptr;
        else
            prev->right=ptr;
    }
}

void deletebook(book **broot)
{
    int isbn;
    char c;
    book *parent,*del,*delparent=NULL,*rp;
    if(*broot==NULL)
    {
        printf("No Books found\n");
        return;
    }
    printf("-------------------------------------------------\n");
    printf("|  ISBN No.    |  Book Name                     |\n");
    printf("-------------------------------------------------\n");
    book_table(*broot);
    printf("Enter ISBN of book to delete: ");
    scanf("%d",&isbn);
    getchar(); //Input Buffer
    del=*broot;
    while(del!=NULL&&del->isbn!=isbn)
    {
        delparent=del;
        if(isbn<del->isbn)
            del=del->left;
        else
            del=del->right;
    }
    if(del==NULL)
    {
        printf("Book not found\n");
        return;
    }
    printf("Book found:-\n");
    display_book(del);
    printf("Do you really want to delete this book\nEnter y for yes n for no: ");
    scanf("%c",&c);
    getchar(); //Input Buffer
    if(c!='y'&&c!='Y')
        return;
    if(del->left==NULL)
        rp=del->right;
    else if(del->right==NULL)
        rp=del->left;
    else
    {
        parent=del;
        rp=del->right;
        while(rp->left!=NULL)
        {
            parent=rp;
            rp=rp->left;
        }
        if(parent!=del)
        {
            parent->left=rp->right;
            rp->right=del->right;
        }
        rp->left=del->left;
    }
    if(delparent==NULL)
        *broot=rp;
    else if(delparent->left==del)
        delparent->left=rp;
    else
        delparent->right=rp;
    free(del);
    printf("Book Deleted\n");
}

void deletestudent(student **sroot)
{
    int rollno;
    char c;
    student *parent,*del,*delparent=NULL,*rp;
    if(*sroot==NULL)
    {
        printf("No Students found\n");
        return;
    }
    printf("Enter Roll Number of student to delete: ");
    scanf("%d",&rollno);
    getchar(); //Input Buffer
    del=*sroot;
    while(del!=NULL&&del->rollno!=rollno)
    {
        delparent=del;
        if(rollno<del->rollno)
            del=del->left;
        else
            del=del->right;
    }
    if(del==NULL)
    {
        printf("Student not found\n");
        return;
    }
    printf("Student found:-\n");
    display_student(del);
    if(del->bor!=NULL)
    {
        printf("%s has yet to return a book please reclaim it first.\n",del->name);
        return;
    }
    printf("Do you really want to delete the records of %s?\n",del->name);
    printf("Enter y for yes n for no: ");
    scanf("%c",&c);
    getchar(); //Input Buffer
    if(c!='y'&&c!='Y')
        return;
    if(del->left==NULL)
        rp=del->right;
    else if(del->right==NULL)
        rp=del->left;
    else
    {
        parent=del;
        rp=del->right;
        while(rp->left!=NULL)
        {
            parent=rp;
            rp=rp->left;
        }
        if(parent!=del)
        {
            parent->left=rp->right;
            rp->right=del->right;
        }
        rp->left=del->left;
    }
    if(delparent==NULL)
        *sroot=rp;
    else if(delparent->left==del)
        delparent->left=rp;
    else
        delparent->right=rp;
    free(del);
    printf("Student Deleted\n");
}

void display_book(book *b)
{
    printf("Book Name: %s\n",b->name);
    printf("Author Name: %s\n",b->a_name);
    printf("ISBN: %d\n",b->isbn);
    printf("Quantity held by Library: %d\n",b->amount);
    printf("Quantity Borrowed by members: %d\n",b->borrowed);
}

void display_student(student *s)
{
    printf("Student Name: %s\n",s->name);
    printf("Roll Number: %d\n",s->rollno);
    printf("Contact Number: %s\n",s->contact);
    if(s->bor!=NULL)
    {
        printf("Borrowed Book:-\n");
        display_book(s->bor->b);
        printf("Issue Date: %d/%d/%d\n",s->bor->issue.day,s->bor->issue.month,s->bor->issue.year);
        printf("Due Date: %d/%d/%d\n",s->bor->due.day,s->bor->due.month,s->bor->due.year);
    }
}

void display_allbooks(book *broot)
{
    if(broot!=NULL)
    {
        display_allbooks(broot->left);
        display_book(broot);
        printf("\n\n");
        display_allbooks(broot->right);
    }
}

void editbook(book *broot)
{
    int isbn,c,qty;
    printf("-------------------------------------------------\n");
    printf("|  ISBN No.    |  Book Name                     |\n");
    printf("-------------------------------------------------\n");
    book_table(broot);
    printf("Enter ISBN of book to edit: ");
    scanf("%d",&isbn);
    getchar(); //Input Buffer
    while(broot!=NULL&&broot->isbn!=isbn)
    {
        if(isbn<broot->isbn)
            broot=broot->left;
        else
            broot=broot->right;
    }
    if(broot==NULL)
    {
        printf("Book not found\n");
        return;
    }
    display_book(broot);
    do
    {
        printf("Options:-\n");
        printf("1. Change Book Name\n2. Change Author Name\n");
        printf("3. Change Quantity held by library\n4. Finish Editing\n");
        printf("Enter your choice: ");
        scanf("%d",&c);
        getchar(); //Input Buffer
        switch (c)
        {
        case 1:
            printf("New Book Name: ");
            scanf("%[^\n]",broot->name);
            break;
        case 2:
            printf("New Author Name: ");
            scanf("%[^\n]",broot->a_name);
            break;
        case 3:
            printf("New quantity held by library: ");
            scanf("%d",&qty);
            getchar();
            if(qty<broot->borrowed)
                printf("Please reclaim the required amount of books to decrease the amount\n");
            else
                broot->amount=qty;
            break;
        case 4:
            break;
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    }while(c!=4);
}

void issue_book(book *broot, student *sroot,struct borrows **bor_head)
{
    int rollno,isbn;
    struct borrows *ptr,*prev,*p;
    printf("Roll Number of Borrower: ");
    scanf("%d",&rollno);
    getchar(); //Input Buffer
    while(sroot!=NULL&&sroot->rollno!=rollno)
    {
        if(rollno<sroot->rollno)
            sroot=sroot->left;
        else
            sroot=sroot->right;
    }
    if(sroot==NULL)
    {
        printf("Student Not found\n");
        return;
    }
    printf("Student Found:-\n");
    display_student(sroot);
    if(sroot->bor!=NULL)
    {
        printf("%s has yet to return a book, please reclaim it first\n",sroot->name);
        return;
    }
    printf("-------------------------------------------------\n");
    printf("|  ISBN No.    |  Book Name                     |\n");
    printf("-------------------------------------------------\n");
    book_table(broot);
    printf("ISBN of book to issue: ");
    scanf("%d",&isbn);
    getchar(); //Input Buffer
    while(broot!=NULL&&broot->isbn!=isbn)
    {
        if(isbn<broot->isbn)
            broot=broot->left;
        else
            broot=broot->right;
    }
    if(broot==NULL)
    {
        printf("Book not found\n");
        return;
    }
    printf("Book found:-\n");
    display_book(broot);
    if(broot->amount<=broot->borrowed)
    {
        printf("Not enough copies of book to issue\n");
        return;
    }
    ptr=(struct borrows*)malloc(sizeof(struct borrows));
    ptr->s=sroot;
    ptr->b=broot;
    sroot->bor=ptr;
    broot->borrowed=(broot->borrowed)+1;
    printf("Enter issue date as follows, DD MM YYYY: ");
    scanf("%d%d%d", &(ptr->issue.day),&(ptr->issue.month),&(ptr->issue.year));
    getchar(); //Input Buffer
    printf("Enter due date as follows, DD MM YYYY: ");
    scanf("%d%d%d", &(ptr->due.day),&(ptr->due.month),&(ptr->due.year));
    getchar(); //Input Buffer
    ptr->next=NULL;
    p=*bor_head;
    prev=NULL;
    while(p!=NULL)
    {
        prev=p;
        p=p->next;
    }
    if(prev==NULL)
        *bor_head=ptr;
    else
        prev->next=ptr;
}

void reclaim_book(struct borrows **bor_head)
{
    int rollno;
    struct borrows *reclaim,*prev;
    if(*bor_head==NULL)
    {
        printf("No books to reclaim\n");
        return;
    }
    printf("Roll Number of Borrower: ");
    scanf("%d",&rollno);
    getchar(); //Input Buffer
    reclaim=*bor_head;
    while(reclaim!=NULL&&reclaim->s->rollno!=rollno)
    {
        prev=reclaim;
        reclaim=reclaim->next;
    }
    if(reclaim==NULL)
    {
        printf("Found no Student with Roll Number %d having borrowed any book\n",rollno);
        return;
    }
    printf("Student Found:-\n");
    display_student(reclaim->s);
    reclaim->b->borrowed=(reclaim->b->borrowed)-1;
    if(reclaim==*bor_head)
        *bor_head=(*bor_head)->next;
    else
        prev->next=reclaim->next;
    reclaim->s->bor=NULL;
    free(reclaim);
    printf("Reclaimed Book\n");
}

void display_borrows(struct borrows *bor_head)
{
    if(bor_head==NULL)
    {
        printf("No books have been issued\n");
        return;
    }
    printf("Details of Borrows:-\n\n");
    while(bor_head!=NULL)
    {
        display_student(bor_head->s);
        printf("\n\n");
        bor_head=bor_head->next;
    }
}

book* search_book(int isbn, book *broot)
{
    while(broot!=NULL&&isbn!=broot->isbn)
    {
        if(isbn<broot->isbn)
            broot=broot->left;
        else
            broot=broot->right;
    }
    return broot;
}

student* search_student(int rollno, student *sroot)
{
    while(sroot!=NULL&&rollno!=sroot->rollno)
    {
        if(rollno<sroot->rollno)
            sroot=sroot->left;
        else
            sroot=sroot->right;
    }
    return sroot;
}

void display_allstudents(student *sroot)
{
    if(sroot!=NULL)
    {
        display_allstudents(sroot->left);
        display_student(sroot);
        printf("\n\n");
        display_allstudents(sroot->right);
    }
}

void editstudent(student *sroot)
{
    int rollno,c;
    printf("Enter Roll No of student to edit: ");
    scanf("%d",&rollno);
    getchar(); //Input Buffer
    while(sroot!=NULL&&sroot->rollno!=rollno)
    {
        if(rollno<sroot->rollno)
            sroot=sroot->left;
        else
            sroot=sroot->right;
    }
    if(sroot==NULL)
    {
        printf("Student not found\n");
        return;
    }
    display_student(sroot);
    do
    {
        printf("Options:-\n");
        printf("1. Change Student Name\n2. Change User Name\n");
        printf("3. Change Password\n4. Change Contact Number\n5. Finish editing\n");
        printf("Enter your choice: ");
        scanf("%d",&c);
        getchar(); //Input Buffer
        switch (c)
        {
        case 1:
            printf("Changed Student Name: ");
            scanf("%[^\n]",sroot->name);
            break;
        case 2:
            printf("Changed User Name: ");
            scanf("%s",sroot->uname);
            break;
        case 3:
            printf("Changed Password: ");
            scanf("%s",sroot->pass);
            break;
        case 4:
            printf("Changed Contact Number: ");
            scanf("%s",sroot->contact);
            break;
        case 5:
            break;
        default:
            printf("Invalid choice, please try again\n");
            break;
        }
    }while(c!=5);
}

student* student_login(student *sroot,char uname[],char pass[])
{
    student *temp=NULL;
    if(sroot==NULL)
        return NULL;
    if((strcmp(uname,sroot->uname)==0)&&(strcmp(pass,sroot->pass)==0))
        return sroot;
    else
    {
        temp=student_login(sroot->left,uname,pass);
        if(temp==NULL)
            temp=student_login(sroot->right,uname,pass);
    }
    return temp;
}

void book_table(book *broot)
{
    if(broot->left!=NULL)
        book_table(broot->left);
    printf("|  %-12d|  %-30s|\n",broot->isbn,broot->name);
    printf("-------------------------------------------------\n");
    if(broot->right!=NULL)
        book_table(broot->right);
}

void init(student **sroot, book **broot,struct borrows **bor_head)
{
    fp=NULL;
    int i=0;
    fp=fopen("./librar.bin","rb");
    if(fp==NULL)
    {
        fp=fopen("./librar.bin","wb");
        fwrite(&libexist,sizeof(int),1,fp);
        fclose(fp);
        fp=fopen("./librar.bin","rb");
    }
    fread(&libexist,sizeof(int),1,fp);
    if(libexist==1)
        fread(&librar,sizeof(libuser),1,fp);
    fclose(fp);
    fp=fopen("./students.bin","rb");
    i=0;
    if(fp==NULL)
    {
        fp=fopen("./students.bin","wb");
        fwrite(&i,sizeof(int),1,fp);
        fclose(fp);
        fp=fopen("./students.bin","rb");
    }
    fread(&i,sizeof(int),1,fp);
    if(i==1)
        *sroot=read_student();
    fclose(fp);
    fp=fopen("./books.bin","rb");
    i=0;
    if(fp==NULL)
    {
        fp=fopen("./books.bin","wb");
        fwrite(&i,sizeof(int),1,fp);
        fclose(fp);
        fp=fopen("./books.bin","rb");
    }
    fread(&i,sizeof(int),1,fp);
    if(i==1)
        *broot=read_book();
    fclose(fp);
    fp=fopen("./borrows.bin","rb");
    i=0;
    if(fp==NULL)
    {
        fp=fopen("./borrows.bin","wb");
        fwrite(&i,sizeof(int),1,fp);
        fclose(fp);
        fp=fopen("./borrows.bin","rb");
    }
    fread(&i,sizeof(int),1,fp);
    if(i==1)
        *bor_head=read_borrows(*sroot,*broot);
    fclose(fp);
}

void close(student *sroot,book *broot, struct borrows *bor_head)
{
    fp=NULL;
    int i=0;
    fp=fopen("./librar.bin","wb");
    if(fp==NULL)
        printf("Something went wrong\n");
    else
    {
        fwrite(&libexist,sizeof(int),1,fp);
        if(libexist==1)
            fwrite(&librar,sizeof(libuser),1,fp);
        fclose(fp);
    }
    fp=fopen("./students.bin","wb");
    if(fp==NULL)
        printf("Something went wrong\n");
    else
    {
        if(sroot!=NULL)
            i=1;
        fwrite(&i,sizeof(int),1,fp);
        if(sroot!=NULL)
            write_student(sroot);
        i=0;
        fclose(fp);
    }
    fp=fopen("./books.bin","wb");
    if(fp==NULL)
        printf("Something went wrong\n");
    else
    {
        if(broot!=NULL)
            i=1;
        fwrite(&i,sizeof(int),1,fp);
        if(broot!=NULL)
            write_book(broot);
        i=0;
        fclose(fp);
    }
    fp=fopen("./borrows.bin","wb");
    if(fp==NULL)
        printf("Something went wrong\n");
    else
    {
        if(bor_head!=NULL)
            i=1;
        fwrite(&i,sizeof(int),1,fp);
        if(bor_head!=NULL)
            write_borrows(bor_head);
        i=0;
        fclose(fp);
    }
}

void write_student(student *sroot)
{
    fwrite(sroot,sizeof(student),1,fp);
    if(sroot->left!=NULL)
        write_student(sroot->left);
    if(sroot->right!=NULL)
        write_student(sroot->right);
}

void write_book(book *broot)
{
    fwrite(broot,sizeof(book),1,fp);
    if(broot->left!=NULL)
        write_book(broot->left);
    if(broot->right!=NULL)
        write_book(broot->right);
}

void write_borrows(struct borrows *bor_head)
{
    fwrite(&(bor_head->s->rollno),sizeof(int),1,fp);
    fwrite(&(bor_head->b->isbn),sizeof(int),1,fp);
    fwrite(&(bor_head->issue),sizeof(bor_head->issue),1,fp);
    fwrite(&(bor_head->due),sizeof(bor_head->due),1,fp);
    fwrite(&(bor_head->next),sizeof(bor_head->next),1,fp);
    if(bor_head->next!=NULL)
        write_borrows(bor_head->next);
}

student* read_student()
{
    student *sroot;
    sroot=(student *)malloc(sizeof(student));
    fread(sroot,sizeof(student),1,fp);
    if(sroot->left!=NULL)
        sroot->left=read_student();
    if(sroot->right!=NULL)
        sroot->right=read_student();
    return sroot;
}

book* read_book()
{
    book *broot;
    broot=(book *)malloc(sizeof(book));
    fread(broot,sizeof(book),1,fp);
    if(broot->left!=NULL)
        broot->left=read_book();
    if(broot->right!=NULL)
        broot->right=read_book();
    return broot;
}

struct borrows* read_borrows(student *sroot, book *broot)
{
    int rollno,isbn;
    struct borrows *bor_head;
    bor_head=(struct borrows*)malloc(sizeof(struct borrows));
    fread(&rollno,sizeof(int),1,fp);
    bor_head->s=search_student(rollno,sroot);
    bor_head->s->bor=bor_head;
    fread(&isbn,sizeof(int),1,fp);
    bor_head->b=search_book(isbn,broot);
    fread(&(bor_head->issue),sizeof(bor_head->issue),1,fp);
    fread(&(bor_head->due),sizeof(bor_head->due),1,fp);
    fread(&(bor_head->next),sizeof(bor_head->next),1,fp);
    if(bor_head->next!=NULL)
    {
        bor_head->next=read_borrows(sroot, broot);
    }
    return bor_head;
}
