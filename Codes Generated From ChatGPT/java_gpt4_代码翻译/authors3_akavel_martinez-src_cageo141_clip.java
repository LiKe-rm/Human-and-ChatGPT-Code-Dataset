import java.io.*;
import java.nio.file.*;

public class PolygonProcessing {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.err.println("Syntax: " + args[0] + " subject_pol clipping_pol result_pol [I|U|D|X]");
            System.exit(1);
        }
        if (args.length > 3 && args[3].charAt(0) != 'I' && args[3].charAt(0) != 'U' && args[3].charAt(0) != 'D' && args[3].charAt(0) != 'X') {
            System.err.println("Syntax: " + args[0] + " subject_pol clipping_pol result_pol [I|U|D|X]");
            System.err.println("The last parameter is optional. It is a character. It can be I (Intersection), U (Union), D (Difference) or X (eXclusive or)");
            System.exit(2);
        }

        // Load polygons from files
        Path subjectPath = Paths.get(args[0]);
        Path clippingPath = Paths.get(args[1]);
        Path outputPath = Paths.get(args[2]);

        Polygon subject = new Polygon(subjectPath);
        Polygon clipping = new Polygon(clippingPath);

        // Set operation type
        Martinez.BoolOpType op = Martinez.BoolOpType.INTERSECTION;
        GpcOp opVatti = GpcOp.INT;

        if (args.length > 3) {
            switch (args[3].charAt(0)) {
                case 'I':
                    op = Martinez.BoolOpType.INTERSECTION;
                    opVatti = GpcOp.INT;
                    break;
                case 'U':
                    op = Martinez.BoolOpType.UNION;
                    opVatti = GpcOp.UNION;
                    break;
                case 'D':
                    op = Martinez.BoolOpType.DIFFERENCE;
                    opVatti = GpcOp.DIFF;
                    break;
                case 'X':
                    op = Martinez.BoolOpType.XOR;
                    opVatti = GpcOp.XOR;
                    break;
            }
        }

        // Benchmark algorithms
        int ntests = 0;
        Polygon martinezResult = new Polygon();
        Timer timer = new Timer();
        int greinerResult;
        float martinezTime = 0;
        float greinerTime = 0;
        float vattiTime = 0;

        while (martinezTime < 1.0f && greinerTime < 1.0f && vattiTime < 1.0f) {
            ntests++;
            martinezResult.clear();

            // Martinez-Rueda's algorithm
            timer.start();
            Martinez mr = new Martinez(subject, clipping);
            mr.compute(op, martinezResult);
            timer.stop();
            martinezTime += timer.timeSecs();

            // Greiner-Hormann's algorithm
            Polygon greinerResult = new Polygon();
            timer.start();
            GreinerHormann gh = new GreinerHormann(subject, clipping);
            greinerResult = gh.boolop(op, greinerResult);
            timer.stop();
            greinerTime += timer.timeSecs();

            // Vatti's algorithm
            GpcPolygon subjectGpc = new GpcPolygon(subject);
            GpcPolygon clippingGpc = new GpcPolygon(clipping);
            GpcPolygon resultGpc = new GpcPolygon();
            timer.start();
            GpcPolygon.clip(opVatti, subjectGpc, clippingGpc, resultGpc);
            timer.stop();
            vattiTime += timer.timeSecs();
        }
        System.out.println("Martinez-Rueda's time: " + martinezTime / ntests);
        System.out.println("Vatti's time: " + vattiTime / ntests);
        System.out.println("Greiner-Hormann's time: " + greinerTime / ntests);
        System.out.println("Possible intersections: " + subject.nvertices() + " x " + clipping.nvertices() + " = " + subject.nvertices() * clipping.nvertices());
        System.out.println("Number of tests: " + ntests);
    
        // Save result to file
        try (BufferedWriter writer = Files.newBufferedWriter(outputPath)) {
            writer.write(martinezResult.toString());
        } catch (IOException e) {
            System.err.println("Can't open " + args[2]);
            e.printStackTrace();
        }
    }
}    