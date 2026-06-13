
import java.util.*;

public class StudentRepository {
    private List<Student> students;

    public StudentRepository(){
        students = new ArrayList<>();
    }
    public void add(Student s){
        students.add(s);
    }

    public List<Student> findAll(){
        return Collections.unmodifiableList(new ArrayList<>(students));
    }

}
