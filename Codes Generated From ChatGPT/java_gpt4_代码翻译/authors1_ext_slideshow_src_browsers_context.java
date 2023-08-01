import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class BrowserContext {
    private String provider;
    private String user;
    private String pass;
    private String host;
    private String name;

    private BrowserContext(String provider, String user, String pass, String host, String name) {
        this.provider = provider;
        this.user = user;
        this.pass = pass;
        this.host = host;
        this.name = name;
    }

    public static BrowserContext parse(String string) {
        return BrowserContextParser.parse(string);
    }

    public String getProvider() {
        return provider;
    }

    public String getUser() {
        return user;
    }

    public String getPass() {
        return pass;
    }

    public String getHost() {
        return host;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "BrowserContext{" +
                "provider='" + provider + '\'' +
                ", user='" + user + '\'' +
                ", pass='" + pass + '\'' +
                ", host='" + host + '\'' +
                ", name='" + name + '\'' +
                '}';
    }

    private static class BrowserContextParser {
        private static final Pattern PATTERN = Pattern
                .compile("^(\\w+):\\/\\/(([^@:]+)(:([^@]+))?@)?([^\\/]+)(\\/([^\\s]+)?)?");

        public static BrowserContext parse(String string) {
            Matcher matcher = PATTERN.matcher(string);
            if (matcher.find()) {
                String provider = matcher.group(1);
                String user = matcher.group(3);
                String pass = matcher.group(5);
                String host = matcher.group(6);
                String name = matcher.group(8);
                return new BrowserContext(provider, user, pass, host, name);
            } else {
                throw new IllegalArgumentException("Failed to parse browser-string");
            }
        }
    }

    public class Main {
        public static void main(String[] args) {
            String input = "http://user:pass@example.com/context";
            BrowserContext context = BrowserContext.parse(input);
            System.out.println(context);
        }
    }
}