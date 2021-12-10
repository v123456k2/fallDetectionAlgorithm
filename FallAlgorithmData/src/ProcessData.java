import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;

public class ProcessData {

    public static List<Boolean> expected = new ArrayList<>();
    public static List<FileParser> files = new ArrayList<>();
    public static double accMinBound = Double.MAX_VALUE;
    public static double accMaxBound = Double.MIN_VALUE;
    public static double angularMaxBound = Double.MIN_VALUE;
    public static List<PotentialBounds> bounds = new ArrayList<>();
    public static int fallSize = 0;
    public static void main(String[] args) throws FileNotFoundException {
        for (int i = 1; i < 55; i++) {
            try {
                FileParser temp = new FileParser("/Users/vincentchow/Desktop/School/School 2021-2022/FallAlgorithmData/src/fall_" + i + "_clean.log");
                fallSize++;
                files.add(temp);
                expected.add(true);
            }
            catch(Exception exception) {
                continue;
            }
        }
        for (int i = 2; i < 53; i++) {
            try {
                FileParser temp = new FileParser("/Users/vincentchow/Desktop/School/School 2021-2022/FallAlgorithmData/src/no_fall_"+i+"_clean.log");
                files.add(temp);
                expected.add(false);
            }
            catch (Exception exception){
                continue;
            }
        }
        getPotentialBounds();
        generateResult();
        boundsData();
        setBestBounds();
        System.out.println("acc min bound is: " + accMinBound);
        System.out.println("acc max bound is: " + accMaxBound);
        System.out.println("angular max bound is: " + angularMaxBound);
        test();
    }

    public static void setBestBounds() {
        double dist = Double.MAX_VALUE;
        for (int i = 0; i < bounds.size(); i++) {
            if (bounds.get(i).distance <= dist) {
                dist = bounds.get(i).distance;
                accMinBound = bounds.get(i).getAccMinBound();
                accMaxBound = bounds.get(i).getAccMaxBound();
                angularMaxBound = bounds.get(i).getAngularMaxBoundBound();
                System.out.println("true positive " + bounds.get(i).truePositive);
                System.out.println("false positive " + bounds.get(i).falsePositive);
                System.out.println("true negative " + bounds.get(i).trueNegative);
                System.out.println("false negative " + bounds.get(i).falseNegative);
                System.out.println("distance " + bounds.get(i).distance);
                System.out.println("acc min bound is: " + accMinBound);
                System.out.println("acc max bound is: " + accMaxBound);
                System.out.println("angular max bound is: " + angularMaxBound);
                System.out.println();
            }

        }
    }

    public static void getPotentialBounds() {
        //for (int i = 0; i < fallSize; i++) {
            for (int j = fallSize - 1; j >=0 ; j--) {
                for (int k = fallSize; k >= 0; k--) {
                    bounds.add(new PotentialBounds(0.045044422518220835, files.get(j).getAccMax(), files.get(k).getAngularMax()));
                }
            }
        //}
        /*for (int i = 0; i < bounds.size(); i++) {
            System.out.print(bounds.get(i).getAccMaxBound() + " ");
            System.out.print(bounds.get(i).getAccMinBound() + " ");
            System.out.print(bounds.get(i).getAngularMaxBoundBound() + " ");
            System.out.println();
        }*/
    }

    public static void boundsData() {
        for (int i = 0; i < bounds.size(); i++) {
            PotentialBounds temp = bounds.get(i);
            bounds.get(i).sensitivity = getSensitivity(temp.truePositive, temp.falseNegative);
            bounds.get(i).specificity = getSpecificity(temp.trueNegative, temp.falsePositive);
            bounds.get(i).distance = distance(bounds.get(i).sensitivity, bounds.get(i).specificity);
        }
    }

