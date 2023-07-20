#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct node{
    int value;
    struct node *next;
    struct node *prev;
}node;

int main(){
    int N=0, M;
    int ortak;
    int n;
    int i;
    int yer, yer2, yer3;
    int ikinci, ucuncu;

    node* createNode();
    void insertEnd(node**, int, int);
    void insertEnd2(node **, node **, node **, int , int);
    void printLists(node**);
    void printLists2(node **);
    int ortakSayiYerlestirme(node **, int , int);
    int ortakSayiveYeri(node **, node **, node **);
    int hangiYoneKacTur(int, int, int);
    node* carkCevirmeİslemi(node **, int , int);

    node *head = NULL;
    node *head2 = NULL;
    node *head3 = NULL;
    
    node *tmp;
    srand(time(NULL));

    printf("Lutfen M degerini giriniz: ");
    scanf("%d", &M);

    n = ((M-1)*3) / 2;
    if((((M-1)*3) % 2) == 1){
        n++;
    }

    while(N <= n){
        printf("\nLutfen N degerini %d degerin esit ya da buyuk olacak sekilde giriniz: ", n+1);
        scanf("%d", &N);
    }

    ortak = rand() % N + 1;
    //printf("\n%d  %d  %d", M, N, ortak);

    for(i=0;i<M-1;i++){
        
        insertEnd(&head, N, ortak);    
    }

    for(i=0;i<M-1;i++){
        
        insertEnd(&head2, N, ortak);    
    }

    for(i=0;i<M-1;i++){
        
        insertEnd2(&head, &head2, &head3, N, ortak);
    }

    yer = ortakSayiYerlestirme(&head, ortak, M);
    yer2 = ortakSayiYerlestirme(&head2, ortak, M);
    yer3 = ortakSayiYerlestirme(&head3, ortak, M);

    printf("\n");
    printf("Birinci cark : ");
    printLists(&head);
    printf("İkinci cark : ");
    printLists(&head2);
    printf("İkinci cark : ");
    printLists(&head3);
    

    ortakSayiveYeri(&head, &head2, &head3);
    printf("\nSayi negatif degerli ise ters yönde cevrilir, pozitif degerli ise saat yönünde cevrilir.\n");
    printf("\nbirinci ile ikinci cark arasindaki ");
    ikinci = hangiYoneKacTur(yer, yer2, M);
    printf("\nbirinci ile ucuncu cark arasindaki ");
    ucuncu = hangiYoneKacTur(yer, yer3, M);

    
    head2 = carkCevirmeİslemi(&head2, yer2, ikinci);
    head3 = carkCevirmeİslemi(&head3, yer3, ucuncu);

    printf("\n");
    printf("Birinci cark : ");
    printLists(&head);
    printf("İkinci cark : ");
    printLists2(&head2);
    printf("İkinci cark : ");
    printLists2(&head3);

    return 0;
}

void printLists(node **head){
    node *tmp = *head;
    
    while(tmp != NULL){
        printf("%d  ", tmp->value);
        tmp = tmp->next;
        
    }
    printf("\n");
}

void printLists2(node **head){
    node *tmp = *head;
    node *tut = *head;
    while(tmp->next != tut){
        printf("%d  ", tmp->value);
        tmp = tmp->next;
        
    }
    printf("%d", tmp->value);
    printf("\n");
}

node* createNode(){
    
    node *ptr;
    ptr = (node*)malloc(sizeof(node));
    if(ptr == NULL){
        printf("Allocation error\n");
        exit(-16);
    }
    return ptr;
}

