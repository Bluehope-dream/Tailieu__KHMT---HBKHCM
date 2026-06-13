public class main {

    // ===== assert kiểm tra int =====
    public static void assertEqInt(String testName, int expected, int actual){
        if (expected == actual){
            System.out.println(testName + " PASSED");
        } else {
            System.out.println(testName + " FAILED | Expected: " 
                               + expected + " | Actual: " + actual);
        }
    }

    // ===== assert kiểm tra exception =====
    public static void assertThrows(String testName, Class<?> expectedException, Runnable code){
        try {
            code.run();
            System.out.println(testName + " FAILED | No exception thrown");
        } catch (Throwable e){
            if (expectedException.isInstance(e)){
                System.out.println(testName + " PASSED");
            } else {
                System.out.println(testName + " FAILED | Wrong exception: " + e);
            }
        }
    }

    public static void main(String[] args) {

        // ===== Test 01 (trim) =====
        RegularStudent tc1 = new RegularStudent(
            "  S2  ", 
            "  Le Van An  ", 
            "  K20 ", 
            " CSE  ", 
            80, 
            new Transcript()
        );

        assertEqInt("TC1a id trimmed", 
            1, tc1.getId().equals("S2") ? 1 : 0);

        assertEqInt("TC1b name trimmed", 
            1, tc1.getFullName().equals("Le Van An") ? 1 : 0);

        assertEqInt("TC1c cohort trimmed", 
            1, tc1.getCohort().equals("K20") ? 1 : 0);

        assertEqInt("TC1d major trimmed", 
            1, tc1.getMajor().equals("CSE") ? 1 : 0);


        // ===== Test 02 =====
        RegularStudent tc3a = new RegularStudent("S4", "Le Van An", "K20", "CSE", 0, new Transcript());
        RegularStudent tc3b = new RegularStudent("S5", "Le Van An", "K20", "CSE", 100, new Transcript());

        assertEqInt("TC3a discipline=0 ok", 0, tc3a.getDisciplineScore());
        assertEqInt("TC3b discipline=100 ok", 100, tc3b.getDisciplineScore());


        // ===== Test 03 =====
        assertThrows("TC2 transcript=null rejected", 
            Throwable.class, 
            () -> new RegularStudent("S1", "Le Van An", "K20", "CSE", 80, null)
        );
    }
}