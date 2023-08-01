import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Regex {
    private static List<String> globalGroups = new ArrayList<>();
    private Pattern pattern;
    private Matcher matcher;

    public Regex() {
        reset();
    }

    public Regex(String regex) {
        Pattern re = Pattern.compile("^/(.*?)/(\\w*)$", Pattern.CASE_INSENSITIVE);
        Matcher m = re.matcher(regex);
        if (m.matches()) {
            String nRegex = m.group(1);
            String opts = m.group(2);
            init(nRegex, opts);
        } else {
            throw new IllegalArgumentException();
        }
    }

    public Regex(String regex, int opts) {
        init(regex, opts);
    }

    public Regex(String regex, String opts) {
        init(regex, opts);
    }

    private void init(String regex, int opts) {
        reset();
        pattern = Pattern.compile(regex, opts);
    }

    private void init(String regex, String opts) {
        int options = parseOptions(opts);
        init(regex, options);
    }

    public void reset() {
        matcher = null;
    }

    public boolean match(String input) {
        if (matcher == null || !input.equals(matcher.input())) {
            matcher = pattern.matcher(input);
        }
        return matcher.find();
    }

    public int groupCount() {
        return matcher.groupCount();
    }

    public String group(int index) {
        return matcher.group(index);
    }

    public String replace(String replacement) {
        return matcher.replaceAll(replacement);
    }

    private int parseOptions(String opts) {
        int options = 0;
        if (opts.contains("i")) options |= Pattern.CASE_INSENSITIVE;
        if (opts.contains("m")) options |= Pattern.MULTILINE;
        if (opts.contains("s")) options |= Pattern.DOTALL;
        if (opts.contains("x")) options |= Pattern.COMMENTS;
        return options;
    }
}
