#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define MAX 100

typedef struct btnode{
    int value;
    int power;
    struct btnode *left;
    struct btnode *right;
}btnode;

typedef struct stack{
    int items[MAX];
    int top;
}stack;

btnode *root;

int main(){
    int M, N, k, p, value, flag=1;
    int i,j;
    int *arr;
    btnode *tmp;
    stack s1;
    stack s2;

    void initialize(stack *s);
    void insert(int);
    btnode* createNode();
    void shoot(stack *, int k, int p);
    int pop(stack *);
    int push(int , stack *);
    void printBTree(btnode* root, int depth);

    
    
    srand(time(NULL));
    printf("Lutfen M degerini giriniz: ");
    scanf("%d", &M);

    printf("Lutfen N degerini giriniz: ");
    scanf("%d", &N);

    arr = (int*)malloc(M*sizeof(int));    
    for(i=0;i<M;i++){          //agaca aktarilacak degerlerin rastgele ve tekrarlamayacak sekilde seçilmesi
        
        value = rand() % N + 1;
        
        if (i==0){
            arr[i] = value;
        }else{
            
            flag = 1;
            while(flag==1){
                
                flag = 0;
                j=0;
                while((flag==0)&&(j<i)){
                    if(value == arr[j]){
                        value = rand() % N + 1;
                        
                        flag = 1;
                        j=0;
                    }
                    j++;   
                }
            }
            arr[j] = value;
        }
        printf("arr[%d]:%d ", i, arr[i]);  
    }

    for(i=0;i<M;i++){       //Secilen degerlerin agaca düzgğn bir sekilde teker eteker yerlestirilmesi
        insert(arr[i]);
        printf("\n");
    }
    
    printf("\n");
    tmp = root;
    printBTree(tmp, 0);
    initialize(&s1);

    while(root!=NULL){     //Atıs islemlerini teker teker kullanıcıdan istenip gerceklenmesi

        printf("\nMeyve degeri k 'yi giriniz: ");
        scanf("%d", &k);

        printf("\nAtisin gucu p 'yi giriniz: ");
        scanf("%d", &p);

        shoot(&s1, k, p);
        printf("\n");
        tmp = root;
        printBTree(tmp, 0);
    }

    for(i=0;i<M;i++){       // Ciktiyi uygun sekle getirmek için teker teker düsen elemanların bi stackten pop edilip digerine aktarilmasi
        push(pop(&s1),&s2);
    }
    printf("\n\n");
    for(i=0;i<M;i++){
        printf("%d ", pop(&s2));
    }

    return 0;
}

void initialize(stack *s){
    s->top = 0; 
}

int isEmpty(stack *s){
    if(s->top==0){
        return 1;
    }else{
        return 0;
    }
}

int isFull(stack *s){
    if(s->top == MAX){
        return 1;
    }else{
        return 0;
    }
}

int push(int value, stack *s){
    if(isFull(s)){
        printf("stack is full\n");
        return 0;
    }else{
        s->items[s->top] = value;
        s->top++;
        return 1;
    }
}

int pop(stack *s){
    int value;
    if(isEmpty(s)){
        printf("Stack is empty");
        exit(-16);
    }else{
        s->top--;
        value = s->items[s->top];  
        return value;
    }
}

btnode* createNode(){
    btnode *ptr;
    ptr = (btnode*)malloc(sizeof(btnode));
    if(ptr == NULL){
        printf("allocation error");
        exit(-16);
    }
    return ptr;
}

void printBTree(btnode* root, int depth) {
    if(root == NULL) {
        return;
    }
    depth += 4;
    printBTree(root->right, depth);
    printf("\n");
    int i;
    for(i = 4; i < depth; i++) {
        printf("| ");
    }
    printf("%d(%d)\n", root->value, root->power);
    printBTree(root->left, depth);
}

void insert(int value){
    int flag;
    btnode *curr;
    btnode *parent;
    btnode *newNode = createNode(); 

    newNode->value = value;
    newNode->power = value;
    newNode->left = NULL;
    newNode->right = NULL;
    
    if(root == NULL){
        root = newNode;
        
    }else{
        curr = root;
        flag = 0;
        while(flag==0){
            
            if(value > curr->value){
                
                parent = curr;
                curr = curr->right;
                if(curr == NULL){
                    parent->right = newNode;
                    flag = 1;
                }
            }else{
                
                parent = curr;
                curr = curr->left;

                if(curr == NULL){
                    parent->left = newNode;
                    flag = 1;
                }
            }
        }
    }

}

void shoot(stack *s, int k, int p){
    int isLeft;
    int flag =0;
    btnode *curr;
    btnode *tmp;
    btnode *parent;

    curr = root;
    parent = root;

    while((curr != NULL)&&(curr->value != k)){
        if(k < curr->value){
            parent = curr;
            curr = curr->left;
            isLeft = 1;

        }else{
            parent = curr;
            curr = curr->right;
            isLeft = 0;
        }
    }
    if(curr==NULL){
        printf("Sectiginiz deger agacta yok!");
        return;
    }else{
        printf("\nDegerin eski power degeri: %d", curr->power);
    }
    
    curr->power = curr->power - p;
    printf("\nDegerin yeni power degeri: %d", curr->power);

    if(curr->power <= 0){

        push(curr->value, s);  //agactan dusen degerin stacke aktarılması

        if((curr->left != NULL)&&(curr->right != NULL)){   //degerin iki tane cocugu olması durumu
            tmp = curr;
            parent = tmp;
            tmp = tmp->right;
            isLeft = 0;
            
            while(tmp->left != NULL){
                isLeft = 1;
                parent = tmp;
                tmp = tmp->left;
                
            }
            curr->value = tmp->value;
            curr->power = tmp->power;
            

            if(tmp->right != NULL){
                if(isLeft){
                    parent->left = tmp->right;
                }else{
                    parent->right = tmp->right;
                }
                
            }else{
                if(isLeft){
                    parent->left = NULL;
                }else{
                    parent->right = NULL;
                }
                
            }

            tmp = NULL;
            free(tmp);


        }else{
            if((curr->left!=NULL) || (curr->right!=NULL)){     //degerin bir tane cocugu olması durumu
                if(curr->left!= NULL){
                    
                    if(parent == curr){
                        root = curr->left;
                    }else{
                        if(isLeft){
                            parent->left = curr->left;
                        }else{
                            parent->right = curr->left;
                        }
                    }
                    
                }else{
                    
                    if(parent == curr){
                        root = curr->right;
                    }else{
                        if(isLeft){
                            parent->left = curr->right;
                        }else{
                            parent->right = curr->right;
                        }
                    }
                }
                curr = NULL;
                free(curr);
            }else{    //degerin yaprak ya da root olmasi durumu
                
                if(parent == curr){
                    root = NULL;
                }else{
                    if(isLeft){
                        parent->left = NULL;
                    }else{
                        parent->right = NULL;
                    }
                    curr = NULL;
                    free(curr);
                    
                    
                }
                
            }
            
        }
    }

    return;
    
}