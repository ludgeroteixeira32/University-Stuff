#include "hashtable.h"

hashtable *hash_table;

item_repository *item_rpst;
item_repository *item_rpst_find;

item_repository *create_item_repository(){
    item_repository * rpst = malloc(sizeof(item_repository));
    rpst->head = NULL;
    rpst->size = 0;
    return rpst;
}

item_rpst_node *create_item_repository_node(item *item){
    item_rpst_node *item_rpst_local = malloc(sizeof(item_rpst_node));
    item_rpst_local->itm = item;
    item_rpst_local->next = NULL;
    return item_rpst_local;
}

void insert_repository(item_repository *rpst , item *item){

    if (rpst->head == NULL){
        rpst->head = create_item_repository_node(item);
        rpst->size++;
        return;
    }

    item_rpst_node *temp = rpst->head;
    while(temp->next != NULL)
        temp = temp->next;
    
    temp->next = create_item_repository_node(item);
    rpst->size++;
    return;
}

void print_item_repository(item_repository *rpst){
    int count = 0;

    item_rpst_node *item_rpst_local = rpst->head;

    while(item_rpst_local != NULL){

        if(strcmp(item_rpst_local->itm->name , "END") == 0){
            count--;
        }

        for (int i = 0 ; i < count ; i++){
            printf(" ");
        }

        printf("%s\n" , item_rpst_local->itm->name);

        if(strcmp(item_rpst_local->itm->name , "START") == 0){
            count++;
        }

        item_rpst_local = item_rpst_local->next;
        
    }

}

unsigned int hash_function(unsigned char *str, int size){
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash % size;
}

hashtable *create_table(int size){
    hashtable * hashtable_local = malloc(sizeof(hashtable));
    hashtable_local->items = malloc(sizeof(item) * size);
    hashtable_local->size = size;
    for ( int i = 0 ; i < size ; i++){
        hashtable_local->items[i] = NULL;
    }
    return hashtable_local;
}

void free_hashtable(hashtable *hashtable){
    for ( int i = 0 ; i < hashtable->size ; i++){
        if (hashtable->items[i] == NULL){
            free(hashtable->items[i]);
        }
        
    }

    free(hashtable);
}

item *create_item( char *value){
    item *item_local = malloc(sizeof(item));
    item_local->name = strdup(value);
    item_local->instantiated = false;

    return item_local;
}

bool is_prime(int n){

    if (n <= 1)  return false;
    if (n <= 3)  return true;
   
    if (n%2 == 0 || n%3 == 0) return false;
   
    for (int i=5; i*i<=n; i=i+6)
        if (n%i == 0 || n%(i+2) == 0)
           return false;
    return true;
}

int next_prime(int n){

    if (n <= 1)
        return 2;
 
    int prime = n * 2;
    bool found = false;
 
    while (!found) {
        prime++;
 
        if (is_prime(prime))
            found = true;
    }

    return prime;
}



hashtable *rehash(hashtable * hash_table){
    int prime = next_prime(hash_table->size);

    hashtable * newhashtable  = create_table(prime);

    for(int i = 0 ; i < hash_table->size ; i++){
        if(hash_table->items[i] != NULL){
            int key = hash_function(hash_table->items[i]->name , newhashtable->size);
            insert_value(&newhashtable , hash_table->items[i] , key);
        }
    }

    free_hashtable(hash_table);
    return newhashtable;

}

item *insert_value(hashtable ** hashtable , item *item , int key){
        
    if((*hashtable)->items[key] == NULL){
        item->id = key;
        (*hashtable)->items[key] = item;
        (*hashtable)->count++;
        return (*hashtable)->items[key];
    }else{
        if (strcmp((*hashtable)->items[key]->name , item->name ) == 0){
            return (*hashtable)->items[key];
        }
        while((*hashtable)->items[key] != NULL){
            (*hashtable) = rehash((*hashtable));
            key = hash_function(item->name , (*hashtable)->size);
        }
        item->id = key;
        (*hashtable)->items[key] = item;
        return (*hashtable)->items[key];

    }

}

void print_hashtable(hashtable * hashtable ){
    for(int i = 0 ; i < hashtable->size ; i++){
        if(hashtable->items[i] != NULL){
            printf("%s %d %s %d\n" , hashtable->items[i]->name , hashtable->items[i]->id , hashtable->items[i]->value.string , hashtable->items[i]->instantiated );
        }else{
            printf("NULL\n");
        }
    }

}

/*int main(){
    hashtable *hash_table1 = create_table(11);
    int key = hash_function("x" , hash_table1->size);
    item *item = create_item("x");
    insert_value(&hash_table1 , item , key);
    print_hashtable(hash_table1);
    key = hash_function("b" , hash_table1->size);
    item = create_item("b");
    insert_value(&hash_table1 , item , key);
    print_hashtable(hash_table1);
}*/
