#include <iostream>
#include <iomanip>
using namespace std;

template<typename Key, typename Info>
class Dictionary{

    struct Element{

        int Balance;
        Key key;
        Info info;

        Element *left;
        Element *right;
        Element(const Key &newKey, const Info &newInfo):key(newKey), info(newInfo), Balance(0), left(NULL), right(NULL), parent(NULL){};
        Element *parent;
    };

    Element *root;

void add_element(Element* &elem, const Key &key, const Info &info){

        if(elem == NULL){

            elem = new Element(key, info);
            set_balance(root);
            set_parent(root);

        }else if(key < elem->key)
            add_element(elem->left, key, info);
        else if(key > elem->key)
            add_element(elem->right, key, info);
        else
            cout << "Key " << key << " must be Unique" << endl;
}

void set_parent(Element *elem){

        if(elem == root){

            elem->parent = root;
        }

        if (elem != NULL){

            set_parent(elem->right);

            if(elem->left){

                Element *elem2 = elem->left;
                elem2->parent = elem;
            }

            if(elem->right){

                Element *elem3 = elem->right;
                elem3->parent = elem;
            }

            if(elem->left == NULL && elem->right == NULL)
                return;
            set_parent(elem->left);
        }

        else

            return;
}

int set_balance(Element *const & elem){

        if(elem == NULL)
            return 0;

        int left_height = set_balance(elem->left);
        int right_height = set_balance(elem->right);
        elem->Balance = difference(elem);

        if(elem->Balance == -2 && (elem->right->Balance == -1 || elem->right->Balance == 0)){
            left_rotation(elem);
            return set_balance(elem);
        }
        if(elem->Balance == 2 && elem->left->Balance == -1){
            left_rotation(elem->left);
            right_rotation(elem);
            return set_balance(elem);
        }
        if(elem->Balance == 2 && (elem->left->Balance == 1 || elem->left->Balance == 0)){
            right_rotation(elem);
            return set_balance(elem);
        }
        if(elem->Balance == -2 && elem->right->Balance == 1){
            right_rotation(elem->right);
            left_rotation(elem);
            return set_balance(elem);
        }
        if(height(elem->left) < height(elem->right))
            return (height(elem->right) + 1);
        return height(elem->left) + 1;
    }

int difference(Element* elem){return (height(elem->left) - height(elem->right));}

int height(Element *elem){

        int height2 = 0;
        if(elem != NULL){

            int left_height = height(elem->left);
            int right_height = height(elem->right);
            int maxHeight = 0;

            if(left_height < right_height)
                maxHeight = right_height;
            else
                maxHeight = left_height;
            height2 = maxHeight + 1;
        }

    return height2;
}

void right_rotation(Element* elem){

        if(elem == root){

            root = elem->left;
            elem->left = elem->left->right;
            root->right = elem;
            return;
        }

        Element *previous = root;

        while((previous->right != elem) && (previous->left != elem)){

           if(elem->key < previous->key)
              previous = previous->left;
           else if (elem->key > previous->key)
              previous = previous->right;
        }

        if(previous->right == elem)
            previous->right = elem->left;
        if(previous->left == elem)
            previous->left = elem->left;

        Element *temp = elem->left->right;
        elem->left->right = elem;
        elem->left = temp;
    }

void left_rotation(Element* elem){

        if(elem == root){

            root = elem->right;
            elem->right = elem->right->left;
            root->left = elem;
            return;
        }

        Element *previous = root;
        while((previous->right != elem) && (previous->left != elem))
        {
            if(elem->key < previous->key)
                previous = previous->left;
            else if (elem->key > previous->key)
                previous = previous->right;
        }

        if(previous->right == elem)
            previous->right = elem->right;
        if(previous->left == elem)
            previous->left = elem->right;
        Element *temp = elem->right->left;
        elem->right->left = elem;
        elem->right = temp;
}

Element *copy(Element* &left_hand_side, Element* const &right_hand_side){

        if(right_hand_side == NULL)
            return NULL;

        left_hand_side = new Element(right_hand_side->key, right_hand_side->info);
        left_hand_side->left = copy(left_hand_side->left, right_hand_side->left);
        left_hand_side->right = copy(left_hand_side->right, right_hand_side->right);

        return left_hand_side;
}

void clear_tree(Element* &elem){

        if(elem == NULL)
            return;

        clear_tree(elem->left);
        clear_tree(elem->right);
        delete elem;
}

void print(Element* const & elem, int space) const{

        if (elem != NULL){

            print(elem->right, space+10);
            cout << setw(space) << " " << elem->key << " " << elem->info << " " << elem->Balance;
            print(elem->left, space+10);

        }else
            cout << setw(space) << " " <<  endl;
}

public:

Dictionary();
~Dictionary();

friend ostream &operator << (ostream &o, const Dictionary<Key, Info> &Dictionary){

    Dictionary.print();
    return o;
};

Dictionary(const Dictionary<Key, Info> &Dictionary);
Dictionary<Key, Info> &operator= (const Dictionary<Key, Info> &Dictionary);
bool operator == (const Dictionary<Key, Info> &Dictionary);
bool operator != (const Dictionary<Key, Info> &Dictionary);
bool isEmpty()const {return (root == NULL);};
void add_element(const Key &key, const Info &info) {add_element(root, key, info);};
void remove_element(const Key &key);
void clear_tree() {clear_tree(root); root = NULL;};
void print() const {print(root, 0);};
bool does_exist(const Key &key) const;
bool compare(Element* const &left_hand_side, Element* const & right_hand_side);
Info findInfo(const Key &key) const;

class Iterator{

