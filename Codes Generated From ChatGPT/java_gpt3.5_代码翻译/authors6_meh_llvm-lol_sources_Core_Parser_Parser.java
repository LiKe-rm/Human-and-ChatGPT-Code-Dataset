import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Parser {
    private BufferedReader file;
    private String source;
    private String current;
    private int line = 0;

    public Parser() {
        this.file = null;
        this.source = null;
        this.current = null;
    }

    public Parser(String filePath) throws IOException {
        this.file = new BufferedReader(new FileReader(filePath));
        this.source = null;
        this.current = null;
    }

    public Parser(String source, boolean isSource) {
        this.file = null;
        this.source = source;
        this.current = null;
    }

    public AST parse() throws IOException {
        AST tree = new AST();
        Token token = nextToken();

        if (!token.type.equals(Token.Type.VERSION)) {
            tree.addError("The source must begin with a HAI instruction.");
            return tree;
        }

        String version = (String) token.data;
        tree.addVersion(version);

        if (version.equals("1.2")) {
            AST toMerge;

            if (file != null) {
                LOLCODE12Parser parser = new LOLCODE12Parser(file);
                toMerge = parser.parse();
            } else if (source != null) {
                LOLCODE12Parser parser = new LOLCODE12Parser(source, true);
                toMerge = parser.parse();
            } else {
                toMerge = new AST();
            }

            tree.merge(toMerge);
        } else {
            tree.removeLast();
            tree.addError("Unknown language version.");
        }

        return tree;
    }

    public void parse(Function function) {
    }

    private char nextChar() throws IOException {
        if (file != null) {
            int ch = file.read();
            return ch == -1 ? (char) 0 : (char) ch;
        } else if (source != null) {
            if (!source.isEmpty()) {
                char ch = source.charAt(0);
                source = source.substring(1);
                return ch;
            }
            return 0;
        } else {
            return 0;
        }
    }

    private Token currentToken() {
        return new Token(current);
    }

    private Token nextToken() throws IOException {
        return current = parseToken();
    }

    private Token parseToken() throws IOException {
        char lastChar;
        do {
            lastChar = nextChar();

            if (Character.isAlphabetic(lastChar)) {
                StringBuilder identifier = new StringBuilder();

                identifier.append(lastChar);
                while (Character.isAlphanumeric(lastChar = nextChar())) {
                    identifier.append(lastChar);
                }

                if (identifier.toString().equals("HAI")) {
                    if (lastChar != '\n') {
                        while (Character.isWhitespace((lastChar = nextChar()))) ;
                    }

                    if (lastChar == '\n') {
                        line++;
                        return new Token(Token.Type.VERSION, "1.2", line);
                    } else {
                        StringBuilder version = new StringBuilder();

                        version.append(lastChar);
                        while (!Character.isWhitespace((lastChar = nextChar()))) {
                            version.append(lastChar);
                        }

                        return new Token(Token.Type.VERSION, version.toString(), line);
                    }
                } else {
                    if (identifier.toString().equals("BTW")) {
                        while ((lastChar = nextChar()) != '\n') ;
                        line++;
                    } else if (identifier.toString().equals("OBTW")) {
                        StringBuilder comment = new StringBuilder("    ");

                        while (!comment.substring(comment.length() - 4).equals("TLDR")) {
                            comment.append((lastChar = nextChar()));
                            if (lastChar == '\n') {
                                line++;
                            }
                        }
                    }
    
                    return parseToken();
                }
            }
        } while (Character.isWhitespace(lastChar));
    
        return new Token();
    }
    
    public static class AST {
        private ArrayList<Object> tree;
    
        public AST() {
            tree = new ArrayList<>();
        }
    
        public void addVersion(String version) {
            tree.add(new Version(version));
        }
    
        public void addError(String error) {
            tree.add(new Error(error));
        }
    
        public void merge(AST other) {
            tree.addAll(other.tree);
        }
    
        public void removeLast() {
            if (!tree.isEmpty()) {
                tree.remove(tree.size() - 1);
            }
        }
    
        public static class Version {
            private String version;
    
            public Version(String version) {
                this.version = version;
            }
        }
    
        public static class Error {
            private String error;
    
            public Error(String error) {
                this.error = error;
            }
        }
    }
    
    public static class Token {
        public enum Type {
            VERSION
        }
    
        public Type type;
        public Object data;
        public int lineNumber;
    
        public Token() {
        }
    
        public Token(Type type, Object data, int lineNumber) {
            this.type = type;
            this.data = data;
            this.lineNumber = lineNumber;
        }
    }
    
    public interface Function {
    }
}

