// import java.lang.*;
public class main {


    public static void main(String[] args) {
        
        // Test 01

        Transcript t1 = new Transcript();
        double gpa = t1.gpa4();
        if (0.0 == gpa){
            System.out.println("Passed");
        } else System.out.println("Failed");
        int count = t1.failedCount();
        if (count ==0){
            System.out.println("Passed");
        } else System.out.println("Failed");

        // Test 02
        Transcript t2 = new Transcript();
        t2.addCourseResult(new CourseResult("C1", 3, 8.5));
        if (4.0 == t2.gpa4()){
            System.out.println("Passed");
        } else System.out.println("Failed");

        if (t2.failedCount() ==0){
            System.out.println("Passed");
        } else System.out.println("Failed");

        // Test 03 
       
        Transcript t3 = new Transcript();
        t3.addCourseResult(new CourseResult("C1", 3, 4.0));
        if (1.0 ==t3.gpa4()){
            System.out.println("Passed T3 single failed GPA");
        } else System.out.println("Failed T3 single failed GPA");
        if (t3.failedCount() == 1){
            
            System.out.println("Passed T3 failed=1");
        }
         else System.out.println("Failed T3 failed=1");
        }

    
    
}
