#include "StringContactMap.h"
#include "Hash.h"

#include <algorithm>

using namespace std;

StringContactMap::StringContactMap(int initial_capacity)
{
    //Set capacity as initial capacity
    capacity = initial_capacity;
    //Make dynamic map with size: capacity
    map = new ListPtr[capacity];
    for(int i = 0; i < capacity; i++)
    {
        //Set all indexes as new ContactList
        map[i] = new ContactList;
    }
    //Set count to 0
    count = 0;
}

StringContactMap::~StringContactMap()
{
    for(int i = 0; i < capacity; i++)
    {
        //Delete every index of the map
        delete map[i];
    }

    //Delete the map
    delete [] map;
}

void StringContactMap::load_check()
{
    //If the input percentage is bigger than the max load
    if((count / static_cast<double>(capacity)) > MAX_LOAD)
    {
        rebuild();
    }
}

void StringContactMap::rebuild()
{
    //Create temp map to keep the old map
    ListPtr *old_map = map;
    //Create temp capacity to keep the old capcity
    int old_capacity = capacity;

    //Double the new capacity
    capacity *= 2;
    //Make new dynamic map with double capacity
    map = new ListPtr[capacity];

    for(int i = 0; i < capacity; i++)
    {
        map[i] = new ContactList;
    }

    //Vector that will keep lists of StringContactPair
    vector<StringContactPair> old_list;

    //Set count to 0 beacuse the add function raises the count by one when called
    count = 0;

    for(int i = 0; i < old_capacity; i++)
    {
        //Set old_list to a vector of list
        old_list = old_map[i]->to_vector();

        //Add the old_list to the new map
        for(unsigned int j = 0; j < old_list.size(); j++)
        {
            add(old_list[j].key, old_list[j].value);
        }

        //Clear the vector for new lists
        old_list.clear();
        delete old_map[i];
    }

    delete [] old_map;
}

int StringContactMap::size() const
{
	return count;
}

bool StringContactMap::empty() const
{
	return count == 0;
}

vector<Contact> StringContactMap::all_contacts() const
{
	//Create vector that will keep contact intsances
	vector<Contact> vec;
	for(int i = 0; i < capacity; i++)
    {
        //Get contacts into the vector
        map[i]->get_contacts(vec);
    }
	return vec;
}

void StringContactMap::add(string key, Contact value)
{
    //Perform a load check before adding
    load_check();

    int hash_key = hash(key) % capacity;

    //If the add function returns true, then raise the counter
    if(map[hash_key]->add(key, value))
    {
        ++count;
    }

}

void StringContactMap::remove(string key)
{
    int hash_key = hash(key) % capacity;

    //If the remove function returns true, then lower the count
    if(map[hash_key]->remove(key))
    {
        --count;
    }

}

bool StringContactMap::contains(string key) const
{
    int hash_key = hash(key) % capacity;

    //Return the truth value of the contains function
    return map[hash_key]->contains(key);
}

Contact StringContactMap::get(string key) const
{
	int hash_key = hash(key) % capacity;

	//Return the value of get function
	return map[hash_key]->get(key);
}

vector<Contact> StringContactMap::prefix_search(string prefix) const
{
	//Make a vector that will contain instances of Contact
	vector<Contact> prefix_vec;

	for(int i = 0; i < capacity; i++)
    {
        map[i]->get_contacts_by_prefix(prefix, prefix_vec);
    }

	return prefix_vec;
}

// Optionally implement.
ostream& operator <<(ostream& out, const StringContactMap& map)
{
	return out;
}

