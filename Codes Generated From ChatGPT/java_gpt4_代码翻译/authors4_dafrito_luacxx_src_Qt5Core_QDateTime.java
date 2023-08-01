import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.LocalTime;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;

public class QDateTime {
    private LocalDateTime dateTime;

    public QDateTime() {
        this.dateTime = LocalDateTime.now();
    }

    public QDateTime(LocalDateTime dateTime) {
        this.dateTime = dateTime;
    }

    public QDateTime(LocalDate date) {
        this.dateTime = LocalDateTime.of(date, LocalTime.MIDNIGHT);
    }

    public QDateTime(LocalDate date, LocalTime time) {
        this.dateTime = LocalDateTime.of(date, time);
    }

    public LocalDateTime getDateTime() {
        return dateTime;
    }

    public void setDateTime(LocalDateTime dateTime) {
        this.dateTime = dateTime;
    }

    public String toString() {
        return dateTime.toString();
    }

    public String toString(DateTimeFormatter formatter) {
        return dateTime.format(formatter);
    }

    public QDateTime addDays(long days) {
        return new QDateTime(dateTime.plusDays(days));
    }

    public QDateTime addMonths(long months) {
        return new QDateTime(dateTime.plusMonths(months));
    }

    public QDateTime addYears(long years) {
        return new QDateTime(dateTime.plusYears(years));
    }

    public QDateTime addHours(long hours) {
        return new QDateTime(dateTime.plusHours(hours));
    }

    public QDateTime addMinutes(long minutes) {
        return new QDateTime(dateTime.plusMinutes(minutes));
    }

    public QDateTime addSeconds(long seconds) {
        return new QDateTime(dateTime.plusSeconds(seconds));
    }

    public QDateTime addNanos(long nanos) {
        return new QDateTime(dateTime.plusNanos(nanos));
    }

    public long daysTo(QDateTime other) {
        return ChronoUnit.DAYS.between(dateTime.toLocalDate(), other.dateTime.toLocalDate());
    }

    public long hoursTo(QDateTime other) {
        return ChronoUnit.HOURS.between(dateTime, other.dateTime);
    }

    public long minutesTo(QDateTime other) {
        return ChronoUnit.MINUTES.between(dateTime, other.dateTime);
    }

    public long secondsTo(QDateTime other) {
        return ChronoUnit.SECONDS.between(dateTime, other.dateTime);
    }

    public long nanosTo(QDateTime other) {
        return ChronoUnit.NANOS.between(dateTime, other.dateTime);
    }

    public static QDateTime now() {
        return new QDateTime();
    }

    public static QDateTime of(LocalDate date, LocalTime time) {
        return new QDateTime(date, time);
    }

    public static QDateTime ofEpochSecond(long epochSecond, ZoneId zone) {
        return new QDateTime(LocalDateTime.ofEpochSecond(epochSecond, 0, zone.getRules().getOffset(Instant.now())));
    }

    public static QDateTime parse(String text) {
        return new QDateTime(LocalDateTime.parse(text));
    }

    public static QDateTime parse(String text, DateTimeFormatter formatter) {
        return new QDateTime(LocalDateTime.parse(text, formatter));
    }
}
