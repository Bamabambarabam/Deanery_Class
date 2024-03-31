// Copyright 2024 HSE NN
// Author: Lev Pestov


#include <algorithm>
#include <cstdlib>
#include <ctime>
#include "Group.h"

Group::Group(const std::string& title, const std::string& spec) : title(title), spec(spec), head(nullptr) {}

void Group::addStudent(const Student* student) {
  students.push_back(const_cast<Student*>(student));
}

void Group::chooseHead() {
  if (!students.empty()) {
    double maxAverageMark = -1.0;
    Student* potentialHead = nullptr;
    for (Student* student : students) {
      double averageMark = student->getAverageMark();
      if (averageMark > maxAverageMark) {
        maxAverageMark = averageMark;
        potentialHead = student;
      }
    }
    head = potentialHead;
  }
}

bool Group::findStudent(const std::string& fio) {
  for (Student *student : students) {
    if (student->getFio() == fio) {
      return true;
    }
  }
  return false;
}

bool Group::findStudent(const int64_t& id) {
  for (Student *student : students) {
    if (student->getId() == id) {
      return true;
    }
  }
  return false;
}

double Group::getAverageMarkGroup() {
  if (students.empty()) {
    return 0.0;
  }
  double sum = 0.0;
  for (Student* student : students) {
    sum += student->getAverageMark();
  }
  return sum / students.size();
}

void Group::deleteStudent(Student* student) {
  for (int64_t i = 0; i < students.size(); ++i) {
    if (students[i] == student) {
      students.erase(students.begin() + i);
      break;
    }
  }
}


void Group::setTitle(const std::string& title) {
  this->title = title;
}

void Group::setSpec(const std::string& spec) {
  this->spec = spec;
}

void Group::setStudents(const std::vector<Student*>& students) {
  this->students = students;
}

void Group::setHead(Student* head) {
  this->head = head;
}

const std::string& Group::getTitle() const {
  return title;
}

const std::string& Group::getSpec() const {
  return spec;
}

const std::vector<Student*>& Group::getStudents() const {
  return students;
}

Student* Group::getHead() const {
  return head;
}