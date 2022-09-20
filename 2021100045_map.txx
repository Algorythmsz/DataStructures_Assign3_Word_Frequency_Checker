/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2022. 5. 1
  *
  */
  //2021100045 자유전공학부 컴퓨터학과 박승원

// destructor
template <class HashMapElemType>
HashMap<HashMapElemType>::~HashMap() 
{
HashMapElemType* del_hash;
HashMapElemType* hash_check;    //traversing the hash map
for(int i = 0; i < capacity; i++)
    {
        if(ht[i] != NULL)
        {
            hash_check = ht[i];
            while(hash_check != NULL)
            {
                del_hash = hash_check;  //temporarily saving the value at the del_hash
                remove(del_hash->key);
                hash_check = hash_check->link;
            }
        }
    }
delete[] ht;   //because it is two dimension array, we have to delete it twice.
}

template <class HashMapElemType>
HashMapElemType* 
HashMap<HashMapElemType>::find(const KeyType k) 
{
    if(isEmpty())
        return NULL;
    else
    {
        int hash_key = hashfunction(k);
        HashMapElemType* hash_check = ht[hash_key];
        if(ht[hash_key] == NULL)
            return NULL;
        else
        {
            while(hash_check != NULL)
            {
                if(hash_check->key == k)
                    return hash_check;
                hash_check = hash_check->link;
            }
            return NULL;
        }
    }
}
	
template <class HashMapElemType>
void 
HashMap<HashMapElemType>::insert(const KeyType k, const ValType v) 
{
    HashMapElemType* hash_temp;
    int hash_key = hashfunction(k);
    
    if(ht[hash_key] == NULL){   //when ht[hash_key] is empty, just insert at the ht.
        ht[hash_key] = new HashMapElemType;
        ht[hash_key]->key = k;
        ht[hash_key]->val = v;
        ht[hash_key]->link = NULL;
        mapsize++;
        }
    else{
            HashMapElemType* trav = ht[hash_key];
            if(find(k) != NULL) //if same key already exitsts then replace it.
                find(k)->val = v;
            else
            {
            hash_temp = new HashMapElemType;
            hash_temp->val = v;
            hash_temp->key = k;
            hash_temp->link = NULL;
            while(trav->link != NULL){trav = trav->link;}
            trav->link = hash_temp;
            mapsize++;
        }
        }
}

    
		
template <class HashMapElemType>
bool 
HashMap<HashMapElemType>::remove(const KeyType k) 
{
    int hash_key = hashfunction(k);
    HashMapElemType* hash_check;
    HashMapElemType* prev_hash; //we need prev pointer because we need to link it the next one before we remove the one.
    HashMapElemType* hash_temp;
    if(isEmpty())
        return false;
    else
    {
        if(ht[hash_key] == NULL)
            return false;
        else
        {
            if(ht[hash_key] == find(k)){   //when the first slot is the finding one
            hash_temp = ht[hash_key]->link;  //save the next one
            delete ht[hash_key];
            ht[hash_key] = hash_temp;    //resaving with the preserved one
            mapsize--;
            return true;
            }
            else
            {
                hash_check = ht[hash_key];
                    while(hash_check != NULL)
                    {
                        prev_hash = hash_check;
                        hash_check = hash_check->link;
                        if(hash_check->key == k)
                        {
                            prev_hash->link = hash_check->link;
                            delete hash_check;
                            mapsize--;
                            return true;
                        }
                    }
                return false;
            }
        }
    }
}
	
template <class HashMapElemType>
unsigned int 
HashMap<HashMapElemType>::hashfunction(const KeyType k)
{
    int hash_val;
    unsigned int h = 0;
    int key_size = k.size();    //you can use k.length() instead.
    for(int i = 0; i < key_size; i++){ //cyclic shift hash function
        h = (h << 5) | (h >> 27);   //5 bit
        h += (unsigned int) k[i];
    }
    hash_val = h % divisor;
    return hash_val;
}

template <class HashMapElemType>
void 
HashMap<HashMapElemType>::print()   //use signly linked list to print the sorted hash map key & values
{
    HashMapElemType* trav;
    HashMapElemType* sorted[size()];
    HashMapElemType* iter;
    HashMapElemType* new_node;
    
    if(isEmpty())
        std::cout << "(This map is empty.)" << std::endl;

    else
    {
        for(int k = 0; k < size(); k++)
            sorted[k] = NULL;
        for(int i = 0; i < capacity; i++)
        {
            for(trav = ht[i]; trav != NULL; trav = trav->link)
            {
                new_node = new HashMapElemType;
                new_node->key = trav->key;
                new_node->val = trav->val;
                if(sorted[0] == NULL || trav->val > sorted[0]->val)
                {
                    new_node->link = sorted[0];
                    sorted[0] = new_node;
                }
                else
                {
                    iter = sorted[0];
                    while(iter->link != NULL && iter->link->val > new_node->val)
                    iter = iter->link;
                    new_node->link = iter->link;
                    iter->link = new_node;
                }
            }
        }
        for(iter = sorted[0]; iter != NULL; iter = iter->link)
        std::cout << iter->key << " : " << iter->val << std::endl;
    }
}
