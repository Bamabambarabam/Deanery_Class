// Copyright 2024 HSE NN
// Author: Lev Pestov

#pragma once
#ifndef DEANERY_INCLUDE_STUDENT_H_
#define DEANERY_INCLUDE_STUDENT_H_

#include <cstdint>
#include <vector>
#include <string>
#include "Group.h"
class Group;


class Student {
 private:
  int64_t id;
  std::string fio;
  Group* group;
  std::vector<int64_t > marks;

 public:
  Student(const int64_t& id, const std::string& fio);
  void addToGroup(Group* group_);
  void addMark(int64_t mark);
  double getAverageMark();


  int64_t getId() const;
  const std::string& getFio() const;
  Group* getGroup() const;
  const std::vector<int64_t>& getMarks() const;

  void setId(int64_t id);
  void setFio(const std::string& fio);
  void setGroup(Group* group);
  void setMarks(const std::vector<int64_t>& marks);
};




#endif //DEANERY_INCLUDE_STUDENT_H_
