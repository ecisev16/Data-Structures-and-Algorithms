#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include <stdbool.h>

typedef struct node{
    int value;
    int is_last_letter;
    char word[30];
    struct node **children;
    int childCount;
}node;

typedef struct wNode{
    char word[30];
    int number[30];
    struct wNode* next;

}wNode;

node* createNode(int );
node* addChild(node* , int , char* , int );
wNode* createWNode();
void addNode(wNode** , char* , int* );
void printList(wNode** );
void readFile(wNode** );
void insert(node* , int* , char* , int );
void insertTree(node **root, wNode** wRoot);
void searchTree(node **, char* );

int main(){

    node* root = createNode(0);
    wNode* wRoot = NULL;
    readFile(&wRoot);
    
    insertTree(&root,&wRoot);

    char sayi[30];

    printf("\n\ndeğer giriniz: ");
    gets(sayi);
    printf("\n");
    searchTree(&root, sayi);

    while(sayi[0] != 'q'){
        printf("\ndeğer giriniz: ");
        gets(sayi);
        printf("\n");
        searchTree(&root, sayi);
        
    }
    
    return 0;
}

node* createNode(int value){
    node* newNode = (node*)malloc(sizeof(node));
    
    newNode->value = value;
    newNode->is_last_letter = 0;
    newNode->children = NULL;
    newNode->childCount = 0;

    return newNode;
}

node* addChild(node* parent, int value, char* word, int boole){
    node* child = createNode(value);
    node* curr;
    node* curr2;
    int i=0,k, flag=0;

    if(boole == 1){  //eklenecek node keimenin son karakteri mi?

        child->is_last_letter = 1;     // son karakteri olduğu bilgisi
        strcpy(child->word, word);     // kelimeyi bu nota atıyor.

        while((i<parent->childCount)&&(child->value != parent->children[i]->value)){
            i++;
        }  //aynı sayı diziminde başka kelime var mı? Bunun araması.

        if(i<parent->childCount){ // varsa...
            k=0;
            while((k<parent->children[i]->childCount) && (0 != parent->children[i]->children[k]->value)){
                k++;
            } //aynı sayı diziminde birden fazla kelime var mı yok mu bulmak için
            if(k<parent->children[i]->childCount){ // varsa...
                curr2 = parent->children[i];
                while((curr2->childCount!=0)&&(flag != 1)){ // '0' ların en altına gidip yerleşme
                    if(curr2->children[0]->value == 0){
                        curr2 = curr2->children[0];
                    }else{
                        flag=1;
                    }
                
                }
                curr = addChild(curr2, 0, word, 1);
            }else{
                curr = addChild(parent->children[i], 0, word, 1); //direkt ekleme
            }
            
            return curr;
        }

    }
    
    parent->childCount++;
    parent->children = (node**) realloc(parent->children, parent->childCount * sizeof(node*));
    parent->children[parent->childCount-1] = child; // child'ı yerleştirme
    return parent->children[parent->childCount-1];
      
}

wNode* createWNode(){
    wNode* newNode = (wNode*)malloc(sizeof(wNode));

    if(newNode == NULL){
        printf("allocation error");
        exit(-16);
    }
   
    return newNode;
}

void addNode(wNode** head, char* word, int* number) {
    // Yeni düğümü oluştur
    int length, i=0;
    wNode* newNode = createWNode();
    strcpy(newNode->word, word);
    while(number[i] != -1){
        newNode->number[i] = number[i];
        i++;
    }
    newNode->number[i] = number[i];
    newNode->next = NULL;

    // Eğer liste boşsa, yeni düğümü başa ekle
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Liste boş değilse, son düğüme kadar ilerle
    wNode* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }

    // Yeni düğümü sona ekle
    current->next = newNode;
}

void printList(wNode** wRoot){
    wNode *tmp = *wRoot;
    int length, i=0;

    while(tmp != NULL){
        printf("\n%s    ", tmp->word);
        i=0;
        while(tmp->number[i] != -1){
            printf("%d", tmp->number[i]);
            i++;
        }
        tmp = tmp->next;

    }
}

