



public class HonorsStudent extends Student{
    public HonorsStudent(String id, String fullName, String cohort,String major,int disciplineScore, Transcript transcript){
        super(id,fullName,cohort,major,disciplineScore,transcript);
    }
    @Override 
    public double tuitionDiscountRate(){
        double gpa = getGpa4();
        if (gpa >= 3.2 && disciplineScore >= 80){
            return 0.1;
        }
        return 0.0;
    }
    public boolean maintainsHonorsStatus(){
        return (getGpa4()>=3.2 && disciplineScore >= 75 && failedCount()==0)? true: false;
    }
}
