// Copyright 2024 HSE NN
// Author: Lev Pestov


#include "Deanery.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

void Deanery::createStudentsFromFile() {;
  std::ifstream file(R"(C:\Users\Leo\CLionProjects\Deanery\src\students.txt)");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    int64_t id;
    std::string surname, initials, groupTitle;
    if (!(iss >> id >> surname >> initials >> groupTitle)) {
      break;
    }
    Student *student = new Student(id, surname + " " + initials);
    for (Group *group : groups) {
      if (group->getTitle() == groupTitle) {
        group->addStudent(student);
        student->setGroup(group);
        break;
      }
    }
    int64_t mark;
    std::vector<int64_t> marks;
    while (iss >> mark) {
      marks.push_back(mark);
    }
    student->setMarks(marks);
  }
}

void Deanery::createGroupFromFile() {
  std::ifstream file(R"(C:\Users\Leo\CLionProjects\Deanery\src\groups.txt)");
  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string title, spec;
    if (!(iss >> title >> spec)) {
      break;
    }
    Group *group = new Group(title, spec);
    groups.push_back(group);
  }
}

void Deanery::addMarksToAll() {
  srand(time(0));
  for (Group *group : groups) {
    for (Student *student : group->getStudents()) {
      int64_t mark = rand() % 11;
      student->addMark(mark);
    }
  }
}

void Deanery::GetStatistics() {
  for (Group *group : groups) {
    std::cout << "Group: " << group->getTitle() << "\n";
    for (Student *student : group->getStudents()) {
      std::cout << "Student: " << student->getFio() << "\n";
      std::cout << "Marks: ";
      for (int64_t mark : student->getMarks()) {
        std::cout << mark << " ";
      }
      std::cout << "\n";
      std::cout << "Average Mark: " << std::fixed << std::setprecision(2) << student->getAverageMark() << "\n";
    }
    std::cout << "Group Average Mark: " << std::fixed << std::setprecision(2) << group->getAverageMarkGroup() << "\n\n";
  }
}

void Deanery::moveStudents(int64_t studentId, const std::string &groupName) {
  Student *studentMove = nullptr;
  Group *oldGroup = nullptr;

  for (Group *group : groups) {
    for (Student *student : group->getStudents()) {
      if (student->getId() == studentId) {
        studentMove = student;
        oldGroup = group;
        break;
      }
    }
    if (studentMove != nullptr) {
      break;
    }
  }
  if (studentMove == nullptr) {
    std::cout << "ERROR, NOT FOUND THIS STUDENT ID\n";
    return;
  }
  Group *newGroup = nullptr;
  for (Group *group : groups) {
    if (group->getTitle() == groupName) {
      newGroup = group;
      break;
    }
  }
  if (newGroup == nullptr) {
    std::cout << "ERROR, NOT FOUND GROUP NAME\n";
    return;
  }

  oldGroup->deleteStudent(studentMove);
  newGroup->addStudent(studentMove);
  studentMove->setGroup(newGroup);
}

void Deanery::expelStudent(int64_t studentId) {
  Student *studentExpel = nullptr;
  Group *groupOfStudent = nullptr;

  for (Group *group : groups) {
    for (Student *student : group->getStudents()) {
      if (student->getId() == studentId) {
        studentExpel = student;
        groupOfStudent = group;
        break;
      }
    }
    if (studentExpel != nullptr) {
      break;
    }
  }

  if (studentExpel == nullptr) {
    std::cout << "ERROR, NOT FOUND THIS STUDENT ID\n";
    return;
  }

  if (studentExpel->getAverageMark() < 4.0) {
    groupOfStudent->deleteStudent(studentExpel);
  } else {
    std::cout << "Student has an average mark of more than 4.\n";
  }
}

void Deanery::saveData() {
  // Save all data to files
}

void Deanery::displayData() {
  // Display all data in console
}

std::vector<Group *> Deanery::getGroups() const {
  return groups;
}

void Deanery::setGroups(const std::vector<Group *> &newGroups) {
  groups = newGroups;
}