void readFile(wNode** wRoot){
    int i, x;
    FILE *fp;
    char line[100];
    wNode *tmp = createWNode();

    fp = fopen("Sozluk.txt","r");
    if (fp == NULL) {
        printf("Dosya açma hatasi!\n");
        exit(-16);
    }

    while(!feof(fp)){
        
        fscanf(fp, "%s", tmp->word);
        i=0;

        while(tmp->word[i] != '\0'){

            if (tmp->word[i] == '#') {
                x = 0;
            } else if (tmp->word[i] == 'a' || tmp->word[i] == 'b' || tmp->word[i] == 'c') {
                x = 2;
            } else if (tmp->word[i] == 'd' || tmp->word[i] == 'e' || tmp->word[i] == 'f') {
                x = 3;
            } else if (tmp->word[i] == 'g' || tmp->word[i] == 'h' || tmp->word[i] == 'i') {
                x = 4;
            } else if (tmp->word[i] == 'j' || tmp->word[i] == 'k' || tmp->word[i] == 'l') {
                x = 5;
            } else if (tmp->word[i] == 'm' || tmp->word[i] == 'n' || tmp->word[i] == 'o') {
                x = 6;
            } else if (tmp->word[i] == 'p' || tmp->word[i] == 'q' || tmp->word[i] == 'r' || tmp->word[i] == 's') {
                x = 7;
            } else if (tmp->word[i] == 't' || tmp->word[i] == 'u' || tmp->word[i] == 'v') {
                x = 8;
            } else if (tmp->word[i] == 'w' || tmp->word[i] == 'x' ||tmp-> word[i] == 'y' || tmp->word[i] == 'z') {
                x = 9;
            } else {
                x = 1;
            }
            
            i++;
            tmp->number[i-1] = x;

        }
        tmp->number[i] = -1;
        addNode(wRoot, tmp->word, tmp->number);
        
        
    }
    fclose(fp);
    printList(wRoot);
}

void insert(node* curr, int* number, char* word, int indis){
    int i, flag=0;
    node* parent ;

    if(number[indis] == -1){  //sayı dizisinin sonundaysa reqursive'den çıkma 
        return;
    }else{
        i = 0;
        while ((i < curr->childCount)&&(number[indis] != curr->children[i]->value)){ //ilgili basamaktan var mı
            i++;
        }

        if(i == curr->childCount){ //kendiyle aynı bulamadı ağaca yeni düğüm eklicek
            if(number[indis+1] == -1){  //son harfin bilsini tutan basmak
                parent = addChild(curr, number[indis], word, 1);
            }else{ //son harf değil
                parent = addChild(curr, number[indis], word, 0);
            }
            indis++;
            insert(parent, number, word, indis);
        }else{//kendiyle aynı harfi buldu
            if(number[indis+1] == -1){
                parent = addChild(curr, number[indis], word, 1); //son harfteyse her türlü eklenmesi gerektiği için
            }
            indis++;
            insert(curr->children[i], number, word, indis);
        }
    }


}

void insertTree(node **root, wNode** wRoot){
    void printTree(node*, int);

    wNode *tmp = *wRoot;
    node *curr = *root;
    while(tmp != NULL){
        insert(*root, tmp->number, tmp->word, 0);
        tmp = tmp->next;

    }
}

void searchTree(node **root, char* sayi){
    node *tmp = *root;
    node *curr2;
    int i, j, k, flag=0, flag2=0;

    i=0;
    while((i<strlen(sayi)) && (flag!=1)){ //sayının bütün basamaklarını tek tek dolaşmak
        int num = sayi[i] - '0';

        j=0;
        while((j<tmp->childCount) &&(tmp->children[j]->value != num)){ //ilgili indise valuesine eşit bir trie nodu var mı?
            j++;
        }
        if(j == tmp->childCount){ // o seviyede eşleşen yoksa diğerlerine bakmamak için
            flag = 1;
            printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
        }else{ // bulunduysa bir ağaçta bir alt seviyeye geçmek için
            if(i != strlen(sayi)-1){
                tmp = tmp->children[j];
            }
            
        }
        i++;
    }

    if(flag == 1){ // kelime yok
        return;
    }else if(tmp->children[j]->is_last_letter==1){ // kelime var
        printf("%s\n", tmp->children[j]->word);

        k=0;
        while((k < tmp->children[j]->childCount)&&(tmp->children[j]->children[k]->value != 0)){ 
            k++;
        }//aynı sayı koduna sahip başka kelime var mı?

        if(k < tmp->children[j]->childCount){ // var
            tmp = tmp->children[j];

            while((tmp->childCount!=0)&&(flag != 1)){ // birden fazla varsa onları da yazdırma
                    if(tmp->children[0]->value == 0){
                        
                        tmp = tmp->children[0];
                        printf("%s\n", tmp->word);
                    }else{
                        flag=1;
                    }
                
                }
        }
    }else{
        printf("Sozlukte bu sayinin karsiligi bir kelime yoktur.\n");
    }

    return;
}
