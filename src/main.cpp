// Copyright 2024 HSE NN
// Author: Lev Pestov


#include <string>
#include <iostream>
#include <vector>
#include "Deanery.h"
#include "Group.h"
#include "Student.h"

int main() {
  // Создаем студентов
  Student* student1 = new Student(1, "Ivanov Ivan");
  Student* student2 = new Student(2, "Petrov Petr");
  Student* student3 = new Student(3, "Sidorov Sidr");

  // Добавляем оценки студентам
  student1->addMark(5);
  student1->addMark(4);
  student2->addMark(3);
  student2->addMark(5);
  student3->addMark(4);
  student3->addMark(4);

  // Создаем группу
  Group* group = new Group("Group 1", "Spec 1");

  // Добавляем студентов в группу
  group->addStudent(student1);
  group->addStudent(student2);
  group->addStudent(student3);

  // Выбираем старосту
  group->chooseHead();

  // Выводим информацию о группе
  std::cout << "Group title: " << group->getTitle() << std::endl;
  std::cout << "Group spec: " << group->getSpec() << std::endl;
  std::cout << "Group average mark: " << group->getAverageMarkGroup() << std::endl;
  std::cout << "Group head: " << group->getHead()->getFio() << std::endl;

  // Проверяем наличие студентов в группе
  std::cout << "Is Ivanov in the group? " << (group->findStudent("Ivanov Ivan") ? "Yes" : "No") << std::endl;
  std::cout << "Is Petrov in the group? " << (group->findStudent("Petrov Petr") ? "Yes" : "No") << std::endl;
  std::cout << "Is Sidorov in the group? " << (group->findStudent("Sidorov Sidr") ? "Yes" : "No") << std::endl;

  // Удаляем студента из группы
  group->deleteStudent(student1);

  // Проверяем наличие студента в группе после удаления
  std::cout << "Is Ivanov in the group after deletion? " << (group->findStudent("Ivanov Ivan") ? "Yes" : "No") << std::endl;

  // Освобождаем память
  delete student1;
  delete student2;
  delete student3;
  delete group;

  return 0;
}