    public static void generateResult() {
        for (int i = 0; i < bounds.size(); i++) {
            double accMin = bounds.get(i).getAccMinBound();
            double accMax = bounds.get(i).getAccMaxBound();
            double angularMax = bounds.get(i).getAngularMaxBoundBound();
            for (int j = 0; j < files.size(); j++) {
                List<Double> acc = files.get(j).getAcceleration();
                List<Double> angular = files.get(j).getAngularVelocity();
                boolean belowAccMin = false;
                boolean aboveAccMax = false;
                boolean aboveAngularMax = false;
                int count = 0;
                boolean positive = false;
                for (int k = 0; k < acc.size(); k++) {
                    if (acc.get(k) <= accMin) {
                        belowAccMin = true;
                        count = 0;
                    }
                    if (belowAccMin && acc.get(k) >= accMax) {
                        aboveAccMax = true;
                    }
                    if (belowAccMin && angular.get(k) >= angularMax) {
                        aboveAngularMax = true;
                    }
                    if (belowAccMin && aboveAccMax && aboveAngularMax) {
                        positive = true;
                        break;
                    }
                    if (belowAccMin || aboveAccMax || aboveAngularMax) {
                        count++;
                    }
                    if (count > 500) {
                        belowAccMin = false;
                        aboveAccMax = false;
                        aboveAngularMax = false;
                    }
                }
                if (positive) {
                    if (expected.get(j) == true) {
                        bounds.get(i).truePositive++;
                    } else {
                        bounds.get(i).falsePositive++;
                    }
                } else {
                    if (expected.get(j) == false) {
                        bounds.get(i).trueNegative++;
                    } else {
                        bounds.get(i).falseNegative++;
                    }
                }
            }
        }
    }

    public static void test() {
            double accMin = 0.045044422518220835;
            double accMax = 0;
            double angularMax = 0;
            int fp = 0;
            int tp = 0;
            int tn = 0;
            int fn = 0;
            for (int j = 0; j < files.size(); j++) {
                List<Double> acc = files.get(j).getAcceleration();
                List<Double> angular = files.get(j).getAngularVelocity();
                boolean belowAccMin = false;
                //boolean aboveAccMax = false;
                //boolean aboveAngularMax = false;
                int count = 0;
                boolean positive = false;

                for (int k = 0; k < acc.size(); k++) {
                    if (acc.get(k) <= accMin) {
                        //belowAccMin = true;
                        positive = true;
                        break;
                    }
                    /*if (belowAccMin && acc.get(k) >= accMax) {
                        aboveAccMax = true;
                    }
                    if (belowAccMin && angular.get(k) >= angularMax) {
                        aboveAngularMax = true;
                    }
                    if (belowAccMin && aboveAccMax && aboveAngularMax) {
                        positive = true;
                        break;
                    }
                    if (belowAccMin || aboveAccMax || aboveAngularMax) {
                        count++;
                    }
                    if (count > 500) {
                        belowAccMin = false;
                        aboveAccMax = false;
                        aboveAngularMax = false;
                    }*/
                }
                if (positive) {
                    if (expected.get(j) == true) {
                        System.out.println("true positive" + j);
                        tp++;
                    } else {
                        System.out.println("false positive" + j);
                        fp++;
                    }
                } else {
                    if (expected.get(j) == false) {
                        System.out.println("true negative" + j);
                        tn++;
                    } else {
                        System.out.println("false negative" + j);
                        fn++;
                    }
                }
            }
        System.out.println("true positive " + tp);
        System.out.println("false positive " + fp);
        System.out.println("true negative " + tn);
        System.out.println("false negative " + fn);
    }

    public static double getSensitivity(double truePositive, double falseNegative) {
        return truePositive / (truePositive + falseNegative);
    }

    public static double getSpecificity(double trueNegative, double falsePositive) {
        return trueNegative / (trueNegative + falsePositive);
    }

    public static double distance(double sensitivity, double specificity) {
        return Math.sqrt(Math.pow((1.0-sensitivity),2) + Math.pow((1.0-specificity), 2));
    }
}
