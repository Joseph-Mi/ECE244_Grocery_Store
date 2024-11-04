#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  delete head;
}

Customer* QueueList::get_head() { return head; }

void QueueList::enqueue(Customer* customer) {
  Customer *newCustomer = new Customer(*customer);

  if (head == nullptr) {
    head = newCustomer;
  } else {
    Customer *temp = head;
    while (temp->get_next() != nullptr) {
      temp = temp->get_next();
    }
    temp->set_next(newCustomer);
  }

  
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  if (head == nullptr) {
    return nullptr;
  } else {
    Customer *temp = head;
    head = head->get_next();
    temp->set_next(nullptr);
    return temp;
  }
  // and return a pointer to it
  
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int total = 0;
  Customer *temp = head;

  while (temp != nullptr) {
    total += temp->get_numOfItems();
    temp = temp->get_next();
  }

  return total;
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
