import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Tokenizer {
    private String input;
    private int currentPosition;
    private List<Character> delimiters;

    public Tokenizer(String input, String delimiterString) {
        this.input = input;
        this.currentPosition = 0;
        setDelimiters(delimiterString);
    }

    public void setDelimiters(String delimiterString) {
        delimiters = new ArrayList<>();
        for (char delimiter : delimiterString.toCharArray()) {
            delimiters.add(delimiter);
        }
        Collections.sort(delimiters);
    }

    public boolean next(StringBuilder result) {
        result.setLength(0);
        int length = input.length();

        while (currentPosition < length && delimiters.contains(input.charAt(currentPosition))) {
            currentPosition++;
        }

        if (currentPosition >= length) {
            return false;
        }

        int startPosition = currentPosition;

        while (currentPosition < length && !delimiters.contains(input.charAt(currentPosition))) {
            currentPosition++;
        }

        result.append(input.substring(startPosition, currentPosition));

        return true;
    }

    public String tail() {
        int length = input.length();
        int currentPos = currentPosition;

        while (currentPos < length && delimiters.contains(input.charAt(currentPos))) {
            currentPos++;
        }

        return currentPos < length ? input.substring(currentPos) : "";
    }

    public static void main(String[] args) {
        Tokenizer tokenizer = new Tokenizer("Hello, World! This is an example", ", .");

        StringBuilder token = new StringBuilder();
        while (tokenizer.next(token)) {
            System.out.println("Token: " + token);
        }

        System.out.println("Tail: " + tokenizer.tail());
    }
}
