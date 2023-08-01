import java.io.*;
import java.util.*;

class DataPoint {
    float x;
    float y;

    DataPoint(float x, float y) {
        this.x = x;
        this.y = y;
    }
}

public class GridVisualizer extends PApplet {
    ArrayList<DataPoint> data;
    ArrayList<DataPoint> grid;

    public static void main(String[] args) {
        PApplet.main("GridVisualizer");
    }

    public void settings() {
        size(400, 400);
    }

    public void setup() {
        loadData();
        buildGrid();
        matchDataToGrid();
        saveGridToFile();
        background(0);
    }

    public void draw() {
        float padding = 128;
        float scale = width - 2 * padding;
        pushMatrix();
        translate(padding, padding);
        scale(scale, scale);

        stroke(255);
        strokeWeight(6);

        float t = map(cos(millis() / 1000.0f), -1, 1, 0, 1);
        for (int i = 0; i < data.size(); i++) {
            DataPoint dataPoint = data.get(i);
            DataPoint gridPoint = grid.get(i);
            point(dataPoint.x * t + gridPoint.x * (1 - t),
                  dataPoint.y * t + gridPoint.y * (1 - t));
        }

        popMatrix();
    }

    public void keyPressed() {
        if (key == ' ') {
            setup();
        }
    }

    void loadData() {
        data = new ArrayList<>();
        String[] lines = loadStrings("data.tsv");
        for (String line : lines) {
            String[] chunks = split(line, "\t");
            if (chunks.length == 2) {
                data.add(new DataPoint(Float.parseFloat(chunks[0]), Float.parseFloat(chunks[1])));
            }
        }
    }

    void buildGrid() {
        grid = new ArrayList<>();
        int gridWidth = 120;
        int gridHeight = 119;
        float xStep = 1.0f / gridWidth;
        float yStep = 1.0f / gridHeight;
        for (int x = 0; x < gridWidth; x++) {
            for (int y = 0; y < gridHeight; y++) {
                grid.add(new DataPoint(x * xStep, y * yStep));
            }
        }
    }

    void matchDataToGrid() {
        // This is a placeholder function. In a real implementation, you would
        // use an algorithm like the one from the ofxAssignment library to match
        // the data points to the grid points.
    }

    void saveGridToFile() {
        PrintWriter out = createWriter("out.tsv");
        for (DataPoint point : grid) {
            out.println(point.x + "\t" + point.y);
        }
        out.flush();
        out.close();
    }
}
