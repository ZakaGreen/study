package oop.skuska;

import java.util.Set;

public class CsvContactExporter implements ContactExporter{

    @Override
    public String export(Student student) {
        return String.format("%d; %s; %s", student.getId(), student.getName(), student.getEmail());
    }

    @Override
    public String export(Set<Student> students) {
        StringBuilder sb = new StringBuilder();
        sb.append("id; name; email\n");
        for (Student student : students) {
            sb.append(String.format("%d; %s; %s\n", student.getId(), student.getName(), student.getEmail()));
        }
        return sb.toString();
    }


// String export(Student student)
//            """
//            %s; %s
//            """

// String export(Set<Student> students) {
//                """
//                name; email
//                """;

}
