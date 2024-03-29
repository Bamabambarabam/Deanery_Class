// Copyright 2024 HSE NN
// Author: Lev Pestov


#pragma once

#ifndef DEANERY_INCLUDE_GROUP_H_
#define DEANERY_INCLUDE_GROUP_H_
#include <string>
#include <vector>
#include "Student.h"
class Student;


class Group {
 private:
  std::string title;
  std::string spec;
  std::vector<Student*> students;
  Student* head;

 public:
  Group(const std::string& title, const std::string& spec);

  void addStudent(const Student* student);
  void chooseHead();
  bool findStudent(const std::string& fio);
  bool findStudent(const int64_t& id);
  double getAverageMarkGroup();
  void deleteStudent(Student* student);


  void setTitle(const std::string& title);
  void setSpec(const std::string& spec);
  void setStudents(const std::vector<Student*>& students);
  void setHead(Student* head);

  const std::string& getTitle() const;
  const std::string& getSpec() const;
  const std::vector<Student*>& getStudents() const;
  Student* getHead() const;
};


#endif //DEANERY_INCLUDE_GROUP_H_
