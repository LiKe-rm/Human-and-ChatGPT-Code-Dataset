import java.nio.charset.StandardCharsets;

public class RichTextAggregator {

    private StringBuilder csNewText;
    private String csSeparator;

    public RichTextAggregator(String csSeparator) {
        this.csSeparator = csSeparator.replace("\r\n", "\\par");
        this.csNewText = new StringBuilder();
    }

    public boolean addClip(byte[] lpData, int nDataSize, int nPos, int nCount) {
        if (lpData == null) {
            return false;
        }

        String pText = new String(lpData, 0, nDataSize, StandardCharsets.UTF_8);

        if (nPos != nCount - 1) {
            int lastIndex = pText.lastIndexOf('}');
            if (lastIndex != -1) {
                pText = pText.substring(0, lastIndex);
            }
        } else if (nPos >= 1) {
            int rtfIndex = pText.indexOf("{\\rtf1");
            if (rtfIndex != -1) {
                pText = pText.substring(rtfIndex + 6);
            }
        }

        csNewText.append(pText);

        if (nPos != nCount - 1) {
            csNewText.append(csSeparator);
        }

        return true;
    }

    public byte[] getByteArray() {
        String text = csNewText.toString();
        return text.getBytes(StandardCharsets.UTF_8);
    }

    public static void main(String[] args) {
        RichTextAggregator aggregator = new RichTextAggregator("\r\n");

        String sampleText1 = "{\\rtf1\\ansi Sample Text 1}";
        String sampleText2 = "{\\rtf1\\ansi Sample Text 2}";
        String sampleText3 = "{\\rtf1\\ansi Sample Text 3}";

        aggregator.addClip(sampleText1.getBytes(StandardCharsets.UTF_8), sampleText1.length(), 0, 3);
        aggregator.addClip(sampleText2.getBytes(StandardCharsets.UTF_8), sampleText2.length(), 1, 3);
        aggregator.addClip(sampleText3.getBytes(StandardCharsets.UTF_8), sampleText3.length(), 2, 3);

        byte[] aggregatedByteArray = aggregator.getByteArray();
        String aggregatedText = new String(aggregatedByteArray, StandardCharsets.UTF_8);

        System.out.println("Aggregated Text:");
        System.out.println(aggregatedText);
    }
}
