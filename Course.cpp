#include <iostream>
#include <string>
#include "Course.h"
#include "Date.h"
#include "AttendanceRecord.h"

using std::string, std::ostream, std::endl;




Course::Course(std::string id, std::string title, Date startTime, Date endTime) : id(id), title(title), startTime(startTime), endTime(endTime), attendanceRecords({})
{

}

void Course::addAttendanceRecord(AttendanceRecord ar)
{
    if(ar.getDate() <= endTime && ar.getDate() >= startTime){
        attendanceRecords.push_back(ar);
        return;
    }
    else{
        throw(std::invalid_argument("argument"));
    }

}

void Course::outputAttendance(std::ostream& os) const
{
    if(attendanceRecords.size() != 0){

    for(size_t i = 0; i < attendanceRecords.size(); i++){
            os << attendanceRecords[i].getDate().getDateTime() << "," << attendanceRecords[i].getCourseID() << "," << attendanceRecords[i].getStudentID()<< endl;

    }
    }
    else{
        os << "No records"<<endl; 
    }
}

void Course::outputAttendance(std::ostream& os, std::string student_id) const
{
    bool isThere = false;
    if(attendanceRecords.size() != 0){
        for(size_t i = 0; i < attendanceRecords.size(); i++){
            if(attendanceRecords[i].getStudentID() == student_id){
                isThere = true;
                os << attendanceRecords[i].getDate().getDateTime() << "," << attendanceRecords[i].getCourseID() << "," << student_id << endl; 
            }
            
    }
    }
    if(!isThere){
        os << "No records"<<endl; 
    }
    
    
}
