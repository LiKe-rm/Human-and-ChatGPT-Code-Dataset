import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PatternFind {
    public static void main(String[] args) {
        byte[] data = "This is a test pattern in the data. Find the pattern and replace it.".getBytes();
        String searchPattern = "pattern";
        String replacePattern = "???????";

        patternSearchAndReplace(data, searchPattern, replacePattern);

        System.out.println(new String(data));
    }

    private static class PatternNibble {
        int n;
        boolean all;
    }

    private static class PatternByte {
        PatternNibble[] n = new PatternNibble[2];
    }

    private static List<PatternByte> patternTransform(String text) {
        List<PatternByte> pattern = new ArrayList<>();
        String formattedText = text.replaceAll("[^?A-Fa-f0-9]", "").toUpperCase();
        if (formattedText.length() % 2 != 0) {
            formattedText += "?";
        }

        for (int i = 0; i < formattedText.length(); i += 2) {
            PatternByte patternByte = new PatternByte();
            for (int j = 0; j < 2; j++) {
                PatternNibble nibble = new PatternNibble();
                char current = formattedText.charAt(i + j);
                if (current == '?') {
                    nibble.all = true;
                    nibble.n = 0;
                } else {
                    nibble.all = false;
                    nibble.n = Character.digit(current, 16);
                }
                patternByte.n[j] = nibble;
            }
            pattern.add(patternByte);
        }

        return pattern;
    }

    private static boolean patternMatchByte(byte dataByte, PatternByte patternByte) {
        int n1 = (dataByte >> 4) & 0xF;
        int n2 = dataByte & 0xF;

        return (patternByte.n[0].all || patternByte.n[0].n == n1) && (patternByte.n[1].all || patternByte.n[1].n == n2);
    }

    private static int patternFind(byte[] data, String searchPattern) {
        List<PatternByte> pattern = patternTransform(searchPattern);
        int patternSize = pattern.size();

        for (int i = 0, pos = 0; i < data.length; i++) {
            if (patternMatchByte(data[i], pattern.get(pos))) {
                pos++;
                if (pos == patternSize) {
                    return i - patternSize + 1;
                }
            } else {
                pos = 0;
            }
        }

        return -1;
    }

    private static void patternWriteByte(byte[] data, int index, PatternByte patternByte) {
        int n1 = (data[index] >> 4) & 0xF;
        int n2 = data[index] & 0xF;

        if (!patternByte.n[0].all) {
            n1 = patternByte.n[0].n;
        }

        if (!patternByte.n[1].all) {
            n2 = patternByte.n[1].n;
        }

        data[index] = (byte) ((n1 << 4) | n2);
    }

    private static void patternWrite(byte[] data, int startIndex, String replacePattern) {
        List<PatternByte> pattern = patternTransform(replacePattern);
        int patternSize = pattern.size();

        for (int i = 0; i < patternSize && startIndex + i < data.length; i++) {
            patternWriteByte(data, startIndex + i, pattern.get(i));
        }
    }

    public static boolean patternSearchAndReplace(byte[] data, String searchPattern, String replacePattern) {
        int found = patternFind(data, searchPattern);
        if (found == -1) {
            return false;
        }

        patternWrite(data, found, replacePattern);
        return true;
    }
}