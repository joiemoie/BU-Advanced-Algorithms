// Copyright 2017 Joseph Liba

#include <iostream>
#include "MyBloomFilter.h"

using namespace std;

int main(){

    string my_str = "Joiemoie";

    MyBloomFilter my_filter(20);
    cout << "My empty filter looks like: " << my_filter.output() << endl;
    
    my_filter.insert(my_str);
    cout << "Inserting " << my_str << endl;
    cout << "My filter now looks like: " << my_filter.output() << endl;
    
    cout << "Is " << my_str << " in my filter? ";
    if (my_filter.exists(my_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;
    
    string fake_str = "eiomeioJ";
    cout << "Is " << fake_str << " in my filter? ";
    if (my_filter.exists(fake_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;

    my_str = "hello";

    cout << "My empty filter looks like: " << my_filter.output() << endl;
    
    my_filter.insert(my_str);
    cout << "Inserting " << my_str << endl;
    cout << "My filter now looks like: " << my_filter.output() << endl;
    
    cout << "Is " << my_str << " in my filter? ";
    if (my_filter.exists(my_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;
    
    fake_str = "hi";
    cout << "Is " << fake_str << " in my filter? ";
    if (my_filter.exists(fake_str)) cout << "\t\tYes." << endl;
    else cout << "\t\tNo." << endl;

}
