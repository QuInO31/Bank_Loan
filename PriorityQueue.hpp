#pragma once
#include <iostream>
template <typename T>
class PriorityQueue
{
    LinkedList<T> customers_;

public:

    bool is_empty() const {
        return customers_.empty();
    }

    size_t size() const {
        return customers_.size();
    }

    void insert_with_priority(const T& elem) {

        if (customers_.empty()) {
            customers_.push_back(elem);
        }
        else {
            typename LinkedList<T>::Node* tmp = customers_.begin();

            while (tmp != nullptr) {
                if (tmp->data == elem) {
                    throw std::string("Error: Customer already exists!");
                }
                else if (tmp->data > elem) {
                    break;
                }
                else {
                    tmp = tmp->next;
                }
            }

            if (tmp == customers_.begin()) {
                customers_.push_front(elem);
            }
            else if (tmp == nullptr) {
                customers_.push_back(elem);
            }
            else {
                typename LinkedList<T>::Node* newNode = new typename LinkedList<T>::Node();
                newNode->data = elem;

                auto* prevNode = tmp->previous;
                auto* nextNode = tmp->next;

                prevNode->next = newNode;
                newNode->previous = prevNode;

                tmp->previous = newNode;
                newNode->next = tmp;
            }
        }
    }

    T pull_highest_priority_element() {
        return customers_.pop_front();
    }

    T peek()
    {
        auto* begin_ = customers_.begin();
        return begin_->data;
    }

    void print() {
        auto* begin_ = customers_.begin();
        int counter = 1;
        while (begin_ != nullptr) {
            std::cout << "Customer " << counter << " : " << (begin_->data).tostring() << "\n";
            begin_ = begin_->next;
            counter++;
        }
    }

    void printToFile(std::ofstream& f) {
        auto* beg_ = customers_.begin();
        int counter = 1;
        while (beg_ != nullptr) {
            f << (beg_->data).toFile() << std::endl;
            beg_ = beg_->next;
            counter++;
        }
    }
};


