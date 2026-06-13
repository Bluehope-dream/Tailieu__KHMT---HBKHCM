public class main {
    public static void main(String[] args) {
        // 1. Tạo dữ liệu học tập (Transcript)
        // Sinh viên A: Học khá, không rớt môn
        Transcript trA = new Transcript();
        trA.addCourseResult(new CourseResult("CS101", 3, 8.0)); // 3.0 điểm hệ 4
        trA.addCourseResult(new CourseResult("CS102", 3, 7.5)); // 3.0 điểm hệ 4
        // GPA hệ 4: (3.0*3 + 3.0*3) / 6 = 3.0

        // Sinh viên B: Học giỏi nhưng rớt 1 môn
        Transcript trB = new Transcript();
        trB.addCourseResult(new CourseResult("CS101", 3, 9.0)); // 4.0 điểm hệ 4
        trB.addCourseResult(new CourseResult("CS102", 2, 4.5)); // 1.0 điểm hệ 4, RỚT (4.5 < 5.0)
        // GPA hệ 4: (4.0*3 + 1.0*2) / 5 = 2.8

        // 2. Khởi tạo các loại sinh viên
        Student regularStu = new RegularStudent("SV01", "Nguyen Van A", "K2022", "CS", 90, trA);
        Student honorsStu = new HonorsStudent("SV02", "Tran Thi B", "K2022", "CS", 85, trB);

        // 3. Khởi tạo các chính sách phân loại (Exercise 3)
        ClassificationPolicy standardPolicy = new StandardPolicy();
        ClassificationPolicy strictPolicy = new StrictPolicy();

        // 4. Chạy Test Case
        System.out.println("=== TEST EXERCISE 3: STUDENT POLICIES ===");
        
        // --- Kiểm tra Sinh viên A (GPA 3.0, Rớt 0) ---
        System.out.println("\n--- Student A (GPA: " + regularStu.getGpa4() + ", Failed: " + regularStu.failedCount() + ") ---");
        // Standard: 2.5 <= 3.0 < 3.2 => FAIR
        System.out.println("Standard Policy: " + standardPolicy.classify(regularStu)); 
        // Strict: 2.7 <= 3.0 < 3.3 => FAIR
        System.out.println("Strict Policy:   " + strictPolicy.classify(regularStu));

        // --- Kiểm tra Sinh viên B (GPA 2.8, Rớt 1) ---
        System.out.println("\n--- Student B (GPA: " + honorsStu.getGpa4() + ", Failed: " + honorsStu.failedCount() + ") ---");
        // Standard: FAIL nếu rớt >= 2 hoặc GPA < 2.0. Ở đây rớt 1, GPA 2.8 => FAIR (2.5 <= 2.8 < 3.2)
        System.out.println("Standard Policy: " + standardPolicy.classify(honorsStu));
        // Strict: FAIL nếu rớt >= 1 hoặc GPA < 2.2. Ở đây rớt 1 => FAIL
        System.out.println("Strict Policy:   " + strictPolicy.classify(honorsStu));

        // 5. Kiểm tra tính đa hình (Polymorphism)
        // Policies không được phụ thuộc vào loại sinh viên (Regular hay Honors)
        System.out.println("\nCheck: Policies only rely on public methods of Student: " + 
            (standardPolicy.classify(regularStu) != null && standardPolicy.classify(honorsStu) != null));
    

    System.out.println("=== KIỂM THỬ CHI TIẾT EXERCISE 3 ===");

        // 1. Case FAIL: Rớt quá số môn cho phép hoặc GPA quá thấp
        // Standard: FAIL nếu failed >= 2 HOẶC GPA < 2.0 [cite: 296, 324]
        // Strict: FAIL nếu failed >= 1 HOẶC GPA < 2.2 [cite: 310, 334]
        Transcript trFail = new Transcript();
        trFail.addCourseResult(new CourseResult("M01", 3, 4.5)); // 1.0 hệ 4, Rớt [cite: 97, 109]
        trFail.addCourseResult(new CourseResult("M02", 3, 9.0)); // 4.0 hệ 4
        // GPA = (1*3 + 4*3)/6 = 2.5. failedCount = 1 [cite: 101, 108]
        Student sFail = new RegularStudent("S01", "Nguyen Fail", "K22", "CS", 80, trFail);
        printTest("CASE FAIL (GPA 2.5, Rớt 1)", sFail);

        // 2. Case PASS: Ngưỡng thấp nhất của đậu
        // Standard: 2.0 <= GPA < 2.5 [cite: 297, 325]
        // Strict: 2.2 <= GPA < 2.7 [cite: 312, 335]
        Transcript trPass = new Transcript();
        trPass.addCourseResult(new CourseResult("M01", 2, 6.0)); // 2.0 hệ 4 [cite: 96]
        // GPA = 2.0. failedCount = 0
        Student sPass = new RegularStudent("S02", "Tran Pass", "K22", "CS", 80, trPass);
        printTest("CASE PASS (GPA 2.0, Rớt 0)", sPass);

        // 3. Case EXCELLENT: Ngưỡng cao nhất và điều kiện không rớt môn
        // Standard: GPA >= 3.6 VÀ failed == 0 [cite: 300, 330]
        // Strict: GPA >= 3.7 VÀ failed == 0 [cite: 316, 340]
        Transcript trExc = new Transcript();
        trExc.addCourseResult(new CourseResult("M01", 3, 8.2)); // 3.0 hệ 4 [cite: 95]
        trExc.addCourseResult(new CourseResult("M02", 3, 9.5)); // 4.0 hệ 4 [cite: 94]
        // GPA = (3*3 + 4*3)/6 = 3.5 (Sau khi làm tròn 1 chữ số) [cite: 101, 103]
        Student sExc = new HonorsStudent("S03", "Le Excellent", "K22", "CS", 95, trExc);
        
        // Thêm 1 môn để đẩy GPA lên đúng 3.7
        trExc.addCourseResult(new CourseResult("M03", 4, 9.0)); // 4.0 hệ 4
        // GPA mới = (3.5*6 + 4.0*4)/10 = 3.7. failedCount = 0
        printTest("CASE EXCELLENT (GPA 3.7, Rớt 0)", sExc);

        // 4. Case Biên: GPA rất cao nhưng rớt 1 môn
        // Standard: Không thể đạt EXCELLENT vì failed != 0 -> Sẽ rơi vào GOOD [cite: 300, 328]
        // Strict: FAIL ngay lập tức vì failed >= 1 [cite: 310, 334]
        Transcript trEdge = new Transcript();
        trEdge.addCourseResult(new CourseResult("M01", 3, 4.0)); // 1.0 hệ 4, Rớt [cite: 97, 109]
        trEdge.addCourseResult(new CourseResult("M02", 10, 10.0)); // 4.0 hệ 4
        // GPA = (1*3 + 4*10)/13 = 3.15 -> Làm tròn thành 3.2 [cite: 101, 103]
        Student sEdge = new RegularStudent("S04", "Hoang Edge", "K22", "CS", 90, trEdge);
        printTest("CASE BIÊN (GPA 3.2, Rớt 1)", sEdge);
    }
    private static void printTest(String label, Student s) {
        ClassificationPolicy std = new StandardPolicy(); 
        ClassificationPolicy str = new StrictPolicy(); 
        System.out.println(label);
        System.out.println("  > Standard Policy: " + std.classify(s));
        System.out.println("  > Strict Policy:   " + str.classify(s));
        System.out.println("-----------------------------------");
    }
}
   
