// Copyright 2024 HSE NN
// Author: Lev Pestov


#include <string>
#include <iostream>
#include <vector>
#include "Deanery.h"
#include "Group.h"
#include "Student.h"

int main() {
  // --< test Student and Group Class >--
  Student student; // create student
  student.setId(123); // set id
  if (student.getId() != 123) { // check id
    std::cout << "Test setId/getId failed\n";
  }

  student.setFio("Ivanov Ivan"); // set fio
  if (student.getFio() != "Ivanov Ivan") { // check fio
    std::cout << "Test setFio/getFio failed\n";
  }

  Group group("Test Group", "Test Spec"); // create group
  student.addToGroup(&group); // add student to group
  if (student.getGroup() != &group) { // check group
    std::cout << "Test setGroup/getGroup failed\n";
  }

  std::vector<int64_t> marks = {5, 4, 3, 2, 1}; // create marks
  student.setMarks(marks); // set marks
  if (student.getMarks() != marks) { // check marks
    std::cout << "Test setMarks/getMarks failed\n";
  }

  student.addMark(5); // add mark
  if (student.getMarks().back() != 5) { // check add mark
    std::cout << "Test addMark failed\n";
  }

  if (abs(student.getAverageMark() - 3.33) > 0.01) { // check average mark
    std::cout << "Test getAverageMark failed\n";
  }

  group.setTitle("Test Group"); // set title
  if (group.getTitle() != "Test Group") { // check title
    std::cout << "Test setTitle/getTitle failed\n";
  }

  group.setSpec("Test Spec"); // set spec
  if (group.getSpec() != "Test Spec") { // check spec
    std::cout << "Test setSpec/getSpec failed\n";
  }

  Student student1(1, "Student 1"); // create student1
  Student student2(2, "Student 2"); // create student2
  std::vector<Student*> students = {&student1, &student2}; // create vector students
  group.setStudents(students); // add students to group
  if (group.getStudents() != students) { // check students
    std::cout << "Test setStudents/getStudents failed\n";
  }

  group.setHead(&student1); // set head
  if (group.getHead() != &student1) { // check head
    std::cout << "Test setHead/getHead failed\n";
  }

  Student student3(3, "Student 3"); // create student3
  group.addStudent(&student3); // add student3
  if (group.getStudents().back() != &student3) { // check add student
    std::cout << "Test addStudent failed\n";
  }

  group.chooseHead(); // choose head
  if (group.getHead() == nullptr) { // check choose head
    std::cout << "Test chooseHead failed\n";
  }

  if (!group.findStudent("Student 3")) { // find student by name
    std::cout << "Test findStudent by name failed\n";
  }

  if (!group.findStudent(3)) { // find student by id
    std::cout << "Test findStudent by id failed\n";
  }

  group.deleteStudent(&student3); // delete student3
  if (group.findStudent(3)) { // check delete student
    std::cout << "Test deleteStudent failed\n";
  }
  // --< test Deanery Class >--
  Deanery deanery;
  deanery.createGroupFromFile(R"(C:\Users\Leo\CLionProjects\Deanery\bd\groups.txt)"); // create groups
  deanery.createStudentsFromFile(R"(C:\Users\Leo\CLionProjects\Deanery\bd\students.txt)"); // create students
  deanery.getStatistics(); // check that the marks
  deanery.addMarksToAll(); // add marks to all students
  deanery.getStatistics(); // check that the average mark has changed


  // Test moveStudents
  deanery.moveStudents(0, "23CST-6"); // Test moveStudents
  deanery.getStatistics("23CST-6"); // check that the student has moved
  deanery.getStatistics("23CST-5");

  return 0;
}
