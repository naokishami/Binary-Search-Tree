// Student: Naoki Atkins
// Program 3


#include <iostream>
using namespace std;


class treeNode
{
public:
    string name;
    int weight;
    treeNode *left, *right;
    // default constructor
    treeNode ()
    {
        left = right = 0;
    }
    // constructor with parameterized values
    treeNode (string name, int weight, treeNode *l = 0, treeNode *r = 0)
    {
        this->name = name;
        this->weight = weight;
        left = l;
        right = r;
    }
};


class binarySearchTree
{
public:
    treeNode *root;
    binarySearchTree ()
    {
        root = 0;
    }
    // #1 method
    bool insert (string name, int weight)
    {
        // keep track of the parent and child node
        treeNode *temp = root, *prev = 0;
        // determine if the parent node equals to 0
        // if so, exit out of the loop
        while (temp != 0)
        {
            // assign child node equal to parent node
            prev = temp;
            // update parent node
            if (name < temp->name)
                temp = temp->left;
            else
                temp = temp->right;
        }
        // now that temp (parent node) equals to 0, we'll use the child node
        // as a reference to insert our new node.
        // assign child node to appropriate placement
        if (root == 0)
            root = new treeNode (name, weight);
        else if (name < prev->name)
            prev->left = new treeNode (name, weight);
        else if (name > prev->name)
            prev->right = new treeNode (name, weight);
        else
            return false;
        return true;
    }
    // #2 method
    void preOrder (treeNode *temp)
    {
        if (temp != 0)
        {
            cout << temp->name << " (" << temp->weight << ") ";
            preOrder(temp->left);
            preOrder(temp->right);
        }
    }
    // #3 method
    void inOrder (treeNode *temp)
    {
        if (temp != 0)
        {
            inOrder(temp->left);
            cout << temp->name << " (" << temp->weight << ") ";
            inOrder(temp->right);
        }
    }
    // #4 method
    void postOrder (treeNode *temp)
    {
        if (temp != 0)
        {
            postOrder(temp->left);
            postOrder(temp->right);
            cout << temp->name << " (" << temp->weight << ") ";
        }
    }
    // #5 method
    int findHeight (treeNode *node)
    {
        // later on, we'll add 1 to the subtree with the greater height
        // so, to balance the height, we assign a node that does not
        // point to anything to have a value of -1.
        if (node == nullptr)
            return -1;
        else
        {
            // recursively call node->left and node->right
            int leftHeight = findHeight (node->left);
            int rightHeight = findHeight (node->right);
            // find the subtree with the greater height and add 1 to it
            if (leftHeight > rightHeight)
                return leftHeight + 1;
            else
                return rightHeight + 1;
        }
    }
    // #6 method
    //      find number of leaves and return the result
    int getLeafCount (treeNode *node)
    {
        // check to see if node does not point to anything
        // if so, then return 0
        if (node == nullptr)
            return 0;
        // check to see if we have a leaf
        // if so, return 1
        if (node->left == nullptr && node->right == nullptr)
            return 1;
        // else, add the count of the left and right subtree
        else
            return getLeafCount(node->left) + getLeafCount(node->right);
    }
    // #7 method
    //      search function      find person with name and return weight
    //                           otherwise stating no match exists
    void searchPerson (string name)
    {
        // start with the root
        treeNode *temp = root;
        // dive down into the tree
        while (temp != 0)
        {
            if (temp->name == name)
            {
                cout << name << "'s weight is: " << temp->weight << endl;
                break;
            }
            else if (name > temp->name)
                temp = temp->right;
            else if (name < temp->name)
                temp = temp->left;
        }
        // if we dived down the tree and could not find a matching name,
        // then that means the name does not exist in the BST
        if (temp == 0)
            cout << name << " could not be found" << endl;
    }
    // #8 method
    //      determine the lowest weight in the tree
    void findLowestWeight (int lowest, treeNode *temp, treeNode *prev)
    {
        // dive down the tree
        // child goes down (temp)
        if (temp != 0)
        {
            // check to see if we have a lower weight
            if (temp->weight < lowest)
                lowest = temp->weight;
            // keep track of the child node
            prev = temp;
            // recursively go down the tree
            return findLowestWeight(lowest, temp->left, prev);
            return findLowestWeight(lowest, temp->right, prev);
        }
        // use the parent node to output the node with the lowest weight
        else
            cout << "The lowest weight is " << prev->name << " with a weight of " << prev->weight << endl;
    }
    // #9 method
    //      find first name in alphabetical order
    void firstAlphabet ()
    {
        // keep track of parent and child node
        treeNode *temp = root;  // child node
        treeNode *prev = 0;     // parent node
        // dive down to the left
        // child node goes down the tree
        while (temp != 0)
        {
            // parent keeps track of the child
            prev = temp;
            temp = temp->left;
        }
        // output the parent node
        cout << "First name in alphabetical order: " << prev->name << " (" << prev->weight << ")" << endl;
    }
};


int main ()
{
    binarySearchTree b = *new binarySearchTree();
    
    int numOfNodes;
    cout << "How many nodes would you like to insert? ";
    cin >> numOfNodes;
    
    string name;
    int weight;
    for (int i = 0; i < numOfNodes; i++)
    {
        cout << "Insert a name followed by weight: ";
        cin >> name >> weight;
        b.insert(name, weight);
    }
    
    cout << "\n\nIn-Order Traversal: " << endl;
    b.inOrder(b.root);
    
    cout << "\n\nPre-Order Traversal: " << endl;
    b.preOrder(b.root);
    
    cout << "\n\nPost-Order Traversal: " << endl;
    b.postOrder(b.root);
    
    cout << endl << endl;
    cout << "The height of the tree is: " << b.findHeight(b.root) << endl << endl;
    
    string searchName;
    cout << "Enter a name you would like to be searched: ";
    cin >> searchName;
    b.searchPerson(searchName);
    
    cout << endl;
    b.firstAlphabet();
    cout << endl;
    
    // assume the root has the lowest weight
    int lowest = b.root->weight;
    b.findLowestWeight(lowest, b.root, nullptr);
    cout << endl;
}

/*
 OUTPUT
 
 How many nodes would you like to insert? 6
 Insert a name followed by weight: Mike 100
 Insert a name followed by weight: Tom 75
 Insert a name followed by weight: Steve 99
 Insert a name followed by weight: Carry 58
 Insert a name followed by weight: Stephanie 82
 Insert a name followed by weight: George 42
 
 
 In-Order Traversal:
 Carry (58) George (42) Mike (100) Stephanie (82) Steve (99) Tom (75)
 
 Pre-Order Traversal:
 Mike (100) Carry (58) George (42) Tom (75) Steve (99) Stephanie (82)
 
 Post-Order Traversal:
 George (42) Carry (58) Stephanie (82) Steve (99) Tom (75) Mike (100)
 
 The height of the tree is: 3
 
 Enter a name you would like to be searched: Carry
 Carry's weight is: 58
 
 First name in alphabetical order: Carry (58)
 
 The lowest weight is Carry with a weight of 58
 
 Program ended with exit code: 0
 */
