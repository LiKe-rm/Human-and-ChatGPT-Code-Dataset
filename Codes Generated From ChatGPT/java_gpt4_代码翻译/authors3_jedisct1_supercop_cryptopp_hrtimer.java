import java.time.Duration;
import java.time.Instant;

public class HRTimer {
    public enum Unit {
        SECONDS,
        MILLISECONDS,
        MICROSECONDS,
        NANOSECONDS
    }

    private Instant startTime;
    private Instant lastTime;
    private Unit timerUnit;
    private boolean started;
    private boolean stuckAtZero;

    public HRTimer(Unit timerUnit) {
        this.timerUnit = timerUnit;
        this.started = false;
        this.stuckAtZero = false;
    }

    public void start() {
        startTime = Instant.now();
        lastTime = startTime;
        started = true;
    }

    public double elapsedTimeAsDouble() {
        if (stuckAtZero) {
            return 0.0;
        }

        if (!started) {
            start();
            return 0.0;
        }

        Instant now = Instant.now();
        if (lastTime.isBefore(now)) {
            lastTime = now;
        }

        return convertTo(Duration.between(startTime, lastTime), timerUnit);
    }

    public long elapsedTime() {
        double elapsedTime = elapsedTimeAsDouble();
        return (long) elapsedTime;
    }

    private static double convertTo(Duration duration, Unit unit) {
        switch (unit) {
            case SECONDS:
                return (double) duration.getSeconds();
            case MILLISECONDS:
                return (double) duration.toMillis();
            case MICROSECONDS:
                return (double) duration.toNanos() / 1000;
            case NANOSECONDS:
                return (double) duration.toNanos();
            default:
                throw new IllegalArgumentException("Invalid timer unit");
        }
    }
    
    public static void main(String[] args) {
        HRTimer timer = new HRTimer(Unit.MILLISECONDS);
        timer.start();
    
        // Example code to demonstrate timer usage
        try {
            Thread.sleep(2000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    
        System.out.println("Elapsed time in milliseconds: " + timer.elapsedTimeAsDouble());
    }
}    
