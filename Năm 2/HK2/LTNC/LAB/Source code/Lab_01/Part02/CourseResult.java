import java.lang.*;

public class CourseResult implements GradedItem {
    
    private String courseId;
    private int credits;
    private double score;

    public CourseResult(String id, int credit, double score) {
        if (id == null|| id.trim().isEmpty()  || credit <=0 || score >10 || score <0){
            throw new IllegalArgumentException("");
        }
        this. courseId = id;
        this.credits = credit;
        this.score = score;
    }

    public String getCoureId(){
        return this.courseId;
    }
    @Override
    public int getCredits(){
        return this.credits;
    }
    @Override
    public double getScore(){
        return this.score;
    }

}
