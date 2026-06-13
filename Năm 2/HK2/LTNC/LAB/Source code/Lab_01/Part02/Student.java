import  java.lang.*;
public abstract  class Student{
    protected String id;
    protected String fullName;
    protected String cohort;
    protected String major;
    protected int disciplineScore;
    protected Transcript transcript;

    protected Student (String id, String fullName, String cohort,String major,int disciplineScore, Transcript transcript){
        if (id == null || id.trim().isEmpty()) 
            throw new IllegalArgumentException("");
        if (fullName == null || fullName.trim().isEmpty())
            throw new IllegalArgumentException("");
        if (cohort == null || cohort.trim().isEmpty())
            throw new IllegalArgumentException("");
        if (major == null || major.trim().isEmpty())
            throw new IllegalArgumentException("");
        if (disciplineScore < 0 || disciplineScore > 100)
            throw new IllegalArgumentException("");
        if (transcript == null)
            throw new IllegalArgumentException("");

        this.id =  id.trim();
        this.fullName = fullName.trim();
        this. cohort = cohort.trim();
        this.major =  major.trim();
        this.disciplineScore = disciplineScore;
        this.transcript = transcript;
    }
    public String getId(){
        return id;
    }
    public String getFullName(){
        return fullName;
    }
    public String getCohort(){
        return cohort;
    }
    public String getMajor(){
        return major;
    }
    public int getDisciplineScore( ){
        return  disciplineScore;
    }
    protected Transcript getTranscript (){
        return transcript;
    }
    public void setCohort(String cohort){
        this.cohort=cohort;
    }
    public void setMajor(String major ){
        this.major= major;
    }
    public void setDisciplineScore(int score){
        this.disciplineScore = score;
    }
    public String getEnglishName(){
        String[] parts = fullName.trim().split("\\s+");  // tách lấy chuỗi của các part 

        String familyName = parts[0]; // họ

        StringBuilder givenName = new StringBuilder();

        for (int i = 1; i < parts.length; i++){
            givenName.append(parts[i]);
            if (i != parts.length - 1){
                givenName.append("-");
            }
        }   

        return givenName.toString() + " " + familyName;
    }
    
    public double getGpa4(){
        return transcript.gpa4();
    }
    public int failedCount(){
        return transcript.failedCount();
    }
    public abstract double tuitionDiscountRate();

}