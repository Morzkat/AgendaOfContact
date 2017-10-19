#include <iostream>
#include <fstream>

using namespace std;

// struct basic for a contact
struct contact
{
    string name;
    string lastName;
    string phoneNumer;

    struct contact* next;
};

// first and last contact objects
contact* firstItem = NULL;
contact* lastItem = NULL;

//file
fstream file;

// class for action
class Action
{
public:
    static void addContact(contact *newContact);
    static void showContacts();
    static void menu();
    static void createContact();
    static void deleteContact();
    static void alterContact();

};

class FileManager
{
public:
    static void WriteInFile(string,string,string);
    static void getAllFileContent();
};

void FileManager::getAllFileContent()
{
    string line;
    ifstream file("contacts.txt", ios::in);
    if(file.is_open())
    {
        while (getline(file,line))
        {
            cout << line << "\n";
        }

        file.close();
    }
}

void FileManager::WriteInFile(string name, string lastName, string phoneNumber)
{
    //open the txt file
    file.open("contacts.txt", ios::app);

    //write in the file
    file << "--------------------------------------------------------\n";
    file << "Nombre del contacto: " << name << "\n";
    file << "Apellido del contacto: " << lastName << "\n";
    file << "Numero de telefo del contacto: " << phoneNumber << "\n";
    file << "---------------------------------------------------------\n";

    file.close();
}

void Action::createContact()
{
    //create a new struct for a contact
    contact* newContact = new (struct contact);

    //get the data for the contact
    cout << "Introduzca el nombre del contacto:";
    string contactName;
    cin >> contactName;

    cout << "Introduza el apellido del contacto:";
    string contactLastName;
    cin >> contactLastName;

    cout << "Introduza el numero de telefono del contacto:";
    string contactPhoneNumber;
    cin >> contactPhoneNumber;

    //add the data to the contact
    newContact->name = contactName;
    newContact->lastName = contactLastName;
    newContact->phoneNumer = contactPhoneNumber;

    //add the contact to the list of items
    addContact(newContact);

    cout << "Contacto Agregado\n";
}

void Action::addContact(contact *newContact)
{
    //last contact like null
    newContact->next = NULL;

    //doesn't exist first contact
    if (firstItem == NULL)
    {
        //the first and the last contact are the same
        firstItem = newContact;
        lastItem = newContact;
    }

        //exist a first contact
    else
    {
        //the last(penultimate) contact the next contact is the newContact(latest created)
        lastItem->next = newContact;
        //the new last contact is the latest created
        lastItem = newContact;
    }
}

void Action::showContacts()
{
    //show the items if there are
    if (firstItem != NULL) {
        contact *i = firstItem;

        while (i != NULL) {
            cout << "--------------------------------------------------------\n";
            cout << "Nombre del contacto: " << i->name << "\n";
            cout << "Apellido del contacto: " << i->lastName << "\n";
            cout << "Numero de telefo del contacto: " << i->phoneNumer << "\n";
            cout << "---------------------------------------------------------\n";

            FileManager::WriteInFile(i->name, i->lastName, i->phoneNumer);

            i = i->next;
        }

    }

    //there aren't items
    else
    {
        cout << "La lista esta vacia\n";
    }

    cout << "Contactos previamente guardados\n";
    FileManager::getAllFileContent();
}

void Action::menu()
{
    //menu for the options
    cout << "Elige una de las opciones\n";
    cout << "1- Listar contactos y guardar\n";
    cout << "2- Nuevo Contacto\n";
    cout << "3- Modificar un contacto \n";
    cout << "4- Eliminar contacto\n";
    cout << "5- Salir\n";
    cout << "Elija una opcion =>";
}

void Action::deleteContact()
{
    //if there are contact show the items to choose which delete
    if (firstItem != NULL)
    {
        cout << "Selecciona el contacto a eliminar\n";
        //show items
        showContacts();

        //get the contact name
        string name;
        cin >> name;

        //object for the loop
        contact* i = firstItem;
        //the current contact
        contact* currentItem = firstItem;
        //the previous contact
        contact* previousItem = NULL;

        //the loop for search the contact
        while(i != NULL && i->name != name)
        {
            previousItem = currentItem;
            currentItem = currentItem->next;
            i = i->next;
        }

        //the first the contact will be delete
        if (previousItem == NULL)
        {
            firstItem = currentItem->next;
            delete currentItem;
        }

        //other contact will be delete
        if (currentItem->name == name)
        {
            firstItem->next = currentItem->next;
            delete currentItem;
            cout << "Contacto elimando\n";
        }
    }

    else
    {
        cout << "La lista esta vacia o no se encontro el contacto";
    }
}

void Action::alterContact()
{
    //if there are contact show the items to choose which delete
    if (firstItem != NULL)
    {
        string newName;
        string newLastName;
        string newPhoneNumber;

        cout << "Selecciona el contacto a modificar\n";
        //show items
        showContacts();

        //get the contact name
        string name;
        cin >> name;

        //object for the loop
        contact* i = firstItem;
        //the current contact
        contact* currentItem = firstItem;
        //the previous contact
        contact* previousItem = NULL;

        cout << "Nuevo nombre del contacto: ";
        cin >> newName;
        cout << "Nuevo apellido del contacto: ";
        cin >> newLastName;
        cout << "Nuevo numero de telefono del contacto: ";
        cin >> newPhoneNumber;

        //the loop for search the contact
        while(i != NULL && i->name != name)
        {
            previousItem = currentItem;
            currentItem = currentItem->next;
            i = i->next;
        }

        //the first the contact will be alter
        if (previousItem == NULL)
        {
            currentItem->name = newName;
            currentItem->lastName = newLastName;
            currentItem->phoneNumer = newPhoneNumber;
            firstItem = currentItem;
        }

        //other contact will be alter
        if (currentItem->name == name)
        {
            currentItem->name = newName;
            currentItem->lastName = newLastName;
            currentItem->phoneNumer = newPhoneNumber;
            firstItem = currentItem;
        }

        cout << "Contacto modificado\n";

    }

    else
    {
        cout << "La lista esta vacia o no se encontro el contacto";
    }
}

int main()
{

// switch opcion
    short op;

    do
    {
        Action::menu();

        cin >> op;

        switch (op)
        {
            case 1 :
                Action::showContacts();
                break;
            case 2:
                Action::createContact();
                break;
            case 3 : Action::alterContact();
                break;
            case 4:
                Action::deleteContact();
                break;
        }
    }while (op < 5);
}