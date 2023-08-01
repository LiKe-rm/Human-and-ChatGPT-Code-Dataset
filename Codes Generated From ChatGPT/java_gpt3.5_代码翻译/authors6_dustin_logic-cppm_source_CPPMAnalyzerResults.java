import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class CPPMAnalyzerResults {

    private CPPMAnalyzerSettings settings;
    private CPPMAnalyzer analyzer;

    public CPPMAnalyzerResults(CPPMAnalyzer analyzer, CPPMAnalyzerSettings settings) {
        this.settings = settings;
        this.analyzer = analyzer;
    }

    // Add Frame class definition here
    // ...

    public void generateBubbleText(long frameIndex, Channel channel, DisplayBase displayBase) {
        // Clear result strings
        // ...

        Frame frame = getFrame(frameIndex);
        String resultString = String.format("%d:%d μS", frame.data2, frame.data1);

        // Add result strings
        // ...
    }

    public void wideExport(String file) throws IOException {
        try (BufferedWriter fileStream = new BufferedWriter(new FileWriter(file))) {
            long numFrames = getNumFrames();
            long triggerSample = analyzer.getTriggerSample();
            int sampleRate = analyzer.getSampleRate();

            // Calculate the number of channels
            int nchans = 0;
            int prevchan = 0;
            for (int i = 0; i < numFrames; i++) {
                Frame frame = getFrame(i);
                if (frame.data2 < prevchan) {
                    break;
                }
                nchans++;
                prevchan = frame.data2;
            }

            // Write header line
            fileStream.write("Time [s]");
            for (int i = 0; i < nchans; i++) {
                fileStream.write(",ch" + (i + 1));
            }
            fileStream.write(",error\n");

            // Write data lines
            for (int i = 0; i < numFrames; i += nchans) {
                Frame frame = getFrame(i);
                int flags = 0;

                String timeString = AnalyzerHelpers.getTimeString(frame.startingSampleInclusive, triggerSample, sampleRate);

                fileStream.write(timeString);

                for (int j = 0; j < nchans; j++) {
                    if (i + j >= numFrames) {
                        fileStream.write(",");
                        continue;
                    }

                    frame = getFrame(i + j);
                    flags |= frame.flags;

                    // Don't include bogus readings
                    if (frame.flags != 0) {
                        i++;
                        j--;
                        continue;
                    }

                    fileStream.write("," + frame.data1);

                    if (updateExportProgressAndCheckForCancel(i + j, numFrames)) {
                        return;
                    }
                }

                fileStream.write((flags == 0 ? "," : ",error") + "\n");
            }
        }
    }

    public void longExport(String file) throws IOException {
        try (BufferedWriter fileStream = new BufferedWriter(new FileWriter(file))) {
            long numFrames = getNumFrames();

            long triggerSample = analyzer.getTriggerSample();
            int sampleRate = analyzer.getSampleRate();

            // Write header line
            fileStream.write("Time [s],val,chan,error\n");

            // Write data lines
            for (int i = 0; i < numFrames; i++) {
                Frame frame = getFrame(i);

                String timeString = AnalyzerHelpers.getTimeString(frame.startingSampleInclusive, triggerSample, sampleRate);

                fileStream.write(String.format("%s,%s,%d,%s\n", timeString, frame.data1, frame.data2, (frame.flags == 0 ? "" : "error")));
            if (updateExportProgressAndCheckForCancel(i, numFrames)) {
                return;
            }
        }
    }
}

public void generateExportFile(String file, DisplayBase displayBase, int exportTypeUserId) throws IOException {
    if (exportTypeUserId == 0) {
        wideExport(file);
    } else {
        longExport(file);
    }
}

public void generateFrameTabularText(long frameIndex, DisplayBase displayBase) {
    Frame frame = getFrame(frameIndex);
    clearTabularText();

    if (frame.type == 0) {
        return;
    }

    String numberString = String.format("%d:%d", frame.data2, frame.data1);
    addTabularText(numberString);
}

public void generatePacketTabularText(long packetId, DisplayBase displayBase) {
    clearResultStrings();
    addResultString("not supported");
}

public void generateTransactionTabularText(long transactionId, DisplayBase displayBase) {
    clearResultStrings();
    addResultString("not supported");
}

// Add necessary helper methods and classes here, such as:
// - Frame class definition
// - getFrame(), getNumFrames()
// - updateExportProgressAndCheckForCancel()
// - clearResultStrings(), addResultString(), clearTabularText(), addTabularText()
// - AnalyzerHelpers.getTimeString()
// ...

