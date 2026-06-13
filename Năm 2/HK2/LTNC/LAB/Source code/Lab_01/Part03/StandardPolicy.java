public class StandardPolicy implements  ClassificationPolicy {

    
    @Override
    public Classification classify(Student s){
        if (s.failedCount() >= 2 || s.getGpa4() < 2.0) {
            return Classification.FAIL;
        } else if (s.getGpa4()>= 2.0 && s.getGpa4()<2.5){
            return Classification.PASS;
        } else if (s.getGpa4()>=2.5 && s.getGpa4() <3.2){
            return Classification.FAIR;
        } else if (s.getGpa4()>= 3.2 && s.getGpa4() <3.6){
            return Classification.GOOD;
        } else if (s.getGpa4()>=3.6 && s.failedCount() == 0){
            return Classification.EXCELLENT;
        }
        return Classification.GOOD;
    }
}
