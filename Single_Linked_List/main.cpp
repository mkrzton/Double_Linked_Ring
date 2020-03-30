#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

template <typename key, typename info>
struct element
{
        key k;
        info data;
        element<key, info>* next;
};

template <typename key, typename info>
class Sequence
{
        int counter;
        element<key, info>* head;
        element<key, info>* last;
public:
        Sequence()
        {
                counter = 0;
                head = NULL;
                last = NULL;
        }
        ~Sequence()
        {
                clear_list();
        }
        Sequence(const Sequence<key, info>& x)
        {
                head = NULL;
                last = NULL;
                counter = 0;
                *this = x;
        }
        void clear_list()
        {
                if (head == NULL)
                        return;

                element<key, info>* temp;
                do {
                        temp = head;
                        head = temp->next;
                        delete temp;
                } while (head != NULL);
                last = NULL;
                counter = 0;
        }
        bool addBack(const key& k, const info& i)
        {
                element<key, info>* etr = new element<key, info>;
                if (etr == NULL) {
                        cerr << "Allocation memory failure!" << endl;
                        return false;
                }
                etr->data = i;
                etr->k = k;
                etr->next = NULL;
                if (head == NULL)
                {

                        head = etr;
                        last = etr;
                        counter++;
                        return true;
                }
                else
                {
                        last->next = etr;
                        last = etr;
                        counter++;
                        return true;
                }
                return false;
        }
        bool addFirst(const key& k, const info& i)
        {
                element<key, info>* etr = new element<key, info>;
                if (etr == NULL) {
                        cerr << "Allocation memory failure!" << endl;
                        return false;
                }
                etr->k = k;
                etr->data = i;
                etr->next = head;
                head = etr;
                counter++;
                if (last == NULL)
                {
                        last = etr;
                        return true;
                }
                return true;
        }
        void display()
        {
                element<key, info>* temp = head;
                if (head == NULL)
                {
                        return;
                }
                while (temp != NULL)
                {
                        cout << temp->k << "=>" << temp->data << endl;
                        temp = temp->next;
                }
        }
        void display_element(const key& k)
        {
                element<key, info>*temp = head;

                if (head == NULL)
                {
                        return;
                }
                while (temp != NULL)
                {
                        if (temp->k == k)
                        {
                                cout << "Element: " << temp->k << "=>" << temp->data << endl;
                        }
                        temp = temp->next;
                }
        }
        void info_element(key k)
        {
                element<key, info>* temp = head;
                while (temp)
                {
                        if (temp->k == k)
                        {
                                cout << temp->data << endl;
                        }
                        temp = temp->next;
                }
        }
        int count_keys(key k) const
        {
                element<key, info>* temp = head;
                int count = 0;
                while (temp)
                {
                        if (temp->k == k)
                        {
                                count++;
                        }
                        temp = temp->next;
                }
                return count;
        }
        void remove(key k)
        {
                int keys = count_keys(k);
                while (keys != 0)
                {
                        element<key, info> *current;
                        element<key, info>* trailCurrent;
                        bool found;
                        if (head == NULL)
                        {
                                cout << "List is empty. You cannot delete from empty list!" << endl;
                                return;
                        }
                        else
                        {
                                if (head->k == k)
                                {
                                        current = head;
                                        head = head->next;
                                        counter--;
                                        keys--;
                                        if (head == NULL)
                                                last = NULL;
                                        delete current;


                                }
                                else
                                {
                                        found = false;
                                        trailCurrent = head;
                                        current = head->next;
                                        while (current != NULL && !found)
                                        {
                                                if (current->k != k)
                                                {
                                                        trailCurrent = current;
                                                        current = current->next;
                                                }
                                                else
                                                        found = true;
                                        }
                                        if (found)
                                        {
                                                trailCurrent->next = current->next;
                                                counter--;
                                                keys--;
                                                if (last == current)
                                                {
                                                        last = trailCurrent;
                                                        delete current;

                                                }
                                        }
                                        else
                                                cout << "The element to be removed is not in the list" << endl;


                                }
                        }
                }
        }
        int size() const
        {
                return counter;
        }
        bool add_at_position(const key& k, const info& d, int position)
        {
                if (position > size() || position < 0)
                {
                        cout << "Not available position!" << endl;
                        return false;
                }

        if (position == 0)
        {
                if (head == NULL)
                {
                        addFirst(k, d);
                        return true;
                }

        }
        else if (position == size())
        {

                addBack(k,d);
                return true;
        }
        else
        {
                element<key, info>* etr = new element<key, info>;
                if (etr == NULL) {
                        cerr << "Allocation memory failure!" << endl;
                        return false;
                }
                etr->k = k;
                etr->data = d;
                element<key, info>* temp = head;
                for (int i = 0; i < position - 1; i++)
                {
                        temp = temp->next;
                }
                etr->next = temp->next;
                temp->next = etr;

                return true;
        }
}
        bool find_key(const key& k)
        {
                element<key, info>*temp = head;
                while (temp)
                {
                        if (temp->k == k)
                                return true;
                        temp = temp->next;
                }
                return false;
        }
        bool find_info(const info& i)
        {
                element<key, info>*temp = head;
                while (temp)
                {
                        if (temp->i == i)
                                return true;
                        temp = temp->next;
                }
                return false;
        }
        bool find_element(const key&k1, const info& data1)
        {
                element<key, info>* temp = head;
                while (temp)
                {
                        if (temp->data == data1 && temp->k == k1)
                        {
                                return true;
                        }
                        temp = temp->next;
                }
                return false;
        }
        Sequence<key, info>& operator=(const Sequence<key, info>& Sequence)
        {
                if (this == &Sequence)
                        return *this;
                else
                        clear_list();
                element<key, info>* temp = Sequence.getHead();
                while (temp)
                {
                        addBack(temp->k, temp->data);
                        temp = temp->next;
                }
                return *this;
        }
        friend Sequence<key, info>& operator+(const Sequence<key, info>& s1, const Sequence<key, info>& s2)
        {
                {
                        Sequence<key, info>* ns = new Sequence<key, info>;
                        element<key, info>* temp1 = s1.getHead();
                        element<key, info>* temp2;
                        element<key, info>* temp3 = s2.getHead();
                        int count = 0;
                        while (temp1)
                        {
                                ns->addBack(temp1->k,temp1->data);
                                temp1 = temp1->next;
                        }


                        while (temp3)
                        {
                                temp2 = s1.getHead();
                                while (temp2)
                                {

                                        if (temp3->k == temp2->k && temp3->data == temp2->data)
                                        {
                                                count++;
                                                break;
                                        }
                                        temp2 = temp2->next;
                                }
                                if (count == 1)
                                {
                                        count = 0;
                                        temp3 = temp3->next;
                                        continue;
                                }
                                ns->addBack(temp3->k,temp3->data);
                                temp3 = temp3->next;
                        }
                        return *ns;
                }
        }
        friend Sequence<key, info>& operator-(const Sequence<key, info>& s1, const Sequence<key, info>& s2)

