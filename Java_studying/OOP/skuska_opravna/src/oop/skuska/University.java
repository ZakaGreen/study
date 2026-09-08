package oop.skuska;


import java.util.Set;

public class University {
    private Set<Student> students;
    private ContactExporter exporter;
    private String name;

    public University(String name) {
        this.name = name;
    }

    public void addStudent(Student student){
        students.add(student);
    }
// void addStudent(student)

// void setExporter(exporter)

// String exportStudents()

}
