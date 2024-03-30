// Copyright 2024 HSE NN
// Author: Lev Pestov


#pragma once
#ifndef DEANERY_INCLUDE_DEANERY_H_
#define DEANERY_INCLUDE_DEANERY_H_

#include <vector>
#include <string>
#include "Group.h"
#include "Student.h"

class Deanery {
 private:
  std::vector<Group*> groups;

 public:
  Deanery() = default;
  void createStudentsFromFile();
  void createGroupFromFile();
  void addMarksToAll();
  void GetStatistics();
  void moveStudents(int64_t studentId, const std::string& groupName);
  void expelStudent(int64_t studentId);
  void saveData();
  void displayData();

  std::vector<Group*> getGroups() const;

  void setGroups(const std::vector<Group*>& newGroups);
};

#endif //DEANERY_INCLUDE_DEANERY_H_
