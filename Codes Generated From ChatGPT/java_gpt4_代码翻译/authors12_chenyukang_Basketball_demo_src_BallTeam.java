import java.util.ArrayList;
import java.util.List;

public class BallTeam {
    private Goal homeGoal;
    private Goal opponentsGoal;
    private Game game;
    private TeamColor color;
    private double distSqToBallOfClosestPlayer;
    private PlayerBase supportingPlayer;
    private PlayerBase receivingPlayer;
    private PlayerBase controllingPlayer;
    private PlayerBase playerClosestToBall;
    private StateMachine<BallTeam> stateMachine;
    private List<PlayerBase> players;

    public BallTeam(Goal homeGoal, Goal opponentsGoal, Game game, TeamColor color) {
        this.homeGoal = homeGoal;
        this.opponentsGoal = opponentsGoal;
        this.game = game;
        this.color = color;
        this.distSqToBallOfClosestPlayer = 0.0;
        this.supportingPlayer = null;
        this.receivingPlayer = null;
        this.controllingPlayer = null;
        this.playerClosestToBall = null;

        this.stateMachine = new StateMachine<>(this);
        this.stateMachine.setCurrentState(Attacking.getInstance());
        this.stateMachine.setPreviousState(Attacking.getInstance());
        this.stateMachine.setGlobalState(null);
        this.players = new ArrayList<>();
        createPlayers();
    }

    // Destructor-like method in Java
    public void cleanUp() {
        for (PlayerBase player : players) {
            player.cleanUp();
        }
    }

    public void update() {
        calculateClosestPlayerToBall();
        stateMachine.update();
        for (PlayerBase player : players) {
            player.update();
        }
    }

    public void render() {
        for (PlayerBase player : players) {
            player.render();
        }
    }

    // Other methods
    // ...
}
