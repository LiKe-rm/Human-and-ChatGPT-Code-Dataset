import java.util.regex.Pattern;

public class RemoveLineFeeds {
    public RemoveLineFeeds() {
    }

    public boolean removeLineFeeds(DittoInfo dittoInfo, IClip clip) {
        boolean didSomething = false;
        IClipFormats formats = clip.getClips();
        if (formats != null) {
            didSomething = handleCFText(formats);

            didSomething |= handleCFUnicodeText(formats);

            didSomething |= handleRichText(formats);
        }

        return didSomething;
    }

    private boolean handleCFText(IClipFormats formats) {
        boolean didSomething = false;

        IClipFormat format = formats.findFormatEx(IClipFormats.CF_TEXT);
        if (format != null) {
            String stringData = format.getData();
            if (stringData != null) {
                stringData = stringData.replaceAll("\r\n", " ");
                format.setData(stringData);

                didSomething = true;
            }
        }

        return didSomething;
    }

    private boolean handleCFUnicodeText(IClipFormats formats) {
        boolean didSomething = false;

        IClipFormat format = formats.findFormatEx(IClipFormats.CF_UNICODETEXT);
        if (format != null) {
            String stringData = format.getData();
            if (stringData != null) {
                stringData = stringData.replaceAll("\r\n", " ");
                format.setData(stringData);

                didSomething = true;
            }
        }

        return didSomething;
    }

    private boolean handleRichText(IClipFormats formats) {
        boolean didSomething = false;

        IClipFormat format = formats.findFormatEx(IClipFormats.RICH_TEXT_FORMAT);
        if (format != null) {
            String stringData = format.getData();
            if (stringData != null) {
                stringData = stringData.replaceAll("\\\\par\r\n", " ");
                stringData = stringData.replaceAll("\\\\par ", " ");
                stringData = stringData.replaceAll("\\\\line ", " ");
                format.setData(stringData);

                didSomething = true;
            }
        }

        return didSomething;
    }
}
