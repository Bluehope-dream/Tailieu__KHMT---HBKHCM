import java.util.*;

public class CohortStats {
    private final String cohort;
    private final int  total;
    private final Map<Classification, Integer> counts;
    private final int regularCount;
    private final int honorsCount;

    
    public CohortStats(String cohort,int  total, Map<Classification, Integer> counts,int regularCount,int honorsCount){
        if (cohort ==null || total < 0 ||counts ==null ||regularCount < 0 || honorsCount <0){
            throw  new IllegalArgumentException("");
        }
        this.cohort = cohort;
        this.total = total;
        this.counts = new HashMap<>(counts);
        this.regularCount = regularCount;
        this.honorsCount= honorsCount;
    }
    public String getCohort(){
        return cohort;
    }
    public int getTotal(){
        return total;
    }
    public Map<Classification, Integer> getCounts(){
        return counts;
    }
    public int getRegularCount(){
        return regularCount;
    }
    public int getHonorsCount(){
        return honorsCount;
    }


}