void insertEnd(node **head, int N, int ortak){
    int flag = 1;
    int value;
    node *tmp;
    node *prev;
    node *newNode = createNode();

    value = rand() % N + 1;
    //printf("    rand sayi: %d", value);
    while(value == ortak){
        value = rand() % N + 1;
        //printf("    iç rand sayi: %d", value);
    }

    if(*head == NULL){
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
        *head = newNode;
        
    }else{
    

    while(flag == 1){
        
        tmp = *head;
        flag = 0;
        while((tmp!=NULL)&&(flag==0)){
            if((tmp->value == value) || (ortak == value)){
                
                value = rand() % N + 1;
                //printf("icicic rand sayi = %d", value);
                flag = 1;
            }
            
            //printf("\nvalue of tmp = %d", tmp->value);
            tmp = tmp->next;
            
        }
        //printf("        flag=%d", flag);
        
    }

    node *curr = *head;
    
    while(curr->next!=NULL){
        prev = curr;
        curr = curr->next;
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = curr;
    curr->next = newNode;
    
    }
    

    
    return;
}

void insertEnd2(node **head, node **head2, node **head3, int N, int ortak){
    int flag = 1;
    int value;
    node *tmp;
    node *tmp2;
    node *tmp3;
    node *prev;
    node *newNode = createNode();
  
    value = rand() % N + 1;
    //printf("    rand sayi: %d", value);
    while(value == ortak){
        value = rand() % N + 1;
        //printf("    iç rand sayi: %d", value);
    }

    while(flag == 1){
        
        tmp = *head;
        
        tmp3 = *head3;
        flag = 0;
        while((tmp3!=NULL)&&(flag==0)){
            if((tmp3->value == value) || (ortak == value)){
                
                value = rand() % N + 1;
                //printf("icicic rand sayi = %d", value);
                flag = 1;
            }
            
            
            //printf("\nvalue of tmp = %d", tmp->value);
            tmp3 = tmp3->next;
            
        }
        //printf("        flag1=%d", flag);
        while((tmp!=NULL)&&(flag==0)){
            if(tmp->value==value){
                tmp2 = *head2;
                while((tmp2!=NULL)&&(flag==0)){
                    if(tmp2->value == value){
                        value = rand() % N + 1;
                        //printf("icicic rand sayi = %d", value);
                        flag = 1;
                    }
                    tmp2 = tmp2->next;
                }
            }
            tmp = tmp->next;
        }
        //printf("        flag2=%d", flag);

        if((*head3 == NULL) && (value == ortak)){
            flag = 1;
        }
        
    }

    if(*head3 == NULL){
        newNode->value = value;
        newNode->next = NULL;
        newNode->prev = NULL;
        *head3 = newNode;
        
    }else{
    node *curr = *head3;
    while(curr->next!=NULL){
        curr = curr->next;
    }
    newNode->value = value;
    newNode->next = NULL;
    newNode->prev = curr;
    curr->next = newNode;
    
    }
    

    
    return;
}

int ortakSayiYerlestirme(node **head, int ortak, int M){
    int yer = rand() % M;
    int i;
    node *newNode = createNode();
    node *curr = *head;
    node *prev = NULL;

    if(yer==0){
        newNode->value = ortak;
        newNode->next = curr;
        *head = newNode;
    }else{

        for(i=0;i<yer;i++){
            prev = curr;
            curr = curr->next;
        }
        newNode->value = ortak;
        prev->next = newNode;
        newNode->next = curr;
    }

    return yer;
}

int ortakSayiveYeri(node **head, node **head2, node **head3){
    node *tmp = *head;
    node *tmp2 = *head2;
    node *tmp3 = *head3;
    int i=0, i2=0, i3=0;
    int flag = 0;

    while((tmp!=NULL)&&(flag==0)){
        i++;
        i2 = 0;
        tmp2 = *head2;
        while((tmp2!=NULL)&&(flag==0)){
            i2++;
            i3 = 0;
            tmp3 = *head3;
            if(tmp->value == tmp2->value){
                while((tmp3!=NULL)&&(flag==0)){
                    i3++;
                    if(tmp->value == tmp3->value){
                        flag = 1;
                        printf("\nOrtak deger = %d", tmp->value);
                    }
                    tmp3 = tmp3->next;
                }
            }
            tmp2 = tmp2->next;
        }
        tmp = tmp->next;
    }

    printf("\nBirinci carktaki yeri = %d\tİkinci carktaki yeri = %d\tUcuncu carktaki yeri=%d\n", i, i2, i3);
}

int hangiYoneKacTur(int yer, int yer2, int M){
    int sayi, sayi2, sayi3, sayi4, mesafe, mesafe2, x;
    
    sayi = yer - yer2;
    if(sayi<=0){
        x = yer + M;
        sayi2 = x - yer2;
        
    }else if(sayi>0){
        x = yer2 + M;
        sayi2 = yer - x;
        
    }
    
    if(abs(sayi) <= abs(sayi2)){

        printf("mesafe    =   %d", sayi);
        return sayi;
    }else if(abs(sayi2) < abs(sayi)){
        printf("mesafe    =   %d", sayi2);
        return sayi2;
    }

}

node* carkCevirmeİslemi(node **head, int yer, int nereye){
    int i;
    node *curr = *head;
    node *tut = *head;
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = tut;
    tut->prev = curr;
    
    node *curr2 = *head;
    if(nereye == 0){
        return curr2;
    }
    if(nereye<0){
        for(i=0;i<abs(nereye);i++){
            curr2 = curr2->next;
        }
        return curr2;
    }
    if(nereye>0){
        for(i=0;i<abs(nereye);i++){
            curr2 = curr2->prev;
        }
        return curr2;
    }

}
