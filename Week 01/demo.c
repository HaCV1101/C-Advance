#include <stdio.h>
#include <stdlib.h>
void menu(){
    printf("\n\n\n\n\t\t\t===========MeNu===============\n");
    printf("\t\t\t+%4s1.Nhap de tra tu.%6s +\n"," ", " ");
    printf("\t\t\t+%4s2.Thoat chuong trinh.%2s +\n"," "," ");
    printf("\t\t\t==============================\n");
    printf("...........Lua chon cua ban: ");

}
void menu1(){
    printf("\n\n\n\n\t\t\t===========MENU================\n");
    printf("\t\t\t+%4s1.Xoa khoi tu dien.%5s +\n"," ", " ");
    printf("\t\t\t+%4s2.Update nghia cua tu.%3s+\n"," ", " ");
    printf("\t\t\t+%4s3.Quay lai.%13s +\n"," "," ");
    printf("\t\t\t===============================\n");
    printf("...........Lua chon cua ban: ");

}
void menu2(){
    printf("\n\n\n\n\t\t\t===========MENU================\n");
    printf("\t\t\t+%4s1.Them vao tu dien.%5s +\n"," ", " ");
    printf("\t\t\t+%4s2.Quay lai.%13s +\n"," "," ");
    printf("\t\t\t===============================\n");
    printf("...........Lua chon cua ban: ");

}


int main()
{
    int scan, chon1, chon2;
    int t=0;
    do
    {
        menu();
        scanf("%d",&scan);
        switch(scan)
        {
            case 1: 
                if(t == 1)
                {
                    printf("Tim thay tu\n");
                    do
                    {
                        menu1();
                        scanf("%d",&chon1);
                        switch(chon1)
                        {
                            case 1: 
                                printf("Xoa o day.\n");
                                break;
                            case 2:
                                printf("Update o day.\n");
                                break;
                            case 3:
                                printf("\t\t\tCam on!\n");
                                break;
                        }
     
                    }while(chon1 != 3);  
                }else
                {
                    printf("Khong tim thay tu\n");
                    do
                    {
                        menu2();
                        scanf("%d",&chon2);
                        switch(chon2)
                        {
                            case 1: 
                                printf("Them vao o day\n");
                                
                                break;
                                return 1;
                            case 2:
                                printf("\t\t\tCam on!\n");
                                break;
                        }
     
                    }while(chon2 != 2);  

                }

                break;
            case 2:
                printf("\t\t\tCam on ban da su dung phan mem!\n");
                break;
        }
     
    }while(scan != 2);  


    return 0;    
}