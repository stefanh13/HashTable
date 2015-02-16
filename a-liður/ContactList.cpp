#include "ContactList.h"

using namespace std;

ContactList::ContactList()
{
    //Let head point to NULL
    head = NULL;
}

ContactList::~ContactList()
{
    remove_all();
}

void ContactList::remove_all()
{
    //If it's the empty list, return
    if(head == NULL)
    {
        return;
    }

    //Set temp pointer to headþ
    NodePtr tmpPtr = head;

    while(head != NULL)
    {
        //Keep old head
        tmpPtr = head;
        //Set head to the next node
        head = head->link;
        //delete the old head
        delete tmpPtr;
    }
}

bool ContactList::add(string key, Contact value)
{
	//If the list is empty
	if(head == NULL)
    {
        //Create a new node
        NodePtr new_node = new ContactNode(key, value);
        //Let head point to the noew node
        head = new_node;
        return true;
    }

    //Set temp pointer to head
    NodePtr tmpPtr = head;
    //Create a new node pointer that will keep the end node if the loops goes all the way through
    NodePtr new_node = NULL;
    while(tmpPtr != NULL)
    {
        //If the key is already in the list
        if(tmpPtr->data.key == key)
        {
            //Update value
            tmpPtr->data.value = value;
            return false;
        }

        new_node = tmpPtr;

        tmpPtr = tmpPtr->link;
    }
    //Add a new node to the back of the list
    new_node->link = new ContactNode(key, value);
	return true;
}

bool ContactList::remove(string key)
{
	//If it's the empty list
	if(head == NULL)
    {
        return false;
    }

	//Set temp pointer to head
	NodePtr tmpPtr = head;

    //If it's the first node of the list
	if(head->data.key == key)
    {
        head = head->link;
        delete tmpPtr;
        return true;
    }

    //Make this node to iterate one note ahead of tmpPtr
    NodePtr removeNode = tmpPtr->link;

    while(removeNode != NULL)
    {
        //If the key is in the list
        if(removeNode->data.key == key)
        {
            tmpPtr->link = removeNode->link;
            delete removeNode;
            return true;
        }

        tmpPtr = removeNode;
        removeNode = removeNode->link;
    }

	return false;
}

bool ContactList::contains(string key)
{
	//If it's the empty list
	if(head == NULL)
    {
        return false;
    }
    //Set new temp pointer to head
    NodePtr tmpPtr = head;
    while(tmpPtr != NULL)
    {
        //If the key is in the list
        if(tmpPtr->data.key == key)
        {
            return true;
        }

        tmpPtr = tmpPtr->link;
    }
	return false;
}

Contact ContactList::get(string key)
{
    //Set new temp pointer to head
    NodePtr tmpPtr = head;

    while(tmpPtr != NULL)
    {
        //If the key is int the list
        if(tmpPtr->data.key == key)
        {
            //return the value with that key
            return tmpPtr->data.value;
        }

        tmpPtr = tmpPtr->link;
    }

    //Throw exception if the key is not in the list
    throw KeyException();

}

void ContactList::get_contacts(vector<Contact>& contacts)
{
    //Set new temp pointer to head
    NodePtr tmpPtr = head;

    while(tmpPtr != NULL)
    {
        //Push value into the vector
        contacts.push_back(tmpPtr->data.value);

        tmpPtr = tmpPtr->link;
    }
}

void ContactList::get_contacts_by_prefix(string prefix, vector<Contact>& contacts)
{
    //Not for part a
}

vector<StringContactPair> ContactList::to_vector()
{
	//Create a vector to push into
	vector<StringContactPair> vec;
	//Set temp pointer to head
	NodePtr tmpPtr = head;


	while(tmpPtr != NULL)
    {
        //Push the data in the vector
        vec.push_back(tmpPtr->data);

        tmpPtr = tmpPtr->link;
    }

	return vec;
}

ostream& operator <<(ostream& outs, const ContactList& lis)
{
	NodePtr tmpPtr = lis.head;

	while(tmpPtr != NULL)
    {
        outs << tmpPtr->data.value << endl;

        tmpPtr = tmpPtr->link;
    }

	return outs;
}
