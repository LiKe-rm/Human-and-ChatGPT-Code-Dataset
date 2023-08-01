import java.io.PrintStream;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public abstract class LineOutputter {
    private static final String AMAZON_S3_REGEX = "^[0-9a-f]+ ([-A-z0-9_\\.]+) \\[(.*)\\] ([0-9\\.]+) " +
            "[-0-9a-f]+ [0-9A-F]+ \\S+ \\S+ (\"[^\"]*\") (\\d+) [-A-z0-9]+ ([-0-9]+) " +
            "[-0-9]+ \\d+ [-0-9]+ (\"[^\"]*\") (\"[^\"]*\")";

    private static final Pattern AMAZON_S3_PATTERN = Pattern.compile(AMAZON_S3_REGEX);

    public abstract void writeLine(String line);

    public static LineOutputter forLine(String line) {
        Matcher matcher = AMAZON_S3_PATTERN.matcher(line);
        if (matcher.find()) {
            return new S3LineOutputter();
        } else {
            return new DirectLineOutputter();
        }
    }
}

class S3LineOutputter extends LineOutputter {
    @Override
    public void writeLine(String line) {
        Matcher matcher = LineOutputter.AMAZON_S3_PATTERN.matcher(line);
        if (matcher.find()) {
            PrintStream out = System.out;
            String formattedLine = String.format("%s - - [%s] %s %s %s %s %s %s%n",
                    matcher.group(3), matcher.group(2), matcher.group(4),
                    matcher.group(5), matcher.group(6), matcher.group(7),
                    matcher.group(8), matcher.group(1));
            out.print(formattedLine);
        } else {
            System.err.println("*** S3: Failed to match \"" + line + "\"");
        }
    }
}

class DirectLineOutputter extends LineOutputter {
    @Override
    public void writeLine(String line) {
        System.out.println(line);
    }
}
