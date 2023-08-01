import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.io.Reader;

public class Parser {
    private BufferedReader reader;
    private String current;

    public Parser() {
    }

    public Parser(String fileName) throws IOException {
        FileReader fileReader = new FileReader(fileName);
        this.reader = new BufferedReader(fileReader);
    }

    public Parser(Reader source) {
        this.reader = new BufferedReader(source);
    }

    public ASTree parse() {
        ASTree tree = new ASTree();
        return tree;
    }

    public void parse(Function function) {
    }

    private Token nextToken() throws IOException {
        current = parseToken();
        return new Token(current);
    }

    private String parseToken() throws IOException {
        StringBuilder identifier = new StringBuilder();
        int lastChar;
        int line = 0;

        do {
            lastChar = reader.read();

            if (Character.isAlphabetic(lastChar)) {
                identifier.append((char) lastChar);
                while (Character.isAlphanumeric(lastChar = reader.read())) {
                    identifier.append((char) lastChar);
                }

                if ("VISIBLE".equals(identifier.toString())) {
                    if (lastChar != '\n') {
                        while (Character.isWhitespace((lastChar = reader.read()))) ;
                    }

                    if (lastChar == '\n') {
                        line++;
                        return parseToken();
                    }
                }

                if ("I".equals(identifier.toString())) {
                    identifier.append(" ");
                }
            }
        } while (Character.isWhitespace(lastChar));

        return identifier.toString();
    }
}