        {
                Sequence<key, info>* ns = new Sequence<key, info>();
                element<key, info>* temp1 = s1.getHead();
                element<key, info>* temp2 = s2.getHead();
                int counter = 0;

                while (temp1)
                {
                        temp2 = s2.getHead();
                        while (temp2)
                        {

                                if (temp1->k == temp2->k && temp1->data == temp2->data)
                                {
                                        counter++;
                                        break;
                                }
                                temp2 = temp2->next;

                        }
                        if (counter == 1)
                        {
                                counter = 0;
                                temp1 = temp1->next;
                                continue;
                        }
                        ns->addBack(temp1->k,temp1->data);
                        temp1 = temp1->next;
                }
                return *ns;
        }
        friend ostream& operator << (ostream &o, const Sequence<key, info>& s)
        {
                if (s.getHead() == NULL)
                        return o;
                element<key, info>* temp = s.getHead();
                while (temp)
                {
                        o << temp->k << "=>" << temp->data << endl;
                        temp = temp->next;
                }
                return o;
        }

        element<key, info>* getHead() const
        {
                if (head == NULL)
                        return NULL;
                else return head;
        }

};



template<typename key, typename info>
Sequence <key, info>& shuffle(const Sequence<key, info> &s1, int start1, int len1, const Sequence<key, info> &s2, int start2, int len2, int count)
{
        Sequence <key, info>* ns = new Sequence<key, info>();
        element <key, info>* temp1 = s1.getHead();
        element<key, info>* temp2 = s2.getHead();

        while (start1 > 0)
        {
                if (s1.size() < start1)
                {
                        temp1 = NULL;
                        break;
                }
                temp1 = temp1->next;
                start1--;
        }
        while (start2 > 0)
        {
                if (s2.size() < start2)
                {
                        temp1 = NULL;
                        break;
                }
                temp2 = temp2->next;
                start2--;
        }

        while (count != 0)
        {
                for (int i = 0; i < len1; i++)
                {
                        if (temp1 == NULL)
                                break;
                        ns->addBack(temp1->k, temp1->data);
                        temp1 = temp1->next;
                }
                for (int i = 0; i < len2; i++)
                {
                        if (temp2 == NULL)
                                break;
                        ns->addBack(temp2->k, temp2->data);
                        temp2 = temp2->next;
                }
                count--;
        }

        return *ns;

}

int main()
{

        Sequence<int, string>s1;
        Sequence<int, string>s2;
        Sequence<int, string>s3;
        s1.add_at_position(1, "first", 0);
        s1.addBack(2, "second");
        s1.addBack(3, "third");
        cout << "S1:" << endl;
        s1.display();
        s2.addBack(1, "first");
        s2.addBack(5, "fifth");
        s2.add_at_position(0, "zeroth", 2);
        s2.addBack(1, "first");
        s2.addFirst(5, "fifth");
        s2.remove(5);
        s2.addBack(9, "ninth");
        s2 = s1 + s2;
        s2 = s2 - s1;
        cout << "S2:" << endl;
        s2.display();
        s3 = shuffle(s1, 0, 1, s2, 0, 1, 3);
        cout << "S3:" << endl << s3;
        return 0;
}



