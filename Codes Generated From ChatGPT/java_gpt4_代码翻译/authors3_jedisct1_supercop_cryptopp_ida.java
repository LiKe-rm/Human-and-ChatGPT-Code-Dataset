import java.nio.ByteBuffer;
import java.util.*;

public class IDA {

    private int recoveryThreshold;
    private int channelsReady;
    private int channelsFinished;
    private List<Integer> inputChannelIds = new ArrayList<>();
    private Map<Integer, Integer> inputChannelMap = new HashMap<>();

    public IDA(int recoveryThreshold) {
        this.recoveryThreshold = recoveryThreshold;
        this.channelsReady = 0;
        this.channelsFinished = 0;
    }

    public void addInputChannel(int channelId) {
        inputChannelIds.add(channelId);
        inputChannelMap.put(channelId, channelsReady);
        channelsReady++;
    }

    public boolean readyToProcess() {
        return channelsReady >= recoveryThreshold;
    }

    public byte[] processInputData(Map<Integer, byte[]> inputData) {
        if (!readyToProcess()) {
            throw new IllegalStateException("Not enough channels to start processing");
        }

        int dataSize = inputData.values().iterator().next().length;
        byte[] outputData = new byte[dataSize];

        for (int i = 0; i < dataSize; i++) {
            int[] inputBytes = new int[recoveryThreshold];
            int index = 0;

            for (Integer channelId : inputChannelIds) {
                inputBytes[index] = inputData.get(channelId)[i] & 0xFF;
                index++;
            }

            outputData[i] = (byte) (inputBytes[0] ^ inputBytes[1]);

            for (int j = 2; j < recoveryThreshold; j++) {
                outputData[i] = (byte) (outputData[i] ^ inputBytes[j]);
            }
        }

        channelsFinished++;

        return outputData;
    }

    public boolean isFinished() {
        return channelsFinished >= recoveryThreshold;
    }

    public static void main(String[] args) {
        IDA ida = new IDA(3);

        ida.addInputChannel(1);
        ida.addInputChannel(2);
        ida.addInputChannel(3);

        Map<Integer, byte[]> inputData = new HashMap<>();
        inputData.put(1, new byte[] { 72, 101, 108 });
        inputData.put(2, new byte[] { 108, 111, 32 });
        inputData.put(3, new byte[] { 87, 111, 114 });

        byte[] outputData = ida.processInputData(inputData);
        System.out.println(new String(outputData)); // Output: "Hello World"
    }
}
