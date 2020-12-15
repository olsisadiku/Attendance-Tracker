#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "School.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::ifstream, std::istringstream, std::endl, std::cout;

School::School(): courses({}), students({})
{

}

void School::addStudents(string filename)
 {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw std::invalid_argument("addStudents: can't open file");
  }
  while (!ifs.eof()) {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    string name;
    getline(ss, name);
    if (!ss.fail()) {
        Student student(uin, name);
        bool exists = false;
        for (Student s : students) {
            if (s == student) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            students.push_back(student);
        }
    }
  }
}

void School::addCourses(string filename)
{
  ifstream ifs(filename);
  if(!ifs.is_open()){
    throw(std::invalid_argument("File does not open"));
  }
  while(!ifs.eof()){
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string uin;
    getline(ss, uin, ',');
    if(uin.empty()){
      break;
    }
    string start;
    getline(ss, start, ',');
    // start time
    int start_hour = std::stoi(start.substr(0, start.find(":")));
    int start_min = std::stoi(start.substr(start.find(":")+1, start.size()));
  
    string end;
    getline(ss,end,',');
    // end time 
    int end_hour = std::stoi(end.substr(0, end.find(":")));
    int end_min = std::stoi(end.substr(end.find(":")+1, end.size()));

    string title;
    getline(ss,title);
    Date startt(start_hour, start_min,0);
    Date endt(end_hour, end_min,0);

    Course course(uin, title, startt, endt);
    courses.push_back(course);

  }
}

bool School::isEnrolled(std::string student_id) const
{
  for(size_t i = 0; i < students.size(); i++)
  {
    if(student_id == students[i].get_id()){
      return true; 
    }
  }
  return false; 
}

unsigned int School::addAttendanceData(std::string filename)
{
  ifstream ifs(filename);
  if(!ifs.is_open())
  {
    throw(std::invalid_argument("invalid"));
  }
  int cnt = 0; 
  
  while (!ifs.eof())
  {
    string line;
    getline(ifs, line);
    istringstream ss(line);
    string date;
    ss >> date;
     
    // date
    if(date.find('-') == string::npos){
      break; 
    }
    int month;
    int day; 
    int year; 
    year = std::stoi(date.substr(0, 4));
    month = std::stoi(date.substr(5,7));
    day = std::stoi(date.substr(8,10));
    
    
    ///
    string time; 
    getline(ss,time, ',');
    // time
    int hour; 
    hour = std::stoi(time.substr(1,3));
    int min; 
    
    min = std::stoi(time.substr(4,6));
    
    int sec;
    
    sec = std::stoi(time.substr(7,9));
    ///

    string course_id;
    
    getline(ss,course_id,',');
    
    string student_id;
    
    getline(ss,student_id, ',');

    Date datest(year,month,day,hour,min,sec);
    bool isThere = false;
    for(size_t i = 0; i < students.size(); i++){
      if(students[i].get_id() == student_id ){
        isThere = true; 
      }
    }
    bool is = false; 
    for(size_t j = 0; j < courses.size(); j++){
      if(courses[j].getID() == course_id ){
        is = true; 
      }
    }
    if(!isThere){
        cnt++;
        continue; 
    }
    if(!is){
      cnt++;
      continue; 
    }
    if(!datest.isValid()){
      cnt++;
      continue;
    }
    AttendanceRecord ar(course_id, student_id, datest);


    for(size_t i = 0; i < courses.size(); i++){
      if(courses[i].getID() == course_id){
          courses[i].addAttendanceRecord(ar);
      }
    }

  }
  


  return cnt; 
}

void School::listCourses(std::ostream& os) const
{
  if(courses.size()== 0){
    os << "No courses"<<endl;
  }
  else{
    for(size_t i =0; i < courses.size();i++){
      Date time = courses[i].getStartTime();
      Date time2= courses[i].getEndTime();
      os << courses[i].getID() << "," << time.getTime(false) << "," << time2.getTime(false) << "," << courses[i].getTitle()<<endl;
    }
  }
}

void School::listStudents(std::ostream& os) const
{
  if(students.size() == 0){
    os << "No students"<<endl; 
  }
  for(size_t i = 0; i < students.size(); i++)
  {
    os << students[i].get_id() << "," << students[i].get_name()<<endl;
  }
}

void School::outputCourseAttendance(std::ostream& os, std::string course_id) const
{
  for(size_t i = 0; i < courses.size(); i++){
    if(courses[i].getID() == course_id){
      courses[i].outputAttendance(cout) ;
    }
  }
  os<<"";
}
void School::outputStudentAttendance(std::ostream& os, std::string student_id, std::string course_id) const
{
  for(size_t i = 0; i < courses.size(); i++){
    if(courses[i].getID() == course_id){
      courses[i].outputAttendance(cout, student_id);
    }
  }
  os<<"";
}


