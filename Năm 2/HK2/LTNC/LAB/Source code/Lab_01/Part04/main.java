import java.util.*;

public class main {
    public static void main(String[] args) {
        System.out.println("========== BẮT ĐẦU KIỂM THỬ EXERCISE 4 (SENIOR LEVEL) ==========");

        // --- SETUP DỮ LIỆU CƠ BẢN ---
        // 1. Tạo các bảng điểm (Transcript) mẫu
        Transcript tGpa4_Fail0 = new Transcript(); 
        tGpa4_Fail0.addCourseResult(new CourseResult("C1", 3, 9.0)); // GPA 4.0, Rớt 0

        Transcript tGpa2_Fail0 = new Transcript(); 
        tGpa2_Fail0.addCourseResult(new CourseResult("C1", 3, 5.5)); // GPA 2.0, Rớt 0

        // 2. Thiết lập StudentRepository
        StudentRepository repo = new StudentRepository();
        
        // --- TEST 1: TÍNH ĐÓNG GÓI CỦA REPOSITORY ---
        System.out.println("\n[TEST 1] Kiểm tra Encapsulation của StudentRepository:");
        RegularStudent sDummy = new RegularStudent("D1", "Le A", "K24", "CS", 90, tGpa4_Fail0);
        repo.add(sDummy);
        List<Student> listFromRepo = repo.findAll();
        try {
            listFromRepo.add(new RegularStudent("D2", "Le B", "K24", "CS", 90, tGpa4_Fail0));
            // Nếu không văng lỗi, kiểm tra xem list trong repo có bị thay đổi kích thước không
            assertEqInt("Repo trả về bản sao hoặc Unmodifiable (size vẫn phải là 1)", 1, repo.findAll().size());
        } catch (UnsupportedOperationException e) {
            System.out.println("[PASS] Repo trả về UnmodifiableList - Rất tốt!");
        }

        // --- TEST 2: TÍNH BẤT BIẾN CỦA COHORT STATS ---
        System.out.println("\n[TEST 2] Kiểm tra tính Immutable của CohortStats:");
        Map<Classification, Integer> dummyMap = new HashMap<>();
        dummyMap.put(Classification.EXCELLENT, 5);
        
        CohortStats stats = new CohortStats("K24", 5, dummyMap, 3, 2);
        try {
            stats.getCounts().put(Classification.GOOD, 10);
            assertEqInt("Dữ liệu bên trong Stats không được thay đổi (size vẫn là 1)", 1, stats.getCounts().size());
        } catch (UnsupportedOperationException e) {
            System.out.println("[PASS] Map trong CohortStats là Unmodifiable - Đúng chuẩn!");
        }

        // --- SETUP DỮ LIỆU CHO REPORTING SERVICE (Để test sắp xếp Top K) ---
        StudentRepository mainRepo = new StudentRepository();
        
        // S1: English: "Z Le" (Lớn nhất theo bảng chữ cái)
        RegularStudent s1 = new RegularStudent("S1", "Le Z", "K24", "CS", 90, tGpa4_Fail0); 
        // S2: English: "A Le" (Cùng mọi thứ với S1 nhưng tên nhỏ hơn)
        HonorsStudent s2 = new HonorsStudent("S2", "Le A", "K24", "CS", 90, tGpa4_Fail0);  
        // S3: Kỷ luật 90 nhưng rớt 1 môn (Thua S1, S2 về failCount)
        Transcript tS3 = new Transcript(); 
        tS3.addCourseResult(new CourseResult("C1", 4, 9.0)); 
        tS3.addCourseResult(new CourseResult("C2", 2, 4.5)); // Rớt
        RegularStudent s3 = new RegularStudent("S3", "Le B", "K24", "CS", 90, tS3); 
        // S4: Kỷ luật 80 (Thua S1, S2 về disciplineScore)
        RegularStudent s4 = new RegularStudent("S4", "Le C", "K24", "CS", 80, tGpa4_Fail0); 
        // S5: GPA 2.0 (Thấp nhất)
        RegularStudent s5 = new RegularStudent("S5", "Le D", "K25", "CS", 100, tGpa2_Fail0);
        
        // Thêm vào Repo theo thứ tự ngẫu nhiên để test tính ổn định (Stability)
        mainRepo.add(s5); mainRepo.add(s3); mainRepo.add(s1); mainRepo.add(s4); mainRepo.add(s2);
        
        ReportingService service = new ReportingService(mainRepo);
        ClassificationPolicy standardPolicy = new StandardPolicy();

        // --- TEST 3: TOP K BY GPA (KIỂM TRA TIE-BREAKERS) ---
        System.out.println("\n[TEST 3] Kiểm tra topKByGpa (4 tầng ưu tiên):");
        List<Student> top3 = service.topKByGpa(3);
        assertEqInt("Trả về đúng k = 3 phần tử", 3, top3.size());
        
        // Thứ tự đúng: S1 (Tên Z) > S2 (Tên A) > S4 (GPA 4, Disc 80)
        assertEqString("Hạng 1: S1 (Thắng nhờ tên Z > A)", "S1", top3.get(0).getId());
        assertEqString("Hạng 2: S2 (Thua tên so với S1)", "S2", top3.get(1).getId());
        assertEqString("Hạng 3: S4 (Thua kỷ luật so với S1, S2)", "S4", top3.get(2).getId());

        // --- TEST 4: GROUP BY CLASSIFICATION (KIỂM TRA STABILITY) ---
        System.out.println("\n[TEST 4] Kiểm tra groupByClassification (Tính ổn định):");
        Map<Classification, List<Student>> groups = service.groupByClassification(standardPolicy);
        
        List<Student> excellents = groups.get(Classification.EXCELLENT);
        // Trong repo, thứ tự nạp vào là: ..., s1, s4, s2.
        // Danh sách nhóm EXCELLENT phải giữ đúng thứ tự này.
        assertEqString("Ổn định vị trí 1: S1", "S1", excellents.get(0).getId());
        assertEqString("Ổn định vị trí 2: S4", "S4", excellents.get(1).getId());
        assertEqString("Ổn định vị trí 3: S2", "S2", excellents.get(2).getId());

        // --- TEST 5: STATS BY COHORT ---
        System.out.println("\n[TEST 5] Kiểm tra statsByCohort:");
        CohortStats statsK24 = service.statsByCohort("K24", standardPolicy);
        assertEqInt("Tổng sinh viên K24 (S1, S2, S3, S4)", 4, statsK24.getTotal());
        assertEqInt("Số lượng Regular (S1, S3, S4)", 3, statsK24.getRegularCount());
        assertEqInt("Số lượng Honors (S2)", 1, statsK24.getHonorsCount());
        
        System.out.println("\n========== TẤT CẢ TEST CASE HOÀN TẤT ==========");
    }

    // --- CÁC PHƯƠNG THỨC HỖ TRỢ (HELPER) ---
    private static void assertEqInt(String msg, int expected, int actual) {
        if (expected == actual) {
            System.out.println("[PASS] " + msg);
        } else {
            System.out.println("[FAIL] " + msg + " -> Mong đợi: " + expected + ", Thực tế: " + actual);
        }
    }

    private static void assertEqString(String msg, String expected, String actual) {
        if (expected.equals(actual)) {
            System.out.println("[PASS] " + msg);
        } else {
            System.out.println("[FAIL] " + msg + " -> Mong đợi: '" + expected + "', Thực tế: '" + actual + "'");
        }
    }
}