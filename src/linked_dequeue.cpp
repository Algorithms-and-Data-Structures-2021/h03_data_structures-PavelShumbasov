#include "linked_dequeue.hpp"

#include <stdexcept>  // logic_error

namespace itis {

void LinkedDequeue::Enqueue(Element e) {
  // TODO: напишите здесь свой код ...
    if(size_ == 0){
        auto *node = new DoublyNode(e, back_, nullptr);
        front_ = node;
        back_ = front_;
    }
    if (size_ > 0) {
        auto *node = new DoublyNode(e,back_, nullptr);
        back_->next = node;
        back_ = node;
    }
    size_++;
}

void LinkedDequeue::EnqueueFront(Element e) {
  // TODO: напишите здесь свой код ...
    if(size_ == 0){
        DoublyNode *new_node = new DoublyNode(e, nullptr, nullptr);
        back_ = new_node;
        front_ = new_node;
    }else{
        DoublyNode *new_node = new DoublyNode(e, nullptr, front_);
        front_->previous = new_node;
        front_ = new_node;
    }

    size_++;
}

void LinkedDequeue::Dequeue() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  // TODO: напишите здесь свой код ...
    if (size_ > 1) {
        DoublyNode *node_to_delete = front_;
        front_ = node_to_delete->next;
        delete node_to_delete;
    } 
    else {
        delete front_;
        front_ = nullptr;
        back_ = nullptr;
    }
    size_--;
}

void LinkedDequeue::DequeueBack() {
  if (size_ == 0) {
    throw std::logic_error("cannot not dequeue from empty queue");
  }

  // TODO: напишите здесь свой код ...
  else if (size_ == 1) {
      delete front_;
      front_ = nullptr;
      back_ = nullptr;
  }
  else {
      auto node = back_;
      back_ = node->previous;
      back_->next = nullptr;
      delete node;
  }
    size_--;
}

void LinkedDequeue::Clear() {
  // TODO: напишите здесь свой код ...
    auto *someKindNode = front_;
    while (someKindNode != nullptr) {
        auto nextNode = someKindNode->next;
        delete someKindNode;
        front_ = nextNode;
        someKindNode = front_;
        size_--;
    }
    back_ = nullptr;
}


// === РЕАЛИЗОВАНО ===

LinkedDequeue::~LinkedDequeue() {
  Clear();
}

std::optional<Element> LinkedDequeue::front() const {
  return front_ == nullptr ? std::nullopt : std::make_optional(front_->data);
}

std::optional<Element> LinkedDequeue::back() const {
  return back_ == nullptr ? std::nullopt : std::make_optional(back_->data);
}

bool LinkedDequeue::IsEmpty() const {
  return size_ == 0;
}

int LinkedDequeue::size() const {
  return size_;
}

// === НЕОБХОДИМО ДЛЯ ТЕСТИРОВАНИЯ ===

std::ostream &operator<<(std::ostream &os, const LinkedDequeue &queue) {
  os << "size: " << queue.size_ << '\n';
  for (auto current_node = queue.front_; current_node != nullptr; current_node = current_node->previous) {
    if (current_node == queue.front_) os << "[FRONT] ";
    if (current_node == queue.back_) os << "[BACK] ";
    os << enum2str(current_node->data) << '\n';
  }
  return os;
}

}  // namespace itis
