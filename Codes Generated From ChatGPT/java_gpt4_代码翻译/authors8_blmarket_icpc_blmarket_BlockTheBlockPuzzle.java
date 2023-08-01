import java.util.*;

public class BlockTheBlockPuzzle {
    private static final int[] dx = {0, -1, 1, 0};
    private static final int[] dy = {-1, 0, 0, 1};
    
    private List<String> board;
    private int[][][] label;
    private List<int[]>[] links;
    private boolean[] sink;
    private int ls = 0;
    
    public int minimumHoles(String[] board_) {
        int px = 0, py = 0;
        board = Arrays.asList(board_);
        int n = board.size();
        label = new int[n][n][2];
        links = new List[n * n * 2];
        sink = new boolean[n * n * 2];
        
        for (int i = 0; i < links.length; i++) {
            links[i] = new ArrayList<>();
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (board.get(i).charAt(j) == '$') {
                    px = i;
                    py = j;
                    break;
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if ((i - px) % 3 == 0 && (j - py) % 3 == 0 && board.get(i).charAt(j) != 'H') {
                    int n1 = label(i, j, 0);
                    int n2 = label(i, j, 1);
                    
                    if (board.get(i).charAt(j) == 'b') {
                        sink[n1] = true;
                    }
                    
                    addLink(n1, n2, 1);
                    
                    for (int k = 0; k < 4; k++) {
                        int nx = i + dx[k] * 3;
                        int ny = j + dy[k] * 3;
                        
                        if (nx < 0 || ny < 0 || nx >= n || ny >= n) {
                            continue;
                        }
                        
                        char c1 = board.get(i + dx[k]).charAt(j + dy[k]);
                        char c2 = board.get(i + dx[k] * 2).charAt(j + dy[k] * 2);
                        int flow = 0;
                        
                        if (c1 == 'b' || c2 == 'b') {
                            flow = 50000;
                        }
                        
                        flow += (c1 == '.') ? 1 : 0;
                        flow += (c2 == '.') ? 1 : 0;
                        
                        if (flow == 0) {
                            continue;
                        }
                        
                        int n3 = label(nx, ny, 0);
                        addLink(n2, n3, flow);
                    }
                }
            }
        }
        
        int sp = label(px, py, 1);
        int ret = 0;
        boolean[] back = new boolean[n * n * 2];
        
        while (true) {
            Arrays.fill(back, false);
            if (!tryFlow(sp, back)) {
                break;
            }
            ret++;
            
            if (ret > 5000) {
                return -1;
            }
        }
        
        return ret;
    }
    
    private int label(int x, int y, int z) {
        if (label[x][y][z] == 0) {
            label[x][y][z] = ++ls;
        }
        return label[x][y][z];
    }

    private void addLink(int s, int e, int f) {
        for (int[] link : links[s]) {
            if (link[0] == e) {
                link[1] += f;
                if (link[1] == 0) {
                    links[s].remove(link);
                }
                return;
            }
        }
        links[s].add(new int[]{e, f});
    }

    private boolean tryFlow(int sp, boolean[] back) {
        if (back[sp]) {
            return false;
        }
        if (sink[sp]) {
            return true;
        }

        back[sp] = true;

        for (int[] link : links[sp]) {
            int np = link[0];
            int flow = link[1];

            if (tryFlow(np, back)) {
                addLink(sp, np, -1);
                addLink(np, sp, 1);
                return true;
            }
        }
        return false;
    }

    public static void main(String[] args) {
        BlockTheBlockPuzzle puzzle = new BlockTheBlockPuzzle();
        String[] board = {
                "...........H....bb.....b...",
                "...........................",
                "........HH.b..b.....H......",
                ".............b.Hb..H.....H.",
                "....H........H.............",
                ".............HH..b.........",
                "b....H..........b.........b",
                "..HH.Hb....$.....H...b..H..",
                "..........H................",
                "..........H....HH..........",
                "...............H.........b.",
                "H...........bH....HbH..HbH.",
                "...H........H.............b",
                "........H.....b...H.H....H.",
                "................H....b...H.",
                "bb..........H....b..Hb.....",
                "..............b..H.........",
                "...H......b................",
                "b......H...HH..............",
                ".....H.....................",
                "..............H............",
                "..H.........b....b.........",
                "..........b................",
                "...b.bH..........H.........",
                "...HH..................H..H",
                "...........H......H........",
                "b........H............bb..."
        };
        System.out.println(puzzle.minimumHoles(board));
    }
}

