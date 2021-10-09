import java.util.List;
import java.util.ArrayList;
import java.io.*;
public class FileParser {

    private double accMin;
    private double accMax;
    private double angularMax;
    private List<Double> acceleration;
    private List<Double> angularVelocity;

    public FileParser(String path) {
        this.accMin = Double.MAX_VALUE;
        this.accMax = Double.MIN_VALUE;
        this.angularMax = Double.MIN_VALUE;
        this.acceleration = new ArrayList<>();
        this.angularVelocity = new ArrayList<>();
        readFile(path);
        findAccMin();
        findAccMax();
        findAngularMax();
    }
    private void readFile(String path) {
        System.out.println(path);
        try {
            File file = new File(path);
            FileReader fileReader = new FileReader(file);
            BufferedReader reader = new BufferedReader(fileReader);  //creates a buffering character input stream
            String line;
            while ((line = reader.readLine()) != null) {
                String[] temp = line.split(" ");
                double x = 0;
                double y = 0;
                double z = 0;
                for (int i = 1; i < temp.length; i++) {
                    if (temp[i].length() != 0) {
                        if (x == 0) {
                            x = Double.parseDouble(temp[i]);
                        } else if (y == 0) {
                            y = Double.parseDouble(temp[i]);
                        } else if (z == 0) {
                            z = Double.parseDouble(temp[i]);
                        }
                    }
                }
                double val = findTotalAcc(x, y, z);
                if (temp[0].equals("gyro:")){
                    this.angularVelocity.add(val);
                } else if (temp[0].equals("accel:")) {
                    this.acceleration.add(val);
                }
            }
            fileReader.close();
        } catch(IOException e) {
            e.printStackTrace();
        }
    }

    private double findTotalAcc(double x, double y, double z) {
        return Math.sqrt(x*x + y*y + z*z);
    }

    private void findAccMin() {
        for (int i = 0; i < acceleration.size(); i++) {
            this.accMin = Math.min(this.accMin, acceleration.get(i));
        }
    }

    private void findAccMax() {
        for (int i = 0; i < acceleration.size(); i++) {
            this.accMax = Math.max(this.accMax, acceleration.get(i));
        }
    }

    private void findAngularMax() {
        for (int i = 0; i < angularVelocity.size(); i++) {
            this.angularMax = Math.max(this.accMax, angularVelocity.get(i));
        }
    }

    public double getAccMin() {
        return this.accMin;
    }

    public double getAccMax() {
        return this.accMax;
    }

    public double getAngularMax() {
        return this.angularMax;
    }

    public List<Double> getAcceleration() {
        return this.acceleration;
    }

    public List<Double> getAngularVelocity() {
        return this.angularVelocity;
    }
}
