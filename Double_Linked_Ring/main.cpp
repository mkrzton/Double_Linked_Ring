#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cstddef>

using namespace std;

template <typename Key, typename Info>
class Double_Linked_Ring {

struct Knob {

    Key  k;
    Info i;
    Knob* next;
    Knob* previous;
};

    Knob* any;
    int counter;

public:

class Constant_Iterator{

    Knob* component;

public:

Constant_Iterator()  { component = NULL; }
Constant_Iterator(Knob* copyComponent) {component = copyComponent;}
Constant_Iterator(const Constant_Iterator& copy) { component = copy.component; *this = copy;}
~Constant_Iterator() {}
Constant_Iterator& operator=(const Constant_Iterator& copy) { component = copy.component; return *this; }
bool operator==(const Constant_Iterator& comparison) { return component == comparison.component; }
bool operator!=(const Constant_Iterator& comparison) { return component != comparison.component; }

Constant_Iterator operator--(){

    if (component != NULL){

        component = component->previous;
    }

    return *this;
}

Constant_Iterator operator++(){

    if (component != NULL){

        component = component->next;
    }
    return *this;
}

Constant_Iterator operator-(const int number){


     Constant_Iterator result(*this);

    for (int i = 0; i<number; i++){
        --(*this);
    }
    return result;
}

Constant_Iterator operator+(const int number){


     Constant_Iterator result(*this);

    for (int i = 0; i<number; i++){
        ++(*this);
    }
    return result;
}

const Knob& operator*() {return *component;}
const Knob* operator->() {return component;}
Key get_Key() const {return component->k;}
Info get_Data() const {return component->i;}
};

Constant_Iterator const_begin() const{

    return Constant_Iterator(any);
}

Constant_Iterator const_end() const{


    return Constant_Iterator(any->previous);    }

Double_Linked_Ring(){

    any = NULL;
    counter = 0;
}

Double_Linked_Ring(const Double_Linked_Ring<Key, Info>& x){

    any = NULL;
    counter = 0;
    *this = x;
}

~Double_Linked_Ring(){

    clearList();
}

int length() const{return counter;}

void clearList(){

    Knob* tab;

        if (any == NULL){

            return;
        }

    any->previous->next = NULL;

            while (any != NULL){

                tab = any;
                any = any->next;
                delete tab;
            }
    counter = 0;
}

bool add_next_component(const Key& key, const Info& info){

    Knob* newKnob = new Knob();
    newKnob->k = key;
    newKnob->i = info;

    if (any == NULL){

        newKnob->next = newKnob;
        newKnob->previous = newKnob;
        any = newKnob;
        counter++;
        return true;

    }else{

        newKnob->next = any;
        newKnob->previous = any->previous;
        any->previous->next = newKnob;
        any->previous = newKnob;
        counter++;
        return true;
    }

    return false;
}

bool add_before_element_added_last(const Key& key, const Info& info){

    Knob* newKnob = new Knob();
    newKnob->k = key;
    newKnob->i = info;

    if (any == NULL){

        newKnob->next = newKnob;
        newKnob->previous = newKnob;
        any = newKnob;
        counter++;
        return true;

    }else{

        newKnob->previous = any;
        newKnob->next = any->next;
        any->next->previous = newKnob;
        any->next = newKnob;
        counter++;
        return true;
    }

    return false;
}

void remove_component(const Key& k, bool each){

    int len1;
    len1 = length();
    Knob* tab = any;
    Knob* tab_2;

    while (any->k == k){

        tab_2 = tab;
        tab->previous->next = tab_2->next;
        tab->next->previous = tab_2-> previous;
        any = tab->next;
        counter--;
        delete tab_2;
        if (each == false)
            return;
    }

    while (len1 > 0){

        if (each == true){

            if (tab->k == k){

                tab_2 = tab;
                tab->previous->next = tab_2->next;
                tab->next->previous = tab_2->previous;
                tab = tab->next;
                delete tab_2;
                counter--;
                len1--;
            }

        tab = tab->next;

        }else

            if (tab->k == k){

                tab_2 = tab;
                tab->previous->next = tab_2->next;
                tab->next->previous = tab_2->previous;
                tab = tab->next;
                delete tab_2;
                counter--;
                len1--;
                return;
            }
        tab = tab->next;
        len1--;

    }
}

void display_list(){

    Knob* tab = any;
    int number = counter;

    if (tab == NULL){

        cout << "List is empty" << endl;
        return;

    }do{

        cout << tab->i <<endl;
        tab = tab->next;
        number--;
    } while(number > 0);
}

Double_Linked_Ring<Key, Info>& operator=(const Double_Linked_Ring<Key, Info>& copyRing){

    if (&copyRing == this)
        return *this;

    int len = copyRing.length();

    clearList();
    Knob* current = copyRing.any;

    while (len > 0){

        add_next_component(current->k, current->i);
        current = current->next;
        len--;
    }

    return *this;
}

friend Double_Linked_Ring<Key, Info>& operator+(const Double_Linked_Ring<Key, Info>& ring1, const Double_Linked_Ring<Key, Info>& ring2){

Double_Linked_Ring<Key, Info> *newRing=new Double_Linked_Ring<Key,Info>;
Double_Linked_Ring<Key, Info>::Constant_Iterator iterator1 = ring1.const_begin();
Double_Linked_Ring<Key, Info>::Constant_Iterator iterator2 = ring2.const_begin();

    do{

        newRing->add_next_component(iterator1.get_Key(), iterator1.get_Data());
        ++iterator1;

    } while (ring1.const_begin()!=iterator1);

    do{

        newRing->add_next_component(iterator2.get_Key(), iterator2.get_Data());
        ++iterator2;

    } while (iterator2 != ring2.const_begin());

    return *newRing;
}

friend Double_Linked_Ring<Key, Info>& operator-(const Double_Linked_Ring<Key, Info>& ring1, const Double_Linked_Ring<Key, Info>& ring2){

    Double_Linked_Ring<Key, Info> *newRing = new Double_Linked_Ring<Key, Info>;
    Double_Linked_Ring<Key, Info>::Constant_Iterator iterator1 = ring1.const_begin();
    Double_Linked_Ring<Key, Info>::Constant_Iterator iterator2 = ring2.const_begin();

    int len = ring1.length();
    bool found = false;

    while (len > 0){

        iterator2 = ring2.const_begin();

        do{
            if (iterator1->k==iterator2->k){

                found = true;
            }
                if (found == true){

                    break;

                }
            ++iterator2;

        } while (ring2.const_begin() != iterator2);

        if (found == false){

            newRing->add_next_component(iterator1.get_Key(), iterator1.get_Data());

        }else{
                found = false;
            }

            len--;
            ++iterator1;
        }
    return *newRing;
}

friend ostream& operator << (ostream &out, const Double_Linked_Ring<Key, Info>& data){

    if (data.any == NULL)
        return out;

    Knob* tab = data.any;

        do{

            out << tab->i << endl;
            tab = tab->next;

        } while (tab != data.any);

    return out;
}
};

