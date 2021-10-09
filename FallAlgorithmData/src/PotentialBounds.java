public class PotentialBounds {

    public double truePositive;
    public double falsePositive;
    public double trueNegative;
    public double falseNegative;
    private double accMinBound;
    private double accMaxBound;
    private double angularMaxBound;
    public double sensitivity;
    public double specificity;
    public double distance;
    public PotentialBounds(double accMinBound, double accMaxBound, double angularMaxBound) {
        this.accMinBound = accMinBound;
        this.accMaxBound = accMaxBound;
        this.angularMaxBound = angularMaxBound;
        this.sensitivity = 0;
        this.specificity = 0;
        this.truePositive = 0;
        this.falsePositive = 0;
        this.trueNegative = 0;
        this.falseNegative = 0;
        this.distance = Double.MAX_VALUE;
    }

    public double getAccMinBound() {
        return this.accMinBound;
    }

    public double getAccMaxBound() {
        return this.accMaxBound;
    }

    public double getAngularMaxBoundBound() {
        return this.angularMaxBound;
    }
}
