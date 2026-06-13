


public class StrictPolicy implements  ClassificationPolicy {
       @Override
    public Classification classify(Student s){
        if (s.failedCount() >= 1 || s.getGpa4() < 2.2) {
            return Classification.FAIL;
        } else if (s.getGpa4()>= 2.2 && s.getGpa4()<2.7){
            return Classification.PASS;
        } else if (s.getGpa4()>=2.7 && s.getGpa4() <3.3){
            return Classification.FAIR;
        } else if (s.getGpa4()>= 3.3 && s.getGpa4() <3.7){
            return Classification.GOOD;
        } else if (s.getGpa4()>=3.7 && s.failedCount() == 0){
            return Classification.EXCELLENT;
        }
        return Classification.GOOD;
    }



}
