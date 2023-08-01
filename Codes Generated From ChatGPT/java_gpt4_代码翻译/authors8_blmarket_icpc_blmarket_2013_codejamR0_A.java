import java.util.Scanner;

public class TicTacToe {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int T = scanner.nextInt();
        scanner.nextLine();

        for (int i = 1; i <= T; i++) {
            char[][] board = new char[4][4];
            for (int j = 0; j < 4; j++) {
                board[j] = scanner.nextLine().toCharArray();
            }

            System.out.printf("Case #%d: ", i);
            char result = process(board);
            switch (result) {
                case -1:
                    System.out.println("Draw");
                    break;
                case 0:
                    System.out.println("Game has not completed");
                    break;
                default:
                    System.out.printf("%c won%n", result);
                    break;
            }
        }
    }

    private static char acc(char a, char b) {
        if (a == 0 || a == 'T') return b;
        if (b == 'T') return a;
        if (a != b) return '.';
        return a;
    }

    private static char process(char[][] board) {
        boolean hasDot = false;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (board[i][j] == '.') hasDot = true;
            }
        }

        for (int i = 0; i < 4; i++) {
            char t1 = board[i][0];
            char t2 = board[0][i];
            for (int j = 1; j < 4; j++) {
                t1 = acc(t1, board[i][j]);
                t2 = acc(t2, board[j][i]);
            }
            if (t1 != '.') return t1;
            if (t2 != '.') return t2;
        }

        char t1 = board[0][0];
        char t2 = board[0][3];
        for (int i = 1; i < 4; i++) {
            t1 = acc(t1, board[i][i]);
            t2 = acc(t2, board[i][3 - i]);
        }
        if (t1 != '.') return t1;
        if (t2 != '.') return t2;

        if (hasDot) return 0;
        return -1;
    }
}
