// Copyright 2024 HSE NN
// Author: Lev Pestov


#include "Deanery.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

void Deanery::createStudentsFromFile(const std::string& filename) {;
  std::ifstream file(filename);
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

void Deanery::createGroupFromFile(const std::string& filename) {
  std::ifstream file(filename);
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

void Deanery::getStatistics() {
  for (Group *group : groups) {
    std::cout << "Group: " << group->getTitle() << "\n";
    std::cout << "Number of students: " << group->getStudents().size() << "\n";
    for (Student *student : group->getStudents()) {
      std::cout << "----------------\n";
      std::cout << "Student: " << student->getFio() << "\n";
      std::cout << "Marks: ";
      for (int64_t mark : student->getMarks()) {
        std::cout << mark << " ";
      }
      std::cout << "\n";
      std::cout << "Average Mark: " << std::fixed << std::setprecision(2) << student->getAverageMark() << "\n";
    }
    std::cout << "----------------\n";
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
  std::ofstream file(R"(C:\Users\Leo\CLionProjects\Deanery\src\data.txt)");
  if (!file) {
    std::cerr << "Unable to open file for writing.\n";
    return;
  }

  for (Group *group : groups) {
    file << "Group:" << group->getTitle() << ":" << group->getSpec() << "\n";
    if (group->getHead() != nullptr) {
      file << "Head:" << group->getHead()->getId() << ":" << group->getHead()->getFio() << "\n";
    } else {
      file << "Head:None\n";
    }
    for (Student *student : group->getStudents()) {
      file << "Student:" << student->getId() << ":" << student->getFio() << ":";
      for (int64_t mark : student->getMarks()) {
        file << mark << " ";
      }
      file << "\n";
    }
    file << "EndGroup\n";
  }

  file.close();
}

void Deanery::loadData() {
  std::ifstream file(R"(C:\Users\Leo\CLionProjects\Deanery\src\data.txt)");
  if (!file) {
    std::cerr << "Unable to open file for reading.\n";
    return;
  }

  std::string line;
  Group* currentGroup = nullptr;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string type;
    std::getline(iss, type, ':');

    if (type == "Group") {
      std::string title, spec;
      std::getline(iss, title, ':');
      std::getline(iss, spec);
      currentGroup = new Group(title, spec);
      groups.push_back(currentGroup);
    } else if (type == "Head" && currentGroup != nullptr) {
      int64_t id;
      std::string fio;
      char colon;
      iss >> id >> colon;
      std::getline(iss, fio);
      Student* head = new Student(id, fio);
      currentGroup->setHead(head);
    }else if (type == "Student" && currentGroup != nullptr) {
      int64_t id;
      std::string fio, marksStr;
      char colon;
      iss >> id >> colon;
      std::getline(iss, fio, ':');
      std::getline(iss, marksStr);
      std::istringstream marksIss(marksStr);
      std::vector<int64_t> marks;
      int64_t mark;
      while (marksIss >> mark) {
        marks.push_back(mark);
      }
      Student* student = new Student(id, fio);
      student->setMarks(marks);
      currentGroup->addStudent(student);
    } else if (type == "EndGroup") {
      currentGroup = nullptr;
    }
  }

  file.close();
}

void Deanery::displayData() {
  for (Group *group : groups) {
    std::cout << "Group Title: " << group->getTitle() << "\n";
    std::cout << "Speciality: " << group->getSpec() << "\n";
    if (group->getHead() != nullptr) {
      std::cout << "Head: " << group->getHead()->getFio() << "\n";
    } else {
      std::cout << "Head: None\n";
    }
    std::cout << "Students: \n";
    std::cout << "----------------\n";
    for (Student *student : group->getStudents()) {
      std::cout << "Student ID: " << student->getId() << "\n";
      std::cout << "Student: " << student->getFio() << "\n";
      std::cout << "Marks: ";
      for (int64_t mark : student->getMarks()) {
        std::cout << mark << " ";
      }
      std::cout << "\n";
      std::cout << "----------------\n";
    }
    std::cout << "\n";
  }
}

std::vector<Group *> Deanery::getGroups() const {
  return groups;
}

void Deanery::setGroups(const std::vector<Group *> &newGroups) {
  groups = newGroups;
}

