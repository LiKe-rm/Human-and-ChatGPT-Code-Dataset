import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.time.format.TextStyle;
import java.util.Locale;

public class QDate {
    private LocalDate localDate;

    public QDate() {
        localDate = LocalDate.now();
    }

    public QDate(int year, int month, int day) {
        localDate = LocalDate.of(year, month, day);
    }

    public QDate addDays(long days) {
        return new QDate(localDate.plusDays(days));
    }

    public QDate addMonths(long months) {
        return new QDate(localDate.plusMonths(months));
    }

    public QDate addYears(long years) {
        return new QDate(localDate.plusYears(years));
    }

    public int day() {
        return localDate.getDayOfMonth();
    }

    public int dayOfWeek() {
        return localDate.getDayOfWeek().getValue();
    }

    public int dayOfYear() {
        return localDate.getDayOfYear();
    }

    public int daysInMonth() {
        return localDate.lengthOfMonth();
    }

    public int daysInYear() {
        return localDate.lengthOfYear();
    }

    public long daysTo(QDate other) {
        return localDate.until(other.localDate).getDays();
    }

    public boolean isNull() {
        return localDate == null;
    }

    public boolean isValid() {
        return localDate != null;
    }

    public int month() {
        return localDate.getMonthValue();
    }

    public void setDate(int year, int month, int day) {
        localDate = LocalDate.of(year, month, day);
    }

    public long toJulianDay() {
        return localDate.toEpochDay() + 2440588;
    }

    public String toString() {
        return localDate.toString();
    }

    public int year() {
        return localDate.getYear();
    }

    public static QDate currentDate() {
        return new QDate();
    }

    public static QDate fromJulianDay(long julianDay) {
        return new QDate(LocalDate.ofEpochDay(julianDay - 2440588));
    }

    public static boolean isLeapYear(int year) {
        return LocalDate.of(year, 1, 1).isLeapYear();
    }

    public static String longDayName(int dayOfWeek) {
        return LocalDate.now().withDayOfWeek(dayOfWeek).getDayOfWeek().getDisplayName(TextStyle.FULL, Locale.getDefault());
    }

    public static String longMonthName(int month) {
        return LocalDate.now().withMonth(month).getMonth().getDisplayName(TextStyle.FULL, Locale.getDefault());
    }

    public static String shortDayName(int dayOfWeek) {
        return LocalDate.now().withDayOfWeek(dayOfWeek).getDayOfWeek().getDisplayName(TextStyle.SHORT, Locale.getDefault());
    }

    public static String shortMonthName(int month) {
        return LocalDate.now().withMonth(month).getMonth().getDisplayName(TextStyle.SHORT, Locale.getDefault());
    }

    public static QDate fromString(String dateString) {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        return new QDate(LocalDate.parse(dateString, formatter));
    }

    private QDate(LocalDate localDate) {
        this.localDate = localDate;
    }
}
