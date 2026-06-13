

public class RegularStudent extends Student{
    public RegularStudent(String id, String fullName, String cohort,String major,int disciplineScore, Transcript transcript){
        super(id,fullName,cohort,major,disciplineScore,transcript);
    }
    @Override
    public double tuitionDiscountRate(){
        return 0.0;
    }
    public boolean  eligibleForHonorsUpgrade(){
        return (getGpa4() >= 3.4 && this.disciplineScore >= 85 && this.failedCount() == 0)? true : false;
    }
} 
