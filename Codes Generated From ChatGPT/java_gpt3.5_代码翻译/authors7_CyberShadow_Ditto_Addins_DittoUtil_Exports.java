import java.util.ArrayList;
import java.util.List;

public class DittoUtils {
    private String name = "Ditto Utils";
    private int addinVersion = 1;
    private List<Function> supportedFunctions;

    public DittoUtils() {
        supportedFunctions = new ArrayList<>();
        supportedFunctions.add(new Function("PasteAnyAsText", "Paste Any Clip As Text", "Displays a list of clip formats allowing you to select one and paste the contents as text"));
        supportedFunctions.add(new Function("ConvertPathToHtmlImageTag", "Paste As html image link", "Converts a CF_DIB or CF_HDROP to a html format for pasting into outlook express"));
        supportedFunctions.add(new Function("ClearReadOnlyFlag", "Clear read only flag", "Clears read only flag on the types CF_HDROP, or files paths in text"));
        supportedFunctions.add(new Function("SetReadOnlyFlag", "Set read only flag", "Sets the read only flag on the types CF_HDROP, or files paths in text"));
        supportedFunctions.add(new Function("RemoveLineFeeds", "Paste Removing Line Feeds", "Removes all line feeds from text and rich text entries"));
    }

    public String getName() {
        return name;
    }

    public int getAddinVersion() {
        return addinVersion;
    }

    public List<Function> getSupportedFunctions() {
        return supportedFunctions;
    }

    public boolean pasteAnyAsText(DittoInfo dittoInfo, IClip clip) {
        return PasteAnyAsText.selectClipToPasteAsText(dittoInfo, clip);
    }

    public boolean convertPathToHtmlImageTag(DittoInfo dittoInfo, IClip clip) {
        PasteImageAsHtmlImage convert = new PasteImageAsHtmlImage();
        return convert.convertPathToHtmlImageTag(dittoInfo, clip);
    }

    public boolean clearReadOnlyFlag(DittoInfo dittoInfo, IClip clip) {
        ReadOnlyFlag readOnly = new ReadOnlyFlag();
        readOnly.resetReadOnlyFlag(dittoInfo, clip, true);
        return false;
    }

    public boolean setReadOnlyFlag(DittoInfo dittoInfo, IClip clip) {
        ReadOnlyFlag readOnly = new ReadOnlyFlag();
        readOnly.resetReadOnlyFlag(dittoInfo, clip, false);
        return false;
    }

    public boolean removeLineFeeds(DittoInfo dittoInfo, IClip clip) {
        RemoveLineFeeds remove = new RemoveLineFeeds();
        boolean didSomething = remove.removeLineFeeds(dittoInfo, clip);
        return didSomething;
    }
}
