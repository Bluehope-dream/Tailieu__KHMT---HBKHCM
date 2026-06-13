
import java.util.*;



public class ReportingService {
    private StudentRepository repo;

    public ReportingService(StudentRepository repo){
        this.repo = repo;
    }

    public Map<Classification, List <Student>> groupByClassification(ClassificationPolicy policy){
        Map<Classification, List <Student>> result = new HashMap<>();

        List <Student> fullStudents = repo.findAll();

        for(Student s: fullStudents)
        {
            Classification cl = policy.classify(s);
            if (!result.containsKey(cl)){
                result.put(cl, new ArrayList<>());
            }

            result.get(cl).add(s);
        }

        return result;
    }
    public List <Student> topKByGpa(int k){
        List<Student> board = new ArrayList<>(repo.findAll());
        // Định nghĩ về bộ thứ tự so sánh 
        Comparator<Student> studentComparator = Comparator
        .comparingDouble(Student::getGpa4).reversed()
        // (b) Nếu GPA bằng, disciplineScore cao hơn xếp trước (descending)
        .thenComparing(Comparator.comparingInt(Student::getDisciplineScore).reversed())
        // (c) Nếu vẫn bằng, failedCount thấp hơn xếp trước (ascending)
        .thenComparingInt(Student::failedCount)
        // (d) Nếu vẫn bằng, EnglishName lớn hơn về từ điển (descending)
        .thenComparing(Student::getEnglishName, Comparator.reverseOrder());

        board.sort(studentComparator);
        int limit = Math.min(k,board.size());


        return board.subList(0, limit) ;

    }
    public CohortStats statsByCohort(String cohort,ClassificationPolicy policy){
        List<Student> board = new ArrayList<>(repo.findAll());
        int total =0;
        int regularCount=0;
        int honorsCount =0;
        Map<Classification,Integer> counts = new HashMap<>();

        for (Classification c : Classification.values()) {
            counts.put(c, 0);
        }
        for (Student s : board ) {
        // Lọc sv
        if (s.getCohort().equals(cohort)) {
            total++;
            
       
            Classification cl = policy.classify(s);
            counts.put(cl, counts.get(cl) + 1);

            if (s instanceof RegularStudent) regularCount++;
            else if (s instanceof HonorsStudent) honorsCount++;
        }
    }
   
        return new CohortStats(cohort, total, counts, regularCount, honorsCount);

    }

    
}