        Element *iter;

public:

    Iterator(){

        iter = NULL;
    }

    Iterator(Element* copyElement){

        iter = copyElement;
    }

    ~Iterator(){}

    Iterator(const Iterator &copyIter){

        iter = copyIter.iter;
    }

    Iterator operator= (const Iterator &copyIter){

        iter = copyIter.iter;
        return *this;
    }

    bool operator== (const Iterator &compare)const{

        return iter == compare.iter;
    }

    bool operator!= (const Iterator &compare)const{

        return iter!= compare.iter;
    }

    Iterator operator+ (int number){

        Iterator new_iter = *this;

           if(iter)

                for(int i = 0; i < number; i++)
                    new_iter++;
            return new_iter;
    }

    Iterator operator- (int number){

        Iterator new_iter = *this;
        if(iter)
            for(int i = 0; i < number; i++)
                new_iter--;
        return new_iter;
    }

    const Iterator operator++ (int){

        if(!iter)
            return *this;

        else{

            Element *elem;
            Iterator *temp = new Iterator(iter);

            if(iter == NULL){

                while(iter->left != NULL){

						iter = iter->left;
                }
            }else if(iter->right != NULL){

                iter = iter->right;
                while(iter->left != NULL){

                    iter = iter->left;
				}
            }else{

                elem = iter->parent;

                while(elem != NULL && iter == elem->right){

						iter = elem;
						elem = elem->parent;
					}
                iter = elem;
            }

    return *temp;
    }
}

    const Iterator operator-- (int){

            if(!iter)
                return *this;

			else{

				Element *elem;
				Iterator *temp = new Iterator(iter);
				if(iter == NULL){

					while(iter->right != NULL){

						iter = iter->right;
					}

				}else if(iter->left != NULL){

					iter = iter->left;

					while(iter->right != NULL){

						iter = iter->right;
					}

				}else{

					elem = iter->parent;

					while(elem != NULL && iter == elem->left){

						iter = elem;
						elem = elem->parent;
					}

					iter = elem;
            }

    return *temp;
    }
}

    Key getKey(){

        if(!this->isNULL())
            return iter->key;
        cerr << "iterator does not point at any element" << endl;
    }

