import java.util.*;

class TreeNode {
    int n;
    int key;
    TreeNode left, right;

    TreeNode(int key) {
        n = 1;
        this.key = key;
        left = right = null;
    }
}

public class Main {
    private static int n;

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int N = sc.nextInt();
        for (int i = 1; i <= N; i++) {
            process(i, sc);
        }
    }

    public static int go(TreeNode t, int a) {
        t.n += 1;
        if (t.key <= a) {
            if (t.right != null) {
                return go(t.right, a);
            }
            t.right = new TreeNode(a);
            return 0;
        }
        int ret = 0;
        if (t.right != null) ret = t.right.n;
        ret++;
        if (t.left != null) {
            ret += go(t.left, a);
        } else {
            t.left = new TreeNode(a);
        }
        return ret;
    }

    public static void deltree(TreeNode t) {
        if (t.left != null) deltree(t.left);
        if (t.right != null) deltree(t.right);
    }

    public static void process(int dataId, Scanner sc) {
        n = sc.nextInt();
        TreeNode root = null;
        long ret = 0;
        for (int i = 0; i < n; i++) {
            int tmp = sc.nextInt();
            if (root == null) {
                root = new TreeNode(tmp);
                continue;
            }
            tmp = go(root, tmp);
            ret += tmp;
        }
        System.out.println(ret);
        deltree(root);
    }
}
