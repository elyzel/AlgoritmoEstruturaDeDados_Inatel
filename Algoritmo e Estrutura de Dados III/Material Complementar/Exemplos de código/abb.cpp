#include<iostream>
#include<list>
using namespace std;
struct node{
  int data;
  struct node * left;
  struct node * right;
};

void insert(node * & current, int data){
  if(current == NULL){
    current = new node;
    current->data = data;
    current->left = NULL;
    current->right = NULL;
  } else if( data < current->data ){
    insert(current->left, data);
  } else {
    insert(current->right, data);
  }
}

node * search(node * current, int data){
  if(current == NULL){
    return NULL;
  } else if(data == current->data){
     return current;
  } else {
    if(data < current->data){
      return search(current->left, data);
    } else {
      return search(current->right, data);
    }
  }
}

node * find_less_save_right(node * & current) {
  if(current->left != NULL) {
    return find_less_save_right(current->left);
  } else {
    node * copy = current;
    current = current->right;
    return copy;
  }
}

bool remove(node * & current, int data){
  if(current == NULL){
    return false;
  } else if(data == current->data){
    node * temp = current;
    if (current->right == NULL) {
      current = current->left;
    } else if (current->left == NULL) {
      current = current->right;
    } else {
      temp = find_less_save_right(current->right);
      current->data = temp->data;
    }
    delete(temp);
    return true;
  } else {
    if(data < current->data){
      return remove(current->left, data);
    } else {
      return remove(current->right, data);
    }
  }
}

void show_in_level(node * current){
  if(current == NULL) {
    cout << "Empty Tree" << endl;
    return;
  }
  list<node*> visit_list;
  visit_list.push_back(current);
  while(!visit_list.empty()) {
    node * temp = visit_list.front();
    cout << temp->data << " ";
    if (temp->left != NULL) visit_list.push_back(temp->left);
    if (temp->right != NULL) visit_list.push_back(temp->right);
    visit_list.pop_front();
  }
}

void show_in_order(node * current) {
  if (current != NULL) {
    if (current->left != NULL) {
      show_in_order(current->left);
    }
    cout << current->data << " ";
    if (current->right != NULL) {
      show_in_order(current->right);
    }
  }
}

void destruct(node * & current) {
  if (current != NULL) {
    if (current->left != NULL) {
      destruct(current->left);
    }
    if (current->right != NULL) {
      destruct(current->right);
    }
    delete(current);
  }
}

int main(){
  node * root = NULL;

  insert(root, 34);
  insert(root, 13);
  insert(root, 9);
  insert(root, 12);
  insert(root, 8);

  node * result = search(root, 56);
  if(result == NULL){
    cout << "Element not found" << endl;
  } else {
    cout << "Element " << result->data << " found" << endl;
  }

  result = search(root, 13);
  if(result == NULL){
    cout << "Element not found" << endl;
  } else {
    cout << "Element " << result->data << " found" << endl;
  }

  bool result_status = remove(root, 13);
  if(result_status == NULL){
    cout << "Element not found" << endl;
  } else {
    cout << "Element removed" << endl;
  }

  result_status = remove(root, 13);
  if(result_status == NULL){
    cout << "Element not found" << endl;
  } else {
    cout << "Element removed" << endl;
  }

  result = search(root, 13);
  if(result == NULL){
    cout << "Element not found" << endl;
  } else {
    cout << "Element " << result->data << " found" << endl;
  }

  show_in_level(root);

  cout << endl;

  show_in_order(root);

  destruct(root);

  return 0;
}