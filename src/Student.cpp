// Copyright 2024 HSE NN
// Author: Lev Pestov

#include "Student.h"

Student::Student(const int64_t &id, const std::string &fio) : id(id), fio(fio), group(nullptr) {}

void Student::addToGroup(Group *group_) {
  group = group_;
  group->addStudent(this);
}

void Student::addMark(int64_t mark) {
  marks.push_back(mark);
}

double Student::getAverageMark() {
  if (marks.empty()) {
    return 0.0;
  } else {
    int64_t sum = 0;
    for (int64_t mark : marks) {
      sum += mark;
    }
    return static_cast<double>(sum) / marks.size();
  }
}

int64_t Student::getId() const {
  return id;
}

const std::string &Student::getFio() const {
  return fio;
}

Group *Student::getGroup() const {
  return group;
}

const std::vector<int64_t> &Student::getMarks() const {
  return marks;
}

void Student::setId(int64_t id) {
  this->id = id;
}

void Student::setFio(const std::string &fio) {
  this->fio = fio;
}

void Student::setGroup(Group *group) {
  this->group = group;
}

void Student::setMarks(const std::vector<int64_t> &marks) {
  this->marks = marks;
}