    Info getInfo(){

        if(!this->isNULL())
            return iter->info;
        cerr << "iterator does not point at any element" << endl;
    }

    bool isNULL(){

        if(iter)
            return false;
        return true;
    }
};

Iterator begin(){

    Element *current = root;

    if (current != NULL)

			while (current->left != NULL)
				current = current->left;

    return Iterator(current);
}

Iterator end(){

        Element *current = root;

		if (current != NULL)

			while (current->right != NULL)
				current = current->right;
		return Iterator(current);
	}
};

template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(){

    root = NULL;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::~Dictionary(){

    if(root)
        clear_tree(root);
    root = NULL;
    cout<<"Tree deleted"<< endl;
}

template<typename Key, typename Info>
Dictionary<Key, Info>::Dictionary(const Dictionary<Key, Info> &Dictionary){

    root = copy(Dictionary.root);
}

template<typename Key, typename Info>
Dictionary<Key, Info>&Dictionary<Key, Info>::operator= (const Dictionary<Key, Info> &Dictionary){

    if(root == Dictionary.root)
        return *this;

    this->~Dictionary();
    if(Dictionary.root == NULL)
        return *this;

    root = copy(root, Dictionary.root);
    set_balance(root);
    set_parent(root);
    return *this;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::operator == (const Dictionary<Key, Info> &Dictionary){

    return compare(root, Dictionary.root);
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::compare(Element* const &left_hand_side, Element* const & right_hand_side){

    if(left_hand_side == NULL && right_hand_side == NULL)
        return true;
    else if(left_hand_side == NULL && right_hand_side)
        return false;
    else if(left_hand_side && right_hand_side == NULL)
        return false;
    else if(left_hand_side && right_hand_side){

        if(left_hand_side->key != right_hand_side->key){

            if(left_hand_side->info != right_hand_side->info)
                return false;
        }
    }

    else if(!compare(left_hand_side->left, right_hand_side->left)){

        if(!compare(left_hand_side->right, right_hand_side->right))
            return false;
    }else
        return true;
}

template<typename Key, typename Info>
bool Dictionary<Key, Info>::operator!= (const Dictionary<Key, Info> &Dictionary){

    return !(*this == Dictionary);
}

template <typename Key, typename Info>
bool Dictionary<Key, Info>::does_exist(const Key &key) const{

    Element *elem = root;

    while(elem != NULL){

        if(elem->key != key){

            if (elem == NULL)
                break;

            else{

                if(elem->key > key)
                    elem = elem->left;
                else if(elem->key < key)
                    elem = elem->right;
            }
        }
        else
            return true;
    }
    cout << "Key: " << key << ", does not exist" << endl;
    return false;
}

template <typename Key, typename Info>
void Dictionary<Key, Info>::remove_element(const Key &key){

    if(root == NULL){
        cout << "Dictionary is empty "<< endl;
        return;
    }

    if(!does_exist(key)){

        return;
    }

    Element *elem = root;
    Element *elem_parent= NULL;

    if((elem->left == NULL) && (elem->right == NULL)){
        this->~Dictionary();
        return;

    }while(elem){

        if(elem->key != key){

            if (elem == NULL)
                break;

            else{

                if(elem->key > key){

                    elem_parent = elem;
                    elem = elem->left;

                }else if(elem->key < key){

                    elem_parent = elem;
                    elem = elem->right;
                }
            }
        }
        else
        break;
}

    cout<< "Element("<< elem->key <<" "<< elem->info << " " << elem->Balance<< ") remove_elementd." <<endl;
    cout << endl << endl;

    if((elem->left) && (elem->right)){

        Element *succesor = elem->right;
        elem_parent = elem;

        while(succesor->left){

              elem_parent = succesor;
              succesor = succesor->left;
        }
        elem->key = succesor->key;
        elem->info = succesor->info;
        elem = succesor;
    }
    Element *subtree = elem->left;
    if(subtree == NULL)
        subtree = elem->right;
    if((elem_parent == NULL) && (elem)){

        elem->key = subtree->key;
        elem->info = subtree->info;
        elem->left = NULL;
        elem->right = NULL;
        delete subtree;
        set_balance(root);
        set_parent(root);
        return;
    }
    if(elem_parent->left == elem)
        elem_parent->left = subtree;
    else
        elem_parent->right = subtree;

    delete elem;
    set_balance(root);
    set_parent(root);
}

int main(){

    Dictionary<string, string> d1;
    d1.add_element("a", "Arbuz");
    d1.add_element("b", "Brzoskwinia");
    d1.add_element("c", "Cukinia");
    d1.add_element("d", "Dynia");
    d1.add_element("e", "Eukaliptus");
    d1.add_element("f", "Fiolek");
    d1.add_element("g", "Gruszka");
    d1.add_element("h", "Hiacynt");
    d1.add_element("i", "Irys");
    d1.add_element("j", "Jezyna");

    cout << "operator <<" << endl;
    cout << d1 << endl;

    cout << "print function: " << endl;
    d1.print();

    cout << endl << "does element with key 'c' exist? " << endl;
    if(d1.does_exist("c"))
        cout << "Exists" << endl;
    cout<<endl<<endl;
    d1.remove_element("j");
    d1.print();
    cout<<endl<<endl;
    d1.remove_element("i");
    d1.print();
    cout<<endl<<endl;
    d1.remove_element("h");
    d1.print();
    cout<<endl<<endl;
    d1.remove_element("k");//removing element with key not in tree
    d1.print();

    cout << "operator =" << endl;
    Dictionary<string, string> d2;
    d2 = d1;
    cout<<"D2:"<<endl;
    d2.print();

    cout << "Destructor:" << endl;
    d1.~Dictionary();
    d1.print();



    d1.add_element("a", "Arbuz");
    d1.add_element("b", "Brzoskwinia");
    d1.add_element("c", "Cukinia");
    d1.add_element("d", "Dynia");
    d1.add_element("e", "Eukaliptus");
    d1.add_element("f", "Fiolek");
    d1.add_element("g", "Gruszka");
    d1.add_element("h", "Hiacynt");
    d1.add_element("i", "Irys");
    d1.add_element("j", "Jezyna");


    cout << endl;
    cout << d1;

    Dictionary<string, string>::Iterator iterator1 = d1.begin();
    Dictionary<string, string>::Iterator iterator2 = d1.end();

    cout << endl << endl << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    cout << "iterator2 points at: (" << iterator2.getKey() << ":" << iterator2.getInfo() << ")" << endl;


    iterator1++;
    cout << "iterator1++" << endl;
    cout << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    iterator1++;
    cout << "iterator1++" << endl;
    cout << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    iterator1++;
    cout << "iterator1++" << endl;
    cout << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    cout<<endl;
    iterator1--;
    cout << "iterator1--" << endl;
    cout << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    iterator1--;
    cout << "iterator1--" << endl;
    cout << "iterator1 points at: (" << iterator1.getKey() << ":" << iterator1.getInfo() << ")" << endl;
    cout<<endl;
    cout << "iterator2 points at: (" << iterator2.getKey() << ":" << iterator2.getInfo() << ")" << endl;
    cout << "iterator2 = iterator2 - 4" << endl;
    iterator2 = iterator2 - 4;
    cout << "iterator2 points at: (" << iterator2.getKey() << ":" << iterator2.getInfo() << ")" << endl;
    cout<<endl;
    cout << "iterator2 points at: (" << iterator2.getKey() << ":" << iterator2.getInfo() << ")" << endl;
    cout << "iterator2 = iterator2 + 3" << endl;
    iterator2 = iterator2 + 3;
    cout << "iterator2 points at: (" << iterator2.getKey() << ":" << iterator2.getInfo() << ")" << endl;
    cout<<endl;

    return 0;
}
