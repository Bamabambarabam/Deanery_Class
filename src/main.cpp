// Copyright 2024 HSE NN
// Author: Lev Pestov


#include <string>
#include <iostream>
#include <vector>
#include "Deanery.h"
#include "Group.h"
#include "Student.h"

int main() {
  Student student;
  student.setId(123);
  if (student.getId() != 123) {
    std::cout << "Test setId/getId failed\n";
  }

  student.setFio("Ivanov Ivan");
  if (student.getFio() != "Ivanov Ivan") {
    std::cout << "Test setFio/getFio failed\n";
  }

  Group group("Test Group", "Test Spec");
  student.addToGroup(&group);
  if (student.getGroup() != &group) {
    std::cout << "Test setGroup/getGroup failed\n";
  }

  std::vector<int64_t> marks = {5, 4, 3, 2, 1};
  student.setMarks(marks);
  if (student.getMarks() != marks) {
    std::cout << "Test setMarks/getMarks failed\n";
  }

  student.addMark(5);
  if (student.getMarks().back() != 5) {
    std::cout << "Test addMark failed\n";
  }

  if (abs(student.getAverageMark() - 3.33) > 0.01) {
    std::cout << "Test getAverageMark failed\n";
  }

  group.setTitle("Test Group");
  if (group.getTitle() != "Test Group") {
    std::cout << "Test setTitle/getTitle failed\n";
  }

  group.setSpec("Test Spec");
  if (group.getSpec() != "Test Spec") {
    std::cout << "Test setSpec/getSpec failed\n";
  }

  Student student1(1, "Student 1");
  Student student2(2, "Student 2");
  std::vector<Student*> students = {&student1, &student2};
  group.setStudents(students);
  if (group.getStudents() != students) {
    std::cout << "Test setStudents/getStudents failed\n";
  }

  group.setHead(&student1);
  if (group.getHead() != &student1) {
    std::cout << "Test setHead/getHead failed\n";
  }

  Student student3(3, "Student 3");
  group.addStudent(&student3);
  if (group.getStudents().back() != &student3) {
    std::cout << "Test addStudent failed\n";
  }

  group.chooseHead();
  if (group.getHead() == nullptr) {
    std::cout << "Test chooseHead failed\n";
  }

  if (!group.findStudent("Student 3")) {
    std::cout << "Test findStudent by name failed\n";
  }

  if (!group.findStudent(3)) {
    std::cout << "Test findStudent by id failed\n";
  }

  group.deleteStudent(&student3);
  if (group.findStudent(3)) {
    std::cout << "Test deleteStudent failed\n";
  }

  return 0;
}
