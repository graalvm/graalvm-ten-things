import org.apache.sis.distance.DistanceUtils;
import org.graalvm.nativeimage.IsolateThread;
import org.graalvm.nativeimage.c.function.CEntryPoint;

public class Distance {

    public static void main(String[] args) {
        final double aLat   = Double.parseDouble(args[0]);
        final double aLong  = Double.parseDouble(args[1]);
        final double bLat   = Double.parseDouble(args[2]);
        final double bLong  = Double.parseDouble(args[3]);
        System.out.printf("%.2f km%n", DistanceUtils.getHaversineDistance(aLat, aLong, bLat, bLong));
    }

    @CEntryPoint(name = "distance")
    public static double distance(IsolateThread thread, double aLat, double aLong, double bLat, double bLong) {
        return DistanceUtils.getHaversineDistance(aLat, aLong, bLat, bLong);
    }

}
