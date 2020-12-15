#include <iostream>
#include <string>
#include "Student.h"

using std::string, std::vector, std::cout, std::endl; 



Student::Student(std::string student_id, std::string name) : id(student_id), name(name), course_ids({})
{
}

void Student::addCourse(string course_id){
    for(size_t i =0; i < course_ids.size(); i++){
        if(course_id == course_ids[i]){
            throw(std::invalid_argument("Course already in list"));
        }
    }
    course_ids.push_back(course_id);
}
std::ostream& operator<<(std::ostream& os, const Student& s){
    os << "ID: " << s.get_id() << ", " << s.get_name() << ", " << endl;  
    return os; 

}
void Student::listCourses(std::ostream& os) const
{
    os<< "Courses for " << id << endl;
    if(course_ids.size() == 0){
        os << "No courses" << endl; 
    }
    for(size_t i = 0; i < course_ids.size(); i++){
        os << course_ids[i] << endl; 
    }
}

