#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  // delete head;
  Register* current = head;
  while (current != nullptr) {
      Register* next = current->get_next(); // Store next register
      delete current; // Delete the current register
      current = next; // Move to the next register
  }
}

Register* RegisterList::get_head() { 
  return head;
 }

int RegisterList::get_size() { 
  // return number of registers 
  return size;
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
  Register *temp = head;
  
  if (temp == nullptr) {
    return nullptr;
  } 

  Register *minReg = temp;
  temp = temp->get_next();

  while (temp != nullptr) {
    if (temp->get_queue_list()->get_items() < minReg->get_queue_list()->get_items()) {
      minReg = temp;
    }
    temp = temp->get_next();
  }

  return minReg;
  
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
  Register *search = head;
  while (search != nullptr) {
    if (search->get_queue_list()->get_head() == nullptr) {
      return search;
    }
    search = search->get_next();
  }

  return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  if (head == nullptr) {
    head = newRegister;
    newRegister->set_next(nullptr);
  } else {
    Register *temp = head;
    while (temp->get_next() != nullptr) {
      temp = temp->get_next();
    }
    temp->set_next(newRegister);
    newRegister->set_next(nullptr);
  }
  
  size++;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  Register *search = head;
  while (search != nullptr) {
    if (search->get_ID() == ID) {
      return true;
    }
  }

  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID
  if (head == nullptr) {
    return nullptr;
  }

  Register *current = head;
  Register *prev = nullptr;

  while (current != nullptr) {
    if (current->get_ID() == ID) {
      if (prev == nullptr) {
        head = current->get_next();
      } else {
        prev->set_next(current->get_next());
      }

      size--;
      return current;
    }

    prev = current;
    current = current->get_next();
  }

  return nullptr;
  // return the dequeued register
  // return nullptr if register was not found
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
    // Return the register with the minimum time of departure of its customer
    // If all registers are free, return nullptr
    if (head == nullptr) {
        return nullptr; // No registers
    }

    Register *temp = head;
    Register *minDepartRegister = nullptr; // Initially no register selected

    // Check the first register if it has customers
    double firstDepartTime = temp->calculateDepartTime();
    if (firstDepartTime != -1) {
        minDepartRegister = temp; // Set as the initial minimum if valid
    }

    // Move to the next register
    temp = temp->get_next();

    while (temp != nullptr) {
        double departTime = temp->calculateDepartTime();

        // Only consider registers with customers
        if (departTime != -1) {
            // Check if this is the first valid departure time found
            if (minDepartRegister == nullptr || departTime < minDepartRegister->calculateDepartTime()) {
                minDepartRegister = temp; // Update the register with the minimum departure time
            }
        }

        temp = temp->get_next(); // Move to the next register
    }

    return minDepartRegister; // Return the register with minimum departure time or nullptr
}


void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
