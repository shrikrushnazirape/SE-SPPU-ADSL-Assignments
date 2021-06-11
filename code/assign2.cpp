/*
A Dictionary stores keywords and its meanings. Provide facility for adding new
keywords, deleting keywords, updating values of any entry. Provide facility to display
whole data sorted in ascending/ Descending order. Also find how many maximum
comparisons may require for finding any keyword. Use Binary Search Tree for
implementation.
*/

#include <iostream>
#include <string>
using namespace std;

class node
{
    string word, mean;
    node *r;
    node *l;

public:
    node()
    {

        r = NULL;
        l = NULL;
    }
    node(string word,string mean)
    {
        this->word = word;
        this->mean = mean;
        r = NULL;
        l = NULL;
    }
    friend class dict;
};

class dict
{
private:
    node *root = NULL;

public:
    node *get_root()
    {
        return root;
    }
    void create();
    void search(node *root, string key, node *&curr, node *&par);
    void search_node();
    void inorder(node *root);
    void del_node(node *ro);
    void del_1(node *&curr, node *&par);
    void del_0(node *&curr, node *&par);
    void del_2(node *&curr, node *&par);
    void postorder(node *ro);
    void successor(node *&curr, node *&par, node *&s);
    void update(node *r);
};
void dict::search_node(){
    string w;
    node* curr;
    node* p;
    cout<<"Which word to search  ";
    cin>>w;
    search(root,w,curr,p);
    if(curr==NULL){
        cout<<w<<" is not present in tree\n";
    }else{
        cout<<w<<" is present in tree\n";
    }
}

void dict::del_2(node *&curr, node *&par)
{
    node *s = NULL;
    successor(curr->r, par, s);
    curr->word = s->word;
    curr->mean = s->mean;
    if (s->r != NULL)
    {
        del_1(s, curr); //successor to delete
    }
    else
    {
        del_0(s, curr);
    }
}

void dict::update(node *r)
{
    string w, m;
    node *curr = NULL;
    node *par = NULL;
    cout << "Which word's meaning you want to update \n";
    cin >> w;
    search(r, w, curr, par);
    if (curr == NULL)
    {
        cout << "sorry but word is not present :((( \n";
        return;
    }
    else
    {
        cout << "Update the meaning of word  ";
        cin >> m;
        curr->mean = m;
        cout << "Successfully get updated :))   \n";
    }
}

void dict::successor(node *&curr, node *&par, node *&s)
{
    if (curr->l == NULL)
    {
        s = curr;
        return;
    }
    par = curr;
    successor(curr->l, par, s);
}

void dict::del_0(node *&curr, node *&par)
{
    if (par->l == curr)
    {
        delete curr;
        par->l = NULL;
        cout << "**********************DELETED SUCCESSFULLY ***************************\n";
        return;
    }
    else
    {
        delete curr;
        par->r = NULL;
        cout << "**********************DELETED SUCCESSFULLY ***************************\n";
        return;
    }
}
void dict::del_1(node *&curr, node *&par)
{
    if (par->l == curr)
    { //if t be delete node is left child of parent
        if (curr->l != NULL)
        {
            par->l = curr->l;
        }
        else
        {
            par->l = curr->r;
        }
        delete curr;
        cout << "**********************DELETED SUCCESSFULLY!!!!!!!!***************************\n";
    }
    else
    {
        if (curr->l != NULL)
        {
            par->r = curr->l;
        }
        else
        {
            par->r = curr->r;
        }
        delete curr;
        cout << "**********************DELETED SUCCESSFULLY!!!!!!!!***************************\n";
    }
}

void dict::del_node(node *ro)
{
    string n;
    cout << "Which word you want to delete ??\n";
    cin >> n;
    node *currnode;
    node *par;
    search(root, n, currnode, par);
    if (par == NULL)
    { //root node to delete
        if (currnode->l != NULL && currnode->r != NULL)
        {
            del_2(currnode, par);
        }
        else if (currnode->l != NULL)
        {
            root = currnode->l;
            delete currnode;
            cout << "************************SUCCESSFULLY DELETED****************************\n";
        }
        else if (currnode->r != NULL)
        {
            root = currnode->r;
            delete currnode;
            cout << "************************SUCCESSFULLY DELETED****************************\n";
        }
        else
        {
            delete currnode;
            cout << "************************SUCCESSFULLY DELETED****************************\n";
            root = NULL;
        }
    }
    else if (currnode->l != NULL && currnode->r != NULL) //case 3 having both childs
    {
        del_2(currnode, par);
    }
    else if (currnode->l != NULL || currnode->r != NULL) //case 2 having 1 child
    {
        del_1(currnode, par);
    }
    else // case 1 have 0 child
    {
        del_0(currnode, par);
    }
}

void dict::postorder(node *ro)
{
    if(root==NULL){
        cout<<"Tree is empty\n";
        return;
    }
    if (ro == NULL)
    {
        return;
    }
    postorder(ro->r);
    cout << ro->word << "  " << ro->mean << endl;
    postorder(ro->l);
}
void dict::inorder(node *ro)
{
    if(root==NULL){
        cout<<"Tree is empty\n";
        return;
    }
    if (ro == NULL)
    {
        return;
    }
    inorder(ro->l);
    cout << ro->word << "  " << ro->mean << endl;
    inorder(ro->r);
}

void dict::search(node *r, string key, node *&curr, node *&par)
{
    curr = r;
    par = NULL;
    while (curr != NULL)
    {
        if (curr->word == key)
        {
            return;
        }
        else if (curr->word < key)
        {
            par = curr;
            curr = curr->r;
        }
        else
        {
            par = curr;
            curr = curr->l;
        }
    }
    return;
}

void dict::create()
{
    string w, m;
    int count = 0;
    node *currnode;
    node *par;
    char op = 'y';
    while (op == 'y' || op == 'Y')
    {
        count++;
        cout << count << "] " << endl;
        cout << "Enter the word  :  ";
        cin >> w;
        cout << "Enter its meaning:  ";
        cin >> m;
        node *newnode = new node(w, m);
        search(root, w, currnode, par);
        if (par == NULL)
        {
            root = newnode;
        }
        else if (par->word > w)
        {
            par->l = newnode;
        }
        else
        {
            par->r = newnode;
        }
        cout << "----------------------------------------------------------------\n";
        cout << "Do you want to continue ??? (y/n) ";
        cin >> op;
    }
}

int main()
{
    dict obj;
    node *root;
    int op;
    while(1){
        cout << "\n\t-------------------------MENU---------------------------";
        cout << "\n1.Insert word"
                "\n2.search word"
                "\n3.Ascending order"
                "\n4.Descending Order"
                "\n5.Update Meaning"
                "\n6.Delete"
                "\n7.Quit";
        cout << "\nEnter choice:- ";
        cin>>op;
    cout << "*************************************************\n";
        switch (op)
        {
        case 1:
            obj.create();
            root=obj.get_root();
            break;
        
        case 2:
            obj.search_node();
            break;
        
        case 3:
            obj.inorder(root);
            break;
        
        case 4:
            obj.postorder(root);
            break;
        case 5:
            obj.update(root);
            break;
        
        case 6:
            obj.del_node(root);
            root=obj.get_root(); //if root get deleted.... therefor necessary to reinitialize the root
            break;
        
        case 7:
            exit(1);
            break;
        
        default:
        cout<<"Enter valid option\n";
            break;
        }
    }
}