template <typename Key, typename Info>
Double_Linked_Ring<Key, Info> produce(const Double_Linked_Ring<Key, Info>& ring1, int start1, int steps1, bool direction1,
    const Double_Linked_Ring<Key, Info>& ring2, int start2, int steps2, bool direction2, int num, bool direction_out){

    int ring1_len = ring1.length();
    int ring2_len = ring2.length();
    int ring1_start = start1 % ring1_len;
    int ring2_start = start2 % ring2_len;

    Double_Linked_Ring<Key, Info> ring3;

    typename Double_Linked_Ring<Key, Info>::Constant_Iterator iterator1 = ring1.const_begin();
    typename Double_Linked_Ring<Key, Info>::Constant_Iterator iterator2 = ring2.const_begin();



    if (direction1 == 0){

        iterator1-ring1_start;

    }else{

        iterator1+ring1_start;
    }

    if (direction2 == 0){

        iterator2-ring2_start;

    }else{

        iterator2+ring2_start;
    }



while (num > 0){

    if (direction_out == 1){

        for (int i = 0; i < steps1; i++){

            ring3.add_next_component(iterator1.get_Key(), iterator1.get_Data());

                if (direction1 == 0){

                --iterator1;

                }else{

                ++iterator1;

                }
            }

        for (int i = 0; i < steps2; i++){

            ring3.add_next_component(iterator2.get_Key(), iterator2.get_Data());

            if (direction2 == 0){

                --iterator2;

            }else{

                ++iterator2;
            }
        }

    num--;

    }else{

        for (int i = 0; i < steps1; i++){

            ring3.add_before_element_added_last(iterator1.get_Key(), iterator1.get_Data());

                if (direction1 == 0){

                    --iterator1;

                }else{

                    ++iterator1;
                }
            }

        for (int i = 0; i < steps2; i++){

            ring3.add_before_element_added_last(iterator2.get_Key(), iterator2.get_Data());

            if (direction2 == 0){

                --iterator2;

            }else{

                ++iterator2;
            }
        }

        num--;
    }
    }

    return ring3;
}

int main()
{
    Double_Linked_Ring<int, string> ring1;
    ring1.add_next_component(1,"ECIRS");
    ring1.add_next_component(2,"EPFU");
    ring1.add_next_component(3,"EPHY");
    cout << "Ring 1 " << endl << ring1<<endl;
    Double_Linked_Ring<int, string> ring2;
    ring2.add_next_component(4,"EORI");
    ring2.add_next_component(5,"EADS");
    ring2.add_next_component(6,"EACAW");
    cout << "Ring 2 " << endl << ring2 << endl;
    ring2.remove_component(6, false);
    cout << "Ring 2 after removing: " << endl << ring2 << endl;
    ring2=ring1+ring2;
    cout <<"+operator"<< endl << ring2 << endl;
    ring2=ring2-ring1;
    cout <<"-operator"<< endl << ring2 << endl;
    cout<<"Demonstration of Produce function: "<<endl;
    Double_Linked_Ring<int, string> ring3= produce(ring1, 0, 2, false, ring2, 3, 1, true, 4, true);
    ring3.display_list();
    cout<< endl;

    Double_Linked_Ring<int, float> r1;
    r1.add_next_component(1, 1.111);
    r1.add_next_component(2, 2.222);
    r1.add_next_component(3, 3.333);
    cout << "Ring 1 " << endl << r1<<endl;
    Double_Linked_Ring<int, float> r2;
    r2.add_next_component(4, 4.444);
    r2.add_next_component(5, 5.555);
    r2.add_next_component(6, 6.666);
    cout<< "Ring 2: " <<endl;
    cout << r2<<endl<< endl;
    r2.remove_component(6, false);
    cout<< "Ring 2 after removing: " <<endl << r2<<endl;
    r1= r1 + r2;
    cout << "+operator: " << endl << r1 << endl;
    r1 = r1 - r2;
    cout << "-operator: " << endl << r1 << endl;
    cout <<endl<< "Produce function: " << endl;
    Double_Linked_Ring<int, float> r3= produce(r1, 1, 2, true, r2, 3, 1, false, 6, false);
    cout << "Ring 3:" << endl;
    r3.display_list();
    return 0;
}
