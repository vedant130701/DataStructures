//this code creates complete binary tree and all major forms of traversal present 
#include <bits/stdc++.h>
using namespace std;

#define SIZE 50

class node{
    public:
    int data;
    node *left, *right;
};

class Queue{
    public:
    int front, rear;
    int size;
    node **array;
};

node* newNode(int data){
    node *temp = new node();
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
} 

Queue* createQueue(int size){
    Queue* queue = new Queue();
    queue->front = queue->rear = -1;
    queue->size = size;
    queue->array = new node*[queue->size * sizeof(node*)];
    int i;
    for(i = 0; i<size; ++i){
        queue->array[i] = NULL;
    }
    return queue;
}

bool isEmptyQueue(Queue* queue){
    if(queue->front == -1){
        return true;
    }
    return false;
}

bool isFullQueue(Queue* queue){
    if(queue->rear == queue->size-1){
        return true;
    }
    return false;
}

bool singleElementQueue(Queue *queue){
    if(queue->rear == queue->front){
        return true;
    }
    return false;
}

void enqueue(Queue* queue, node* element){
    if(isFullQueue(queue)){
        return; 
    }
    queue->array[++queue->rear] = element;
    if(isEmptyQueue(queue)){
        ++queue->front;
    }
}

node* dequeue(Queue* queue){
    if(isEmptyQueue(queue)){
        return NULL;
    }
    node* temp = queue->array[queue->front];
    if(singleElementQueue(queue)){
        queue->front = queue->rear = -1;
    }
    else{
        ++queue->front;
    }
    return temp;
}

node* peekFront(Queue* queue){
    if(isEmptyQueue(queue)){
        return NULL;
    }
    return queue->array[queue->front];
}

void insert(node **root, int data, Queue* queue){
    node* temp = newNode(data);
    if(!*root){
        *root = temp;
    }
    else{
        node* front = peekFront(queue);
        if(!front->left){
            front->left = temp;
        }
        else if(!front->right){
            front->right = temp;
        }
        if(front && front->left && front->right){
            dequeue(queue);
        }
    }
    enqueue(queue, temp);
}

void levelOrder(node* root){
    Queue* queue = createQueue(SIZE);

    enqueue(queue,root);

    while(!isEmptyQueue(queue)){
        node* temp = dequeue(queue);
        cout<<temp->data<<" ";
        if(temp->left){
            enqueue(queue,temp->left);
        }
        if(temp->right){
            enqueue(queue,temp->right);
        }
    }
}

void inOrderRecursive(node* root){
    node* temp = root;
    if(root==NULL){
        return;
    }

    inOrderRecursive(temp->left);
    cout<<temp->data<<" ";
    inOrderRecursive(temp->right);

}

void inOrderIterative(node* root){
    stack<node*> s;
    node* curr = root;
    while(curr!= NULL || s.empty()==false){
        while(curr!=NULL){
            s.push(curr);
            curr=curr->left;
        }
        curr= s.top();
        s.pop();

        cout<<curr->data<<" ";
        curr = curr->right;
    }
}

void preOrderRecursive(node* root){
    if(root == NULL){
        return;
    }
    cout<<root->data<<" ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
}

void preOrderIterative(node* root){
    if(root == NULL){
        return;
    }
    stack<node*> s;
    s.push(root);
    while(s.empty()==false){
        node* n = s.top();
        s.pop();
        cout<<n->data<<" ";
        if(n->right){
            s.push(n->right);
        }
        if(n->left){
            s.push(n->left);
        }
    }
}

void postOrderRecursive(node* root){
    if(root==NULL){
        return;
    }
    postOrderRecursive(root->left);
    postOrderRecursive(root->right);
    cout<<root->data<<" ";
}

void postOrderIterative(node* root){
    if(root == NULL){
        return;
    }
    stack<node*> s;
    do{
        while(root){
            if(root->right){
                s.push(root->right);
            }
        s.push(root);
        root = root->left;
        }
        root = s.top();
        s.pop();
        if(root->right && s.top() == root->right){
            s.pop();
            s.push(root);
            root = root->right;
        }
        else{
            cout<<root->data<<" ";
            root = NULL;
        }
    }while(s.empty() == false);
}

int main(){
    node* root = NULL;
    Queue* queue = createQueue(SIZE);
    int i,choice,data;

    while(1){
        cout<<"Enter choice 1 to insert, 2 to display, 3 to exit:";
        cin>>choice;
        cout<<endl;
        switch(choice){
            case 1:
                cout<<"Enter element to be inserted:";
                cin>>data;
                insert(&root,data,queue);
                break;
            case 2:
                cout<<"Level Order:"<<endl;
                levelOrder(root);
                cout<<endl;
                cout<<"In Order recursive:"<<endl;
                inOrderRecursive(root);
                cout<<endl;
                cout<<"Iterative Inorder:"<<endl;
                inOrderIterative(root);
                cout<<endl;
                cout<<"Pre Order recursive:"<<endl;
                preOrderRecursive(root);
                cout<<endl;
                cout<<"Iterative Preorder:"<<endl;
                preOrderIterative(root);
                cout<<endl;
                cout<<"Post Order recursive:"<<endl;
                postOrderRecursive(root);
                cout<<endl;
                cout<<"Iterative Postorder:"<<endl;
                postOrderIterative(root);
                cout<<endl;
                break;
            case 3:
                return 0;
            default:
                cout<<"Wrong choice entered\n";
                break;
        }
    }
    return 0;
}