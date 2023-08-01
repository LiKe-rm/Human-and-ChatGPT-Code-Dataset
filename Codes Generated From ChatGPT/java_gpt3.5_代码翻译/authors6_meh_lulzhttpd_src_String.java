import java.io.Serializable;

public class MyString implements Serializable {
    private String string;

    public MyString() {
        this.string = "";
    }

    public MyString(char c) {
        this.string = String.valueOf(c);
    }

    public MyString(String s) {
        this.string = s;
    }

    public MyString(int i) {
        this.string = String.valueOf(i);
    }

    public MyString(long l) {
        this.string = String.valueOf(l);
    }

    public MyString(double d) {
        this.string = String.valueOf(d);
    }

    public char charAt(int index) {
        return string.charAt(index);
    }

    public void append(MyString s) {
        string = string.concat(s.toString());
    }

    public void append(char c) {
        string = string.concat(String.valueOf(c));
    }

    public void append(String s) {
        string = string.concat(s);
    }

    public void append(int i) {
        string = string.concat(String.valueOf(i));
    }

    public void append(long l) {
        string = string.concat(String.valueOf(l));
    }

    public void append(double d) {
        string = string.concat(String.valueOf(d));
    }

    public MyString substring(int beginIndex, int endIndex) {
        return new MyString(string.substring(beginIndex, endIndex));
    }

    public int length() {
        return string.length();
    }

    public boolean isEmpty() {
        return string.isEmpty();
    }

    public int toInt() {
        return Integer.parseInt(string);
    }

    public long toLong() {
        return Long.parseLong(string);
    }

    public double toDouble() {
        return Double.parseDouble(string);
    }

    public String toString() {
        return string;
    }

    public MyString toUpperCase() {
        return new MyString(string.toUpperCase());
    }

    public MyString toLowerCase() {
        return new MyString(string.toLowerCase());
    }

    // Overridden methods and custom operators are not directly supported in Java.
    // You can implement custom methods to achieve similar functionality.
}
