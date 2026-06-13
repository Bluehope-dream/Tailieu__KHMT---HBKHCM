
import java.lang.*;
import java.util.*;

public class Transcript {
    private List<CourseResult> results;

    public Transcript(){
        this.results = new ArrayList<>();
    }
  
    public void addCourseResult(CourseResult r){
        if (r == null){
            throw new NullPointerException("");
        }
        results.add(r);
    }
    public double point4Converted(double score){
        if (score >= 8.5){
            return 4.0;
        } else if (score >=7.0){
            return 3.0;
        } else if (score >= 5.5){
            return 2.0;
        } else if (score >=4.0){
            return 1.0;
        } 
        return 0.0;
    }
    public double gpa4(){
        if (this.results == null){
            throw new NullPointerException("");
        }
        if (results.isEmpty() ){
            return 0.0;
        }
        double sum =0.0;
        double credits =0.0;
        for (CourseResult r : results){
            sum += point4Converted(r.getScore()) * r.getCredits();
            credits  += r.getCredits();
        }
        double  gpa = sum / credits;
        return Math.round(gpa*10.0) / 10.0;

    }
    public int failedCount(){
        if (results.isEmpty() || results == null){
            return 0;
        }
        int count =0;
        for (CourseResult r : results){
            if (r.getScore() < 5.0){
                count++;
            }
        }
        return count;

    }
    public List<CourseResult> getResults(){
        return Collections.unmodifiableList(results);
    }
}
